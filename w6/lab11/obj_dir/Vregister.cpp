// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vregister__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vregister::Vregister(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vregister__Syms(contextp(), _vcname__, this)}
    , reset{vlSymsp->TOP.reset}
    , clk{vlSymsp->TOP.clk}
    , en{vlSymsp->TOP.en}
    , d_in{vlSymsp->TOP.d_in}
    , d_out{vlSymsp->TOP.d_out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vregister::Vregister(const char* _vcname__)
    : Vregister(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vregister::~Vregister() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vregister___024root___eval_debug_assertions(Vregister___024root* vlSelf);
#endif  // VL_DEBUG
void Vregister___024root___eval_static(Vregister___024root* vlSelf);
void Vregister___024root___eval_initial(Vregister___024root* vlSelf);
void Vregister___024root___eval_settle(Vregister___024root* vlSelf);
void Vregister___024root___eval(Vregister___024root* vlSelf);

void Vregister::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vregister::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vregister___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vregister___024root___eval_static(&(vlSymsp->TOP));
        Vregister___024root___eval_initial(&(vlSymsp->TOP));
        Vregister___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vregister___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vregister::eventsPending() { return false; }

uint64_t Vregister::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vregister::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vregister___024root___eval_final(Vregister___024root* vlSelf);

VL_ATTR_COLD void Vregister::final() {
    Vregister___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vregister::hierName() const { return vlSymsp->name(); }
const char* Vregister::modelName() const { return "Vregister"; }
unsigned Vregister::threads() const { return 1; }
void Vregister::prepareClone() const { contextp()->prepareClone(); }
void Vregister::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vregister::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vregister___024root__trace_decl_types(VerilatedVcd* tracep);

void Vregister___024root__trace_init_top(Vregister___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vregister___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vregister___024root*>(voidSelf);
    Vregister__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vregister___024root__trace_decl_types(tracep);
    Vregister___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vregister___024root__trace_register(Vregister___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vregister::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vregister::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vregister___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
