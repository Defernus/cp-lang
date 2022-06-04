#include "handler.h"
#include "strings.h"

static const char *SEPARATORS = ";";

size_t chopExpressionSeparator(Source src, size_t offset) {
  size_t result = 0;

  for (const char *c = src.content + offset; *c; ++c, ++result) {
    if (!strchr(SEPARATORS, *c)) {
      break;
    }
  }
  return result;
}
