// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VKEY_LOCK_FSM__SYMS_H_
#define VERILATED_VKEY_LOCK_FSM__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vkey_lock_fsm.h"

// INCLUDE MODULE CLASSES
#include "Vkey_lock_fsm___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vkey_lock_fsm__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vkey_lock_fsm* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vkey_lock_fsm___024root        TOP;

    // CONSTRUCTORS
    Vkey_lock_fsm__Syms(VerilatedContext* contextp, const char* namep, Vkey_lock_fsm* modelp);
    ~Vkey_lock_fsm__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
