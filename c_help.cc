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
class CMD_HELP : public CMD {
public:
  void do_it(CS& Cmd, CARD_LIST*) {
		//If no command is passed as an argument
		if(Cmd.tail()==""){
			throw Exception("Usage: help [command]");
		}
		std::string file_name = "c_"+Cmd.tail()+".cc";//Generate concerned file name using the command name which is enquired.
		std::string line;
		std::ifstream file;
		
		//Open the file with filename in the "current directory".
		file.open(file_name.c_str(),std::ios::out);
		if(file.is_open()){
			while(getline(file,line) && line.find("<Plugin Manual>")==std::string::npos);//Search for the line "Plugin Manual".

			//If no manual is dpecified by the developer.			
			if(line==""){																																																			
				throw Exception("No manual entry found.Refer GNUcap Manual or contact gnucap-devel.");
			}

			while(getline(file,line) && line.find("<End>")==std::string::npos){//Find the End marker.
				IO::mstdout << line << '\n';
				}
		}

		else{																											//If there is a problem opening c_command.cc
			IO::mstdout << "No entry matching "<<Cmd.tail()<<" found.\nPlease check Gnucap Manual or contact gnucap-devel for more info on "\
			<<Cmd.tail()<<'\n';
		}		
		
  }
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"help",&p);
/*-------------------------------------------------------------------*/
}
