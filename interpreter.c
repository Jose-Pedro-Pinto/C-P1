#include <stdio.h>
#include "parser.h"
void printMain(CmdList* commandList);
void printCmd(Cmd* command, int tab);
void printCmdList(CmdList* commandList, int tab);
void printExpr(Expr* expr, int tab);
void printExprList(ExprList* expr, int tab);
void printBool(Bexpr* b, int tab);
void printExpr(Expr* expr, int tab){
	if (expr == 0) {
	  yyerror("Null expression!!\n");
	}
	if (expr->kind == E_INTEGER){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("%d\n",expr->attr.value);	
	}
	if (expr->kind == E_OPERATION){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("expr:");
		switch (expr->attr.op.operator) {
		      case PLUS: 
			printf("+\n");
			break;
		      case MINUS: 
			printf("-\n");
			break;
		      case TIMES: 
			printf("*\n");
			break;
		      case DIV: 
			printf("/\n");
			break;
		      case MOD: 
			printf("%\n");
			break;
		      default: yyerror("Unknown operator!\n");
		}
		printExpr(expr->attr.op.left,tab+1);
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("expr:\n");
		printExpr(expr->attr.op.right,tab+1);
	}
	if (expr->kind == E_VAR){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("Var: ");
		printf("%s\n",expr->attr.var);
	}
}
void printBool(Bexpr* b, int tab){
	if (b == 0) {
	  yyerror("Null expression!!\n");
	}
	if (b->kind == E_BOOL){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("%d\n",b->attr.value);	
	}
	if (b->kind == E_OPERATION){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("bexpr:");
		    switch (b->attr.op.operator) {
		      case EQ: 
			printf("==\n");
			break;
		      case DIF: 
			printf("!=\n");
			break;
		      case LE: 
			printf("<\n");
			break;
		      case GT: 
			printf(">\n");
			break;
		      case LEQ: 
			printf("<=\n");
			break;
		      case GTQ: 
			printf(">=\n");
			break;
		      default: yyerror("Unknown operator!\n");
		    }
		printExpr(b->attr.op.left,tab+1);
		for (int i=0;i<tab+1;i++){
			printf("  ");
		}
		printf("expr:\n");
		printExpr(b->attr.op.right,tab+2);
	}
}
void printCmd(Cmd* command, int tab){
	if (command == 0) {
	  yyerror("Null expression!!\n");
	}
	if (command->kind == C_IF){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("Command If:\n");
		printBool(command->attr.sif.bexp,tab+1);
		for (int i=0;i<tab+1;i++){
			printf("  ");
		}
		printf("Command List:\n");
		printCmdList(command->attr.sif.cmdList,tab+2);	
	}
	if (command->kind == C_IF_ELSE){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("Command If Else:\n");
		printBool(command->attr.if_else.bexp,tab+1);
		for (int i=0;i<tab+1;i++){
			printf("  ");
		}
		printf("If Command List:\n");
		printCmdList(command->attr.if_else.ifCmdList,tab+2);
		for (int i=0;i<tab+1;i++){
			printf("  ");
		}
		printf("Else Command List:\n");
		printCmdList(command->attr.if_else.elseCmdList,tab+2);	
	}
	if (command->kind == C_WHILE){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("Command While:\n");
		printBool(command->attr.swhile.bexp,tab+1);
		for (int i=0;i<tab+1;i++){
			printf("  ");
		}
		printf("Command List:\n");
		printCmdList(command->attr.swhile.cmdList,tab+2);	
	}
	if (command->kind == C_FOR){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("Command For:\n");
		printCmd(command->attr.sfor.iatrb,tab+1);
		printBool(command->attr.sfor.bexp,tab+2);
    		printCmd(command->attr.sfor.iter,tab+1);
		for (int i=0;i<tab+1;i++){
			printf("  ");
		}
		printf("Command List:\n");
		printCmdList(command->attr.sfor.cmdList,tab+2);	
	}
	if (command->kind == C_ATRB){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("Command Atribution:\n");
		for (int i=0;i<tab+1;i++){
			printf("  ");
		}
		printf("Var: %s\n",command->attr.atrb.var);
		printExpr(command->attr.atrb.expr,tab+2);
	}
	if (command->kind == C_TATRB){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("Command Type Atribution:\n");
		for (int i=0;i<tab+1;i++){
			printf("  ");
		}
		printf("Type: %s\n",command->attr.tatrb.type);
		printCmd(command->attr.tatrb.atrb,tab+1);
	}
	if (command->kind == C_INCDEC){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("Command Increase/Decrease:\n");
		for (int i=0;i<tab+1;i++){
			printf("  ");
		}
		printf("Var: %s + (%d)\n",command->attr.incdec.var,command->attr.incdec.incdec);
	}
	if (command->kind == C_PRINT){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("Command Print:\n");
		for (int i=0;i<tab+1;i++){
			printf("  ");
		}
		printf("String: %s\n",command->attr.print.string);
		if (command->attr.print.varlist!=NULL){
			for (int i=0;i<tab+1;i++){
			printf("  ");
			}
			printf("Varlist: \n");
			printExprList(command->attr.print.varlist, tab+2);
		}
	}
	if (command->kind == C_SCAN){
		for (int i=0;i<tab;i++){
			printf("  ");
		}
		printf("Command Scan:\n");
		for (int i=0;i<tab+1;i++){
			printf("  ");
		}
		printf("String: %s\n",command->attr.scan.string);
		if (command->attr.scan.varlist!=NULL){
			for (int i=0;i<tab+1;i++){
				printf("  ");
			}
			printf("Varlist: \n");
			printExprList(command->attr.scan.varlist, tab+2);
		}
	}
}
void printCmdList(CmdList* commandList, int tab){
	if (commandList == 0) {
	  return;
	}
	printCmd(commandList->cmd,tab);
	printCmdList(commandList->next,tab);
}
void printExprList(ExprList* varlist, int tab){
	if (varlist == 0) {
	  return;
	}
	printExpr(varlist->exp,tab+1);
	printExprList(varlist->next, tab);
}
void printMain(CmdList* commandList){
	if (commandList == 0) {
	  printf("empty main\n");
	  return;
	}
	printf("funcion Main:\n");
	printCmdList(commandList, 1);
}
void eval(Expr* expr) {
  if (expr == 0) {
    yyerror("Null expression!!\n");
    return;
  }
  printf("expr:\n");
  printExpr(expr,1);
}
int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
	      printMain(root);
  }
  return 0;


}
