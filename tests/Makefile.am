# this file is part of gnucap
# (c) 2013 Felix Salfelder
# License: GPLv3
#

# needed for gnucap-run.sh
AM_TESTS_ENVIRONMENT = \
    export PATH='../main:$(PATH)' \
           GNUCAP_DEFAULT_PLUGINS='../apps/.libs/gnucap_default_plugins.so';
AM_TESTS_FD_REDIRECT = 9>&2
TEST_EXTENSIONS = .sh
TESTS = \
    gnucap_run.sh \
	 $(CKT_TESTS)

REF = ==out

check_PROGRAMS = filter

CKT_TESTS = \
    1lin.sh \
    ap_ctof.2.sh \
    ap_ctof.sh \
    basic.sh \
    bm_complex.1a.sh \
    bm_complex.1.sh \
    bm_complex.2.sh \
    bm_complex.3.sh \
    bm_complex.4.sh \
    bm_cond.1.sh \
    bm_cond.2.sh \
    bm_cond.3.sh \
    bm_exp.1.sh \
    bm_exp.1p.sh \
    bm_exp.2.sh \
    bm_exp.3.sh \
    bm_exp.3p.sh \
    bm_exp.4p.sh \
    bm_exp.5p.sh \
    bm_fit.0.1.sh \
    bm_fit.1.1.sh \
    bm_fit.2.1.sh \
    bm_fit.2.2.sh \
    bm_fit.2.3.sh \
    bm_fit.2.4.sh \
    bm_fit.3.1.sh \
    bm_fit.3.2.sh \
    bm_fit.3.3.sh \
    bmm_cap.1.sh \
    bmm_cap.2.sh \
    bmm_cap.3.sh \
    bmm_cap.4.sh \
    bmm_cap.5.sh \
    bmm_res.1.sh \
    bmm_res.1p.sh \
    bmm_res.2.sh \
    bmm_res.2p.sh \
    bmm_res.3.sh \
    bmm_res.3p.sh \
    bmm_res.4.sh \
    bmm_res.4p.sh \
    bmm_res.5.sh \
    bmm_res.5p.sh \
    bm_poly.1.sh \
    bm_poly.2.sh \
    bm_posy.1.sh \
    bm_pulse.1.sh \
    bm_pulse.2.sh \
    bm_pulse.3.sh \
    bm_pwl.1.sh \
    bm_pwl.2.sh \
    bm_pwl.3.sh \
    bm_pwl.4.sh \
    bm_pwl.5.sh \
    bm_sffm.1.sh \
    bm_sffm.2.sh \
    bm_sffm.3.sh \
    bm_sffm.4.sh \
    bm_sffm.5.sh \
    bm_sffm.6.sh \
    bm_sin.1.sh \
    bm_sin.2.sh \
    bm_sin.3.sh \
    bm_sin.4.sh \
    bm_sin.5.sh \
    bm_sin.6.sh \
    bm_sin.7.sh \
    bm_sin.8.sh \
    bm_sin.9.sh \
    bm_table.1.1.sh \
    bm_table.2.1.sh \
    bm_table.2.2.sh \
    bm_table.2.3.sh \
    bm_table.2.4.sh \
    bm_table.3.1.sh \
    bm_table.3.2.sh \
    bm_table.3.3.sh \
    bm_table.error1.sh \
    bm_tanh.1.sh \
    bm_tanh.2.sh \
    cc.sh \
    c.sh \
    c_delete.2.sh \
    c_delete.3.sh \
    c_delete.4.sh \
    c_delete.5.sh \
    c_delete.6.sh \
    c_delete.7.sh \
    c_delete.sh \
    c_eval.1.sh \
    c_getckt.sh \
    charge-cons2.sh \
    charge-cons3.sh \
    charge-cons.sh \
    c_lib.1.sh \
    c_list.sh \
    c_measure.1.sh \
    c_measure.2.sh \
    c_modify.sh \
    current.sh \
    d_bjt.2.sh \
    d_bjt.sh \
    d_bjt-diffpair-ccs.sh \
    d_bjt-diffpair-cjc.sh \
    d_bjt-diffpair-dc.sh \
    d_bjt-diffpair-nocap.sh \
    d_bjt-diffpair-tf.sh \
    d_bjt-diffpair-tran.sh \
    d_bjt-diffpair-tr.sh \
    d_bjt.error1.sh \
    d_bjt-pnp.sh \
    d_bjt-rca3040.sh \
    d_bjt-rtlinv.sh \
    d_bjt-schmitt-bypass.sh \
    d_bjt-schmitt-nobypass.sh \
    d_cap.1.sh \
    d_cap.2.sh \
    d_cap.3a.sh \
    d_cap.3.sh \
    d_cap.4.sh \
    d_cap.5.sh \
    d_cap.6.sh \
    d_cap.ic1.sh \
    d_cap.ic2.sh \
    d_cap.ic4.sh \
    d_cccs.1.sh \
    d_cccs.2.sh \
    d_cccs.3.sh \
    d_cccs.4.sh \
    d_cccs.5.sh \
    d_cccs.6.sh \
    d_ccvs.1.sh \
    d_ccvs.2.sh \
    d_ccvs.3.sh \
    d_coil.1a.sh \
    d_coil.1b.sh \
    d_coil.1c.sh \
    d_coil.1.sh \
    d_coil.1d.sh \
    d_coil.1e.sh \
    d_coil.2.sh \
    d_coil.3.sh \
    d_coil.4.sh \
    d_coil.5.sh \
    d_coil.error1.sh \
    d_coil.error2.sh \
    d_coil.error3.sh \
    d_coil.error4.sh \
    d_coil.error5.sh \
    d_coil.m3a.sh \
    d_coil.m3.sh \
    d_diode.10a.sh \
    d_diode.10.sh \
    d_diode.11a.sh \
    d_diode.11b.sh \
    d_diode.11c.sh \
    d_diode.11.sh \
    d_diode.11d.sh \
    d_diode.12.sh \
    d_diode.1.sh \
    d_diode.2.sh \
    d_diode.3.sh \
    d_diode.4.sh \
    d_diode.5.sh \
    d_diode.6.sh \
    d_diode.7.sh \
    d_diode.8.sh \
    d_diode.9.sh \
    d_diode.error1.sh \
    d_logic.1.sh \
    d_logic.2.sh \
    d_logic.3.sh \
    d_logic.4.sh \
    d_logic.5.sh \
    d_logic.6.sh \
    d_logic.7.sh \
    d_logic.error1.sh \
    d_logic_nand-dc.sh \
    d_logic_tr_ab1.sh \
    d_logic_tr_ab2.sh \
    d_logic_tr_an1.sh \
    d_logic_tr_an2.sh \
    d_logic_tr_db1.sh \
    d_logic_tr_db2.sh \
    d_logic_tr_dn1.sh \
    d_logic_tr_dn2.sh \
    d_logic_tr_mb1a.sh \
    d_logic_tr_mb1b.sh \
    d_logic_tr_mb2a.sh \
    d_logic_tr_mb2b.sh \
    d_logic_tr_mn1a.sh \
    d_logic_tr_mn1b.sh \
    d_logic_tr_mn2a.sh \
    d_logic_tr_mn2b.sh \
    d_macro.1.sh \
    d_mos1.bin1.sh \
    d_mos1.bin2.sh \
    d_mos1.bin3.sh \
    d_mos1.inv1.sh \
    d_mos1.inv2.sh \
    d_mos1.inv3.sh \
    d_mos1.lin1.sh \
    d_mos1.lin1.late.sh \
    d_mos1.lin1.none.sh \
    d_mos1.lin2.sh \
    d_mos1.lin3.sh \
    d_mos1.lin4.sh \
    d_mos1.lin5.sh \
    d_mos1.n0.sh \
    d_mos1.n-1.sh \
    d_mos1.n+1.sh \
    d_mos1.nand1.sh \
    d_mos1.nand2.sh \
    d_mos1.p0.sh \
    d_mos1.p-1.sh \
    d_mos1.p+1.sh \
    d_mos1.plin.sh \
    d_mos1.psat1.sh \
    d_mos1.psat2.sh \
    d_mos1.psat3.sh \
    d_mos1.sat1.sh \
    d_mos1.sat2.sh \
    d_mos1.sat3.sh \
    d_mos1.sat4.sh \
    d_mos1.sat5.sh \
    d_mos1.sat6.sh \
    d_mos1.sat7.sh \
    d_mos1.sts.sh \
    d_mos1.zero.sh \
    d_mos2.inv1.sh \
    d_mos2.lin1.sh \
    d_mos2.lin1.late.sh \
    d_mos2.lin1r.sh \
    d_mos2.lin1z.sh \
    d_mos2.lin2.sh \
    d_mos2.lin3.sh \
    d_mos2.lin4.sh \
    d_mos2.lin5.sh \
    d_mos2.n0.sh \
    d_mos2.n-1.sh \
    d_mos2.n+1.sh \
    d_mos2.nand1.sh \
    d_mos2.p0.sh \
    d_mos2.p-1.sh \
    d_mos2.p+1.sh \
    d_mos2.plin.sh \
    d_mos2.psat1.sh \
    d_mos2.psat2.sh \
    d_mos2.psat3.sh \
    d_mos2.sat1.sh \
    d_mos2.sat2.sh \
    d_mos2.sat3.sh \
    d_mos2.sat4.sh \
    d_mos2.sat5.sh \
    d_mos2.sat6.sh \
    d_mos2.sat7.sh \
    d_mos2.sts.sh \
    d_mos2.zero.sh \
    d_mos3.inv1.sh \
    d_mos3.lin1.sh \
    d_mos3.lin1r.sh \
    d_mos3.lin1z.sh \
    d_mos3.lin2.sh \
    d_mos3.lin3.sh \
    d_mos3.lin4.sh \
    d_mos3.lin5.sh \
    d_mos3.n0.sh \
    d_mos3.n-1.sh \
    d_mos3.n+1.sh \
    d_mos3.nand1.sh \
    d_mos3.p0.sh \
    d_mos3.p-1.sh \
    d_mos3.p+1.sh \
    d_mos3.plin.sh \
    d_mos3.psat1.sh \
    d_mos3.psat2.sh \
    d_mos3.psat3.sh \
    d_mos3.sat000.sh \
    d_mos3.sat007.sh \
    d_mos3.sat1.sh \
    d_mos3.sat2.sh \
    d_mos3.sat3.sh \
    d_mos3.sat4.sh \
    d_mos3.sat5.sh \
    d_mos3.sat6.sh \
    d_mos3.sat7.sh \
    d_mos3.sts000.sh \
    d_mos3.sts.sh \
    d_mos3.zero.sh \
    d_mos4.1.sh \
    d_mos4.2.sh \
    d_mos4.3.sh \
    d_mos49.nand1.sh \
    d_mos5.1.sh \
    d_mos6.inv1.sh \
    d_mos6.lin1.sh \
    d_mos6.lin1r.sh \
    d_mos6.lin1z.sh \
    d_mos6.lin2.sh \
    d_mos6.lin2r.sh \
    d_mos6.lin2z.sh \
    d_mos6.n0.sh \
    d_mos6.n-1.sh \
    d_mos6.n+1.sh \
    d_mos6.nand1.sh \
    d_mos6.p0.sh \
    d_mos6.p-1.sh \
    d_mos6.p+1.sh \
    d_mos6.plin.sh \
    d_mos6.psat1.sh \
    d_mos6.psat2.sh \
    d_mos6.psat3.sh \
    d_mos6.sat1.sh \
    d_mos6.sat1r.sh \
    d_mos6.sat1s.sh \
    d_mos6.sat1v.sh \
    d_mos6.sat2.sh \
    d_mos6.sat2r.sh \
    d_mos6.sat3.sh \
    d_mos6.sat3r.sh \
    d_mos6.sts000.sh \
    d_mos6.sts.sh \
    d_mos6.zero.sh \
    d_mos7.alpha.sh \
    d_mos7.inv1.sh \
    d_mos7.lin1.sh \
    d_mos7.lin2.sh \
    d_mos7.nand1.sh \
    d_mos7.nand1.nobypass.sh \
    d_mos7.plin.sh \
    d_mos7.psat.sh \
    d_mos7.sat1.sh \
    d_mos7.sat2.sh \
    d_mos7.sat3.sh \
    d_mos7.sts.sh \
    d_mos7.zero.sh \
    d_mos8c2.nand1.sh \
    d_mos8c2.nand1.nobypass.sh \
    d_mos8.nand1.sh \
    d_mos8.sat2.sh \
    d_mos8.sat3.sh \
    d_mos8.sat4.sh \
    d_mos.error1.sh \
    d_mos.error2.sh \
    d_mos.error3.sh \
    d_mos.error4.sh \
    d_subckt.1.sh \
    d_subckt.2.sh \
    d_subckt.3.sh \
    d_subckt.4.sh \
    d_subckt.5.sh \
    d_subckt.6.sh \
    d_subckt.7.sh \
    d_subckt.8.sh \
    d_subckt.error1.sh \
    d_subckt.error2.sh \
    d_switch.c0.sh \
    d_switch.c1a.sh \
    d_switch.c1.sh \
    d_switch.c1.inc.sh \
    d_switch.c1.noinc.sh \
    d_switch.c1r.sh \
    d_switch.c2a.sh \
    d_switch.c2.sh \
    d_switch.c2r.sh \
    d_switch.c3.sh \
    d_switch.error1.sh \
    d_switch.error2.sh \
    d_switch.error3.sh \
    d_switch.nro.1.sh \
    d_switch.nro.1e.sh \
    d_switch.nro.1g.sh \
    d_switch.nro.1gr.sh \
    d_switch.nro.2.sh \
    d_switch.nro.3.sh \
    d_switch.nro.3h.sh \
    d_switch.nro.4.sh \
    d_switch.v.sh \
    d_switch.vr.sh \
    d_tcap.1.sh \
    d_tcap.2.sh \
    d_tcap.3.sh \
    d_tcap.4.sh \
    d_trln.ac.sh \
    d_trln.tr.100.im.sh \
    d_trln.tr.100.nim.sh \
    d_trln.tr.300.im.sh \
    d_trln.tr.300.nim.sh \
    d_trln.tr.im.sh \
    d_trln.tr.m.sh \
    d_trln.tr.nim.sh \
    d_vccap.1.sh \
    d_vccap.2.sh \
    d_vcg.1.sh \
    d_vcg.2.sh \
    d_vcg.3.sh \
    d_vcg.4.sh \
    d_vcg.5.sh \
    d_vcr.1.sh \
    d_vcr.2.sh \
    d_vcr.3.sh \
    d_vcr.4.sh \
    d_vcr.5.sh \
    d_vcvs.1.sh \
    dc_temp.sh \
    dcsweep.sh \
    e_ccsrc.1.sh \
    e_ccsrc.2.sh \
    e_node_probes.sh \
    eq3-1153.sh \
    eq3-1153.fg2.sh \
    eq3-1153.fg.sh \
    eq3-1153.tr-b.sh \
    eq3-1153.tr-nb.sh \
    eq3-1153.tr-ni.sh \
    eqb1.sh \
    eqboost.sh \
    eqflat.sh \
    eqmodify.sh \
    e_storag.1.sh \
    list.1.sh \
    l2.sh \
    l.sh \
    ll1.sh \
    ll.sh \
    lll.sh \
    llll.sh \
    m_expression.1.sh \
    m_expression.2.sh \
    m_expression.3.sh \
    m_expression.error.1.sh \
    named_nodes.sh \
    nmos100.1.sh \
    nmos100.sh \
    nmos15a.sh \
    nmos15.sh \
    nmp100.sh \
    nothing.sh \
    opamp-ol.sh \
    opamp-ol-disto.2.sh \
    opamp-ol-disto.sh \
    opamp-vf.1.sh \
    opamp-vf.1d.sh \
    opamp-vf.2.sh \
    opamp-vf.3.sh \
    opamp-vf.sh \
    oscillator.1.sh \
    oscillator.2.sh \
    oscillator.3.sh \
    oscillator.4.sh \
    oscillator.5.sh \
    oscillator.6.sh \
    oscillator.7.sh \
    param.0a.sh \
    param.0.sh \
    param.10.sh \
    param.11.sh \
    param.1.sh \
    param.2a.sh \
    param.2b.sh \
    param.2.sh \
    param.3.sh \
    param.4.sh \
    param.5.sh \
    param.6.sh \
    param.7.sh \
    param.8.sh \
    param.9.sh \
    parse.1.sh \
    sl.sh \
    trcurve2.sh \
    trcurve.sh \
    trcurves.sh

XFAIL_TESTS = list.1.sh dc_temp.sh

AUTO_TESTS = $(CKT_TESTS)

.PHONY: $(AUTO_TESTS:%.sh=%.out)

$(CKT_TESTS): %.sh: %.out

# try this first
$(CKT_TESTS:%.sh:%.log): gnucap_run.log

# this will trigger a warning in autogen.sh
# (apparently this warning is s bug)
c_getckt.sh c_getckt.log c_getckt.out: | $(PWD)/d_cccs.1.ckt
c_lib.1.sh c_lib.1.log c_lib.1.out: | $(PWD)/c_lib.1.ckt

PREDIFF= \
   '1,/^default·plugins/d' \
   '/^stashing·as/d' \
	'/^@/d' \
	'/:·already.installed,·replacing/d'

# permit different control values
d_logic_tr_%.out: POSTDIFF+= '3·s/[01]\.········$$/X.········/'

# close to zero...
d_vcg.%.out: POSTDIFF+= '27·s/975\.[0-9][0-9]f/0.·····/'

# close enough
bm_poly.%.out: POSTDIFF+= '30·s/-.\.f/·0.·/g'
bm_poly.%.out: POSTDIFF+= '30·s/-..\.f/·0.··/g'

# same
trcurve2.out: POSTDIFF+= 's/·[0-9]\.E-21/·0.····/'
trcurve2.out: POSTDIFF+= 's/·[0-9][0-9]\.E-21/·0.·····/'

# negative zeroes? nice, but should not be machine dependent
bm_sffm.%.out: POSTDIFF+= 's/-0\.000\>/·0.000/g'

bm_table.2.4.out: POSTDIFF+= '54·s/[- ][0-9]\.f/·0.·/g'

$(AUTO_TESTS:%.sh=%.out): %.out: %.ckt
	$(AM_V_at)GNUCAP_DEFAULT_PLUGINS='../apps/.libs/gnucap_default_plugins.so' \
	    ../main/gnucap $(GNUCAP_PLUGINS:%=-a ../plugins/.libs/%) $(GNUCAP_ARGS) -b $< | \
	    sed $(subst ·, ,$(PREDIFF:%=-e %)) \
	    $(if $(POSTDIFF),| sed) $(subst ·, ,$(POSTDIFF:%=-e %)) > $*.out

define testgen
	@echo "#!/bin/sh" > $@
	@echo "set -e" >> $@
	@echo "exec 2>&9" >> $@
	@echo "./filter $< < $*.out | diff -rup $< - || exit 1" >> $@
	@echo "rm $*.out" >> $@
	@chmod +x $@
endef

%.sh: $(REF)/%.ckt.out
	$(testgen)

$(GC_TESTS:%.sh=%.out): %.out: %.gc
	$(AM_V_at)$(GNUCAP) $(GNUCAP_PLUGINS:%=-a ../plugins/.libs/%) $(GNUCAP_ARGS) $< | \
	    sed $(subst ·, ,$(PREDIFF:%=-e %)) \
	    $(if $(POSTDIFF),| sed) $(subst ·, ,$(POSTDIFF:%=-e %)) > $*.out

$(GC_TESTS): %.sh: %.ref
	@echo "#!/bin/sh" > $@
	@echo "set -e" >> $@
	@echo "exec 2>&9" >> $@
	@echo "cat $*.out | diff -rup $< - || exit 1" >> $@
	@echo "rm $*.out" >> $@
	@chmod +x $@

CLEANFILES = *.out $(AUTO_TESTS)

# hmmm.
if VPATH_BUILD
$(PWD)/%.ckt: %.ckt
	$(AM_V_at)$(LN_S) $< $@

CLEANFILES+= d_cccs.1.ckt c_lib.1.ckt
endif
