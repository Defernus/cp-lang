#include <stdio.h>
#include "handler.h"
#include "strings.h"

static bool chop(Token *out, Source src, size_t offset) {
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
      .id = TOKEN_IDENTIFIER,
      .size = size,
      .src = src,
      .start = offset,
      .value = NULL,
    };

    return true;
  }

  return false;
}

static void toString(Token token, char *out) {
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
