#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "utils/array/array.h"
#include "compile-error/compile-error.h"
#include "syntax-tree/syntax-parsing-helpers.h"
#include "tokens/token.h"
#include "tokens/tokens/bracket-open/handler.h"
#include "tokens/tokens/bracket-close/handler.h"
#include "handler.h"

typedef struct {
  // Array<SyntaxNode>
  Array *expressions;
  bool is_root;
} ScopeValue;

static Array *_handlers;
static Array *getHandlers() {
  if (!_handlers) {
    _handlers = createEmptyArray(1, sizeof(void*));
  }
  return _handlers;
}

static List* parseSingleExpression(SyntaxNode *out, List *current_token) {
  Array *handlers = getHandlers();

  for (size_t i = 0; i != arrayGetLength(handlers); ++i) {
    SyntaxNodeHandler *handler = *(SyntaxNodeHandler**) arrayAt(handlers, i);
    List *new_token = handler->chop(out, current_token);
    if (new_token != NULL) {
      return new_token;
    }
  }

  throwCompileError((CompileError) {
    .category_message = ERROR_MSG_SYNTAX,
    .message = "Unknown expression",
    .status = -1,
    .token = (Token*) listGetValue(current_token),
  });

  return NULL;
}

static bool checkScopeStart(List *token, bool starts_with_bracket) {
  List *prev_token = listPrev(token);
  return
    starts_with_bracket ||
    !prev_token ||
    (*(Token*)listGetValue(prev_token)).src.path != getToken(token).src.path;
}

static bool checkIfEnded(bool starts_with_bracket, List *last_token, List *new_token) {
  if (starts_with_bracket) {
    if (!new_token) {
      throwCompileError((CompileError) {
        .category_message = ERROR_MSG_SYNTAX,
        .message = "Missing close curly bracket",
        .status = -1,
        .token = (Token*) listGetValue(!new_token ? last_token : new_token),
      });
    } else if (checkOpenBracketType(new_token, TOKEN_BRACKET_OPEN_CURLY)) {
      return true;
    }
  }
  if (!new_token) {
    return true;
  }
  return false;
}

static List* chop(SyntaxNode *out, List *token) {
  out->handler = NULL;

  List *current_token = token;
  bool starts_with_bracket = checkOpenBracketType(current_token, TOKEN_BRACKET_OPEN_CURLY);
  

  if (!checkScopeStart(current_token, starts_with_bracket)) {
    return NULL;
  }

  if (starts_with_bracket) {
    current_token = listNext(current_token);
  }

  Array *expressions = createEmptyArray(1, sizeof(SyntaxNode));

  while (true) {
    List *new_token = trimTokensLeft(current_token);

    if (checkIfEnded(starts_with_bracket, current_token, new_token)) {
      break;
    }

    SyntaxNode result;
    current_token = parseSingleExpression(&result, new_token);
    arrayPush(expressions, &result);
  }


  ScopeValue *value = malloc(sizeof(ScopeValue));
  *value = (ScopeValue) {
    .expressions = expressions,
    .is_root = !starts_with_bracket,
  };

  *out = (SyntaxNode) {
    .value = value,
    .handler = getNodeScope(),
  };

  return current_token;
}

static const size_t BASE_LENGTH = 1024;

static const char* toString(SyntaxNode node) {
  char *result = malloc(BASE_LENGTH);

  sprintf(result, "{}");

  return result;
}

static SyntaxNodeHandler instance = (SyntaxNodeHandler) {
  .chop = chop,
  .toString = toString,
  .name = "scope",
  .id = SYNTAX_SCOPE
};

SyntaxNodeHandler* getNodeScope() {
  return &instance;
}
