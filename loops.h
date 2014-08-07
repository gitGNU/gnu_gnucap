#ifndef LOOPS_H
#define LOOPS_H

void store_body(CS& cmd, CARD_LIST* body){

			int end=0,start=0;			
			while((end-start)!=1){untested();
				cmd.get_line("> ");
			
				//Match the command name of all the loop and conditionals in gnucap.
				if(cmd.umatch("repeat ") || cmd.umatch("for " || cmd.umatch("dowhile") || cmd.umatch("while ") || cmd.umatch("if "))){untested();
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
