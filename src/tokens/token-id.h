#ifndef TOKEN_ID_H
#define TOKEN_ID_H


typedef enum {
  TOKEN_WHITE_SPACE,
  TOKEN_KEYWORD,
  TOKEN_IDENTIFIER,
  TOKEN_OPERATOR,
  TOKEN_STRING,
  TOKEN_FLOAT,
  TOKEN_INT,
  TOKEN_EXPRESSION_SEPARATOR,
  TOKEN_COMMENT,

  TOKENS_COUNT,

  TOKEN_UNKNOWN,
} TokenId;

#endif // TOKEN_ID_H
