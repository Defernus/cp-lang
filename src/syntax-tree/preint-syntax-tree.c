#include "syntax-tree.h"
#include "syntax-node-handler.h"

void printSyntaxTree(FILE *out_stream, SyntaxTree ast) {
  const char* node_str = ast.root_node.handler->toString(ast.root_node);
  fprintf(out_stream, "{\"ast\":%s}\n", node_str);
}
