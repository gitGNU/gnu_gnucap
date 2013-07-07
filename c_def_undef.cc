/*$Id: c_def_undef.cc,v 26.133 2013/07/12 18:30:00 al Exp $ -*- C++ -*-
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
 * def:Command is used to define a function which can take int,float and double type arguments.
 * undef:undef command removes the the user defined functions.
 */

#include "c_comand.h"
#include "globals.h"
#include "u_status.h"
#include "exprtk.hpp"
#define SIZE 20
class CMD_FUNC;
CMD_FUNC* objects_ptr[SIZE];
int id=0;

template<typename T>
T trig_function(std::string expression_string,T arg1,T arg2,T arg3)
{  
   exprtk::symbol_table<T> symbol_table;
   symbol_table.add_variable("x",arg1);
   symbol_table.add_variable("y",arg2);
   symbol_table.add_variable("z",arg3);
   symbol_table.add_constants();

   exprtk::expression<T> expression;
   expression.register_symbol_table(symbol_table);
   exprtk::parser<T> parser;
   parser.compile(expression_string,expression);
   return expression.value();
}

/*------------------------------------------------------------------------*/


class CMD_FUNC: public CMD {

private:
     std::string func_name,expression;
     double  arg1,arg2,arg3;
     DISPATCHER<CMD>::INSTALL* dispatcher_ptr;
    

public:
 
      CMD_FUNC(std::string function,std::string expression_str)
       :func_name(function),
       expression(expression_str){
       objects_ptr[id++]=this;  //Stores the address of objects of this class
        objects_ptr[id]='\0'; 
      }


      void install(DISPATCHER<CMD>::INSTALL* p){
       this->dispatcher_ptr=p;
      }


      std::string get_func_name(){
        return func_name;
      }
      void uninstall(int index){
     	 if (id>0){ 
            objects_ptr[index]=objects_ptr[--id];
            objects_ptr[id]='\0';
             }
   	delete this->dispatcher_ptr;
   	delete this;
      }

    void uninstall_all(){
    	  delete this->dispatcher_ptr;
    	  delete this; 
    }

      void do_it(CS& cmd,CARD_LIST* Scope){
           cmd >> "(" >> arg1 >> "," >> arg2 >> "," >> arg3 >>")";
	   IO::mstdout << trig_function<double>(expression,arg1,arg2,arg3) << "\n";
	}
};

/*--------------------------------------------------------------------------*/
class CMD_DEF : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST*) {
      std::string func_name,expression_str;
      cmd >> func_name;
      if(func_name=="")    throw Exception("Usage:def [function_name]");
      IO::mstdout << ">";
      std::cin >> expression_str;     
      CMD_FUNC* function = new CMD_FUNC(func_name,expression_str);
      DISPATCHER<CMD>::INSTALL* install_ref = new DISPATCHER<CMD>::INSTALL(&command_dispatcher, func_name, function);
      function->install(install_ref);
  }
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"def",&p);

/*-----------------------------------------------------------------------------*/

class CMD_UNDEF : public CMD{

 public:
       void do_it(CS& Cmd,CARD_LIST* Scope){
        std::string func_name = Cmd.tail();	
        if(func_name == "-a"){
              char ch;
              IO::mstdout << "are you sure you want to remove all defined functions?y/n:";
              std::cin >> ch;
              if(ch=='y' || ch =='Y'){
              	 for(int i=0;objects_ptr[i]!='\0';i++){
               		objects_ptr[i]->uninstall_all();
                        
                }
                 id=0;
  	         objects_ptr[id]='\0';
              throw Exception("all defined functions removed.");
  	     }
             else if(ch=='n' || ch=='N'){throw Exception("");}
             else throw Exception("Wrong Input!");
          }
        int flag=1;
        for(int i=0;objects_ptr[i]!='\0';i++)
        {
          if (objects_ptr[i]->get_func_name() == func_name){
               objects_ptr[i]->uninstall(i);
               flag=0;
               break;
            }
         }  

         if (flag){
          IO::mstdout << "No such function exists.\n";
         }  
}
}p1;

DISPATCHER<CMD>::INSTALL d1(&command_dispatcher,"undef",&p1);






