/*

Write a program to remove all comments from a C program. Don't forget to
handle quoted strings and character constants properly. C commenents do not
nest.

*/

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define IN 1
#define OUT 0
#define MAXLEN 1000

int getLine(char *, int);
int isComment(char, char);
void comDel(char *, char *);

int getLine(char line[], int maxlen)
{
  int i, c;

  for (i = 0; i < maxlen && ((c = getchar()) != EOF) && c != '\n'; ++i)
    line[i] = c;
  if (c == '\n') {
    line[i] = c;
    ++i;
  }
  line[i] = '\0';

  return i;
}

int isComment(char first, char second)
{
  if (first == '/' && second == '/')
    return TRUE;
  else
    return FALSE;
}

void comDel(char in[], char out[])
{
  int i, j;
  char state; // IN comment OUT of comment

  state = OUT;
  for (i = j = 0; in[i] != '\0'; ++i) {
    if (isComment(in[i], in[i+1])) 
      state = IN;
    if (state == IN)
      continue;
    else 
      out[j++] = in[i];
      state = OUT;
  }
  out[j++] = '\n';
  out[j] = '\0';
}

int main(int argc, char *argv[])
{
  char in[MAXLEN], out[MAXLEN];

  while ((getLine(in, MAXLEN)) > 0) {
    comDel(in, out);
    printf("%s", out);
  }

  return 0;
}
