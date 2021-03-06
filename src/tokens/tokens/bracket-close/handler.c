#include <stdio.h>
#include "handler.h"
#include "strings.h"

static const char BRACKETS[] = {
  ')',
  ']',
  '}',
};

static bool chop(Token *out, Source src, size_t offset) {
  for (size_t i = 0; i != TOKEN_BRACKETS_CLOSE_COUNT; ++i) {
    if (src.content[offset] == BRACKETS[i]) {
      TokenBracketCloseId *value = (TokenBracketCloseId*) malloc(sizeof(TokenBracketCloseId));
      *value = i;

      *out = (Token) {
        .id = TOKEN_BRACKET_CLOSE,
        .size = 1,
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
  sprintf(out, "%d", *(TokenBracketCloseId*) token.value);
}

TokenHandler newBracketCloseTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_BRACKET_CLOSE,
    .name = "bracket-close",
    .toString = toString,
  };
}

bool checkCloseBracketType(List *token_el, TokenBracketCloseId bracket) {
  Token token = getToken(token_el);
  return token.id == TOKEN_BRACKET_CLOSE && token.value && (*(TokenBracketCloseId*) token.value) == bracket;
}
