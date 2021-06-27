#include <stdio.h>

#define MAXLINE 1000

int getLine(char line[], int maxLine);

int getLine(char line[], int maxLine)
{
  int i, c;

  for(i = 0; i < maxLine && ((c = getchar()) != '\n') && c != EOF; ++i)
  {
    line[i] = c;
  }  
  if (c == '\n')
  {
    line[i] = '\n';
    ++i;
  }
  line[i] = '\0';

  return i;
}

int main(void)
{
  char line[MAXLINE];

  while((getLine(line, MAXLINE)) > 0)
  {
    printf("%s", line);
  }

  return 0;
}
