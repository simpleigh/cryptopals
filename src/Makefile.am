## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libconversions.la
libconversions_la_SOURCES = conversions.c conversions.h

bin_PROGRAMS = crypto1 crypto2 crypto3

crypto1_SOURCES = crypto1.c
crypto1_LDADD = libconversions.la

crypto2_SOURCES = crypto2.c
crypto2_LDADD = libconversions.la

crypto3_SOURCES = crypto3.c
crypto3_LDADD = libconversions.la
