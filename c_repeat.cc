/*$Id: c_repeat.cc,v 26.138 2014/07/03 02:01:00 al Exp $ -*- C++ -*-
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
//Modified the copy constructor in d_dot.h and privacy of clone() member function
#include <gnucap/d_dot.h>
#include <gnucap/e_cardlist.h>
#include <stdlib.h>
#include "loops.h"
/*-------------------------------------------------------------------*/
namespace {
/*-------------------------------------------------------------------*/
//Declaration
class repeat{
	public:
		long int counter;	//Variable to count the number of times loops has to be executed.
		bool infinite;
	private:
	  CARD_LIST body; //Body stores the complete body of the loop.
		
	public:
		repeat(int _counter,bool _infinite)
			:counter(_counter),infinite(_infinite){
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
void repeat::store(	 CS& cmd, CARD_LIST* Scope ){itested();
	CARD_LIST* ptr = &body;
	store_body( cmd, ptr );			
}

void repeat::execute( CS& cmd, CARD_LIST* Scope ) { itested();
	if ( !body.is_empty() ) { itested();
		for( int ii=1; ii<=counter || infinite; ii++) { itested();
			//Iterate over all the stored instructions in given CARD_LIST
			for( CARD_LIST::iterator i=body.begin(); i!=body.end(); ++i ){
				//Cast the stored CARD_LIST* type object to DEV_DOT object			
				DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>( *i );
				assert( ptr_command );									
				//Extract the instruction string				
				std::string instruction = ptr_command->s();
				//Bypass the execution if instruction is "end" else continue
				if(instruction == "end" || instruction == "end "){itested();						
				}else{itested();
					CS& cmd_copy = cmd;
					cmd_copy = instruction;
					CMD::cmdproc(cmd_copy,Scope);
				}
			}					
		}
	}
}

void repeat::free(){
	body.erase_all();
}
/*-------------------------------------------------------------------*/

class CMD_REPEAT : public CMD {
public:
  void do_it( CS& cmd, CARD_LIST* Scope ) {
		
		long int counter;	
		bool infinite;	
		//Get the number of times loop has to be repeated.If no paramter is passed,execute infinite times.
		//Set counter such that loop runs infinite times
		if( cmd.umatch(" ") ){ itested();
			//Infinite loop;
			counter = -1;
			infinite = true;
		}

		//Set counter such that loop runs finite times
		else{itested();
			counter = atoi( (cmd.ctos()).c_str() );	
			infinite = false;
			if( counter<0 ){ itested();	
				throw Exception("repeat command takes only non-negative values of counter");
			}else{ itested();
			}		
		}
		//Create a loop object,store the body and then execute the instructions
		repeat loop(counter,infinite);
		loop.store(cmd,Scope);
		loop.execute(cmd,Scope);
		loop.free();		
	}
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"repeat",&p);
/*-------------------------------------------------------------------*/
}
