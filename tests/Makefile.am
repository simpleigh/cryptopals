## Process this file with automake to produce Makefile.in

TESTS = conversions_byte_stream

check_PROGRAMS = conversions_byte_stream
conversions_byte_stream_SOURCES = conversions_byte_stream.c $(top_builddir)/src/lib/conversions.h
conversions_byte_stream_CFLAGS = @CHECK_CFLAGS@
conversions_byte_stream_LDADD = $(top_builddir)/src/lib/libconversions.a @CHECK_LIBS@
