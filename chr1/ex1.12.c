#include <stdio.h>

#define OUT 0
#define IN 1

main() 
{
  int c, nl, nc, nt, state;
  state = OUT;
  nl = nc = nt = 0;
  while((c = getchar()) != EOF)
  {
    if (c != ' ' && c != '\t' && c != '\n')
      {
      putchar(c);
      state = IN;
      }
      else if (state)
      {
        putchar('\n');
        state = OUT;
      }
    }

    return 0;
 }
