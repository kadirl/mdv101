// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vbitty_core__Syms.h"


void Vbitty_core___024root__trace_chg_0_sub_0(Vbitty_core___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vbitty_core___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root__trace_chg_0\n"); );
    // Init
    Vbitty_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vbitty_core___024root*>(voidSelf);
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vbitty_core___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vbitty_core___024root__trace_chg_0_sub_0(Vbitty_core___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root__trace_chg_0_sub_0\n"); );
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgBit(oldp+0,(vlSelfRef.bitty_core__DOT__en_i));
        bufp->chgBit(oldp+1,(vlSelfRef.bitty_core__DOT__en_s));
        bufp->chgBit(oldp+2,(vlSelfRef.bitty_core__DOT__en_c));
        bufp->chgBit(oldp+3,(vlSelfRef.bitty_core__DOT__en_0));
        bufp->chgBit(oldp+4,(vlSelfRef.bitty_core__DOT__en_1));
        bufp->chgBit(oldp+5,(vlSelfRef.bitty_core__DOT__en_2));
        bufp->chgBit(oldp+6,(vlSelfRef.bitty_core__DOT__en_3));
        bufp->chgBit(oldp+7,(vlSelfRef.bitty_core__DOT__en_4));
        bufp->chgBit(oldp+8,(vlSelfRef.bitty_core__DOT__en_5));
        bufp->chgBit(oldp+9,(vlSelfRef.bitty_core__DOT__en_6));
        bufp->chgBit(oldp+10,(vlSelfRef.bitty_core__DOT__en_7));
        bufp->chgBit(oldp+11,(vlSelfRef.bitty_core__DOT__mode));
        bufp->chgBit(oldp+12,(vlSelfRef.bitty_core__DOT__cout));
        bufp->chgCData(oldp+13,(vlSelfRef.bitty_core__DOT__alu_sel),4);
        bufp->chgCData(oldp+14,(vlSelfRef.bitty_core__DOT__mux_sel),3);
        bufp->chgSData(oldp+15,(vlSelfRef.bitty_core__DOT__mux_in_array[0]),16);
        bufp->chgSData(oldp+16,(vlSelfRef.bitty_core__DOT__mux_in_array[1]),16);
        bufp->chgSData(oldp+17,(vlSelfRef.bitty_core__DOT__mux_in_array[2]),16);
        bufp->chgSData(oldp+18,(vlSelfRef.bitty_core__DOT__mux_in_array[3]),16);
        bufp->chgSData(oldp+19,(vlSelfRef.bitty_core__DOT__mux_in_array[4]),16);
        bufp->chgSData(oldp+20,(vlSelfRef.bitty_core__DOT__mux_in_array[5]),16);
        bufp->chgSData(oldp+21,(vlSelfRef.bitty_core__DOT__mux_in_array[6]),16);
        bufp->chgSData(oldp+22,(vlSelfRef.bitty_core__DOT__mux_in_array[7]),16);
        bufp->chgSData(oldp+23,(vlSelfRef.bitty_core__DOT__alu_inst__DOT__arithmetic_out),16);
        bufp->chgSData(oldp+24,(vlSelfRef.bitty_core__DOT__alu_inst__DOT__logic_out),16);
        bufp->chgSData(oldp+25,(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__ab),16);
        bufp->chgSData(oldp+26,(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__anotb),16);
        bufp->chgSData(oldp+27,(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__aorb),16);
        bufp->chgSData(oldp+28,(vlSelfRef.bitty_core__DOT__alu_inst__DOT__AU__DOT__aornotb),16);
        bufp->chgCData(oldp+29,((7U & ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                       >> 0xdU))),3);
        bufp->chgCData(oldp+30,((7U & ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                       >> 0xaU))),3);
        bufp->chgCData(oldp+31,((7U & ((IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage) 
                                       >> 7U))),3);
        bufp->chgCData(oldp+32,((3U & (IData)(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage))),2);
        bufp->chgCData(oldp+33,(vlSelfRef.bitty_core__DOT__control_inst__DOT__state),2);
        bufp->chgCData(oldp+34,(vlSelfRef.bitty_core__DOT__control_inst__DOT__next_state),2);
        bufp->chgSData(oldp+35,(vlSelfRef.bitty_core__DOT__reg0_inst__DOT__storage),16);
        bufp->chgSData(oldp+36,(vlSelfRef.bitty_core__DOT__reg1_inst__DOT__storage),16);
        bufp->chgSData(oldp+37,(vlSelfRef.bitty_core__DOT__reg2_inst__DOT__storage),16);
        bufp->chgSData(oldp+38,(vlSelfRef.bitty_core__DOT__reg3_inst__DOT__storage),16);
        bufp->chgSData(oldp+39,(vlSelfRef.bitty_core__DOT__reg4_inst__DOT__storage),16);
        bufp->chgSData(oldp+40,(vlSelfRef.bitty_core__DOT__reg5_inst__DOT__storage),16);
        bufp->chgSData(oldp+41,(vlSelfRef.bitty_core__DOT__reg6_inst__DOT__storage),16);
        bufp->chgSData(oldp+42,(vlSelfRef.bitty_core__DOT__reg7_inst__DOT__storage),16);
        bufp->chgSData(oldp+43,(vlSelfRef.bitty_core__DOT__reg_c_inst__DOT__storage),16);
        bufp->chgSData(oldp+44,(vlSelfRef.bitty_core__DOT__reg_instr_inst__DOT__storage),16);
        bufp->chgSData(oldp+45,(vlSelfRef.bitty_core__DOT__reg_s_inst__DOT__storage),16);
    }
    bufp->chgBit(oldp+46,(vlSelfRef.clk));
    bufp->chgBit(oldp+47,(vlSelfRef.reset));
    bufp->chgSData(oldp+48,(vlSelfRef.instruction),16);
    bufp->chgBit(oldp+49,(vlSelfRef.run));
    bufp->chgBit(oldp+50,(vlSelfRef.done));
    bufp->chgSData(oldp+51,(vlSelfRef.reg_instr_out),16);
    bufp->chgSData(oldp+52,(vlSelfRef.reg_s_out),16);
    bufp->chgSData(oldp+53,(vlSelfRef.reg_c_out),16);
    bufp->chgSData(oldp+54,(vlSelfRef.reg0_out),16);
    bufp->chgSData(oldp+55,(vlSelfRef.reg1_out),16);
    bufp->chgSData(oldp+56,(vlSelfRef.reg2_out),16);
    bufp->chgSData(oldp+57,(vlSelfRef.reg3_out),16);
    bufp->chgSData(oldp+58,(vlSelfRef.reg4_out),16);
    bufp->chgSData(oldp+59,(vlSelfRef.reg5_out),16);
    bufp->chgSData(oldp+60,(vlSelfRef.reg6_out),16);
    bufp->chgSData(oldp+61,(vlSelfRef.reg7_out),16);
    bufp->chgSData(oldp+62,(vlSelfRef.mux_out),16);
    bufp->chgSData(oldp+63,(vlSelfRef.alu_out),16);
    bufp->chgBit(oldp+64,(((IData)(vlSelfRef.bitty_core__DOT__reg_s_inst__DOT__storage) 
                           == (IData)(vlSelfRef.mux_out))));
}

void Vbitty_core___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vbitty_core___024root__trace_cleanup\n"); );
    // Init
    Vbitty_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vbitty_core___024root*>(voidSelf);
    Vbitty_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
