/*
 * Exercise 8-3. Design and write _flushbuf, fflush, and fclose.
 */
#include <stdlib.h>
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

int _flushbuf(int, FILE2 *);
int fflush(FILE2 *);
int fclose(FILE2 *);

/* _flushbuf: allocate and flush output buffer */
int _flushbuf(int x, FILE2 *fp) {
  unsigned nc; /* number of chars to flush */
  int bufsize; /* size of buf to alloc */

  if (fp < _iob || fp >= _iob + OPEN_MAX) {
    return EOF; /* invalid pointer */
  }
  if ((fp->flag & (_WRITE | _ERR)) != _WRITE) {
    return EOF;
  }
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ2;
  if (fp->base == NULL) { /* no buffer yet */
    if ((fp->base = (char *)malloc(bufsize)) == NULL) {
      fp->flag |= _ERR;
      return EOF; /* can't get buffer */
    }
  } else { /* buffer allready exists */
    nc = fp->ptr - fp->base;
    if (write(fp->fd, fp->base, nc) != nc) {
      fp->flag |= _ERR;
      return EOF;
    }
  }
  fp->ptr = fp->base;   /* beginning of buffer */
  *fp->ptr++ = (char)x; /* save current char */
  fp->cnt = bufsize - 1;
  return x;
}

/* fflush: flush buffer associated with file fp */
int fflush(FILE2 *fp) {
  int rc = 0;
  if (fp < _iob || fp >= _iob + OPEN_MAX) {
    return EOF; /* error: invalid pointer */
  }
  if (fp->flag & _WRITE) {
    rc = _flushbuf(0, fp);
  }
  fp->ptr = fp->base;
  fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ2;
  return rc;
}

/* fclose: close file */
int fclose(FILE2 *fp) {
  int rc; /* return code */

  if ((rc = fflush(fp)) != EOF) { /* anything to flush? */
    free(fp->base);               /* free allocated buffer */
    fp->ptr = NULL;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag &= ~(_READ | _WRITE);
  }
  return rc;
}

int main() { return 0; }
