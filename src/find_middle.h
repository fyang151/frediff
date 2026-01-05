typedef struct snake {
  int x;
  int y;
  int u;
  int v;
} snake;

snake find_middle(const char *a_str, int N, const char *b_str, int M);
