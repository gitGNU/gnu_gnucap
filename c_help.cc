/*$Id: c_help.cc 2014/08/09 al $ -*- C++ -*-
 * Copyright (C) 2014 Albert Davis
 * Author: Albert Davis <aldavis@gnu.org>
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
 */
//testing=informal
#include "gnucap/l_dispatcher.h"
#include "gnucap/c_comand.h"
#include "gnucap/globals.h"
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
namespace {
/*--------------------------------------------------------------------------*/
  static DISPATCHER<CKT_BASE>* dispatchers[] = {
    reinterpret_cast<DISPATCHER<CKT_BASE>*>(&help_dispatcher),
    reinterpret_cast<DISPATCHER<CKT_BASE>*>(&bm_dispatcher),
    reinterpret_cast<DISPATCHER<CKT_BASE>*>(&function_dispatcher),
    reinterpret_cast<DISPATCHER<CKT_BASE>*>(&measure_dispatcher),
    reinterpret_cast<DISPATCHER<CKT_BASE>*>(&model_dispatcher),
    reinterpret_cast<DISPATCHER<CKT_BASE>*>(&device_dispatcher),
    reinterpret_cast<DISPATCHER<CKT_BASE>*>(&language_dispatcher),
    reinterpret_cast<DISPATCHER<CKT_BASE>*>(&command_dispatcher),
    reinterpret_cast<DISPATCHER<CKT_BASE>*>(&status_dispatcher),
    reinterpret_cast<DISPATCHER<CKT_BASE>*>(&probe_dispatcher),
    NULL };
  // the order here determines the search order
  //BUG// reinterpret_cast is needed because there is not a common base class
  // but they really are all the same.  Fix is needed to provide one in l_dispatcher.h.
/*--------------------------------------------------------------------------*/
class CMD_HELP : public CMD {
public:
  void do_it(CS& Cmd, CARD_LIST*)
  {
    std::string topic;
    Cmd >> topic;

    bool did_something = false;
    unsigned here = Cmd.cursor();
    for (DISPATCHER<CKT_BASE>** ii = dispatchers; *ii; ++ii) {
      CKT_BASE* object = (**ii)[topic];
      if (object) {
	   		did_something = true;
	 			//BUG// help in in CKT_BASE needs to be changed to return bool
	 			// where true means it actually did something
				object->help(Cmd, IO::mstdout);
      }else{
	 			// nothing, it's ok
      }
      Cmd.reset(here);
    }
    if (!did_something) {
      Cmd.warn(bWARNING, here, "no help on " + topic);
    }else{
    }
  }
  
  CS& help_text()const
  {
    static CS ht(CS::_STRING,
	      "help command\n"
	      "Provides help on a variety of topics\n"
	      "Syntax: help topic\n"
	      "In some cases, help on subtopics is available\n"
	      "Syntax: help topic subtopic\n\n"
	      "@@nuts\n"
	      "help nuts\n\n"
	      "@@eggs\n"
	      "help eggs\n\n");
    return ht;
  }

  void help(CS& Cmd, OMSTREAM& Out)const
  {
    std::string keyword;
    Cmd >> keyword;
    Out << help_text().reset().scan("@@" + keyword + ' ').get_to("@@");
    //return true;
  }
} p0;
DISPATCHER<CMD>::INSTALL d0(&command_dispatcher, "help", &p0);
/*--------------------------------------------------------------------------*/
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
