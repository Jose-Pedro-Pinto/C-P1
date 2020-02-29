// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}
Bexpr* ast_bool(int v) {
  Bexpr* node = (Bexpr*) malloc(sizeof(Bexpr));
  node->kind = E_BOOL;
  node->attr.value = v;
  return node;
}

Expr* ast_operation
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}
Expr* ast_var
(char* var) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_VAR;
  node->attr.var = var;
  return node;
}
Bexpr* ast_boperation
(int boperator, Expr* left, Expr* right) {
  Bexpr* node = (Bexpr*) malloc(sizeof(Bexpr));
  node->kind = E_BOPERATION;
  node->attr.op.operator = boperator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

ExprList* ast_exprlist
(Expr* expr, ExprList* next){
  ExprList* list = (ExprList*) malloc(sizeof(ExprList));
  list->exp=expr;
  list->next=next;
  return list;
}
Cmd* ast_cmdsif
(Bexpr* bexp, CmdList* cmdList){
  Cmd* cmd = (Cmd*) malloc(sizeof(Cmd));
  cmd->kind = C_IF;
  cmd->attr.sif.bexp = bexp;
  cmd->attr.sif.cmdList = cmdList;
  return cmd;
}
Cmd* ast_cmdif_else
(Bexpr* bexp, CmdList* ifCmdList, CmdList* elseCmdList){
  Cmd* cmd = (Cmd*) malloc(sizeof(Cmd));
  cmd->kind = C_IF_ELSE;
  cmd->attr.if_else.bexp = bexp;
  cmd->attr.if_else.ifCmdList = ifCmdList;
  cmd->attr.if_else.elseCmdList = elseCmdList;
  return cmd;
}
Cmd* ast_cmdswhile
(Bexpr* bexp, CmdList* cmdList){
  Cmd* cmd = (Cmd*) malloc(sizeof(Cmd));
  cmd->kind = C_WHILE;
  cmd->attr.sif.bexp = bexp;
  cmd->attr.sif.cmdList = cmdList;
  return cmd;
}
Cmd* ast_cmdsfor
(Cmd* iatrb, Bexpr* bexp, Cmd* iter, CmdList* cmdList){
  Cmd* cmd = (Cmd*) malloc(sizeof(Cmd));
  cmd->kind = C_FOR;
  cmd->attr.sfor.iatrb = iatrb;
  cmd->attr.sfor.bexp = bexp;
  cmd->attr.sfor.iter = iter;
  cmd->attr.sfor.cmdList = cmdList;
  return cmd;
}
Cmd* ast_cmdatrb
(Expr* exp, char* var){
  Cmd* cmd = (Cmd*) malloc(sizeof(Cmd));
  cmd->kind = C_ATRB;
  cmd->attr.atrb.expr = exp;
  cmd->attr.atrb.var = var;
  return cmd;
}
Cmd* ast_cmdtatrb
(char* type, Cmd* atrb){
  Cmd* cmd = (Cmd*) malloc(sizeof(Cmd));
  cmd->kind = C_TATRB;
  cmd->attr.tatrb.type = type;
  cmd->attr.tatrb.atrb = atrb;
  return cmd;
}
Cmd* ast_cmdincdec(int incdec, char* var){
  Cmd* cmd = (Cmd*) malloc(sizeof(Cmd));
  cmd->kind = C_INCDEC;
  cmd->attr.incdec.incdec = incdec;
  cmd->attr.incdec.var = var;
  return cmd;
}
Cmd* ast_cmdprint(char* string, ExprList* varlist){
  Cmd* cmd = (Cmd*) malloc(sizeof(Cmd));
  cmd->kind = C_PRINT;
  cmd->attr.print.string = string;
  cmd->attr.print.varlist = varlist;
  return cmd;
}
Cmd* ast_cmdscan(char* string, ExprList* varlist){
  Cmd* cmd = (Cmd*) malloc(sizeof(Cmd));
  cmd->kind = C_SCAN	;
  cmd->attr.scan.string = string;
  cmd->attr.scan.varlist = varlist;
  return cmd;
}
CmdList* ast_cmdlist
(Cmd* cmd, CmdList* next){
  CmdList* cmdList = (CmdList*) malloc(sizeof(CmdList));
  cmdList->cmd = cmd;
  cmdList->next = next;
  return cmdList;
}
