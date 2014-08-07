/*$Id: c_for.cc,v 26.138 2014/08/07 10:28:00 al Exp $ -*- C++ -*-
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
#include <gnucap/u_parameter.h>
#include <stdlib.h>
#include "loops.h"
/*-------------------------------------------------------------------*/
namespace {
/*-------------------------------------------------------------------*/

class _while{
	public:
	 PARAMETER<double> condition;
	private:
	 CARD_LIST body;
	public:
		_while(PARAMETER<double> condition)
			:condition(condition){
			}
		~_while(){
			delete this;
			}
		void store(CS& ,CARD_LIST*);
		void execute(CS&,CARD_LIST*);	
		void free();
};

void _while::store(CS& cmd, CARD_LIST* Scope){untested();
			CARD_LIST* ptr = &body;
			store_body(cmd,ptr);
			
}
void _while::execute(CS& cmd,CARD_LIST* Scope){untested();
			if (!body.is_empty()){untested();
				while(condition.e_val(0.,Scope)!=0){untested();
					for(CARD_LIST::iterator i=body.begin(); i!=body.end(); ++i){
						DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>(*i);
						assert(ptr_command);									
						std::string instruction = ptr_command->s();
						if(instruction!="end"){untested();
							CS& cmd_copy = cmd;
							cmd_copy = instruction;
							CMD::cmdproc(cmd_copy,Scope);
						}else{untested();
							//break;
						}
					}				
				}
			}
}

void _while::free(){
	for(CARD_LIST::iterator i=(this->body).begin(); i!=(this->body).end(); ++i){
		DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>(*i);
		assert(ptr_command);
		delete ptr_command;
	}
}
	

class CMD_WHILE : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* Scope) {
		
		//Define a variable "condition" which evaluates to either true and false.
		PARAMETER<double> condition;
		
		//If no "condition" is given by the user
		if(cmd.umatch(" ")){untested();
			throw Exception("while command requires an expression as its input.");
		}
		
		//Get the condition. 
		else{untested();
			cmd >> condition;
		}
		_while* loop = new _while(condition);
		loop->store(cmd,Scope);
		loop->execute(cmd,Scope);
		loop->free();		
}
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"while",&p);
/*-------------------------------------------------------------------*/
}

