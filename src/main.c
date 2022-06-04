#include <stdio.h>
#include "source/source.h"
#include "tokens/tokenize.h"
#include "tokens/token.h"

int main(int argc, const char **argv) {
  Source src = readSource("example/rule110/main.cp");
  Array *tokens = tokenizeSource(src);

  printf("tokens length: %ld\n", arrayGetLength(tokens));

  for (size_t i = 0; i != arrayGetLength(tokens); ++i) {
    Token token = *(Token*) arrayAt(tokens, i);
    char token_str[1024];
    sprintToken(token_str, token);
    printf("token: %s\n", token_str);
  }

  return 0;
}

