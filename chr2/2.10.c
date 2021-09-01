/*

Rewrite the function lower, which converts upper case letters to
lower case, with a conditional expression instead of if-else.

*/

#include <stdio.h>

#define MAXLINE 1000

void lower(char*, char*);
int getLine(char*, int);

void lower(char in[], char out[])
{
  int i;

  for(i = 0; in[i] != '\0'; ++i)
    (in[i]>='A' && in[i]<='Z') ? (out[i]=in[i]+32) : (out[i]=in[i]);
  out[i] = '\0';
}

int getLine(char line[], int maxline)
{
  int c, i;

  for(i = 0; i < maxline && (c = getchar()) != '\n' && c != EOF; ++i)
    line[i] = c;
  if(c == '\n') {
    line[i] = c;
    ++i;
  }
  line[i] = '\0';

  return i;
}

int main(int argc, char *argv[])
{
  char in[MAXLINE], out[MAXLINE];

  while(getLine(in, MAXLINE) > 0) {
    lower(in, out);
    printf("%s", out);
  }

  return 0;
}
