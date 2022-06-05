#include <stdio.h>
#include "handler.h"
#include "strings.h"

static const char BRACKETS[] = {
  '(',
  '[',
  '{',
};

static bool chop(Token *out, Source src, size_t offset) {
  for (size_t i = 0; i != TOKEN_BRACKETS_OPEN_COUNT; ++i) {
    if (src.content[offset] == BRACKETS[i]) {
      TokenBracketOpenId *value = (TokenBracketOpenId*) malloc(sizeof(TokenBracketOpenId));
      *value = i;

      *out = (Token) {
        .id = TOKEN_BRACKET_OPEN,
        .size = 1,
        .src = src,
        .start = offset,
        .value = value,
      };
      return true;
    }
  }
  return false;
}

static void toString(Token token, char *out) {
  sprintf(out, "%d", *(TokenBracketOpenId*) token.value);
}

TokenHandler newBracketOpenTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_BRACKET_OPEN,
    .name = "bracket-open",
    .toString = toString,
  };
}

bool checkOpenBracketType(List *token_el, TokenBracketOpenId bracket) {
  Token token = getToken(token_el);
  return token.id == TOKEN_BRACKET_OPEN && token.value && (*(TokenBracketOpenId*) token.value) == bracket;
}
