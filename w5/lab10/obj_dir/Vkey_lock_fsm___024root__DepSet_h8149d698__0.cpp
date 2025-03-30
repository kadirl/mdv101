// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vkey_lock_fsm.h for the primary calling header

#include "Vkey_lock_fsm__pch.h"
#include "Vkey_lock_fsm___024root.h"

void Vkey_lock_fsm___024root___ico_sequent__TOP__0(Vkey_lock_fsm___024root* vlSelf);

void Vkey_lock_fsm___024root___eval_ico(Vkey_lock_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkey_lock_fsm___024root___eval_ico\n"); );
    Vkey_lock_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vkey_lock_fsm___024root___ico_sequent__TOP__0(vlSelf);
    }
}

extern const VlUnpacked<CData/*2:0*/, 128> Vkey_lock_fsm__ConstPool__TABLE_h24fd19fa_0;

VL_INLINE_OPT void Vkey_lock_fsm___024root___ico_sequent__TOP__0(Vkey_lock_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkey_lock_fsm___024root___ico_sequent__TOP__0\n"); );
    Vkey_lock_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*6:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    __Vtableidx1 = (((IData)(vlSelfRef.key_in) << 3U) 
                    | (IData)(vlSelfRef.key_lock_fsm__DOT__current_state));
    vlSelfRef.key_lock_fsm__DOT__next_state = Vkey_lock_fsm__ConstPool__TABLE_h24fd19fa_0
        [__Vtableidx1];
}

void Vkey_lock_fsm___024root___eval_triggers__ico(Vkey_lock_fsm___024root* vlSelf);

bool Vkey_lock_fsm___024root___eval_phase__ico(Vkey_lock_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkey_lock_fsm___024root___eval_phase__ico\n"); );
    Vkey_lock_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vkey_lock_fsm___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vkey_lock_fsm___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vkey_lock_fsm___024root___eval_act(Vkey_lock_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkey_lock_fsm___024root___eval_act\n"); );
    Vkey_lock_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vkey_lock_fsm___024root___nba_sequent__TOP__0(Vkey_lock_fsm___024root* vlSelf);

void Vkey_lock_fsm___024root___eval_nba(Vkey_lock_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkey_lock_fsm___024root___eval_nba\n"); );
    Vkey_lock_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vkey_lock_fsm___024root___nba_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vkey_lock_fsm___024root___nba_sequent__TOP__0(Vkey_lock_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkey_lock_fsm___024root___nba_sequent__TOP__0\n"); );
    Vkey_lock_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*6:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    vlSelfRef.key_lock_fsm__DOT__current_state = ((IData)(vlSelfRef.rst)
                                                   ? 0U
                                                   : (IData)(vlSelfRef.key_lock_fsm__DOT__next_state));
    vlSelfRef.locked = (6U != (IData)(vlSelfRef.key_lock_fsm__DOT__current_state));
    vlSelfRef.state_debug = vlSelfRef.key_lock_fsm__DOT__current_state;
    __Vtableidx1 = (((IData)(vlSelfRef.key_in) << 3U) 
                    | (IData)(vlSelfRef.key_lock_fsm__DOT__current_state));
    vlSelfRef.key_lock_fsm__DOT__next_state = Vkey_lock_fsm__ConstPool__TABLE_h24fd19fa_0
        [__Vtableidx1];
}

void Vkey_lock_fsm___024root___eval_triggers__act(Vkey_lock_fsm___024root* vlSelf);

bool Vkey_lock_fsm___024root___eval_phase__act(Vkey_lock_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkey_lock_fsm___024root___eval_phase__act\n"); );
    Vkey_lock_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vkey_lock_fsm___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vkey_lock_fsm___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vkey_lock_fsm___024root___eval_phase__nba(Vkey_lock_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkey_lock_fsm___024root___eval_phase__nba\n"); );
    Vkey_lock_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vkey_lock_fsm___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vkey_lock_fsm___024root___dump_triggers__ico(Vkey_lock_fsm___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vkey_lock_fsm___024root___dump_triggers__nba(Vkey_lock_fsm___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vkey_lock_fsm___024root___dump_triggers__act(Vkey_lock_fsm___024root* vlSelf);
#endif  // VL_DEBUG

void Vkey_lock_fsm___024root___eval(Vkey_lock_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkey_lock_fsm___024root___eval\n"); );
    Vkey_lock_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vkey_lock_fsm___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("rtl/key_lock_fsm.v", 1, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vkey_lock_fsm___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vkey_lock_fsm___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("rtl/key_lock_fsm.v", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vkey_lock_fsm___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("rtl/key_lock_fsm.v", 1, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vkey_lock_fsm___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vkey_lock_fsm___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vkey_lock_fsm___024root___eval_debug_assertions(Vkey_lock_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkey_lock_fsm___024root___eval_debug_assertions\n"); );
    Vkey_lock_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY(((vlSelfRef.key_in & 0xf0U)))) {
        Verilated::overWidthError("key_in");}
}
#endif  // VL_DEBUG
