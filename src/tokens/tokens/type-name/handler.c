#include <stdio.h>
#include "handler.h"
#include "strings.h"

static const char *TYPE_NAMES[] = {
  "void",
  "int",
  "float",
  "char",
};

static bool chop(Token *out, Source src, size_t offset) {
  for (size_t i = 0; i != TOKEN_TYPE_NAMES_COUNT; ++i) {
    size_t size = strlen(TYPE_NAMES[i]);
    int dif = strncmp(src.content + offset, TYPE_NAMES[i], size);

    if (!dif) {
      TokenTypeNameId *value = (TokenTypeNameId*) malloc(sizeof(TokenTypeNameId));
      *value = i;

      *out = (Token) {
        .id = TOKEN_TYPE_NAME,
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

static void toString(Token token, char *out) {
  sprintf(out, "%d", *(TokenTypeNameId*) token.value);
}

TokenHandler newTypeNameTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_TYPE_NAME,
    .name = "type-name",
    .toString = toString,
  };
}
