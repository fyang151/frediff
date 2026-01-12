#include "diff.h"
#include <stdio.h>
#include <stdlib.h>

char *A = "frad";
char *B = "fred";

int str_length(const char *str) {
  int len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

int main() {
  int *result = diff(A, B, str_length(A), str_length(B));

  int result_len = result[0];

  printf("diff_count: %i\n", result_len / 2);
  for (int i = 1; i < result_len; i += 2) {
    printf("diff_type: %i\n", result[i]);
    printf("len: %i\n", result[i + 1]);
  }

  free(result);
  return 0;
}
