/*$Id: u_opt.h,v 26.127 2009/11/09 16:06:11 al Exp $ -*- C++ -*-
 * Copyright (C) 2001 Albert Davis
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
 * all the options set by the .options card.
 */
//testing=script,complete 2006.07.14
#ifndef U_OPT_H
#define U_OPT_H
#include "mode.h"
#include "u_opt_base.h"
/*--------------------------------------------------------------------------*/
class CS;
class LANGUAGE;
/*--------------------------------------------------------------------------*/
inline OMSTREAM& operator<<(OMSTREAM& o, method_t t) {
  const std::string s[] = {"unknown", "euler", "euleronly", "trap", "traponly",
		     "gear2", "gear2only", "trapgear", "trapeuler"};
  return (o << s[t]);
}
/*--------------------------------------------------------------------------*/
inline OMSTREAM& operator<<(OMSTREAM& o, order_t t) {
  const std::string s[] = {"", "reverse", "forward", "auto"};
  return (o << s[t]);
}
/*--------------------------------------------------------------------------*/
inline OMSTREAM& operator<<(OMSTREAM& o, phase_t t) {
  const std::string s[] = {"degrees", "radians", "+degrees", "-degrees"};
  return (o << s[t]);
}
/*--------------------------------------------------------------------------*/
inline OMSTREAM& operator<<(OMSTREAM& o, UNITS t) {
  const std::string s[] = {"si", "spice"};
  return (o << s[t]);
}
/*--------------------------------------------------------------------------*/
enum {dsINIT=001, dsRANGE=002, dsDEVLIMIT=004, dsDEVREGION=010, dsREVERSE=020};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
class SET_RUN_MODE {
private:
  RUN_MODE _old_run_mode;
  explicit SET_RUN_MODE() :_old_run_mode(ENV::run_mode) {unreachable();}
public:
  explicit SET_RUN_MODE(RUN_MODE rm)
    :_old_run_mode(ENV::run_mode) 
  {
    ENV::run_mode = rm;
  }
  ~SET_RUN_MODE()
  {
    ENV::run_mode = _old_run_mode;
  }
};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif
// vim:ts=8:sw=2:noet:
