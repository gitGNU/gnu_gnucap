/*$Id: c_dowhile.cc,v 26.138 2014/08/07 11:30:00 al Exp $ -*- C++ -*-
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

//Declaration
class dowhile{
	
	public:
		PARAMETER<double> condition;//variable to store the condition of dowhile loop.
	
	private:
		CARD_LIST body;//variable to store the body of while loop
	
	public:
		dowhile(PARAMETER<double> condition)
			:condition( condition ){
		}
		~dowhile(){
			delete this;
		}

		//Function to read and store the body of loop
		void store( CS&, CARD_LIST* );

		//Function to execute the instruction stored in the body
		void execute( CS&, CARD_LIST* );	

		//Function to free the memory
		void free();
};
/*-------------------------------------------------------------------*/
//Function definitions
void dowhile::store( CS& cmd, CARD_LIST* Scope ){itested();
	CARD_LIST* ptr = &body;
	store_body( cmd, ptr );			
}

void dowhile::execute( CS& cmd, CARD_LIST* Scope ){itested();
	//Check if the body is not empty.
	if ( !body.is_empty() ){untested();
		do{itested();
			for( CARD_LIST::iterator i=body.begin(); i!=body.end(); ++i ){
				
				//Retrieve the pointer to stored object and dynamically cast it into DEV_DOT* type pointer.	
				DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>( *i );
				assert( ptr_command );									
				
				//instruction is a command in string form.
				std::string instruction = ptr_command->s();
	
				//bypass the execution if instruction is "end". 
				if( instruction!="end" ){itested();
					CS& cmd_copy = cmd;
					cmd_copy = instruction;
					CMD::cmdproc( cmd_copy, Scope );
					}else{untested();
					}
			}				
		}while( condition.e_val(0.,Scope)!=0 );
	}
}

void dowhile::free(){
	//Free the pointer of all the stored objects from CARD_LIST(body).
	for( CARD_LIST::iterator i=(this->body).begin(); i!=(this->body).end(); ++i ){
		DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>( *i );
		assert(ptr_command);
		delete ptr_command;
	}
}
	
/*-------------------------------------------------------------------*/
class CMD_DOWHILE : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* Scope) {
		
		//Define a variable "condition" which evaluates to either true or false.
		PARAMETER<double> condition;
		
		//If no "condition" is given by the user
		if(cmd.umatch(" ")){untested();
			throw Exception("dowhile command requires an expression as its input.");
		}
		
		//Get the condition. 
		else{untested();
			cmd >> condition;
		}
		//Initialise a "dowhile" object and get the pointer in "loop".
		dowhile* loop = new dowhile(condition);
		//Store the body.
		loop->store( cmd, Scope );
		//Exeute the stored commands.
		loop->execute( cmd, Scope );
		//Free the dynamically allocated memory.
		loop->free();		
	}
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"dowhile",&p);
/*-------------------------------------------------------------------*/
}


