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
    fprintf(stderr, "Usage: brainfuck <input file> [output file]\n");
    fprintf(stderr, "passing only the input file will trigger the interpreter\n");
    fprintf(stderr, "passing in a parameter for the output file will compile the input file\n");
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

    static char buffer[1000] = {0};

    while (true) {
      if (feof(file)) break;
      fgets(buffer, sizeof(buffer), file);

      for (size_t i = 0; i < sizeof(buffer); ++i) {
        if (!buffer[i]) break;

        BF_Token tok = {0};
        BF_tokenize(&tok, &i, buffer, i);

        if (tok.type != BF_TOK_NONE) BF_token_list_push(&ctx.tokens, tok);
      }
    }

    fclose(file);
  }

  int result = (argc == 3)? BF_compile_context(&ctx, argv[2]) : BF_run_context(&ctx);

  if (result) {
    fprintf(stderr, "Error: %s\n", BF_get_error_name(result));
    if (result == BF_ERR_COULD_NOT_OPEN_FILE) perror("Could not open output file");

    return EXIT_FAILURE;
  }

  BF_destroy_context(&ctx);

  return 0;
}
