#include <stdio.h>
#include <strings.h>
#include "handler.h"
#include "compile-error/compile-error.h"

#define MAX_STRING_LENGTH 1024
const char *SPECIAL_CHARACTERS = "ntvbrfa\\?\"0";

static bool chop(Token *out, Source src, size_t offset){
  char result[MAX_STRING_LENGTH];
  char *curent = result;
  const char *c = src.content + offset;

  if (*c != '"') {
    return false;
  }
  ++c;

  while (curent < result + MAX_STRING_LENGTH) {
    if (*c == '\0') {
      return false;
    }
    if (*c == '"') {
      ++c;
      *(curent++) = 0;
      break;
    }
    if (*c == '\\') {
      ++c;
      switch (*c) {
        case 'n': {
          *(curent++) = '\n';
          break;
        }
        case 't': {
          *(curent++) = '\t';
          break;
        }
        case 'v': {
          *(curent++) = '\v';
          break;
        }
        case 'b': {
          *(curent++) = '\b';
          break;
        }
        case 'r': {
          *(curent++) = '\r';
          break;
        }
        case 'f': {
          *(curent++) = '\f';
          break;
        }
        case 'a': {
          *(curent++) = '\a';
          break;
        }
        case '\\': {
          *(curent++) = '\\';
          break;
        }
        case '?': {
          *(curent++) = '\?';
          break;
        }
        case '"': {
          *(curent++) = '\"';
          break;
        }
        case '0': {
          *(curent++) = '\0';
          break;
        }
        default: {
          out->start = (size_t) (c - src.content);
          out->src = src;
          out->id = TOKEN_STRING;
          throwCompileError((CompileError) {
            .category_message = "Failed to tokenize string literal",
            .message = "Unknown special character",
            .status = -1,
            .token = out,
          });
        }
      }
      ++c;
      continue;
    }
  
    *(curent++) = *(c++);
  }

  int val_size = (int) (curent - result);
  void *value = malloc(val_size);
  memcpy(value, result, val_size);

  *out = (Token) {
    .id = TOKEN_STRING,
    .size = c - src.content - offset,
    .src = src,
    .start = offset,
    .value = value,
  };

  return true;
}

static void toString(Token token, char *out) {
  sprintf(out, "%.*s", (int) token.size, token.src.content + token.start);
}

TokenHandler newStringTokenHandler() {
  return (TokenHandler) {
    .chop = chop,
    .id = TOKEN_STRING,
    .name = "string",
    .toString = toString,
  };
}
