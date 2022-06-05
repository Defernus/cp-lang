#include "handler.h"

static bool chop(Token *out, Source src, size_t offset){
  if (src.content[offset] != ':') {
    return false;
  }

  *out = (Token) {
    .id = TOKEN_COLON,
    .size = 1,
    .src = src,
    .start = offset,
    .value = NULL,
  };

  return true;
}

static void toString(Token token, char *out) {
  sprintf(out, "null");
}

TokenHandler newColonTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_COLON,
    .name = "colon",
    .toString = toString,
  };
}
