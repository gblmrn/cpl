/*

Rewrite appropriate programs from earlier chapters and exercises with 
pointers instead of array indexing. Good possibilities include getline,
atoi, itoa, and their variants, reverse, and strindex and getop.

*/

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100
#define BUFSIZE 100
#define NUMBER '0'

int getlinep(char*, int);
int atoip(char*);
char* itoap(int, char*);
char* reversep(char*);
int strindexp(char*, char*); 
int getopp(char*);

int main(int argc, char** argv)
{
  char s[MAXLINE], pattern[MAXLINE];
  int n;
  int type, index;

  // getlinep test
  printf("Please enter a number:\n");
  getlinep(s, MAXLINE);

  // atoip test
  n = atoip(s);
  printf("atoi: %d\n", n);

  // itoap test
  printf("string(itoa): %s\nnumber: %d\n", itoap(n,s), n);

  // rev test
  printf("rev: %s", reversep(s));
  
  //strindex
  printf("Enter a string you want to serach in:\n");
  getlinep(s, MAXLINE);
  printf("Enter pattern to search in string:\n");
  getlinep(pattern, MAXLINE);
  index = strindexp(s, pattern);
  if (index == -1)
    printf("The pattern was not found\n");
  else printf("The pattern was found starting as position: %d\n", index);
  // getopp test
  printf("Please enter a number or an operator(+, -)\n");
  while((type = getopp(s)) != EOF) {
    switch(type) {
    case NUMBER:
      printf("Found number: %s\n", s);
      break;
    case '+':
      printf("Found \'+\'\n");
      break;
    case '\n':
      printf("Found line break\n");
      break;
    default:
      printf("Found something else %s\n", s);
      break;
    }
  }

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

int strlenp(char*);
void swap(char*, char*);

char* reversep(char* s)
{
  int start = 0;
  int end = strlenp(s) - 1; // skip /n and /0
  while (start <= end)
    swap((s + start++), (s + end--));
  return s;
}

int strlenp(char* s)
{
  int count = 0;
  while(*s++ != '\0')
    count++;
  return count;
}

void swap(char* x, char* y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

// retuns index where t occurs in s else -1
int strindexp(char* s, char* t)
{
  int i, j;
  char* tb = t; // beginning address 
  char* sb = s; // same
  char* s2 = s;
  for (i = 0; *s != '\0'; ++i, ++s) {
    t = tb; 
    s2 = s;
    for (j = 0; *t != '\0' && *s2 == *t ; ++s2, ++t, ++j)
      if (*(t + 1) == '\0' && j > 0)
        return i;
  }
  return -1;
}


// string->integer
int atoip (char* s)
{
  int n, sign;
  for ( ; isspace(*s) || *s == '\t'; ++s); // skip white space
  sign = (*s == '-') ? -1 : 1;
  if (*s == '-' || *s == '+')
    s++;
  for (n = 0; isdigit(*s); ++s)
    n = n * 10 + (*s - '0');
  return sign * n;
}

// integer->string
char* itoap(int n, char* s)
{
  char* s2 = s;
  do {
    *s2++ = n % 10 + '0';
  } while ((n /= 10) > 0);
  reversep(s);
  return s;
}

int getch(void);
void ungetch(int);

int getopp(char* s) // get next operator or numeric operand
{
  int c;
  while (isspace(*s = c = getch())); // remove white spaces
  *(s+1) = '\0';
  if (!isdigit(c) && c != '.')
    return c; // not a number
  if (isdigit(c)) // colect integer part
    while (isdigit(*++s = c = getch()));
  if (c == '.') // colect fraction part
    while (isdigit(*++s = c = getch()));
  *++s = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0; // next free position in buf

int getch(void) // get a (possibly pushed back) character
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push back character to input
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
