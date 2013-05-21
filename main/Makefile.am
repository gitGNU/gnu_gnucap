## -*- Makefile -*-
##
## $Id: Makefile.am,v 26.136 2009/12/08 02:03:49 al Exp $
##
##                            COPYRIGHT
##
## This file is part of "Gnucap", the Gnu Circuit Analysis Package
##
##  Copyright (C) 2005, 2006 Dan McMahill
##
##  This program is free software; you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation; either version 3 of the License, or
##  (at your option) any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##
##  You should have received a copy of the GNU General Public License
##  along with this program; if not, write to the Free Software
##  Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA
##  02110-1301, USA.

bin_PROGRAMS = gnucap

gnucap_SOURCES = main.cc
gnucap_LDADD = -L$(top_builddir)/lib/.libs -lgnucap
gnucap_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/include -I$(top_builddir)/include

gnucap_LDFLAGS = -rpath ${pkglibdir}
