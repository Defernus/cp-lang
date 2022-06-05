#ifndef SYNTAX_NODE_HANDLER_H
#define SYNTAX_NODE_HANDLER_H

#include <stdbool.h>
#include "syntax-node.h"
#include "utils/list/list.h"
#include "synatx-node-id.h"

typedef struct SyntaxNodeHandler SyntaxNodeHandler;

typedef List* (*chopNode_t)(SyntaxNode *out, List *token);
typedef const char* (*nodeToString_t)(SyntaxNode);

struct SyntaxNodeHandler {
  chopNode_t chop;
  nodeToString_t toString;
  const char *name;
  SyntaxNodeId id;
};

#endif // SYNTAX_NODE_HANDLER_H
