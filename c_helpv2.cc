/*$Id: c_help.cc,v 26.138 2014/03/15 01:53:23 al Exp $ -*- C++ -*-
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
#include <gnucap/c_comand.h>
#include <gnucap/globals.h>
#include <fstream> 
/*-------------------------------------------------------------------*/
namespace {
/*-------------------------------------------------------------------*/
static std::string helptext = "Usage: help [command]\nTo get help for a command you can also type command --help\n";

class CMD_HELP : public CMD {
public:
  
  void do_it(CS& cmd, CARD_LIST* Scope) {
		//If no command is passed as an argument
		if(cmd.tail()==""){
			throw Exception("Usage: help [command]");
		}
		else if(cmd.tail() == "--help"){
			IO::mstdout << helptext;
		}
		else{
			if(cmd.more()){//if some command is passed run it. 
				command(cmd.tail()+" --help",Scope);
			}else{
			}
		}	
  }
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"help",&p);
/*-------------------------------------------------------------------*/
}

