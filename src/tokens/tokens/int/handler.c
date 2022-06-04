#include <stdbool.h>
#include "handler.h"
#include "strings.h"

size_t chopInt(Source src, size_t offset) {
  size_t result = 0;

  for (const char *c = src.content + offset; *c; ++c, ++result) {
    bool is_int =
      (result == 0 && *c == '-') ||
      (*c >= '0' && *c <= '9') ||
      (result != 0 && *c == '_')
    ;

    if (!is_int) {
      break;
    }
  }
  return result;
}
