## Process this file with automake to produce Makefile.in

MAINTAINERCLEANFILES = Makefile.in

TESTS = conversions

check_PROGRAMS = conversions
conversions_SOURCES = conversions.c   \
                      conversions.h   \
                      byte_stream.c   \
                      hex_byte.c      \
                      hex_stream.c    \
                      string_stream.c \
                      base64_stream.c \
                      xor_stream.c    \
                      $(top_builddir)/src/lib/conversions.h

conversions_CFLAGS = @CHECK_CFLAGS@
conversions_LDADD = $(top_builddir)/src/lib/libconversions.a @CHECK_LIBS@
