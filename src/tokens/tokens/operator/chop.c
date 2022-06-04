#include "chop.h"
#include "strings.h"

static const char *OPERATORS[] = {
  "==",
  "=",
  "<=",
  ">=",
  "<",
  ">",
  "++",
  "--",
  "+",
  "-",
};
static const size_t OPERATORS_COUNT = sizeof(OPERATORS) / sizeof(char*);

size_t chopOperator(Source src, size_t offset) {
  for (const char **operator = OPERATORS; operator != OPERATORS + OPERATORS_COUNT; ++operator) {
    size_t size = strlen(*operator);
    int dif = strncmp(src.content + offset, *operator, size);

    if (!dif) {
      return size;
    }
  }
  return 0;
}
