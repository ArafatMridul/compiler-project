%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>

extern int yylex(void);
extern FILE *yyin;
extern int line_no;
extern char last_token_text[];
extern int last_token_line;
extern char current_line_text[];

static FILE *outf;
static int indent_level = 0;
static int syntax_error_count = 0;
static int semantic_error_count = 0;
static struct Function *current_function = NULL;
static char **g_source_lines = NULL;
static int g_source_line_count = 0;

typedef enum {
    T_INT,
    T_FLOAT,
    T_DOUBLE,
    T_LONG,
    T_CHAR,
    T_BOOL,
    T_VOID,
    T_STRING,
    T_UNKNOWN,
    T_ERROR
} TypeKind;

typedef struct Expr Expr;
typedef struct ExprList ExprList;
typedef struct Param Param;
typedef struct Stmt Stmt;
typedef struct Branch Branch;
typedef struct Function Function;
typedef struct Include Include;
typedef struct Define Define;
typedef struct Symbol Symbol;
typedef struct Scope Scope;
typedef struct IfTail IfTail;

typedef enum {
    EXPR_IDENT,
    EXPR_NUMBER,
    EXPR_STRING,
    EXPR_CALL,
    EXPR_INDEX,
    EXPR_BINARY,
    EXPR_UNARY
} ExprKind;

typedef enum {
    STMT_DECL,
    STMT_ASSIGN,
    STMT_INDEX_ASSIGN,
    STMT_RETURN,
    STMT_PRINT,
    STMT_BREAK,
    STMT_CONTINUE,
    STMT_EXPR,
    STMT_BLOCK,
    STMT_IF,
    STMT_WHILE,
    STMT_FOR,
    STMT_SWITCH
} StmtKind;

struct Expr {
    int line;
    ExprKind kind;
    TypeKind inferred;
    int is_array;
    int array_size;
    char *text;
    char *op;
    Expr *left;
    Expr *right;
    Expr *index;
    ExprList *args;
};

struct ExprList {
    Expr *expr;
    ExprList *next;
};

struct Param {
    char *name;
    TypeKind type;
    int line;
    Param *next;
};

struct Branch {
    Expr *cond;
    Stmt *body;
    int line;
    Branch *next;
};

struct Stmt {
    int line;
    StmtKind kind;
    Stmt *next;
    union {
        struct {
            TypeKind type;
            char *name;
            int is_array;
            int array_size;
            Expr *init;
            ExprList *array_init;
        } decl;
        struct {
            char *name;
            Expr *value;
        } assign;
        struct {
            char *name;
            Expr *index;
            Expr *value;
        } index_assign;
        struct {
            Expr *expr;
        } ret;
        struct {
            ExprList *args;
        } print;
        struct {
            Expr *expr;
        } expr_stmt;
        struct {
            Stmt *stmts;
        } block;
        struct {
            Expr *cond;
            Stmt *then_branch;
            Branch *elifs;
            Stmt *else_branch;
        } if_stmt;
        struct {
            Expr *cond;
            Stmt *body;
        } while_stmt;
        struct {
            Expr *init;
            Expr *cond;
            Expr *post;
            Stmt *body;
            int has_init_decl;
            TypeKind init_decl_type;
            char *init_decl_name;
            Expr *init_decl_value;
        } for_stmt;
        struct {
            Expr *expr;
            Branch *cases;
            Stmt *default_branch;
        } switch_stmt;
    } u;
};

struct Function {
    char *name;
    TypeKind return_type;
    Param *params;
    Stmt *body;
    int line;
    int is_main;
    Function *next;
};

struct Include {
    char *header;
    int line;
    Include *next;
};

struct Define {
    char *name;
    Expr *value;
    int line;
    Define *next;
};

struct Symbol {
    char *name;
    TypeKind type;
    int is_array;
    int array_size;
    int is_function;
    TypeKind return_type;
    Param *params;
    Symbol *next;
};

struct Scope {
    Symbol *symbols;
    Scope *parent;
};

struct IfTail {
    Branch *elifs;
    Stmt *else_branch;
};

static Include *g_includes = NULL;
static Include *g_includes_tail = NULL;
static Define *g_defines = NULL;
static Define *g_defines_tail = NULL;
static Function *g_functions = NULL;
static Function *g_functions_tail = NULL;
static Function *g_main_fn = NULL;
static Scope *scope_stack = NULL;

static void yyerror(const char *s);
static void semantic_error(int line, const char *fmt, ...);
static void semantic_error_at(int line, const char *focus_token, const char *fmt, ...);
static void syntax_error(int line, const char *fmt, ...);
static void print_error_context(int line, const char *focus_token);
static void print_did_you_mean(const char *input, int include_symbols, int include_functions, int include_keywords, int include_types);
static void load_source_lines(const char *path);
static void free_source_lines(void);
static const char *source_line_at(int line);
static TypeKind type_from_string(const char *name);
static const char *type_name(TypeKind type);
static int is_numeric(TypeKind type);
static int is_integral(TypeKind type);
static int is_bool_like(TypeKind type);
static int type_compatible(TypeKind expected, TypeKind actual);
static TypeKind numeric_promote(TypeKind left, TypeKind right);
static Expr *make_expr_ident(char *name, int line);
static Expr *make_expr_number(char *text, int line);
static Expr *make_expr_string(char *text, int line);
static Expr *make_expr_call(char *name, ExprList *args, int line);
static Expr *make_expr_index(char *name, Expr *index, int line);
static Expr *make_expr_binary(char *op, Expr *left, Expr *right, int line);
static Expr *make_expr_unary(char *op, Expr *expr, int line);
static ExprList *expr_list_single(Expr *expr);
static ExprList *expr_list_append(ExprList *list, Expr *expr);
static Param *param_new(const char *type_name, char *name, int line);
static Param *param_append(Param *list, Param *node);
static Branch *branch_new(Expr *cond, Stmt *body, int line);
static Stmt *stmt_new(StmtKind kind, int line);
static Stmt *stmt_append(Stmt *list, Stmt *node);
static Stmt *make_decl_stmt(const char *type_name, char *name, Expr *init, ExprList *array_init, int line);
static Stmt *make_assign_stmt(char *name, Expr *value, int line);
static Stmt *make_index_assign_stmt(char *name, Expr *index, Expr *value, int line);
static Stmt *make_return_stmt(Expr *expr, int line);
static Stmt *make_print_stmt(ExprList *args, int line);
static Stmt *make_expr_stmt(Expr *expr, int line);
static Stmt *make_block_stmt(Stmt *stmts, int line);
static Stmt *make_if_stmt(Expr *cond, Stmt *then_branch, Branch *elifs, Stmt *else_branch, int line);
static Stmt *make_while_stmt(Expr *cond, Stmt *body, int line);
static Stmt *make_for_stmt(Expr *init, Expr *cond, Expr *post, Stmt *body, int line);
static Stmt *make_switch_stmt(Expr *expr, Branch *cases, Stmt *default_branch, int line);
static Stmt *make_break_stmt(int line);
static Stmt *make_continue_stmt(int line);
static Function *function_new(char *name, const char *return_type_name, Param *params, Stmt *body, int line, int is_main);
static void add_include(char *header, int line);
static void add_define(char *name, Expr *value, int line);
static void add_function(Function *fn);
static void set_main(Function *fn);
static Scope *push_scope(void);
static void pop_scope(void);
static Symbol *scope_lookup(Scope *scope, const char *name);
static Symbol *lookup_symbol(const char *name);
static Symbol *scope_add_symbol(const char *name, TypeKind type, int line);
static Function *find_function(const char *name);
static void add_function_symbol(const Function *fn);
static void analyze_program(void);
static void analyze_function(Function *fn);
static void analyze_stmt_list(Stmt *stmt);
static void analyze_stmt(Stmt *stmt);
static TypeKind infer_expr(Expr *expr);
static void emit_program(const char *path);
static void emit_include(FILE *f, const char *header);
static void emit_indent(FILE *f);
static void emit_expr_prec(FILE *f, Expr *expr, int parent_prec);
static void emit_stmt_list(FILE *f, Stmt *stmt);
static void emit_stmt(FILE *f, Stmt *stmt);
static void emit_expr(FILE *f, Expr *expr);
static void emit_params(FILE *f, Param *params);
static int includes_contains(const char *header);
static void emit_binary_search_helper(FILE *f);
static void emit_array_helpers(FILE *f);
static int stmt_list_needs_switch_break(Stmt *stmt);
%}
%define parse.error detailed
%union {
    char *str;
    void *ptr;
}

%token <str> IDENT NUMBER STRING_LITERAL HEADER
%token INCLUDE DEFINE MAIN
%token TYPE_INT TYPE_FLOAT TYPE_DOUBLE TYPE_LONG TYPE_CHAR TYPE_BOOL TYPE_VOID
%token RETURN PRINT IF ELIF ELSE THEN FOR WHILE_KW BREAK_KW CONTINUE_KW
%token CHOOSE WHEN BASE_CHOICE
%token ASSIGN AND OR NOT LE GE EQ NE

%type <str> type
%type <ptr> expr opt_expr opt_init
%type <ptr> arg_list_opt arg_list
%type <ptr> param param_list_opt param_list
%type <ptr> stmt stmt_list block function_def main_block if_stmt while_stmt for_stmt
%type <ptr> if_tail
%type <ptr> switch_stmt switch_tail
%type <ptr> extra_stmts_opt extra_stmt_list

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
    : top_items main_block extra_stmts_opt
      {
          if (!g_main_fn) {
              syntax_error(line_no, "missing Start_From_Here() block");
          }
          if ($3) {
              g_main_fn->body = stmt_append(g_main_fn->body, (Stmt *)$3);
          }
      }
    ;

top_items
    : top_items top_item
    | /* empty */
    ;

extra_stmts_opt
        : /* empty */
            {
                    $$ = NULL;
            }
        | extra_stmt_list
            {
                    $$ = $1;
            }
        ;

extra_stmt_list
        : extra_stmt_list stmt
            {
                    $$ = stmt_append($1, $2);
            }
        | stmt
            {
                    $$ = $1;
            }
        ;

top_item
        : INCLUDE HEADER
            {
                    add_include($2, line_no);
            }
        | DEFINE IDENT expr
            {
                    add_define($2, $3, line_no);
            }
        | function_def
        ;

function_def
        /* Original C-style: return_type name(params) { ... } */
        : type IDENT '(' param_list_opt ')' block
            {
                    add_function(function_new($2, $1, $4, $6, line_no, 0));
                    $$ = NULL;
            }
        /* New custom style: name(params): return_type => { ... } */
        | IDENT '(' param_list_opt ')' ':' type ASSIGN '>' block
            {
              add_function(function_new($1, $6, $3, $9, line_no, 0));
                    $$ = NULL;
            }
        ;

main_block
    : MAIN '(' ')' block
      {
          set_main(function_new(strdup("main"), "int", NULL, $4, line_no, 1));
          $$ = NULL;
      }
    ;

block
    : '{' stmt_list '}'
      {
          $$ = $2;
      }
        | '{' stmt_list error '}'
            {
                    yyerrok;
                    $$ = $2;
            }
    ;

stmt_list
    : stmt_list stmt
      {
          $$ = stmt_append($1, $2);
      }
    | /* empty */
      {
          $$ = NULL;
      }
    ;

stmt
    : type IDENT opt_init ';'
      {
          $$ = make_decl_stmt($1, $2, $3, NULL, line_no);
      }
        | type IDENT '[' NUMBER ']' ';'
            {
                    $$ = make_decl_stmt($1, $2, NULL, NULL, line_no);
                    ((Stmt *)$$)->u.decl.is_array = 1;
                    ((Stmt *)$$)->u.decl.array_size = atoi($4);
            }
        | type IDENT '[' NUMBER ']' ASSIGN '[' arg_list_opt ']' ';'
            {
                    $$ = make_decl_stmt($1, $2, NULL, (ExprList *)$8, line_no);
                    ((Stmt *)$$)->u.decl.is_array = 1;
                    ((Stmt *)$$)->u.decl.array_size = atoi($4);
            }
        | IDENT IDENT opt_init ';'
            {
                    semantic_error_at(line_no, $1, "unknown type '%s'", $1);
                    print_did_you_mean($1, 0, 0, 0, 1);
                    $$ = NULL;
            }
    | IDENT ASSIGN expr ';'
      {
          $$ = make_assign_stmt($1, $3, line_no);
      }
        | IDENT '[' expr ']' ASSIGN expr ';'
            {
                    $$ = make_index_assign_stmt($1, $3, $6, line_no);
            }
    | RETURN expr ';'
      {
          $$ = make_return_stmt($2, line_no);
      }
    | PRINT '(' arg_list_opt ')' ';'
      {
          $$ = make_print_stmt($3, line_no);
      }
    | expr ';'
      {
          $$ = make_expr_stmt($1, line_no);
      }
    | BREAK_KW ';'
      {
          $$ = make_break_stmt(line_no);
      }
    | CONTINUE_KW ';'
      {
          $$ = make_continue_stmt(line_no);
      }
    | if_stmt
    | while_stmt
    | for_stmt
        | switch_stmt
    | block
      {
          $$ = make_block_stmt($1, line_no);
      }
    | ';'
      {
          $$ = NULL;
      }
        | error ';'
            {
                    yyerrok;
                    $$ = NULL;
            }
    ;

if_stmt
        : IF expr block if_tail
            {
                                        IfTail *tail = (IfTail *)$4;
                                        $$ = make_if_stmt($2, $3, tail->elifs, tail->else_branch, line_no);
            }
        | IF expr THEN block if_tail
            {
                                        IfTail *tail = (IfTail *)$5;
                                        $$ = make_if_stmt($2, $4, tail->elifs, tail->else_branch, line_no);
            }
        ;

if_tail
    : /* empty */
      {
          IfTail *tail = malloc(sizeof(IfTail));
          if (!tail) {
              fprintf(stderr, "Out of memory\n");
              exit(1);
          }
          tail->elifs = NULL;
          tail->else_branch = NULL;
          $$ = tail;
      }
    | ELIF expr block if_tail
      {
          Branch *node = branch_new($2, $3, line_no);
          IfTail *tail = (IfTail *)$4;
          node->next = tail->elifs;
          IfTail *out = malloc(sizeof(IfTail));
          if (!out) {
              fprintf(stderr, "Out of memory\n");
              exit(1);
          }
          out->elifs = node;
          out->else_branch = tail->else_branch;
          $$ = out;
      }
    | ELSE block
      {
          IfTail *out = malloc(sizeof(IfTail));
          if (!out) {
              fprintf(stderr, "Out of memory\n");
              exit(1);
          }
          out->elifs = NULL;
          out->else_branch = $2;
          $$ = out;
      }
    ;

switch_stmt
        : CHOOSE '(' expr ')' '{' switch_tail '}'
            {
                    IfTail *tail = (IfTail *)$6;
                    $$ = make_switch_stmt($3, tail->elifs, tail->else_branch, line_no);
            }
        ;

switch_tail
        : /* empty */
            {
                    IfTail *tail = malloc(sizeof(IfTail));
                    if (!tail) {
                            fprintf(stderr, "Out of memory\n");
                            exit(1);
                    }
                    tail->elifs = NULL;
                    tail->else_branch = NULL;
                    $$ = tail;
            }
        | WHEN expr ':' block switch_tail
            {
                    Branch *node = branch_new($2, $4, line_no);
                    IfTail *tail = (IfTail *)$5;
                    node->next = tail->elifs;
                    IfTail *out = malloc(sizeof(IfTail));
                    if (!out) {
                            fprintf(stderr, "Out of memory\n");
                            exit(1);
                    }
                    out->elifs = node;
                    out->else_branch = tail->else_branch;
                    $$ = out;
            }
        | BASE_CHOICE ':' block
            {
                    IfTail *out = malloc(sizeof(IfTail));
                    if (!out) {
                            fprintf(stderr, "Out of memory\n");
                            exit(1);
                    }
                    out->elifs = NULL;
                    out->else_branch = $3;
                    $$ = out;
            }
        ;

while_stmt
    : WHILE_KW expr block
      {
          $$ = make_while_stmt($2, $3, line_no);
      }
    ;

for_stmt
    : FOR '(' opt_expr ';' opt_expr ';' opt_expr ')' block
      {
          $$ = make_for_stmt($3, $5, $7, $9, line_no);
            }
        | FOR '(' type IDENT ASSIGN expr ';' opt_expr ';' opt_expr ')' block
            {
                Stmt *loop = make_for_stmt(NULL, $8, $10, $12, line_no);
                loop->u.for_stmt.has_init_decl = 1;
                loop->u.for_stmt.init_decl_type = type_from_string($3);
                loop->u.for_stmt.init_decl_name = $4;
                loop->u.for_stmt.init_decl_value = $6;
                $$ = loop;
            }
    ;

param_list_opt
    : /* empty */
      {
          $$ = NULL;
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
          $$ = param_append($1, $3);
      }
    ;

param
    : type IDENT
      {
          $$ = param_new($1, $2, line_no);
      }
    ;

arg_list_opt
    : /* empty */
      {
          $$ = NULL;
      }
    | arg_list
      {
          $$ = $1;
      }
    ;

arg_list
    : expr
      {
          $$ = expr_list_single($1);
      }
    | arg_list ',' expr
      {
          $$ = expr_list_append($1, $3);
      }
    ;

opt_expr
    : /* empty */
      {
          $$ = NULL;
      }
    | expr
      {
          $$ = $1;
      }
    ;

opt_init
    : /* empty */
      {
          $$ = NULL;
      }
    | ASSIGN expr
      {
          $$ = $2;
      }
    ;

expr
    : IDENT
      {
          $$ = make_expr_ident($1, line_no);
      }
        | IDENT '[' expr ']'
            {
                    $$ = make_expr_index($1, $3, line_no);
            }
    | IDENT ASSIGN expr
      {
          Expr *lhs = make_expr_ident($1, line_no);
          $$ = make_expr_binary(strdup("="), lhs, $3, line_no);
      }
    | NUMBER
      {
          $$ = make_expr_number($1, line_no);
      }
    | STRING_LITERAL
      {
          $$ = make_expr_string($1, line_no);
      }
    | IDENT '(' arg_list_opt ')'
      {
          $$ = make_expr_call($1, $3, line_no);
      }
    | '(' expr ')'
      {
          $$ = $2;
      }
    | expr '+' expr
      {
          $$ = make_expr_binary(strdup("+"), $1, $3, line_no);
      }
    | expr '-' expr
      {
          $$ = make_expr_binary(strdup("-"), $1, $3, line_no);
      }
    | expr '*' expr
      {
          $$ = make_expr_binary(strdup("*"), $1, $3, line_no);
      }
    | expr '/' expr
      {
          $$ = make_expr_binary(strdup("/"), $1, $3, line_no);
      }
    | expr '%' expr
      {
          $$ = make_expr_binary(strdup("%"), $1, $3, line_no);
      }
    | expr '<' expr
      {
          $$ = make_expr_binary(strdup("<"), $1, $3, line_no);
      }
    | expr '>' expr
      {
          $$ = make_expr_binary(strdup(">"), $1, $3, line_no);
      }
    | expr LE expr
      {
          $$ = make_expr_binary(strdup("<="), $1, $3, line_no);
      }
    | expr GE expr
      {
          $$ = make_expr_binary(strdup(">="), $1, $3, line_no);
      }
    | expr EQ expr
      {
          $$ = make_expr_binary(strdup("=="), $1, $3, line_no);
      }
    | expr NE expr
      {
          $$ = make_expr_binary(strdup("!="), $1, $3, line_no);
      }
    | expr AND expr
      {
          $$ = make_expr_binary(strdup("&&"), $1, $3, line_no);
      }
    | expr OR expr
      {
          $$ = make_expr_binary(strdup("||"), $1, $3, line_no);
      }
    | NOT expr
      {
          $$ = make_expr_unary(strdup("!"), $2, line_no);
      }
    | '-' expr %prec UMINUS
      {
          $$ = make_expr_unary(strdup("-"), $2, line_no);
      }
    ;

type
    : TYPE_INT    { $$ = strdup("int"); }
    | TYPE_FLOAT  { $$ = strdup("float"); }
    | TYPE_DOUBLE { $$ = strdup("double"); }
    | TYPE_LONG   { $$ = strdup("long int"); }
    | TYPE_CHAR   { $$ = strdup("char"); }
    | TYPE_BOOL   { $$ = strdup("bool"); }
    | TYPE_VOID   { $$ = strdup("void"); }
    ;

%%

static const char *k_language_keywords[] = {
    "Start_From_Here",
    "IF", "ELIF", "ELSE", "THEN",
    "FOR", "until_false", "snap", "next_iter",
    "give_back", "console.out",
    "#=>", "#denote",
    "BOTH", "EITHER", "NEGATE",
    "CHOOSE", "WHEN", "BASE_CHOICE"
};

static const char *k_language_types[] = {
    "num", "fnum", "dnum", "lonum", "ch", "bol", "empty",
    "int", "float", "double", "long", "char", "bool", "void"
};

static const char *k_builtin_functions[] = {
    "binary_search",
    "sort", "find", "map", "filter", "reduce",
    "raise_to", "square_root", "magnitude", "round_down", "round_up", "ln",
    "SIN", "COS", "TAN"
};

static int min3(int a, int b, int c) {
    int m = a < b ? a : b;
    return m < c ? m : c;
}

static int edit_distance_ci(const char *a, const char *b, int max_dist) {
    if (!a || !b) return max_dist + 1;
    size_t n = strlen(a);
    size_t m = strlen(b);
    size_t diff = n > m ? n - m : m - n;
    if ((int)diff > max_dist) return max_dist + 1;

    int *prev = malloc((m + 1) * sizeof(int));
    int *curr = malloc((m + 1) * sizeof(int));
    if (!prev || !curr) {
        free(prev);
        free(curr);
        return max_dist + 1;
    }

    for (size_t j = 0; j <= m; j++) prev[j] = (int)j;

    for (size_t i = 1; i <= n; i++) {
        curr[0] = (int)i;
        int row_min = curr[0];
        for (size_t j = 1; j <= m; j++) {
            int cost = tolower((unsigned char)a[i - 1]) == tolower((unsigned char)b[j - 1]) ? 0 : 1;
            curr[j] = min3(prev[j] + 1, curr[j - 1] + 1, prev[j - 1] + cost);
            if (curr[j] < row_min) row_min = curr[j];
        }
        if (row_min > max_dist) {
            free(prev);
            free(curr);
            return max_dist + 1;
        }
        int *tmp = prev;
        prev = curr;
        curr = tmp;
    }

    int dist = prev[m];
    free(prev);
    free(curr);
    return dist;
}

static void consider_candidate(const char *input, const char *candidate, const char **best, int *best_dist) {
    if (!input || !candidate || !best || !best_dist) return;
    if (strcmp(input, candidate) == 0) return;
    int dist = edit_distance_ci(input, candidate, 3);
    if (dist < *best_dist) {
        *best = candidate;
        *best_dist = dist;
    }
}

static const char *source_line_at(int line) {
    if (line <= 0 || line > g_source_line_count || !g_source_lines) return NULL;
    return g_source_lines[line - 1];
}

static void print_error_context(int line, const char *focus_token) {
    const char *src = source_line_at(line);
    if ((!src || src[0] == '\0') && current_line_text[0] != '\0') {
        src = current_line_text;
    }
    if (!src || src[0] == '\0') return;

    fprintf(stderr, "  %s\n", src);
    fprintf(stderr, "  ");

    int col = 0;
    if (focus_token && focus_token[0] != '\0') {
        const char *pos = strstr(src, focus_token);
        if (pos) col = (int)(pos - src);
    }

    for (int i = 0; i < col; i++) {
        fputc(src[i] == '\t' ? '\t' : ' ', stderr);
    }
    fputc('^', stderr);

    if (focus_token && focus_token[0] != '\0') {
        size_t n = strlen(focus_token);
        for (size_t i = 1; i < n; i++) {
            fputc('~', stderr);
        }
    }
    fputc('\n', stderr);
}

static void print_did_you_mean(const char *input, int include_symbols, int include_functions, int include_keywords, int include_types) {
    const char *best = NULL;
    int best_dist = 4;
    if (!input || !input[0]) return;

    if (include_keywords) {
        size_t n = sizeof(k_language_keywords) / sizeof(k_language_keywords[0]);
        for (size_t i = 0; i < n; i++) {
            consider_candidate(input, k_language_keywords[i], &best, &best_dist);
        }
    }

    if (include_types) {
        size_t n = sizeof(k_language_types) / sizeof(k_language_types[0]);
        for (size_t i = 0; i < n; i++) {
            consider_candidate(input, k_language_types[i], &best, &best_dist);
        }
    }

    if (include_functions) {
        size_t n = sizeof(k_builtin_functions) / sizeof(k_builtin_functions[0]);
        for (size_t i = 0; i < n; i++) {
            consider_candidate(input, k_builtin_functions[i], &best, &best_dist);
        }
        for (Function *fn = g_functions; fn; fn = fn->next) {
            consider_candidate(input, fn->name, &best, &best_dist);
        }
        if (g_main_fn) {
            consider_candidate(input, g_main_fn->name, &best, &best_dist);
        }
    }

    if (include_symbols) {
        for (Scope *scope = scope_stack; scope; scope = scope->parent) {
            for (Symbol *sym = scope->symbols; sym; sym = sym->next) {
                consider_candidate(input, sym->name, &best, &best_dist);
            }
        }
    }

    if (best) {
        fprintf(stderr, "  hint: did you mean '%s'?\n", best);
    }
}

static void load_source_lines(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return;

    char buf[4096];
    while (fgets(buf, sizeof(buf), f)) {
        size_t len = strlen(buf);
        while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
            buf[--len] = '\0';
        }
        char **next = realloc(g_source_lines, (g_source_line_count + 1) * sizeof(*g_source_lines));
        if (!next) {
            fclose(f);
            return;
        }
        g_source_lines = next;
        g_source_lines[g_source_line_count] = strdup(buf);
        if (!g_source_lines[g_source_line_count]) {
            fclose(f);
            return;
        }
        g_source_line_count++;
    }

    fclose(f);
}

static void free_source_lines(void) {
    if (!g_source_lines) return;
    for (int i = 0; i < g_source_line_count; i++) {
        free(g_source_lines[i]);
    }
    free(g_source_lines);
    g_source_lines = NULL;
    g_source_line_count = 0;
}

static void syntax_error(int line, const char *fmt, ...) {
    va_list ap;
    syntax_error_count++;
    fprintf(stderr, "Syntax error on line %d: ", line);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    print_error_context(line, (line == last_token_line) ? last_token_text : NULL);
}

static void semantic_error(int line, const char *fmt, ...) {
    va_list ap;
    fprintf(stderr, "Semantic error on line %d: ", line);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    print_error_context(line, (line == last_token_line) ? last_token_text : NULL);
    semantic_error_count++;
}

static void semantic_error_at(int line, const char *focus_token, const char *fmt, ...) {
    va_list ap;
    fprintf(stderr, "Semantic error on line %d: ", line);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    print_error_context(line, focus_token);
    semantic_error_count++;
}

static void yyerror(const char *s) {
    syntax_error_count++;
    if (last_token_text[0] != '\0') {
        fprintf(stderr, "Syntax error on line %d near '%s': %s\n", last_token_line, last_token_text, s);
    } else {
        fprintf(stderr, "Syntax error on line %d: %s\n", line_no, s);
    }
    print_error_context(last_token_line > 0 ? last_token_line : line_no, last_token_text);
    if (isalpha((unsigned char)last_token_text[0]) || last_token_text[0] == '_') {
        print_did_you_mean(last_token_text, 1, 1, 1, 1);
    }
}

static const char *type_name(TypeKind type) {
    switch (type) {
        case T_INT: return "int";
        case T_FLOAT: return "float";
        case T_DOUBLE: return "double";
        case T_LONG: return "long int";
        case T_CHAR: return "char";
        case T_BOOL: return "bool";
        case T_VOID: return "void";
        case T_STRING: return "string";
        case T_UNKNOWN: return "unknown";
        case T_ERROR: return "error";
    }
    return "unknown";
}

static int is_numeric(TypeKind type) {
    return type == T_INT || type == T_FLOAT || type == T_DOUBLE || type == T_LONG || type == T_CHAR;
}

static int is_integral(TypeKind type) {
    return type == T_INT || type == T_LONG || type == T_CHAR;
}

static int is_bool_like(TypeKind type) {
    return type == T_BOOL || is_numeric(type);
}

static int type_compatible(TypeKind expected, TypeKind actual) {
    if (expected == T_ERROR || actual == T_ERROR) return 1;
    if (expected == actual) return 1;
    if (expected == T_UNKNOWN || actual == T_UNKNOWN) return 1;
    return 0;
}

static TypeKind numeric_promote(TypeKind left, TypeKind right) {
    if (left == T_ERROR || right == T_ERROR) return T_ERROR;
    if (left == T_DOUBLE || right == T_DOUBLE) return T_DOUBLE;
    if (left == T_FLOAT || right == T_FLOAT) return T_FLOAT;
    if (left == T_LONG || right == T_LONG) return T_LONG;
    return T_INT;
}

static Expr *alloc_expr(ExprKind kind, int line) {
    Expr *expr = calloc(1, sizeof(*expr));
    if (!expr) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    expr->kind = kind;
    expr->line = line;
    expr->inferred = T_UNKNOWN;
    expr->is_array = 0;
    expr->array_size = 0;
    expr->index = NULL;
    return expr;
}

static Expr *make_expr_ident(char *name, int line) {
    Expr *expr = alloc_expr(EXPR_IDENT, line);
    expr->text = name;
    return expr;
}

static Expr *make_expr_number(char *text, int line) {
    Expr *expr = alloc_expr(EXPR_NUMBER, line);
    expr->text = text;
    return expr;
}

static Expr *make_expr_string(char *text, int line) {
    Expr *expr = alloc_expr(EXPR_STRING, line);
    expr->text = text;
    return expr;
}

static Expr *make_expr_call(char *name, ExprList *args, int line) {
    Expr *expr = alloc_expr(EXPR_CALL, line);
    expr->text = name;
    expr->args = args;
    return expr;
}

static Expr *make_expr_index(char *name, Expr *index, int line) {
    Expr *expr = alloc_expr(EXPR_INDEX, line);
    expr->text = name;
    expr->index = index;
    return expr;
}

static Expr *make_expr_binary(char *op, Expr *left, Expr *right, int line) {
    Expr *expr = alloc_expr(EXPR_BINARY, line);
    expr->op = op;
    expr->left = left;
    expr->right = right;
    return expr;
}

static Expr *make_expr_unary(char *op, Expr *expr_node, int line) {
    Expr *expr = alloc_expr(EXPR_UNARY, line);
    expr->op = op;
    expr->left = expr_node;
    return expr;
}

static ExprList *expr_list_single(Expr *expr) {
    ExprList *list = calloc(1, sizeof(*list));
    if (!list) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    list->expr = expr;
    return list;
}

static ExprList *expr_list_append(ExprList *list, Expr *expr) {
    if (!list) return expr_list_single(expr);
    ExprList *tail = list;
    while (tail->next) tail = tail->next;
    tail->next = expr_list_single(expr);
    return list;
}

static TypeKind type_from_string(const char *name) {
    if (!name) return T_UNKNOWN;
    if (strcmp(name, "int") == 0) return T_INT;
    if (strcmp(name, "float") == 0) return T_FLOAT;
    if (strcmp(name, "double") == 0) return T_DOUBLE;
    if (strcmp(name, "long int") == 0) return T_LONG;
    if (strcmp(name, "char") == 0) return T_CHAR;
    if (strcmp(name, "bool") == 0) return T_BOOL;
    if (strcmp(name, "void") == 0) return T_VOID;
    return T_UNKNOWN;
}

static Param *param_new(const char *type_name, char *name, int line) {
    Param *param = calloc(1, sizeof(*param));
    if (!param) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    param->type = type_from_string(type_name);
    param->name = name;
    param->line = line;
    return param;
}

static Param *param_append(Param *list, Param *node) {
    if (!list) return node;
    Param *tail = list;
    while (tail->next) tail = tail->next;
    tail->next = node;
    return list;
}

static Branch *branch_new(Expr *cond, Stmt *body, int line) {
    Branch *branch = calloc(1, sizeof(*branch));
    if (!branch) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    branch->cond = cond;
    branch->body = body;
    branch->line = line;
    return branch;
}

static Stmt *stmt_new(StmtKind kind, int line) {
    Stmt *stmt = calloc(1, sizeof(*stmt));
    if (!stmt) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    stmt->kind = kind;
    stmt->line = line;
    return stmt;
}

static Stmt *stmt_append(Stmt *list, Stmt *node) {
    if (!list) return node;
    Stmt *tail = list;
    while (tail->next) tail = tail->next;
    tail->next = node;
    return list;
}

static Stmt *make_decl_stmt(const char *type_name, char *name, Expr *init, ExprList *array_init, int line) {
    Stmt *stmt = stmt_new(STMT_DECL, line);
    stmt->u.decl.type = type_from_string(type_name);
    stmt->u.decl.name = name;
    stmt->u.decl.init = init;
    stmt->u.decl.is_array = 0;
    stmt->u.decl.array_size = 0;
    stmt->u.decl.array_init = array_init;
    return stmt;
}

static Stmt *make_assign_stmt(char *name, Expr *value, int line) {
    Stmt *stmt = stmt_new(STMT_ASSIGN, line);
    stmt->u.assign.name = name;
    stmt->u.assign.value = value;
    return stmt;
}

static Stmt *make_index_assign_stmt(char *name, Expr *index, Expr *value, int line) {
    Stmt *stmt = stmt_new(STMT_INDEX_ASSIGN, line);
    stmt->u.index_assign.name = name;
    stmt->u.index_assign.index = index;
    stmt->u.index_assign.value = value;
    return stmt;
}

static Stmt *make_return_stmt(Expr *expr, int line) {
    Stmt *stmt = stmt_new(STMT_RETURN, line);
    stmt->u.ret.expr = expr;
    return stmt;
}

static Stmt *make_print_stmt(ExprList *args, int line) {
    Stmt *stmt = stmt_new(STMT_PRINT, line);
    stmt->u.print.args = args;
    return stmt;
}

static Stmt *make_expr_stmt(Expr *expr, int line) {
    Stmt *stmt = stmt_new(STMT_EXPR, line);
    stmt->u.expr_stmt.expr = expr;
    return stmt;
}

static Stmt *make_block_stmt(Stmt *stmts, int line) {
    Stmt *stmt = stmt_new(STMT_BLOCK, line);
    stmt->u.block.stmts = stmts;
    return stmt;
}

static Stmt *make_if_stmt(Expr *cond, Stmt *then_branch, Branch *elifs, Stmt *else_branch, int line) {
    Stmt *stmt = stmt_new(STMT_IF, line);
    stmt->u.if_stmt.cond = cond;
    stmt->u.if_stmt.then_branch = then_branch;
    stmt->u.if_stmt.elifs = elifs;
    stmt->u.if_stmt.else_branch = else_branch;
    return stmt;
}

static Stmt *make_while_stmt(Expr *cond, Stmt *body, int line) {
    Stmt *stmt = stmt_new(STMT_WHILE, line);
    stmt->u.while_stmt.cond = cond;
    stmt->u.while_stmt.body = body;
    return stmt;
}

static Stmt *make_for_stmt(Expr *init, Expr *cond, Expr *post, Stmt *body, int line) {
    Stmt *stmt = stmt_new(STMT_FOR, line);
    stmt->u.for_stmt.init = init;
    stmt->u.for_stmt.cond = cond;
    stmt->u.for_stmt.post = post;
    stmt->u.for_stmt.body = body;
    stmt->u.for_stmt.has_init_decl = 0;
    stmt->u.for_stmt.init_decl_type = T_UNKNOWN;
    stmt->u.for_stmt.init_decl_name = NULL;
    stmt->u.for_stmt.init_decl_value = NULL;
    return stmt;
}

static Stmt *make_switch_stmt(Expr *expr, Branch *cases, Stmt *default_branch, int line) {
    Stmt *stmt = stmt_new(STMT_SWITCH, line);
    stmt->u.switch_stmt.expr = expr;
    stmt->u.switch_stmt.cases = cases;
    stmt->u.switch_stmt.default_branch = default_branch;
    return stmt;
}

static Stmt *make_break_stmt(int line) {
    return stmt_new(STMT_BREAK, line);
}

static Stmt *make_continue_stmt(int line) {
    return stmt_new(STMT_CONTINUE, line);
}

static Function *function_new(char *name, const char *return_type_name, Param *params, Stmt *body, int line, int is_main) {
    Function *fn = calloc(1, sizeof(*fn));
    if (!fn) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    fn->name = name;
    fn->return_type = type_from_string(return_type_name);
    fn->params = params;
    fn->body = body;
    fn->line = line;
    fn->is_main = is_main;
    return fn;
}

static int includes_contains(const char *header) {
    for (Include *it = g_includes; it; it = it->next) {
        if (strcmp(it->header, header) == 0) {
            return 1;
        }
    }
    return 0;
}

static void add_include(char *header, int line) {
    (void)line;
    if (includes_contains(header)) {
        free(header);
        return;
    }
    Include *node = calloc(1, sizeof(*node));
    if (!node) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    node->header = header;
    node->line = line;
    if (!g_includes) {
        g_includes = g_includes_tail = node;
    } else {
        g_includes_tail->next = node;
        g_includes_tail = node;
    }
}

static void add_define(char *name, Expr *value, int line) {
    Define *node = calloc(1, sizeof(*node));
    if (!node) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    node->name = name;
    node->value = value;
    node->line = line;
    if (!g_defines) {
        g_defines = g_defines_tail = node;
    } else {
        g_defines_tail->next = node;
        g_defines_tail = node;
    }
}

static void add_function(Function *fn) {
    if (!g_functions) {
        g_functions = g_functions_tail = fn;
    } else {
        g_functions_tail->next = fn;
        g_functions_tail = fn;
    }
}

static void set_main(Function *fn) {
    g_main_fn = fn;
}

static Scope *push_scope(void) {
    Scope *scope = calloc(1, sizeof(*scope));
    if (!scope) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    scope->parent = scope_stack;
    scope_stack = scope;
    return scope;
}

static void pop_scope(void) {
    if (!scope_stack) return;
    Scope *parent = scope_stack->parent;
    Symbol *sym = scope_stack->symbols;
    while (sym) {
        Symbol *next = sym->next;
        free(sym);
        sym = next;
    }
    free(scope_stack);
    scope_stack = parent;
}

static Symbol *scope_lookup(Scope *scope, const char *name) {
    for (Symbol *sym = scope ? scope->symbols : NULL; sym; sym = sym->next) {
        if (strcmp(sym->name, name) == 0) {
            return sym;
        }
    }
    return NULL;
}

static Symbol *lookup_symbol(const char *name) {
    for (Scope *scope = scope_stack; scope; scope = scope->parent) {
        Symbol *sym = scope_lookup(scope, name);
        if (sym) return sym;
    }
    return NULL;
}

static Symbol *scope_add_symbol(const char *name, TypeKind type, int line) {
    if (!scope_stack) {
        push_scope();
    }
    if (scope_lookup(scope_stack, name)) {
        semantic_error(line, "duplicate symbol '%s'", name);
        return NULL;
    }
    Symbol *sym = calloc(1, sizeof(*sym));
    if (!sym) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    sym->name = strdup(name);
    sym->type = type;
    sym->is_array = 0;
    sym->array_size = 0;
    sym->next = scope_stack->symbols;
    scope_stack->symbols = sym;
    return sym;
}

static Function *find_function(const char *name) {
    if (g_main_fn && strcmp(g_main_fn->name, name) == 0) {
        return g_main_fn;
    }
    for (Function *fn = g_functions; fn; fn = fn->next) {
        if (strcmp(fn->name, name) == 0) {
            return fn;
        }
    }
    return NULL;
}

static void add_function_symbol(const Function *fn) {
    if (!scope_stack) {
        push_scope();
    }
    if (scope_lookup(scope_stack, fn->name)) {
        semantic_error(fn->line, "duplicate function '%s'", fn->name);
        return;
    }
    Symbol *sym = calloc(1, sizeof(*sym));
    if (!sym) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    sym->name = strdup(fn->name);
    sym->is_function = 1;
    sym->return_type = fn->return_type;
    sym->params = fn->params;
    sym->is_array = 0;
    sym->array_size = 0;
    sym->next = scope_stack->symbols;
    scope_stack->symbols = sym;
}

static int count_params(Param *params) {
    int count = 0;
    for (Param *p = params; p; p = p->next) count++;
    return count;
}

static int count_args(ExprList *args) {
    int count = 0;
    for (ExprList *e = args; e; e = e->next) count++;
    return count;
}

static TypeKind infer_expr(Expr *expr) {
    if (!expr) return T_UNKNOWN;
    if (expr->inferred != T_UNKNOWN) return expr->inferred;

    switch (expr->kind) {
        case EXPR_IDENT: {
            Symbol *sym = lookup_symbol(expr->text);
            if (!sym) {
                semantic_error_at(expr->line, expr->text, "undeclared identifier '%s'", expr->text);
                print_did_you_mean(expr->text, 1, 1, 1, 0);
                expr->inferred = T_ERROR;
            } else {
                expr->is_array = sym->is_array;
                expr->array_size = sym->array_size;
                if (sym->is_array) {
                    semantic_error(expr->line, "array '%s' must be indexed before use", expr->text);
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = sym->type;
                }
            }
            break;
        }
        case EXPR_INDEX: {
            Symbol *sym = lookup_symbol(expr->text);
            if (!sym) {
                semantic_error_at(expr->line, expr->text, "undeclared array '%s'", expr->text);
                print_did_you_mean(expr->text, 1, 0, 0, 0);
                expr->inferred = T_ERROR;
                break;
            }
            if (!sym->is_array) {
                semantic_error(expr->line, "'%s' is not an array", expr->text);
                expr->inferred = T_ERROR;
                break;
            }
            TypeKind idx_type = infer_expr(expr->index);
            if (!is_integral(idx_type)) {
                semantic_error(expr->line, "array index for '%s' must be an integer", expr->text);
            }
            expr->inferred = sym->type;
            break;
        }
        case EXPR_NUMBER:
            expr->inferred = strchr(expr->text, '.') ? T_DOUBLE : T_INT;
            break;
        case EXPR_STRING:
            expr->inferred = T_STRING;
            break;
        case EXPR_CALL: {
            if (strcmp(expr->text, "binary_search") == 0) {
                int argc = count_args(expr->args);
                if (argc != 2) {
                    semantic_error(expr->line, "binary_search expects 2 arguments: array and target value");
                    expr->inferred = T_ERROR;
                    break;
                }
                ExprList *first = expr->args;
                ExprList *second = first ? first->next : NULL;
                if (!first || !second) {
                    expr->inferred = T_ERROR;
                    break;
                }
                Expr *array_expr = first->expr;
                Expr *target_expr = second->expr;
                if (!array_expr || array_expr->kind != EXPR_IDENT) {
                    semantic_error(expr->line, "binary_search first argument must be an array name");
                    expr->inferred = T_ERROR;
                    break;
                }
                Symbol *arr_sym = lookup_symbol(array_expr->text);
                if (!arr_sym) {
                    semantic_error_at(expr->line, array_expr->text, "undeclared array '%s'", array_expr->text);
                    print_did_you_mean(array_expr->text, 1, 0, 0, 0);
                    expr->inferred = T_ERROR;
                    break;
                }
                if (!arr_sym->is_array) {
                    semantic_error(expr->line, "binary_search expects an array as first argument, got '%s'", array_expr->text);
                    expr->inferred = T_ERROR;
                    break;
                }
                expr->array_size = arr_sym->array_size;
                if (arr_sym->type != T_INT) {
                    semantic_error(expr->line, "binary_search currently supports only int arrays");
                }
                TypeKind target_type = infer_expr(target_expr);
                if (!is_numeric(target_type)) {
                    semantic_error(expr->line, "binary_search target must be numeric");
                }
                expr->inferred = T_INT;
                break;
            }
            if (strcmp(expr->text, "sort") == 0 ||
                strcmp(expr->text, "find") == 0 ||
                strcmp(expr->text, "map") == 0 ||
                strcmp(expr->text, "filter") == 0 ||
                strcmp(expr->text, "reduce") == 0) {
                int argc = count_args(expr->args);
                ExprList *first = expr->args;
                Expr *array_expr = first ? first->expr : NULL;

                if (!array_expr || array_expr->kind != EXPR_IDENT) {
                    semantic_error(expr->line, "%s first argument must be an array name", expr->text);
                    expr->inferred = T_ERROR;
                    break;
                }

                Symbol *arr_sym = lookup_symbol(array_expr->text);
                if (!arr_sym) {
                    semantic_error_at(expr->line, array_expr->text, "undeclared array '%s'", array_expr->text);
                    print_did_you_mean(array_expr->text, 1, 0, 0, 0);
                    expr->inferred = T_ERROR;
                    break;
                }
                if (!arr_sym->is_array) {
                    semantic_error(expr->line, "%s expects an array as first argument, got '%s'", expr->text, array_expr->text);
                    expr->inferred = T_ERROR;
                    break;
                }
                if (arr_sym->type != T_INT) {
                    semantic_error(expr->line, "%s currently supports only int arrays", expr->text);
                }

                expr->array_size = arr_sym->array_size;

                if (strcmp(expr->text, "sort") == 0) {
                    if (argc != 1) {
                        semantic_error(expr->line, "sort expects 1 argument: array");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    expr->inferred = T_VOID;
                    break;
                }

                if (strcmp(expr->text, "find") == 0) {
                    if (argc != 2) {
                        semantic_error(expr->line, "find expects 2 arguments: array and target value");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    ExprList *second = first->next;
                    TypeKind target_type = infer_expr(second ? second->expr : NULL);
                    if (!is_numeric(target_type)) {
                        semantic_error(expr->line, "find target must be numeric");
                    }
                    expr->inferred = T_INT;
                    break;
                }

                if (strcmp(expr->text, "map") == 0) {
                    if (argc != 2) {
                        semantic_error(expr->line, "map expects 2 arguments: array and unary function");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    ExprList *second = first->next;
                    Expr *fn_expr = second ? second->expr : NULL;
                    if (!fn_expr || fn_expr->kind != EXPR_IDENT) {
                        semantic_error(expr->line, "map second argument must be a function name");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    Function *fn = find_function(fn_expr->text);
                    if (!fn) {
                        semantic_error_at(expr->line, fn_expr->text, "call to undefined function '%s'", fn_expr->text);
                        print_did_you_mean(fn_expr->text, 0, 1, 0, 0);
                        expr->inferred = T_ERROR;
                        break;
                    }
                    if (count_params(fn->params) != 1) {
                        semantic_error(expr->line, "map callback '%s' must accept exactly 1 parameter", fn->name);
                    } else {
                        Param *p = fn->params;
                        if (!is_numeric(p->type) || !is_numeric(fn->return_type)) {
                            semantic_error(expr->line, "map callback '%s' must be numeric -> numeric", fn->name);
                        }
                    }
                    expr->inferred = T_VOID;
                    break;
                }

                if (strcmp(expr->text, "filter") == 0) {
                    if (argc != 2) {
                        semantic_error(expr->line, "filter expects 2 arguments: array and predicate function");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    ExprList *second = first->next;
                    Expr *fn_expr = second ? second->expr : NULL;
                    if (!fn_expr || fn_expr->kind != EXPR_IDENT) {
                        semantic_error(expr->line, "filter second argument must be a function name");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    Function *fn = find_function(fn_expr->text);
                    if (!fn) {
                        semantic_error_at(expr->line, fn_expr->text, "call to undefined function '%s'", fn_expr->text);
                        print_did_you_mean(fn_expr->text, 0, 1, 0, 0);
                        expr->inferred = T_ERROR;
                        break;
                    }
                    if (count_params(fn->params) != 1) {
                        semantic_error(expr->line, "filter callback '%s' must accept exactly 1 parameter", fn->name);
                    } else {
                        Param *p = fn->params;
                        if (!is_numeric(p->type) || !is_bool_like(fn->return_type)) {
                            semantic_error(expr->line, "filter callback '%s' must be numeric -> bool-like", fn->name);
                        }
                    }
                    expr->inferred = T_INT;
                    break;
                }

                if (strcmp(expr->text, "reduce") == 0) {
                    if (argc != 3) {
                        semantic_error(expr->line, "reduce expects 3 arguments: array, binary function, initial value");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    ExprList *second = first->next;
                    ExprList *third = second ? second->next : NULL;
                    Expr *fn_expr = second ? second->expr : NULL;
                    Expr *init_expr = third ? third->expr : NULL;
                    if (!fn_expr || fn_expr->kind != EXPR_IDENT) {
                        semantic_error(expr->line, "reduce second argument must be a function name");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    Function *fn = find_function(fn_expr->text);
                    if (!fn) {
                        semantic_error_at(expr->line, fn_expr->text, "call to undefined function '%s'", fn_expr->text);
                        print_did_you_mean(fn_expr->text, 0, 1, 0, 0);
                        expr->inferred = T_ERROR;
                        break;
                    }
                    if (count_params(fn->params) != 2) {
                        semantic_error(expr->line, "reduce callback '%s' must accept exactly 2 parameters", fn->name);
                    } else {
                        Param *p1 = fn->params;
                        Param *p2 = p1 ? p1->next : NULL;
                        if (!is_numeric(p1->type) || !is_numeric(p2 ? p2->type : T_ERROR) || !is_numeric(fn->return_type)) {
                            semantic_error(expr->line, "reduce callback '%s' must be (numeric, numeric) -> numeric", fn->name);
                        }
                    }
                    TypeKind init_type = infer_expr(init_expr);
                    if (!is_numeric(init_type)) {
                        semantic_error(expr->line, "reduce initial value must be numeric");
                    }
                    expr->inferred = T_INT;
                    break;
                }
            }
            /* Built-in math-like helpers from the custom language */
            if (strcmp(expr->text, "raise_to") == 0 ||
                strcmp(expr->text, "square_root") == 0 ||
                strcmp(expr->text, "magnitude") == 0 ||
                strcmp(expr->text, "round_down") == 0 ||
                strcmp(expr->text, "round_up") == 0 ||
                strcmp(expr->text, "ln") == 0 ||
                strcmp(expr->text, "SIN") == 0 ||
                strcmp(expr->text, "COS") == 0 ||
                strcmp(expr->text, "TAN") == 0) {
                /* Treat these as int-returning numeric helpers to match 'num' variables. */
                ExprList *arg = expr->args;
                while (arg) {
                    infer_expr(arg->expr);
                    arg = arg->next;
                }
                expr->inferred = T_INT;
                break;
            }
            Function *fn = find_function(expr->text);
            if (!fn) {
                semantic_error_at(expr->line, expr->text, "call to undefined function '%s'", expr->text);
                print_did_you_mean(expr->text, 0, 1, 0, 0);
                expr->inferred = T_ERROR;
                break;
            }
            int expected = count_params(fn->params);
            int actual = count_args(expr->args);
            if (expected != actual) {
                semantic_error(expr->line, "function '%s' expects %d arguments, got %d", expr->text, expected, actual);
            }
            Param *param = fn->params;
            ExprList *arg = expr->args;
            while (param && arg) {
                TypeKind arg_type = infer_expr(arg->expr);
                if (!type_compatible(param->type, arg_type)) {
                    semantic_error(arg->expr ? arg->expr->line : expr->line,
                                   "argument type mismatch for '%s': expected %s, got %s",
                                   param->name,
                                   type_name(param->type),
                                   type_name(arg_type));
                }
                param = param->next;
                arg = arg->next;
            }
            expr->inferred = fn->return_type;
            break;
        }
        case EXPR_BINARY: {
            TypeKind left = infer_expr(expr->left);
            TypeKind right = infer_expr(expr->right);
            if (!strcmp(expr->op, "+") || !strcmp(expr->op, "-") || !strcmp(expr->op, "*") || !strcmp(expr->op, "/")) {
                if (!is_numeric(left) || !is_numeric(right)) {
                    semantic_error(expr->line, "arithmetic operator '%s' requires numeric operands", expr->op);
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = numeric_promote(left, right);
                }
            } else if (!strcmp(expr->op, "%")) {
                if (!is_integral(left) || !is_integral(right)) {
                    semantic_error(expr->line, "operator '%%' requires integral operands");
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = T_INT;
                }
            } else if (!strcmp(expr->op, "<") || !strcmp(expr->op, ">") || !strcmp(expr->op, "<=") || !strcmp(expr->op, ">=") || !strcmp(expr->op, "==") || !strcmp(expr->op, "!=")) {
                if (!type_compatible(left, right) || !type_compatible(right, left)) {
                    semantic_error(expr->line, "comparison operator '%s' requires compatible operands", expr->op);
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = T_BOOL;
                }
            } else if (!strcmp(expr->op, "&&") || !strcmp(expr->op, "||")) {
                if (!is_bool_like(left) || !is_bool_like(right)) {
                    semantic_error(expr->line, "logical operator '%s' requires boolean-like operands", expr->op);
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = T_BOOL;
                }
            } else if (!strcmp(expr->op, "=")) {
                if (!type_compatible(left, right)) {
                    semantic_error(expr->line, "assignment requires compatible types");
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = left;
                }
            } else {
                expr->inferred = T_ERROR;
            }
            break;
        }
        case EXPR_UNARY: {
            TypeKind inner = infer_expr(expr->left);
            if (!strcmp(expr->op, "!")) {
                if (!is_bool_like(inner)) {
                    semantic_error(expr->line, "operator '!' requires a boolean-like operand");
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = T_BOOL;
                }
            } else if (!strcmp(expr->op, "-")) {
                if (!is_numeric(inner)) {
                    semantic_error(expr->line, "unary '-' requires a numeric operand");
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = inner;
                }
            } else {
                expr->inferred = T_ERROR;
            }
            break;
        }
    }

    return expr->inferred;
}

static void analyze_stmt_list(Stmt *stmt) {
    for (Stmt *it = stmt; it; it = it->next) {
        analyze_stmt(it);
    }
}

static void analyze_stmt(Stmt *stmt) {
    if (!stmt) return;

    switch (stmt->kind) {
        case STMT_DECL: {
            if (stmt->u.decl.type == T_VOID) {
                semantic_error(stmt->line, "variable '%s' cannot have type void", stmt->u.decl.name);
            }
            if (stmt->u.decl.is_array) {
                if (stmt->u.decl.array_size <= 0) {
                    semantic_error(stmt->line, "array '%s' must have a positive size", stmt->u.decl.name);
                }
                if (stmt->u.decl.array_init) {
                    int count = 0;
                    for (ExprList *it = stmt->u.decl.array_init; it; it = it->next) {
                        count++;
                        TypeKind elem_type = infer_expr(it->expr);
                        if (!type_compatible(stmt->u.decl.type, elem_type)) {
                            semantic_error(stmt->line,
                                           "array '%s' element type %s does not match %s",
                                           stmt->u.decl.name,
                                           type_name(elem_type),
                                           type_name(stmt->u.decl.type));
                        }
                    }
                    if (stmt->u.decl.array_size > 0 && count != stmt->u.decl.array_size) {
                        semantic_error(stmt->line,
                                       "array '%s' size is %d but initializer has %d elements",
                                       stmt->u.decl.name,
                                       stmt->u.decl.array_size,
                                       count);
                    }
                }
            }
            if (stmt->u.decl.init) {
                TypeKind init_type = infer_expr(stmt->u.decl.init);
                if (!type_compatible(stmt->u.decl.type, init_type)) {
                    semantic_error(stmt->line,
                                   "cannot initialize '%s' of type %s with %s",
                                   stmt->u.decl.name,
                                   type_name(stmt->u.decl.type),
                                   type_name(init_type));
                }
            }
            Symbol *sym = scope_add_symbol(stmt->u.decl.name, stmt->u.decl.type, stmt->line);
            if (sym) {
                sym->is_array = stmt->u.decl.is_array;
                sym->array_size = stmt->u.decl.array_size;
            }
            break;
        }
        case STMT_ASSIGN: {
            Symbol *sym = lookup_symbol(stmt->u.assign.name);
            if (!sym) {
                semantic_error_at(stmt->line, stmt->u.assign.name, "assignment to undeclared variable '%s'", stmt->u.assign.name);
                print_did_you_mean(stmt->u.assign.name, 1, 0, 0, 0);
                break;
            }
            TypeKind value_type = infer_expr(stmt->u.assign.value);
            if (!type_compatible(sym->type, value_type)) {
                semantic_error(stmt->line,
                               "cannot assign %s to variable '%s' of type %s",
                               type_name(value_type),
                               stmt->u.assign.name,
                               type_name(sym->type));
            }
            break;
        }
        case STMT_INDEX_ASSIGN: {
            Symbol *sym = lookup_symbol(stmt->u.index_assign.name);
            if (!sym) {
                semantic_error_at(stmt->line, stmt->u.index_assign.name, "assignment to undeclared array '%s'", stmt->u.index_assign.name);
                print_did_you_mean(stmt->u.index_assign.name, 1, 0, 0, 0);
                break;
            }
            if (!sym->is_array) {
                semantic_error(stmt->line, "'%s' is not an array", stmt->u.index_assign.name);
                break;
            }
            TypeKind idx_type = infer_expr(stmt->u.index_assign.index);
            if (!is_integral(idx_type)) {
                semantic_error(stmt->line, "array index for '%s' must be an integer", stmt->u.index_assign.name);
            }
            TypeKind value_type = infer_expr(stmt->u.index_assign.value);
            if (!type_compatible(sym->type, value_type)) {
                semantic_error(stmt->line,
                               "cannot assign %s to element of '%s' of type %s",
                               type_name(value_type),
                               stmt->u.index_assign.name,
                               type_name(sym->type));
            }
            break;
        }
        case STMT_RETURN: {
            if (!current_function) {
                semantic_error(stmt->line, "return statement outside of function");
                break;
            }
            TypeKind value_type = infer_expr(stmt->u.ret.expr);
            if (!type_compatible(current_function->return_type, value_type)) {
                semantic_error(stmt->line,
                               "return type mismatch in '%s': expected %s, got %s",
                               current_function->name,
                               type_name(current_function->return_type),
                               type_name(value_type));
            }
            break;
        }
        case STMT_PRINT: {
            for (ExprList *arg = stmt->u.print.args; arg; arg = arg->next) {
                infer_expr(arg->expr);
            }
            break;
        }
        case STMT_EXPR: {
            infer_expr(stmt->u.expr_stmt.expr);
            break;
        }
        case STMT_BLOCK: {
            push_scope();
            analyze_stmt_list(stmt->u.block.stmts);
            pop_scope();
            break;
        }
        case STMT_IF: {
            TypeKind cond_type = infer_expr(stmt->u.if_stmt.cond);
            if (!is_bool_like(cond_type)) {
                semantic_error(stmt->line, "if condition must be boolean-like");
            }
            push_scope();
            analyze_stmt_list(stmt->u.if_stmt.then_branch);
            pop_scope();
            for (Branch *br = stmt->u.if_stmt.elifs; br; br = br->next) {
                TypeKind branch_cond = infer_expr(br->cond);
                if (!is_bool_like(branch_cond)) {
                    semantic_error(br->line, "elif condition must be boolean-like");
                }
                push_scope();
                analyze_stmt_list(br->body);
                pop_scope();
            }
            if (stmt->u.if_stmt.else_branch) {
                push_scope();
                analyze_stmt_list(stmt->u.if_stmt.else_branch);
                pop_scope();
            }
            break;
        }
        case STMT_WHILE: {
            TypeKind cond_type = infer_expr(stmt->u.while_stmt.cond);
            if (!is_bool_like(cond_type)) {
                semantic_error(stmt->line, "while condition must be boolean-like");
            }
            push_scope();
            analyze_stmt_list(stmt->u.while_stmt.body);
            pop_scope();
            break;
        }
        case STMT_FOR: {
            push_scope();
            if (stmt->u.for_stmt.has_init_decl) {
                if (stmt->u.for_stmt.init_decl_type == T_VOID) {
                    semantic_error(stmt->line, "variable '%s' cannot have type void", stmt->u.for_stmt.init_decl_name);
                }
                if (stmt->u.for_stmt.init_decl_value) {
                    TypeKind init_type = infer_expr(stmt->u.for_stmt.init_decl_value);
                    if (!type_compatible(stmt->u.for_stmt.init_decl_type, init_type)) {
                        semantic_error(stmt->line,
                                       "cannot initialize '%s' of type %s with %s",
                                       stmt->u.for_stmt.init_decl_name,
                                       type_name(stmt->u.for_stmt.init_decl_type),
                                       type_name(init_type));
                    }
                }
                scope_add_symbol(stmt->u.for_stmt.init_decl_name, stmt->u.for_stmt.init_decl_type, stmt->line);
            } else if (stmt->u.for_stmt.init) {
                infer_expr(stmt->u.for_stmt.init);
            }
            if (stmt->u.for_stmt.cond) {
                TypeKind cond_type = infer_expr(stmt->u.for_stmt.cond);
                if (!is_bool_like(cond_type)) {
                    semantic_error(stmt->line, "for condition must be boolean-like");
                }
            }
            if (stmt->u.for_stmt.post) infer_expr(stmt->u.for_stmt.post);
            analyze_stmt_list(stmt->u.for_stmt.body);
            pop_scope();
            break;
        }
        case STMT_SWITCH: {
            TypeKind cond_type = infer_expr(stmt->u.switch_stmt.expr);
            if (!is_integral(cond_type)) {
                semantic_error(stmt->line, "switch expression must be integral");
            }
            for (Branch *br = stmt->u.switch_stmt.cases; br; br = br->next) {
                TypeKind case_type = infer_expr(br->cond);
                if (!type_compatible(cond_type, case_type)) {
                    semantic_error(br->line, "case label type must match switch expression type");
                }
                push_scope();
                analyze_stmt_list(br->body);
                pop_scope();
            }
            if (stmt->u.switch_stmt.default_branch) {
                push_scope();
                analyze_stmt_list(stmt->u.switch_stmt.default_branch);
                pop_scope();
            }
            break;
        }
        case STMT_BREAK:
        case STMT_CONTINUE:
            break;
    }
}

static void analyze_function(Function *fn) {
    current_function = fn;
    push_scope();

    for (Param *p = fn->params; p; p = p->next) {
        if (scope_lookup(scope_stack, p->name)) {
            semantic_error(p->line, "duplicate parameter '%s' in function '%s'", p->name, fn->name);
            continue;
        }
        scope_add_symbol(p->name, p->type, p->line);
    }

    analyze_stmt_list(fn->body);
    pop_scope();
    current_function = NULL;
}

static void analyze_program(void) {
    push_scope();

    for (Function *fn = g_functions; fn; fn = fn->next) {
        add_function_symbol(fn);
    }
    if (g_main_fn) {
        add_function_symbol(g_main_fn);
    }

    if (g_main_fn && g_main_fn->return_type != T_INT) {
        semantic_error(g_main_fn->line, "main function must return int");
    }

    for (Function *fn = g_functions; fn; fn = fn->next) {
        analyze_function(fn);
    }
    if (g_main_fn) {
        analyze_function(g_main_fn);
    }

    pop_scope();
}

static void emit_indent(FILE *f) {
    for (int i = 0; i < indent_level; i++) {
        fputs("    ", f);
    }
}

static int expr_precedence(Expr *expr) {
    if (!expr) return 0;

    switch (expr->kind) {
        case EXPR_IDENT:
        case EXPR_NUMBER:
        case EXPR_STRING:
        case EXPR_CALL:
        case EXPR_INDEX:
            return 100;
        case EXPR_UNARY:
            return 90;
        case EXPR_BINARY:
            if (!strcmp(expr->op, "=")) return 10;
            if (!strcmp(expr->op, "||")) return 20;
            if (!strcmp(expr->op, "&&")) return 30;
            if (!strcmp(expr->op, "==") || !strcmp(expr->op, "!=")) return 40;
            if (!strcmp(expr->op, "<") || !strcmp(expr->op, ">") || !strcmp(expr->op, "<=") || !strcmp(expr->op, ">=")) return 50;
            if (!strcmp(expr->op, "+") || !strcmp(expr->op, "-")) return 60;
            if (!strcmp(expr->op, "*") || !strcmp(expr->op, "/") || !strcmp(expr->op, "%")) return 70;
            return 50;
    }
    return 0;
}

static void emit_expr_prec(FILE *f, Expr *expr, int parent_prec) {
    if (!expr) return;

    int prec = expr_precedence(expr);
    int need_parens = prec < parent_prec;
    if (need_parens) fputc('(', f);

    switch (expr->kind) {
        case EXPR_IDENT:
        case EXPR_NUMBER:
        case EXPR_STRING:
            fputs(expr->text, f);
            break;
        case EXPR_CALL: {
            if (strcmp(expr->text, "binary_search") == 0) {
                ExprList *first = expr->args;
                ExprList *second = first ? first->next : NULL;
                fprintf(f, "binary_search(");
                emit_expr_prec(f, first ? first->expr : NULL, 0);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d, ", expr->array_size);
                } else {
                    fputs(", 0, ", f);
                }
                emit_expr_prec(f, second ? second->expr : NULL, 0);
                fputc(')', f);
                break;
            }
            if (strcmp(expr->text, "sort") == 0) {
                ExprList *first = expr->args;
                fprintf(f, "array_sort_int(");
                emit_expr_prec(f, first ? first->expr : NULL, 0);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d", expr->array_size);
                } else {
                    fputs(", 0", f);
                }
                fputc(')', f);
                break;
            }
            if (strcmp(expr->text, "find") == 0) {
                ExprList *first = expr->args;
                ExprList *second = first ? first->next : NULL;
                fprintf(f, "array_find_int(");
                emit_expr_prec(f, first ? first->expr : NULL, 0);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d, ", expr->array_size);
                } else {
                    fputs(", 0, ", f);
                }
                emit_expr_prec(f, second ? second->expr : NULL, 0);
                fputc(')', f);
                break;
            }
            if (strcmp(expr->text, "map") == 0) {
                ExprList *first = expr->args;
                ExprList *second = first ? first->next : NULL;
                fprintf(f, "array_map_int(");
                emit_expr_prec(f, first ? first->expr : NULL, 0);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d, ", expr->array_size);
                } else {
                    fputs(", 0, ", f);
                }
                emit_expr_prec(f, second ? second->expr : NULL, 0);
                fputc(')', f);
                break;
            }
            if (strcmp(expr->text, "filter") == 0) {
                ExprList *first = expr->args;
                ExprList *second = first ? first->next : NULL;
                fprintf(f, "array_filter_int(");
                emit_expr_prec(f, first ? first->expr : NULL, 0);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d, ", expr->array_size);
                } else {
                    fputs(", 0, ", f);
                }
                emit_expr_prec(f, second ? second->expr : NULL, 0);
                fputc(')', f);
                break;
            }
            if (strcmp(expr->text, "reduce") == 0) {
                ExprList *first = expr->args;
                ExprList *second = first ? first->next : NULL;
                ExprList *third = second ? second->next : NULL;
                fprintf(f, "array_reduce_int(");
                emit_expr_prec(f, first ? first->expr : NULL, 0);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d, ", expr->array_size);
                } else {
                    fputs(", 0, ", f);
                }
                emit_expr_prec(f, second ? second->expr : NULL, 0);
                fputs(", ", f);
                emit_expr_prec(f, third ? third->expr : NULL, 0);
                fputc(')', f);
                break;
            }
            const char *fname = expr->text;
            if (strcmp(fname, "raise_to") == 0) fname = "pow";
            else if (strcmp(fname, "square_root") == 0) fname = "sqrt";
            else if (strcmp(fname, "magnitude") == 0) fname = "abs";
            else if (strcmp(fname, "round_down") == 0) fname = "floor";
            else if (strcmp(fname, "round_up") == 0) fname = "ceil";
            else if (strcmp(fname, "ln") == 0) fname = "logf";
            else if (strcmp(fname, "SIN") == 0) fname = "sinf";
            else if (strcmp(fname, "COS") == 0) fname = "cosf";
            else if (strcmp(fname, "TAN") == 0) fname = "tanf";
            fprintf(f, "%s(", fname);
            for (ExprList *arg = expr->args; arg; arg = arg->next) {
                emit_expr_prec(f, arg->expr, 0);
                if (arg->next) fputs(", ", f);
            }
            fputc(')', f);
            break;
        }
        case EXPR_INDEX:
            fprintf(f, "%s[", expr->text);
            emit_expr_prec(f, expr->index, 0);
            fputc(']', f);
            break;
        case EXPR_BINARY: {
            int child_prec = prec;
            emit_expr_prec(f, expr->left, child_prec);
            fprintf(f, " %s ", expr->op);
            emit_expr_prec(f, expr->right, child_prec);
            break;
        }
        case EXPR_UNARY:
            fprintf(f, "%s", expr->op);
            emit_expr_prec(f, expr->left, prec);
            break;
    }

    if (need_parens) fputc(')', f);
}

static void emit_expr(FILE *f, Expr *expr) {
    emit_expr_prec(f, expr, 0);
}

static void emit_stmt_list(FILE *f, Stmt *stmt) {
    for (Stmt *it = stmt; it; it = it->next) {
        emit_stmt(f, it);
    }
}

static int stmt_list_needs_switch_break(Stmt *stmt) {
    if (!stmt) return 1;
    Stmt *last = stmt;
    while (last->next) last = last->next;
    return last->kind != STMT_BREAK && last->kind != STMT_RETURN;
}

static void emit_stmt(FILE *f, Stmt *stmt) {
    if (!stmt) return;

    switch (stmt->kind) {
        case STMT_DECL:
            emit_indent(f);
            if (stmt->u.decl.is_array) {
                fprintf(f, "%s %s[%d]", type_name(stmt->u.decl.type), stmt->u.decl.name, stmt->u.decl.array_size);
                if (stmt->u.decl.array_init) {
                    fputs(" = {", f);
                    for (ExprList *it = stmt->u.decl.array_init; it; it = it->next) {
                        emit_expr(f, it->expr);
                        if (it->next) fputs(", ", f);
                    }
                    fputs("}", f);
                }
            } else {
                fprintf(f, "%s %s", type_name(stmt->u.decl.type), stmt->u.decl.name);
                if (stmt->u.decl.init) {
                    fputs(" = ", f);
                    emit_expr(f, stmt->u.decl.init);
                }
            }
            fputs(";\n", f);
            break;
        case STMT_ASSIGN:
            emit_indent(f);
            fprintf(f, "%s = ", stmt->u.assign.name);
            emit_expr(f, stmt->u.assign.value);
            fputs(";\n", f);
            break;
        case STMT_INDEX_ASSIGN:
            emit_indent(f);
            fprintf(f, "%s[", stmt->u.index_assign.name);
            emit_expr(f, stmt->u.index_assign.index);
            fputs("] = ", f);
            emit_expr(f, stmt->u.index_assign.value);
            fputs(";\n", f);
            break;
        case STMT_RETURN:
            emit_indent(f);
            fputs("return ", f);
            emit_expr(f, stmt->u.ret.expr);
            fputs(";\n", f);
            break;
        case STMT_PRINT:
            emit_indent(f);
            fputs("printf(", f);
            for (ExprList *arg = stmt->u.print.args; arg; arg = arg->next) {
                emit_expr(f, arg->expr);
                if (arg->next) fputs(", ", f);
            }
            fputs(");\n", f);
            break;
        case STMT_EXPR:
            emit_indent(f);
            emit_expr(f, stmt->u.expr_stmt.expr);
            fputs(";\n", f);
            break;
        case STMT_BLOCK:
            emit_indent(f);
            fputs("{\n", f);
            indent_level++;
            emit_stmt_list(f, stmt->u.block.stmts);
            indent_level--;
            emit_indent(f);
            fputs("}\n", f);
            break;
        case STMT_IF:
            emit_indent(f);
            fputs("if (", f);
            emit_expr(f, stmt->u.if_stmt.cond);
            fputs(") {\n", f);
            indent_level++;
            emit_stmt_list(f, stmt->u.if_stmt.then_branch);
            indent_level--;
            emit_indent(f);
            fputs("}\n", f);
            for (Branch *br = stmt->u.if_stmt.elifs; br; br = br->next) {
                emit_indent(f);
                fputs("else if (", f);
                emit_expr(f, br->cond);
                fputs(") {\n", f);
                indent_level++;
                emit_stmt_list(f, br->body);
                indent_level--;
                emit_indent(f);
                fputs("}\n", f);
            }
            if (stmt->u.if_stmt.else_branch) {
                emit_indent(f);
                fputs("else {\n", f);
                indent_level++;
                emit_stmt_list(f, stmt->u.if_stmt.else_branch);
                indent_level--;
                emit_indent(f);
                fputs("}\n", f);
            }
            break;
        case STMT_WHILE:
            emit_indent(f);
            fputs("while (", f);
            emit_expr(f, stmt->u.while_stmt.cond);
            fputs(") {\n", f);
            indent_level++;
            emit_stmt_list(f, stmt->u.while_stmt.body);
            indent_level--;
            emit_indent(f);
            fputs("}\n", f);
            break;
        case STMT_FOR:
            emit_indent(f);
            fputs("for (", f);
            if (stmt->u.for_stmt.has_init_decl) {
                fprintf(f, "%s %s", type_name(stmt->u.for_stmt.init_decl_type), stmt->u.for_stmt.init_decl_name);
                if (stmt->u.for_stmt.init_decl_value) {
                    fputs(" = ", f);
                    emit_expr(f, stmt->u.for_stmt.init_decl_value);
                }
            } else if (stmt->u.for_stmt.init) {
                emit_expr(f, stmt->u.for_stmt.init);
            }
            fputs("; ", f);
            if (stmt->u.for_stmt.cond) emit_expr(f, stmt->u.for_stmt.cond);
            fputs("; ", f);
            if (stmt->u.for_stmt.post) emit_expr(f, stmt->u.for_stmt.post);
            fputs(") {\n", f);
            indent_level++;
            emit_stmt_list(f, stmt->u.for_stmt.body);
            indent_level--;
            emit_indent(f);
            fputs("}\n", f);
            break;
        case STMT_SWITCH:
            emit_indent(f);
            fputs("switch (", f);
            emit_expr(f, stmt->u.switch_stmt.expr);
            fputs(") {\n", f);
            indent_level++;
            for (Branch *br = stmt->u.switch_stmt.cases; br; br = br->next) {
                emit_indent(f);
                fputs("case ", f);
                emit_expr(f, br->cond);
                fputs(":\n", f);
                indent_level++;
                emit_stmt_list(f, br->body);
                if (stmt_list_needs_switch_break(br->body)) {
                    emit_indent(f);
                    fputs("break;\n", f);
                }
                indent_level--;
            }
            if (stmt->u.switch_stmt.default_branch) {
                emit_indent(f);
                fputs("default:\n", f);
                indent_level++;
                emit_stmt_list(f, stmt->u.switch_stmt.default_branch);
                if (stmt_list_needs_switch_break(stmt->u.switch_stmt.default_branch)) {
                    emit_indent(f);
                    fputs("break;\n", f);
                }
                indent_level--;
            }
            indent_level--;
            emit_indent(f);
            fputs("}\n", f);
            break;
        case STMT_BREAK:
            emit_indent(f);
            fputs("break;\n", f);
            break;
        case STMT_CONTINUE:
            emit_indent(f);
            fputs("continue;\n", f);
            break;
    }
}

static void emit_params(FILE *f, Param *params) {
    for (Param *p = params; p; p = p->next) {
        fprintf(f, "%s %s", type_name(p->type), p->name);
        if (p->next) fputs(", ", f);
    }
}

static void emit_include(FILE *f, const char *header) {
    fprintf(f, "#include %s\n", header);
}

static void emit_binary_search_helper(FILE *f) {
    fputs("\nstatic int binary_search(int arr[], int n, int target) {\n", f);
    fputs("    int left = 0;\n", f);
    fputs("    int right = n - 1;\n", f);
    fputs("    while (left <= right) {\n", f);
    fputs("        int mid = left + (right - left) / 2;\n", f);
    fputs("        if (arr[mid] == target) return mid;\n", f);
    fputs("        if (arr[mid] < target) left = mid + 1;\n", f);
    fputs("        else right = mid - 1;\n", f);
    fputs("    }\n", f);
    fputs("    return -1;\n", f);
    fputs("}\n\n", f);
}

static void emit_array_helpers(FILE *f) {
    fputs("static void array_sort_int(int arr[], int n) {\n", f);
    fputs("    for (int i = 0; i < n; i++) {\n", f);
    fputs("        for (int j = 0; j + 1 < n - i; j++) {\n", f);
    fputs("            if (arr[j] > arr[j + 1]) {\n", f);
    fputs("                int t = arr[j];\n", f);
    fputs("                arr[j] = arr[j + 1];\n", f);
    fputs("                arr[j + 1] = t;\n", f);
    fputs("            }\n", f);
    fputs("        }\n", f);
    fputs("    }\n", f);
    fputs("}\n\n", f);

    fputs("static int array_find_int(int arr[], int n, int target) {\n", f);
    fputs("    for (int i = 0; i < n; i++) {\n", f);
    fputs("        if (arr[i] == target) return i;\n", f);
    fputs("    }\n", f);
    fputs("    return -1;\n", f);
    fputs("}\n\n", f);

    fputs("static void array_map_int(int arr[], int n, int (*op)(int)) {\n", f);
    fputs("    for (int i = 0; i < n; i++) {\n", f);
    fputs("        arr[i] = op(arr[i]);\n", f);
    fputs("    }\n", f);
    fputs("}\n\n", f);

    fputs("static int array_filter_int(int arr[], int n, int (*pred)(int)) {\n", f);
    fputs("    int write_idx = 0;\n", f);
    fputs("    for (int i = 0; i < n; i++) {\n", f);
    fputs("        if (pred(arr[i])) {\n", f);
    fputs("            arr[write_idx++] = arr[i];\n", f);
    fputs("        }\n", f);
    fputs("    }\n", f);
    fputs("    return write_idx;\n", f);
    fputs("}\n\n", f);

    fputs("static int array_reduce_int(int arr[], int n, int (*op)(int, int), int init) {\n", f);
    fputs("    int acc = init;\n", f);
    fputs("    for (int i = 0; i < n; i++) {\n", f);
    fputs("        acc = op(acc, arr[i]);\n", f);
    fputs("    }\n", f);
    fputs("    return acc;\n", f);
    fputs("}\n\n", f);
}

static void emit_program(const char *path) {
    outf = fopen(path, "w");
    if (!outf) {
        fprintf(stderr, "Error: cannot create %s\n", path);
        exit(1);
    }

    emit_include(outf, "<stdio.h>");
    emit_include(outf, "<math.h>");
    emit_include(outf, "<stdlib.h>");
    emit_include(outf, "<stdbool.h>");
    emit_binary_search_helper(outf);
    emit_array_helpers(outf);
    for (Include *inc = g_includes; inc; inc = inc->next) {
        if (strcmp(inc->header, "<stdio.h>") == 0 || strcmp(inc->header, "<math.h>") == 0 || strcmp(inc->header, "<stdbool.h>") == 0) {
            continue;
        }
        emit_include(outf, inc->header);
    }
    fputc('\n', outf);

    for (Define *def = g_defines; def; def = def->next) {
        fprintf(outf, "#define %s ", def->name);
        emit_expr(outf, def->value);
        fputc('\n', outf);
    }
    if (g_defines) fputc('\n', outf);

    for (Function *fn = g_functions; fn; fn = fn->next) {
        fprintf(outf, "%s %s(", type_name(fn->return_type), fn->name);
        emit_params(outf, fn->params);
        fputs(") {\n", outf);
        indent_level++;
        emit_stmt_list(outf, fn->body);
        indent_level--;
        fputs("}\n\n", outf);
    }

    if (g_main_fn) {
        fprintf(outf, "int main(");
        emit_params(outf, g_main_fn->params);
        fputs(") {\n", outf);
        indent_level++;
        emit_stmt_list(outf, g_main_fn->body);
        indent_level--;
        fputs("}\n", outf);
    }

    fclose(outf);
    printf("output.c generated successfully.\n");
    printf("Total lines processed: %d\n", line_no);
}

int main(int argc, char **argv) {
    const char *input_path = (argc > 1) ? argv[1] : "input.txt";
    const char *output_path = (argc > 2) ? argv[2] : "output.c";

    load_source_lines(input_path);

    FILE *infile = fopen(input_path, "r");
    if (!infile) {
        fprintf(stderr, "Error: cannot open %s\n", input_path);
        free_source_lines();
        return 1;
    }

    yyin = infile;
    yyparse();

    fclose(infile);

    analyze_program();

    if (semantic_error_count > 0 || syntax_error_count > 0) {
        free_source_lines();
        return 1;
    }

    emit_program(output_path);
    free_source_lines();
    return 0;
}
