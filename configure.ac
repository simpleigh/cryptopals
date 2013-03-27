# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([Crypto], [0.1])
LT_INIT

AC_CONFIG_SRCDIR([src/conversions.c])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs.
: ${CFLAGS="-Wall -Wextra -std=c89 -pedantic"}
AC_PROG_CC([cc gcc])

# Checks for libraries.

# This macro is defined in check.m4 and tests if check.h and
# libcheck.a are installed in your system. It sets CHECK_CFLAGS and
# CHECK_LIBS accordingly.
#  AM_PATH_CHECK([MINIMUM-VERSION,
#                [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
#AM_PATH_CHECK()

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stddef.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

# Output files
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])

AC_OUTPUT
