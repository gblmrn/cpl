/*
 * Exercise 6-2. Write a program that reads a C program and prints in
 * alphabetical order each group of variable names that are identical in the
 * first 6 characters, but different somewhere thereafter. Don't count words
 * within strings and comments. Make 6 a parameter that can be set from the
 * command line.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define YES 1
#define NO 0
#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

struct tnode {         /* the tree node: */
  char *word;          /* points to the text */
  int match;           /* match found */
  struct tnode *left;  /* left child */
  struct tnode *right; /* right child */
};

int getword(char *word, int lim);
int comment(void);
struct tnode *addtreex(struct tnode *p, char *w, int num, int *found);
struct tnode *talloc2(void);
void treexprint(struct tnode *p);
int compare(char *s, struct tnode *p, int num, int *found);
int getch(void);
void ungetch(int);

/* getword: get next word or character from input */
int getword(char *word, int lim) {
  int c, d, getch(void);
  void ungetch(int);
  char *w = word;

  while (isspace(c = getch()))
    ;
  if (c != EOF)
    *w++ = c;
  if (isalpha(c) || c == '_' || c == '#') {
    for (; --lim > 0; w++) {
      if (!isalnum(*w = getch()) && *w != '_') {
        ungetch(*w);
        break;
      }
    }
  } else if (c == '\'' && c == '"') {
    for (; --lim > 0; w++) {
      if ((*w = getch()) == '\\') {
        *++w = getch();
      } else if (*w == c) {
        w++;
        break;
      } else if (*w == EOF) {
        break;
      } else if (c == '/') {
        if ((d = getch()) == '*') {
          c = comment();
        } else {
          ungetch(d);
        }
      }
    }
  }
  *w = '\0';
  return c;
}

/* comment: skip over commnet and return a character */
int comment() {
  int c;
  while ((c = getch()) != EOF) {
    if (c == '*') {
      if ((c = getch()) == '/') {
        break;
      } else {
        ungetch(c);
      }
    }
  }
  return c;
}

/* talloc2: make a tnode */
struct tnode *talloc2(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

/* addtreex: add a node with w, at or below p */
struct tnode *addtreex(struct tnode *p, char *w, int num, int *found) {
  int cond;
  if (p == NULL) {
    /* a new word has arrived */
    p = talloc2();
    /* make a new node */
    p->word = strdup(w);
    p->match = *found;
    p->left = p->right = NULL;
  } else if ((cond = compare(w, p, num, found)) < 0)
    p->left = addtreex(p->left, w, num, found);
  else if (cond > 0)
    p->right = addtreex(p->right, w, num, found);
  return p;
}

/* treeprint: in-order print of tree p if p->match == YES */
void treexprint(struct tnode *p) {
  if (p != NULL) {
    treexprint(p->left);
    if (p->match == YES)
      printf("%s\n", p->word);
    treexprint(p->right);
  }
}

/* compare: compare words and update p->match */
int compare(char *s, struct tnode *p, int num, int *found) {
  int i;
  char *t = p->word;
  for (i = 0; *s == *t; i++, s++, t++) {
    if (*s == '\0') {
      return 0;
    }
  }
  if (i >= num) {
    *found = YES;
    p->match = YES;
  }
  return *s - *t;
}

/* get a (possibly pushed back) character */
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

/* push character back to input */
void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

/* word frequency count */
int main(int argc, char *argv[]) {
  struct tnode *root;
  char word[MAXWORD];
  int found = NO; /* YES is match was found */
  int num;

  num = (--argc && (*++argv)[0] == '-') ? atoi(argv[1]) : 6;
  root = NULL;
  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0]) && strlen(word) >= num) {
      root = addtreex(root, word, num, &found);
    }
    found = NO;
  }
  treexprint(root);
  return 0;
}
