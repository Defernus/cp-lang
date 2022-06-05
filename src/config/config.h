#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef struct {
  const char *in_path;
  bool log_tokens;
  bool log_ast;
} Config;

Config readConfig(int argc, const char **argv);

#endif // CONFIG_H
