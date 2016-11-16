/*$Id: l_dispatcher.h 2016/03/29 al -*- C++ -*-
 * Copyright (C) 2006 Albert Davis
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
 * dispatcher -- for dynamically loaded modules
 */
//testing=script 2015.01.21
#ifndef L_DISPATCHER_H
#define L_DISPATCHER_H
#include "e_base.h"
#include "ap.h"
/*--------------------------------------------------------------------------*/
class DISPATCHER_BASE {
protected:
  std::map<IString, CKT_BASE*> * _map;
private:
  explicit DISPATCHER_BASE(DISPATCHER_BASE*) {unreachable();incomplete();}
public:
  DISPATCHER_BASE() /*: _map(new std::map<IString, CKT_BASE*>)*/ {
    if (!_map) {
      _map = new std::map<IString, CKT_BASE*>;
    }else{unreachable();
      puts("build error: link order: constructing dispatcher that already has contents\n");
    }    
  }
  ~DISPATCHER_BASE() {
#if !defined(NDEBUG)
    for (typename std::map<IString, CKT_BASE*>::iterator
	 ii = _map->begin();
	 ii != _map->end();
	 ++ii) {
      assert(!(ii->second));
    }
#endif
    delete _map;
    _map = NULL;
  }

  typedef std::map<IString, CKT_BASE*>::const_iterator const_iterator;

  const_iterator begin()const		{assert(_map); return _map->begin();}
  const_iterator end()const		{assert(_map); return _map->end();}

  CKT_BASE* operator[](IString s) {
    assert(_map);
    CKT_BASE* rv = (*_map)[s];
    return rv;
  }
};
/*--------------------------------------------------------------------------*/
template <class TT>
class INTERFACE DISPATCHER : public DISPATCHER_BASE {
public:
  void install(const IString& s, TT* p) {
    assert(s.find(',', 0) == IString::npos);
    if (!_map) {unreachable();
      puts("build error: link order: dispatcher not yet constructed\n");
      _map = new std::map<IString, CKT_BASE*>;
    }else{
    }
    trace0(s.c_str());
    // loop over all keys, separated by '|'
    for (IString::size_type			// bss: begin sub-string
	 bss = 0, ess = s.find('|', bss);	// ess: end sub-string
	 bss != IString::npos;
	 bss = (ess != IString::npos) ? ess+1 : IString::npos,
	   ess = s.find('|', bss)) {
      IString name = s.substr(bss, 
		(ess != IString::npos) ? ess-bss : IString::npos);
      trace2(name.c_str(), bss, ess);
      if (name == "") {untested();
	// quietly ignore empty string
      }else if ((*_map)[name]) {
	// duplicate .. stash the old one so we can get it back
	error(bWARNING, name + ": already installed, replacing\n");
	IString save_name = name + IString(":0");
	for (int ii = 0; (*_map)[save_name]; ++ii) {untested();
	  save_name = name + IString(":") + to_string(ii);
	}
	(*_map)[save_name] = (*_map)[name];	
	error(bWARNING, "stashing as " + save_name + "\n");
      }else{
	// it's new, just put it in
      }
      (*_map)[name] = p;
    }
  }
  
  void uninstall(TT* p) {
    assert(_map);
    for (typename std::map<IString, CKT_BASE*>::iterator
	 ii = _map->begin();
	 ii != _map->end();
	 ++ii) {
      if (ii->second == p) {
	ii->second = NULL;
      }else{
      }
    }
#if !defined(NDEBUG)
    for (typename std::map<IString, CKT_BASE*>::iterator
	 ii = _map->begin();
	 ii != _map->end();
	 ++ii) {
      assert(ii->second != p);
    }
#endif
  }
  
  void uninstall(const IString& s) {untested();
    assert(_map);
    // loop over all keys, separated by '|'
    for (IString::size_type			// bss: begin sub-string
	 bss = 0, ess = s.find('|', bss);	// ess: end sub-string
	 bss != IString::npos;
	 bss = (ess != IString::npos) ? ess+1 : IString::npos,
	   ess = s.find('|', bss)) {untested();
      IString name = s.substr(bss,
		(ess != IString::npos) ? ess-bss : IString::npos);
      if (name == "") {untested();
	// quietly ignore empty string
      }else if ((*_map)[name]) {untested();
	// delete, try to get back the old one
	int ii = 0;
	IString save_name = name + ":0";
	for (ii = 0; (*_map)[save_name]; ++ii) {untested();
	  save_name = name + ":" + to_string(ii);
	}
	if (ii > 1) {untested();
	  save_name = name + ":" + to_string(ii-2);
	  (*_map)[name] = (*_map)[save_name];
	  (*_map)[save_name] = NULL;
	  error(bWARNING, "restoring " + save_name + " as " + name + "\n");
	}else{untested();
	  (*_map)[name] = NULL;
	}
      }else{untested();
	error(bWARNING, name + ": not installed, doing nothing\n");
      }
    }
  }

  TT* operator[](IString s) {
    assert(_map);
    CKT_BASE* rv = (*_map)[s];
    return prechecked_cast<TT*>(rv);
  }

  TT* operator[](CS& cmd) {
    unsigned here = cmd.cursor();
    IString s;
    cmd >> s;
    //------------------------
    TT* p = (*this)[s];
    //------------------------
    if (!p) {
      cmd.reset(here);
    }else{
    }
    return p;
  }

  TT* clone(IString s) {
    TT* proto = (*this)[s];
    if (proto) {
      return proto->clone();
    }else{untested();
      return NULL;
    }
  }

  class INSTALL {
  private:
    const IString _name;
    DISPATCHER<TT>* _d;
    TT* _p;
  public:
    INSTALL(DISPATCHER<TT>* d, const IString& name, TT* p) :
      _name(name),
      _d(d),
      _p(p)
    {
      assert(_d);
      assert(p);
      _d->install(_name, p);
    }
    // // same as above, but cannot delegate yet
    // INSTALL(DISPATCHER<TT>* d, const std::string& name, TT* p) :
    //   _name(IString(name)),
    //   _d(d),
    //   _p(p)
    // {
    //   assert(_d);
    //   assert(p);
    //   _d->install(_name, p);
    // }
    
    ~INSTALL() {
      //_d->uninstall(_name);
      _d->uninstall(_p);
    }
  };
};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif
// vim:ts=8:sw=2:noet:
