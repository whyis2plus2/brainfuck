#include "tokens.h"

enum BF_Token BF_normalize_token(enum BF_Token token)
{
  switch (token) {
    case BF_TOK_NONE:
    case BF_TOK_INC:
    case BF_TOK_DEC:
    case BF_TOK_NEXT:
    case BF_TOK_PREV:
    case BF_TOK_BEGIN_LOOP:
    case BF_TOK_END_LOOP:
    case BF_TOK_PRINT:
    case BF_TOK_INPUT:
      return token;
  }

  return BF_TOK_NONE;
}

char const *BF_get_token_name(enum BF_Token token)
{
  switch (token) {
    case BF_TOK_NONE:       return "BF_TOK_NONE";
    case BF_TOK_INC:        return "BF_TOK_INC";
    case BF_TOK_DEC:        return "BF_TOK_DEC";
    case BF_TOK_NEXT:       return "BF_TOK_NEXT";
    case BF_TOK_PREV:       return "BF_TOK_PREV";
    case BF_TOK_BEGIN_LOOP: return "BF_TOK_BEGIN_LOOP";
    case BF_TOK_END_LOOP:   return "BF_TOK_END_LOOP";
    case BF_TOK_PRINT:      return "BF_TOK_PRINT";
    case BF_TOK_INPUT:      return "BF_TOK_INPUT";
  }

  return "BF_TOK_NONE";
}
