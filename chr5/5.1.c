/*

As written, getint treats a + or - not followed by a digit as a valid
representation of zero. Fix it to push such a character back on the input.

*/

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAX 10

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
int getint(int *pn);

int main(int argc, char** argv)
{
  int i, num[MAX];
  int val;

  for (i = 0; i < MAX && (val = getint(&num[i])) != EOF; ++i)
    printf("num[%d] = %d, \tvalue returned: %d (%s)\n", \
      i, num[i], val, val != 0 ? "number" : "not a number");

  return 0;
}

int getch(void) // get a (possibly pushed back char 
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push char back to input
{
  if (bufp > BUFSIZE) printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

int getint(int *pn)
{
  int c, sign;

  while (isspace(c = getch())) // skip white spaces
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    c = getch();
    if (!isdigit(c)) {
      ungetch(sign == 1 ? '+' : '-');
      return 0;
    }
  }
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

