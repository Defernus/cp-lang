#include <stdio.h>

#include "token.h"
#include "tokenize.h"
#include "token-handler.h"

#include "tokens/white-space/chop.h"
#include "tokens/keyword/chop.h"
#include "tokens/identifie/chop.h"
#include "tokens/float/chop.h"
#include "tokens/int/chop.h"
#include "tokens/operator/chop.h"
#include "tokens/expression-separator/chop.h"

static Array *token_handlers = NULL;

static void registerToken(TokenId id, const char *name, chopToken_t chop) {
  arraySetElementAt(token_handlers, id, &(TokenHandler){
    .chop = chop,
    .id = id,
    .name = name,
  });
}

static Array *getHandlers() {
  if (!token_handlers) {
    token_handlers = createArray(TOKENS_COUNT, sizeof(TokenHandler), NULL);

    registerToken(TOKEN_WHITE_SPACE, "white-space", chopWhiteSpace);
    registerToken(TOKEN_KEYWORD, "keyword", chopKeyword);
    registerToken(TOKEN_IDENTIFIER, "identifier", chopIdentifier);
    registerToken(TOKEN_OPERATOR, "operator", chopOperator);
    registerToken(TOKEN_FLOAT, "float", chopFloat);
    registerToken(TOKEN_INT, "int", chopInt);
    registerToken(TOKEN_EXPRESSION_SEPARATOR, "expression-separator", chopExpressionSeparator);
  }

  return token_handlers;
}

Token chopToken(Source src, size_t offset) {
  Array *handlers = getHandlers();

  for (size_t id = 0; id != arrayGetLength(handlers); ++id) {
    TokenHandler *handler = (TokenHandler*) arrayAt(handlers, id);

    size_t token_size = handler->chop(src, offset);
    if (token_size) {
      printf("token chopped at %zu: %s (size: %zu)\n", offset, handler->name, token_size);
      Token result = (Token) {
        .id = id,
        .size = token_size,
        .src = src,
        .start = offset,
      };
      return result;
    }
  }

  Token result = (Token) {
    .id = TOKEN_UNKNOWN,
    .size = 0,
    .src = src,
    .start = offset,
  };

  return result;
}

Array *tokenizeSource(Source src) {
  Array *result = createEmptyArray(1, sizeof(Token));
  size_t offset = 0;

  while (offset < src.size) {
    Token token = chopToken(src, offset);
    if (token.id >= TOKENS_COUNT) {
      printf("Failed to tokenize \"%s\", error: %u\n", src.path, token.id - TOKENS_COUNT);
      exit(-1);
    }
    offset += token.size;
    arrayPush(result, &token);
  }
  
  
  return result;
}
