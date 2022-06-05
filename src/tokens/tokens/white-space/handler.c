#include <stdio.h>
#include <ctype.h>
#include "handler.h"

static bool chop(Token *out, Source src, size_t offset){
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
    .id = TOKEN_WHITE_SPACE,
    .size = size,
    .src = src,
    .start = offset,
    .value = NULL,
  };

  return true;
}

static void toString(Token token, char *out) {
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
