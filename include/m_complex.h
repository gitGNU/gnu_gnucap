/*                      -*- C++ -*-
 * Copyright (C) 2017 Felix Salfelder
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
 */

#ifndef M_COMPLEX_H
#define M_COMPLEX_H
/*--------------------------------------------------------------------------*/
#include <complex>
/*--------------------------------------------------------------------------*/
class COMPLEX{
public:
  COMPLEX() { untested();
  }
  COMPLEX(double real, double imag=0)
	  : _r(real), _i(imag)
  { untested();
  }
  double const& real() const{return _r;}
  double const& imag() const{return _i;}
  double& real(){return _r;}
  double& imag(){return _i;}
public: // assign
  double& real(double r){untested();
	  return _r=r;
  }
  double& imag(double i){untested();
	  return _i=i;
  }
public: // op
  bool operator==(COMPLEX const& c) const{ untested();
    return _r==c._r && _i==c._i;
  }
  bool operator==(double const& d) const{ untested();
    return _i==0. && _r==d;
  }
  bool operator!=(double const& d) const{ untested();
    return !operator==(d);
  }
private:
  double _r;
  double _i;
};
/*--------------------------------------------------------------------------*/
inline double real(COMPLEX const& a)
{ untested();
  return a.real();
}
/*--------------------------------------------------------------------------*/
inline double imag(COMPLEX const& a)
{ untested();
  return a.imag();
}
/*--------------------------------------------------------------------------*/
inline COMPLEX operator-(const COMPLEX& a)
{ untested();
  return COMPLEX(-a.real(), -a.imag());
}
/*--------------------------------------------------------------------------*/
inline COMPLEX operator+(COMPLEX a, const COMPLEX& b)
{ untested();
  return COMPLEX(a.real()+b.real(), a.imag()+b.imag());
}
/*--------------------------------------------------------------------------*/
inline COMPLEX operator-(const COMPLEX& a, const COMPLEX& b)
{ untested();
  return -b + a;
}
/*--------------------------------------------------------------------------*/
inline COMPLEX& operator+=(COMPLEX& a, const COMPLEX& b)
{ untested();
  a.real() += b.real();
  a.imag() += b.imag();
  return a;
}
/*--------------------------------------------------------------------------*/
inline COMPLEX operator/(const double& d, const COMPLEX& c)
{ untested();
  double scale=d/(c.real()*c.real() - c.imag()*c.imag());
  return COMPLEX(d*c.real(), -d*c.imag());
}
/*--------------------------------------------------------------------------*/
inline COMPLEX& operator-=(COMPLEX& a, const COMPLEX& b)
{ untested();
  a += -b;
  return a;
}
/*--------------------------------------------------------------------------*/
inline COMPLEX operator/(COMPLEX const& a, COMPLEX const& b)
{ untested();
  double scale=1./(b.real()*b.real() - b.imag()*b.imag());
  double r=scale*(a.real()*b.real() + a.imag()*b.imag());
  double i=scale*(a.imag()*b.real() - a.real()*b.imag());
  return COMPLEX(r, i);
}
/*--------------------------------------------------------------------------*/
inline COMPLEX& operator*=(COMPLEX& a, std::complex<double> const& b)
{ untested();
  double r=a.real()*b.real() - a.imag()*b.imag();
  double i=a.imag()*b.real() + a.real()*b.imag();
  return a=COMPLEX(r, i);
}
/*--------------------------------------------------------------------------*/
inline COMPLEX& operator*=(COMPLEX& a, double const& s)
{ untested();
  a.real() *= s;
  a.imag() *= s;
  return a;
}
/*--------------------------------------------------------------------------*/
inline COMPLEX& operator*=(COMPLEX& a, COMPLEX const& b)
{ untested();
  double r=a.real()*b.real() - a.imag()*b.imag();
  double i=a.imag()*b.real() + a.real()*b.imag();
  return a=COMPLEX(r, i);
}
/*--------------------------------------------------------------------------*/
inline COMPLEX& operator/=(COMPLEX& a, COMPLEX const& b)
{ untested();
  double scale=1./(b.real()*b.real() - b.imag()*b.imag());
  double r=scale*(a.real()*b.real() + a.imag()*b.imag());
  double i=scale*(a.imag()*b.real() - a.real()*b.imag());
  return a=COMPLEX(r, i);
}
/*--------------------------------------------------------------------------*/
inline COMPLEX& operator/=(COMPLEX& a, int n)
{ untested();
  a.real() /= n;
  a.imag() /= n;
  return a;
}
/*--------------------------------------------------------------------------*/
inline COMPLEX operator*(double s, COMPLEX b)
{ untested();
  b *= s;
  return b;
}
/*--------------------------------------------------------------------------*/
inline COMPLEX operator*(const COMPLEX& b, double s)
{ untested();
  return s * b;
}
/*--------------------------------------------------------------------------*/
inline COMPLEX operator*(COMPLEX a, const COMPLEX& b)
{ untested();
  return COMPLEX(a.real()*b.real() - a.imag()+b.imag(),
                 a.real()*b.imag() + a.imag()*b.real());
}
/*--------------------------------------------------------------------------*/
inline COMPLEX conj(COMPLEX const& a)
{
  COMPLEX c(a.real(), -a.imag());
}
/*--------------------------------------------------------------------------*/
inline void swap(COMPLEX& a, COMPLEX& b)
{ untested();
  std::swap(a, b);
}
/*--------------------------------------------------------------------------*/
inline double abs(COMPLEX const& a)
{ untested();
  return std::abs(std::complex<double>(a.real(), a.imag()));
}
/*--------------------------------------------------------------------------*/
inline double arg(COMPLEX const& a)
{ untested();
  return std::arg(std::complex<double>(a.real(), a.imag()));
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif

// vim:ts=8:sw=2:noet:
