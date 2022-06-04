#include <stdio.h>
#include "source/source.h"
#include "tokens/tokenize.h"
#include "tokens/token.h"

int main(int argc, const char **argv) {
  Source src = readSource("example/rule110/main.cp");
  Array *tokens = tokenizeSource(src);

  printTokens(stdout, tokens);

  return 0;
}

