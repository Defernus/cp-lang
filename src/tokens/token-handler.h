#ifndef TOKEN_HANDLER_H
#define TOKEN_HANDLER_H

#include <stdlib.h>
#include "source/source.h"
#include "token-id.h"

typedef size_t (*chopToken_t)(Source src, size_t offset);

typedef struct {
  chopToken_t chop;
  TokenId id;
  const char *name;
} TokenHandler;

#endif // TOKEN_HANDLER_H
