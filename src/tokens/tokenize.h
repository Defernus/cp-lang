#ifndef TOKENIZE_H
#define TOKENIZE_H

#include "source/source.h"
#include "utils/list/list.h"
#include "utils/array/array.h"

List *tokenizeSource(Source);
Array *getTokenHandlers();

#endif // TOKENIZE_H
