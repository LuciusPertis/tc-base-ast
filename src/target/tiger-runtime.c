/**
   \file target/tiger-runtime.c
   \brief C Implementation of the Tiger runtime.
*/

#include <stdio.h>
#include <stdlib.h>

#define EXIT_RUNTIME_FAILURE 120

/** \name Internal functions (calls generated by the compiler only). */
/** \{ */

__attribute__((stdcall))
int *
tc_init_array(int size, int init)
{
  int i;
  int *a = (int *) malloc(size * sizeof (int));
  for (i = 0; i < size; i++)
    a[i] = init;
  return a;
}

__attribute__((stdcall))
int *
tc_malloc(int size)
{
  int i;
  int *p, *a;
  p = a = (int *) malloc(size);
  if (a == NULL)
    {
      static const char msg[] = "malloc: memory exhausted\n";
      /* -1: exclude terminating null */
      fwrite(msg, 1, sizeof (msg) - 1, stderr);
      exit(EXIT_RUNTIME_FAILURE);
    }
  /* memset could be used here */
  for (i = 0; i < size; i += sizeof (int))
    *p++ = 0;
  return a;
}
/** \} */


/** \name Miscellaneous */
/** \{ */

__attribute__((stdcall))
int
tc_not(int i)
{
  return !i;
}

__attribute__((stdcall))
void
tc_exit(int status)
{
  exit(status);
}

/** \} */


/** \name Operations on strings. */
/** \{ */

/* A string contains its length.  We use the classical final array
   trick to have a single malloc instead of two (one for the structure,
   another for the array of chars).  */

struct string
{
  int length;
  unsigned char chars[1];
};

struct string consts[256] = { 0 };
struct string empty = { 0, "" };

__attribute__((stdcall))
struct string *
tc_chr(int i)
{
  if (!(0 <= i && i <= 255))
    {
      static const char msg[] = "chr: character out of range\n";
      /* -1: exclude terminating null */
      fwrite(msg, 1, sizeof (msg) - 1, stderr);
      exit(EXIT_RUNTIME_FAILURE);
    }
  return consts + i;
}

__attribute__((stdcall))
struct string *
tc_concat(struct string *a, struct string *b)
{
  if (a->length == 0)
    return b;
  else if (b->length == 0)
    return a;
  else
    {
      int i, n = a->length + b->length;
      struct string *t = (struct string *) malloc(sizeof (int) + n);
      t->length = n;
      for (i = 0; i < a->length; i++)
        t->chars[i] = a->chars[i];
      for (i = 0; i < b->length; i++)
        t->chars[i + a->length] = b->chars[i];
      return t;
    }
}

__attribute__((stdcall))
int
tc_ord(struct string *s)
{
  if (s->length == 0)
    return -1;
  else
    return s->chars[0];
}

__attribute__((stdcall))
int
tc_size(struct string *s)
{
  return s->length;
}


/** \brief Return a part of the string \a s.
    \param s       The source string
    \param first   The first character of the extraction (starting at 0)
    \param n       The number of characters to get.

    \a first and \a n must be positive, and one shall not go beyond the size
    of \a s.  Otherwise, exit with runtime failure.
*/

__attribute__((stdcall))
struct string *
tc_substring(struct string *s, int first, int n)
{
  if (!(0 <= first
        && 0 <= n
        && first + n <= s->length))
    {
      static const char msg[] = "substring: arguments out of bounds\n";
      /* -1: exclude terminating null */
      fwrite(msg, 1, sizeof (msg) - 1, stderr);
      exit(EXIT_RUNTIME_FAILURE);
    }

  if (n == 1)
    return consts + s->chars[first];
  else
  {
    struct string *t = (struct string *) malloc(sizeof (int) + n);
    int i;
    t->length = n;
    for (i = 0; i < n; i++)
      t->chars[i] = s->chars[first + i];
    return t;
  }
}

__attribute__((stdcall))
int
tc_strcmp(struct string *lhs, struct string *rhs)
{
  int len = lhs->length < rhs->length ? lhs->length : rhs->length;
  int i;

  if (rhs == lhs)
    return 0;

  for (i = 0; i < len; i++)
    if (lhs->chars[i] < rhs->chars[i])
      return -1;
    else if (lhs->chars[i] > rhs->chars[i])
      return +1;

  /* Maybe one is prefix of the other. */
  if (lhs->length < rhs->length)
    return -1;
  else if (lhs->length > rhs->length)
    return +1;
  else
    return 0;
}

__attribute__((stdcall))
int
tc_streq(struct string *s, struct string *t)
{
  int i;
  if (s == t)
    return 1;
  if (s->length != t->length)
    return 0;
  for (i = 0; i < s->length; i++)
    if (s->chars[i] != t->chars[i])
      return 0;
  return 1;
}

/** \} */


/** \name Input/Output. */
/** \{ */

__attribute__((stdcall))
struct string *
tc_getchar()
{
  int i = getc(stdin);
  if (i == EOF)
    return &empty;
  else
    return consts + i;
}

__attribute__((stdcall))
void
tc_print(struct string *s)
{
  int i;
  unsigned char *p = s->chars;
  for (i = 0; i < s->length; i++, p++)
    putchar(*p);
}

__attribute__((stdcall))
void
tc_print_err(struct string *s)
{
  int i;
  unsigned char *p = s->chars;
  for (i = 0; i < s->length; i++, p++)
    putc(*p, stderr);
}

__attribute__((stdcall))
void
tc_print_int(int t0)
{
  if (t0 < 0)
    {
      putc('-', stdout);
      t0 *= -1;
    }

  {
    int t1 = 1;
    int t2 = t0 / 10;

    while (t2 != 0)
      {
        t1 = t1 * 10;
        t2 = t2 / 10;
      }

    while (1 <= t1)
      {
        t2 = t0 / t1;
        putc('0' + t2, stdout);
        t0 = t0 - t2 * t1;
        t1 = t1 / 10;
      }
  }
}

__attribute__((stdcall))
void
tc_flush()
{
  fflush(stdout);
}

/** \} */

int
main()
{
  int i;
  for (i = 0; i < 256; i++)
    {
      consts[i].length = 1;
      consts[i].chars[0] = i;
    }
  tc_main(0 /* static link. */ );
  return 0;
}
