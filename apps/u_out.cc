/*                            -*- C++ -*-
 * Copyright (C) 2015-17 Felix Salfelder
 * Author: Felix Salfelder <felix@salfelder.org>
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
 */

#include "globals.h"
#include "u_out.h"
#include "u_prblst.h"
#include "u_sim_data.h"
#include "ap.h"

/*--------------------------------------------------------------------------*/
OUTPUT::OUTPUT()
{ untested();
}
/*--------------------------------------------------------------------------*/
OUTPUT::~OUTPUT()
{ untested();
}
/*--------------------------------------------------------------------------*/
/* OUTPUT::head: print column headings and draw plot borders
 */
void OUTPUT::head(double, double, const std::string&)
{ incomplete();
  // put legacy here?
}
/*--------------------------------------------------------------------------*/
void OUTPUT::outdata(double x, int y)
{ incomplete();
  // put legacy here?
}
/*--------------------------------------------------------------------------*/
/* OUTPUT::flush: eject data
 */
void OUTPUT::flush()
{ incomplete();
}
#if 0
{
  std::vector<OUTPUT*>::iterator i=_outputs.begin();
  for (; i!=_outputs.end(); ++i){untested();
    (*i)->do_flush();
  }
}
/*--------------------------------------------------------------------------*/
void OUTPUT::purge(CKT_BASE* brh)
{ untested();
  std::vector<OUTPUT*>::iterator i=_outputs.begin();
  for (; i!=_outputs.end(); ++i){untested();
    (*i)->do_purge(brh);
  }
}
#endif
/*--------------------------------------------------------------------------*/
void OUTPUT::do_purge(CKT_BASE* brh)
{ untested();
  incomplete();
//  for (int i = 0;  i < sCOUNT;  ++i) { untested();
//    probelists()[i].remove_one(brh);
//  }
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// ?
OMSTREAM& SIM::out(){return _out;}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// vim:ts=8:sw=2:noet
