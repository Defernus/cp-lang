#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <stdio.h>
#include "utils/list/list.h"
#include "syntax-node.h"

typedef struct {
  SyntaxNode root_node;
} SyntaxTree;

SyntaxTree parseSyntaxTree(List* first_token);
void printSyntaxTree(FILE *out_stream, SyntaxTree ast);

#endif // SYNTAX_TREE_H
