/*$Id: c_mul_commands.cc,v 26.138 2013/07/26 09:41:00 al Exp $ -*- C++ -*-
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
 *--------------------------------------------------------------------------
 * ":" issued with multiple commands separated by semi-colon runs the commands one by one.
 */

/*---------------------------------------------------------------------------------*/
#include <gnucap/c_comand.h>
#include <gnucap/globals.h>
#include <iostream>
#include <string>
/*----------------------------------------------------------------------------------*/
namespace {
/*----------------------------------------------------------------------------------*/
class CMD_SYSTEM : public CMD
{
public:
  void do_it(CS& cmd,CARD_LIST* Scope){
    std::string commands;
    commands = cmd.tail();
    std::string delim = ";";
    int start = 0U;
    int end = commands.find(delim);
    while (end != std::string::npos){
      CMD::command(commands.substr(start, end - start),Scope);
      start = end + delim.length();
      end = commands.find(delim, start);
    }
    CMD::command(commands.substr(start, end),Scope);
  }
}p;
DISPATCHER<CMD>::INSTALL d3(&command_dispatcher, ":", &p);

/*-------------------------------------------------------------------*/
}
