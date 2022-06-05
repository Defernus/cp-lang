#include <stdio.h>
#include "handler.h"
#include "strings.h"

static const char BRACKETS[] = {
  '(',
  '[',
  '{',
};

static bool chop(TokenHandler *self, Token *out, Source src, size_t offset) {
  for (size_t i = 0; i != TOKEN_BRACKETS_OPEN_COUNT; ++i) {
    if (src.content[offset] == BRACKETS[i]) {
      TokenBracketOpenId *value = (TokenBracketOpenId*) malloc(sizeof(TokenBracketOpenId));
      *value = i;

      *out = (Token) {
        .id = self->id,
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

static void toString(TokenHandler *self, Token token, char *out) {
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
