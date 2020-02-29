
// AST definitions
#ifndef __ast_h__
#define __ast_h__
// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION,
    E_VAR
  } kind;
  union {
    int value; // for integer values
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
    char* var;
  } attr;
};
struct _ExprList{
  struct _Expr* exp;
  struct _ExprList* next;
};
struct _Bexpr {
  enum { 
    E_BOOL,
    E_BOPERATION
  } kind;
  union {
    int value; // for integer values
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};
struct _Cmd {
  enum { 
    C_IF,
    C_IF_ELSE,
    C_WHILE,
    C_FOR,
    C_ATRB,
    C_TATRB,
    C_INCDEC,
    C_PRINT,
    C_SCAN
  } kind;
  union {
    struct { 
      struct _Bexpr* bexp;
      struct _CmdList* cmdList;
    } sif; // for binary expressions
    struct { 
      struct _Bexpr* bexp;
      struct _CmdList* ifCmdList;
      struct _CmdList* elseCmdList;
    } if_else; // for binary expressions
    struct { 
      struct _Bexpr* bexp;
      struct _CmdList* cmdList;
    } swhile; // for binary expressions
    struct { 
      struct _Cmd* iatrb;
      struct _Bexpr* bexp;
      struct _Cmd* iter;
      struct _CmdList* cmdList;
    } sfor; // for binary expressions
    struct { 
      struct _Expr* expr; 
      char* var;
    } atrb; // for binary expressions
    struct { 
      char* type;
      struct _Cmd* atrb; 
    } tatrb; // for binary expressions
    struct { 
      int incdec;
      char* var;
    } incdec; // for binary expressions
    struct { 
      char* string;
      struct _ExprList* varlist; 
    } print; // for binary expressions
    struct { 
      char* string;
      struct _ExprList* varlist; 
    } scan; // for binary expressions
  } attr;
};
struct _CmdList{
  struct _Cmd* cmd;
  struct _CmdList* next;
};


typedef struct _Expr Expr; // Convenience typedef
typedef struct _Bexpr Bexpr; // Convenience typedef
typedef struct _ExprList ExprList;
typedef struct _Cmd Cmd;
typedef struct _CmdList CmdList;
// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Bexpr* ast_bool(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr* ast_var(char* var);
Bexpr* ast_boperation(int operator, Expr* left, Expr* right);
ExprList* ast_exprlist(Expr* expr, ExprList* next);
Cmd* ast_cmdsif(Bexpr* bexp, CmdList* cmdList);
Cmd* ast_cmdif_else(Bexpr* bexp, CmdList* ifCmdList, CmdList* elseCmdList);
Cmd* ast_cmdswhile(Bexpr* bexp, CmdList* cmdList);
Cmd* ast_cmdsfor(Cmd* iatrb, Bexpr* bexp, Cmd* iter, CmdList* cmdList);
Cmd* ast_cmdatrb(Expr* exp, char* var);
Cmd* ast_cmdtatrb(char* type, Cmd* atrb);
Cmd* ast_cmdincdec(int incdec, char* var);
Cmd* ast_cmdprint(char* type, ExprList* varList);
Cmd* ast_cmdscan(char* type, ExprList* varList);
CmdList* ast_cmdlist(Cmd* cmd, CmdList* next);
#endif 
