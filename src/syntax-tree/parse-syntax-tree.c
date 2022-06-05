#include "syntax-tree.h"
#include "syntax-parsing-helpers.h"
#include "syntax-node-handler.h"
#include "nodes/scope/handler.h"
#include "compile-error/compile-error.h"

SyntaxTree parseSyntaxTree(List* first_token) {
  SyntaxNode root_node = (SyntaxNode) {
    .handler = NULL,
  };

  List *current_toke = trimTokensLeft(first_token);
  if (!current_toke) {
    throwCompileError((CompileError) {
      .category_message = "Empty file",
      .status = -1,
    });
  }

  List* last_node = getNodeScope()->chop(&root_node, current_toke);
  if (!last_node) {
    throwCompileError((CompileError) {
      .category_message = ERROR_MSG_SYNTAX,
      .message = "Unexpected token",
      .token = (Token*) listGetValue(current_toke),
      .status = -1,
    });
  }

  return (SyntaxTree) {
    .root_node = root_node,
  };
}
