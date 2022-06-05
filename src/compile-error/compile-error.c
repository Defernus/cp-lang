#include <stdio.h>
#include "utils/string/string.h"

#include "compile-error.h"

typedef struct {
  size_t row;
  size_t col;
} SourcePos;

static size_t getNumberLength (int n) {
  size_t result = 1;
  while (n >= 10) {
    ++result;
    n /= 10;
  }
  return result;
}

static SourcePos getSrcPos(const char *src, size_t offset) {
  SourcePos result = (SourcePos){
    .col = 0,
    .row = 0,
  };

  for (const char *c = src; c != src + offset; ++c) {
    if (*c == '\n') {
      ++result.row;
      result.col = 0;
    } else {
      ++result.col;
    }
  }

  return result;
}

void throwCompileError(CompileError err) {
  printf("Failed to compile: \"%s\"\n", err.category_message);
  if (!err.token) {
    exit(err.status);
  }

  SourcePos pos = getSrcPos(err.token->src.content, err.token->start);

  printf("At %s:%zu:%zu\n", err.token->src.path, pos.row, pos.col);

  Array *lines = stringSplit(err.token->src.content, "\n", true);
  const char* line = *(char**) arrayAt(lines, pos.row);

  size_t offset_size = pos.col + 4 + getNumberLength(pos.row + 1);
  char *msg_offset = malloc(offset_size);
  memset(msg_offset, ' ', offset_size - 1);
  msg_offset[offset_size - 1] = 0;

  printf("%zu | %s\n%s^ %s\n", pos.row + 1, line, msg_offset, err.message);
  exit(err.status);
}
