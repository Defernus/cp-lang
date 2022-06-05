#ifndef CHOP_KEYWORD_SPACE_H
#define CHOP_KEYWORD_SPACE_H

#include <stdlib.h>
#include "tokens/token-handler.h"
#include "source/source.h"

typedef enum {
  TOKEN_KEYWORD_IMPORT,
  TOKEN_KEYWORD_CONST,
  TOKEN_KEYWORD_VAR,
  TOKEN_KEYWORD_FOR,

  TOKEN_KEYWORDS_COUNT,
} TokenKeywordId;

TokenHandler newKeywordTokenHandler();

#endif // CHOP_KEYWORD_SPACE_H
