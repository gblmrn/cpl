/*

Rewrite appropriate programs from earlier chapters and exercises with 
pointers instead of array indexing. Good possibilities include getline,
atoi, itoa, and their variants, reverse, and strindex and getop.

*/

#include <stdio.h>

#define MAXLINE 100

int getlinep(char* s, int len);
int atoip(char* s);
char* itoap(int n);
char* reversep(char* s);
int strindexp(char* s);

int main(int argc, char** argv)
{
  char s[MAXLINE];
  while(getlinep(s, MAXLINE))
    printf("%s", s);

  return 0;
}

int getlinep(char* s, int len)
{
  int i;
  char c;
  for (i = 0; i < len && ((c = getchar()) != '\n') && c != '\0'; ++i)
    *(s + i) = c;
  if (c == '\n')
    *(s + i++) = c;
  *(s + i) = '\0';
  return i;
}
