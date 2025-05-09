// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vbitty_core.h for the primary calling header

#ifndef VERILATED_VBITTY_CORE___024ROOT_H_
#define VERILATED_VBITTY_CORE___024ROOT_H_  // guard

#include "verilated.h"


class Vbitty_core__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vbitty_core___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(run,0,0);
    VL_OUT8(done,0,0);
    CData/*0:0*/ bitty_core__DOT__en_i;
    CData/*0:0*/ bitty_core__DOT__en_s;
    CData/*0:0*/ bitty_core__DOT__en_c;
    CData/*0:0*/ bitty_core__DOT__en_0;
    CData/*0:0*/ bitty_core__DOT__en_1;
    CData/*0:0*/ bitty_core__DOT__en_2;
    CData/*0:0*/ bitty_core__DOT__en_3;
    CData/*0:0*/ bitty_core__DOT__en_4;
    CData/*0:0*/ bitty_core__DOT__en_5;
    CData/*0:0*/ bitty_core__DOT__en_6;
    CData/*0:0*/ bitty_core__DOT__en_7;
    CData/*1:0*/ bitty_core__DOT__control_inst__DOT__state;
    CData/*1:0*/ bitty_core__DOT__control_inst__DOT__next_state;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__reset__0;
    CData/*0:0*/ __VactContinue;
    VL_IN16(instruction,15,0);
    VL_OUT16(reg_instr_out,15,0);
    VL_OUT16(reg_s_out,15,0);
    VL_OUT16(reg_c_out,15,0);
    VL_OUT16(reg0_out,15,0);
    VL_OUT16(reg1_out,15,0);
    VL_OUT16(reg2_out,15,0);
    VL_OUT16(reg3_out,15,0);
    VL_OUT16(reg4_out,15,0);
    VL_OUT16(reg5_out,15,0);
    VL_OUT16(reg6_out,15,0);
    VL_OUT16(reg7_out,15,0);
    VL_OUT16(mux_out,15,0);
    VL_OUT16(alu_out,15,0);
    SData/*15:0*/ bitty_core__DOT__reg_instr_inst__DOT__storage;
    SData/*15:0*/ bitty_core__DOT__reg_s_inst__DOT__storage;
    SData/*15:0*/ bitty_core__DOT__reg_c_inst__DOT__storage;
    SData/*15:0*/ bitty_core__DOT__reg0_inst__DOT__storage;
    SData/*15:0*/ bitty_core__DOT__reg1_inst__DOT__storage;
    SData/*15:0*/ bitty_core__DOT__reg2_inst__DOT__storage;
    SData/*15:0*/ bitty_core__DOT__reg3_inst__DOT__storage;
    SData/*15:0*/ bitty_core__DOT__reg4_inst__DOT__storage;
    SData/*15:0*/ bitty_core__DOT__reg5_inst__DOT__storage;
    SData/*15:0*/ bitty_core__DOT__reg6_inst__DOT__storage;
    SData/*15:0*/ bitty_core__DOT__reg7_inst__DOT__storage;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<SData/*15:0*/, 9> bitty_core__DOT__mux_in_array;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vbitty_core__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vbitty_core___024root(Vbitty_core__Syms* symsp, const char* v__name);
    ~Vbitty_core___024root();
    VL_UNCOPYABLE(Vbitty_core___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
