// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Valu.h for the primary calling header

#ifndef VERILATED_VALU___024ROOT_H_
#define VERILATED_VALU___024ROOT_H_  // guard

#include "verilated.h"


class Valu__Syms;

class alignas(VL_CACHE_LINE_BYTES) Valu___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(carry_in,0,0);
    VL_IN8(select,3,0);
    VL_IN8(mode,0,0);
    VL_OUT8(carry_out,0,0);
    VL_OUT8(compare,0,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __VactContinue;
    VL_IN16(in_a,15,0);
    VL_IN16(in_b,15,0);
    VL_OUT16(alu_out,15,0);
    SData/*15:0*/ alu__DOT__arithmetic_out;
    SData/*15:0*/ alu__DOT__logic_out;
    SData/*15:0*/ alu__DOT__AU__DOT__ab;
    SData/*15:0*/ alu__DOT__AU__DOT__anotb;
    SData/*15:0*/ alu__DOT__AU__DOT__aorb;
    SData/*15:0*/ alu__DOT__AU__DOT__aornotb;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    Valu__Syms* const vlSymsp;

    // CONSTRUCTORS
    Valu___024root(Valu__Syms* symsp, const char* v__name);
    ~Valu___024root();
    VL_UNCOPYABLE(Valu___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
