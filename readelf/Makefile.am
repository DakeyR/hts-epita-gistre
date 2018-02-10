EXTRA_DIST = autogen.sh
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_MAKEFLAGS = --no-print-directory

AM_CPPFLAGS = \
	      -include $(top_builddir)/config.h \
	      -I${top_srcdir}/src \
	      -I${top_srcdir}/src/xlat

AM_CFLAGS = -Wall -g -std=c99# $(PTHREAD_FLAGS) $(OPENSSL_INCLUDES) $(CURL_FLAGS)
#AM_LDFLAGS = $(WARN_LDFLAGS)

bin_PROGRAMS = simple-readelf

simple_readelf_SOURCES = \
		  src/readelf.c \
			src/xlat.c

#simple-readelf_LDADD = $(PTHREAD_LIBS) $(OPENSSL_LDFLAGS) $(OPENSSL_LIBS) $(CURL_LIBS)

#TESTS = \
#	tests/test-args \
#	test-example

#EXTRA_DIST += tests/test-args

#check_PROGRAMS = test-example

#test_example_SOURCES = tests/test-example.c
