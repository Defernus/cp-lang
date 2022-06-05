#include <stdlib.h>
#include <stdio.h>
#include "handler.h"

static List* chop(SyntaxNode *out, List *token) {
  return NULL;
}

static const size_t BASE_LENGTH = 1024;

static const char* toString(SyntaxNode node) {
  char *result = malloc(BASE_LENGTH);

  sprintf(result, "null");

  return result;
}

static SyntaxNodeHandler instance = (SyntaxNodeHandler) {
  .chop = chop,
  .toString = toString,
  .name = "example",
  .id = SYNTAX_EXAMPLE,
};
SyntaxNodeHandler* getNodeExample() {
  return &instance;
}
