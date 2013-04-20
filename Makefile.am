## Process this file with automake to produce Makefile.in

# Global configuration
AM_CPPFLAGS = -I$(srcdir)/deps/bytestream/include/


# Main build
bin_PROGRAMS = crypto1 crypto2 crypto3

crypto1_SOURCES = src/crypto1.c deps/bytestream/include/bs.h
crypto1_LDADD = libbs.a

crypto2_SOURCES = src/crypto2.c deps/bytestream/include/bs.h
crypto2_LDADD = libbs.a

crypto3_SOURCES = src/crypto3.c deps/bytestream/include/bs.h src/char_distn.h src/char_distn.c
crypto3_LDADD = libbs.a


# bytestream library
noinst_LIBRARIES = libbs.a
libbs_a_SOURCES = deps/bytestream/include/bs.h     \
                  deps/bytestream/src/bs_alloc.h   \
                  deps/bytestream/src/bs_alloc.c   \
                  deps/bytestream/src/bs.c         \
                  deps/bytestream/src/bs_hex.c     \
                  deps/bytestream/src/bs_base64.c  \
                  deps/bytestream/src/bs_filter.c  \
                  deps/bytestream/src/bs_combine.c


# DIST target
EXTRA_DIST = autogen


# MAINTAINER-CLEAN target
MAINTAINERCLEANFILES = Makefile.in          \
                       aclocal.m4           \
                       build-aux/depcomp    \
                       build-aux/install-sh \
                       build-aux/missing    \
                       config.h.in          \
                       config.h.in~         \
                       configure


# WARNINGS target, compiles with strict compiler settings
warnings:
	$(MAKE) V=0 CFLAGS='-g -O -Wall -Wextra -std=c89 -pedantic -Werror'
