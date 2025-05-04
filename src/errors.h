#include <stdio.h>
#include <stdlib.h>

#ifndef BF_ERRORS_H
#define BF_ERRORS_H 1

#define BF_PANIC(...) do { \
  fprintf(stderr, "BF_PANIC: %s: ", __func__); \
  fprintf(stderr, __VA_ARGS__); \
  fputc('\n', stderr); \
  exit(EXIT_FAILURE); \
} while (0)

enum BF_ErrCode
{
  // BF_ERR_NONE
  // this is only here for convenience, returning 0 is prefered
  BF_ERR_NONE = 0,

  // api errors
  BF_ERR_INVALID_PARAM,
  BF_ERR_INVALID_TOKEN,
  BF_ERR_COULD_NOT_OPEN_FILE,

  // runtime errors
  BF_ERR_BAD_CELL_IDX,
  BF_ERR_TOO_NESTED,
  BF_ERR_UNMATCHED_LOOP,

  // the number of error codes
  BF_NUM_ERROR_CODES
};

char const *BF_get_error_name(enum BF_ErrCode error);

#endif // !BF_ERRORS_H
