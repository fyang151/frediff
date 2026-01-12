#include "find_middle.h"

void ses(const char *A, const char *B, int N_start, int M_start, int N, int M,
         int *result, int *result_i) {
  if (M == 0 && N == 0) {
    return;
  }

  if (M_start == M) {
    result[(*result_i)++] = -1;
    result[(*result_i)++] = N - N_start;
    return;
  }

  if (N_start == N) {
    result[(*result_i)++] = 1;
    result[(*result_i)++] = M - M_start;
    return;
  }

  snake middle = find_middle(A, B, N_start, M_start, N, M);

  if (middle.x == -1) {
    result[(*result_i)++] = -1;
    result[(*result_i)++] = N - N_start;

    result[(*result_i)++] = 1;
    result[(*result_i)++] = M - M_start;
    return;
  }

  ses(A, B, N_start, M_start, middle.x, middle.y, result, result_i);

  result[(*result_i)++] = 0;
  result[(*result_i)++] = middle.u - middle.x;

  if (!(middle.u == N && middle.v == M)) {
    ses(A, B, middle.u, middle.v, N, M, result, result_i);
  }
}
