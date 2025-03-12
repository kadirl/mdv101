// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfibonacci_generator.h for the primary calling header

#include "Vfibonacci_generator__pch.h"
#include "Vfibonacci_generator___024root.h"

VL_ATTR_COLD void Vfibonacci_generator___024root___eval_static(Vfibonacci_generator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root___eval_static\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vfibonacci_generator___024root___eval_initial(Vfibonacci_generator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root___eval_initial\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vfibonacci_generator___024root___eval_final(Vfibonacci_generator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root___eval_final\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfibonacci_generator___024root___dump_triggers__stl(Vfibonacci_generator___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vfibonacci_generator___024root___eval_phase__stl(Vfibonacci_generator___024root* vlSelf);

VL_ATTR_COLD void Vfibonacci_generator___024root___eval_settle(Vfibonacci_generator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root___eval_settle\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x64U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vfibonacci_generator___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("fibonacci_generator.v", 1, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vfibonacci_generator___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfibonacci_generator___024root___dump_triggers__stl(Vfibonacci_generator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root___dump_triggers__stl\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vfibonacci_generator___024root___stl_sequent__TOP__0(Vfibonacci_generator___024root* vlSelf);

VL_ATTR_COLD void Vfibonacci_generator___024root___eval_stl(Vfibonacci_generator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root___eval_stl\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vfibonacci_generator___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vfibonacci_generator___024root___stl_sequent__TOP__0(Vfibonacci_generator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root___stl_sequent__TOP__0\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.fib_out = vlSelfRef.fibonacci_generator__DOT__fib_out1;
}

VL_ATTR_COLD void Vfibonacci_generator___024root___eval_triggers__stl(Vfibonacci_generator___024root* vlSelf);

VL_ATTR_COLD bool Vfibonacci_generator___024root___eval_phase__stl(Vfibonacci_generator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root___eval_phase__stl\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vfibonacci_generator___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vfibonacci_generator___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfibonacci_generator___024root___dump_triggers__act(Vfibonacci_generator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root___dump_triggers__act\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfibonacci_generator___024root___dump_triggers__nba(Vfibonacci_generator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root___dump_triggers__nba\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vfibonacci_generator___024root___ctor_var_reset(Vfibonacci_generator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfibonacci_generator___024root___ctor_var_reset\n"); );
    Vfibonacci_generator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst = VL_RAND_RESET_I(1);
    vlSelf->enable = VL_RAND_RESET_I(1);
    vlSelf->fib_out = VL_RAND_RESET_I(32);
    vlSelf->fibonacci_generator__DOT__fib_prev1 = VL_RAND_RESET_I(32);
    vlSelf->fibonacci_generator__DOT__fib_prev2 = VL_RAND_RESET_I(32);
    vlSelf->fibonacci_generator__DOT__fib_out1 = VL_RAND_RESET_I(32);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
