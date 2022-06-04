#include <stdio.h>
#include "token.h"
#include "tokenize.h"
#include "token-handler.h"

void sprintToken(char *out, Token token) {
  TokenHandler *handler = (TokenHandler*) arrayAt(getTokenHandlers(), token.id);

  const char* name = handler ? handler->name : "unknown-token";
  char content[1024] = "NULL";
  if (handler) {
    handler->toString(handler, token, content);
  }

  sprintf(
    out,
    "{\"id\":%u,\"name\":\"%s\",\"col\":%zu,\"row\":%zu}",
    token.id,
    name,
    token.col,
    token.row
  );
}
