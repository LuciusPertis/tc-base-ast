dnl LSH_GCC_ATTRIBUTES
dnl Check for gcc's __attribute__ construction
AC_DEFUN([LSH_GCC_ATTRIBUTES],
[AC_CACHE_CHECK([for __attribute__], [lsh_cv_c_attribute],
  [AC_COMPILE_IFELSE([AC_LANG_SOURCE([[
#include <stdlib.h>
static void foo(void) __attribute__ ((noreturn));

static void __attribute__ ((noreturn))
foo(void)
{
  exit(1);
}
]])], [lsh_cv_c_attribute=yes], [lsh_cv_c_attribute=no])
])

AH_TEMPLATE([HAVE_GCC_ATTRIBUTE],
            [Define if the compiler understands __attribute__])
if test "x$lsh_cv_c_attribute" = xyes; then
  AC_DEFINE([HAVE_GCC_ATTRIBUTE])
fi

AH_BOTTOM([
#if __GNUC__ && HAVE_GCC_ATTRIBUTE
# define NORETURN __attribute__ ((__noreturn__))
# define PRINTF_STYLE(f, a) __attribute__ ((__format__ (__printf__, f, a)))
# define UNUSED __attribute__ ((__unused__))
#else
# define NORETURN
# define PRINTF_STYLE(f, a)
# define UNUSED
#endif
])
])dnl LSH_GCC_ATTRIBUTES
