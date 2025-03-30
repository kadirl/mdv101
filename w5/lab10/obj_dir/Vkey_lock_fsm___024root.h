// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vkey_lock_fsm.h for the primary calling header

#ifndef VERILATED_VKEY_LOCK_FSM___024ROOT_H_
#define VERILATED_VKEY_LOCK_FSM___024ROOT_H_  // guard

#include "verilated.h"


class Vkey_lock_fsm__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vkey_lock_fsm___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(key_in,3,0);
    VL_OUT8(state_debug,2,0);
    VL_OUT8(locked,0,0);
    CData/*2:0*/ key_lock_fsm__DOT__current_state;
    CData/*2:0*/ key_lock_fsm__DOT__next_state;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vkey_lock_fsm__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vkey_lock_fsm___024root(Vkey_lock_fsm__Syms* symsp, const char* v__name);
    ~Vkey_lock_fsm___024root();
    VL_UNCOPYABLE(Vkey_lock_fsm___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
