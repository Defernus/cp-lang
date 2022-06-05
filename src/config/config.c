#include <stdlib.h>
#include "config.h"
#include "args/args.h"

Config readConfig(int argc, const char **argv) {
  Config result;

  result.in_path = registerStrFlag(argc, argv, "-i", "Input file path", NULL);
  
  result.log_tokens = registerBoolFlag(argc, argv, "--tokens", "Log tokens as json");
  result.log_ast = registerBoolFlag(argc, argv, "--ast", "Log abstract syntax tree as json");

  processFlags(argc, argv);

  return result;
}
