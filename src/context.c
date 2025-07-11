#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "context.h"
#include "errors.h"
#include "tokens.h"

int BF_token_list_push(BF_TokenList *tl, BF_Token token)
{
  if (!tl) return BF_ERR_INVALID_PARAM;
  if (BF_normalize_token_type(token.type) == BF_TOK_NONE) return BF_ERR_INVALID_TOKEN;

  if (tl->len == tl->cap) {
    tl->cap = (tl->cap)? tl->cap * 2 : BF_LIST_START_CAPACITY;

    tl->data = realloc(
      tl->data,
      sizeof(*tl->data) * tl->cap
    );

    if (!tl->data) BF_PANIC("failed to append to token list: out of memory");
  }

  tl->data[tl->len] = token;
  ++tl->len;

  return 0;
}

int BF_jump_list_push(BF_JumpList *jl, size_t idx)
{
  if (!jl) return BF_ERR_INVALID_PARAM;
  
  if (jl->len == jl->cap) {
    jl->cap = (jl->cap)? jl->cap * 2 : BF_LIST_START_CAPACITY;

    jl->indicies = realloc(
      jl->indicies,
      sizeof(*jl->indicies) * jl->cap
    );

    if (!jl->indicies) BF_PANIC("failed to append to jump list: out of memory");
  }

  jl->indicies[jl->len] = idx;
  ++jl->len;

  return 0;
}

int BF_create_context(BF_Context *out_ctx, const char *filename, size_t num_cells, bool alloc_cells)
{
  if (!out_ctx || !num_cells) return BF_ERR_INVALID_PARAM;

  BF_Context ctx = {
    .num_cells = num_cells,
    .filename = filename
  };

  if (alloc_cells) {
    ctx.cells = calloc(ctx.num_cells, 1 /* sizeof(uint8_t) is always 1 */ );
    if (!ctx.cells) BF_PANIC("out of memory");
  }

  *out_ctx = ctx;
  return 0;
}

int BF_destroy_context(BF_Context *ctx)
{
  if (!ctx) return BF_ERR_INVALID_PARAM;

  free(ctx->cells);
  free(ctx->tokens.data);
  memset(ctx, 0, sizeof(*ctx));

  return 0;
}

int BF_eval_token(size_t *out_idx, BF_Context *ctx, size_t idx, bool do_io)
{
  if (!ctx) return BF_ERR_INVALID_PARAM;
  if (!ctx->num_cells || !ctx->cells) return BF_ERR_INVALID_PARAM;
  if (idx > ctx->tokens.len) return BF_ERR_INVALID_PARAM;

  const BF_Token tok = ctx->tokens.data[idx];
  switch (tok.type) {
    case BF_NUM_TOKEN_TYPES:
    case BF_TOK_NONE: break;

    case BF_TOK_ARITH:
      ctx->cells[ctx->current_index] += tok.arith.amount;
      break;

    case BF_TOK_MOVIDX:
      ctx->current_index += tok.mov_idx.amount;
      if (ctx->current_index >= ctx->num_cells) return BF_ERR_BAD_CELL_IDX;
      break;

    case BF_TOK_BEGIN_LOOP:
      BF_jump_list_push(&ctx->loops, idx);

      if (ctx->loops.len > BF_NESTING_LIMIT) return BF_ERR_TOO_NESTED;
      break;

    case BF_TOK_END_LOOP:
      // just incase of integer overflow
      if (ctx->loops.len == 0) return BF_ERR_UNMATCHED_LOOP;

      if (ctx->cells[ctx->current_index] && out_idx) {
        *out_idx = ctx->loops.indicies[ctx->loops.len - 1];
        return 0;
      }

      --ctx->loops.len;

      break;

    case BF_TOK_PRINT:
      if (!do_io) break;
      putchar((char)ctx->cells[ctx->current_index]);
      break;

    case BF_TOK_INPUT:
      if (!do_io) break;
      ctx->cells[ctx->current_index] = getchar();
      break;
  }

  if (out_idx) *out_idx = idx;
  return 0;
}

int BF_run_context(BF_Context *ctx)
{
  if (!ctx) return BF_ERR_INVALID_PARAM;
  if (!ctx->num_cells || !ctx->cells) return BF_ERR_INVALID_PARAM;

  for (size_t i = 0; i < ctx->tokens.len; ++i) {
    int result = BF_eval_token(&i, ctx, i, true);
    if (result) return result;
  }

  return 0;
}

// check for errors in a context without changing the state of any of the cells
// this works even if no cells have been allocated
int BF_test_context(const BF_Context *ctx)
{
  if (!ctx) return BF_ERR_INVALID_PARAM;
  if (!ctx->num_cells) return BF_ERR_INVALID_PARAM;

  BF_Context local = *ctx;
  local.cells = calloc(1, local.num_cells);

  for (size_t i = 0; i < ctx->tokens.len; ++i) {
    int result = BF_eval_token(&i, &local, i, false);
    if (result) return result;
  }

  return 0;
}
