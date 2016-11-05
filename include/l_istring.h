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
 * parameter dictionaries for (in) sensitive lookup
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
// TODO: move to l_istring.h (or something like that)
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
#if 0 // redundant, but recheck
namespace mystd{
struct char_traits_Ichar : std::char_traits<Ichar>{
  typedef char_traits<char> base;
  typedef Ichar char_type;
  typedef int int_type;
  typedef std::streamoff off_type;
  typedef std::streampos pos_type;
  static bool lt(const Ichar& a, const Ichar& b)
  { untested();
    return a < b; // use operator< defined above
  }
  static bool eq(const Ichar& a, const Ichar& b)
  { untested();
    return a == b; // use operator== defined above
  }
  static int compare (const char_type* p, const char_type* q, size_t n)
  {untested();
    while (n--) { untested();
      if (!eq(*p,*q)) return lt(*p,*q)?-1:1; ++p; ++q;
    }
    return 0;
  }
  static void copy(Ichar* x, const Ichar* y, size_t s)
  { untested();
    base::copy((char*) x, (char*) y, s);
  }
  static size_t length(const Ichar* x)
  { untested();
    return base::length((char*) x);
  }
};
} // std
#endif
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
  IString(const char* s) : base((Ichar*)s) { untested(); }
  IString(const std::string& s) : base((Ichar*)s.c_str()) { untested(); }
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
  return std::string((char*) s.c_str()) + x;
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(IString s, const char x[])
{ untested();
  return std::string((char*) s.c_str()) + x;
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(char x, IString s)
{ untested();
  return x + std::string((char*) s.c_str());
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(const char* x, IString s)
{ untested();
  return x + std::string((char*) s.c_str());
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(IString s, std::string x)
{ untested();
  return std::string((char*) s.c_str()) + x;
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(std::string x, IString s)
{ untested();
  return x + std::string((char*) s.c_str());
}
/*--------------------------------------------------------------------------*/
template<class S>
inline S& operator<< (S& o, const IString& s)
{untested();
  o << s.c_str();
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
