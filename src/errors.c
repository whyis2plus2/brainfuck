#include "errors.h"

char const *BF_get_error_name(enum BF_ErrCode error)
{
  switch (error) {
    case BF_ERR_NONE:
      return "BF_ERR_NONE";
    case BF_ERR_INVALID_PARAM:
      return "BF_ERR_INVALID_PARAM";
    case BF_ERR_INVALID_TOKEN:
      return "BF_ERR_INVALID_TOKEN";
    case BF_ERR_COULD_NOT_OPEN_FILE:
      return "BF_ERR_COULD_NOT_OPEN_FILE";
    case BF_ERR_BAD_TARGET:
      return "BF_ERR_BAD_TARGET";
    case BF_ERR_TOO_NESTED:
      return "BF_ERR_TOO_NESTED";
    case BF_ERR_BAD_CELL_IDX:
      return "BF_ERR_BAD_CELL_IDX";
    case BF_ERR_UNMATCHED_LOOP:
      return "BF_ERR_UNMATCHED_LOOP";
    
    case BF_NUM_ERROR_CODES: break;
  }

  return "<unknown error>";
}
