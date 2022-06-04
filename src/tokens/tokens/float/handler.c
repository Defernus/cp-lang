#include <stdbool.h>
#include "handler.h"
#include "strings.h"

#include "tokens/tokens/int/handler.h"

size_t chopFloat(Source src, size_t offset) {
  size_t result = chopInt(src, offset);

  if (*(src.content + offset + result) != '.') {
    return 0;
  }

  for (const char *c = src.content + offset; *c; ++c, ++result) {
    bool is_float =
      (*c >= '0' && *c <= '9') ||
      (result != 0 && *c == '_')
    ;

    if (!is_float) {
      break;
    }
  }
  return result;
}
