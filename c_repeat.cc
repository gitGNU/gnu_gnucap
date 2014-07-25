/*$Id: c_for.cc,v 26.138 2014/07/03 02:01:00 al Exp $ -*- C++ -*-
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
 
#include <gnucap/c_comand.h>
#include <gnucap/globals.h>
#include <gnucap/d_dot.h>
#include <gnucap/d_coment.h>
#include <gnucap/d_subckt.h>
#include <gnucap/e_model.h>
#include <gnucap/u_lang.h>
#include <stdlib.h>
/*-------------------------------------------------------------------*/
namespace {
/*-------------------------------------------------------------------*/

class CMD_REPEAT : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST*) {
			 int counter = atoi((cmd.ctos()).c_str());
			 
			 MODEL_SUBCKT* new_module = new MODEL_SUBCKT;
		 	 assert(new_module);
       assert(!new_module->owner());
       assert(new_module->subckt());
       assert(new_module->subckt()->is_empty());	
       new_module = parse_module(cmd, new_module);
       std::list<CARD*>::iterator ci;
       while(counter>=0){
				for (ci=new_module->subckt()->begin(); ci!=new_module->subckt()->end(); ++ci) {
						//TODO:Iterate over the whole body,read and then execute each command one by one.
				}
				counter--;
			}
			 
}
 
MODEL_SUBCKT* parse_module(CS& cmd, MODEL_SUBCKT* x)
{
   assert(x);
   for (;;) {
		  cmd.get_line(">");
     if (cmd >> "end ") {
       break;
     }else{
       new__instance(cmd, x, x->subckt());
    }
   }
   return x;
}

void new__instance(CS& cmd, MODEL_SUBCKT* owner, CARD_LIST* Scope)
{
  if (cmd.is_end()) {
    // nothing
  }else{
    std::string type = find_type_in_string(cmd);
    if (const CARD* proto = find_proto(type, owner)) {
      CARD* new_instance = proto->clone_instance();
      assert(new_instance);
      new_instance->set_owner(owner);
      CARD* x = parse_item(cmd, new_instance);
      if (x) {
	assert(Scope);
	Scope->push_back(x);
      }else{
      }
    }else{
      cmd.warn(bDANGER, type + ": no match");
    }
  }
}

CARD* parse_item(CS& cmd, CARD* c)
{

  if (dynamic_cast<DEV_DOT*>(c)) {
    return parse_command(cmd, prechecked_cast<DEV_DOT*>(c));
  }else{untested();
    incomplete();
    unreachable();
    return NULL;
  }
}
		
DEV_DOT* parse_command(CS& cmd, DEV_DOT* x)
{
  assert(x);
  x->set(cmd.fullstring());
  CARD_LIST* scope = (x->owner()) ? x->owner()->subckt() : &CARD_LIST::card_list;

  cmd.reset();
  CMD::cmdproc(cmd, scope);
  delete x;
  return NULL;
}

const CARD* find_proto(const std::string& Name, const CARD* Scope)
{
  const CARD* p = NULL;
  if (Scope) {
    try {
      p = Scope->find_looking_out(Name);
    }catch (Exception_Cant_Find& e) {
      assert(!p);
    }
  }else{
    CARD_LIST::const_iterator i = CARD_LIST::card_list.find_(Name);
    if (i != CARD_LIST::card_list.end()) {
      p = *i;
    }else{
      assert(!p);
    }
  }
  
  if (p) {itested();
    return p;
  }else if ((p = command_dispatcher[Name])) {
    return new DEV_DOT;
  }else if ((p = device_dispatcher[Name])) {
    return p;
  }else if ((p = model_dispatcher[Name])) {
    return p;
  }else{
    assert(!p);
    std::string s;
    /* */if (Umatch(Name, "b{uild} "))      {itested();  s = "build";}
    else if (Umatch(Name, "del{ete} "))     {            s = "delete";}
    else if (Umatch(Name, "fo{urier} "))    {            s = "fourier";}
    else if (Umatch(Name, "gen{erator} "))  {            s = "generator";}
    else if (Umatch(Name, "inc{lude} "))    {itested();  s = "include";}
    else if (Umatch(Name, "l{ist} "))       {            s = "list";}
    else if (Umatch(Name, "m{odify} "))     {            s = "modify";}
    else if (Umatch(Name, "opt{ions} "))    {            s = "options";}
    else if (Umatch(Name, "par{ameter} "))  {            s = "param";}
    else if (Umatch(Name, "pr{int} "))      {            s = "print";}
    else if (Umatch(Name, "q{uit} "))       {            s = "quit";}
    else if (Umatch(Name, "st{atus} "))     {            s = "status";}
    else if (Umatch(Name, "te{mperature} ")){untested(); s = "temperature";}
    else if (Umatch(Name, "tr{ansient} "))  {            s = "transient";}
    else if (Umatch(Name, "!"))             {untested(); s = "system";}
    else if (Umatch(Name, "<"))             {untested(); s = "<";}
    else if (Umatch(Name, ">"))             {untested(); s = ">";}
    else{
      s = Name;
    }
    if ((command_dispatcher[s])) {
      return new DEV_DOT;
    }else{
      return NULL;
    }
  }
}

std::string find_type_in_string(CS& cmd)
{
  unsigned here = cmd.cursor();
  std::string type;
  if ((cmd >> "//")) {
    assert(here == 0);
    type = "dev_comment";
  }else{
    cmd >> type;
  }
  cmd.reset(here);
  return type;
}

}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"repeat",&p);
/*-------------------------------------------------------------------*/
}
