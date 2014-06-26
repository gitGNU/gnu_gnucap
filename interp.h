/*$Id: interp.h,v 26.133 2014/06/20 23:58:04 al Exp $ -*- C++ -*-
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
 */

#ifndef INTERP_H
#define INTERP_H

#include "gnucap/c_comand.h"
#include "gnucap/globals.h"
#include "gnucap/u_parameter.h"
#include <stdbool.h>

#define TRUE 1
#define FALSE 0

std::string process_block(CS& cmd,std::queue< PARAMETER<double> >*,bool);
/*
 * process_block()
 * This functions processes a complete body of if/elif/else statements and returns else/end if user inputs any of these and 
 * in case of elif,retuens the boolean value after evaluating the condition.
 * 
*/

bool is_symbol(std::string p);
/*
 * is_symbol()
 * This function checks if the passed string is a logical symbol or not.later on it will be modified to look for identifiers,variablesand keywords.
*/

std::string process_block(CS& cmd,CARD_LIST* Scope,std::queue<std::string> *p,bool execute){untested();

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


bool is_symbol(std::string p){untested();
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

#endif


/*********************************************Following code is obsolete***********************************************/
//Conditionals Block
/*---------------------------------------------------------------------------------------------------

#define START_BRACE 0
#define END_BRACE 1
#define ELSE 2
#define COMMENT 3
#define ELSE_IF  4



This structure is not in use now.
typedef struct environment_variables{
	bool _else;
	bool start_brace;
	bool end_brace;
}if_struct;


std::string parse(std::string instruction,int* flag_ptr,int length,std::string type = "expression"){
	
	//if_struct env_vars;
	//Initialise structure variables
	//env_vars.end_brace = false;
	//env_vars._else = false;
	//env_vars.start_brace = true;
	
	std::string command = instruction;
	flag_ptr[START_BRACE] = 1;
	flag_ptr[END_BRACE] = 0;
	flag_ptr[ELSE] = 0;
	flag_ptr[COMMENT] = 0;
	flag_ptr[ELSE_IF] =0;
	
	if(type == "condition")
		flag_ptr[START_BRACE] = false;
	
	//Length of instruction
	unsigned int len = instruction.length();
	
	//Counter to check the balance of opening and closing brace in an instruction.
	int count=0,i=0;
	
	char delim;  //Delimiter:
	for(i=0;i<len;i++){
		delim = instruction[i];
		if(delim == '/' && instruction[i+1]=='/' ){untested();
			flag_ptr[COMMENT] = TRUE;
		}
			
		if(delim == '}'){itested();
			
			//env_vars.end_brace = true;	
			//env_vars.start_brace = false;
			
			flag_ptr[START_BRACE] = FALSE;
			flag_ptr[END_BRACE] = TRUE;
			
		}
		else if(delim == '{'){itested();
			
			//env_vars.start_brace = true;
			//env_vars.instruction = instruction.substr(0,i);
			
			flag_ptr[START_BRACE] = TRUE;
			command = instruction.substr(0,i);
			(if(i!=(len-1)){
				if(instruction[len-1]!='}' || int(instruction[len-1])!= 32){
					std::cout << "Syntax Error:symbols should be not be defined after '{' in the same line.\n";
					//exit(1);
				}
			}
		}
		else if(delim == '('){itested();
			count++;
		}
		else if(delim == ')'){itested();
			count--;
		}
		else if(delim == 'e' && i==0){itested();
				if(instruction.substr(i+1,4) == "lse{"){itested();
						flag_ptr[ELSE] = TRUE;
					}
				if(instruction.substr(i+1,3) == "lif" ){itested();
						flag_ptr[ELSE_IF] = TRUE;
						if(len>6)
							command = instruction.substr(5,len-5);
						else
							std::cout << "SYNTAX ERROR:ELIF satement needs a condition to evaluate\n";//Convert to Gnucap's standard Error
					}
		}
	}
	if(count!=0){itested();
			std::cout << "Syntax Error:No matching brace found.\n";//Convert to Gnucap's standard Error
			
			//exit(1);
	}
	return command;
	
	}
*/
/*
All cases covered
Cases to consider (){},(){,expression,expression;,expression},expression;},}
*/
