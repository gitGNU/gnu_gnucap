/*                                 -*- C++ -*-
 * Copyright (C) 2014 Felix Salfelder
 * Author: Felix Salfelder
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
#include "c_comand.h"
#include "u_parameter.h"
#include "globals.h"
#include "m_wave.h"
#include "u_sim_data.h"
/*--------------------------------------------------------------------------*/
namespace {

using std::map;
using std::string;
using std::max;
#define endl '\n'
/*--------------------------------------------------------------------------*/
class CMD_WAVE : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST* scope)
  {
    if (cmd.is_end()) {incomplete();
    }else if (cmd.umatch("clear ")) {untested();
      clear();
    }else{
      incomplete();
    }
  }
private:
  void clear(){
    for(DISPATCHER<WAVELIST>::iterator i=wavelist_dispatcher.begin();
	i!=wavelist_dispatcher.end(); ++i){
      WAVELIST* w = dynamic_cast<WAVELIST*>(i->second);
      assert(w);
      delete w;
      trace0(("WL cleanup " + i->first).c_str());
      i->second = NULL;
    }
  }
#if 0 // later
  void dumpwaves(CS& cmd, const WAVELIST* wl)
  {
    OMSTREAM out = IO::mstdout;
    out.setfloatwidth(OPT::numdgt, OPT::numdgt+6);
    out.outset(cmd);
    std::pair<const WAVE*, WAVE::const_iterator> Wit[wl->size()];
    std::pair<const WAVE*, WAVE::const_iterator>* ws = &Wit[0];

    int width = std::min(OPT::numdgt+5, BIGBUFLEN-10);
    char format[20];
    //sprintf(format, "%%c%%-%u.%us", width, width);
    sprintf(format, "%%c%%-%us", width);
    out.form(format, '#', "key");

    for(const auto& x : *wl){
      out.form(format, ' ', x.first.c_str());
      *ws = std::pair<const WAVE*, WAVE::const_iterator>(&x.second, x.second.begin());
      ++ws;
    }
    out << endl;

    while(true){
      double key = inf;
      for( std::pair<const WAVE*, WAVE::const_iterator> x : Wit ){
	trace5("found key", *(Wit[0].second), x.first->size(), *x.first->begin(), *x.second, x.second->first);

	if(x.second == x.first->end()){
	}else if (x.second->first <= key) {
	  key = x.second->first;
	}else{untested();
	}
      }
      if(key==inf){
	break;
      }
      out << key;
      for( auto& x : Wit ){
	if(x.second == x.first->end()){
	  out << NOT_VALID;
	}else{
	  out << x.first->v_out(key).f0; // fixme: pass iterator
	  if(x.second->first == key) {
	    ++(x.second);
	  }else{untested();
	  }
	}

      }

      out << endl;
    }
  }

  void dump(CS& cmd, CARD_LIST*)
  {
    string what;
    unsigned here=cmd.cursor();
    cmd >> what; // >> what_else >> whatnot ... FIXME dump multiple waves
    // trace1("dump", what);
    const WAVELIST* wl = CKT_BASE::find_waves(what);
    if (wl){
      dumpwaves(cmd, wl);
    }else if( const WAVE* w = CKT_BASE::find_wave(what)) {
      OMSTREAM out = IO::mstdout;
      out.setfloatwidth(OPT::numdgt, OPT::numdgt+6);
      out.outset(cmd);
      error(bTRACE, "dumping " + what + "\n");
      for(auto pair : *w){
	out << pair.first << pair.second << endl;
      }
    }else{
      cmd.reset(here);
      cmd.warn(bWARNING, "what's this?");
    }

  }
  void list(CS& cmd, CARD_LIST*)
  {
    string what;
    string comma;
    cmd >> what;
    if(what!=""){
      WAVELIST* w = CKT_BASE::find_waves(what);
      if(w){
	for (auto i : *w){
	  IO::mstdout << comma << i.first << " (" << i.second.size() << ")";
	  comma = ",\n";
	}
	IO::mstdout << endl;
      }else{incomplete();
      }
    }else{
      for (auto i : _sim->_waves){
	IO::mstdout << comma;
	if(_sim->_label == i.first){
	  IO::mstdout << "*";
	}
	IO::mstdout << i.first;
	assert(CKT_BASE::find_waves(i.first));
	IO::mstdout << " (" << i.second.size() << ")";
	comma = ", ";
      }
      IO::mstdout << endl;
    }
  }
  void build(CS& cmd, CARD_LIST*)
  {
    string file_name;
    string coll_name;
    CS* input = &cmd;
    bool file = false;
    if(!cmd.match1("<")){
      cmd >> coll_name;
    }else{itested();
    }
    if(cmd.umatch("<")){ itested();
      cmd >> file_name;
      if(coll_name==""){ itested();
	coll_name = file_name;
      }
      trace1("wave", file_name);
      input = new CS(CS::_INC_FILE, file_name);
      file = true;
    }else if(coll_name==""){
      cmd.warn(bDANGER, "need name");
      return;
    }

    WAVELIST& wl = create_waves(coll_name);
    std::forward_list<WAVE*> wp;
    auto before_end = wp.before_begin();

    input->get_line("wave-head>");
    if(input->match1('#')){
      string name;
      *input >> name; // discard
      name = input->ctos("","","","");
      while(*input){
	if (OPT::case_insensitive) {
	  notstd::to_upper(&name);
	}else{untested();
	}
	wp.insert_after(before_end, &wl[name]);
	++before_end;
	name = input->ctos("","","","");
      }
    }else{
      double key, data;
      *input >> key;
      unsigned i = 0;
      while(*input >> data){
	trace2("push head", key, data);
	string name = to_string(i++);
	WAVE* w = &wl[name];
	wp.insert_after(before_end, w);
	++before_end;
	w->push(key, data);
      }
    }
    input->get_line("wave>");

    while(!input->is_end()){
      double key, data;
      *input >> key;
      trace2("line", key, input->fullstring());
      auto p = wp.begin();
      while(p!=wp.end()){
	if(*input >> data){
	  (*p)->push(key,data);
	}else{
	  input->skiparg();
	}
	assert(p!=wp.end());
	++p;
      }
      try{
	input->get_line("wave>");
      }catch (Exception_End_Of_Input& e) { itested();
	break;
      }
    }
    if(file){itested();
      delete input;
      itested();
    }
  }

  void select(CS& cmd, CARD_LIST*)
  {
    string what;
    cmd >> what;
    _sim->_label = what;
  }
#endif
} p5;
/*--------------------------------------------------------------------------*/
DISPATCHER<CMD>::INSTALL d5(&command_dispatcher, "wave", &p5);
/*--------------------------------------------------------------------------*/
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// vim:ts=8:sw=2:noet
