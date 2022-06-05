#include <stdio.h>
#include "config/config.h"
#include "source/source.h"
#include "tokens/tokenize.h"
#include "tokens/token.h"

int main(int argc, const char **argv) {
  Config cfg = readConfig(argc, argv);

  Source src = readSource(cfg.in_path);
  List *tokens = tokenizeSource(src);

  if (cfg.log_tokens) {
    printTokens(stdout, tokens);
  }

  return 0;
}

