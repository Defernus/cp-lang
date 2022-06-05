#include "token.h"

Token getToken(List *token) {
  return *(Token*) listGetValue(token);
}
