#include <stdio.h>
#include "config/config.h"
#include "source/source.h"
#include "tokens/tokenize.h"
#include "tokens/token.h"
#include "syntax-tree/syntax-tree.h"

int main(int argc, const char **argv) {
  Config cfg = readConfig(argc, argv);

  Source src = readSource(cfg.in_path);
  List *first_token = tokenizeSource(src);

  if (cfg.log_tokens) {
    printTokens(stdout, first_token);
  }

  SyntaxTree ast = parseSyntaxTree(first_token);

  if (cfg.log_ast) {
    printSyntaxTree(stdout, ast);
  }

  return 0;
}

