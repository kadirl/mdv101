// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vbitty_core.h for the primary calling header

#include "Vbitty_core__pch.h"
#include "Vbitty_core___024root.h"

void Vbitty_core___024root___eval_act(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___eval_act\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vbitty_core___024root___nba_sequent__TOP__0(Vbitty_core___024root* vlSelf);

void Vbitty_core___024root___eval_nba(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___eval_nba\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vbitty_core___024root___nba_sequent__TOP__0(vlSelf);
    }
}

extern const VlUnpacked<CData/*1:0*/, 4> Vbitty_core__ConstPool__TABLE_hcac39648_0;

VL_INLINE_OPT void Vbitty_core___024root___nba_sequent__TOP__0(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___nba_sequent__TOP__0\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*2:0*/ bitty_core__DOT__alu_sel;
    bitty_core__DOT__alu_sel = 0;
    CData/*2:0*/ bitty_core__DOT__mux_sel;
    bitty_core__DOT__mux_sel = 0;
    CData/*1:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    if (vlSelfRef.reset) {
        vlSelfRef.bitty_core__DOT__reg_c_inst__DOT__storage = 0U;
        vlSelfRef.bitty_core__DOT__reg_s_inst__DOT__storage = 0U;
        vlSelfRef.bitty_core__DOT__reg0_inst__DOT__storage = 0U;
        vlSelfRef.bitty_core__DOT__reg1_inst__DOT__storage = 0U;
        vlSelfRef.bitty_core__DOT__reg2_inst__DOT__storage = 0U;
        vlSelfRef.bitty_core__DOT__reg3_inst__DOT__storage = 0U;
        vlSelfRef.bitty_core__DOT__reg4_inst__DOT__storage = 0U;
        vlSelfRef.bitty_core__DOT__reg5_inst__DOT__storage = 0U;
        vlSelfRef.bitty_core__DOT__reg6_inst__DOT__storage = 0U;
        vlSelfRef.bitty_core__DOT__reg7_inst__DOT__storage = 0U;
        vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage = 0U;
        vlSelfRef.bitty_core__DOT__control_inst__DOT__state = 0U;
    } else {
        if (vlSelfRef.bitty_core__DOT__en_c) {
            vlSelfRef.bitty_core__DOT__reg_c_inst__DOT__storage 
                = vlSelfRef.alu_out;
        }
        if (vlSelfRef.bitty_core__DOT__en_s) {
            vlSelfRef.bitty_core__DOT__reg_s_inst__DOT__storage 
                = vlSelfRef.mux_out;
        }
        if (vlSelfRef.bitty_core__DOT__en_0) {
            vlSelfRef.bitty_core__DOT__reg0_inst__DOT__storage 
                = vlSelfRef.reg_c_out;
        }
        if (vlSelfRef.bitty_core__DOT__en_1) {
            vlSelfRef.bitty_core__DOT__reg1_inst__DOT__storage 
                = vlSelfRef.reg_c_out;
        }
        if (vlSelfRef.bitty_core__DOT__en_2) {
            vlSelfRef.bitty_core__DOT__reg2_inst__DOT__storage 
                = vlSelfRef.reg_c_out;
        }
        if (vlSelfRef.bitty_core__DOT__en_3) {
            vlSelfRef.bitty_core__DOT__reg3_inst__DOT__storage 
                = vlSelfRef.reg_c_out;
        }
        if (vlSelfRef.bitty_core__DOT__en_4) {
            vlSelfRef.bitty_core__DOT__reg4_inst__DOT__storage 
                = vlSelfRef.reg_c_out;
        }
        if (vlSelfRef.bitty_core__DOT__en_5) {
            vlSelfRef.bitty_core__DOT__reg5_inst__DOT__storage 
                = vlSelfRef.reg_c_out;
        }
        if (vlSelfRef.bitty_core__DOT__en_6) {
            vlSelfRef.bitty_core__DOT__reg6_inst__DOT__storage 
                = vlSelfRef.reg_c_out;
        }
        if (vlSelfRef.bitty_core__DOT__en_7) {
            vlSelfRef.bitty_core__DOT__reg7_inst__DOT__storage 
                = vlSelfRef.reg_c_out;
        }
        if (vlSelfRef.bitty_core__DOT__en_i) {
            vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage 
                = vlSelfRef.instruction;
        }
        if (vlSelfRef.run) {
            vlSelfRef.bitty_core__DOT__control_inst__DOT__state 
                = vlSelfRef.bitty_core__DOT__control_inst__DOT__next_state;
        }
    }
    vlSelfRef.reg_c_out = vlSelfRef.bitty_core__DOT__reg_c_inst__DOT__storage;
    vlSelfRef.reg_s_out = vlSelfRef.bitty_core__DOT__reg_s_inst__DOT__storage;
    vlSelfRef.reg0_out = vlSelfRef.bitty_core__DOT__reg0_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[0U] = vlSelfRef.bitty_core__DOT__reg0_inst__DOT__storage;
    vlSelfRef.reg1_out = vlSelfRef.bitty_core__DOT__reg1_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[1U] = vlSelfRef.bitty_core__DOT__reg1_inst__DOT__storage;
    vlSelfRef.reg2_out = vlSelfRef.bitty_core__DOT__reg2_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[2U] = vlSelfRef.bitty_core__DOT__reg2_inst__DOT__storage;
    vlSelfRef.reg3_out = vlSelfRef.bitty_core__DOT__reg3_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[3U] = vlSelfRef.bitty_core__DOT__reg3_inst__DOT__storage;
    vlSelfRef.reg4_out = vlSelfRef.bitty_core__DOT__reg4_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[4U] = vlSelfRef.bitty_core__DOT__reg4_inst__DOT__storage;
    vlSelfRef.reg5_out = vlSelfRef.bitty_core__DOT__reg5_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[5U] = vlSelfRef.bitty_core__DOT__reg5_inst__DOT__storage;
    vlSelfRef.reg6_out = vlSelfRef.bitty_core__DOT__reg6_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[6U] = vlSelfRef.bitty_core__DOT__reg6_inst__DOT__storage;
    vlSelfRef.reg7_out = vlSelfRef.bitty_core__DOT__reg7_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[7U] = vlSelfRef.bitty_core__DOT__reg7_inst__DOT__storage;
    vlSelfRef.reg_instr_out = vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__en_s = 0U;
    vlSelfRef.done = 0U;
    vlSelfRef.bitty_core__DOT__en_i = 0U;
    if ((1U & (~ ((IData)(vlSelfRef.bitty_core__DOT__control_inst__DOT__state) 
                  >> 1U)))) {
        if ((1U & (IData)(vlSelfRef.bitty_core__DOT__control_inst__DOT__state))) {
            vlSelfRef.bitty_core__DOT__en_s = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.bitty_core__DOT__control_inst__DOT__state)))) {
            vlSelfRef.bitty_core__DOT__en_i = 1U;
        }
    }
    vlSelfRef.bitty_core__DOT__en_c = 0U;
    vlSelfRef.bitty_core__DOT__en_0 = 0U;
    vlSelfRef.bitty_core__DOT__en_1 = 0U;
    vlSelfRef.bitty_core__DOT__en_2 = 0U;
    vlSelfRef.bitty_core__DOT__en_3 = 0U;
    vlSelfRef.bitty_core__DOT__en_4 = 0U;
    vlSelfRef.bitty_core__DOT__en_5 = 0U;
    vlSelfRef.bitty_core__DOT__en_6 = 0U;
    vlSelfRef.bitty_core__DOT__en_7 = 0U;
    __Vtableidx1 = vlSelfRef.bitty_core__DOT__control_inst__DOT__state;
    vlSelfRef.bitty_core__DOT__control_inst__DOT__next_state 
        = Vbitty_core__ConstPool__TABLE_hcac39648_0
        [__Vtableidx1];
    bitty_core__DOT__alu_sel = 0U;
    bitty_core__DOT__mux_sel = 0U;
    if ((2U & (IData)(vlSelfRef.bitty_core__DOT__control_inst__DOT__state))) {
        if ((1U & (IData)(vlSelfRef.bitty_core__DOT__control_inst__DOT__state))) {
            vlSelfRef.done = 1U;
            if ((1U & (~ ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                          >> 0xfU)))) {
                if ((1U & (~ ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                              >> 0xeU)))) {
                    if ((1U & (~ ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                  >> 0xdU)))) {
                        vlSelfRef.bitty_core__DOT__en_0 = 1U;
                    }
                    if ((0x2000U & (IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage))) {
                        vlSelfRef.bitty_core__DOT__en_1 = 1U;
                    }
                }
                if ((0x4000U & (IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage))) {
                    if ((1U & (~ ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                  >> 0xdU)))) {
                        vlSelfRef.bitty_core__DOT__en_2 = 1U;
                    }
                    if ((0x2000U & (IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage))) {
                        vlSelfRef.bitty_core__DOT__en_3 = 1U;
                    }
                }
            }
            if ((0x8000U & (IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage))) {
                if ((1U & (~ ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                              >> 0xeU)))) {
                    if ((1U & (~ ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                  >> 0xdU)))) {
                        vlSelfRef.bitty_core__DOT__en_4 = 1U;
                    }
                    if ((0x2000U & (IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage))) {
                        vlSelfRef.bitty_core__DOT__en_5 = 1U;
                    }
                }
                if ((0x4000U & (IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage))) {
                    if ((1U & (~ ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                  >> 0xdU)))) {
                        vlSelfRef.bitty_core__DOT__en_6 = 1U;
                    }
                    if ((0x2000U & (IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage))) {
                        vlSelfRef.bitty_core__DOT__en_7 = 1U;
                    }
                }
            }
        }
        if ((1U & (~ (IData)(vlSelfRef.bitty_core__DOT__control_inst__DOT__state)))) {
            vlSelfRef.bitty_core__DOT__en_c = 1U;
            bitty_core__DOT__alu_sel = (7U & ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                              >> 2U));
            bitty_core__DOT__mux_sel = (7U & ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                              >> 0xaU));
        }
    } else if ((1U & (IData)(vlSelfRef.bitty_core__DOT__control_inst__DOT__state))) {
        bitty_core__DOT__mux_sel = (7U & ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                          >> 0xdU));
    }
    vlSelfRef.mux_out = ((4U & (IData)(bitty_core__DOT__mux_sel))
                          ? ((2U & (IData)(bitty_core__DOT__mux_sel))
                              ? ((1U & (IData)(bitty_core__DOT__mux_sel))
                                  ? vlSelfRef.bitty_core__DOT__mux_in_array
                                 [7U] : vlSelfRef.bitty_core__DOT__mux_in_array
                                 [6U]) : ((1U & (IData)(bitty_core__DOT__mux_sel))
                                           ? vlSelfRef.bitty_core__DOT__mux_in_array
                                          [5U] : vlSelfRef.bitty_core__DOT__mux_in_array
                                          [4U])) : 
                         ((2U & (IData)(bitty_core__DOT__mux_sel))
                           ? ((1U & (IData)(bitty_core__DOT__mux_sel))
                               ? vlSelfRef.bitty_core__DOT__mux_in_array
                              [3U] : vlSelfRef.bitty_core__DOT__mux_in_array
                              [2U]) : ((1U & (IData)(bitty_core__DOT__mux_sel))
                                        ? vlSelfRef.bitty_core__DOT__mux_in_array
                                       [1U] : vlSelfRef.bitty_core__DOT__mux_in_array
                                       [0U])));
    vlSelfRef.alu_out = (0xffffU & ((4U & (IData)(bitty_core__DOT__alu_sel))
                                     ? ((2U & (IData)(bitty_core__DOT__alu_sel))
                                         ? ((1U & (IData)(bitty_core__DOT__alu_sel))
                                             ? (((IData)(vlSelfRef.reg_s_out) 
                                                 == (IData)(vlSelfRef.mux_out))
                                                 ? 0U
                                                 : 
                                                (((IData)(vlSelfRef.reg_s_out) 
                                                  > (IData)(vlSelfRef.mux_out))
                                                  ? 1U
                                                  : 2U))
                                             : VL_SHIFTR_III(16,16,16, (IData)(vlSelfRef.reg_s_out), (IData)(vlSelfRef.mux_out)))
                                         : ((1U & (IData)(bitty_core__DOT__alu_sel))
                                             ? VL_SHIFTL_III(16,16,16, (IData)(vlSelfRef.reg_s_out), (IData)(vlSelfRef.mux_out))
                                             : ((IData)(vlSelfRef.reg_s_out) 
                                                ^ (IData)(vlSelfRef.mux_out))))
                                     : ((2U & (IData)(bitty_core__DOT__alu_sel))
                                         ? ((1U & (IData)(bitty_core__DOT__alu_sel))
                                             ? ((IData)(vlSelfRef.reg_s_out) 
                                                | (IData)(vlSelfRef.mux_out))
                                             : ((IData)(vlSelfRef.reg_s_out) 
                                                & (IData)(vlSelfRef.mux_out)))
                                         : ((1U & (IData)(bitty_core__DOT__alu_sel))
                                             ? ((IData)(vlSelfRef.reg_s_out) 
                                                - (IData)(vlSelfRef.mux_out))
                                             : ((IData)(vlSelfRef.reg_s_out) 
                                                + (IData)(vlSelfRef.mux_out))))));
}

void Vbitty_core___024root___eval_triggers__act(Vbitty_core___024root* vlSelf);

bool Vbitty_core___024root___eval_phase__act(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___eval_phase__act\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vbitty_core___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vbitty_core___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vbitty_core___024root___eval_phase__nba(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___eval_phase__nba\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vbitty_core___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vbitty_core___024root___dump_triggers__nba(Vbitty_core___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vbitty_core___024root___dump_triggers__act(Vbitty_core___024root* vlSelf);
#endif  // VL_DEBUG

void Vbitty_core___024root___eval(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___eval\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vbitty_core___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("rtl/bitty_core.v", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vbitty_core___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("rtl/bitty_core.v", 1, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vbitty_core___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vbitty_core___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vbitty_core___024root___eval_debug_assertions(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___eval_debug_assertions\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY(((vlSelfRef.reset & 0xfeU)))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY(((vlSelfRef.run & 0xfeU)))) {
        Verilated::overWidthError("run");}
}
#endif  // VL_DEBUG
