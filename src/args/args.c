#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "args.h"
#include "utils/array/array.h"
#include "utils/unreachable.h"

#define HELP_FLAG "-h"

typedef enum {
  ARG_TYPE_STR,
  ARG_TYPE_BOOL,
  ARG_TYPES_COUNT,
} ArgTypeId;

typedef struct {
  ArgTypeId expected_type;
  const void *value;
  bool required;
  const char *description;
  const char *flag;
} Arg;

static Array *_registered_args;
static Array *getRegistered() {
  if (!_registered_args) {
    _registered_args = createEmptyArray(1, sizeof(Arg));
  }
  return _registered_args;
}

static void printFlag(const char *flag, const ArgTypeId expected_type, bool required) {
  char result[1024];
  sprintf(result, "%c%s", (required && expected_type != ARG_TYPE_BOOL ? '<' : '['), flag);
  switch (expected_type) {
    case ARG_TYPE_STR: {
      sprintf(result, "%s <str>", result);
      break;
    }
    case ARG_TYPE_BOOL: {
      break;
    }
    default: {
      UNREACHABLE
    }
  }
  printf("%s%c", result, (required && expected_type != ARG_TYPE_BOOL ? '>' : ']'));
}

static void *parseFlagValue(const char *str, ArgTypeId type) {
  switch (type) {
    case ARG_TYPE_STR: {
      int str_len = strlen(str) + 1;
      void* result = (char*) malloc(str_len);
      memcpy(result, str, str_len);
      return result;
    }
    case ARG_TYPE_BOOL: {
      bool* result = (bool*) malloc(sizeof(bool));
      *result = strlen(str);
      return result;
    }
    default: {
      UNREACHABLE
    }
  }
}

const void *_registerFlagValue(int argc, const char **argv, const char *flag, ArgTypeId expected_type, const char *description, const void *default_val, bool required) {
  if (!strcmp(flag, HELP_FLAG)) {
    printf("flag \"%s\" is reserved\n", HELP_FLAG);
    exit(-1);
  }

  for (int i = 1; i < argc; ++i) {
    if (!strcmp(argv[i], flag)) {
      if (expected_type == ARG_TYPE_BOOL) {
        bool* result = (bool*) malloc(sizeof(bool));
        *result = true;

        Arg a = (Arg) {
          .flag = flag,
          .description = description,
          .expected_type = expected_type,
          .required = required,
          .value = result ? result : default_val,
        };
        arrayPush(getRegistered(), &a);
        return result;
      }

      if (i == argc - 1) {
        printf("Unexpected flag \"%s\".\nExpected usage: ", flag);
        printFlag(flag, expected_type, false);
        printf("\n");
        exit(-1);
      }

      void *result = parseFlagValue(argv[i + 1], expected_type);
      Arg a = (Arg) {
        .flag = flag,
        .description = description,
        .expected_type = expected_type,
        .required = required,
        .value = result ? result : default_val,
      };
      arrayPush(getRegistered(), &a);
      return result;
    }
  }
  if (expected_type == ARG_TYPE_BOOL) {
    bool* result = (bool*) malloc(sizeof(bool));
    *result = false;

    Arg a = (Arg) {
      .flag = flag,
      .description = description,
      .expected_type = expected_type,
      .required = required,
      .value = result ? result : default_val,
    };
    arrayPush(getRegistered(), &a);
    return result;
  }
  
  Arg a = (Arg) {
    .flag = flag,
    .description = description,
    .expected_type = expected_type,
    .required = required,
    .value = default_val,
  };
  arrayPush(getRegistered(), &a);
  return default_val;
}

const void *registerOptionalFlagValue(int argc, const char **argv, const char *flag, ArgTypeId expected_type, const char *description) {
  return _registerFlagValue(argc, argv, flag, expected_type, description, NULL, false);
}

const void *registerFlagValue(int argc, const char **argv,const char *flag, ArgTypeId expected_type, const char *description, const void *default_val) {
  const void* result = _registerFlagValue(argc, argv, flag, expected_type, description, default_val, true);

  if (result) {
    return result;
  }
  if (default_val) {
    return default_val;
  }
  
  return NULL;
}

static void printHelp() {
  for (size_t i = 0; i != arrayGetLength(getRegistered()); ++i) {
    Arg *arg = (Arg*) arrayAt(getRegistered(), i);
    printFlag(arg->flag, arg->expected_type, arg->required);
    printf("\t\t%s\n", arg->description);
  }
}

void processFlags(int argc, const char **argv) {
  for (int i = 1; i != argc; ++i) {
    if (!strcmp(argv[i], HELP_FLAG)) {
      printHelp();
      exit(0);
    }
  }
  for (size_t i = 0; i != arrayGetLength(getRegistered()); ++i) {
    Arg *arg = (Arg*) arrayAt(getRegistered(), i);
    if (arg->required && !arg->value) {
      printf("missing arg ");
      printFlag(arg->flag, arg->expected_type, true);
      printf(": %s\n", arg->description);
      exit(-1);
    }
  }
}

bool registerBoolFlag(int argc, const char **argv, const char *flag, const char *description) {
  bool default_val = false;
  bool *result_p = (bool*) registerFlagValue(argc, argv, flag, ARG_TYPE_BOOL,description, &default_val);
  bool result = *result_p;
  free(result_p);

  return result;
}
const char *registerStrFlag(int argc, const char **argv, const char *flag, const char *description, const char *default_val) {
  return (const char *) registerFlagValue(argc, argv, flag, ARG_TYPE_STR, description, default_val);
}

const char *registerOptionalStrFlag(int argc, const char **argv, const char *flag, const char *description) {
  return (const char *) registerOptionalFlagValue(argc, argv, flag, ARG_TYPE_STR, description);
}

