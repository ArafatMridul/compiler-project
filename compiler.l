%{
#include "compiler.tab.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int line_no = 1;
char last_token_text[128] = "";
int last_token_line = 1;
char current_line_text[512] = "";

static void append_text(const char *text) {
    size_t used = strlen(current_line_text);
    size_t avail = sizeof(current_line_text) - used - 1;
    if (avail == 0 || !text) {
        return;
    }
    strncat(current_line_text, text, avail);
}

static void finish_line(void) {
    current_line_text[0] = '\0';
}

static void record_token(const char *text) {
    if (!text) {
        last_token_text[0] = '\0';
        last_token_line = line_no;
        return;
    }

    snprintf(last_token_text, sizeof(last_token_text), "%s", text);
    last_token_line = line_no;
}
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

"#=>"                 { append_text(yytext); record_token(yytext); return INCLUDE; }
"#denote"             { append_text(yytext); record_token(yytext); return DEFINE; }
"<"{IDENT}"."{IDENT}">"   { append_text(yytext); record_token(yytext); yylval.str = strdup(yytext); return HEADER; }

"Start_From_Here"     { append_text(yytext); record_token(yytext); return MAIN; }

"num"                 { append_text(yytext); record_token(yytext); return TYPE_INT; }
"int"                 { append_text(yytext); record_token(yytext); return TYPE_INT; }
"fnum"                { append_text(yytext); record_token(yytext); return TYPE_FLOAT; }
"float"               { append_text(yytext); record_token(yytext); return TYPE_FLOAT; }
"dnum"                { append_text(yytext); record_token(yytext); return TYPE_DOUBLE; }
"double"              { append_text(yytext); record_token(yytext); return TYPE_DOUBLE; }
"lonum"               { append_text(yytext); record_token(yytext); return TYPE_LONG; }
"long"                { append_text(yytext); record_token(yytext); return TYPE_LONG; }
"ch"                  { append_text(yytext); record_token(yytext); return TYPE_CHAR; }
"char"                { append_text(yytext); record_token(yytext); return TYPE_CHAR; }
"bol"                 { append_text(yytext); record_token(yytext); return TYPE_BOOL; }
"bool"                { append_text(yytext); record_token(yytext); return TYPE_BOOL; }
"empty"               { append_text(yytext); record_token(yytext); return TYPE_VOID; }
"void"                { append_text(yytext); record_token(yytext); return TYPE_VOID; }

"IF"                  { append_text(yytext); record_token(yytext); return IF; }
"ELIF"                { append_text(yytext); record_token(yytext); return ELIF; }
"ELSE"                { append_text(yytext); record_token(yytext); return ELSE; }
"THEN"                { append_text(yytext); record_token(yytext); return THEN; }
"FOR"                 { append_text(yytext); record_token(yytext); return FOR; }
"until_false"         { append_text(yytext); record_token(yytext); return WHILE_KW; }
"snap"                { append_text(yytext); record_token(yytext); return BREAK_KW; }
"next_iter"           { append_text(yytext); record_token(yytext); return CONTINUE_KW; }
"give_back"           { append_text(yytext); record_token(yytext); return RETURN; }
"console.out"         { append_text(yytext); record_token(yytext); return PRINT; }
"choose"              { append_text(yytext); record_token(yytext); return CHOOSE; }
"when"                { append_text(yytext); record_token(yytext); return WHEN; }
"base_choice"         { append_text(yytext); record_token(yytext); return BASE_CHOICE; }

"<-"                  { append_text(yytext); record_token(yytext); return ASSIGN; }
"="                   { append_text(yytext); record_token(yytext); return ASSIGN; }
"BOTH"                { append_text(yytext); record_token(yytext); return AND; }
"EITHER"              { append_text(yytext); record_token(yytext); return OR; }
"NEGATE"              { append_text(yytext); record_token(yytext); return NOT; }

"<=="                 { append_text(yytext); record_token(yytext); return LE; }
"<="                  { append_text(yytext); record_token(yytext); return LE; }
">=="                 { append_text(yytext); record_token(yytext); return GE; }
">="                  { append_text(yytext); record_token(yytext); return GE; }
"!=="                 { append_text(yytext); record_token(yytext); return NE; }
"=="                  { append_text(yytext); record_token(yytext); return EQ; }

"--".*                { append_text(yytext); }
"<!-"                 { BEGIN(COMMENT); }
<COMMENT>"-!>"         { BEGIN(INITIAL); }
<COMMENT>\n            { finish_line(); line_no++; }
<COMMENT>.             { append_text(yytext); }

{FLOAT}                { append_text(yytext); record_token(yytext); yylval.str = strdup(yytext); return NUMBER; }
{INTEGER}              { append_text(yytext); record_token(yytext); yylval.str = strdup(yytext); return NUMBER; }
{STRING}               { append_text(yytext); record_token(yytext); yylval.str = strdup(yytext); return STRING_LITERAL; }

{IDENT}                { append_text(yytext); record_token(yytext); yylval.str = strdup(yytext); return IDENT; }

"("                    { append_text(yytext); record_token(yytext); return '('; }
")"                    { append_text(yytext); record_token(yytext); return ')'; }
"{"                    { append_text(yytext); record_token(yytext); return '{'; }
"}"                    { append_text(yytext); record_token(yytext); return '}'; }
";"                    { append_text(yytext); record_token(yytext); return ';'; }
","                    { append_text(yytext); record_token(yytext); return ','; }
"+"                    { append_text(yytext); record_token(yytext); return '+'; }
"-"                    { append_text(yytext); record_token(yytext); return '-'; }
"*"                    { append_text(yytext); record_token(yytext); return '*'; }
"/"                    { append_text(yytext); record_token(yytext); return '/'; }
"%"                    { append_text(yytext); record_token(yytext); return '%'; }
"<"                    { append_text(yytext); record_token(yytext); return '<'; }
">"                    { append_text(yytext); record_token(yytext); return '>'; }

{NEWLINE}               { finish_line(); line_no++; }
{WHITESPACE}+           { append_text(yytext); }
.                       { append_text(yytext); record_token(yytext); return yytext[0]; }

%%

int yywrap(void) {
    return 1;
}
