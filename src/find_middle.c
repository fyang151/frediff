#include <stdlib.h>

#include "find_middle.h"

// D (wavefront): the farthest x for each path after D edits
// V: the array we use to store D, value x indexed by diagonals k
// k (diagonal): well... its a diagonal
// snake: a sequence of identical chars

// lemmas reference the original paper, proof wont be shown here

struct snake find_middle(const char *a_str, int N, const char *b_str, int M) {
  int MAX = N + M;
  int delta = N - M;

  // u, v are x, y in reverse direction
  int x, y, u, v;
  snake snake = {-1, -1, -1, -1};

  int *V = malloc((2 * MAX + 1) * sizeof(int));
  int *V_r = malloc((2 * MAX + 1) * sizeof(int));

  for (int D = 0; D <= MAX; D++) {
    // lemma 1: paths after D edits must end up on diagonals k in {-D, -D+2,
    // ... D-2, D}
    for (int k = -D; k <= D; k += 2) {
      int k_adj = k + MAX;

      // initial case
      if (D == 0) {
        x = 0;
        // path can only come from above (deletion)
      } else if (k == -D) {
        x = V[k_adj + 1];
        // path can only come from left (insertion)
      } else if (k == D) {
        x = V[k_adj - 1] + 1;
        // otherwise, path comes from previous diagonal k with higher x
      } else if (V[k_adj - 1] < V[k_adj + 1]) {
        // path comes from above (deletion)
        x = V[k_adj + 1];
      } else {
        // path comes from left (insertion)
        x = V[k_adj - 1] + 1;
      }

      y = x - k;

      int start_x = x;
      int start_y = y;

      // freely traverse down same letters (snake), we only care about edits
      // think about it as the hungry snake eats all the same chars :)
      while (x < N && y < M && a_str[x] == b_str[y]) {
        snake.x = start_x;
        snake.y = start_y;

        x++;
        y++;

        snake.u = x;
        snake.v = y;
      }

      V[k_adj] = x;

      // first check if delta is odd because:
      // lemma 1: the optimal path is odd or even as delta is odd or even
      // landing on a middle path in the forward path means the optimal path
      // has odd length vice versa for reverse path
      if (delta % 2 == 1
          // reverse path will have only visited diagonals k - delta in
          // [-(D-1), (D-1)] we decrement from wavefront D because reverse path
          // is only at the previous iteration of D
          && k - delta >= -D + 1 && k - delta <= D - 1) {
        if (V_r[k_adj - delta] <= x) {
          free(V);
          free(V_r);

          return snake;
        }
      }

      if (x == N && y == M) {
        free(V);
        free(V_r);

        return snake;
      }
    }

    // reverse path, very similar to forward path, but we need to adjust for
    // the reverse to forward starting diagonal with delta
    for (int k = -D; k <= D; k += 2) {
      int k_adj = k + MAX;

      // initial case
      if (D == 0) {
        u = N;
        // path must come from right (insertion)
      } else if (k == -D) {
        u = V_r[k_adj + 1] - 1;
        // path must come from below (deletion)
      } else if (k == D) {
        u = V_r[k_adj - 1];
        // otherwise, path comes from previous diagonal k with lower x
      } else if (V_r[k_adj + 1] < V_r[k_adj - 1]) {
        // path comes from right (insertion)
        u = V_r[k_adj + 1] - 1;
      } else {
        // path come from below (deletion)
        u = V_r[k_adj - 1];
      }

      v = u - k - delta;

      int start_x = u;
      int start_y = v;

      while (u > 0 && v > 0 && a_str[u - 1] == b_str[v - 1]) {
        snake.u = start_x;
        snake.v = start_y;

        u--;
        v--;

        snake.x = u;
        snake.y = v;
      }

      V_r[k_adj] = u;

      if (delta % 2 == 0 && k + delta >= -D && k + delta <= D) {
        if (V[k_adj + delta] >= u) {
          free(V);
          free(V_r);

          return snake;
        }
      }

      if (u == 0 && v == 0) {
        free(V);
        free(V_r);

        return snake;
      }
    }
  }

  free(V);
  free(V_r);
  return snake;
}
