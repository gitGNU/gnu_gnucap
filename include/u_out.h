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
#ifndef U_OUT_H
#define U_OUT_H
#include "s__.h"
#include "u_prblst.h"
/*--------------------------------------------------------------------------*/
class PROBELIST;
// class OUTPUT_CMD;
/*--------------------------------------------------------------------------*/
// attached to SIM, can store probelist, do whatever output.
// here: holds a list of CMD references, which can be OUTPUT_CMD
// OUTPUT_CMD attaches OUTPUT object to SIM.
//
// an OUTPUT_CMD
class INTERFACE OUTPUT {
public: // construct
  OUTPUT();
  virtual ~OUTPUT();
public:
//  /*static*/ OMSTREAM& out(){return SIM::out();} // SIM?!
public:
  PROBE_LISTS* _probelists;
public:
  virtual void outset(OMSTREAM& o){ untested();
    _out = o;
  }
  virtual void head(double,double,const std::string&);
  virtual void outdata(double, int);
  virtual void flush();
  static void purge(CKT_BASE*);
protected:
private: // used?
  void do_purge(CKT_BASE*);
public:
  PROBELIST* probelists();
//  friend class OUTPUT_CMD;
  virtual int flags() const{ unreachable(); 
  return -1; }
protected:
  OMSTREAM _out;
}; // OUTPUT
/*--------------------------------------------------------------------------*/
//bool Get(CS&, const std::string& key, OUTPUT** val);
/*--------------------------------------------------------------------------*/
#endif
// vim:ts=8:sw=2:noet:
