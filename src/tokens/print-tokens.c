#include "token.h"

void printTokens(FILE *out, Array *tokens) {
  fprintf(out, "{\"tokens\":[");
  for (size_t i = 0; i != arrayGetLength(tokens); ++i) {
    Token token = *(Token*) arrayAt(tokens, i);
    char token_str[1024];
    sprintToken(token_str, token);
    fprintf(out, "%s", token_str);
    if (i != arrayGetLength(tokens) - 1) {
      fprintf(out, ",");
    }
  }
  fprintf(out, "]}\n");
}
