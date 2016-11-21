/*                           -*- C++ -*-
 * Copyright (C) 2016 Felix Salfelder
 * Authors: Felix Salfelder <felix@salfelder.org>
 *          Albert Davis <aldavis@gnu.org>
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
  static int compare_old (const char_type* p, const char_type* q, size_t)
  {
    typedef enum{
      lt  =-1,
      same=0,
      gt  =1
    }ord_t;
    char_type const* i=p;
    char_type const* j=q;

    ord_t ret = same;
    ord_t try_ord = same;
    for (;;) {
      if (!*i && !*j) {
	// both end, matched
	ret =  (OPT::case_insensitive) ? same : try_ord;
	break;
      }else if (*i == *j) {
	// sensitive match, move on
	++i;
	++j;
      }else if (i->to_lower() == j->to_lower()) {
	// insensitive match, move on, but remember
	if (try_ord==same){ itested();
	  try_ord = (*i < *j) ? lt : gt;
	}else{ untested();
	  // don't touch. the left most difference decides
	}
	++i;
	++j;
      }else if (*i < *j) {
	// includes *i, p ends
	ret =  lt;
	break;
      }else if (*i > *j) {
	// includes *j, q ends
	ret =  gt;
	break;
      }else{untested();
	unreachable();
	break;
      }
    }

    return ret;
  }
  // return +-1 if substrings compare to less or more.
  // zero means, they are equal
  // result multiplied by two if tie break is not required.
  static int compare_new (const char_type* i, const char_type* j, size_t n)
  {
    typedef enum{
      lt  =-1,
      same=0,
      gt  =1
    }ord_t;

    ord_t try_ord = same;
    for (unsigned I=0; I<n; ++I) {
      assert (*i!='\0');
      assert (*j!='\0');

      if (i->to_char() == j->to_char()) {
	// sensitive match, move on
	++i;
	++j;
      }else if (i->to_char() == j->to_lower()) {
	// insensitive match, move on, but remember
	if (try_ord==same){ itested();
	  try_ord = gt;
	}else{ itested();
	  // don't touch. the left most difference decides
	}
	++i;
	++j;
      }else if (i->to_lower() == j->to_char()) {
	// insensitive match, move on, but remember
	if (try_ord==same){ itested();
	  try_ord = lt;
	}else{ itested();
	  // don't touch. the left most difference decides
	}
	++i;
	++j;
      }else if (*i < *j) {
	return 2*lt;
      }else{
	assert (*i > *j);
	return 2*gt;
      }
    }

    return (OPT::case_insensitive)? same : try_ord;
  }
  static int compare (const char_type* p, const char_type* q, size_t n){
    int ret=compare_new(p, q, n);
    assert(!ret || ret * compare_old(p, q, n) > 0);
    return ret;
  }
};
}
/*--------------------------------------------------------------------------*/
class IString : public std::basic_string<Ichar, detail::ichar_traits> { //
private:
  typedef std::basic_string<Ichar, detail::ichar_traits> base;
public: // construct
  IString() {}
  IString(const IString& s) : base(s) {}
  IString(const base& s) : base(s) {}
  IString(const char* s) : base((const Ichar*)s) {}
  IString(const std::string& s) :
    base(reinterpret_cast<const IString&>(s)) {}
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
  std::string operator+(char x) const
  { untested();
    return to_string() + x;
  }
  std::string operator+(const char* x) const
  { untested();
    return to_string() + x;
  }
  std::string operator+(std::string x) const
  {
    return to_string() + x;
  }
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
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
public: // explicit conversion
  std::string const& to_string() const
  {
    return reinterpret_cast<std::string const&>(*this);
  }
public: // more compare logic
  int compare(const IString& str) const
  { itested();
    const size_type size = this->size();
    const size_type osize = str.size();
    const size_type len = std::min(size, osize);

    int r = traits_type::compare(data(), str.data(), len);
    trace1("strcmp", *this);
    trace3("strcmp", str, len, r);
    if (r == 2 || r == -2){ untested();
      // traits_type::compare is really sure
      return r;
    }else if(size == osize){
      // same length, use tie break
      return r;
    }else if(size < osize){
      return -1;
    }else{
      assert(size > osize);
      return 1;
    }
  }
}; // IString
/*--------------------------------------------------------------------------*/
inline bool operator<(const IString& lhs, const IString& rhs)
{ itested();
  return lhs.compare(rhs) < 0;
}
/*--------------------------------------------------------------------------*/
template<typename CharT>
inline bool operator<(const IString lhs, const CharT* rhs)
{ untested();
  return lhs.compare(rhs) < 0;
}
/*--------------------------------------------------------------------------*/
inline bool operator>(const IString& lhs, const IString& rhs)
{ untested();
  return lhs.compare(rhs) > 0;
}
/*--------------------------------------------------------------------------*/
template<typename CharT>
inline bool operator>(const IString lhs, const CharT* rhs)
{ untested();
  return lhs.compare(rhs) > 0;
}
/*--------------------------------------------------------------------------*/
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
// no implicit conversion, need *match wrappers.
inline bool Umatch(const char*s, const std::string&t)
{ untested();
  return Umatch(std::string(s), t);
}
/*--------------------------------------------------------------------------*/
inline bool Umatch(const IString&s, const std::string&t)
{ untested();
  return Umatch(s.to_string(), t);
}
/*--------------------------------------------------------------------------*/
inline bool wmatch(const IString& s1, const IString& s2)
{ untested();
  return wmatch(s1.to_string(), s2.to_string());
}
/*--------------------------------------------------------------------------*/
template<class MAP, class key>
inline typename MAP::const_iterator find_in_map(MAP const&d, key k)
{
  // later: report close misses and ambiguous matches
  return d.find(k);
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif // guard
// vim:ts=8:sw=2:noet:
