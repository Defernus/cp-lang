#include <stdio.h>
#include "handler.h"
#include "strings.h"

const char *OPERATORS[] = {
  "==",
  "=",
  "<=",
  ">=",
  "<",
  ">",
  "++",
  "--",
  "+=",
  "-=",
  "*=",
  "/=",
  "+",
  "-",
  "*",
  "/",
};

static bool chop(TokenHandler *self, Token *out, Source src, size_t offset) {
  for (size_t i = 0; i != TOKEN_OPS_COUNT; ++i) {
    size_t size = strlen(OPERATORS[i]);
    int dif = strncmp(src.content + offset, OPERATORS[i], size);


    if (!dif) {
      TokenOperatorId *value = (TokenOperatorId*) malloc(sizeof(TokenOperatorId));
      *value = i;

      *out = (Token) {
        .id = self->id,
        .size = size,
        .src = src,
        .start = offset,
        .value = value,
      };
      return true;
    }
  }
  return false;
}

static void toString(TokenHandler *self, Token token, char *out) {
  sprintf(out, "%d", *(TokenOperatorId*) token.value);
}

TokenHandler newOperatorTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_OPERATOR,
    .name = "operator",
    .toString = toString,
  };
}
