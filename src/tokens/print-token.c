#include <stdio.h>
#include "token.h"
#include "tokenize.h"
#include "token-handler.h"

void sprintToken(char *out, List *token_el) {
  Token token = *(Token*) listGetValue(token_el);
  TokenHandler *handler = (TokenHandler*) arrayAt(getTokenHandlers(), token.id);

  const char* name = handler ? handler->name : "unknown-token";
  char value[1024] = "null";
  if (handler) {
    handler->toString(token, value);
  }

  sprintf(
    out,
    "{\"id\":%u,\"name\":\"%s\",\"start\":%zu,\"value\":%s,\"src\":\"%s\"}",
    token.id,
    name,
    token.start,
    value,
    token.src.path
  );
}
