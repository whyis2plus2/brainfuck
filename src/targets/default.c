#include <stdio.h>

#include "../context.h"
#include "../errors.h"

#ifndef _WIN64
int BF_compile_context(BF_Context *ctx, const char *output_file)
{
  (void)ctx; (void)output_file;
  fprintf(stderr, "Current system not supported!\n");
  return BF_ERR_BAD_TARGET;
}
#endif
