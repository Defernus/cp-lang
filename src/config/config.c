#include <stdlib.h>
#include "config.h"
#include "args/args.h"

Config readConfig(int argc, const char **argv) {
  Config result;

  result.in_path = (const char*) registerFlagValue(argc, argv, "-i", ARG_TYPE_STR, "Input file path", NULL);
  
  bool default_log_tokens = false;
  bool *log_tokens = (bool*) registerFlagValue(argc, argv, "--tokens", ARG_TYPE_BOOL, "Log tokens as json", &default_log_tokens);
  result.log_tokens = *log_tokens;
  free(log_tokens);

  processFlags(argc, argv);

  return result;
}
