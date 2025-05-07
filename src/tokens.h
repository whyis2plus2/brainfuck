#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef BF_TOKENS_H
#define BF_TOKENS_H 1

enum BF_TokenType
{
  BF_TOK_NONE,
  BF_TOK_ARITH,
  BF_TOK_MOVIDX,
  BF_TOK_BEGIN_LOOP,
  BF_TOK_END_LOOP,
  BF_TOK_PRINT,
  BF_TOK_INPUT,
  BF_NUM_TOKEN_TYPES
};

typedef struct {
  enum BF_TokenType type;
  uint16_t amount;
} BF_TokenArith;

typedef struct {
  enum BF_TokenType type;
  int64_t amount;
} BF_TokenMovIdx;

typedef union {
  enum BF_TokenType type;
  BF_TokenArith arith;
  BF_TokenMovIdx mov_idx;
} BF_Token;

/* 
 * TODO:
 *  - implement a tokenization function for new token type
 *  - remake the parser :(
 *  - implement arithmetic folding (eg. folding +++ into {add 3})
 */
int BF_tokenize(BF_Token *out, size_t *out_idx, const char *src, size_t start_idx);
enum BF_TokenType BF_normalize_token_type(enum BF_TokenType tt);
const char *BF_get_token_type_name(enum BF_TokenType tt);

#endif // !BF_TOKENS_H
