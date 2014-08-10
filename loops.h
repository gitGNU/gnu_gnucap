/*$Id: loops.h,v 26.138 2014/08/10 06:41:00 al Exp $ -*- C++ -*-
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

#ifndef LOOPS_H
#define LOOPS_H

void store_body( CS& cmd, CARD_LIST* body ){itested();
	//Take the input until each body associated command has corresponding end inputted by the user. 
	int end=0,start=0;//end denotes the number of ends in the body and start denotes the body associated commands like repeat,while,if,etc.			
	std::string prompt = "> ";			
	while((end-start)!=1){itested();
		//Prompt for the input				
		cmd.get_line(prompt);
			
		//Check if the inputted commmand is body associated command.
		if(cmd.umatch("repeat ") || cmd.umatch("for ") || cmd.umatch("dowhile") || cmd.umatch("while ") || cmd.umatch("if ")){untested();
			start+=1;
		}
		else if(cmd.umatch("end ")){itested();
					end +=1;
		}
						
		//Create a DEV_DOT object to store the command as a string.
		DEV_DOT* instruction = new DEV_DOT();	
				 
		//Store the command.
		instruction->set(cmd.fullstring());
			
		//Insert the cloned DEV_DOT object into the list.
		body->push_back(instruction->clone());			
			
		}
}
#endif 
