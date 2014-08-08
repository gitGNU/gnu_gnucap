#ifndef LOOPS_H
#define LOOPS_H

void store_body( CS& cmd, CARD_LIST* body ){
	//Take the input until each body associated command has corresponding end inputted by the user. 
	int end=0,start=0;//end denotes the number of ends in the body and start denotes the body associated commands like repeat,while,if,etc.			
	std::string prompt = "> ";			
	while((end-start)!=1){untested();
		//Prompt for the input				
		cmd.get_line(prompt);
			
		//Check if the inputted commmand is body associated command.
		if(cmd.umatch("repeat ") || cmd.umatch("for ") || cmd.umatch("dowhile") || cmd.umatch("while ") || cmd.umatch("if ")){untested();
			start+=1;
		}
		else if(cmd.umatch("end ")){untested();
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
