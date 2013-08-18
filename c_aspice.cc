/*$Id: c_aspice.cc,v 26.138 2013/08/29 01:40:53 al Exp $ -*- C++ -*-
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
 *------------------------------------------------------------------*/

#include "globals.h"
#include "c_comand.h"

/*-------------------------------------------------------------------*/
class CMD_ASPICE : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* Scope) {itested();
      std::string input_file,output_file,mode,operation;
      cmd >>input_file >>output_file;
      if(input_file=="" or output_file =="")
             throw Exception("Usage: aspice input_file output_file");
      char *x = new char[std::max(output_file.length(),input_file.length())+1+1];//1+1 for length of ">" and space.
      sprintf(x,"> %s",output_file.c_str());
      operation = x;
      CMD::command(operation,Scope);
      sprintf(x,"< %s",input_file.c_str());
      operation = x;
      CMD::command(operation,Scope);
      CMD::command(">",Scope);
      delete[] x;
     }
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"aspice",&p);

/*-------------------------------------------------------------------*/
