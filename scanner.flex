%{
// HEADERS
#include <stdlib.h>
#include "parser.h"
// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

\-?[0-9]+ { 
   yylval.intValue = atoi(yytext);
   return INT; 
}
"\"".*"\"" { yylval.stringValue=strdup(yytext); return STRING; }
"=" { return ATRB; }
"float"|"int" { yylval.stringValue=strdup(yytext); return TYPE; }
"main" {return MAIN; }
"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"for" { return FOR; }
"printf" { return PRINT; }
"scanf" { return SCAN; }
"(" { return LPAR; }
")" { return RPAR; }
"{" { return LBRA; }
"}" { return RBRA; }
";" { return SCOLEN; }
"," { return COLEN; }
"TRUE" { yylval.intValue=1; return BOOL; }
"FALSE" { yylval.intValue=0; return BOOL; }
"++" { return INCR; }
"--" { return DECR; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return DIV; }
"%" { return MOD; }
"==" { return EQ; }
"!=" { return DIF; }
"<" { return LE; }
">" { return GT; }
"<=" { return LEQ; }
">=" { return GTQ; }
[a-z][a-zA-Z0-9_]* { yylval.stringValue=strdup(yytext); return VAR; }
.  { yyerror("unexpected character"); }
%%

