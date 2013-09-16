/*                                                   -*- C++ -*-
 * Copyright (C) 2001 Albert Davis
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
 * dc analysis top
 */
#include "globals.h"
#include "u_status.h"
#include "u_prblst.h"
#include "u_cardst.h"
#include "e_elemnt.h"
#include "s__.h"
/*--------------------------------------------------------------------------*/
namespace {
/*--------------------------------------------------------------------------*/
class DCOP : public SIM {
protected:
  enum STEP_CAUSE {
    scUSER      =  1,	/* user requested				*/
    scSKIP      =  3,	/* effect of "skip" parameter			*/
    scITER_R    =  4,	/* iter count exceeds itl4 (reducing)		*/
    scITER_A    =  5,	/* iter count exceeds itl3 (holding)		*/
    scTE        =  6,	/* truncation error, or device stuff		*/
    scINITIAL   =  9,	/* initial guess				*/
    scREJECT    = 10,	/* rejected previous time step			*/
    scZERO      = 11,	/* fixed zero time step				*/
    scSMALL     = 12,	/* time step too small				*/
    scNO_ADVANCE= 13,	/* after all that it still didn't advance	*/
    scLAST      = 15 	/* last step */
  };
  void	set_step_cause(STEP_CAUSE C) {::status.control = C;}
  STEP_CAUSE step_cause()const {return STEP_CAUSE(::status.control);}
public:
  void	finish();
protected:
  void	fix_args(int);
  void	options(CS&, int);
private:
  void	sweep();
  void	sweep_recursive(int);
  void	first(int);
  bool	next(int);
  explicit DCOP(const DCOP&): SIM() {unreachable(); incomplete();}
protected:
  explicit DCOP();
  ~DCOP() {}
  
protected:
  enum {DCNEST = 4};
  int _n_sweeps;
  PARAMETER<double> _start[DCNEST];
  PARAMETER<double> _stop[DCNEST];
  PARAMETER<double> _step_in[DCNEST];
  double _step[DCNEST];
  double _val_by_user_request[DCNEST];
  double _sweepdamp[DCNEST];
  bool _linswp[DCNEST];
  double* (_sweepval[DCNEST]);	/* pointer to thing to sweep, dc command */
  ELEMENT* (_zap[DCNEST]);	/* to branch to zap, for re-expand */
  CARDSTASH _stash[DCNEST];	/* store std values of elements being swept */
  bool _loop[DCNEST];		/* flag: do it again backwards */
  bool _reverse_in[DCNEST];	/* flag: sweep backwards, input */
  bool _reverse[DCNEST];	/* flag: sweep backwards, working */
  bool _cont;			/* flag: continue from previous run */
  TRACE _trace;			/* enum: show extended diagnostics */
  bool _converged;
  enum {ONE_PT, LIN_STEP, LIN_PTS, TIMES, OCTAVE, DECADE} _stepmode[DCNEST];
  static double temp_c_in;	/* ambient temperature, input and sweep variable */
};
/*--------------------------------------------------------------------------*/
double	DCOP::temp_c_in = 0.;
/*--------------------------------------------------------------------------*/
class DC : public DCOP {
public:
  explicit DC(): DCOP() {}
  ~DC() {}
  void	do_it(CS&, CARD_LIST*);
private:
  void	setup(CS&);
  explicit DC(const DC&): DCOP() {unreachable(); incomplete();}
};
/*--------------------------------------------------------------------------*/
class OP : public DCOP {
public:
  explicit OP(): DCOP() {}
  ~OP() {}
  void	do_it(CS&, CARD_LIST*);
private:
  void	setup(CS&);
  explicit OP(const OP&): DCOP() {unreachable(); incomplete();}
};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
void DC::do_it(CS& Cmd, CARD_LIST* Scope)
{
  _scope = Scope;
  _sim->_time0 = 0.;
  _sim->set_command_dc();
  _sim->_phase = p_INIT_DC;
  ::status.dc.reset().start();
  _sim->_temp_c = temp_c_in;
  command_base(Cmd);
  _scope = NULL;
  ::status.dc.stop();
}
/*--------------------------------------------------------------------------*/
void OP::do_it(CS& Cmd, CARD_LIST* Scope)
{
  _scope = Scope;
  _sim->_time0 = 0.;
  _sim->set_command_op();
  _sim->_phase = p_INIT_DC;
  ::status.op.reset().start();
  _sim->_temp_c = temp_c_in;
  command_base(Cmd);
  _scope = NULL;
  ::status.op.stop();
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
DCOP::DCOP()
  :SIM(),
   _n_sweeps(1),
   _cont(false),
   _trace(tNONE),
   _converged(0)
{
  for (int ii = 0; ii < DCNEST; ++ii) {
    _loop[ii] = false;
    _reverse_in[ii] = false;
    _reverse[ii] = false;
    _step[ii]=0.;
    _linswp[ii]=true;
    _sweepval[ii]=&_sim->_genout;
    _zap[ii]=NULL; 
    _stepmode[ii] = ONE_PT;
  }
  
  //BUG// in SIM.  should be initialized there.
  //_sim->_genout=0.;
  temp_c_in=OPT::temp_c;
  _out=IO::mstdout;
  //_sim->_uic=false;
}
/*--------------------------------------------------------------------------*/
void DCOP::finish(void)
{
  for (int ii = 0;  ii < _n_sweeps;  ++ii) {
    if (exists(_zap[ii])) { // component
      _stash[ii].restore();
      _zap[ii]->dec_probes();
      _zap[ii]->precalc_first();
      _zap[ii]->precalc_last();
      _zap[ii] = NULL;
    }else{
    }
  }
}
/*--------------------------------------------------------------------------*/
void OP::setup(CS& Cmd)
{
  _sim->_temp_c = temp_c_in;
  _cont = false;
  _trace = tNONE;
  _out = IO::mstdout;
  _out.reset(); //BUG// don't know why this is needed */
  bool ploton = IO::plotset  &&  plotlist().size() > 0;

  _zap[0] = NULL;
  _sweepval[0] = &temp_c_in;

  if (Cmd.match1("'\"({") || Cmd.is_float()) {
    Cmd >> _start[0];
    if (Cmd.match1("'\"({") || Cmd.is_float()) {
      Cmd >> _stop[0];
    }else{
      _stop[0] = _start[0];
    }
  }else{
  }
  
  _step[0] = 0.;
  _sim->_genout = 0.;

  options(Cmd,0);

  _n_sweeps = 1;
  Cmd.check(bWARNING, "what's this?");
  _sim->_freq = 0;

  IO::plotout = (ploton) ? IO::mstdout : OMSTREAM();
  initio(_out);

  _start[0].e_val(OPT::temp_c, _scope);
  fix_args(0);
}
/*--------------------------------------------------------------------------*/
void DC::setup(CS& Cmd)
{
  _cont = false;
  _trace = tNONE;
  _out = IO::mstdout;
  _out.reset(); //BUG// don't know why this is needed */
  bool ploton = IO::plotset  &&  plotlist().size() > 0;

  if (Cmd.more()) {
    for (_n_sweeps = 0; Cmd.more() && _n_sweeps < DCNEST; ++_n_sweeps) {
      CARD_LIST::fat_iterator ci = findbranch(Cmd, &CARD_LIST::card_list);
      if (!ci.is_end()) {			// sweep a component
	if (ELEMENT* c = dynamic_cast<ELEMENT*>(*ci)) {
	  _zap[_n_sweeps] = c;
	}else{untested();
	  throw Exception("dc/op: can't sweep " + (**ci).long_label() + '\n');
	}
      }else if (Cmd.is_float()) {		// sweep the generator
	_zap[_n_sweeps] = NULL;
      }else{
	// leave as it was .. repeat Cmd with no args
      }
      
      if (Cmd.match1("'\"({") || Cmd.is_float()) {	// set up parameters
	_start[_n_sweeps] = "NA";
	_stop[_n_sweeps] = "NA";
	Cmd >> _start[_n_sweeps] >> _stop[_n_sweeps];
	_step[_n_sweeps] = 0.;
      }else{
	// leave it as it was .. repeat Cmd with no args
      }
      
      _sim->_genout = 0.;
      temp_c_in = OPT::temp_c;
      _sim->_temp_c = temp_c_in;
      options(Cmd,_n_sweeps);
    }
  }else{ 
  }
  Cmd.check(bWARNING, "what's this?");

  IO::plotout = (ploton) ? IO::mstdout : OMSTREAM();
  initio(_out);

  assert(_n_sweeps > 0);
  for (int ii = 0;  ii < _n_sweeps;  ++ii) {
    _start[ii].e_val(0., _scope);
    fix_args(ii);

    if (exists(_zap[ii])) { // component
      _stash[ii] = _zap[ii];			// stash the std value
      _zap[ii]->inc_probes();			// we need to keep track of it
      _zap[ii]->set_value(_zap[ii]->value(),0);	// zap out extensions
      _zap[ii]->set_constant(false);		// so it will be updated
      _sweepval[ii] = _zap[ii]->set__value();	// point to value to patch
    }else{ // generator
      _sweepval[ii] = &_sim->_genout;			// point to value to patch
    }
  }
  _sim->_freq = 0;
}
/*--------------------------------------------------------------------------*/
void DCOP::fix_args(int Nest)
{
  _stop[Nest].e_val(_start[Nest], _scope);
  _step_in[Nest].e_val(0., _scope);
  _step[Nest] = _step_in[Nest];
  
  switch (_stepmode[Nest]) {
  case ONE_PT:
  case LIN_STEP:
    _linswp[Nest] = true;
    break;
  case LIN_PTS:untested();
    if (_step[Nest] <= 2.) {untested();
      _step[Nest] = 2.;
    }else{untested();
    }
    _linswp[Nest] = true;
    break;
  case TIMES:untested();
    if (_step[Nest] == 0.  &&  _start[Nest] != 0.) {untested();
      _step[Nest] = _stop[Nest] / _start[Nest];
    }else{untested();
    }
    _linswp[Nest] = false;
    break;
  case OCTAVE:
    if (_step[Nest] == 0.) {untested();
      _step[Nest] = 1.;
    }else{
    }
    _step[Nest] = pow(2.00000001, 1./_step[Nest]);
    _linswp[Nest] = false;
    break;
  case DECADE:
    if (_step[Nest] == 0.) {
      _step[Nest] = 1.;
    }else{
    }
    _step[Nest] = pow(10., 1./_step[Nest]);
    _linswp[Nest] = false;
    break;
  };
  
  if (_step[Nest] == 0.) {	// prohibit log sweep from 0
    _step[Nest] = _stop[Nest] - _start[Nest];
    _linswp[Nest] = true;
  }else{
  }
}
/*--------------------------------------------------------------------------*/
void DCOP::options(CS& Cmd, int Nest)
{
  _sim->_uic = _loop[Nest] = _reverse_in[Nest] = false;
  unsigned here = Cmd.cursor();
  do{
    ONE_OF
      || (Cmd.match1("'\"({")	&& ((Cmd >> _step_in[Nest]), (_stepmode[Nest] = LIN_STEP)))
      || (Cmd.is_float()	&& ((Cmd >> _step_in[Nest]), (_stepmode[Nest] = LIN_STEP)))
      || (Get(Cmd, "*",		  &_step_in[Nest]) && (_stepmode[Nest] = TIMES))
      || (Get(Cmd, "+",		  &_step_in[Nest]) && (_stepmode[Nest] = LIN_STEP))
      || (Get(Cmd, "by",	  &_step_in[Nest]) && (_stepmode[Nest] = LIN_STEP))
      || (Get(Cmd, "step",	  &_step_in[Nest]) && (_stepmode[Nest] = LIN_STEP))
      || (Get(Cmd, "d{ecade}",	  &_step_in[Nest]) && (_stepmode[Nest] = DECADE))
      || (Get(Cmd, "ti{mes}",	  &_step_in[Nest]) && (_stepmode[Nest] = TIMES))
      || (Get(Cmd, "lin",	  &_step_in[Nest]) && (_stepmode[Nest] = LIN_PTS))
      || (Get(Cmd, "o{ctave}",	  &_step_in[Nest]) && (_stepmode[Nest] = OCTAVE))
      || Get(Cmd, "c{ontinue}",   &_cont)
      || Get(Cmd, "dt{emp}",	  &temp_c_in,   mOFFSET, OPT::temp_c)
      || Get(Cmd, "lo{op}", 	  &_loop[Nest])
      || Get(Cmd, "re{verse}",	  &_reverse_in[Nest])
      || Get(Cmd, "te{mperature}",&temp_c_in)
      || (Cmd.umatch("tr{ace} {=}") &&
	  (ONE_OF
	   || Set(Cmd, "n{one}",      &_trace, tNONE)
	   || Set(Cmd, "o{ff}",       &_trace, tNONE)
	   || Set(Cmd, "w{arnings}",  &_trace, tUNDER)
	   || Set(Cmd, "a{lltime}",   &_trace, tALLTIME)
	   || Set(Cmd, "r{ejected}",  &_trace, tREJECTED)
	   || Set(Cmd, "i{terations}",&_trace, tITERATION)
	   || Set(Cmd, "v{erbose}",   &_trace, tVERBOSE)
	   || Cmd.warn(bWARNING, 
		       "need none, off, warnings, iterations, verbose")
	   )
	  )
      || outset(Cmd,&_out)
      ;
  }while (Cmd.more() && !Cmd.stuck(&here));
}
/*--------------------------------------------------------------------------*/
void DCOP::sweep()
{
  head(_start[0], _stop[0], " ");
  _sim->_bypass_ok = false;
  _sim->set_inc_mode_bad();
  if (_cont) {untested();
    _sim->restore_voltages();
  }else{
  }
  
  _sim->clear_limit();
  CARD_LIST::card_list.tr_begin();
  set_step_cause(scUSER);
  sweep_recursive(_n_sweeps-1);
  _sim->pop_voltages();
}
/*--------------------------------------------------------------------------*/
static double mul(double a,double b){ return a*b; }
static double sub(double a,double b){ return a-b; }
static double div(double a,double b){ return a/b; }
static double add(double a,double b){ return a+b; }
static bool ge(double a,double b){ return a>=b; }
static bool le(double a,double b){ return a<=b; }
/*--------------------------------------------------------------------------*/
void DCOP::sweep_recursive(int Nest)
{
  static unsigned extra_steps;
  assert(Nest >= 0);
  assert(Nest < DCNEST);

  OPT::ITL itl = OPT::DCBIAS;

  first(Nest);

  double (*step)(double a, double b) = add;
  double (*back)(double a, double b) = sub;
  if (!_linswp[Nest]) { untested();
    step=mul;
    back=div;
  }
  if (_reverse[Nest]) { untested();
    std::swap(step,back);
  }
  
  trace2("DCOP::sweep_recursive", Nest, *(_sweepval[Nest]));

  _sim->_temp_c = temp_c_in;

  bool firstloop=true;
  do {
    _sim->_temp_c = temp_c_in;
    if (Nest) {
      sweep_recursive(Nest-1);
      if(_converged){ untested();
	//if(!firstloop) 
	_sim->pop_voltages();
	_sim->restore_voltages();
        if(firstloop)_sim->keep_voltages(true); // push values for sweep. hmmm
      } else {
	trace2("not converged II", Nest, *(_sweepval[Nest]));
	// step back...
	incomplete();
      }
    }else{ // leaf
      _converged = solve_with_homotopy(itl,_trace);
      bool printnow =
        (_trace >= tREJECTED)
        || (_converged && ((_trace >= tALLTIME)
        || (step_cause() == scUSER )));
      trace3("outdata?", _trace, _converged, printnow);
      if (!printnow) {
	++extra_steps;
	++::status.hidden_steps;
	if(extra_steps > 100){
	  throw Exception("dc stepping did not succeed");
	}
      }
      if (!_converged) {untested();
	trace2("DCOP::sweep_recursive noconv", Nest, *_sweepval[Nest]);
	error(bWARNING, "did not converge\n");
        _sim->restore_voltages();
      }else{
        ::status.accept.start();
        _sim->set_limit();
        CARD_LIST::card_list.tr_accept();
        ::status.accept.stop();
        _sim->keep_voltages();
        if(firstloop)_sim->keep_voltages(true); // push values for sweep. hmmm
      }
      if (printnow) {
	extra_steps = 0;
	fixzero(_sweepval[Nest], _step[Nest]); // hack
	if (_converged){
	  outdata(*_sweepval[Nest]);
	} else {
	  outdata(- *_sweepval[Nest]);
	}
      }

      if(!_converged && firstloop){ untested();
	trace1("didnt converge in first", Nest);
	return;
      }

      itl = OPT::DCXFER;

    }

    if(firstloop){
      if(step_cause() != scUSER){
	trace1("firststep nouser", Nest);
	return;
      }
    } else {
      // UGLY. next may have changed _reverse[Nest]
      step = add;
      back = sub;
      if (!_linswp[Nest]) {
	step=mul;
	back=div;
      }
      if (_reverse[Nest]) { untested();
	std::swap(step,back);
      }
      // /UGLY

    }
    if (_converged && step_cause() == scUSER) {
      _val_by_user_request[Nest] = step(_val_by_user_request[Nest], _step[Nest]);
      trace2("ordered next step loop", Nest, _val_by_user_request[Nest]);
    }
    firstloop = false;
  } while (next(Nest));

  // _sim->pop_voltages();
}
/*--------------------------------------------------------------------------*/
void DCOP::first(int Nest)
{
  assert(Nest >= 0);
  assert(Nest < DCNEST);
  assert(_start);
  assert(_sweepval);
  assert(_sweepval[Nest]);

  *_sweepval[Nest] = _start[Nest];
  if(_converged){
    trace1("BUG", Nest);
//    set_step_cause(scUSER);
  }else{
    untested();
  }
  assert(step_cause());

  _val_by_user_request[Nest] = _start[Nest];
  _sweepdamp[Nest] = 1;
  if (ELEMENT* c = dynamic_cast<ELEMENT*>(_zap[Nest])) {
  c->set_constant(false); // because of extra precalc_last
                          // obsolete, once pointer hack is fixed
  }
  _reverse[Nest] = false;
  if (_reverse_in[Nest]) {itested();
    _converged=1;
    double (*step)(double a, double b) = add;
    double (*back)(double a, double b) = sub;
    if (!_linswp[Nest]) { untested();
      step=mul;
      back=div;
    }
    while (next(Nest)) {
      _val_by_user_request[Nest] = step(*(_sweepval[Nest]), _step[Nest]);
    }
    _val_by_user_request[Nest] = back(*(_sweepval[Nest]), _step[Nest]);
    _reverse[Nest] = true;
    next(Nest);
    _converged=0;
  }else{
  }
  _sim->_phase = p_INIT_DC;
}
/*--------------------------------------------------------------------------*/
bool DCOP::next(int Nest)
{
  trace1("next", Nest);
  bool ok = false;
  double nothing = 0;
  double (*step)(double a, double b) = add;
  double (*back)(double a, double b) = sub;
  bool (*further)(double a, double b) = ge;
  double (*scale)(double a, double b) = mul;
  if (!_linswp[Nest]) {
    step = mul;
    back = div;
    scale = pow;
    nothing = 1;
    scale = pow;
  }
  double fudge = scale(_step[Nest], .1);
  if (_reverse[Nest]) { untested();
    trace2("next, reverse", *_sweepval[Nest], _val_by_user_request[Nest]);
    std::swap(step,back);
    further=le;
    fudge = scale(_step[Nest], -.1);
  }
  if (_step[Nest] == nothing) {
    ok = false;
    set_step_cause(scZERO);
  }else if (!_converged) { untested();
    if (_sweepdamp[Nest]<OPT::dtmin)
      throw Exception("step too small (does not converge)");
    _sweepdamp[Nest] /= 2.;
    trace2("reducing step by", _sweepdamp[Nest], Nest);
    *(_sweepval[Nest]) = back(*(_sweepval[Nest]), scale(_step[Nest],_sweepdamp[Nest]));
    trace1("next at", *(_sweepval[Nest]));
    ok = true;
    set_step_cause(scREJECT);
  }else{
    if (_sweepdamp[Nest] != 1) {
      trace3("recovered from", _sweepdamp[Nest], Nest, *(_sweepval[Nest]));
      set_step_cause(scTE);
    }
    _sweepdamp[Nest] *= 1.4;
    _sweepdamp[Nest] = std::min(_sweepdamp[Nest],1.);
    *(_sweepval[Nest]) = step(*(_sweepval[Nest]), scale(_step[Nest],_sweepdamp[Nest]));
    fixzero(_sweepval[Nest], _step[Nest]);
    ok = in_order(back(_start[Nest],fudge), *(_sweepval[Nest]), step(_stop[Nest],fudge));
    if (!_reverse[Nest] && !ok && _loop[Nest]) { untested();
      _reverse[Nest] = true;
      further = le;
      fudge = scale(_step[Nest], -.1);
      *(_sweepval[Nest]) = back(*(_sweepval[Nest]), _step[Nest]);
      std::swap(step,back);
      ok = in_order(back(_start[Nest],fudge),*(_sweepval[Nest]),step(_stop[Nest],fudge));
      assert(ok);
      untested();
      _val_by_user_request[Nest] = *_sweepval[Nest]; // BUG: here?
    }else{
    }

  }

  double v = _val_by_user_request[Nest];
  if (further(step(*(_sweepval[Nest]), scale(_step[Nest],1e-6) ), v)) {
    trace4("userstep at", v, *(_sweepval[Nest]), ok, _reverse[Nest]);
    set_step_cause(scUSER);
    *(_sweepval[Nest]) = v;
  }else{
  }

  _sim->_phase = p_DC_SWEEP;
  return ok;
}
/*--------------------------------------------------------------------------*/
static DC p2;
static OP p4;
static DISPATCHER<CMD>::INSTALL d2(&command_dispatcher, "dc", &p2);
static DISPATCHER<CMD>::INSTALL d4(&command_dispatcher, "op", &p4);
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// vim:ts=8:sw=2:
