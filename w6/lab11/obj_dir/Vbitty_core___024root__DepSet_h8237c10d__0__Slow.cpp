// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vbitty_core.h for the primary calling header

#include "Vbitty_core__pch.h"
#include "Vbitty_core___024root.h"

VL_ATTR_COLD void Vbitty_core___024root___eval_static(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___eval_static\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vbitty_core___024root___eval_initial(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___eval_initial\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__reset__0 = vlSelfRef.reset;
}

VL_ATTR_COLD void Vbitty_core___024root___eval_final(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___eval_final\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vbitty_core___024root___dump_triggers__stl(Vbitty_core___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vbitty_core___024root___eval_phase__stl(Vbitty_core___024root* vlSelf);

VL_ATTR_COLD void Vbitty_core___024root___eval_settle(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___eval_settle\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
            Vbitty_core___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("rtl/bitty_core.v", 1, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vbitty_core___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vbitty_core___024root___dump_triggers__stl(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___dump_triggers__stl\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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

VL_ATTR_COLD void Vbitty_core___024root___stl_sequent__TOP__0(Vbitty_core___024root* vlSelf);
VL_ATTR_COLD void Vbitty_core___024root____Vm_traceActivitySetAll(Vbitty_core___024root* vlSelf);

VL_ATTR_COLD void Vbitty_core___024root___eval_stl(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___eval_stl\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vbitty_core___024root___stl_sequent__TOP__0(vlSelf);
        Vbitty_core___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

extern const VlUnpacked<CData/*1:0*/, 4> Vbitty_core__ConstPool__TABLE_hcac39648_0;

VL_ATTR_COLD void Vbitty_core___024root___stl_sequent__TOP__0(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___stl_sequent__TOP__0\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*1:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
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
    vlSelfRef.reg_instr_out = vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage;
    vlSelfRef.reg_c_out = vlSelfRef.bitty_core__DOT__reg_c_inst__DOT__storage;
    vlSelfRef.reg0_out = vlSelfRef.bitty_core__DOT__reg0_inst__DOT__storage;
    vlSelfRef.reg1_out = vlSelfRef.bitty_core__DOT__reg1_inst__DOT__storage;
    vlSelfRef.reg2_out = vlSelfRef.bitty_core__DOT__reg2_inst__DOT__storage;
    vlSelfRef.reg3_out = vlSelfRef.bitty_core__DOT__reg3_inst__DOT__storage;
    vlSelfRef.reg4_out = vlSelfRef.bitty_core__DOT__reg4_inst__DOT__storage;
    vlSelfRef.reg5_out = vlSelfRef.bitty_core__DOT__reg5_inst__DOT__storage;
    vlSelfRef.reg6_out = vlSelfRef.bitty_core__DOT__reg6_inst__DOT__storage;
    vlSelfRef.reg7_out = vlSelfRef.bitty_core__DOT__reg7_inst__DOT__storage;
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
    vlSelfRef.bitty_core__DOT__mode = 0U;
    vlSelfRef.reg_s_out = vlSelfRef.bitty_core__DOT__reg_s_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__alu_sel = 0U;
    vlSelfRef.bitty_core__DOT__mux_sel = 0U;
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
            vlSelfRef.bitty_core__DOT__mode = (1U & 
                                               ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                                >> 2U));
            vlSelfRef.bitty_core__DOT__alu_sel = (0xfU 
                                                  & ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                                     >> 3U));
            vlSelfRef.bitty_core__DOT__mux_sel = (7U 
                                                  & ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                                     >> 0xaU));
        }
    } else if ((1U & (IData)(vlSelfRef.bitty_core__DOT__control_inst__DOT__state))) {
        vlSelfRef.bitty_core__DOT__mux_sel = (7U & 
                                              ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                               >> 0xdU));
    }
    vlSelfRef.bitty_core__DOT__mux_in_array[0U] = vlSelfRef.bitty_core__DOT__reg0_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[1U] = vlSelfRef.bitty_core__DOT__reg1_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[2U] = vlSelfRef.bitty_core__DOT__reg2_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[3U] = vlSelfRef.bitty_core__DOT__reg3_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[4U] = vlSelfRef.bitty_core__DOT__reg4_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[5U] = vlSelfRef.bitty_core__DOT__reg5_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[6U] = vlSelfRef.bitty_core__DOT__reg6_inst__DOT__storage;
    vlSelfRef.bitty_core__DOT__mux_in_array[7U] = vlSelfRef.bitty_core__DOT__reg7_inst__DOT__storage;
    vlSelfRef.mux_out = ((4U & (IData)(vlSelfRef.bitty_core__DOT__mux_sel))
                          ? ((2U & (IData)(vlSelfRef.bitty_core__DOT__mux_sel))
                              ? ((1U & (IData)(vlSelfRef.bitty_core__DOT__mux_sel))
                                  ? vlSelfRef.bitty_core__DOT__mux_in_array
                                 [7U] : vlSelfRef.bitty_core__DOT__mux_in_array
                                 [6U]) : ((1U & (IData)(vlSelfRef.bitty_core__DOT__mux_sel))
                                           ? vlSelfRef.bitty_core__DOT__mux_in_array
                                          [5U] : vlSelfRef.bitty_core__DOT__mux_in_array
                                          [4U])) : 
                         ((2U & (IData)(vlSelfRef.bitty_core__DOT__mux_sel))
                           ? ((1U & (IData)(vlSelfRef.bitty_core__DOT__mux_sel))
                               ? vlSelfRef.bitty_core__DOT__mux_in_array
                              [3U] : vlSelfRef.bitty_core__DOT__mux_in_array
                              [2U]) : ((1U & (IData)(vlSelfRef.bitty_core__DOT__mux_sel))
                                        ? vlSelfRef.bitty_core__DOT__mux_in_array
                                       [1U] : vlSelfRef.bitty_core__DOT__mux_in_array
                                       [0U])));
    vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__anotb 
        = ((~ (IData)(vlSelfRef.mux_out)) & (IData)(vlSelfRef.bitty_core__DOT__reg_s_inst__DOT__storage));
    vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__aorb 
        = ((IData)(vlSelfRef.bitty_core__DOT__reg_s_inst__DOT__storage) 
           | (IData)(vlSelfRef.mux_out));
    vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__ab 
        = ((IData)(vlSelfRef.bitty_core__DOT__reg_s_inst__DOT__storage) 
           & (IData)(vlSelfRef.mux_out));
    vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__aornotb 
        = (0xffffU & ((~ (IData)(vlSelfRef.mux_out)) 
                      | (IData)(vlSelfRef.bitty_core__DOT__reg_s_inst__DOT__storage)));
    if ((8U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
        if ((4U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
            if ((2U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
                if ((1U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
                    vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                        = (0xffffU & (IData)(vlSelfRef.reg_s_out));
                    vlSelfRef.bitty_core__DOT__cout 
                        = (1U & (1U & (((IData)(vlSelfRef.reg_s_out) 
                                        - (IData)(1U)) 
                                       >> 0x10U)));
                    vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                        = (0xffffU & ((IData)(vlSelfRef.reg_s_out) 
                                      - (IData)(1U)));
                } else {
                    vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                        = (0xffffU & ((IData)(vlSelfRef.reg_s_out) 
                                      | (IData)(vlSelfRef.mux_out)));
                    vlSelfRef.bitty_core__DOT__cout 
                        = (1U & (1U & (((IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__aornotb) 
                                        + (IData)(vlSelfRef.reg_s_out)) 
                                       >> 0x10U)));
                    vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                        = (0xffffU & ((IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__aornotb) 
                                      + (IData)(vlSelfRef.reg_s_out)));
                }
            } else if ((1U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
                vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                    = (0xffffU & ((IData)(vlSelfRef.reg_s_out) 
                                  | (~ (IData)(vlSelfRef.mux_out))));
                vlSelfRef.bitty_core__DOT__cout = (1U 
                                                   & (1U 
                                                      & (((IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__aorb) 
                                                          + (IData)(vlSelfRef.reg_s_out)) 
                                                         >> 0x10U)));
                vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                    = (0xffffU & ((IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__aorb) 
                                  + (IData)(vlSelfRef.reg_s_out)));
            } else {
                vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                    = (0xffffU & 1U);
                vlSelfRef.bitty_core__DOT__cout = (1U 
                                                   & (1U 
                                                      & (((IData)(vlSelfRef.reg_s_out) 
                                                          + (IData)(vlSelfRef.reg_s_out)) 
                                                         >> 0x10U)));
                vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                    = (0xffffU & ((IData)(vlSelfRef.reg_s_out) 
                                  + (IData)(vlSelfRef.reg_s_out)));
            }
        } else if ((2U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
            if ((1U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
                vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                    = (0xffffU & ((IData)(vlSelfRef.reg_s_out) 
                                  & (IData)(vlSelfRef.mux_out)));
                vlSelfRef.bitty_core__DOT__cout = (1U 
                                                   & (1U 
                                                      & (((IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__ab) 
                                                          - (IData)(1U)) 
                                                         >> 0x10U)));
                vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                    = (0xffffU & ((IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__ab) 
                                  - (IData)(1U)));
            } else {
                vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                    = (0xffffU & (IData)(vlSelfRef.mux_out));
                vlSelfRef.bitty_core__DOT__cout = (1U 
                                                   & (1U 
                                                      & (((IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__aornotb) 
                                                          + (IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__ab)) 
                                                         >> 0x10U)));
                vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                    = (0xffffU & ((IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__aornotb) 
                                  + (IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__ab)));
            }
        } else if ((1U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
            vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                = (0xffffU & (~ ((IData)(vlSelfRef.reg_s_out) 
                                 ^ (IData)(vlSelfRef.mux_out))));
            vlSelfRef.bitty_core__DOT__cout = (1U & 
                                               (1U 
                                                & (((IData)(vlSelfRef.reg_s_out) 
                                                    + (IData)(vlSelfRef.mux_out)) 
                                                   >> 0x10U)));
            vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                = (0xffffU & ((IData)(vlSelfRef.reg_s_out) 
                              + (IData)(vlSelfRef.mux_out)));
        } else {
            vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                = (0xffffU & ((~ (IData)(vlSelfRef.reg_s_out)) 
                              | (IData)(vlSelfRef.mux_out)));
            vlSelfRef.bitty_core__DOT__cout = (1U & 
                                               (1U 
                                                & (((IData)(vlSelfRef.reg_s_out) 
                                                    + (IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__ab)) 
                                                   >> 0x10U)));
            vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                = (0xffffU & ((IData)(vlSelfRef.reg_s_out) 
                              + (IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__ab)));
        }
    } else if ((4U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
        if ((2U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
            if ((1U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
                vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                    = (0xffffU & ((IData)(vlSelfRef.reg_s_out) 
                                  & (~ (IData)(vlSelfRef.mux_out))));
                vlSelfRef.bitty_core__DOT__cout = (1U 
                                                   & (1U 
                                                      & (((IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__anotb) 
                                                          - (IData)(1U)) 
                                                         >> 0x10U)));
                vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                    = (0xffffU & ((IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__anotb) 
                                  - (IData)(1U)));
            } else {
                vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                    = (0xffffU & ((IData)(vlSelfRef.reg_s_out) 
                                  ^ (IData)(vlSelfRef.mux_out)));
                vlSelfRef.bitty_core__DOT__cout = (1U 
                                                   & (1U 
                                                      & ((((IData)(vlSelfRef.reg_s_out) 
                                                           - (IData)(vlSelfRef.mux_out)) 
                                                          - (IData)(1U)) 
                                                         >> 0x10U)));
                vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                    = (0xffffU & (((IData)(vlSelfRef.reg_s_out) 
                                   - (IData)(vlSelfRef.mux_out)) 
                                  - (IData)(1U)));
            }
        } else if ((1U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
            vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                = (0xffffU & (~ (IData)(vlSelfRef.mux_out)));
            vlSelfRef.bitty_core__DOT__cout = (1U & 
                                               (((IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__aorb) 
                                                 | (IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__anotb)) 
                                                >> 0x10U));
            vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                = (0xffffU & ((IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__aorb) 
                              | (IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__anotb)));
        } else {
            vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                = (0xffffU & (~ ((IData)(vlSelfRef.reg_s_out) 
                                 & (IData)(vlSelfRef.mux_out))));
            vlSelfRef.bitty_core__DOT__cout = (1U & 
                                               (((IData)(vlSelfRef.reg_s_out) 
                                                 | (IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__anotb)) 
                                                >> 0x10U));
            vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                = (0xffffU & ((IData)(vlSelfRef.reg_s_out) 
                              | (IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__anotb)));
        }
    } else if ((2U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
        if ((1U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
            vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                = (0xffffU & 0U);
            vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                = (0xffffU & 0xffffU);
        } else {
            vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
                = (0xffffU & ((~ (IData)(vlSelfRef.reg_s_out)) 
                              & (IData)(vlSelfRef.mux_out)));
            vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
                = (0xffffU & ((IData)(vlSelfRef.reg_s_out) 
                              | (~ (IData)(vlSelfRef.mux_out))));
        }
        vlSelfRef.bitty_core__DOT__cout = (1U & VL_REDOR_I(
                                                           (1U 
                                                            & (~ (IData)(vlSelfRef.bitty_core__DOT__alu_sel)))));
    } else if ((1U & (IData)(vlSelfRef.bitty_core__DOT__alu_sel))) {
        vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
            = (0xffffU & (~ ((IData)(vlSelfRef.reg_s_out) 
                             | (IData)(vlSelfRef.mux_out))));
        vlSelfRef.bitty_core__DOT__cout = (1U & (((IData)(vlSelfRef.reg_s_out) 
                                                  | (IData)(vlSelfRef.mux_out)) 
                                                 >> 0x10U));
        vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
            = (0xffffU & ((IData)(vlSelfRef.reg_s_out) 
                          | (IData)(vlSelfRef.mux_out)));
    } else {
        vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out 
            = (0xffffU & (~ (IData)(vlSelfRef.reg_s_out)));
        vlSelfRef.bitty_core__DOT__cout = (1U & ((IData)(vlSelfRef.reg_s_out) 
                                                 >> 0x10U));
        vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out 
            = (0xffffU & (IData)(vlSelfRef.reg_s_out));
    }
    vlSelfRef.alu_out = ((IData)(vlSelfRef.bitty_core__DOT__mode)
                          ? (IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out)
                          : (IData)(vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out));
}

VL_ATTR_COLD void Vbitty_core___024root___eval_triggers__stl(Vbitty_core___024root* vlSelf);

VL_ATTR_COLD bool Vbitty_core___024root___eval_phase__stl(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___eval_phase__stl\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vbitty_core___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vbitty_core___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vbitty_core___024root___dump_triggers__act(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___dump_triggers__act\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge reset)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vbitty_core___024root___dump_triggers__nba(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___dump_triggers__nba\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge reset)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vbitty_core___024root____Vm_traceActivitySetAll(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root____Vm_traceActivitySetAll\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void Vbitty_core___024root___ctor_var_reset(Vbitty_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root___ctor_var_reset\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->instruction = VL_RAND_RESET_I(16);
    vlSelf->run = VL_RAND_RESET_I(1);
    vlSelf->done = VL_RAND_RESET_I(1);
    vlSelf->reg_instr_out = VL_RAND_RESET_I(16);
    vlSelf->reg_s_out = VL_RAND_RESET_I(16);
    vlSelf->reg_c_out = VL_RAND_RESET_I(16);
    vlSelf->reg0_out = VL_RAND_RESET_I(16);
    vlSelf->reg1_out = VL_RAND_RESET_I(16);
    vlSelf->reg2_out = VL_RAND_RESET_I(16);
    vlSelf->reg3_out = VL_RAND_RESET_I(16);
    vlSelf->reg4_out = VL_RAND_RESET_I(16);
    vlSelf->reg5_out = VL_RAND_RESET_I(16);
    vlSelf->reg6_out = VL_RAND_RESET_I(16);
    vlSelf->reg7_out = VL_RAND_RESET_I(16);
    vlSelf->mux_out = VL_RAND_RESET_I(16);
    vlSelf->alu_out = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__en_i = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__en_s = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__en_c = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__en_0 = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__en_1 = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__en_2 = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__en_3 = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__en_4 = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__en_5 = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__en_6 = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__en_7 = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__mode = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__cout = VL_RAND_RESET_I(1);
    vlSelf->bitty_core__DOT__alu_sel = VL_RAND_RESET_I(4);
    vlSelf->bitty_core__DOT__mux_sel = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->bitty_core__DOT__mux_in_array[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->bitty_core__DOT__control_inst__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->bitty_core__DOT__control_inst__DOT__next_state = VL_RAND_RESET_I(2);
    vlSelf->bitty_core__DOT__reg_instr_inst__DOT__storage = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__reg_s_inst__DOT__storage = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__reg_c_inst__DOT__storage = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__reg0_inst__DOT__storage = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__reg1_inst__DOT__storage = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__reg2_inst__DOT__storage = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__reg3_inst__DOT__storage = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__reg4_inst__DOT__storage = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__reg5_inst__DOT__storage = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__reg6_inst__DOT__storage = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__reg7_inst__DOT__storage = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__alu_inst__DOT__arithmetic_out = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__alu_inst__DOT__logic_out = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__alu_inst__DOT__AU__DOT__ab = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__alu_inst__DOT__AU__DOT__anotb = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__alu_inst__DOT__AU__DOT__aorb = VL_RAND_RESET_I(16);
    vlSelf->bitty_core__DOT__alu_inst__DOT__AU__DOT__aornotb = VL_RAND_RESET_I(16);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__reset__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
