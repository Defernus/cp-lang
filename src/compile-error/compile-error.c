#include <stdio.h>
#include "utils/string/string.h"

#include "compile-error.h"

static size_t getNumberLength (int n) {
  size_t result = 1;
  while (n >= 10) {
    ++result;
    n /= 10;
  }
  return result;
}

void throwCompileError(CompileError err) {
  if (!err.token) {
    printf("Failed to compile: %s\n", err.category_message);
    exit(err.status);
  }

  Array *lines = stringSplit(err.token->src.content, "\n", true);
  const char* line = *(char**) arrayAt(lines, err.token->row - 1);

  size_t offset_size = err.token->col + 3 + getNumberLength(err.token->row);
  char *msg_offset = malloc(offset_size);
  memset(msg_offset, ' ', offset_size - 1);
  msg_offset[offset_size - 1] = 0;

  printf("%s\n%zu | %s\n%s^ %s\n", err.category_message, err.token->row, line, msg_offset, err.message);
  exit(err.status);
}
