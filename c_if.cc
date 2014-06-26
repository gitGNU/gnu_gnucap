/*$Id: c_if.cc,v 26.133 2013/07/01 06:00:04 al Exp $ -*- C++ -*-
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
 *------------------------------------------------------------------
 *
 * <plugin>
 * Syntax: if condition_1
 * 				//instruction_1
 * 				//instruction_2
 * 				.....
 * 			elif condition_2
 * 				//instruction_3
 * 				//instruction_4
 * 				.....
 * 			elif condition_3
 * 				//instruction_5
 * 				//instruction_6
 * 				.....
 * 			.
 * 			.
 * 			elif condition_i
 * 				//instruction_(m-1)
 * 				//instruction_m
 * 				.....
 * 			else
 * 				//instruction_(n-1)
 * 				//instruction_n
 * 				...
 * 			end
 */
 
 /* 
  * TO DO: Debug Nested Loops
 */
 
#include <gnucap/c_comand.h>
#include <gnucap/globals.h>
#include <gnucap/u_parameter.h>
#include <string>
#include <queue>

#define TRUE 1
#define FALSE 0

/*--------------------------------------------------------------------------*/
namespace {
	
/*Function Declarations and Definitions*/

std::string process_block(CS& cmd,std::queue< PARAMETER<double> >*,bool);
bool is_symbol(std::string p);


std::string process_block(CS& cmd,CARD_LIST* Scope,std::queue<std::string> *p,bool execute){itested();
	/*
	* process_block()
	* This functions processes a complete body of if/elif/else statements and returns else/end if user inputs any of these and 
	* in case of elif,retuens the boolean value after evaluating the condition.
	* 
	*/
	std::string cmd_ctos,cmd_tail,instruction;
	PARAMETER<double> condition;
	std::string prompt = "> ";
	do{
		cmd.get_line(prompt);
		cmd_ctos = cmd.ctos();
		cmd_tail = cmd.tail();
		instruction = cmd_ctos+" "+cmd_tail;
		//IO::mstdout << "Instruction: " << 	instruction << "\n";	
		if(execute){untested();
			p->push(instruction);	 
			//CMD::command(instruction,Scope);
		}
		
	}while(!is_symbol(cmd_ctos));
	
	if(cmd_ctos == "elif"){untested();
		cmd >> condition;
		cmd.check(bDANGER, "syntax error");
		condition.e_val(0.,Scope);
		return to_string(condition!=0);
	}
	else{untested();
		return cmd_ctos;
	}	
}


bool is_symbol(std::string p){itested();
	/*
	* is_symbol()
	* This function checks if the passed string is a logical symbol or not.later on it will be modified to look for identifiers,variablesand keywords.
	*/
	if(p == "else" || p == "elif"){
		return true;
	}
	else if(p == "end"){
		return true;
	}
	else{
		return false;
	}	
	
}
/*--------------------------------------------------------------------------*/
class CMD_IF : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* Scope){	  
	//Queue to store the instructions to be executed.
    std::queue< std::string > operations;
    PARAMETER<double> condition;
    cmd >> condition;
    cmd.check(bDANGER, "syntax error");
    condition.e_val(0.,Scope);
    bool truth = condition != 0;
    new_subckt();

	//IF BLOCK
	std::string symbol = process_block(cmd,Scope,&operations,truth);
	
	while(symbol != "end"){untested();		
		
		//ELSE-IF BLOCK
		if(symbol != "else"){untested();
			//Take the branch only if previous if/elif statements hasn't been executed.
			if(truth == false){itested();
				truth = atoi(symbol.c_str());
				symbol = process_block(cmd,Scope,&operations,truth);
			}
			else{itested();
				symbol = process_block(cmd,Scope,&operations,false);
			}
		}
	
		//ELSE BLOCK
		if(symbol == "else"){itested();
			symbol = process_block(cmd,Scope,&operations,!truth);
		}
	}
	while(!operations.empty()){itested();	
			command(operations.front(), Scope);
			operations.pop();
		}					
  }
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher, "if", &p);
/*--------------------------------------------------------------------------*/
}
