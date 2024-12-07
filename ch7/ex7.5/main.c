/*
 * Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf
 * and/or sscanf to do the input and number conversion.
 */
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* max depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

int getop(char s[]);
void push(double);
double pop(void);

/* getop: get next operator or numeric operand */
int getop(char s[]) {
  int i, rc;
  char c;
  static char lastc[] = " ";

  sscanf(lastc, "%c", &c);
  lastc[0] = ' '; /* clear last char */
  while ((s[0] = c) == ' ' || c == '\t')
    if (scanf("%c", &c) == EOF)
      c = EOF;
  s[1] = '\0';
  if (!isdigit(c) && c != '.') /* not a number */
    return c;
  i = 0;
  if (isdigit(c)) { /* collect integer */
    do {
      rc = scanf("%c", &c);
      if (!isdigit(s[++i] = c)) {
        break;
      }
    } while (rc != EOF);
  }
  if (c == '.') { /* collect fraction part */
    do {
      rc = scanf("%c", &c);
      if (!isdigit(s[i++] = c)) {
        break;
      }
    } while (rc != EOF);
  }
  s[i] = '\0';
  if (rc != EOF) {
    lastc[0] = c;
  }
  return NUMBER;
}

/* push: push f onto value stack */
void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

/* reverse Polish calculator */
int main(int argc, char **argv) {
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      if (op2 != 0.0)
        push(fmod(pop(), op2));
      else
        printf("error: modulo by zero\n");
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}
