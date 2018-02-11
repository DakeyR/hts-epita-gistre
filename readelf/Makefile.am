@CODE_COVERAGE_RULES@
EXTRA_DIST = autogen.sh
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_MAKEFLAGS = --no-print-directory

AM_CPPFLAGS = \
	      -include $(top_builddir)/config.h \
	      -I${top_srcdir}/src \
	      -I${top_srcdir}/src/xlat

AM_CFLAGS = -Wall -g -std=c99 $(CODE_COVERAGE_CFLAGS) #$(OPENSSL_INCLUDES) $(CURL_FLAGS)

BUILT_SOURCES= \
							 ${top_srcdir}/src/xlat/e_type.h \
							 ${top_srcdir}/src/xlat/e_version.h \
							 ${top_srcdir}/src/xlat/e_machine.h \
							 ${top_srcdir}/src/xlat/sh_type.h \
							 ${top_srcdir}/src/xlat/st_shndx.h \
							 ${top_srcdir}/src/xlat/p_type.h \
							 ${top_srcdir}/src/xlat/type.h \
							 ${top_srcdir}/src/xlat/bind.h \
							 ${top_srcdir}/src/xlat/visibility.h


EXTRA_DIST+= \
							${top_srcdir}/tests/example.c \
							${top_srcdir}/tests/printf-test.c \
							${top_srcdir}/tests/simple.sh \
							${top_srcdir}/tests/simple2.sh \
							${top_srcdir}/tests/ls.sh \
							${top_srcdir}/tests/cat.sh \
							${top_srcdir}/src/xlat/gen.sh

EXTRA_DIST+= ${BUILT_SOURCES:.h=.in}
$(BUILT_SOURCES):
	${top_srcdir}/xlat/gen.sh ${@:.h=.in} $@

bin_PROGRAMS = simple-readelf

simple_readelf_SOURCES = \
		  src/readelf.c \
		  src/readelf.h \
			src/xlat.c \
			src/xlat.h \
			${BUILT_SOURCES}

TESTS = \
				tests/simple.sh \
				tests/simple2.sh \
				tests/ls.sh \
				tests/cat.sh

check_PROGRAMS = tests/example tests/printf-test

test_example_SOURCES = tests/example.c
test_printf_test_SOURCES = tests/printf-test.c
