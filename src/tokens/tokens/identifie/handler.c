#include "handler.h"
#include "strings.h"

size_t chopIdentifier(Source src, size_t offset) {
  size_t result = 0;

  for (const char *c = src.content + offset; *c; ++c, ++result) {
    if (
      !(*c >= 'a' && *c <= 'z') &&
      !(*c >= 'A' && *c <= 'Z') &&
      !(*c == '_') &&
      !(result > 0 && *c >= '0' && *c <= '9')
    ) {
      break;
    }
  }
  return result;
}
