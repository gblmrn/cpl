/*
 * Exercise 6-6. Implement a simple version of the #define processor (i.e., no
 * arguments) suitable for use with C programs, based on the routines of this
 * section. You may also find getch and ungetch helpful.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
#define MAXWORD 100
#define BUFSIZE 100

static struct nlist *hashtab[HASHSIZE]; /* pointer table */
char buf[BUFSIZE];                      /* buffer for ungetch */
int bufp = 0;                           /* next free position in buf */

struct nlist {        /* table entry: */
  struct nlist *next; /* next entry in chain */
  char *name;         /* defined name */
  char *defn;         /* replacement text */
};

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *s);
int getword(char *w, int lim);
int getch(void);
void ungetch(int c);
void ungets(char *);
void getdef(void);
void error(int, char *);
void skipblanks(void);

/* hash: form hash value for string s */
unsigned hash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
  struct nlist *np;
  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np;
  /* found */
  return NULL;
  /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;
  if ((np = lookup(name)) == NULL) { /* not found */
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else                    /* already there */
    free((void *)np->defn); /* free previous defn */
  if ((np->defn = strdup(defn)) == NULL)
    return NULL;
  return np;
}

/* undef: remove a name and definition from the table */
void undef(char *s) {
  unsigned int h;
  struct nlist *np, *prev;

  prev = NULL;
  h = hash(s); /* hash value of string s */
  for (np = hashtab[h]; np != NULL; np = np->next) {
    if (strcmp(s, np->name) == 0) {
      break;
    }
    prev = np; /* remember previous entry */
  }
  if (np != NULL) { /* found name */
    if (prev == NULL) {
      hashtab[h] = np->next;
    } else {
      prev->next = np->next;
    }
    free((void *)np->name);
    free((void *)np->defn);
    free((void *)np->next);
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

/* ungets: push string back to input */
void ungets(char *s) {
  int len = strlen(s);
  while (len > 0)
    ungetch(s[--len]);
}

/* getdef: get definition and install it */
void getdef(void) {
  char dir[MAXWORD], name[MAXWORD], def[MAXWORD];
  int i;

  skipblanks();
  if (!isalpha(getword(dir, MAXWORD))) {
    error(dir[0], "getdef: expecting a directive after #");
  } else if (strcmp(dir, "define") == 0) {
    skipblanks();
    if (!isalpha(getword(name, MAXWORD))) {
      error(name[0], "getdef: non-alpha - name expected");
    } else {
      skipblanks();
      for (i = 0; i < MAXWORD - 1; i++) {
        if ((def[i] = getch()) == EOF || def[i] == '\n') {
          break; /* end of definition */
        }
      }
      def[i] = '\0';
      if (i <= 0) { /* no definition? */
        error('\n', "getdef: incomplete define");
      } else { /* install definition */
        install(name, def);
      }
    }
  } else if (strcmp(dir, "undef") == 0) {
    skipblanks();
    if (!isalpha(getword(name, MAXWORD))) {
      error(name[0], "getdef: non-alpha in undef");
    } else {
      undef(name);
    }
  } else {
    error(dir[0], "getdef: expecting a directive after #");
  }
}

/* error: print error message and skip the rest of the line */
void error(int c, char *s) {
  printf("error: %s\n", s);
  while (c != EOF && c != '\n') {
    c = getch();
  }
}

/* skipblanks: skip blank and tab characters */
void skipblanks(void) {
  int c;
  while ((c = getch()) == ' ' || c == '\t')
    ;
  ungetch(c);
}

/* simple version of #define processor */
int main() {
  char word[MAXWORD];
  struct nlist *p;
  int i;

  while (getword(word, MAXWORD) != EOF) {
    if (strcmp(word, "#") == 0) {
      getdef();
    } else if (isalpha(word[0])) {
      printf("%s\n", word); /* cannot be defined */
    } else if ((p = lookup(word)) == NULL) {
      printf("%s\n", word); /* not defined */
    } else {
      ungets(p->defn); /* push back definition */
    }
  }
  return 0;
}
