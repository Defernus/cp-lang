#ifndef SOURCE_H
#define SOURCE_H

#include <stdlib.h>

typedef struct {
  size_t size;
  const char *content;
  const char *path;
} Source;

Source readSource(const char *path);

#endif // SOURCE_H
