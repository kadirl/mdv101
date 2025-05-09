// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vmux__Syms.h"


void Vmux___024root__trace_chg_0_sub_0(Vmux___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vmux___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux___024root__trace_chg_0\n"); );
    // Init
    Vmux___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vmux___024root*>(voidSelf);
    Vmux__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vmux___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vmux___024root__trace_chg_0_sub_0(Vmux___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux___024root__trace_chg_0_sub_0\n"); );
    Vmux__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    bufp->chgSData(oldp+0,(vlSelfRef.in[0]),16);
    bufp->chgSData(oldp+1,(vlSelfRef.in[1]),16);
    bufp->chgSData(oldp+2,(vlSelfRef.in[2]),16);
    bufp->chgSData(oldp+3,(vlSelfRef.in[3]),16);
    bufp->chgSData(oldp+4,(vlSelfRef.in[4]),16);
    bufp->chgSData(oldp+5,(vlSelfRef.in[5]),16);
    bufp->chgSData(oldp+6,(vlSelfRef.in[6]),16);
    bufp->chgSData(oldp+7,(vlSelfRef.in[7]),16);
    bufp->chgCData(oldp+8,(vlSelfRef.sel),3);
    bufp->chgSData(oldp+9,(vlSelfRef.out),16);
}

void Vmux___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux___024root__trace_cleanup\n"); );
    // Init
    Vmux___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vmux___024root*>(voidSelf);
    Vmux__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
