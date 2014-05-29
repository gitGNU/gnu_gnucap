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
//testing = script 2013.09.12
#include <gnucap/c_comand.h>
#include <gnucap/globals.h>
#include <vector>
/*--------------------------------------------------------------------------*/
namespace{
/*--------------------------------------------------------------------------*/
class CMD_EXEC;
std::vector<CMD_EXEC*> objects_ptr(2);//vector to store the address of aliased objects.
int id=0;

class CMD_EXEC :public CMD {
private:
  std::string _command_string;
  std::string _alias_name;
  DISPATCHER<CMD>::INSTALL* _dispatcher_ptr;

public:
  CMD_EXEC(std::string s)
        : _command_string(s) {
        if(id<=objects_ptr.size()-2){//vector bound checking
          objects_ptr.resize(objects_ptr.size()+5);
        }else{//resize vector
        }
          objects_ptr[id++]=this;// //Stores the address of objects of this class
          objects_ptr[id]='\0';    //Signifies the end of array             
  }

  void do_it(CS& Cmd, CARD_LIST* Scope) {//do_it method invoked on the aliased object
    command(_command_string +" "+Cmd.tail(), Scope);
  }

  std::string get_aliasname(){
    return _alias_name;
  }

  void set_aliasname(std::string s,DISPATCHER<CMD>::INSTALL* p){
    _alias_name=s;
    this->_dispatcher_ptr=p;
  }

  void uninstall(int index){//used to unalias.
   if (id>0){ 
     objects_ptr[index]=objects_ptr[--id];
     objects_ptr[id]='\0';
   }
   delete this->_dispatcher_ptr;
   delete this;
   
  }
  void uninstall_all(){//unalias all objects.
    delete this->_dispatcher_ptr;
    delete this; 
    }
};



/*--------------------------------------------------------------------------*/

class CMD_ALIAS : public CMD {
public:
  void do_it(CS& Cmd, CARD_LIST*) {
    std::string _alias_name = Cmd.ctos();
    if(_alias_name == "" || Cmd.tail()==""){
      throw Exception("Usage: alias [word] [command]");
    }else{
    }
    //Install aliased object.
    CMD_EXEC* new_command = new CMD_EXEC(Cmd.tail());
    DISPATCHER<CMD>::INSTALL* install_ref = new DISPATCHER<CMD>::INSTALL(&command_dispatcher, _alias_name, new_command); 
    new_command->set_aliasname(_alias_name,install_ref);//Will be used in unalias
  }
}alias_command;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"alias",&alias_command);

/*--------------------------------------------------------------------------*/

class CMD_UNALIAS : public CMD {
private:
     std::string _alias_name;
     int _flag;//flag to tell whether the object to be unaliased exists or not.
public:
     void do_it(CS& Cmd,CARD_LIST*){
       _alias_name = Cmd.ctos();
       if(_alias_name == "all"){
         char ch;
         IO::mstdout << "are you sure you want to remove all aliases?y/n:";
         std::cin >> ch;
         if(ch=='y' || ch =='Y'){
           //Remove all aliases.
           for(int i=0;objects_ptr[i]!='\0';i++){
             objects_ptr[i]->uninstall_all();
           }
           id=0;
           objects_ptr[id]='\0';
           throw Exception("all aliases removed");
  	 }
         else if(ch=='n' || ch=='N'){
           throw Exception("");
         }
         else{
           throw Exception("Wrong Input!");
         }
       }else{
       }
       _flag=1;
       //Remove the "alias" object.
       for(int i=0;objects_ptr[i]!='\0';i++){
         if (objects_ptr[i]->get_aliasname() == _alias_name){//get the address of aliased name and uninstall it.
           objects_ptr[i]->uninstall(i);
           _flag=0;
           break;
         }
       }  
       if (_flag){
         IO::mstdout << "No such aliased word exists\n";
       }else{
       }
}
}unalias_command;
DISPATCHER<CMD>::INSTALL d1(&command_dispatcher,"unalias",&unalias_command);
/*----------------------------------------------------------------------------*/
}

