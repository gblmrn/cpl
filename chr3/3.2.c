/*

Write a function escape(s,t) that converts characters like newline and
tab into visible escape sequences like \n and \t as it copies the string
t to s. Use a switch. Write a function for the other direction as well,
converting escape sequences into the real characters.

*/

#include <stdio.h>

#define MAXLEN 1000

int getLine(char*, int);
void escape(char*, char*);
void enter(char*, char*); // this is the reverse function

int getLine(char str[], int maxlen)
{
  int i, c;

  for(i = 0; i < maxlen && ((c = getchar()) != '\n') && c != EOF; ++i)
    str[i] = c;
  if(c == '\n') {
    str[i] = c;
    ++i;
  }
  str[i] = '\0';

  return i;
}

void escape(char s[], char t[])
{
  int i, j;
  i = j = 0;

  while(t[i] != '\0') {
    switch (t[i]) {
      case '\t':
        s[j++] = '\\';
        s[j] = 't';
        break;
      case '\n':
        s[j++] = '\\';
        s[j] = 'n';
        break;
      default:
        s[j] = t[i];
        break;
    }
    ++i;
    ++j;
  }
  s[j] = t[i];
}

void enter(char s[], char t[])
{
  int i, j;
  i = j = 0;

  while(t[i] != '\0') {
    switch (t[i]) {
      case '\\':
        switch(t[++i]) {
          case 't':
            s[j] = '\t';
            break;
          case 'n':
            s[j] = '\n';
          default:
            s[j++] = '\\';
            s[j] = t[i];
        }
    }
    ++i;
    ++j;
  }
  s[j] = t[i];
}

int main(int argc, char *argv[])
{
  char t[MAXLEN], s[MAXLEN];

  while(getLine(t, MAXLEN) > 0) {
    escape(s,t);
    printf("%s\n", s);
    enter(s,t);
    printf("%s", t);
  }

  return 0;
}
