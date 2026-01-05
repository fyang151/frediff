#include <stdio.h>

#include "find_middle.h"

int str_length(const char *str) {
  int len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

char *a_str_example = "a";
char *b_str_example = "a";

int main() {
  int N_example = str_length(a_str_example);
  int M_example = str_length(b_str_example);

  int N = N_example;
  int M = M_example;

  // printf("d, D, k, x, y\n");
  snake middle = find_middle(a_str_example, N, b_str_example, M);

  printf("middle snake %i, %i, %i, %i\n", middle.x, middle.y, middle.u,
         middle.v);
}
