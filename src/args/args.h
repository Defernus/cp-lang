#ifndef ARGS_H
#define ARGS_H

typedef enum {
  ARG_TYPE_STR,
  ARG_TYPE_BOOL,
  ARG_TYPES_COUNT,
} ArgTypeId;

const void *registerFlagValue(int argc, const char **argv, const char *flag, ArgTypeId expected_type, const char *description, const void *default_val);
const void *registerOptionalFlagValue(int argc, const char **argv, const char *flag, ArgTypeId expected_type, const char *description);
void processFlags(int argc, const char **argv);

#endif // ARGS_H
