/*$Id: c_alias_unalias.cc,v 26.133 2013/07/06 23:06:04 al Exp $ -*- C++ -*-
 * Copyright (C) 2013 Rishabh Yadav
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
 * alias:creates an alias for a command
 * unalias:removes the aliases for the given name
 */

#include "c_comand.h"
#include "globals.h"
#include "alias.h"

/*--------------------------------------------------------------------------*/

class CMD_ALIAS : public CMD {
public:
  void do_it(CS& Cmd, CARD_LIST* Scope) {
    int i;
    std::string alias_name = Cmd.ctos();
    CMD_EXEC* new_command = new CMD_EXEC(Cmd.tail());
    DISPATCHER<CMD>::INSTALL* install_ref = new DISPATCHER<CMD>::INSTALL(&command_dispatcher, alias_name, new_command); 
    new_command->set_aliasname(alias_name,install_ref);
  }
}alias_command;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"alias",&alias_command);

/*--------------------------------------------------------------------------*/

class CMD_UNALIAS : public CMD {
private:
     std::string alias_name;
     int flag;
public:
     void do_it(CS& Cmd,CARD_LIST* Scope){
        alias_name = Cmd.tail();
        if(alias_name == "-a"){
              char ch;
              IO::mstdout<<"are you sure you want to remove all aliases?y/n:";
              std::cin >> ch;
              if(ch=='y' || ch =='Y'){
              	 for(int i=0;objects_ptr[i]!='\0';i++){
               		objects_ptr[i]->uninstall();
                }
              throw Exception("all aliases removed");
  	     }
             else if(ch=='n' || ch=='N'){throw Exception("");}
             else throw Exception("Wrong Input!");
          }
        flag=1;
        for(int i=0;objects_ptr[i]!='\0';i++)
        {
          if (objects_ptr[i]->get_aliasname() == alias_name){
               objects_ptr[i]->uninstall();
               flag=0;
               break;
            }
         }  

         if (flag){
          IO::mstdout << "No such aliased word exists\n";
         }  
}
}unalias_command;
DISPATCHER<CMD>::INSTALL d1(&command_dispatcher,"unalias",&unalias_command);

