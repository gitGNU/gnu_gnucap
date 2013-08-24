#$Id: Makefile.template,v 26.133 2013/08/18 04:30:00 al Exp $ -*- Makefile -*-
# Copyright (C) 2013 Rishabh Yadav
# Author: Rishabh Yadav <rishabh.ece.iitbhu@gmail.com>
#
# This file is part of "Gnucap", the Gnu Circuit Analysis Package
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.
#------------------------------------------------------------------------

CC=g++ 
CFLAGS=-shared -fPIC -o

all:c_alias_unalias.so \
        c_alter.so \
        c_aspice.so \
        c_cls.so \
	c_def_undef.so \
	c_echo.so \
	c_history.so \
	c_mdump.so \
	c_colon_comand.so \
	c_quit.so \
	c_rmcirc.so \
        c_set.so \
        c_showmod.so \
	c_shell.so \
	c_strcmp.so \
	c_sysinfo.so \
        c_version.so 
	

c_alias_unalias.so : c_alias_unalias.cc
	$(CC) $(CFLAGS) c_alias_unalias.so c_alias_unalias.cc

c_alter.so : c_alter.cc
	$(CC) $(CFLAGS) c_alter.so c_alter.cc

c_aspice.so : c_aspice.cc
	$(CC) $(CFLAGS) c_aspice.so c_aspice.cc

c_cls.so : c_cls.cc
	$(CC) $(CFLAGS) c_cls.so c_cls.cc

c_def_undef.so : c_def_undef.cc
	$(CC) $(CFLAGS) c_def_undef.so c_def_undef.cc

c_echo.so : c_echo.cc
	$(CC) $(CFLAGS) c_echo.so c_echo.cc

c_history.so : c_history.cc
	$(CC) $(CFLAGS) c_history.so c_history.cc

c_mdump.so : c_mdump.cc
	$(CC) $(CFLAGS) c_mdump.so c_mdump.cc

c_colon_comand.so : c_colon_comand.cc
	$(CC) $(CFLAGS) c_colon_comand.so c_colon_comand.cc

c_quit.so : c_quit.cc
	$(CC) $(CFLAGS) c_quit.so c_quit.cc

c_rmcirc.so : c_rmcirc.cc
	$(CC) $(CFLAGS) c_rmcirc.so c_rmcirc.cc

c_set.so : c_set.cc
	$(CC) $(CFLAGS) c_set.so c_set.cc

c_shell.so : c_shell.cc
	$(CC) $(CFLAGS) c_shell.so c_shell.cc

c_showmod.so : c_showmod.cc
	$(CC) $(CFLAGS) c_showmod.so c_showmod.cc

c_strcmp.so : c_strcmp.cc
	$(CC) $(CFLAGS) c_strcmp.so c_strcmp.cc

c_sysinfo.so : c_sysinfo.cc
	$(CC) $(CFLAGS) c_sysinfo.so c_sysinfo.cc

c_version.so : c_version.cc
	$(CC) $(CFLAGS) c_version.so c_version.cc













 
	
