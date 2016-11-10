/*                           -*- C++ -*-
 * Copyright (C) 2016 Felix Salfelder
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
 *------------------------------------------------------------------
 * Characters and Strings with optional case (in)sensitivity
 */

#ifndef L_ISTRING_H
#define L_ISTRING_H

/*--------------------------------------------------------------------------*/
#include <map>
#include <string>
#include <assert.h>
#include "u_opt.h"
#include "l_stlextra.h"
#include "io_trace.h"
/*--------------------------------------------------------------------------*/
struct Ichar{
  Ichar() {untested();}
  Ichar(char c) : _c(c) {untested();}
  // Ichar(const Ichar& c) : _c(c._c) {untested();}
  bool operator==(char o) const
  { untested();
    if(OPT::case_insensitive){
      return tolower(_c)==tolower(o);
    }else{
      return o == _c;
    }
  }
  bool operator==(Ichar o) const
  { untested();
    if(OPT::case_insensitive){
      return tolower(_c)==tolower(o);
    }else{
      return o == _c;
    }
  }
  bool operator<(const Ichar& o) const
  { untested();
    return((!OPT::case_insensitive && tolower(_c)==tolower(o._c))
      ? _c<o._c : tolower(_c)<tolower(o._c));
  }
  operator char const&() const{untested(); return _c;}
  operator char&(){untested(); return _c;}
  char _c;
};
/*--------------------------------------------------------------------------*/
class IString : public std::basic_string<Ichar> { //
private:
  typedef std::basic_string<Ichar> base;
public:
  IString() { untested(); }
  IString(const IString& s) : base(s) { untested(); }
  IString(const base& s) : base(s) { untested(); }
  IString(const Ichar* s) : base(s) { untested(); }
public: // construct from conventional types
  IString(const char* s) : base((const Ichar*)s) { untested(); }
  IString(const std::string& s) : base((Ichar const*)s.c_str()) { untested(); }
public: // views
  operator const std::string&() const
  { untested();
    return reinterpret_cast<std::string const&>(*this);
  }
};
/*--------------------------------------------------------------------------*/
inline bool operator==(const IString& s, char c)
{ untested();
  return s.size()==1 && s[0]==c;
}
/*--------------------------------------------------------------------------*/
inline bool operator!=(const IString& s, char c)
{ untested();
  return !(s==c);
}
/*--------------------------------------------------------------------------*/
inline bool operator==(const IString& s, const char* c)
{ untested();
  return s == IString(c);
}
/*--------------------------------------------------------------------------*/
inline bool operator!=(const IString& s, const char* c)
{ untested();
  return !(s==c);
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(IString s, char x)
{ untested();
  return std::string(s) + x;
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(IString s, const char* x)
{ untested();
  return std::string(s) + x;
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(char x, IString s)
{ untested();
  return x + std::string(s);
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(const char* x, IString s)
{ untested();
  return x + std::string(s);
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(IString s, std::string x)
{ untested();
  return std::string(s) + x;
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(std::string x, IString s)
{ untested();
  return x + std::string(s);
}
/*--------------------------------------------------------------------------*/
template<class S>
inline S& operator<< (S& o, const IString& s)
{untested();
  o << std::string(s);
  return o;
}
/*--------------------------------------------------------------------------*/
template<class MAP, class key>
typename MAP::const_iterator find_in_map(MAP const&d, key k)
{ untested();
  // TODO: report close misses and ambiguous matches
  return d.find(k);
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif // guard
// vim:ts=8:sw=2:noet:
