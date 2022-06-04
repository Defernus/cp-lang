#include <stdio.h>
#include "handler.h"
#include "strings.h"

static bool chop(TokenHandler *self, Token *out, Source src, size_t offset) {
  size_t size = 0;

  for (const char *c = src.content + offset; *c; ++c, ++size) {
    if (
      !(*c >= 'a' && *c <= 'z') &&
      !(*c >= 'A' && *c <= 'Z') &&
      !(*c == '_') &&
      !(size > 0 && *c >= '0' && *c <= '9')
    ) {
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
  sprintf(out, "\"%.*s\"", (int)token.size, token.src.content + token.start);
}

TokenHandler newIdentifierTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_IDENTIFIER,
    .name = "identifier",
    .toString = toString,
  };
}
