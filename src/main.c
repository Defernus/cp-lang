#include <stdio.h>
#include "source/source.h"
#include "tokens/tokenize.h"

int main(int argc, const char **argv) {
  Source src = readSource("example/rule110/main.cp");
  Array *tokens = tokenizeSource(src);

  printf("tokens length: %ld\n", arrayGetLength(tokens));

  return 0;
}

