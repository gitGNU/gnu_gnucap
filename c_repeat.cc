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
//Modified d_dot.h to make the clone member function from DEV_DOT class a public member function.
#include "d_dot.h"
#include <gnucap/e_cardlist.h>
#include <gnucap/ap.h>
#include <stdlib.h>
/*-------------------------------------------------------------------*/
namespace {
/*-------------------------------------------------------------------*/

class CMD_REPEAT : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* Scope) {
				//Get the number of times loop has to be repeated.
			 int counter = atoi((cmd.ctos()).c_str());
			 
			 //std::cout << "Counter:" << counter << "\n";
			 
			 //Create a CARD_LIST object to store the body of the loop.
			 CARD_LIST new_module;;
			 
			 //Read the body
			  do{
				 //Create a DEV_DOT object to store the command as a string.
				 DEV_DOT* instruction = new DEV_DOT();
				 				 
				 //Get the command.
				 cmd.get_line(">");
				 
				 //Store the command.
				 instruction->set(cmd.fullstring());
				 
				 //Insert the cloned DEV_DOT object into the list.
				 new_module.push_back(instruction->clone());
			}while(!(cmd >> "end "));
			
			//Execute the body
			
			if (!new_module.is_empty()){	
				while(counter>0){std::cout << "in while\n";
				   for(CARD_LIST::iterator i=new_module.begin(); i!=new_module.end(); ++i){
								DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>(*i);
								assert(ptr_command);
								//ISSUE:Retrieved object is CARD* not DEV_DOT and since the CARD* don't have access to DEV_DOT::s()
								//function so command string is not retrievable. 
								
								//Test if the order of command execution is correct.
								std::cout << "command string is " << ptr_command->s() << "\n";	
								
								//Construct the CS object with ptr_command as a parameter.
								/*
								CS cmd_str = CS(CS::_STRING,ptr_command->s());
								cmdproc(cmd_str,Scope);
								*/
								command(ptr_command->s(),Scope);
				}
				counter--;
			}
		}			 
}
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"repeat",&p);
/*-------------------------------------------------------------------*/
}
