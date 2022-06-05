#include <stdio.h>
#include "handler.h"
#include "strings.h"

static bool chop(TokenHandler *self, Token *out, Source src, size_t offset) {
  size_t size = 2;
  if (src.content[offset] != '/' || src.content[offset + 1] != '/') {
    return false;
  }

  for (const char *c = src.content + offset + 2; *c; ++c, ++size) {
    if (*c == '\n') {
      break;
    }
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

TokenHandler newCommentTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_COMMENT,
    .name = "comment",
    .toString = toString,
  };
}
