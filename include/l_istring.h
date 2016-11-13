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
  Ichar() : _c('\0') {untested();}
  Ichar(const Ichar& c) : _c(c._c) {untested();}
  explicit Ichar(char c) : _c(c) {untested();}
  bool operator==(char o) const {
    if(OPT::case_insensitive){ untested();
      return tolower(_c)==tolower(o);
    }else if(o==_c){ untested();
      return true;
    }else{ untested();
      return false;
    }
  }
 // bool operator!=(char o) const { untested();
 //   return(!operator==(o));
 // }
  bool operator==(Ichar o) const { untested();
    if(OPT::case_insensitive){ untested();
      return tolower(_c)==tolower(o._c);
    }else{ untested();
      return o._c == _c;
    }
  }
  bool operator!=(Ichar o) const { untested();
    return(!operator==(o));
  }
  bool operator<(const Ichar& o) const { untested();
    return((!OPT::case_insensitive && tolower(_c)==tolower(o._c))
      ? _c<o._c : tolower(_c)<tolower(o._c));
  }
  bool operator>(const Ichar& o) const { untested();
    return((!OPT::case_insensitive && tolower(_c)==tolower(o._c))
      ? _c>o._c : tolower(_c)>tolower(o._c));
  }
  bool operator!() const{ untested();
    return !_c;
  }
  operator bool() const{ untested();
    return _c;
  }
  char const& to_char() const{itested(); return _c;}
  char to_lower() const{untested(); return (char)tolower(_c);}
private:
  char _c;
};
/*--------------------------------------------------------------------------*/
namespace detail{
struct ichar_traits : std::char_traits<Ichar>{
  typedef char_traits<char> base;
  typedef Ichar char_type;
  typedef int int_type;
  typedef std::streamoff off_type;
  typedef std::streampos pos_type;
  // inherited
  // static bool lt(const Ichar& a, const Ichar& b);
  // static bool eq(const Ichar& a, const Ichar& b);
  // static void copy(Ichar* x, const Ichar* y, size_t s);
  // static size_t length(const Ichar* x);

  // compare needs to be different. default to insensitive order.
  // if enabled, use sensitive order as a tie break.
  static int compare (const char_type* p, const char_type* q, size_t)
  { untested();
    typedef enum{
      lt  =-1,
      same=0,
      gt  =1
    }ord_t;
    char_type const* i=p;
    char_type const* j=q;

    ord_t ord=same;
    for(; *i; ++i, ++j){ untested();
      if(*j=='\0'){ untested();
	// a is a proper prefix of b
	ord = gt;
	trace3("done1", (char const*)(p), (char const*)(q), ord);
	return ord;
      }else if(i->to_char()==j->to_char()){ untested();
      }else if(i->to_lower() < j->to_lower()){ untested();
	ord = lt;
	trace3("done2", (char const*)(p), (char const*)(q), ord);
	return ord;
      }else if(j->to_lower() < i->to_lower()){ untested();
	ord = gt;
	trace3("done2", (char const*)(p), (char const*)(q), ord);
	return ord;
      }else if(OPT::case_insensitive){ untested();
      }else if(ord!=same){ untested();
      }else if(i->to_char() == j->to_lower()){ untested();
	ord = gt; // lower case before upper case...
      }else if(i->to_lower() == j->to_char()){ untested();
	ord = lt;
      }else{ untested();
      }
    }
    // b is a prefix of a...
    if(OPT::case_insensitive){ untested();
      ord = (*j=='\0')? same: gt;
    }if(*j=='\0'){ untested();
      // same length. order aAAaa before aaaaa
      trace3("samelen sensitive", (char const*)(p), (char const*)(q), ord);
      // return ord;
    }else{ untested();
      ord = lt;
    }
    trace3("done", (char const*)(p), (char const*)(q), ord);
    return ord;
  }
};
}
/*--------------------------------------------------------------------------*/
class IString : public std::basic_string<Ichar, detail::ichar_traits> { //
private:
  typedef std::basic_string<Ichar, detail::ichar_traits> base;
public:
  IString() { untested(); }
  IString(const IString& s) : base(s) { untested(); }
  IString(const base& s) : base(s) { untested(); }
public: // these are better implicit.
  IString(const char* s) : base((const Ichar*)s) { untested(); }
  IString(const std::string& s) : base((Ichar const*)s.c_str()) { untested(); }
public: // ops
  IString& operator=(const std::string& s){ untested();
    base::operator=(IString(s));
    return *this;
  }
  IString& operator=(const char* s){ untested();
    base::operator=((Ichar const*)s);
    return *this;
  }
  bool operator==(const IString& s) const{ untested();
    return base(*this)==base(s);
  }
  IString& operator+=(const std::string& s){ untested();
    base::operator+=(IString(s));
    return *this;
  }
  bool operator==(char c) const { untested();
    return size()==1 && base::operator[](0).to_char()==c;
  }
  bool operator!=(char c) const { untested();
    return !(*this==c);
  }
  bool operator==(char const* c) const { untested();
    return (*this==IString(c));
  }
  bool operator!=(char const* c) const { untested();
    return !(operator==(c));
  }
public: // more conventional type bridge
  size_type find(char x, size_type y) const { untested();
    return base::find(Ichar(x), y);
  }
  size_type find(char x) const { untested();
    return base::find(Ichar(x));
  }
  size_type find_first_of(char const* x) const { untested();
    return base::find_first_of((Ichar const*)x);
  }
  std::string const& to_string() const
  { untested();
    return reinterpret_cast<std::string const&>(*this);
  }
public: // implicit conversion
 // operator bool() const { untested();
 //   return size();
 // }
//   operator const std::string&() const
//   { untested();
//     return reinterpret_cast<std::string const&>(*this);
//   }
}; // IString
/*--------------------------------------------------------------------------*/
inline std::string operator+(IString s, char x)
{ untested();
  return s.to_string() + x;
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(IString s, const char* x)
{ untested();
  return s.to_string() + x;
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(char x, IString s)
{ untested();
  return x + s.to_string();
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(const char* x, IString s)
{ untested();
    return x + s.to_string();
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(IString s, std::string x)
{ untested();
  return s.to_string() + x;
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(std::string x, IString s)
{ untested();
  return x + s.to_string();
}
/*--------------------------------------------------------------------------*/
inline std::ostream& operator<< (std::ostream& o, IString s)
{untested();
  o << s.to_string();
  return o;
}
/*--------------------------------------------------------------------------*/
inline OMSTREAM& operator<< (OMSTREAM& o, IString s)
{untested();
  o << s.to_string();
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
