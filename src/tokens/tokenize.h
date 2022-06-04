#ifndef TOKENIZE_H
#define TOKENIZE_H

#include "source/source.h"
#include "utils/array/array.h"

Array *tokenizeSource(Source);
Array *getTokenHandlers();

#endif // TOKENIZE_H
