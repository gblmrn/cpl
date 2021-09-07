/*

Write a function strrindex(s,t), which returns the 
position of the rightmost occurrence of t in s, or -1
if there is none.

 */

#include <stdio.h>

#define MAXLINE 1000
#define MAXPAT 20 // Patern string max lenght

int getLine(char*, int);
int strrindex(char*, char*);

int getLine(char s[], int maxline)
{
  int i, c;

  for (i = 0; i < maxline && ((c = getchar()) != '\n') && c != EOF; ++i)
    s[i] = c;
  if (c == '\n')
    s[i++] = '\n';
  s[i] = '\0';
      
  return i;
}

int strrindex(char s[], char t[])
{
  int i, j, k, m = -1;

  for (i = 0; s[i] != '\0'; ++i) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k)
      ;
    if (k > 0 && t[k] == '\0')
      m = i;
  }
  return m;
}

int main(int argc, char** argv)
{  
  char s[MAXLINE];
  char pattern[MAXPAT] = "ga";

  while (getLine(s, MAXLINE))
    printf("%d\n", strrindex(s, pattern));

  return 0;
}

 
  
