#include "handler.h"
#include "strings.h"

static const char *WHITESPACES = " \t\n\r";

size_t chopWhiteSpace(Source src, size_t offset) {
  size_t result = 0;

  for (const char *c = src.content + offset; *c; ++c, ++result) {
    if (!strchr(WHITESPACES, *c)) {
      break;
    }
  }
  return result;
}
