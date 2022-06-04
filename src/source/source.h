#ifndef SOURCE_H
#define SOURCE_H

typedef struct {
  size_t size;
  const char *content;
  const char *path;
} Source;

Source readSource(const char *path);

#endif // SOURCE_H
