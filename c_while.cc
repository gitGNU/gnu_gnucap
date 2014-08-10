/*$Id: c_while.cc,v 26.138 2014/08/07 10:28:00 al Exp $ -*- C++ -*-
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
 //testing = script 2014.08.10 
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
//Declaration
class _while{
	public:
		PARAMETER<double> condition;//variable to store the condition of while loop.
	private:
	 	CARD_LIST body;//variable to store the body of while loop
	public:
		_while(PARAMETER<double> condition)
			:condition( condition ){
		}
		~_while(){
			delete this;
		}
		//Function to read and store the body of loop
		void store( CS&, CARD_LIST*);

		//Function to execute the instruction stored in the body
		void execute( CS&, CARD_LIST*);	

		//Function to free the memory
		void free();
};

/*-------------------------------------------------------------------*/
//Function definitions
void _while::store( CS& cmd, CARD_LIST* Scope ){itested();
	CARD_LIST* ptr = &body;
	store_body( cmd, ptr );			
}

void _while::execute( CS& cmd, CARD_LIST* Scope ){itested();
	//Check if the body is not empty.
	if ( !body.is_empty() ){itested();
		while( condition.e_val(0.,Scope)!=0 ){ itested();
			for( CARD_LIST::iterator i=body.begin(); i!=body.end(); ++i ){
				
				//Retrieve the pointer to stored object and dynamically cast it into DEV_DOT* type pointer.				
				DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>( *i );
				assert(ptr_command);									
				
				//instruction is a command in string form.
				std::string instruction = ptr_command->s();
				
				//bypass the execution if instruction is "end". 
				if(instruction == "end" || instruction == "end "){itested();						
				}else{itested();
					CS& cmd_copy = cmd;
					cmd_copy = instruction;
					CMD::cmdproc(cmd_copy,Scope);
				}
			}				
		}
	}else{itested();
	}
}

void _while::free(){itested();
	//Free the pointer of all the stored objects from CARD_LIST(body).
	for( CARD_LIST::iterator i=( this->body ).begin(); i!=(this->body).end(); ++i ){itested();
		DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>( *i );
		assert(ptr_command);
		delete ptr_command;
	}
}
	
/*-------------------------------------------------------------------*/
class CMD_WHILE : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* Scope) {
		//Define a variable "condition" which evaluates to either true or false.
		PARAMETER<double> condition;
		
		//If no "condition" is given by the user
		if(cmd.umatch(" ")){itested();
			throw Exception("while command requires an expression as its input.");
		}
		
		//Get the condition. 
		else{itested();
			cmd >> condition;
		}
		//Initialise a "while" object and get the pointer to that object in "loop".
		_while* loop = new _while( condition );
		if(!loop){untested();
			throw Exception("Not enough memory available");
		}
		else{itested();	
			//Store the body.
			loop->store( cmd, Scope );
			//Exeute the stored commands.
			loop->execute( cmd, Scope );
			//Free the dynamically allocated memory.
			loop->free();		
	  }
	}
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"while",&p);
/*-------------------------------------------------------------------*/
}

