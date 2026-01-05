#include <stdio.h>
#include <stdlib.h>

// snake: a possible edit path or sequence
// D (wavefront): the farthest x for each snake after D edits
// V: the array we use to store D, value x indexed by diagonals k
// k (diagonal): well... its a diagonal

// lemmas reference the original paper, proof wont be shown here

int find_middle(const char *a_str, int N, const char *b_str, int M) {
  int MAX = N + M;
  int delta = N - M;

  int x, y, x_r, y_r;

  int *V = calloc((2 * MAX + 1), sizeof(int));
  int *V_r = malloc((2 * MAX + 1) * sizeof(int));

  for (int D = 0; D <= MAX; D++) {
    // lemma 1: snakes after D edits must end up on diagonals k in {-D, -D+2,
    // ... D-2, D}
    for (int k = -D; k <= D; k += 2) {
      int k_adj = k + MAX;

      // snake can only come from above (deletion)
      if (k == -D) {
        x = V[k_adj + 1];
        // snake can only come from left (insertion)
      } else if (k == D) {
        x = V[k_adj - 1] + 1;
        // otherwise, snake comes from previous diagonal k with higher x
      } else if (V[k_adj - 1] < V[k_adj + 1]) {
        x = V[k_adj + 1];
      } else {
        x = V[k_adj - 1] + 1;
      }

      y = x - k;

      // freely traverse down same letters, we only care about edits
      // think about it as the hungry snake eats all the same chars :)
      while (x < N && y < M && a_str[x] == b_str[y]) {
        x++;
        y++;
      }

      V[k_adj] = x;
      printf("f: %i, %i, %i, %i\n", D, k, x, y);

      if (x == N && y == M) {
        free(V);
        free(V_r);
        return D;
      }

      // first check if delta is odd because:
      // lemma 1: the optimal snake is odd or even as delta is odd or even
      // landing on a middle path in the forward snake means the optimal snake
      // has odd length vice versa for reverse snake
      if (delta % 2 == 1
          // reverse snake will have only visited diagonals k - delta in
          // [-(D-1), (D-1)] we decrement from wavefront D because reverse snake
          // is only at the previous iteration of D
          && k - delta >= -D + 1 && k - delta <= D - 1) {
        if (V_r[k_adj - delta] <= x) {
          printf("match found!\n");
          free(V);
          free(V_r);
          return 2 * D - 1;
        }
      }
    }

    // reverse snake, very similar to forward snake, but we need to adjust for
    // the reverse to forward starting diagonal with delta
    for (int k = -D; k <= D; k += 2) {
      int k_adj = k + MAX;

      if (D == 0) {
        x_r = N;
      } else if (k == -D) {
        x_r = V_r[k_adj + 1] - 1;
      } else if (k == D) {
        x_r = V_r[k_adj - 1];
      } else if (V_r[k_adj + 1] < V_r[k_adj - 1]) {
        x_r = V_r[k_adj + 1] - 1;
      } else {
        x_r = V_r[k_adj - 1];
      }

      y_r = x_r - k - delta;

      while (x_r > 0 && y_r > 0 && a_str[x_r - 1] == b_str[y_r - 1]) {
        x_r--;
        y_r--;
      }

      V_r[k_adj] = x_r;
      printf("r: %i, %i, %i, %i\n", D, k + delta, x_r, y_r);

      if (x_r == 0 && y_r == 0) {
        free(V);
        free(V_r);
        return D;
      }

      if (delta % 2 == 0 && k + delta >= -D && k + delta <= D) {
        if (V[k_adj + delta] >= x_r) {
          printf("match found!\n");
          free(V);
          free(V_r);
          return 2 * D;
        }
      }
    }
  }

  free(V);
  free(V_r);
  return -1;
}
