#include "token.h"

void printTokens(FILE *out, List *first_token) {
  fprintf(out, "{\"tokens\":[");
  List *current_token = first_token;

  while (current_token) {
    char token_str[1024];
    sprintToken(token_str, current_token);
    fprintf(out, "%s", token_str);

    current_token = listNext(current_token);
    if (current_token) {
      fprintf(out, ",");
    }
  }
  fprintf(out, "]}\n");
}
