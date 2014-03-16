/*$Id: c_sysinfo.cc,v 26.133 2013/06/28 06:00:04 al Exp $ -*- C++ -*-
 * Copyright (C) 2013 Rishabh Yadav
 * Author: Rishabh Yadav <rishabh.ece.iitbhu@gmail.com>
 *
 * This file is part of "Gnucap", the Gnu Circuit Analysis Package
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *------------------------------------------------------------------
 * This command prints the System Information which may help users to send bug report to the gnucap developers community.
 * Note:This command doesn't works on Windows.
 */
//testing = script 2013.09.10
#include <gnucap/c_comand.h>
#include <gnucap/globals.h>
/*--------------------------------------------------------------------------*/
namespace {
/*--------------------------------------------------------------------------*/

class CMD_SYSINFO : public CMD {
public:
  void do_it(CS&, CARD_LIST*){
    //Take information from the shell and format the output
    std::system("cat /proc/cpuinfo  |  grep 'model name'  |  sed 's/m/M/' ");
    std::system("cat /etc/*release*  |  grep 'DISTRIB_DESCRIPTION'  |   sed 's/DISTRIB_DESCRIPTION=/OS Description  :/' ");
    std::system("cat /proc/cpuinfo  |  grep 'cpu MHz'   |   sed 's/cpu/CPU/' ");
    std::system("cat /proc/meminfo  |  grep 'MemTotal'  | awk '{print $1 $2 $3}' |   sed 's/MemTotal:/RAM Available   :/'");
    std::system("cat /proc/meminfo  |  grep 'MemFree'   | awk '{print $1 $2 $3}' |   sed 's/MemFree:/RAM Free        :/'");
  }
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher, "sysinfo", &p);
/*-------------------------------------------------------------------------*/
}


