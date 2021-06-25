#include <stdio.h>

main() {
  int c, nl;

  nl = 0;
  while ((c = getchar()) != EOF)
    if (c == '\n')
      ++nl;
    printf("The number of lines currently is %d\n", nl);
}
