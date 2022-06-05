#include "handler.h"

static bool chop(TokenHandler *self, Token *out, Source src, size_t offset){
  if (src.content[offset] != ',') {
    return false;
  }

  *out = (Token) {
    .id = self->id,
    .size = 1,
    .src = src,
    .start = offset,
    .value = NULL,
  };

  return true;
}

static void toString(TokenHandler *self, Token token, char *out) {
  sprintf(out, "null");
}

TokenHandler newCommaTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_COMMA,
    .name = "comma",
    .toString = toString,
  };
}
