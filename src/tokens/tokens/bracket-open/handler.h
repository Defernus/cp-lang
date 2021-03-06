#ifndef CHOP_TOKEN_BRACKET_OPEN_H
#define CHOP_TOKEN_BRACKET_OPEN_H

#include <stdbool.h>
#include "tokens/token-handler.h"

typedef enum {
  TOKEN_BRACKET_OPEN_ROUND,
  TOKEN_BRACKET_OPEN_SQUARE,
  TOKEN_BRACKET_OPEN_CURLY,

  TOKEN_BRACKETS_OPEN_COUNT,
} TokenBracketOpenId;

TokenHandler newBracketOpenTokenHandler();
bool checkOpenBracketType(List *token, TokenBracketOpenId bracket);

#endif // CHOP_TOKEN_BRACKET_OPEN_H
