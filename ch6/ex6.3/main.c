/*
 * Exercise 6-3. Write a cross-referencer that prints a list of all words in a
 * document, and for each word, a list of the line numbers on which it occurs.
 * Remove noise words like ``the,'' ``and,'' and so on.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

struct linkedlist { /* linked list of line numbers */
  int lnum;
  struct linkedlist *ptr;
};

struct tnode {              /* the tree node: */
  char *word;               /* points to the text */
  struct linkedlist *lines; /* line numbers */
  struct tnode *left;       /* left child */
  struct tnode *right;      /* right child */
};

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

struct tnode *addtreex(struct tnode *, char *, int);
void treeprintx(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
struct linkedlist *lalloc(void);
void addln(struct tnode *, int);
int noiseword(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtreex(struct tnode *p, char *w, int linenum) {
  int cond;
  if (p == NULL) { /* a new word has arrived */
    p = talloc();  /* make a new node */
    p->word = strdup(w);
    p->lines = lalloc();
    p->lines->lnum = linenum;
    p->lines->ptr = NULL;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0)
    addln(p, linenum);
  /* repeated word */
  else if (cond < 0)
    /* less than into left subtree */
    p->left = addtreex(p->left, w, linenum);
  else
    /* greater than into right subtree */
    p->right = addtreex(p->right, w, linenum);
  return p;
}

/* treeprintx: in-order print of tree p */
void treeprintx(struct tnode *p) {
  struct linkedlist *temp;
  if (p != NULL) {
    treeprintx(p->left);
    printf("%13s: ", p->word);
    for (temp = p->lines; temp != NULL; temp = temp->ptr) {
      printf("%4d ", temp->lnum);
    }
    printf("\n");
    treeprintx(p->right);
  }
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

/* getword: get next word or character from input */
int getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;
  while (isspace(c = getch()) && c != '\n')
    ;
  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for (; --lim > 0; w++)
    if (!isalnum(*w = getch())) {
      ungetch(*w);
      break;
    }
  *w = '\0';
  return word[0];
}

/* talloc: make a tnode */
struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

/* lalloc: make a linkedlist node */
struct linkedlist *lalloc(void) {
  return (struct linkedlist *)malloc(sizeof(struct linkedlist));
}

/* addln: add a line number to a linkedlist */
void addln(struct tnode *p, int linenum) {
  struct linkedlist *temp;

  temp = p->lines;
  while (temp->ptr != NULL && temp->lnum != linenum)
    temp = temp->ptr;
  if (temp->lnum != linenum) {
    temp->ptr = lalloc();
    temp->ptr->lnum = linenum;
    temp->ptr->ptr = NULL;
  }
}

/* noiseword: identify word as a noise word */
int noiseword(char *w) {
  static char *nw[] = {
      "and",
      "the",
      "this",
  };
  int cond, mid;
  int low = 0;
  int high = sizeof(nw) / sizeof(nw[0]) - 1;

  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(w, nw[mid])) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

/* word frequency count */
int main() {
  struct tnode *root;
  char word[MAXWORD];
  int linenum = 1;

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]) && noiseword(word) == -1) {
      root = addtreex(root, word, linenum);
    } else if (word[0] == '\n')
      linenum++;
  treeprintx(root);
  return 0;
}
