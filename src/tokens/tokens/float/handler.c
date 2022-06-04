#include <stdio.h>
#include "handler.h"
#include "strings.h"

#include "tokens/tokens/int/handler.h"
#include "tokens/tokenize.h"

static bool chop(TokenHandler *self, Token *out, Source src, size_t offset) {
  size_t size = 0;
  int int_val = 0;
  size_t float_digit = 1;

  Token int_token;
  TokenHandler* int_handler = (TokenHandler* )arrayAt(getTokenHandlers(), TOKEN_INT);
  if (int_handler->chop(int_handler, &int_token,  src, offset)) {
    size += int_token.size;
    int_val = *(int*)(int_token.value);
    free(int_token.value);
  }

  if (*(src.content + offset + size) != '.') {
    return false;
  }

  float result = (float)int_val;

  for (const char *c = src.content + offset; *c; ++c, ++size) {
    if (*c >= '0' && *c <= '9') {
      float_digit *= 10;
      result += (float)(*c - '0') / float_digit;
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
  sprintf(out, "%f", *(float*) token.value);
}

TokenHandler newFloatTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_FLOAT,
    .name = "float",
    .toString = toString,
  };
}
