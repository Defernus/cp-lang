#include <stdio.h>
#include "handler.h"
#include "strings.h"

static const char *SEPARATORS = ";";

static bool chop(TokenHandler *self, Token *out, Source src, size_t offset) {
  size_t size = 0;

  for (const char *c = src.content + offset; *c; ++c, ++size) {
    if (!strchr(SEPARATORS, *c)) {
      break;
    }
  }

  if (size) {
    *out = (Token) {
      .id = self->id,
      .size = size,
      .src = src,
      .start = offset,
      .value = NULL,
    };

    return true;
  }

  return false;
}

static void toString(TokenHandler *self, Token token, char *out) {
  sprintf(out, "\";\"");
}

TokenHandler newExpressionSeparatorTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_EXPRESSION_SEPARATOR,
    .name = "expression-separator",
    .toString = toString,
  };
}
