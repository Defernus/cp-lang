#ifndef CHOP_TOKEN_OPERATOR_H
#define CHOP_TOKEN_OPERATOR_H

#include <stdlib.h>
#include "tokens/token-handler.h"
#include "source/source.h"

typedef enum {
  TOKEN_OP_CMP,
  TOKEN_OP_EQ,
  TOKEN_OP_LE,
  TOKEN_OP_GE,
  TOKEN_OP_LT,
  TOKEN_OP_GT,
  TOKEN_OP_INC,
  TOKEN_OP_DEC,
  TOKEN_OP_PLUS,
  TOKEN_OP_MINUS,

  TOKEN_OPS_COUNT,
} TokenOperatorId;

TokenHandler newOperatorTokenHandler();

#endif // CHOP_TOKEN_OPERATOR_H
