/*$Id: c_mdump.cc,v 26.138 2013/07/20 01:00: al Exp $ -*- C++ -*-
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
 *--------------------------------------------------------------------------
 * mdump commands prints the dc-tran matrix into the console.if the filename is specified then output is redirected to the file.
 */

#include "gnucap/c_comand.h"
#include "gnucap/globals.h"
#include "gnucap/u_sim_data.h"

using namespace std;
/*--------------------------------------------------------------------------*/
class CMD_MDUMP: public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* )
  {
    std::string mode,filename;
    cmd >> filename;
    assert(_sim);
    unsigned size_aa = _sim->_aa.size();//size of matrix before lu decomposition
    unsigned size_lu = _sim->_lu.size();//size of matrix after lu decomposition
    if(!size_aa) throw Exception(".");
    IO::mstdout.setfloatwidth(4);
    if (filename!= ""){
      FILE *fptr;
      fptr = fopen(filename.c_str(),"a+");
      if (!fptr) throw Exception("Unable to open or create file.");
      fprintf(fptr,"DC-Tran matrix before LU decomposition:\n");
      for(unsigned i=1;i<=size_aa;i++){
          for(unsigned j=1;j<=size_aa;j++)              
                fprintf(fptr,"%8.6f \t",(_sim->_aa).s(i,j));
           fprintf(fptr,"\n");
       }

      fprintf(fptr,"DC-Tran matrix after LU decomposition:\n");
      for(unsigned i=1;i<=size_lu;i++){ 
           for(unsigned j=1;j<=size_lu;j++)
                fprintf(fptr,"%8.6f \t",(_sim->_lu).s(i,j));
           fprintf(fptr,"\n");
       }       
      fclose(fptr);
     }
    else{
       IO::mstdout << "DC-Tran matrix before LU decomposition:\n";
       std::string io_s; //formatted string to be printed at console
       for(unsigned i=1;i<=size_aa;i++){
             for(unsigned j=1;j<=size_aa;j++) {     
                io_s = to_string(_sim->_aa.s(i,j));
                io_s.resize(10,' ');     
                IO::mstdout << io_s <<"\t\t\t";
                }
           IO::mstdout<<"\n";
       }

     IO::mstdout << "DC-Tran matrix after LU decomposition:\n";
     for(unsigned i=1;i<=size_lu;i++){ 
           for(unsigned j=1;j<=size_lu;j++){
               io_s = to_string(_sim->_lu.s(i,j));
               io_s.resize(10,' ');
               IO::mstdout << io_s<<"\t\t\t";
               }
           IO::mstdout<<"\n";
       }
     }       
 }
} p;
DISPATCHER<CMD>::INSTALL d3(&command_dispatcher, "mdump", &p);

