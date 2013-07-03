/*$Id: c_alias.cc,v 26.133 2013/07/06 23:06:04 al Exp $ -*- C++ -*-
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
 * Creates an alias for command.
 */

#include "c_comand.h"
#include "globals.h"
/*--------------------------------------------------------------------------*/

class CMD_EXEC :public CMD {
private:
  std::string _command_string;
public:
  CMD_EXEC(std::string s)
        : _command_string(s) {
  }
  void do_it(CS& Cmd, CARD_LIST* Scope) {
    command(_command_string + Cmd.tail(), Scope);
  }

};

class CMD_ALIAS : public CMD {
public:
  void do_it(CS& Cmd, CARD_LIST* Scope) {
    std::string alias_name = Cmd.ctos();
    CMD_EXEC* new_command = new CMD_EXEC(Cmd.tail());
    new DISPATCHER<CMD>::INSTALL(&command_dispatcher, alias_name, new_command); 
  }
}alias_command;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher,"alias",&alias_command);

/*-------------------------------------------------------------------------------*/

