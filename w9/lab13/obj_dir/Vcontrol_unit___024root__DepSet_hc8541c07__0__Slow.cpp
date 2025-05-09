// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcontrol_unit.h for the primary calling header

#include "Vcontrol_unit__pch.h"
#include "Vcontrol_unit___024root.h"

VL_ATTR_COLD void Vcontrol_unit___024root___eval_static(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___eval_static\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vcontrol_unit___024root___eval_initial__TOP(Vcontrol_unit___024root* vlSelf);

VL_ATTR_COLD void Vcontrol_unit___024root___eval_initial(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___eval_initial\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vcontrol_unit___024root___eval_initial__TOP(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__reset__0 = vlSelfRef.reset;
}

VL_ATTR_COLD void Vcontrol_unit___024root___eval_initial__TOP(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___eval_initial__TOP\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.i_out = 0U;
}

VL_ATTR_COLD void Vcontrol_unit___024root___eval_final(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___eval_final\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontrol_unit___024root___dump_triggers__stl(Vcontrol_unit___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vcontrol_unit___024root___eval_phase__stl(Vcontrol_unit___024root* vlSelf);

VL_ATTR_COLD void Vcontrol_unit___024root___eval_settle(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___eval_settle\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
            Vcontrol_unit___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("rtl/control_unit.v", 1, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vcontrol_unit___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontrol_unit___024root___dump_triggers__stl(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___dump_triggers__stl\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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

VL_ATTR_COLD void Vcontrol_unit___024root___stl_sequent__TOP__0(Vcontrol_unit___024root* vlSelf);

VL_ATTR_COLD void Vcontrol_unit___024root___eval_stl(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___eval_stl\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vcontrol_unit___024root___stl_sequent__TOP__0(vlSelf);
    }
}

extern const VlUnpacked<CData/*1:0*/, 4> Vcontrol_unit__ConstPool__TABLE_hcac39648_0;

VL_ATTR_COLD void Vcontrol_unit___024root___stl_sequent__TOP__0(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___stl_sequent__TOP__0\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*1:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    vlSelfRef.en_s = 0U;
    vlSelfRef.done = 0U;
    vlSelfRef.en_i = 0U;
    if ((1U & (~ ((IData)(vlSelfRef.control_unit__DOT__state) 
                  >> 1U)))) {
        if ((1U & (IData)(vlSelfRef.control_unit__DOT__state))) {
            vlSelfRef.en_s = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.control_unit__DOT__state)))) {
            vlSelfRef.en_i = 1U;
        }
    }
    vlSelfRef.en_c = 0U;
    vlSelfRef.i_out = (0xffU & ((IData)(vlSelfRef.d_in) 
                                >> 5U));
    vlSelfRef.en_0 = 0U;
    vlSelfRef.en_1 = 0U;
    vlSelfRef.en_2 = 0U;
    vlSelfRef.en_3 = 0U;
    vlSelfRef.en_4 = 0U;
    vlSelfRef.en_5 = 0U;
    vlSelfRef.en_6 = 0U;
    vlSelfRef.en_7 = 0U;
    vlSelfRef.mux_sel = 0U;
    vlSelfRef.alu_sel = 0U;
    if ((2U & (IData)(vlSelfRef.control_unit__DOT__state))) {
        if ((1U & (IData)(vlSelfRef.control_unit__DOT__state))) {
            vlSelfRef.done = 1U;
            if ((1U & (~ (1U & ((IData)(vlSelfRef.d_in) 
                                >> 0xfU))))) {
                if ((1U & (~ (3U & ((IData)(vlSelfRef.d_in) 
                                    >> 0xeU))))) {
                    if ((1U & (~ (7U & ((IData)(vlSelfRef.d_in) 
                                        >> 0xdU))))) {
                        vlSelfRef.en_0 = 1U;
                    }
                    if ((0x2000U & (IData)(vlSelfRef.d_in))) {
                        vlSelfRef.en_1 = 1U;
                    }
                }
                if ((0x4000U & (IData)(vlSelfRef.d_in))) {
                    if ((1U & (~ (7U & ((IData)(vlSelfRef.d_in) 
                                        >> 0xdU))))) {
                        vlSelfRef.en_2 = 1U;
                    }
                    if ((0x2000U & (IData)(vlSelfRef.d_in))) {
                        vlSelfRef.en_3 = 1U;
                    }
                }
            }
            if ((0x8000U & (IData)(vlSelfRef.d_in))) {
                if ((1U & (~ (3U & ((IData)(vlSelfRef.d_in) 
                                    >> 0xeU))))) {
                    if ((1U & (~ (7U & ((IData)(vlSelfRef.d_in) 
                                        >> 0xdU))))) {
                        vlSelfRef.en_4 = 1U;
                    }
                    if ((0x2000U & (IData)(vlSelfRef.d_in))) {
                        vlSelfRef.en_5 = 1U;
                    }
                }
                if ((0x4000U & (IData)(vlSelfRef.d_in))) {
                    if ((1U & (~ (7U & ((IData)(vlSelfRef.d_in) 
                                        >> 0xdU))))) {
                        vlSelfRef.en_6 = 1U;
                    }
                    if ((0x2000U & (IData)(vlSelfRef.d_in))) {
                        vlSelfRef.en_7 = 1U;
                    }
                }
            }
        }
        if ((1U & (~ (IData)(vlSelfRef.control_unit__DOT__state)))) {
            vlSelfRef.en_c = 1U;
            vlSelfRef.mux_sel = ((1U == (3U & (IData)(vlSelfRef.d_in)))
                                  ? 8U : (7U & ((IData)(vlSelfRef.d_in) 
                                                >> 0xaU)));
            vlSelfRef.alu_sel = (7U & ((IData)(vlSelfRef.d_in) 
                                       >> 2U));
        }
    } else if ((1U & (IData)(vlSelfRef.control_unit__DOT__state))) {
        vlSelfRef.mux_sel = (7U & ((IData)(vlSelfRef.d_in) 
                                   >> 0xdU));
    }
    __Vtableidx1 = vlSelfRef.control_unit__DOT__state;
    vlSelfRef.control_unit__DOT__next_state = Vcontrol_unit__ConstPool__TABLE_hcac39648_0
        [__Vtableidx1];
}

VL_ATTR_COLD void Vcontrol_unit___024root___eval_triggers__stl(Vcontrol_unit___024root* vlSelf);

VL_ATTR_COLD bool Vcontrol_unit___024root___eval_phase__stl(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___eval_phase__stl\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vcontrol_unit___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vcontrol_unit___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontrol_unit___024root___dump_triggers__ico(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___dump_triggers__ico\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontrol_unit___024root___dump_triggers__act(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___dump_triggers__act\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
VL_ATTR_COLD void Vcontrol_unit___024root___dump_triggers__nba(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___dump_triggers__nba\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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

VL_ATTR_COLD void Vcontrol_unit___024root___ctor_var_reset(Vcontrol_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___ctor_var_reset\n"); );
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->d_in = VL_RAND_RESET_I(16);
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->run = VL_RAND_RESET_I(1);
    vlSelf->alu_sel = VL_RAND_RESET_I(3);
    vlSelf->mux_sel = VL_RAND_RESET_I(4);
    vlSelf->i_out = VL_RAND_RESET_I(16);
    vlSelf->en_s = VL_RAND_RESET_I(1);
    vlSelf->en_c = VL_RAND_RESET_I(1);
    vlSelf->en_0 = VL_RAND_RESET_I(1);
    vlSelf->en_1 = VL_RAND_RESET_I(1);
    vlSelf->en_2 = VL_RAND_RESET_I(1);
    vlSelf->en_3 = VL_RAND_RESET_I(1);
    vlSelf->en_4 = VL_RAND_RESET_I(1);
    vlSelf->en_5 = VL_RAND_RESET_I(1);
    vlSelf->en_6 = VL_RAND_RESET_I(1);
    vlSelf->en_7 = VL_RAND_RESET_I(1);
    vlSelf->en_i = VL_RAND_RESET_I(1);
    vlSelf->done = VL_RAND_RESET_I(1);
    vlSelf->control_unit__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->control_unit__DOT__next_state = VL_RAND_RESET_I(2);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__reset__0 = VL_RAND_RESET_I(1);
}
