/**
   \file llvm/tiger-runtime.c
   \brief C Implementation of the Tiger runtime.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_RUNTIME_FAILURE 120

// FWD, declared by tc
void tc_main(int);

/** \name Internal functions (calls generated by the compiler only). */
/** \{ */

/** \brief Allocate an array and fill it with a default value.
    \param size    The size of the array.
    \param elt     The default element.

    An element size is always the size of a word on 32-bit systems.
*/
int *tc_init_array(int size, int elt)
{
  int *arr = (int *)malloc(size * sizeof (elt));
  for (size_t i = 0; i < size; ++i)
    arr[i] = elt;
  return arr;
}
/** \} */

/** \name Miscellaneous */
/** \{ */

/** \brief Equivalent to operator! in C.
    \param i       The integer to be inversed.
*/
int tc_not(int i)
{
  return !i;
}

/** \brief Exit the program with the desired status.
    \param status  The status code.
*/
void tc_exit(int status)
{
  exit(status);
}
/** \} */

/** \name Operations on strings. */
/** \{ */

// Small trick. Add a \0 after each char in the consts
// This is filled in tc_main
static char consts[512] = { 0 };

/** \brief Get a string containing the character represented by the ascii value
 *         of \a i.
    \param i  The ascii value of the desired character.
*/
const char *tc_chr(int i)
{
  if (!(0 <= i && i <= 255))
  {
    fputs("chr: character out of range\n", stderr);
    exit(EXIT_RUNTIME_FAILURE);
  }
  return consts + i * 2;
}

/** \brief Concatenate two strings.
    \param a  The first string.
    \param b  The second string.
*/
const char *tc_concat(const char *a, const char *b)
{
  size_t len_a = strlen(a);
  size_t len_b = strlen(b);
  if (len_a == 0)
    return b;
  else if (len_b == 0)
    return a;
  else
  {
    int i = 0;
    int n = len_a + len_b;
    char *t = (char *) malloc(n + 1);
    for (i = 0; i < len_a; i++)
      t[i] = a[i];
    for (i = 0; i < len_b; i++)
      t[i + len_a] = b[i];
    t[n] = '\0';
    return t;
  }
}

/** \brief Get the ascii value of a character.
    \param s  The string representing the desired character to be converted.

    Inverse of `tc_chr`.
*/
int tc_ord(const char *s)
{
  size_t len = strlen(s);
  if (len == 0)
    return -1;
  else
    return s[0];
}

/** \brief Get the size of a string.
    \param s  The string.
*/
int tc_size(const char *s)
{
  return strlen(s);
}

/** \brief Return a part of the string \a s.
    \param s       The source string
    \param first   The first character of the extraction (starting at 0)
    \param n       The number of characters to get.

    \a first and \a n must be positive, and one shall not go beyond the size
    of \a s.  Otherwise, exit with runtime failure.
*/
const char *tc_substring(const char *s, int first, int n)
{
  size_t len = strlen(s);
  if (!(0 <= first
        && 0 <= n
        && first + n <= len))
  {
    fputs("substring: arguments out of bounds\n", stderr);
    exit(EXIT_RUNTIME_FAILURE);
  }

  if (n == 1)
    return consts + s[first] * 2;
  else
  {
    char *t = (char *) malloc(n + 1);
    for (int i = 0; i < n; i++)
      t[i] = s[first + i];
    t[n] = '\0';
    return t;
  }
}

/** \brief Compare two strings.
    \param lhs       The first string.
    \param rhs       The second string.
*/
int tc_strcmp(const char *lhs, const char *rhs)
{
  return strcmp(lhs, rhs);
}

/** \brief Return a part of the string \a s.
    \param s       The source string
    \param first   The first character of the extraction (starting at 0)
    \param n       The number of characters to get.

    \a first and \a n must be positive, and one shall not go beyond the size
    of \a s.  Otherwise, exit with runtime failure.
*/
int tc_streq(const char *lhs, const char *rhs)
{
  return strcmp(lhs, rhs) == 0;
}
/** \} */

/** \name Input/Output. */
/** \{ */

/** \brief Get a character from the standard input.
*/
const char *tc_getchar()
{
  int i = getc(stdin);
  if (i == EOF)
    return "";
  else
    return consts + i * 2;
}

/** \brief Print a string on the standard output.
    \param s   The string to be printed.
*/
void tc_print(const char *s)
{
  printf("%s", s);
}

/** \brief Print a string on the standard error.
    \param s   The string to be printed.
*/
void tc_print_err(const char *s)
{
  fprintf(stderr, "%s", s);
}

/** \brief Print an int on the standard error.
    \param i   The int to be printed.
*/
void tc_print_int(int i)
{
  printf("%d", i);
}

/** \brief Flush the standard output.
*/
void tc_flush()
{
  fflush(stdout);
}

/** \} */

int main()
{
  // Fill the `consts` array with every character in the ascii table, followed
  // by a null character.
  for (int i = 0; i < 512; i += 2)
  {
    consts[i] = i / 2;
    consts[i + 1] = 0;
  }

  tc_main(0);
  return 0;
}
