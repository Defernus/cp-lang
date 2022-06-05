#ifndef SYNTAX_NODE_H
#define SYNTAX_NODE_H

#include "synatx-node-id.h"

typedef struct {
  void *value;
  struct SyntaxNodeHandler *handler;
} SyntaxNode;

#endif // SYNTAX_NODE_H
