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

#include "c_comand.h"
#include "globals.h"
#include "e_base.h"
#include "u_sim_data.h"

/*--------------------------------------------------------------------------*/
class CMD_AA : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* )
  {
    std::string mode,filename;
    cmd >> filename;
    unsigned size_aa = _sim->_aa.size();
    unsigned size_lu = _sim->_lu.size();
    if(!size_aa) throw Exception(".");
    IO::mstdout.setfloatwidth(4);
    if (filename!= ""){
      FILE *fptr;
      fptr = fopen(filename.c_str(),"a+");
      if (!fptr) throw Exception("Unable to open or create file.");
      fprintf(fptr,"DC-Tran matrix before LU decomposition:\n");
      for(unsigned i=0;i<size_aa;i++){
          for(unsigned j=0;j<size_aa;j++)              
                fprintf(fptr,"%8.6f \t",(_sim->_aa).s(i,j));
           fprintf(fptr,"\n");
       }

      fprintf(fptr,"DC-Tran matrix after LU decomposition:\n");
      for(unsigned i=0;i<size_lu;i++){ 
           for(unsigned j=0;j<size_lu;j++)
                fprintf(fptr,"%8.6f \t",(_sim->_lu).s(i,j));
           fprintf(fptr,"\n");
       }       
      
     }
 
    else{
       IO::mstdout << "DC-Tran matrix before LU decomposition:\n";
       for(unsigned i=0;i<size_aa;i++){
             for(unsigned j=0;j<size_aa;j++)              
                IO::mstdout <<(_sim->_aa).s(i,j)<<"\t\t\t";
           IO::mstdout<<"\n";
       }

     IO::mstdout << "DC-Tran matrix after LU decomposition:\n";
     for(unsigned i=0;i<size_lu;i++){ 
           for(unsigned j=0;j<size_lu;j++)
                IO::mstdout << (_sim->_lu).s(i,j) <<"\t\t\t";
           IO::mstdout<<"\n";
       }       
    } 
 }
} p;
DISPATCHER<CMD>::INSTALL d3(&command_dispatcher, "mdump", &p);

