#include "handler.h"
#include "strings.h"

static const char *KEYWORDS[] = {
  "const",
  "var",
  "for",
};
static const size_t KEYWORDS_COUNT = sizeof(KEYWORDS) / sizeof(char*);

size_t chopKeyword(Source src, size_t offset) {
  for (const char **keyword = KEYWORDS; keyword != KEYWORDS + KEYWORDS_COUNT; ++keyword) {
    size_t size = strlen(*keyword);
    int dif = strncmp(src.content + offset, *keyword, size);

    if (!dif) {
      return size;
    }
  }
  return 0;
}
