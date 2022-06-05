#include <stdio.h>
#include <ctype.h>
#include "handler.h"

static bool chop(TokenHandler *self, Token *out, Source src, size_t offset){
  size_t size = 0;

  for (const char *c = src.content + offset; *c; ++c, ++size) {
    if (!isspace(*c)) {
      break;
    }
  }

  if (!size) {
    return false;
  }

  *out = (Token) {
    .id = self->id,
    .size = size,
    .src = src,
    .start = offset,
    .value = NULL,
  };

  return true;
}

static void toString(TokenHandler *self, Token token, char *out) {
  sprintf(out, "null");
}

TokenHandler newWhiteSpaceTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_WHITE_SPACE,
    .name = "white-space",
    .toString = toString,
  };
}
