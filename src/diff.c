#include "ses.h"
#include <stdlib.h>

int *diff(const char *A, const char *B, int N, int M) {
  // result buffer format is [result_len, diff_type, len, diff_type, len, .....]
  int *result = malloc((N + M) * 2 * sizeof(int));
  int result_len = 0;

  ses(A, B, 0, 0, N, M, result + 1, &result_len);

  result[0] = result_len;
  return result;
}
