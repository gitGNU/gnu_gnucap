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
//Modified the privacy of clone() member function and copy constructor in d_dot.h
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
		//Get the number of times loop has to be repeated.
		int counter = atoi((cmd.ctos()).c_str());

		//Create a CARD_LIST object to store the body of the loop.
		CARD_LIST new_module;;
			 
		//Read the body
		cmd.get_line(">");
		while(!(cmd >> "end ")){untested();
			 //Create a DEV_DOT object to store the command as a string.
			DEV_DOT* instruction = new DEV_DOT();	
				 
			//Store the command.
			instruction->set(cmd.fullstring());
			
			//TODO::DEV_DOT clone() not working so directly calling the constructor for the time being.
			CARD* ptr_comand = new DEV_DOT(*instruction);
			
			//Insert the cloned DEV_DOT object into the list.
			new_module.push_back(ptr_comand);
			
			//Get the command.
			cmd.get_line(">");

		}
			
		//Execute the body of the loop			
		if (!new_module.is_empty()){untested();
			while(counter>0){itested();
				for(CARD_LIST::iterator i=new_module.begin(); i!=new_module.end(); ++i){untested();
					DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>(*i);
					assert(ptr_command);
													
					//Assign the command to cmd.
					cmd = ptr_command->s();
					cmdproc(cmd,Scope);
				}
				counter--;
			}
		}			 
}
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"repeat",&p);
/*-------------------------------------------------------------------*/
}
