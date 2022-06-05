#include <stdio.h>
#include "handler.h"
#include "strings.h"

static const char BRACKETS[] = {
  ')',
  ']',
  '}',
};

static bool chop(TokenHandler *self, Token *out, Source src, size_t offset) {
  for (size_t i = 0; i != TOKEN_BRACKETS_CLOSE_COUNT; ++i) {
    if (src.content[offset] == BRACKETS[i]) {
      TokenBracketCloseId *value = (TokenBracketCloseId*) malloc(sizeof(TokenBracketCloseId));
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
  sprintf(out, "%d", *(TokenBracketCloseId*) token.value);
}

TokenHandler newBracketCloseTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_BRACKET_CLOSE,
    .name = "bracket-close",
    .toString = toString,
  };
}
