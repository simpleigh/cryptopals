## Process this file with automake to produce Makefile.in

MAINTAINERCLEANFILES = Makefile.in          \
                       aclocal.m4           \
                       build-aux/depcomp    \
                       build-aux/install-sh \
                       build-aux/missing    \
                       config.h.in          \
                       config.h.in~         \
                       configure

EXTRA_DIST = autogen

SUBDIRS = src . tests

WARNINGS = -g -O -Wall -Wextra -std=c89 -pedantic -Werror

warnings:
	$(MAKE) V=0 CFLAGS='$(WARNINGS)'
	$(MAKE) V=0 CFLAGS='$(WRANINGS)' $(check_PROGRAMS)
