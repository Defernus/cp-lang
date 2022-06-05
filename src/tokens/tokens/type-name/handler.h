#ifndef CHOP_TYPE_NAME_H
#define CHOP_TYPE_NAME_H

#include "tokens/token-handler.h"

typedef enum {
  TOKEN_TYPE_NAME_VOID,
  TOKEN_TYPE_NAME_INT,
  TOKEN_TYPE_NAME_FLOAT,
  TOKEN_TYPE_NAME_CHAR,

  TOKEN_TYPE_NAMES_COUNT,
} TokenTypeNameId;

TokenHandler newTypeNameTokenHandler();

#endif // CHOP_TYPE_NAME_H
