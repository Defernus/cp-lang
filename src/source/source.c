#include <stdio.h>
#include <stdlib.h>

#include "source.h"

Source readSource(const char *path) {
  FILE *file = fopen(path, "r");

  if (file == NULL) {
    printf("Failed to open file '%s'.\n", path);
    exit(-1);
  }


  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);
  
  Source result;
  result.path = path;
  char *content = malloc(length+1);

  fread(content, 1, length, file);
  fclose(file);
  content[length] = 0;

  result.content = content;
  result.size = length;

  return result;
}
