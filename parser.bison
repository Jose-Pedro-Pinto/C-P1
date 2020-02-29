// Tokens
%token 
  MAIN
  PRINT
  SCAN
  IF
  ELSE
  WHILE
  FOR
  LPAR
  RPAR
  LBRA
  RBRA
  SCOLEN
  COLEN
  ATRB
  VAR
  TYPE
  INT  
  STRING
  BOOL
  INCR
  DECR
  PLUS
  MINUS
  TIMES
  DIV
  MOD
  EQ
  DIF
  LE
  GT
  LEQ
  GTQ

// Operator associativity & precedence
%left PLUS MINUS
%left TIMES DIV
%left MOD
%left EQ DIF LE GT LEQ GTQ
// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue; 
  Bexpr* bexprValue;
  Cmd* cmdValue;
  CmdList* cmdListValue;
  char* stringValue;
  ExprList* varListValue;
}

%type <intValue> INT
%type <stringValue> VAR
%type <intValue> BOOL
%type <stringValue> STRING
%type <stringValue> TYPE
%type <exprValue> expr
%type <bexprValue> bexpr
%type <cmdValue> cmd
%type <cmdValue> atrb
%type <cmdListValue> cmdlist
%type <varListValue> varlist

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
CmdList* root;
}

%%
program: TYPE MAIN LPAR RPAR LBRA cmdlist RBRA  { root = $6; }
expr: 
  INT { 
    $$ = ast_integer($1); 
  }
  |
  VAR{
    $$ = ast_var($1);
  }
  | 
  expr PLUS expr { 
    $$ = ast_operation(PLUS, $1, $3); 
  } 
  | 
  expr MINUS expr { 
    $$ = ast_operation(MINUS, $1, $3); 
  } 
  | 
  expr TIMES expr { 
    $$ = ast_operation(TIMES, $1, $3); 
  } 
  | 
  expr DIV expr { 
    $$ = ast_operation(DIV, $1, $3); 
  } 
  | 
  expr MOD expr { 
    $$ = ast_operation(MOD, $1, $3); 
  } 
  ;
bexpr: 
  BOOL { 
    $$ = ast_bool($1); 
  }
  | 
  expr EQ expr { 
    $$ = ast_boperation(EQ, $1, $3); 
  } 
  | 
  expr DIF expr { 
    $$ = ast_boperation(DIF, $1, $3); 
  } 
  | 
  expr LE expr { 
    $$ = ast_boperation(LE, $1, $3); 
  } 
  | 
  expr GT expr { 
    $$ = ast_boperation(GT, $1, $3); 
  } 
  | 
  expr LEQ expr { 
    $$ = ast_boperation(LEQ, $1, $3); 
  } 
  |
  expr GTQ expr { 
    $$ = ast_boperation(GTQ, $1, $3); 
  } 
;
cmdlist:
  {$$ = NULL;}
  |cmd cmdlist{
    $$ = ast_cmdlist($1, $2);
  }
;
cmd:
  IF LPAR bexpr RPAR LBRA cmdlist RBRA{
    $$ = ast_cmdsif($3, $6); 
  }
  |
  IF LPAR bexpr RPAR LBRA cmdlist RBRA ELSE LBRA cmdlist RBRA{
    $$ = ast_cmdif_else($3, $6, $10); 
  }
  |
  WHILE LPAR bexpr RPAR LBRA cmdlist RBRA{
    $$ = ast_cmdswhile($3, $6); 
  }
  |
  FOR LPAR atrb SCOLEN bexpr SCOLEN atrb RPAR LBRA cmdlist RBRA{
    $$ = ast_cmdsfor($3, $5, $7, $10); 
  }
  |
  SCAN LPAR STRING varlist RPAR SCOLEN {
    $$ = ast_cmdscan($3,$4);
  }
  |
  PRINT LPAR STRING varlist RPAR SCOLEN {
    $$ = ast_cmdprint($3,$4);
  }
  |
  TYPE atrb SCOLEN {
    $$ = ast_cmdtatrb($1, $2); 
  }
  |
  atrb SCOLEN {
    $$ = $1; 
  }
;
atrb:
  VAR ATRB expr{
    $$ = ast_cmdatrb($3, $1); 
  }
  |
  VAR INCR{
    $$ = ast_cmdincdec(1, $1);
  }
  |
  VAR DECR{
    $$ = ast_cmdincdec(-1, $1);
  }
;
varlist:
  {
    $$ = NULL;
  }
  |
  COLEN VAR varlist{
    $$ = ast_exprlist(ast_var($2), $3);
  } 
;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
 
