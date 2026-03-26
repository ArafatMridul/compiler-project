%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern int yylex(void);
extern int yyparse(void);
extern FILE *yyin;
extern int line_no;

static FILE *outfile;
static int indent_level = 0;
static int include_stdio = 0;
static int include_math = 0;
static int include_bool = 0;

static void emit_indent(void);
static void emit_line(const char *fmt, ...);
static char *dupstr(const char *s);
static char *fmtstr(const char *fmt, ...);
static void emit_include(const char *header);

void yyerror(const char *s);
%}

%define parse.error verbose

%union {
    char *str;
}

%token <str> IDENT NUMBER STRING_LITERAL HEADER
%token INCLUDE DEFINE MAIN
%token TYPE_INT TYPE_FLOAT TYPE_DOUBLE TYPE_LONG TYPE_CHAR TYPE_BOOL TYPE_VOID
%token RETURN PRINT IF ELIF ELSE THEN FOR WHILE_KW BREAK_KW CONTINUE_KW
%token ASSIGN AND OR NOT LE GE EQ NE

%type <str> type expr opt_expr arg_list_opt arg_list param_list_opt param_list param declaration opt_init assignment return_stmt print_stmt break_stmt continue_stmt call_expr

%left OR
%left AND
%left EQ NE
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right NOT UMINUS

%start program

%%

program
    : top_items main_block
    ;

top_items
    : top_items top_item
    | /* empty */
    ;

top_item
    : include_directive
    | define_directive
    | function_def
    ;

include_directive
    : INCLUDE HEADER
      {
          emit_include($2);
          free($2);
      }
    ;

define_directive
    : DEFINE IDENT expr
      {
          emit_line("#define %s %s", $2, $3);
      }
    ;

function_def
    : type IDENT '(' param_list_opt ')' '{'
      {
          emit_line("%s %s(%s) {", $1, $2, $4);
          indent_level++;
      }
      compound_tail
    ;

main_block
    : MAIN '(' ')' '{'
      {
          emit_line("int main() {");
          indent_level++;
      }
      compound_tail
    ;

compound_tail
    : stmt_list '}'
      {
          if (indent_level > 0) {
              indent_level--;
          }
          emit_line("}");
      }
    ;

stmt_list
    : stmt_list stmt
    | /* empty */
    ;

stmt
    : declaration ';'
      {
          emit_line("%s;", $1);
      }
    | assignment ';'
      {
          emit_line("%s;", $1);
      }
    | return_stmt ';'
      {
          emit_line("%s;", $1);
      }
    | print_stmt ';'
      {
          emit_line("%s;", $1);
      }
    | call_expr ';'
      {
          emit_line("%s;", $1);
      }
    | break_stmt ';'
      {
          emit_line("%s;", $1);
      }
    | continue_stmt ';'
      {
          emit_line("%s;", $1);
      }
    | block_stmt
    | if_stmt
    | while_stmt
    | for_stmt
    | ';'
      {
      }
    ;

block_stmt
    : '{'
      {
          emit_line("{");
          indent_level++;
      }
      compound_tail
    ;

if_stmt
    : IF expr THEN '{'
      {
          emit_line("if (%s) {", $2);
          indent_level++;
      }
      compound_tail if_tail
    ;

if_tail
    : /* empty */
    | ELIF expr THEN '{'
      {
          emit_line("else if (%s) {", $2);
          indent_level++;
      }
      compound_tail if_tail
    | ELSE '{'
      {
          emit_line("else {");
          indent_level++;
      }
      compound_tail
    ;

while_stmt
    : WHILE_KW expr '{'
      {
          emit_line("while (%s) {", $2);
          indent_level++;
      }
      compound_tail
    ;

for_stmt
    : FOR '(' opt_expr ';' opt_expr ';' opt_expr ')' '{'
      {
          emit_line("for (%s; %s; %s) {", $3, $5, $7);
          indent_level++;
      }
      compound_tail
    ;

declaration
    : type IDENT opt_init
      {
          $$ = fmtstr("%s %s%s", $1, $2, $3);
      }
    ;

opt_init
    : /* empty */
      {
          $$ = dupstr("");
      }
    | ASSIGN expr
      {
          $$ = fmtstr(" = %s", $2);
      }
    ;

assignment
    : IDENT ASSIGN expr
      {
          $$ = fmtstr("%s = %s", $1, $3);
      }
    ;

return_stmt
    : RETURN expr
      {
          $$ = fmtstr("return %s", $2);
      }
    ;

print_stmt
    : PRINT '(' arg_list_opt ')'
      {
          $$ = fmtstr("printf(%s)", $3);
      }
    ;

break_stmt
    : BREAK_KW
      {
          $$ = dupstr("break");
      }
    ;

continue_stmt
    : CONTINUE_KW
      {
          $$ = dupstr("continue");
      }
    ;

call_expr
    : IDENT '(' arg_list_opt ')'
      {
          $$ = fmtstr("%s(%s)", $1, $3);
      }
    ;

arg_list_opt
    : /* empty */
      {
          $$ = dupstr("");
      }
    | arg_list
      {
          $$ = $1;
      }
    ;

arg_list
    : expr
      {
          $$ = $1;
      }
    | arg_list ',' expr
      {
          $$ = fmtstr("%s, %s", $1, $3);
      }
    ;

param_list_opt
    : /* empty */
      {
          $$ = dupstr("");
      }
    | param_list
      {
          $$ = $1;
      }
    ;

param_list
    : param
      {
          $$ = $1;
      }
    | param_list ',' param
      {
          $$ = fmtstr("%s, %s", $1, $3);
      }
    ;

param
    : type IDENT
      {
          $$ = fmtstr("%s %s", $1, $2);
      }
    ;

opt_expr
    : /* empty */
      {
          $$ = dupstr("");
      }
    | expr
      {
          $$ = $1;
      }
    ;

expr
    : IDENT
      {
          $$ = $1;
      }
    | NUMBER
      {
          $$ = $1;
      }
    | STRING_LITERAL
      {
          $$ = $1;
      }
    | call_expr
      {
          $$ = $1;
      }
    | '(' expr ')'
      {
          $$ = fmtstr("(%s)", $2);
      }
    | expr '+' expr
      {
          $$ = fmtstr("%s + %s", $1, $3);
      }
    | expr '-' expr
      {
          $$ = fmtstr("%s - %s", $1, $3);
      }
    | expr '*' expr
      {
          $$ = fmtstr("%s * %s", $1, $3);
      }
    | expr '/' expr
      {
          $$ = fmtstr("%s / %s", $1, $3);
      }
    | expr '%' expr
      {
          $$ = fmtstr("%s %% %s", $1, $3);
      }
    | expr '<' expr
      {
          $$ = fmtstr("%s < %s", $1, $3);
      }
    | expr '>' expr
      {
          $$ = fmtstr("%s > %s", $1, $3);
      }
    | expr LE expr
      {
          $$ = fmtstr("%s <= %s", $1, $3);
      }
    | expr GE expr
      {
          $$ = fmtstr("%s >= %s", $1, $3);
      }
    | expr EQ expr
      {
          $$ = fmtstr("%s == %s", $1, $3);
      }
    | expr NE expr
      {
          $$ = fmtstr("%s != %s", $1, $3);
      }
    | expr AND expr
      {
          $$ = fmtstr("%s && %s", $1, $3);
      }
    | expr OR expr
      {
          $$ = fmtstr("%s || %s", $1, $3);
      }
    | NOT expr
      {
          $$ = fmtstr("!%s", $2);
      }
    | '-' expr %prec UMINUS
      {
          $$ = fmtstr("-%s", $2);
      }
    ;

type
    : TYPE_INT
      {
          $$ = dupstr("int");
      }
    | TYPE_FLOAT
      {
          $$ = dupstr("float");
      }
    | TYPE_DOUBLE
      {
          $$ = dupstr("double");
      }
    | TYPE_LONG
      {
          $$ = dupstr("long int");
      }
    | TYPE_CHAR
      {
          $$ = dupstr("char");
      }
    | TYPE_BOOL
      {
          $$ = dupstr("bool");
      }
    | TYPE_VOID
      {
          $$ = dupstr("void");
      }
    ;

%%

static void emit_indent(void) {
    for (int i = 0; i < indent_level; i++) {
        fputs("    ", outfile);
    }
}

static void emit_line(const char *fmt, ...) {
    va_list ap;
    emit_indent();
    va_start(ap, fmt);
    vfprintf(outfile, fmt, ap);
    va_end(ap);
    fputc('\n', outfile);
}

static char *dupstr(const char *s) {
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (!copy) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    memcpy(copy, s, len);
    return copy;
}

static char *fmtstr(const char *fmt, ...) {
    va_list ap;
    va_list copy;
    int needed;
    char *buf;

    va_start(ap, fmt);
    va_copy(copy, ap);
    needed = vsnprintf(NULL, 0, fmt, copy);
    va_end(copy);

    if (needed < 0) {
        va_end(ap);
        fprintf(stderr, "Formatting error\n");
        exit(1);
    }

    buf = malloc((size_t)needed + 1);
    if (!buf) {
        va_end(ap);
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }

    vsnprintf(buf, (size_t)needed + 1, fmt, ap);
    va_end(ap);
    return buf;
}

static void emit_include(const char *header) {
    if (strcmp(header, "<stdio.h>") == 0) {
        if (include_stdio) return;
        include_stdio = 1;
    } else if (strcmp(header, "<math.h>") == 0) {
        if (include_math) return;
        include_math = 1;
    } else if (strcmp(header, "<stdbool.h>") == 0) {
        if (include_bool) return;
        include_bool = 1;
    }

    emit_line("#include %s", header);
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse error on line %d: %s\n", line_no, s);
}

int main(int argc, char **argv) {
    const char *input_path = (argc > 1) ? argv[1] : "input.txt";
    const char *output_path = (argc > 2) ? argv[2] : "output.c";
    FILE *infile = fopen(input_path, "r");

    if (!infile) {
        fprintf(stderr, "Error: Cannot open %s\n", input_path);
        return 1;
    }

    outfile = fopen(output_path, "w");
    if (!outfile) {
        fprintf(stderr, "Error: Cannot create %s\n", output_path);
        fclose(infile);
        return 1;
    }

    fprintf(outfile, "#include <stdio.h>\n");
    fprintf(outfile, "#include <math.h>\n");
    fprintf(outfile, "#include <stdbool.h>\n\n");
    include_stdio = 1;
    include_math = 1;
    include_bool = 1;

    yyin = infile;
    if (yyparse() != 0) {
        fclose(infile);
        fclose(outfile);
        return 1;
    }

    fclose(infile);
    fclose(outfile);

    printf("output.c generated successfully.\n");
    printf("Total lines processed: %d\n", line_no);
    return 0;
}
