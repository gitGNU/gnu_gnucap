/*$Id: c_history.cc,v 26.133 2013/07/01 07:00:04 al Exp $ -*- C++ -*-
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
 * This command prints the System Information which may help users to send bug report to the gnucap developers community.
 * Note:This command doesn't works on Windows.
 */

#include "u_status.h"
#include "c_comand.h"
#include "globals.h"

/*--------------------------------------------------------------------------*/

class CMD_HISTORY : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* Scope)
  {
   itested();
   std::string track;
   FILE *fptr;
   cmd >> track;
   fptr=fopen("history.txt","r+");
   if (track==""){
   itested();
       	if(fptr!=NULL){itested();
       		system("cat history.txt");}
       	else
       		throw Exception("You haven't enabled the history mode to track the commands.\nUsage:history [mode]\n"
   				"-t        Start tracking\n"
   				"-s        Stop tracking");
    }
   else if (track!= "-t" && track!= "-s") {
   itested();
   IO::mstdout<<"Usage:history [mode]\n"
   "-t        Start tracking\n"
   "-s        Stop tracking\n";
   }
   
   else if (track == "-t"){
   	itested();
	CMD::command("log >> history.txt ",Scope); 
   }
 
   else if(track == "-s" && fptr!=NULL){
        OS::system("rm history.txt");
        fclose(fptr);
    }      
}
}p;
DISPATCHER<CMD>::INSTALL d(&command_dispatcher, "history", &p);



