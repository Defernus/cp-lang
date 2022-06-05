#include "syntax-node-handler.h"
#include "tokens/token.h"

List *trimTokensLeft(List* token_el) {
  Token *current_token = ((Token*) listGetValue(token_el));
  while (current_token && (current_token->id == TOKEN_WHITE_SPACE || current_token->id == TOKEN_COMMENT)) {
    token_el = listNext(token_el);
    current_token = ((Token*) listGetValue(token_el));
  }

  return token_el;
}
