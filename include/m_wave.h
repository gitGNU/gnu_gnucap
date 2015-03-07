/*$Id: m_wave.h 2014/11/23$ -*- C++ -*-
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
 * "wave" class, for transmission lines and delays
 */
//testing=script 2006.07.13
#include "l_denoise.h"
#include "m_interp.h"
#include "l_dispatcher.h"
/*--------------------------------------------------------------------------*/
class WAVE : public CKT_BASE {
private:
  std::deque<DPAIR> _w;
  double _delay;
  explicit WAVE(const WAVE&);
public:
  WAVE* clone()const{return new WAVE(*this);}
  typedef std::deque<DPAIR>::iterator iterator;
  typedef std::deque<DPAIR>::const_iterator const_iterator;

  explicit WAVE(double d=0);
	  ~WAVE() {}
  WAVE&	   set_delay(double d);
  WAVE&	   initialize();
  WAVE&	   push(double t, double v);
  FPOLY1   v_out(double t)const;
  double   v_reflect(double t, double v_total)const;
  WAVE&	   operator+=(const WAVE& x);
  WAVE&	   operator+=(double x);
  WAVE&	   operator*=(const WAVE& x);
  WAVE&	   operator*=(double x);
  const_iterator begin()const {return _w.begin();}
  const_iterator end()const {return _w.end();}
};
/*--------------------------------------------------------------------------*/
class WAVELIST : public CKT_BASE, public DISPATCHER_BASE {
  public:
    WAVELIST() : CKT_BASE(), DISPATCHER_BASE() {}
    CKT_BASE* clone(){return new WAVELIST(*this);}

    WAVE* operator[](const std::string& x) {
      WAVE* r = prechecked_cast<WAVE*>((*_map)[x]);
      return r;
    }
    void install(const std::string& s, WAVE* p) {
      if (!_map) {unreachable();
	puts("build error: link order: dispatcher not yet constructed\n");
	_map = new std::map<std::string, CKT_BASE*>;
      }else{
      }
      (*_map)[s] = p;
    }

    ~WAVELIST(){
      for(std::map<std::string, CKT_BASE*>::iterator i=_map->begin(); i!=_map->end(); ++i){
	WAVE* w = dynamic_cast<WAVE*>(i->second);
	assert(w);
	delete w;
	i->second = NULL;
      }
    }
};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// push: insert a signal on the "input" end.
// args: t = the time now
//       v = the value to push
//
inline WAVE& WAVE::push(double t, double v)
{
  _w.push_back(DPAIR(t+_delay, v));
  return *this;
}
/*--------------------------------------------------------------------------*/
// initialize: remove all info, fill it with all 0.
//
inline WAVE& WAVE::initialize()
{
  _w.clear();
  return *this;
}
/*--------------------------------------------------------------------------*/
inline WAVE::WAVE(const WAVE& w)
  :_w(w._w),
   _delay(w._delay)
{ untested();
}
/*--------------------------------------------------------------------------*/
// constructor -- argument is the delay
//
inline WAVE::WAVE(double d)
  :_w(),
   _delay(d)
{
  initialize();
}
/*--------------------------------------------------------------------------*/
inline WAVE& WAVE::set_delay(double d) 
{
  _delay = d; 
  return *this;
}
/*--------------------------------------------------------------------------*/
// v_out: return the value at the "output" end
// args: t = the time now
//
inline FPOLY1 WAVE::v_out(double t)const
{
  return interpolate(_w.begin(), _w.end(), t, 0., 0.);
}
/*--------------------------------------------------------------------------*/
// reflect: calculate a reflection
// args: t = the time now
//       v_total = actual voltage across the termination
// returns: the value (voltage) to send back as the reflection
//
inline double WAVE::v_reflect(double t, double v_total)const
{
  // return (v_total*2 - v_out(t)); // de-noised
  return dn_diff(v_total*2, v_out(t).f0);
}
/*--------------------------------------------------------------------------*/
inline WAVE& WAVE::operator+=(const WAVE& x)
{
  untested();
  for (std::deque<DPAIR>::iterator
	 i = _w.begin(); i != _w.end(); ++i) {
    untested();
    (*i).second += x.v_out((*i).first).f0;
  }
  return *this;
}
/*--------------------------------------------------------------------------*/
inline WAVE& WAVE::operator+=(double x)
{
  untested();
  for (std::deque<DPAIR>::iterator
	 i = _w.begin(); i != _w.end(); ++i) {
    untested();
    (*i).second += x;
  }
  return *this;
}
/*--------------------------------------------------------------------------*/
inline WAVE& WAVE::operator*=(const WAVE& x)
{
  untested();
  for (std::deque<DPAIR>::iterator
	 i = _w.begin(); i != _w.end(); ++i) {
    untested();
    (*i).second *= x.v_out((*i).first).f0;
  }
  return *this;
}
/*--------------------------------------------------------------------------*/
inline WAVE& WAVE::operator*=(double x)
{
  untested();
  for (std::deque<DPAIR>::iterator
	 i = _w.begin(); i != _w.end(); ++i) {
    untested();
    (*i).second *= x;
  }
  return *this;
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// vim:ts=8:sw=2:noet:
