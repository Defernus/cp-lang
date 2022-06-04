#ifndef TOKEN_HANDLER_H
#define TOKEN_HANDLER_H

#include <stdlib.h>
#include <stdbool.h>
#include "source/source.h"
#include "token-id.h"
#include "token.h"

typedef struct TokenHandler TokenHandler;

typedef bool (*chopToken_t)(TokenHandler *self, Token *out, Source src, size_t offset);
typedef void (*tokenToString_t)(TokenHandler *self, Token, char *out);

struct TokenHandler {
  chopToken_t chop;
  tokenToString_t toString;
  TokenId id;
  const char *name;
};

#endif // TOKEN_HANDLER_H
