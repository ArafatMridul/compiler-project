%{
#include "parser.tab.h"
#include <string.h>
#include <stdlib.h>

int line_no = 1;
int pending_include = 0;
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

"#=>"                 { pending_include = 1; return INCLUDE; }
"#denote"             { return DEFINE; }
"<"{IDENT}"."{IDENT}">"   { yylval.str = strdup(yytext); pending_include = 0; return HEADER; }

"Start_From_Here"     { return MAIN; }

"num"                 { return TYPE_INT; }
"fnum"                { return TYPE_FLOAT; }
"dnum"                { return TYPE_DOUBLE; }
"lonum"               { return TYPE_LONG; }
"ch"                  { return TYPE_CHAR; }
"bol"                 { return TYPE_BOOL; }
"empty"               { return TYPE_VOID; }

"IF"                  { return IF; }
"ELIF"                { return ELIF; }
"ELSE"                { return ELSE; }
"THEN"                { return THEN; }
"FOR"                 { return FOR; }
"until_false"         { return WHILE_KW; }
"snap"                { return BREAK_KW; }
"next_iter"           { return CONTINUE_KW; }
"give_back"           { return RETURN; }
"console.out"         { return PRINT; }

"<-"                  { return ASSIGN; }
"BOTH"                { return AND; }
"EITHER"              { return OR; }
"NEGATE"              { return NOT; }

"<=="                 { return LE; }
">=="                 { return GE; }
"!=="                 { return NE; }
"=="                  { return EQ; }

"--".*                { /* line comment */ }
"<!-"                 { BEGIN(COMMENT); }
<COMMENT>"-!>"         { BEGIN(INITIAL); }
<COMMENT>\n            { line_no++; }
<COMMENT>.             { /* skip block comment content */ }

{FLOAT}                { yylval.str = strdup(yytext); return NUMBER; }
{INTEGER}              { yylval.str = strdup(yytext); return NUMBER; }
{STRING}               { yylval.str = strdup(yytext); return STRING_LITERAL; }

{IDENT}                { yylval.str = strdup(yytext); return IDENT; }

"("                    { return '('; }
")"                    { return ')'; }
"{"                    { return '{'; }
"}"                    { return '}'; }
";"                    { return ';'; }
","                    { return ','; }
"+"                    { return '+'; }
"-"                    { return '-'; }
"*"                    { return '*'; }
"/"                    { return '/'; }
"%"                    { return '%'; }
"<"                    { return '<'; }
">"                    { return '>'; }

{NEWLINE}               { line_no++; }
{WHITESPACE}+           { /* skip spaces */ }
.                       { return yytext[0]; }

%%

int yywrap(void) {
    return 1;
}
