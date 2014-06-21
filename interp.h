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

#include <gnucap/c_comand.h>
#include <gnucap/globals.h>	
#include <stdbool.h>

#define TRUE 1
#define FALSE 0


//Conditionals Block
/*---------------------------------------------------------------------------------------------------*/

#define START_BRACE 0
#define END_BRACE 1
#define ELSE 2
#define COMMENT 3

/*This structure is not in use now.
typedef struct environment_variables{
	bool _else;
	bool start_brace;
	bool end_brace;
}if_struct;
*/

std::string parse(std::string instruction,int* flag_ptr,int length,std::string type = "expression"){
	/*
	if_struct env_vars;
	Initialise structure variables
	/*env_vars.end_brace = false;
	env_vars._else = false;
	env_vars.start_brace = true;
	*/
	std::string command = instruction;
	flag_ptr[START_BRACE] = 1;
	flag_ptr[END_BRACE] = 0;
	flag_ptr[ELSE] = 0;
	flag_ptr[COMMENT] =0;
	
	if(type == "condition")
		flag_ptr[START_BRACE] = false;
	
	//Length of instruction
	unsigned int len = instruction.length();
	
	//Counter to check the balance of opening and closing brace in an instruction.
	int count=0,i=0;
	
	char delim;  //Delimiter:
	for(i=0;i<len;i++){
		delim = instruction[i];
		if(delim == '/' && instruction[i+1]=='/' ){
			flag_ptr[COMMENT] = TRUE;
		}
			
		if(delim == '}'){
			/*
			env_vars.end_brace = true;	
			env_vars.start_brace = false;
			*/
			flag_ptr[START_BRACE] = FALSE;
			flag_ptr[END_BRACE] = TRUE;
		}
		else if(delim == '{'){
			/*
			env_vars.start_brace = true;
			env_vars.instruction = instruction.substr(0,i);
			*/
			flag_ptr[START_BRACE] = TRUE;
			command = instruction.substr(0,i);
			/*(if(i!=(len-1)){
				if(instruction[len-1]!='}' || int(instruction[len-1])!= 32){
					std::cout << "Syntax Error:symbols should be not be defined after '{' in the same line.\n";
					//exit(1);
				}
			}*/
		}
		else if(delim == '('){
			count++;
		}
		else if(delim == ')'){
			count--;
		}
		else if(delim == 'e'){
				if(instruction.substr(i+1,4) == "lse{"){
						flag_ptr[ELSE] = TRUE;
						//std::cout << "else detected\n";
					}
		}
	}
	if(count!=0){
			std::cout << "Syntax Error:No matching brace found.\n";
			//exit(1);
	}
	return command;
	
	}
//Cases to consider (){},(){,expression,expression;,expression},expression;},}

/*---------------------------------------------------------------------------------------------------*/


#endif
