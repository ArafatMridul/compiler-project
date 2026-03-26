%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int line_no = 1;
int indent_level = 0;
int if_paren_needed = 0;
int pending_include = 0;
int include_stdio = 0;
int include_math = 0;
int include_bool = 0;
FILE *outfile;

void add_indentation(FILE *f, int level);
void emit_include(const char *header);
%}

%option noinput nounput

%x COMMENT

DIGIT       [0-9]
INTEGER     {DIGIT}+
FLOAT       {DIGIT}+\.{DIGIT}+
IDENT       [A-Za-z_][A-Za-z0-9_]*
WHITESPACE  [ \t\r]
NEWLINE     \n
STRING      \"[^\"\n]*\"

%%

"#=>"                { pending_include = 1; }
"#denote"            { fprintf(outfile, "#define"); }
"<"{IDENT}"."{IDENT}">"   {
    if (pending_include) {
        emit_include(yytext);
        pending_include = 0;
    } else {
        fprintf(outfile, "%s", yytext);
    }
}

"Start_From_Here"[ \t]*"("[ \t]*")" {
    fprintf(outfile, "int main()");
}

"num"        { fprintf(outfile, "int"); }
"fnum"       { fprintf(outfile, "float"); }
"dnum"       { fprintf(outfile, "double"); }
"lonum"      { fprintf(outfile, "long int"); }
"ch"         { fprintf(outfile, "char"); }
"bol"        { fprintf(outfile, "bool"); }
"empty"      { fprintf(outfile, "void"); }

"IF"         { fprintf(outfile, "if ("); if_paren_needed = 1; }

"ELIF"       {
    if (indent_level > 0) {
        indent_level--;
    }
    fprintf(outfile, "\n");
    add_indentation(outfile, indent_level);
    fprintf(outfile, "else if (");
    if_paren_needed = 1;
}

"ELSE"       {
    if (indent_level > 0) {
        indent_level--;
    }
    fprintf(outfile, "\n");
    add_indentation(outfile, indent_level);
    fprintf(outfile, "else");
}

"THEN"       {
    if (if_paren_needed) {
        fprintf(outfile, ") ");
        if_paren_needed = 0;
    }
}

"FOR"        { fprintf(outfile, "for"); }
"until_false" { fprintf(outfile, "while"); }
"snap"       { fprintf(outfile, "break"); }
"next_iter"  { fprintf(outfile, "continue"); }
"give_back"  { fprintf(outfile, "return"); }

"console.out" { fprintf(outfile, "printf"); }

"<-"         { fprintf(outfile, " = "); }
"BOTH"       { fprintf(outfile, "&&"); }
"EITHER"     { fprintf(outfile, "||"); }
"NEGATE"     { fprintf(outfile, "!"); }

"<=="        { fprintf(outfile, "<="); }
">=="        { fprintf(outfile, ">="); }
"!=="        { fprintf(outfile, "!="); }
"=="         { fprintf(outfile, "=="); }

"--".*       { fprintf(outfile, "//%s", yytext + 2); }

"<!-" {
    fprintf(outfile, "/*");
    BEGIN(COMMENT);
}

<COMMENT>"-!>" {
    fprintf(outfile, "*/");
    BEGIN(INITIAL);
}

<COMMENT>\n {
    fprintf(outfile, "\n");
    line_no++;
}

<COMMENT>. {
    fprintf(outfile, "%s", yytext);
}

{FLOAT}      { fprintf(outfile, "%s", yytext); }
{INTEGER}    { fprintf(outfile, "%s", yytext); }
{STRING}     { fprintf(outfile, "%s", yytext); }

{IDENT}      { fprintf(outfile, "%s", yytext); }

"("          { fprintf(outfile, "("); }
")"          { fprintf(outfile, ")"); }

"{"          {
    fprintf(outfile, " {\n");
    indent_level++;
    add_indentation(outfile, indent_level);
}

"}"          {
    if (indent_level > 0) {
        indent_level--;
    }
    fprintf(outfile, "\n");
    add_indentation(outfile, indent_level);
    fprintf(outfile, "}");
}

";"          { fprintf(outfile, ";"); }
"+"          { fprintf(outfile, "+"); }
"-"          { fprintf(outfile, "-"); }
"*"          { fprintf(outfile, "*"); }
"/"          { fprintf(outfile, "/"); }
"%"          { fprintf(outfile, "%%"); }
"<"          { fprintf(outfile, "<"); }
">"          { fprintf(outfile, ">"); }

"->"         { fprintf(outfile, ";"); }

{NEWLINE} {
    fprintf(outfile, "\n");
    line_no++;
    add_indentation(outfile, indent_level);
}

{WHITESPACE}+ { fprintf(outfile, "%s", yytext); }

. { fprintf(outfile, "%s", yytext); }

%%

int yywrap() {
    return 1;
}

void emit_include(const char *header) {
    if (strcmp(header, "<stdio.h>") == 0) {
        if (include_stdio) {
            return;
        }
        include_stdio = 1;
    } else if (strcmp(header, "<math.h>") == 0) {
        if (include_math) {
            return;
        }
        include_math = 1;
    } else if (strcmp(header, "<stdbool.h>") == 0) {
        if (include_bool) {
            return;
        }
        include_bool = 1;
    }

    fprintf(outfile, "#include %s", header);
}

void add_indentation(FILE *f, int level) {
    for (int i = 0; i < level; i++) {
        fprintf(f, "    ");
    }
}

int main(int argc, char **argv) {
    const char *input_path = (argc > 1) ? argv[1] : "input.txt";
    const char *output_path = (argc > 2) ? argv[2] : "output.c";
    FILE *infile = fopen(input_path, "r");
    if (!infile) {
        printf("Error: Cannot open %s\n", input_path);
        return 1;
    }

    outfile = fopen(output_path, "w");
    if (!outfile) {
        printf("Error: Cannot create %s\n", output_path);
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
    yylex();

    if (pending_include) {
        fprintf(stderr, "Warning: dangling #=> without a header near line %d\n", line_no);
    }

    fclose(infile);
    fclose(outfile);

    printf("output.c generated successfully.\n");
    printf("Total lines processed: %d\n", line_no);
    return 0;
}