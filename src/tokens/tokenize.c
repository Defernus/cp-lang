#include <stdio.h>

#include "compile-error/compile-error.h"

#include "token.h"
#include "tokenize.h"
#include "token-handler.h"

#include "tokens/white-space/handler.h"
#include "tokens/keyword/handler.h"
#include "tokens/identifie/handler.h"
#include "tokens/float/handler.h"
#include "tokens/int/handler.h"
#include "tokens/string/handler.h"
#include "tokens/operator/handler.h"
#include "tokens/expression-separator/handler.h"
#include "tokens/comment/handler.h"

static Array *token_handlers = NULL;

static void registerToken( TokenHandler handler) {
  arraySetElementAt(token_handlers, handler.id, &handler);
}

Array *getTokenHandlers() {
  if (!token_handlers) {
    token_handlers = createArray(TOKENS_COUNT, sizeof(TokenHandler), NULL);

    registerToken(newWhiteSpaceTokenHandler());
    registerToken(newKeywordTokenHandler());
    registerToken(newIdentifierTokenHandler());
    registerToken(newOperatorTokenHandler());
    registerToken(newFloatTokenHandler());
    registerToken(newIntTokenHandler());
    registerToken(newStringTokenHandler());
    registerToken(newExpressionSeparatorTokenHandler());
    registerToken(newCommentTokenHandler());
  }

  return token_handlers;
}

Token chopToken(Source src, size_t offset) {
  Array *handlers = getTokenHandlers();

  for (size_t id = 0; id != arrayGetLength(handlers); ++id) {
    TokenHandler *handler = (TokenHandler*) arrayAt(handlers, id);

    Token result;
    if (handler->chop(handler, &result, src, offset)) {
      result.id = id;
      result.src = src;
      result.start = offset;
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
      char err[1024];
      sprintf(err, "Failed to tokenize \"%s\"", src.path);
      throwCompileError((CompileError) {
        .category_message = err,
        .message = "Unknown token",
        .token = &token,
        .status = -1,
      });
    }

    offset += token.size;
    arrayPush(result, &token);
  }
  
  return result;
}
