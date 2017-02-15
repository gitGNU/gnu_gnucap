/*$Id: c_prbcmd.cc,v 26.137 2010/04/10 02:37:05 al Exp $ -*- C++ -*-
 * Copyright (C) 2001 Albert Davis
 *               2015-17 Felix Salfelder
 * Author: Albert Davis <aldavis@gnu.org>
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
 * probe and plot commands
 * set up print and plot (select points, maintain probe lists)
 * command line operations
 */
#include "u_sim_data.h"
#include "c_comand.h"
#include "u_prblst.h"
#include "globals.h"
#include "m_wave.h"
#include "m_phase.h"
#include "u_out.h"
#include "declare.h"
#include "s__.h"
/*--------------------------------------------------------------------------*/
namespace {
/*--------------------------------------------------------------------------*/
class OUTPUT_CMD;
/*--------------------------------------------------------------------------*/
// SIM sends output to TEE, TEE passes on to OUTPUT_CMD
class INTERFACE OUTPUT_TEE : public OUTPUT {
public:
  typedef std::map<OUTPUT_TEE*, std::string> name_map;
  typedef name_map::const_iterator const_iterator;
protected:
  OUTPUT_TEE(){}
private:
  std::map<OUTPUT_CMD*, PROBELIST*> _m;
public:
  PROBELIST& probelist(OUTPUT_CMD* x);
  static const_iterator begin(){ return _n.begin(); }
  static const_iterator end(){ return _n.end(); }

public:
  static PROBELIST* setup(CS&, OUTPUT_CMD*);
public: // OUTPUT
  void outdata(double, int);
  void head(double,double,const std::string&);
  void flush(){ untested(); }
private:
  typedef std::list<OUTPUT_TEE> teecontainer_t;
  static teecontainer_t _tees;
  static name_map _n;
};
/*--------------------------------------------------------------------------*/
OUTPUT_TEE::teecontainer_t OUTPUT_TEE::_tees;
// simcommands do not seem to have canonical names (yet?)
OUTPUT_TEE::name_map OUTPUT_TEE::_n;
/*--------------------------------------------------------------------------*/
PROBELIST* OUTPUT_TEE::setup(CS& cmd, OUTPUT_CMD* oc)
{ untested();
  trace1("setup", cmd.tail());
    unsigned here = cmd.cursor();
    std::string s;
    cmd >> s;
  CMD* c=command_dispatcher[s];
  if(!c){ untested();
    cmd.reset(here);
    return NULL;
  }else if(!dynamic_cast<SIM*>(c)){ untested();
    cmd.reset(here);
    return NULL;
  }else{ untested();
    SIM* sim=prechecked_cast<SIM*>(c);
    if(!sim->output()){ untested();
      _tees.push_back(OUTPUT_TEE());
      OUTPUT_TEE* t=&_tees.back();
      sim->attach_output(t);
      t->_n[t] = s;
      return &(t->probelist(oc));
    }else if(OUTPUT_TEE* t=dynamic_cast<OUTPUT_TEE*>(sim->output())){ untested();
      // already attached.
      return &(t->probelist(oc));
    }else{ untested();
      // something different. leave alone.
      incomplete();
      return NULL;
    }
  }
}
/*--------------------------------------------------------------------------*/
class INTERFACE OUTPUT_CMD : public OUTPUT, public CMD {
public:
  enum OUTFLAGS {
    ofPRINT = 1,
    ofSTORE = 2
  };
private:
  OUTPUT_CMD(const OUTPUT_CMD&) : OUTPUT(), CMD() {unreachable();}
protected:
  OUTPUT_CMD() : OUTPUT() {unreachable();}
public:
  virtual void do_head(double, double,
      const std::string&, PROBELIST const&){ untested();
  }
  virtual void do_outdata(double, PROBELIST const&){unreachable();}
  virtual void do_flush(){unreachable();}
public:
  void do_it(CS& cmd, CARD_LIST*);
protected:
  OUTPUT_CMD(std::string name, int flags);
protected:
//  PROBELIST* probes();
public: //?
  PROBELIST const* probes(std::string mode) const{ untested();
    auto p=_map.find(mode);
    if(p==_map.end()){ untested();
      return NULL;
    }else{ untested();
      return p->second;
    }
  }
  PROBELIST* probes(std::string mode){ untested();
    return _map[mode];
  }
//  const PROBELIST& probes() const;

protected:
  int flags() const{return _flags;}
private:
  int _flags;
  std::string _key; // label?
private: // does not fully make sense.
  void	setup(CS&){unreachable();}
  void	sweep(){unreachable();}

  std::map<std::string /*simtype*/, PROBELIST*> _map;

  friend class OUTPUT_TEE;
};
/*--------------------------------------------------------------------------*/
PROBELIST& OUTPUT_TEE::probelist(OUTPUT_CMD* x)
{ untested();
  if(_m.find(x)==_m.end()){
    trace2("installing probelist", _n[this], x->short_label());
    std::string reason=x->short_label()+":"+_n[this];

    assert(CKT_BASE::_probe_lists);
    _m[x] = CKT_BASE::_probe_lists->install(reason);
  }else{
  }
  return *_m[x];
}
/*--------------------------------------------------------------------------*/
void OUTPUT_TEE::outdata(double x, int y)
{ untested();
  trace2("TEE, out", _m.size(), x);
  for(auto const& p : _m){ untested();
    if(p.first->flags() & y){ untested();
      p.first->do_outdata(x, *p.second); // hmm, don't pass flags?
    }else{ untested();
    }
  }
}
/*--------------------------------------------------------------------------*/
void OUTPUT_TEE::head(double x, double y, const std::string& l)
{ untested();
  for(auto const& p : _m){ untested();
      p.first->outset(_out);
      p.first->do_head(x, y, l, *p.second);
  }
}
/*--------------------------------------------------------------------------*/
OUTPUT_CMD::OUTPUT_CMD(std::string key, int flags)
  : OUTPUT(), // SIM(),
    _flags(flags)
{ untested();
  set_label(key);

  assert(!_map[key]); // for now. switch to dispatcher?
  // key is "alarm" etc.
//  _map[key] = this;
}
/*--------------------------------------------------------------------------*/
// former do_probe
void OUTPUT_CMD::do_it(CS& cmd, CARD_LIST*)
{ untested();
  CKT_BASE::_sim->set_command_none();
  enum {aADD, aDELETE, aNEW} action;

  if (cmd.match1('-')) {untested();	/* handle .probe - ac ...... */
    action = aDELETE;		/* etc. 		     */
    cmd.skip();
  }else if (cmd.match1('+')) {untested();
    action = aADD;
    cmd.skip();
  }else{			/* no -/+ means clear, but wait for */
    action = aNEW;		/* .probe ac + ..... 		    */
  }				/* which will not clear first	    */

  // cmd is something like "ac", "dc" ...
  // this results in NULL, if there is no SIM registered.
  PROBELIST* probelist = OUTPUT_TEE::setup(cmd, this);

  // "this" is something like "print", "alarm"...
  if (!probelist) { untested();
    // go through all simtypes
    if (cmd.is_end()) { untested();
      // list probes for this output command.
      // forall simulations
      for(auto i=OUTPUT_TEE::begin(); i!=OUTPUT_TEE::end(); ++i){
	auto& pl=i->first->probelist(this);
	pl.listing(i->second);
      }
    }else if (cmd.umatch("clear ")) { untested();
      // clear all
      for(auto i=OUTPUT_TEE::begin(); i!=OUTPUT_TEE::end(); ++i){
	auto& pl=i->first->probelist(this);
	pl.clear();
      }
    }else{itested();				/* error */
      throw Exception_CS("what's this?", cmd);
    }
  }else{ untested();
    //assert(probes);
    if (cmd.is_end()) {untested();		/* list */
      probelist->listing("");
    }else if (cmd.umatch("clear ")) {untested();/* clear */
      probelist->clear();
    }else{					/* add/remove */
      CKT_BASE::_sim->init();
      if (cmd.match1('-')) {itested();		/* setup cases like: */
	action = aDELETE;			/* .probe ac + ....  */
	cmd.skip();
      }else if (cmd.match1('+')) { untested();
	action = aADD;
	cmd.skip();
      }else{ untested();
      }
      if (action == aNEW) {			/* no +/- here or at beg. */
	probelist->clear();		/* means clear first	  */
	action = aADD;
      }else{ untested();
      }
      while (cmd.more()) {			/* do-it */
	if (cmd.match1('-')) {			/* handle cases like:	    */
	  action = aDELETE;			/* .pr ac +v(7) -e(6) +r(8) */
	  cmd.skip();
	}else if (cmd.match1('+')) {itested();
	  action = aADD;
	  cmd.skip();
	}else{ untested();
	}
	if (action == aDELETE) { untested();
	  probelist->remove_list(cmd);
	}else{ untested();
	  probelist->add_list(cmd);
	}
      }
    }
  }
}
/*--------------------------------------------------------------------------*/
class CMD_STORE : public OUTPUT_CMD {
public:
  CMD_STORE() : OUTPUT_CMD("store", OUTPUT_CMD::ofSTORE) {}
public:
/* fo_head: print output header
 * arg is index into probe array, to select probe name
 */

  void do_head(double, double, const std::string&, PROBELIST const& pr)
  { untested();
    SIM_DATA* _sim = CKT_BASE::_sim;
    WAVELIST* wl = wavelist_dispatcher[_sim->_label];
    if(!wl){ untested();
      wl = new WAVELIST;
      // BUG. uninstall somewhere.
      wavelist_dispatcher.install(_sim->_label, wl);
    }

    _wavep = new WAVE*[pr.size()];

    unsigned ii = 0;
    for (PROBELIST::const_iterator
	p=pr.begin(); p!=pr.end(); ++p) { untested();
      WAVELIST* wls = wavelist_dispatcher[_sim->_label];
      assert(wls);
      WAVE* w = (*wls)[p->label()];
      if(!w){ untested();
	w = new WAVE;
	wls->install(p->label(), w);
      }else{ untested();
	w->initialize();
      }
      _wavep[ii] = w;
      ++ii;
    }
  }
  void do_outdata(double x, PROBELIST const& pr)
  { untested();
    trace1("store out", pr.size());
    int ii = 0;
    { untested();
      for (PROBELIST::const_iterator
	  p=pr.begin(); p!=pr.end(); ++p) { untested();
	_wavep[ii++]->push(x, p->value());
      }
    }
  }
private:
  WAVE** _wavep;
} p0;
DISPATCHER<CMD>::INSTALL d0(&command_dispatcher, "store", &p0);
/*--------------------------------------------------------------------------*/
/* ALARM: print a message when a probe is out of range
 */
class CMD_ALARM : public OUTPUT_CMD {
public:
  CMD_ALARM() : OUTPUT_CMD("alarm", ofSTORE) {}
public:
  void do_outdata(double, PROBELIST const& prb)
  { untested();
    OUTPUT::_out.setfloatwidth(OPT::numdgt, OPT::numdgt+6);
    // if(m & SIM::ofPRINT ... )?
    for (PROBELIST::const_iterator
	   p=prb.begin();  p!=prb.end();  ++p) { untested();
      if (!p->in_range()) { untested();
	OUTPUT::_out << p->label() << '=' << p->value() << '\n';
      }else{ untested();
      }
    }
  }
} p1;
DISPATCHER<CMD>::INSTALL d1(&command_dispatcher, "alarm", &p1);
/*--------------------------------------------------------------------------*/
class CMD_PLOT : public OUTPUT_CMD {
public:
  CMD_PLOT() : OUTPUT_CMD("plot", ofPRINT) {}
public:
  void do_it(CS& cmd, CARD_LIST* l)
  { untested();
    IO::plotset = true;
    OUTPUT_CMD::do_it(cmd, l);
  }
  void do_head(double start, double stop, const std::string&, PROBELIST const& pr)
  { untested();
    if(!IO::plotout.any()){ untested();
    }else if(pr.size()){ untested();
      plopen(start, stop, pr);
    }
  }
  void do_outdata(double x, PROBELIST const& pr)
  { untested();
    if(!IO::plotout.any()){ untested();
    }else if(pr.size()){ untested();
      plottr(x, pr);
    }else{ untested();
    }
  }
public:
  bool has_probes() const{ untested();
    incomplete();
    PROBELIST const* prb=probes(short_label());
    if(prb){ untested();
      return prb->size();
    }else{ untested();
      return false;
    }
  }
} plt;
DISPATCHER<CMD>::INSTALL d2(&command_dispatcher, "iplot|plot", &plt);
/*--------------------------------------------------------------------------*/
/* CMD_PRINT: print the list of results (text form) to out()
 * The argument is the first column (independent variable, aka "x")
 */
class CMD_PRINT : public OUTPUT_CMD {
private:
  CMD_PRINT(const CMD_PRINT&) : OUTPUT_CMD() { unreachable(); }
public:
  CMD_PRINT() : OUTPUT_CMD("print", ofPRINT) {}
public:
  void do_it(CS& cmd, CARD_LIST* l)
  { untested();
    IO::plotset = false;
    OUTPUT_CMD::do_it(cmd, l);
  }
  void fo_head(const PROBE& Prob)
  { untested();
    OUTPUT::_out.form("# %-10s", Prob.label().c_str())
      << "--------- actual ---------  -------- relative --------\n"
      << "#freq       "
      << "value        dB      phase  value        dB      phase\n";
  }

  // CMD_PRINT::
  void do_head(double start, double stop, const std::string& col1,
      PROBELIST const& p){ untested();
   // if(CKT_BASE::_sim->_mode==s_FOURIER){ untested();
   //   incomplete();
   // }else
    { untested();
      normal_head(start, stop, col1, p);
    }
  }
  void normal_head(double, double, const std::string& col1, PROBELIST const& pr)
  { untested();
    trace1("print head", col1);
   //  if(col1==" "){ untested();
   //    // hack, always print head in op
   //  }else
    if(CKT_BASE::_sim->_mode==s_DC){ untested();
    }else if(CKT_BASE::_sim->_mode==s_OP){ untested();
      // print anyway
    }else if(!pr.size()){ untested();
      return;
    }else if (IO::plotout.any()) { untested(); // hmmm
      return;
    }else{ untested();
    }
    int width = std::min(OPT::numdgt+5, BIGBUFLEN-10);
    char format[20];
    //sprintf(format, "%%c%%-%u.%us", width, width);
    sprintf(format, "%%c%%-%us", width);

    OUTPUT::_out.form(format, '#', col1.c_str());

    for (PROBELIST::const_iterator
	 p=pr.begin(); p!=pr.end(); ++p) { untested();
      OUTPUT::_out.form(format, ' ', p->label().c_str());
    }
    OUTPUT::_out << '\n';
  }
  // CMD_PRINT::
  void do_outdata(double x, PROBELIST const& pr)
  { untested();
    trace1("print outdata", pr.size());

    // if(CKT_BASE::_sim->_mode==s_OP){ untested();
    // }else
    if (IO::plotout.any() /*&& plt.has_probes()*/
      && !(CKT_BASE::_sim->_mode==s_OP)){ untested();
      // this is a hack from s_ac..
    }else{ untested();
      OUTPUT::_out.setfloatwidth(OPT::numdgt, OPT::numdgt+6);
      assert(x != NOT_VALID);
      OUTPUT::_out << x;
      for (PROBELIST::const_iterator
	    p=pr.begin(); p!=pr.end(); ++p) { untested();
	OUTPUT::_out << p->value();
      }
      OUTPUT::_out << '\n';
    }
  }
} p3;
DISPATCHER<CMD>::INSTALL d3(&command_dispatcher, "iprint|print|probe", &p3);
/*--------------------------------------------------------------------------*/
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// vim:ts=8:sw=2:noet:
