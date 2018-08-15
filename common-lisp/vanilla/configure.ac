#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Five Minute Microservice], [0.0.1], [m@ahungry.com])

AC_CONFIG_HEADERS([])
AC_CONFIG_SRCDIR([])

# Checks for programs.
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Check for custom binaries that we require for the make commands
AC_CHECK_PROG(SBCL_CHECK, sbcl, yes)
if test x"$SBCL_CHECK" != x"yes" ; then
    AC_MSG_ERROR([Please install sbcl.])
fi

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
