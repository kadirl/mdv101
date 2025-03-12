// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfibonacci_generator.h for the primary calling header

#include "Vfibonacci_generator__pch.h"
#include "Vfibonacci_generator__Syms.h"
#include "Vfibonacci_generator___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfibonacci_generator___024root___dump_triggers__stl(Vfibonacci_generator___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vfibonacci_generator___024root___eval_triggers__stl(Vfibonacci_generator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root___eval_triggers__stl\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.set(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vfibonacci_generator___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
