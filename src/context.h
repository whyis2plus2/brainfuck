#include <stdbool.h>
#include <stdint.h>

#include "tokens.h"

#ifndef BF_CONTEXT_H
#define BF_CONTEXT_H 1

#define BF_LIST_START_CAPACITY 256u
typedef struct {
  size_t len, cap;
  enum BF_Token *data;
} BF_TokenList;

#define BF_INTERPRETER_NESTING_LIMIT 50u
typedef struct {
  size_t len, cap;
  size_t *indicies;
} BF_JumpList;

typedef struct {
  size_t num_cells;
  size_t current_index;
  const char *filename;
  uint8_t *cells;
  BF_TokenList tokens;
  BF_JumpList  loops;
} BF_Context;

int BF_token_list_push(BF_TokenList *tl, enum BF_Token token);
int BF_jump_list_push(BF_JumpList *jl, size_t idx);

int BF_create_context(BF_Context *out_ctx, const char *filename, size_t num_cells, bool alloc_cells);
int BF_destroy_context(BF_Context *ctx);
int BF_eval_token(size_t *out_idx, BF_Context *ctx, size_t idx);
int BF_run_context(BF_Context *ctx);

// generate an assembly file from a context
// this file can be assembled and linked into an executable
int BF_compile_context(BF_Context *ctx, const char *output_file);

#endif // !BF_CONTEXT_H
