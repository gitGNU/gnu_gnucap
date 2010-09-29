/*$Id: mg_main.cc,v 25.92 2006/06/28 15:03:12 al Exp $ -*- C++ -*-
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
#include "mg_out.h"
#include "patchlev.h"
/*global*/ int errorcount = 0;
/*--------------------------------------------------------------------------*/
int main(int argc, char** argv)
{
  {if (argc > 2 && strcmp(argv[1],"-h")==0) {
    for (int i=2; i<argc; ++i) {
      File f(argv[i]);
      make_h_file(f);
    }
  }else if (argc > 2 && strcmp(argv[1],"-cc")==0) {
    for (int i=2; i<argc; ++i) {
      File f(argv[i]);
      make_cc_file(f);
    }
  }else if (argc > 2 && strcmp(argv[1],"-v")==0) {
    std::cerr <<
      "Gnucap model compiler "  PATCHLEVEL  "\n"
      "Part of the Gnu Circuit Analysis Package\n"
      "Never trust any version less than 1.0\n"
      " or any version with a number that looks like a date.\n"
      "Copyright 2001-2003, Albert Davis\n"
      "Gnucap comes with ABSOLUTELY NO WARRANTY\n"
      "This is free software, and you are welcome\n"
      "to redistribute it under certain conditions\n"
      "according to the GNU General Public License.\n"
      "See the file \"COPYING\" for details.\n";
  }else if (argc > 1) {
    for (int i=1; i<argc; ++i) {
      File f(argv[i]);
      make_h_file(f);
      make_cc_file(f);
    }
  }else{
    error("no input files");
  }}
  return errorcount;
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
