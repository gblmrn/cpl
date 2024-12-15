/*
 * Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit
 * operations. Compare code size and execution speed.
 */
#include <fcntl.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>

#define PERMS 0666
#define EOF (-1)
#define BUFSIZ2 1024
#define OPEN_MAX 20 /* max #files open at once */

typedef struct _iobuf {
  int cnt;    /* characters left */
  char *ptr;  /* next character position */
  char *base; /* location of buffer */
  int flag;   /* mode of file access */
  int fd;     /* file descriptor */
} FILE2;

extern FILE2 _iob[OPEN_MAX];

enum _flags {
  _READ = 01,  /* file open for reading */
  _WRITE = 02, /* file open for writing */
  _UNBUF = 04, /* file is unbuffered */
  _EOF = 010,  /* EOF has occurred on this file */
  _ERR = 020   /* error occurred on this file */
};

FILE2 _iob[OPEN_MAX] = {/* stdin, stdout, stderr */
                        {0, (char *)0, (char *)0, _READ, 0},
                        {0, (char *)0, (char *)0, _WRITE, 1},
                        {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

/* RW for owner, group, others */
FILE2 *fopen2(char *name, char *mode) {
  int fd;
  FILE2 *fp;
  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL;
  for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if ((fp->flag & (_READ | _WRITE)) == 0)
      break;
  /* found free slot */
  if (fp >= _iob + OPEN_MAX)
    /* no free slots */
    return NULL;
  if (*mode == 'w')
    fd = creat(name, PERMS);
  else if (*mode == 'a') {
    if ((fd = open(name, O_WRONLY, 0)) == -1)
      fd = creat(name, PERMS);
    lseek(fd, 0L, 2);
  } else
    fd = open(name, O_RDONLY, 0);
  if (fd == -1)
    /* couldn't access name */
    return NULL;
  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  fp->flag = (*mode == 'r') ? _READ : _WRITE;
  return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE2 *fp) {
  int bufsize;
  if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
    return EOF;
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ2;
  if (fp->base == NULL)
    /* no buffer yet */
    if ((fp->base = (char *)malloc(bufsize)) == NULL)
      return EOF;
  /* can't get buffer */
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
    if (fp->cnt == -1)
      fp->flag |= _EOF;
    else
      fp->flag |= _ERR;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char)*fp->ptr++;
}

int main() {
  FILE2 *fp;

  fp = fopen2("./ch8/ex8.2/test.data", "r");

  return 0;
}
