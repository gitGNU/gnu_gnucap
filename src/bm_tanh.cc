/*$Id: bm_tanh.cc,v 21.14 2002/03/26 09:20:25 al Exp $ -*- C++ -*-
 * Copyright (C) 2001 Albert Davis
 * Author: Albert Davis <aldavis@ieee.org>
 *
 * This file is part of "Gnucap", the Gnu Circuit Analysis Package
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *------------------------------------------------------------------
 * behavioral modeling hyperbolic tangent
 */
#include "ap.h"
#include "bm.h"
/*--------------------------------------------------------------------------*/
EVAL_BM_TANH::EVAL_BM_TANH(int c)
  :EVAL_BM_ACTION_BASE(c),
   _gain(NOT_INPUT),
   _limit(NOT_INPUT)
{
}
/*--------------------------------------------------------------------------*/
EVAL_BM_TANH::EVAL_BM_TANH(const EVAL_BM_TANH& p)
  :EVAL_BM_ACTION_BASE(p),
   _gain(p._gain),
   _limit(p._limit)
{
}
/*--------------------------------------------------------------------------*/
void EVAL_BM_TANH::parse(CS& cmd)
{
  int here = cmd.cursor();
  do{
    double gain=NOT_VALID;
    double limit=NOT_VALID;
    cmd >> gain >> limit;
    {if (cmd.gotit(here)){
      _gain  = gain;
      _limit = limit;
    }else{
      get(cmd, "Gain",	&_gain);
      get(cmd, "Limit",	&_limit);
      parse_base(cmd);
    }}
  }while (cmd.more() && !cmd.stuck(&here));
  parse_base_finish();
}
/*--------------------------------------------------------------------------*/
void EVAL_BM_TANH::print(OMSTREAM& where)const
{
  where << "  " << name()
	<< "  gain=" << _gain
	<< "  limit="<< _limit;
  print_base(where);
}
/*--------------------------------------------------------------------------*/
void EVAL_BM_TANH::tr_eval(ELEMENT* d)const
{
  double x = ioffset(d->_y0.x);
  double aa = x * _gain/_limit;
  double cosine = cosh(aa);
  double f1 = _gain / (cosine*cosine);
  double f0 = _limit * tanh(aa);
  d->_y0 = FPOLY1(x, f0, f1);
  tr_final_adjust(&(d->_y0), d->f_is_value());
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
