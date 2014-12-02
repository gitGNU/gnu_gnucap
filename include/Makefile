#$Id: Make1,v 26.138 2013/04/24 02:32:27 al Exp $ -*- Makefile -*-
# Copyright (C) 2001 Albert Davis
# Author: Albert Davis <aldavis@gnu.org>
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
TARGET =
#------------------------------------------------------------------------
INSTALL_FILES = $(RAW_SRCS) $(RAW_HDRS)
#------------------------------------------------------------------------
INSTALL_DIR = $(PREFIX)/include/gnucap
#------------------------------------------------------------------------
DELETED =
#------------------------------------------------------------------------
RAW_SRCS = \
spice-wrapper.cc
#------------------------------------------------------------------------
RAW_HDRS = \
ap.h bm.h c_comand.h constant.h d_coment.h d_dot.h d_logic.h \
d_subckt.h declare.h e_aux.h e_base.h e_card.h e_cardlist.h e_ccsrc.h \
e_compon.h e_elemnt.h e_model.h e_node.h e_storag.h e_subckt.h \
globals.h io_.h io_error.h io_trace.h l_compar.h l_denoise.h \
l_dispatcher.h l_lib.h l_stlextra.h l_timer.h m_base.h m_cpoly.h \
m_divdiff.h m_expression.h m_interp.h m_matrix.h m_phase.h m_spline.h \
m_wave.h md.h mode.h patchlev.h s__.h s_tr.h trace_off.h trace_on.h \
u_cardst.h u_function.h u_lang.h u_limit.h u_nodemap.h u_opt.h \
u_parameter.h u_prblst.h u_probe.h u_sdp.h u_sim_data.h u_status.h \
u_time_pair.h u_xprobe.h
#------------------------------------------------------------------------
RAW_OTHER = \
configure Make1
#------------------------------------------------------------------------
RAW = $(RAW_HDRS) $(RAW_SRCS) $(MODELS) $(RAW_OTHER)
#------------------------------------------------------------------------
#------------------------------------------------------------------------
IMPORTED_SRCS =
IMPORTED_HDRS =
IMPORTED_OTHER =
IMPORTED = $(IMPORTED_SRCS) $(IMPORTED_HDRS) $(IMPORTED_OTHER)
#------------------------------------------------------------------------
#------------------------------------------------------------------------
GENERATED_SRCS = ${MODELS:.model=.cc}
GENERATED_HDRS = ${MODELS:.model=.h}
GENERATED_OTHER = Make.aux
GENERATED = $(GENERATED_HDRS) $(GENERATED_SRCS) $(GENERATED_OTHER)
#------------------------------------------------------------------------
#------------------------------------------------------------------------
GENERATED_DIST = Make.depend
IMPORTED_DIST = $(IMPORTED)
DISTFILES = $(RAW) $(GENERATED_DIST) $(IMPORTED_DIST)
#------------------------------------------------------------------------
#------------------------------------------------------------------------
SRCS = $(IMPORTED_SRCS) $(GENERATED_SRCS) $(RAW_SRCS)
HDRS = $(RAW_HDRS) $(GENERATED_HDRS) $(IMPORTED_HDRS)
OBJS = ${SRCS:.cc=.o}
TARGET_DEPENDS = $(OBJS) $(RAW) $(MODELS)
#------------------------------------------------------------------------
#------------------------------------------------------------------------
MOSTLYCLEANFILES = $(OBJS) $(GENERATED)
CLEANFILES = $(MOSTLYCLEANFILES)
DISTCLEANFILES = $(CLEANFILES)
MAINTAINERCLEANFILES = $(DISTCLEANFILES)
#------------------------------------------------------------------------
#------------------------------------------------------------------------

PREFIX =  /usr

#$Id: Make3,v 26.133 2009/11/26 04:58:04 al Exp $ -*- Makefile -*-
# Copyright (C) 2001 Albert Davis
# Author: Albert Davis <aldavis@gnu.org>
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
# Part 3 of a Makefile
#------------------------------------------------------------------------
tags: $(HDRS) $(SRCS)
	etags --c++ $(HDRS) $(SRCS)
#------------------------------------------------------------------------
checkin:
	date "+#define PATCHLEVEL \"%Y.%m.%d RCS `cat rcsversion`\"" \
		>patchlev.h
	-ci -u`cat rcsversion` -m. -t/dev/null $(RAW)
	-ci -r`cat rcsversion` -m. -t/dev/null $(DELETED) $(GENERATED)
	touch patchlev.h
#------------------------------------------------------------------------
checkout:
	co $(RAW)
#------------------------------------------------------------------------
install : $(INSTALL_FILES)
	echo ==================
	mkdir -p $(INSTALL_DIR)
	cp $(INSTALL_FILES) $(INSTALL_DIR)
#------------------------------------------------------------------------
uninstall : 
	(cd $(INSTALL_DIR) ; rm $(INSTALL_FILES))
#------------------------------------------------------------------------
#unclean:
#	rm $(ALL)
#------------------------------------------------------------------------
backup:
	-mkdir BACKUP
	cp $(RAW) BACKUP
#------------------------------------------------------------------------
depend: Make.depend
Make.depend: $(SRCS) $(HDRS)
	$(CCC) -MM $(CCFLAGS) $(SRCS) > Make.depend
#-----------------------------------------------------------------------------
date:
	date "+#define PATCHLEVEL \"%Y.%m.%d RCS `cat rcsversion` +\"" \
		>patchlev.h
#-----------------------------------------------------------------------------
header-check:
	$(CCC) -o /dev/null $(RAW_HDRS)
#-----------------------------------------------------------------------------
manifest: MANIFEST
MANIFEST: $(DISTFILES)
	echo $(DISTFILES) | sed 's/ /\n/g' >MANIFEST
#-----------------------------------------------------------------------------
md5sums: MD5SUMS
MD5SUMS: $(DISTFILES)
	md5sum $(DISTFILES) | grep -v MD5SUMS >MD5SUMS
#-----------------------------------------------------------------------------
mostlyclean:
	rm -rf $(MOSTLYCLEANFILES)
	rm -f */*.o */*.obj */*.h */*.cc
clean:
	rm -rf $(CLEANFILES)
	rm -f */*.o */*.obj */*.h */*.cc
distclean:
	rm -rf $(DISTCLEANFILES)
	rm -f */*.o */*.obj */*.h */*.cc
	rm -f *~ \#*\#
maintainer-clean:
	rm -rf $(MAINTAINERCLEANFILES)
	rm -f */*.o */*.obj */*.h */*.cc
	rm -f *~ \#*\#
#-----------------------------------------------------------------------------
#-----------------------------------------------------------------------------
