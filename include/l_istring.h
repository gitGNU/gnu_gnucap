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
#include "u_opt.h"
/*--------------------------------------------------------------------------*/
struct Ichar{
  Ichar() : _c('\0') {}
  Ichar(const Ichar& c) : _c(c._c) {}
  explicit Ichar(char c) : _c(c) {}
  bool operator==(char o) const {
    if(OPT::case_insensitive){
      return tolower(_c)==tolower(o);
    }else if(o==_c){
      return true;
    }else{
      return false;
    }
  }
 // bool operator!=(char o) const {untested();
 //   return(!operator==(o));
 // }
  bool operator==(Ichar o) const {
    if(OPT::case_insensitive){
      return tolower(_c)==tolower(o._c);
    }else{
      return o._c == _c;
    }
  }
  bool operator!=(char o) const {
    return(!operator==(o));
  }
  bool operator!=(Ichar o) const {
    return(!operator==(o));
  }
  bool operator<(const Ichar& o) const {
    return((!OPT::case_insensitive && tolower(_c)==tolower(o._c))
      ? _c<o._c : tolower(_c)<tolower(o._c));
  }
  bool operator>(const Ichar& o) const {
    return((!OPT::case_insensitive && tolower(_c)==tolower(o._c))
      ? _c>o._c : tolower(_c)>tolower(o._c));
  }
  bool operator!() const{
    return !bool(_c);
  }
  char const& to_char() const{
    return _c;
  }
  char to_lower() const{
    return (char)tolower(_c);
  }
public: //dangerous
//  operator bool() const{untested();
//    return bool(_c);
//  }
private:
  char _c;
};
/*--------------------------------------------------------------------------*/
inline std::ostream& operator<<(std::ostream& o, const Ichar* s)
{untested();
  o << (char const*) s;
  return o;
}
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
  {
    typedef enum{
      lt  =-1,
      same=0,
      gt  =1
    }ord_t;
    char_type const* i=p;
    char_type const* j=q;

    ord_t ret1 = same;
    ord_t try_ord = same;
    for (;;) {
      if (!*i && !*j) {
	// both end, matched
	ret1 =  (OPT::case_insensitive) ? same : try_ord;
	break;
      }else if (*i == *j) {
	// sensitive match, move on
	++i;
	++j;
      }else if (i->to_lower() == j->to_lower()) {
	// insensitive match, move on, but remember
	try_ord = (*i < *j) ? lt : gt;
	++i;
	++j;
      }else if (*i < *j) {
	// includes *i, p ends
	ret1 =  lt;
	break;
      }else if (*i > *j) {
	// includes *j, q ends
	ret1 =  gt;
	break;
      }else{untested();
	unreachable();
	break;
      }
    }

    bool bb=false;
    ord_t ret2 = same;
    ord_t ord=same;
    for(; *i!='\0'; ++i, ++j){
      if(*j=='\0'){
	// a is a proper prefix of b
	ord = gt;
	trace3("done1", (char const*)(p), (char const*)(q), ord);
	ret2 =  ord;
	bb = true;
	break;
      }else if(i->to_char()==j->to_char()){untested();
      }else if(i->to_lower() < j->to_lower()){
	ord = lt;
	trace3("done2", (char const*)(p), (char const*)(q), ord);
	ret2 =  ord;
	bb = true;
	break;
      }else if(j->to_lower() < i->to_lower()){
	ord = gt;
	trace3("done2", (char const*)(p), (char const*)(q), ord);
	ret2 =  ord;
	bb = true;
	break;
      }else if(OPT::case_insensitive){untested();
      }else if(ord!=same){untested();
      }else if(i->to_char() == j->to_lower()){untested();
	ord = gt; // lower case before upper case...
      }else if(i->to_lower() == j->to_char()){untested();
	ord = lt;
      }else{untested();
      }
    }

    if (!bb) {
      // b is a prefix of a...
      if(OPT::case_insensitive){
	ord = (*j=='\0')? same: gt;
      }else{
      }
      if(*j=='\0'){
	// same length. order aAAaa before aaaaa
	trace3("samelen sensitive", (char const*)(p), (char const*)(q), ord);
	// ret2 =  ord;
      }else{
	ord = lt;
      }
      trace3("done", (char const*)(p), (char const*)(q), ord);
      ret2 =  ord;
    }else{
      // early return
    }

    assert (ret1 == ret2);
    return ret1;
  }
};
}
/*--------------------------------------------------------------------------*/
class IString : public std::basic_string<Ichar, detail::ichar_traits> { //
private:
  typedef std::basic_string<Ichar, detail::ichar_traits> base;
public:
  IString() {}
  IString(const IString& s) : base(s) {}
  IString(const base& s) : base(s) {}
public: // these are better implicit.
  IString(const char* s) : base((const Ichar*)s) {}
  IString(const std::string& s) : base((Ichar const*)s.c_str()) {}
public: // ops
  IString& operator=(Ichar s){ untested();
    base::operator=(s);
    return *this;
  }
  IString& operator=(const std::string& s){
    base::operator=(IString(s));
    return *this;
  }
  IString& operator=(const char* s){
    base::operator=((Ichar const*)s);
    return *this;
  }
  bool operator==(const IString& s) const{
    return base(*this)==base(s);
  }
  IString& operator+=(const std::string& s){
    base::operator+=(IString(s));
    return *this;
  }
  bool operator==(char c) const {untested();
    return size()==1 && base::operator[](0).to_char()==c;
  }
  bool operator!=(char c) const {untested();
    return !(*this==c);
  }
  bool operator==(char const* c) const {
    return (*this==IString(c));
  }
  bool operator!=(char const* c) const {
    return !(operator==(c));
  }
public: // more conventional type bridge
  size_type find(char x, size_type y) const {
    return base::find(Ichar(x), y);
  }
  size_type find(char x) const {
    return base::find(Ichar(x));
  }
  size_type find_first_of(char const* x) const {
    return base::find_first_of((Ichar const*)x);
  }
  std::string const& to_string() const
  {
    return reinterpret_cast<std::string const&>(*this);
  }
public: // implicit conversion
 // operator bool() const {untested();
 //   return size();
 // }
//   operator const std::string&() const
//   {untested();
//     return reinterpret_cast<std::string const&>(*this);
//   }
}; // IString
/*--------------------------------------------------------------------------*/
inline std::string operator+(IString s, char x)
{
  return s.to_string() + x;
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(IString s, const char* x)
{
  return s.to_string() + x;
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(char x, IString s)
{
  return x + s.to_string();
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(const char* x, IString s)
{
    return x + s.to_string();
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(IString s, std::string x)
{
  return s.to_string() + x;
}
/*--------------------------------------------------------------------------*/
inline std::string operator+(std::string x, IString s)
{
  return x + s.to_string();
}
/*--------------------------------------------------------------------------*/
inline std::ostream& operator<< (std::ostream& o, IString s)
{
  o << s.to_string();
  return o;
}
/*--------------------------------------------------------------------------*/
inline OMSTREAM& operator<< (OMSTREAM& o, IString s)
{
  o << s.to_string();
  return o;
}
/*--------------------------------------------------------------------------*/
template<class MAP, class key>
typename MAP::const_iterator find_in_map(MAP const&d, key k)
{
  // TODO: report close misses and ambiguous matches
  return d.find(k);
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif // guard
// vim:ts=8:sw=2:noet:
