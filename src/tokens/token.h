#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdio.h>
#include "utils/list/list.h"
#include "source/source.h"

#include "token-id.h"

typedef struct {
  Source src;

  size_t start;
  size_t size;

  TokenId id;

  void* value;
} Token;

void sprintToken(char *out, Token token);
void printTokens(FILE *out, List *first_token);

#endif // TOKEN_H
