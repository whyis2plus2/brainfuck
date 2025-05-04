#include <assert.h>
#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "context.h"
#include "errors.h"

int main(int argc, char **argv)
{
  BF_Context ctx = {0};

  if (argc < 2 || argc > 3) {
    printf("Usage: brainfuck <input file> [output file]\n");
    printf("passing only the input file will trigger the interpreter\n");
    printf("passing in a parameter for the output file will compile the input file\n");
    return 1;
  } else {
    int err = BF_create_context(&ctx, argv[1], 256, (argc == 2));
    if (err) {
      fprintf(stderr, "Failed to create context: %s\n", BF_get_error_name(err));
      return EXIT_FAILURE;
    }

    FILE *file = fopen(ctx.filename, "r");
    if (!file) {
      perror("Failed to read input file");
      return EXIT_FAILURE;
    }

    while (true) {
      enum BF_Token token = BF_normalize_token(fgetc(file));

      if (feof(file)) break;
      if (token != BF_TOK_NONE) BF_token_list_push(&ctx.tokens, token);
    }

    fclose(file);
  }

  int compile_err = 0;
  if (argc == 3) compile_err = BF_compile_context(&ctx, argv[2]);
  else BF_run_context(&ctx);

  if (compile_err) {
    printf("Compiler error: %s\n", BF_get_error_name(compile_err));
    if (compile_err == BF_ERR_COULD_NOT_OPEN_FILE) perror("Could not open output file");

    return 1;
  }

  BF_destroy_context(&ctx);

  return 0;
}
