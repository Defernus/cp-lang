#include <stdio.h>
#include "handler.h"
#include "strings.h"

static const char *KEYWORDS[] = {
  "import",
  "const",
  "var",
  "for",
};

static bool chop(TokenHandler *self, Token *out, Source src, size_t offset) {
  for (size_t i = 0; i != TOKEN_KEYWORDS_COUNT; ++i) {
    size_t size = strlen(KEYWORDS[i]);
    int dif = strncmp(src.content + offset, KEYWORDS[i], size);

    if (!dif) {
      TokenKeywordId *value = (TokenKeywordId*) malloc(sizeof(TokenKeywordId));
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
  sprintf(out, "%d", *(TokenKeywordId*) token.value);
}

TokenHandler newKeywordTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_KEYWORD,
    .name = "keyword",
    .toString = toString,
  };
}
