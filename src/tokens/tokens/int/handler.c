#include <stdio.h>
#include "handler.h"
#include "strings.h"

static bool chop(TokenHandler *self, Token *out, Source src, size_t offset) {
  size_t size = 0;
  int result = 0;
  int sign = 1;

  if (src.content[offset] == '-') {
    sign = -1;
    ++size;
  }
    
  for (const char *c = src.content + offset; *c; ++c, ++size) {
    if (*c >= '0' && *c <= '9') {
      result *= 10;
      result += sign * (int)(*c - '0');
      continue;
    }

    if (size != 0 && *c == '_') {
      continue;
    }

    break;
  }


  if (size) {
    int *value = (int*) malloc(sizeof(int));
    *value = result;

    *out = (Token) {
      .id = self->id,
      .size = size,
      .src = src,
      .start = offset,
      .value = value,
    };
    return true;
  }

  return false;
}

static void toString(TokenHandler *self, Token token, char *out) {
  sprintf(out, "%d", *(int*) token.value);
}

TokenHandler newIntTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_INT,
    .name = "int",
    .toString = toString,
  };
}
