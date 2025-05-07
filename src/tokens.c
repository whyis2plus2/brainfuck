#include <string.h>

#include "errors.h"
#include "tokens.h"

int BF_tokenize(BF_Token *out, size_t *out_idx, const char *src, size_t start_idx)
{
  if (!out || !src) return BF_ERR_INVALID_PARAM;

  src += start_idx;
  size_t src_len = strlen(src);

  BF_Token result = {0};
  char last = src[0];

  size_t i = 0;
  for (;i < src_len; ++i) {
    switch (src[i]) {
      case '+':
        result.type = BF_TOK_ARITH;
        ++result.arith.amount;
        break;

      case '-':
        result.type = BF_TOK_ARITH;
        --result.arith.amount;
        break;

      case '>':
        result.type = BF_TOK_MOVIDX;
        ++result.mov_idx.amount;
        break;

      case '<':
        result.type = BF_TOK_MOVIDX;
        --result.mov_idx.amount;
        break;

      case '[':
        result.type = BF_TOK_BEGIN_LOOP;
        *out = result;
        if (out_idx) *out_idx = start_idx + i;
        return 0;
      
      case ']':
        result.type = BF_TOK_END_LOOP;
        *out = result;
        if (out_idx) *out_idx = start_idx + i;
        return 0;

      case '.':
        result.type = BF_TOK_PRINT;
        *out = result;
        if (out_idx) *out_idx = start_idx + i;
        return 0;

      case ',':
        result.type = BF_TOK_INPUT;
        *out = result;
        if (out_idx) *out_idx = start_idx + i;
        return 0;

      default: break;
    }

    last = src[i];
    if (src[i + 1] != last) break;
  }

  *out = result;
  if (out_idx) *out_idx = start_idx + i;
  return 0;
}

enum BF_TokenType BF_normalize_token_type(enum BF_TokenType tt)
{
  if ((int)tt < 0 || tt > BF_NUM_TOKEN_TYPES) return BF_TOK_NONE;
  return tt;
}

const char *BF_get_token_type_name(enum BF_TokenType tt)
{
  switch (tt) {
    case BF_TOK_ARITH:       return "BF_TOK_ARITH";
    case BF_TOK_MOVIDX:      return "BF_TOK_MOVIDX";
    case BF_TOK_BEGIN_LOOP:  return "BF_TOK_BEGIN_LOOP";
    case BF_TOK_END_LOOP:    return "BF_TOK_END_LOOP";
    case BF_TOK_PRINT:       return "BF_TOK_PRINT";
    case BF_TOK_INPUT:       return "BF_TOK_INPUT";

    case BF_TOK_NONE:        break;
    case BF_NUM_TOKEN_TYPES: break;
  }

  return "BF_TOK_NONE";
}
