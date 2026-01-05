#include <stdio.h>
#include <stdlib.h>

#include "find_middle.h"

// snake: a possible edit path or sequence
// D (wavefront): the farthest x for each snake after D edits
// V: the array we use to store D, value x indexed by diagonals k
// k (diagonal): well... its a diagonal

// lemmas reference the original paper, proof wont be shown here

snake find_middle(const char *a_str, int N, const char *b_str, int M) {
  int MAX = N + M;
  int delta = N - M;

  int x, y, x_r, y_r;

  int *V = malloc((2 * MAX + 1) * sizeof(int));
  int *V_r = malloc((2 * MAX + 1) * sizeof(int));

  snake snake = {-1, -1, -1, -1};

  for (int D = 0; D <= MAX; D++) {
    // lemma 1: snakes after D edits must end up on diagonals k in {-D, -D+2,
    // ... D-2, D}
    for (int k = -D; k <= D; k += 2) {
      int k_adj = k + MAX;

      // initial case
      if (D == 0) {
        x = 0;

        snake.x = x;
        snake.y = 0;
        // snake can only come from above (deletion)
      } else if (k == -D) {
        x = V[k_adj + 1];

        snake.x = x;
        snake.y = x - k - 1;
        // snake can only come from left (insertion)
      } else if (k == D) {
        x = V[k_adj - 1] + 1;

        snake.x = x - 1;
        snake.y = x - k;
        // otherwise, snake comes from previous diagonal k with higher x
      } else if (V[k_adj - 1] < V[k_adj + 1]) {
        // snake comes from above (deletion)
        x = V[k_adj + 1];

        snake.x = x;
        snake.y = x - k - 1;
      } else {
        // snake comes from left (insertion)
        x = V[k_adj - 1] + 1;

        snake.x = x - 1;
        snake.y = x - k;
      }

      y = x - k;

      // freely traverse down same letters, we only care about edits
      // think about it as the hungry snake eats all the same chars :)
      while (x < N && y < M && a_str[x] == b_str[y]) {
        x++;
        y++;
      }

      V[k_adj] = x;
      // printf("f: %i, %i, %i, %i\n", D, k, x, y);
      printf("F, x: %i, y: %i, u: %i, v: %i\n", snake.x, snake.y, x, y);

      if (x == N && y == M) {
        free(V);
        free(V_r);

        snake.u = x;
        snake.v = y;

        return snake;
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

          snake.u = x;
          snake.v = y;

          return snake;
        }
      }
    }

    // reverse snake, very similar to forward snake, but we need to adjust for
    // the reverse to forward starting diagonal with delta
    for (int k = -D; k <= D; k += 2) {
      int k_adj = k + MAX;

      // initial case
      if (D == 0) {
        x_r = N;

        snake.u = x_r;
        snake.v = N;
        // snake must come from right (insertion)
      } else if (k == -D) {
        x_r = V_r[k_adj + 1] - 1;

        snake.u = x_r + 1;
        snake.v = x_r - k - delta;
        // snake must come from below (deletion)
      } else if (k == D) {
        x_r = V_r[k_adj - 1];

        snake.u = x_r;
        snake.v = x_r - k - delta + 1;
        // otherwise, snake comes from previous diagonal k with lower x
      } else if (V_r[k_adj + 1] < V_r[k_adj - 1]) {
        // snake comes from right (insertion)
        x_r = V_r[k_adj + 1] - 1;

        snake.u = x_r + 1;
        snake.v = x_r - k - delta;
      } else {
        // snake come from below (deletion)
        x_r = V_r[k_adj - 1];

        snake.u = x_r;
        snake.v = x_r - k - delta + 1;
      }

      y_r = x_r - k - delta;

      while (x_r > 0 && y_r > 0 && a_str[x_r - 1] == b_str[y_r - 1]) {
        x_r--;
        y_r--;
      }

      V_r[k_adj] = x_r;
      // printf("r: %i, %i, %i, %i\n", D, k + delta, x_r, y_r);
      printf("R, x: %i, y: %i, u: %i, v: %i\n", x_r, y_r, snake.u, snake.v);

      if (x_r == 0 && y_r == 0) {
        free(V);
        free(V_r);

        snake.x = x_r;
        snake.y = y_r;
        return snake;
      }

      if (delta % 2 == 0 && k + delta >= -D && k + delta <= D) {
        if (V[k_adj + delta] >= x_r) {
          printf("match found!\n");
          free(V);
          free(V_r);

          snake.x = x_r;
          snake.y = y_r;
          return snake;
        }
      }
    }
  }

  free(V);
  free(V_r);
  return snake;
}
