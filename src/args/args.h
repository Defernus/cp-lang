#ifndef ARGS_H
#define ARGS_H

bool registerBoolFlag(int argc, const char **argv, const char *flag, const char *description);
const char *registerStrFlag(int argc, const char **argv, const char *flag, const char *description, const char *default_val);
const char *registerOptionalStrFlag(int argc, const char **argv, const char *flag, const char *description);

void processFlags(int argc, const char **argv);

#endif // ARGS_H
