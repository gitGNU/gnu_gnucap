/*$Id: c_for.cc,v 26.138 2014/07/03 02:01:00 al Exp $ -*- C++ -*-
 * Copyright (C) 2014 Rishabh Yadav
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
#include <gnucap/d_dot.h>
#include <gnucap/e_cardlist.h>
#include <gnucap/ap.h>
#include <stdlib.h>
/*-------------------------------------------------------------------*/
namespace {
/*-------------------------------------------------------------------*/

class CMD_REPEAT : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* Scope) {
				//Get the number of ties loop has to be repeated.
			 int counter = atoi((cmd.ctos()).c_str());
			 IO::mstdout << "Counter" << counter << "\n";
			 
			 //Create a CARD_LIST object to store the body of the loop.
			 CARD_LIST* new_module = subckt();
			 
			 //Read the body
			 while(!(cmd >> "end ")){
				 //Create a DEV_DOT object to store the command as a string.
				 DEV_DOT* _command = new DEV_DOT();
				 				 
				 //Get the command.
				 cmd.get_line(">");
				 
				 //Store the command.
				 _command->set(cmd.fullstring());
				 
				 //Insert the DEV_DOT object into the list.
				 new_module->push_front(_command);
			}
			
			//Execute the body
			typedef std::list<CARD*>::iterator iterator;
			if (!new_module->is_empty()){	
				for (iterator ci=new_module->begin(); ci!=new_module->end(); ++ci) {
								//Retrieve the object at index ci;								
								std::string ptr_command = (dynamic_cast<DEV_DOT*>(*ci))->s();
								
								//ISSUE:Retrieved object is CARD* not DEV_DOT and since the CARD* don't have access to  DEV_DOT::s() function so command string is not retrieveable. 
								
								//Test if the order of command execution is correct.
								IO::mstdout << "command: " << ptr_command << "\n";
								
								//Construct the CS object with command as a parameter.
								/*
								CS cmd_str = CS(CS::_STRING,ptr_command->s());
								cmdproc(cmd_str,Scope);
								*/
								command(ptr_command,Scope);
				}
		}			 
}
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"repeat",&p);
/*-------------------------------------------------------------------*/
}
