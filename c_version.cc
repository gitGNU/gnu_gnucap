/*$Id: c_version.cc,v 26.138 2013/06/22 03:32:53 al Exp $ -*- C++ -*-
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
 *------------------------------------------------------------------*/
//Outputs the current version of gnucap

//testing=script 2013.09.10
#include <gnucap/patchlev.h>
#include <gnucap/c_comand.h>
#include <gnucap/globals.h>
/*-------------------------------------------------------------------*/
namespace {
/*-------------------------------------------------------------------*/
//help string
static std::string helptext = "Usage: version\n\t\t\t\t\t\t\tver\nversion or ver command tells the version of gnucap installed on the system.\n";

class CMD_VERSION : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST*) {itested();
	 if(cmd.tail() == "--help"){
			IO::mstdout << helptext;
	 }else{
     IO::mstdout <<
     "Gnucap : The Gnu Circuit Analysis Package\n"
     "Main version: " PATCHLEVEL "\n"
     "Core-lib version: " << lib_version() << "\n";  
	 }
  }
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"version|ver",&p);
/*-------------------------------------------------------------------*/
}