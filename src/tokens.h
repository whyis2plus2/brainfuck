#ifndef BF_TOKENS_H
#define BF_TOKENS_H 1

enum BF_Token
{
  BF_TOK_NONE       = 0,
  BF_TOK_INC        = '+',
  BF_TOK_DEC        = '-',
  BF_TOK_NEXT       = '>',
  BF_TOK_PREV       = '<',
  BF_TOK_BEGIN_LOOP = '[',
  BF_TOK_END_LOOP   = ']',
  BF_TOK_PRINT      = '.',
  BF_TOK_INPUT      = ',',
};

enum BF_Token BF_normalize_token(enum BF_Token token);
char const *BF_get_token_name(enum BF_Token token);

#endif // !BF_TOKENS_H
