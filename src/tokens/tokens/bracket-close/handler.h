#ifndef CHOP_TOKEN_BRACKET_CLOSE_H
#define CHOP_TOKEN_BRACKET_CLOSE_H

#include <stdbool.h>
#include "tokens/token-handler.h"

typedef enum {
  TOKEN_BRACKET_CLOSE_ROUND,
  TOKEN_BRACKET_CLOSE_SQUARE,
  TOKEN_BRACKET_CLOSE_CURLY,

  TOKEN_BRACKETS_CLOSE_COUNT,
} TokenBracketCloseId;

TokenHandler newBracketCloseTokenHandler();
bool checkCloseBracketType(List *token, TokenBracketCloseId bracket);

#endif // CHOP_TOKEN_BRACKET_CLOSE_H
