/*
 * Exercise 6-4. Write a program that prints the distinct words in its input
 * sorted into decreasing order of frequency of occurrence. Precede each word
 * by its count.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NDISTINCT 1000

struct tnode {         /* the tree node: */
  char *word;          /* points to the text */
  int count;           /* number of occurrences */
  struct tnode *left;  /* left child */
  struct tnode *right; /* right child */
};

char buf[BUFSIZE];             /* buffer for ungetch */
int bufp = 0;                  /* next free position in buf */
struct tnode *list[NDISTINCT]; /* pointers to tree nodes */
int ntn = 0;                   /* number of tree nodes */

struct tnode *talloc(void);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
void treestore(struct tnode *);
void sortlist(void);

/* talloc: make a tnode */
struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
  int cond;
  if (p == NULL) {
    /* a new word has arrived */
    p = talloc();
    /* make a new node */
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0)
    p->count++;
  /* repeated word */
  else if (cond < 0)
    /* less than into left subtree */
    p->left = addtree(p->left, w);
  else
    /* greater than into right subtree */
    p->right = addtree(p->right, w);
  return p;
}

/* treeprint: */
void treeprint(struct tnode *p) {
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
  }
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;
  while (isspace(c = getch()))
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

/* get a (possibly pushed back) character */
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

/* push character back to input */
void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

/* treestore: store in list[] pointers to tree nodes */
void treestore(struct tnode *p) {
  if (p != NULL) {
    treestore(p->left);
    if (ntn < NDISTINCT)
      list[ntn++] = p;
    treestore(p->right);
  }
}

/* sortlist: sort list of pointers to tree nodes */
void sortlist(void) {
  int gap, i, j;
  struct tnode *temp;

  for (gap = ntn / 2; gap > 0; gap /= 2) {
    for (i = gap; i < ntn; i++) {
      for (j = i - gap; j >= 0; j -= gap) {
        if ((list[j]->count) >= (list[j + gap]->count))
          break;
        temp = list[j];
        list[j] = list[j + gap];
        list[j + gap] = temp;
      }
    }
  }
}

/* word frequency count */
int main() {
  struct tnode *root;
  char word[MAXWORD];
  int i;

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word);
  treestore(root);
  sortlist();
  for (i = 0; i < ntn; i++)
    printf("%2d:%20s\n", list[i]->count, list[i]->word);
  return 0;
}
