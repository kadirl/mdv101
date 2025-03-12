// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vfibonacci_generator__Syms.h"


void Vfibonacci_generator___024root__trace_chg_0_sub_0(Vfibonacci_generator___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vfibonacci_generator___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root__trace_chg_0\n"); );
    // Init
    Vfibonacci_generator___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vfibonacci_generator___024root*>(voidSelf);
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vfibonacci_generator___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vfibonacci_generator___024root__trace_chg_0_sub_0(Vfibonacci_generator___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root__trace_chg_0_sub_0\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgIData(oldp+0,(vlSelfRef.fibonacci_generator__DOT__fib_prev1),32);
        bufp->chgIData(oldp+1,(vlSelfRef.fibonacci_generator__DOT__fib_prev2),32);
        bufp->chgIData(oldp+2,(vlSelfRef.fibonacci_generator__DOT__fib_out1),32);
    }
    bufp->chgBit(oldp+3,(vlSelfRef.clk));
    bufp->chgBit(oldp+4,(vlSelfRef.rst));
    bufp->chgBit(oldp+5,(vlSelfRef.enable));
    bufp->chgIData(oldp+6,(vlSelfRef.fib_out),32);
}

void Vfibonacci_generator___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root__trace_cleanup\n"); );
    // Init
    Vfibonacci_generator___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vfibonacci_generator___024root*>(voidSelf);
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
