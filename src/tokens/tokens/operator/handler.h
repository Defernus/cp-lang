#ifndef CHOP_TOKEN_OPERATOR_H
#define CHOP_TOKEN_OPERATOR_H

#include "tokens/token-handler.h"

typedef enum {
  TOKEN_OP_CMP,
  TOKEN_OP_EQ,
  TOKEN_OP_LE,
  TOKEN_OP_GE,
  TOKEN_OP_LT,
  TOKEN_OP_GT,
  TOKEN_OP_INC,
  TOKEN_OP_DEC,
  TOKEN_OP_PLUS_EQ,
  TOKEN_OP_MINUS_EQ,
  TOKEN_OP_MUL_EQ,
  TOKEN_OP_DIV_EQ,
  TOKEN_OP_PLUS,
  TOKEN_OP_MINUS,
  TOKEN_OP_MUL,
  TOKEN_OP_DIV,

  TOKEN_OPS_COUNT,
} TokenOperatorId;

TokenHandler newOperatorTokenHandler();

#endif // CHOP_TOKEN_OPERATOR_H
