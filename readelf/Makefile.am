EXTRA_DIST = autogen.sh
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_MAKEFLAGS = --no-print-directory

AM_CPPFLAGS = \
	      -include $(top_builddir)/config.h \
	      -I${top_srcdir}/src \
	      -I${top_srcdir}/src/xlat

AM_CFLAGS = -Wall -g -std=c99 $(CODE_COVERAGE_CFLAGS) #$(OPENSSL_INCLUDES) $(CURL_FLAGS)
#AM_LDFLAGS = $(WARN_LDFLAGS)

EXTRA_DIST+=${top_srcdir}/src/xlat/gen.sh \
							${top_srcdir}/src/xlat/e_type.in \
							${top_srcdir}/src/xlat/e_version.in \
							${top_srcdir}/src/xlat/e_machine.in \
							${top_srcdir}/src/xlat/sh_type.in \
							${top_srcdir}/src/xlat/st_shndx.in \
							${top_srcdir}/src/xlat/p_type.in \
							${top_srcdir}/src/xlat/type.in \
							${top_srcdir}/src/xlat/bind.in \
							${top_srcdir}/src/xlat/visibility.in

#gen_headers_xlat:
#	cd ${top_srcdir}/src/xlat && ./gen.sh

bin_PROGRAMS = simple-readelf

simple_readelf_SOURCES = \
		  src/readelf.c \
		  src/readelf.h \
			src/xlat.c \
			src/xlat.h

#simple-readelf_LDADD = $(PTHREAD_LIBS) $(OPENSSL_LDFLAGS) $(OPENSSL_LIBS) $(CURL_LIBS)

#TESTS = \
#	tests/test-args \
#	test-example

#check_PROGRAMS = test-example

#test_example_SOURCES = tests/test-example.c
