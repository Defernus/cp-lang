#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include "source/source.h"

#include "token-id.h"

typedef struct {
  Source src;

  size_t row;
  size_t col;

  size_t start;
  size_t size;

  TokenId id;

  void* value;
} Token;

#endif // TOKEN_H
