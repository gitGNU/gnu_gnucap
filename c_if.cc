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
 * Syntax: if (condition){
 * 				//Set of instructions;
 * 		   }
 * 		   else{
 * 				//Set of instructions
 * 		   }
 * 
 * The if statement should be followed by a space then the condition(brackets '()' are not necessary).The condition should be immediately terminated by 
 * '{' brace.The end of if block is designated by '}'.The set of instructions supposed to work when the condition in if statement is true can be defined
 * between the two pair of curley braces.
 * single if statement and set of if-else statements both are supported.
 * Example statements:
 * 1. if (condition){
 * 		//instruction1
 * 		//instruction2
 * 		...	
 * }
 * 
 * 2. if (condition){
 * 		//instruction1
 * 		//instruction2
 * 		...
 * 	  }
 * 	  else{}
 * 
 * 3.if (condition){
 * 		//instruction1
 * 		//instruction2
 * 		...	
 * 	}
 * 	else{
 * 		//instruction3
 * 		//instruction4
 * 		...
 *  }		
 */
 
 /* TO DO: 1.Debug nested loops.
		   2.Find the usage of gnucap's expression parser library and substitute in line 96.
		   3.Make the conditionals work without brackets.(Now,'{','}' braces are necessary)
    Notice:Right now it is assumed that condition in if clause evaluates to false.After doing a bit research on TODO#2 it will be fixed.It only 
    requires a modification 
    of line 96 and removal of line 101; 
 */
 
#include <gnucap/c_comand.h>
#include <gnucap/globals.h>
#include <gnucap/m_expression.h>
#include "interp.h"
#include <stack>

#define NUM_FLAGS 10
#define TRUE 1
#define FALSE 0

#define START_BRACE 0
#define END_BRACE 1
#define ELSE 2
#define COMMENT 3
/*--------------------------------------------------------------------------*/
namespace {
/*--------------------------------------------------------------------------*/
class CMD_IF : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* Scope){
    
    std::string condition = cmd.tail();
    //if_struct env_vars;
    
    /*Flag array */
    int flags[NUM_FLAGS];
    
    //Find the condition to be checked for the branch to be taken or not
    std::string instruction = parse(condition,flags,NUM_FLAGS,"condition");
    
    //TO DO:Evaluate the condition
    bool _flag;//= eval(condition);
    
    //Setting the _flag for testing.
    _flag=false;
    
    
    //TO DO:Check if only one instruction follows the condtional statement or if there is a block of instructions
    //Now,assuming instructions are always defined in a pair of curley braces.
    
    //if(_flag){
	//functionalize the following procedure as process_block()
	//IF BLOCK
	while(flags[START_BRACE] && !flags[END_BRACE]){
		IO::mstdout << '>';
 		//std::cin >> instruction;
		//std::cin.clear();
		std::getline(std::cin, instruction);
		//std::cout << "Execute:"<<instruction << '\n';
		instruction = parse(instruction,flags,NUM_FLAGS);
		if(_flag){
			//std::cout << "Returned " << instruction << "\n";
			CMD::command(instruction.c_str(),Scope);
		}
	}
	
	//Look for else statement.
	std::getline(std::cin, instruction);
	instruction = parse(instruction,flags,NUM_FLAGS);
	
	//ELSE BLOCK
	if(flags[ELSE]){
		//functionalize the the following procedure as process_block()
		while(flags[START_BRACE] && !flags[END_BRACE]){	
			IO::mstdout << '>';
			std::getline(std::cin, instruction);
			instruction = parse(instruction,flags,NUM_FLAGS);
			if(!_flag){
				CMD::command(instruction.c_str(),Scope);
			}
		}
	}				
  }
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher, "if", &p);
/*--------------------------------------------------------------------------*/
}
