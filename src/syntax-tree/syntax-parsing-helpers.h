#ifndef SYNTAX_PARSER_HELPERS_H
#define SYNTAX_PARSER_HELPERS_H

#include "tokens/token.h"

// return first not white-space token or NULL if reaches end of a file
List *trimTokensLeft(List* token);

#endif // SYNTAX_PARSER_HELPERS_H
