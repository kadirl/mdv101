// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vcontrol_unit__Syms.h"


void Vcontrol_unit___024root__trace_chg_0_sub_0(Vcontrol_unit___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vcontrol_unit___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root__trace_chg_0\n"); );
    // Init
    Vcontrol_unit___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcontrol_unit___024root*>(voidSelf);
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vcontrol_unit___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vcontrol_unit___024root__trace_chg_0_sub_0(Vcontrol_unit___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root__trace_chg_0_sub_0\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    bufp->chgSData(oldp+0,(vlSelfRef.d_in),16);
    bufp->chgBit(oldp+1,(vlSelfRef.clk));
    bufp->chgBit(oldp+2,(vlSelfRef.reset));
    bufp->chgBit(oldp+3,(vlSelfRef.run));
    bufp->chgCData(oldp+4,(vlSelfRef.alu_sel),4);
    bufp->chgBit(oldp+5,(vlSelfRef.alu_mode));
    bufp->chgCData(oldp+6,(vlSelfRef.mux_sel),3);
    bufp->chgBit(oldp+7,(vlSelfRef.en_s));
    bufp->chgBit(oldp+8,(vlSelfRef.en_c));
    bufp->chgBit(oldp+9,(vlSelfRef.en_0));
    bufp->chgBit(oldp+10,(vlSelfRef.en_1));
    bufp->chgBit(oldp+11,(vlSelfRef.en_2));
    bufp->chgBit(oldp+12,(vlSelfRef.en_3));
    bufp->chgBit(oldp+13,(vlSelfRef.en_4));
    bufp->chgBit(oldp+14,(vlSelfRef.en_5));
    bufp->chgBit(oldp+15,(vlSelfRef.en_6));
    bufp->chgBit(oldp+16,(vlSelfRef.en_7));
    bufp->chgBit(oldp+17,(vlSelfRef.en_i));
    bufp->chgBit(oldp+18,(vlSelfRef.done));
    bufp->chgCData(oldp+19,((7U & ((IData)(vlSelfRef.d_in) 
                                   >> 0xdU))),3);
    bufp->chgCData(oldp+20,((7U & ((IData)(vlSelfRef.d_in) 
                                   >> 0xaU))),3);
    bufp->chgCData(oldp+21,((7U & ((IData)(vlSelfRef.d_in) 
                                   >> 7U))),3);
    bufp->chgCData(oldp+22,((3U & (IData)(vlSelfRef.d_in))),2);
    bufp->chgCData(oldp+23,(vlSelfRef.control_unit__DOT__state),2);
    bufp->chgCData(oldp+24,(vlSelfRef.control_unit__DOT__next_state),2);
}

void Vcontrol_unit___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root__trace_cleanup\n"); );
    // Init
    Vcontrol_unit___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcontrol_unit___024root*>(voidSelf);
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
