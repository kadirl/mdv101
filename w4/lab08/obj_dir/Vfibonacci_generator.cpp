// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vfibonacci_generator__pch.h"

//============================================================
// Constructors

Vfibonacci_generator::Vfibonacci_generator(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vfibonacci_generator__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , enable{vlSymsp->TOP.enable}
    , fib_out{vlSymsp->TOP.fib_out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vfibonacci_generator::Vfibonacci_generator(const char* _vcname__)
    : Vfibonacci_generator(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vfibonacci_generator::~Vfibonacci_generator() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vfibonacci_generator___024root___eval_debug_assertions(Vfibonacci_generator___024root* vlSelf);
#endif  // VL_DEBUG
void Vfibonacci_generator___024root___eval_static(Vfibonacci_generator___024root* vlSelf);
void Vfibonacci_generator___024root___eval_initial(Vfibonacci_generator___024root* vlSelf);
void Vfibonacci_generator___024root___eval_settle(Vfibonacci_generator___024root* vlSelf);
void Vfibonacci_generator___024root___eval(Vfibonacci_generator___024root* vlSelf);

void Vfibonacci_generator::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vfibonacci_generator::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vfibonacci_generator___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vfibonacci_generator___024root___eval_static(&(vlSymsp->TOP));
        Vfibonacci_generator___024root___eval_initial(&(vlSymsp->TOP));
        Vfibonacci_generator___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vfibonacci_generator___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vfibonacci_generator::eventsPending() { return false; }

uint64_t Vfibonacci_generator::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vfibonacci_generator::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vfibonacci_generator___024root___eval_final(Vfibonacci_generator___024root* vlSelf);

VL_ATTR_COLD void Vfibonacci_generator::final() {
    Vfibonacci_generator___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vfibonacci_generator::hierName() const { return vlSymsp->name(); }
const char* Vfibonacci_generator::modelName() const { return "Vfibonacci_generator"; }
unsigned Vfibonacci_generator::threads() const { return 1; }
void Vfibonacci_generator::prepareClone() const { contextp()->prepareClone(); }
void Vfibonacci_generator::atClone() const {
    contextp()->threadPoolpOnClone();
}
