#ifndef ALIAS_H
#define ALIAS_H
#include "c_comand.h"
#include "globals.h"
#define SIZE 30 //no. of commands

/*--------------------------------------------------------------------------*/
class CMD_EXEC;
CMD_EXEC* objects_ptr[SIZE];
int id=0;

class CMD_EXEC :public CMD {

private:
  std::string _command_string;
  std::string alias_name;
  DISPATCHER<CMD>::INSTALL* dispatcher_ptr;

public:
  CMD_EXEC(std::string s)
        : _command_string(s) {
        objects_ptr[id++]=this;  //Stores the address of objects of this class
        objects_ptr[id]='\0';    //Signifies the end of array
  }

  void do_it(CS& Cmd, CARD_LIST* Scope) {
    command(_command_string + Cmd.tail(), Scope);
  }

  std::string get_aliasname(){
    return alias_name;
  }

  void set_aliasname(std::string s,DISPATCHER<CMD>::INSTALL* p){
     alias_name=s;
     this->dispatcher_ptr=p;
  }

  void uninstall(int index){
   if (id>=1){ 
     for(int i=index;objects_ptr[i]!='\0';i++){
         objects_ptr[i]=objects_ptr[i+1];
    }
    id--;
   }
   delete this->dispatcher_ptr;
   delete this;
   
  }
  void uninstall_all(){
    id=0;
    objects_ptr[id]='\0';
    delete this->dispatcher_ptr;
    delete this; 
    }
};

#endif
