# From glibc

# Copyright (C) 1997, 2003, 2004, 2007, 2012, 2014 Free Software
# Foundation, Inc.
# This file is part of the GNU C Library.

# The GNU C Library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public License as
# published by the Free Software Foundation; either version 2 of the
# License, or (at your option) any later version.

# The GNU C Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.

# You should have received a copy of the GNU Library General Public
# License along with the GNU C Library; see the file COPYING.LIB.  If
# not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

ACLOCAL_AMFLAGS = -I build-aux

AUTOMAKE_OPTIONS = subdir-objects

noinst_LTLIBRARIES = libargp.la
noinst_PROGRAMS = argp-test
noinst_HEADERS = argp.h argp-fmtstream.h argp-namefrob.h # argp-comp.h

EXTRA_DIST = mempcpy.c strchrnul.c strndup.c Versions

libargp_la_SOURCES = argp-ba.c argp-eexst.c argp-fmtstream.c \
		     argp-help.c argp-parse.c argp-pv.c \
		     argp-pvh.c

libargp_la_LIBADD = $(LTLIBOBJS)

argp_test_LDADD = libargp.la

include testsuite/local.mk
