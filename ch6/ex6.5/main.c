/*
 * Exercise 6-5. Write a function undef that will remove a name and definition
 * from the table maintained by lookup and install.
 */
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

struct nlist {        /* table entry: */
  struct nlist *next; /* next entry in chain */
  char *name;         /* defined name */
  char *defn;         /* replacement text */
};

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *s);

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

int main(int argc, char *argv[]) { return 0; }
