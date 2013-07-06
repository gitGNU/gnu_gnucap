/*$Id: c_strcmp.cc,v 26.133 2013/06/27 04:19:04 al Exp $ -*- C++ -*-
 * Copyright (C) 2013 Rishabh Yadav
 * Author: Rishabh Yadav <rishabh.ece.iitbhu@gmail.com>
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
 * Compares two string and outputs 0 if the two strings are equal otherwise output is the difference of the first non-matching character in string1 by string2.
 */

#include "u_status.h"
#include "c_comand.h"
#include "globals.h"
/*--------------------------------------------------------------------------*/
class CMD_STRCMP : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST*)
  { 
    static int flag;
    std::string s1,s2;
    cmd >> s1 >> s2;
    if((s1== "" or s2== "") || (s1=="--help" && s2==""))
    {
	throw Exception("Usage: strcmp string1 string2\nOutput Value:output variable flag is 0 if the two strings are equal otherwise output is the difference of the first non-matching character in string1 and string2");
    }
    int i=0;
    while(s1[i]!='\0' || s2[i]!='\0')
    {
          flag=s1[i]-s2[i++];
          if(flag)
             break;
      
    }
    IO::mstdout<<"flag="<<flag<<"\n";

}
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher, "strcmp", &p);


