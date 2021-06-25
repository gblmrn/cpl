/* Blanks, tabs and newlines counter*/

#include <stdio.h>

int main() {
 int c, nb = 0, nt = 0, nl = 0;

 while((c = getchar()) != EOF) {
  if (c == ' ')
    ++nb;
  if (c == '\t')
    ++nt;
  if (c == '\n')
    ++nl;
  }
  printf("Blanks:%d Tabs:%d Lines:%d\n", nb, nt, nl);
}
