/*$Id: c_foreach.cc,v 26.138 2014/08/08 00:45:00 al Exp $ -*- C++ -*-
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

class foreach{
	public:
		std::string variable;
	private:
		CARD_LIST body;
  	void replace(std::string &s, const std::string &search, const std::string &replace);//Function to replace a substring in a string with new value.
	public:
		foreach(std::string variable)
			:variable(variable){
	   }
		~foreach(){
		 	delete this;
		 }
		void store(CS& ,CARD_LIST*);
		void execute(CS&,CARD_LIST*,std::vector<int>);	
		void free();
};

void foreach::store(CS& cmd, CARD_LIST* Scope){untested();
	CARD_LIST* ptr = &body;
	store_body(cmd,ptr);			
}

void foreach::execute(CS& cmd,CARD_LIST* Scope,std::vector<int> range){untested();
	if (!body.is_empty()){untested();
		int len = range.size(),j; 
			for(j=0;j<len;j++){
				for(CARD_LIST::iterator i=body.begin(); i!=body.end(); ++i){
					DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>(*i);
					assert(ptr_command);									
					std::string instruction = ptr_command->s();
					
					//Substitue $var by the value in "var".
					std::string search = "$"+variable;
					std::string rep = to_string(range[j]);

					if(instruction.find(search)){itested();
						replace(instruction,search,rep);
					}

					if(instruction!="end"){itested();
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

void foreach::replace(std::string &s, const std::string &search, const std::string &replace ) {
	for(size_t pos = 0; ; pos += replace.length()){
		pos = s.find( search, pos );
		if( pos == std::string::npos ) break;
		s.erase( pos, search.length() );
		s.insert( pos, replace );
	}
}

void foreach::free(){
	for(CARD_LIST::iterator i=(this->body).begin(); i!=(this->body).end(); ++i){
		DEV_DOT* ptr_command = dynamic_cast<DEV_DOT*>(*i);
		assert(ptr_command);
		delete ptr_command;
	}
}
	

class CMD_FOREACH : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* Scope) {
		std::string variable;
		int first,last;
		std::vector<int> range(10);
		
		//If no range and variable name is given by the user
		if(cmd.umatch(" ")){itested();
			throw Exception("foreach command requires a variable and range of values that variable can take.\nSyntax: foreach var m:n");
		}

		else{itested();
			//Fil the values given by the user into appropriate variables
			cmd >> variable >> first >> ":" >> last;
			range.resize(last-first+1);
			for(int i=first;i<=last;i++){
				range[i-first] = i;
			}
	
			foreach* loop = new foreach(variable);
			loop->store(cmd,Scope);
			loop->execute(cmd,Scope,range);
			loop->free();
		}	
	}
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"foreach",&p);
/*-------------------------------------------------------------------*/
}
