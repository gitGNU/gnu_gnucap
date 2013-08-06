/*$Id: c_rmcirc.cc,v 26.81 2013/06/11 09:34:00 al Exp $ -*- C++ -*-
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
 * rmcirc:removes the current circuit
 */

#include <gnucap/c_comand.h>
#include <gnucap/globals.h>
/*--------------------------------------------------------------------------*/
namespace {
/*--------------------------------------------------------------------------*/
/* cmd_rmcirc: clear the whole circuit, including faults, etc
 *   equivalent to unfault; unkeep; delete all; title = (blank)
 */
class CMD_RMCIRC : public CMD {
public:
  void do_it(CS&, CARD_LIST* Scope)
  {
    command("unfault", Scope);
    command("unmark", Scope);
    command("alarm clear", Scope);
    command("plot clear", Scope);
    command("print clear", Scope);
    command("delete all", Scope);
    command("title '", Scope);
  }
} p0;
DISPATCHER<CMD>::INSTALL d0(&command_dispatcher, "rmcirc", &p0);
/*--------------------------------------------------------------------*/
}
/*--------------------------------------------------------------------*/
