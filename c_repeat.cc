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
//Modified the copy constructor in d_dot.h and privacy of clone() member function
#include <gnucap/d_dot.h>
#include <gnucap/e_cardlist.h>
#include <stdlib.h>
#include "loops.h"
/*-------------------------------------------------------------------*/
namespace {
/*-------------------------------------------------------------------*/

class repeat{
	public:
	 long int counter;
	 CARD_LIST body;
		repeat(int counter)
			:counter(counter){
			}
		~repeat(){
			delete this;
			}
		void store(CS& ,CARD_LIST*);
		void execute(CS&,CARD_LIST*);	
		void free();
};

void repeat::store(CS& cmd, CARD_LIST* Scope){
			CARD_LIST* ptr = &body;
			store_body(cmd,ptr);
			
}
void repeat::execute(CS& cmd,CARD_LIST* Scope){untested();
			if (!body.is_empty()){untested();
				while(counter!=0){untested();
					for(CARD_LIST::iterator i=body.begin(); i!=body.end(); ++i){
						DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>(*i);
						assert(ptr_command);									
						//Assign the command to cmd.
						std::string instruction = ptr_command->s();
						if(instruction!="end"){untested();
							CS& cmd_copy = cmd;
							cmd_copy = instruction;
							CMD::cmdproc(cmd_copy,Scope);
						}else{untested();
							//break;
						}
					}
					if(counter!=-1){untested();
						counter--;
					}
					else{untested();
					}					
				}
			}
}

void repeat::free(){
	for(CARD_LIST::iterator i=(this->body).begin(); i!=(this->body).end(); ++i){
		DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>(*i);
		assert(ptr_command);
		delete ptr_command;
	}
}
	

class CMD_REPEAT : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* Scope) {
		//Get the number of times loop has to be repeated.If no paramter is passed execute infinite times.
		long int counter;
		
		//Set counter such that loop runs infinite times
		if(cmd.umatch(" ")){untested();
			counter = -1;
		}
		//Set counter such that loop runs finite times
		else{untested();
			counter = atoi((cmd.ctos()).c_str());	
			if(counter<0){untested();	
				throw Exception("repeat command takes only non-negative values of counter");
			}else{untested();
			}		
		}
		
		repeat* loop = new repeat(counter);
		loop->store(cmd,Scope);
		loop->execute(cmd,Scope);
		loop->free();		
}
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"repeat",&p);
/*-------------------------------------------------------------------*/
}
