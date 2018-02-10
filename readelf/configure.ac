AC_PREREQ(2.60)
AC_INIT([simple-readelf],
	[1.0],
	[gault_r@epita.fr],
	[simple-readelf],
	[https://lse.epita.fr/])

AC_CONFIG_SRCDIR([src/])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([
		  foreign
		  -Wall
		  subdir-objects
])

CFLAGS=-g

AC_PROG_CC_C99
AC_PROG_CC_STDC
AC_USE_SYSTEM_EXTENSIONS

AX_COMPILER_FLAGS
AX_CODE_COVERAGE

#AM_SILENT_RULES([yes])

#AX_PTHREAD(
#	   [PTHREAD_LIBS="-lpthread"],
#	   [AC_MSG_ERROR([$PACKAGE requires pthreads])])

#PKG_CHECK_MODULES([CURL], [libcurl])
#AX_CHECK_OPENSSL()

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile])
AC_CONFIG_MACRO_DIR([m4])

AC_OUTPUT
AC_MSG_RESULT([
	$PACKAGE $VERSION
	====================

	prefix:		${prefix}
	compiler:	${CC}
	cflags:		${CFLAGS}
	ldflags:	${LDFLAGS}
])
