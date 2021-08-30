/* Write a loop equivalent to the for loop above without using && or || 
  for (i=0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i) */

#include <stdio.h>

#define MAXLINE 1000

int getLine(char[], int);

int getLine(char s[], int lim)
{
  int i, c, halt;
  halt = 0;

  for (i = 0; !halt; ++i)
  {
    if (i > lim - 1)
      halt = 1;
    else if ((c = getchar()) == '\n')
      halt = 1;
    else if (c == EOF)
      halt = 1;
    else
      s[i] = c;
  }
  --i;

  if (c == '\n')
    s[i++] = c;

  s[i] = '\0';

  return i;
}
    
int main(void)
{
  char line[MAXLINE];

  while(getLine(line, MAXLINE) > 0)
    printf("%s", line);

  return 0;
}
