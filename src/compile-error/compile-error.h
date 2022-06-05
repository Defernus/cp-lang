#ifndef COMPILE_ERROR_H
#define COMPILE_ERROR_H

#include "tokens/token.h"

#define ERROR_MSG_SYNTAX "Syntax error"

typedef enum {
  COMPILE_ERROR_TOKENIZE,
  COMPILE_ERROR_AST,
  COMPILE_ERROR_,
} CompileErrorStatus;

typedef struct {
  Token *token;
  const char *category_message;
  const char *message;
  int status;
} CompileError;

void throwCompileError(CompileError);

#endif // COMPILE_ERROR_H
