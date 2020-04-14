// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vtop_H_
#define _Vtop_H_

#include "verilated.h"

class Vtop__Syms;
class VerilatedVcd;

//----------

VL_MODULE(Vtop) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(cs1,0,0);
    VL_IN8(cs2,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(sck,0,0);
    VL_IN8(mosi,0,0);
    VL_OUT8(miso,0,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk,0,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0_rx_dv,0,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0_rx,7,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0_tx_dv,0,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0_tx,7,0);
    VL_SIG8(top__DOT__sensor0__DOT__tx_done,0,0);
    VL_SIG8(top__DOT__sensor0__DOT__regaddr,7,0);
    VL_SIG8(top__DOT__sensor0__DOT__regresp,7,0);
    VL_SIG8(top__DOT__sensor0__DOT__readcnt,2,0);
    VL_SIG8(top__DOT__sensor0__DOT__streamlen,7,0);
    VL_SIG8(top__DOT__sensor0__DOT__stream_firstbyte,0,0);
    VL_SIG8(top__DOT__sensor0__DOT__sensor_state,1,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count,2,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count,2,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte,7,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0__DOT__r_RX_Byte,7,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0__DOT__r_RX_Done,0,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done,0,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done,0,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte,7,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0__DOT__r_SPI_MISO_Bit,0,0);
    VL_SIG8(top__DOT__sensor0__DOT__spi0__DOT__r_Preload_MISO,0,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0_rx_dv,0,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0_rx,7,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0_tx_dv,0,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0_tx,7,0);
    VL_SIG8(top__DOT__flash0__DOT__page,7,0);
    VL_SIG8(top__DOT__flash0__DOT__offset,7,0);
    VL_SIG8(top__DOT__flash0__DOT__regaddr,7,0);
    VL_SIG8(top__DOT__flash0__DOT__effaddr,7,0);
    VL_SIG8(top__DOT__flash0__DOT__wren,0,0);
    VL_SIG8(top__DOT__flash0__DOT__regresp,7,0);
    VL_SIG8(top__DOT__flash0__DOT__data_wren,0,0);
    VL_SIG8(top__DOT__flash0__DOT__data_value,7,0);
    VL_SIG8(top__DOT__flash0__DOT__flash_state,2,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count,2,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count,2,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte,7,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0__DOT__r_RX_Byte,7,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0__DOT__r_RX_Done,0,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done,0,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done,0,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte,7,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0__DOT__r_SPI_MISO_Bit,0,0);
    VL_SIG8(top__DOT__flash0__DOT__spi0__DOT__r_Preload_MISO,0,0);
    VL_SIG16(top__DOT__sensor0__DOT__dataidx,12,0);
    VL_SIG16(top__DOT__flash0__DOT__dataaddr,15,0);
    VL_SIG8(top__DOT__sensor0__DOT__sensordata[8192],7,0);
    VL_SIG8(top__DOT__flash0__DOT__data[8192],7,0);
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L,0,0);
    VL_SIG8(miso__out1,0,0);
    VL_SIG8(__Vdly__top__DOT__sensor0__DOT__tx_done,0,0);
    VL_SIG8(__Vdly__top__DOT__sensor0__DOT__regaddr,7,0);
    VL_SIG8(__Vdly__top__DOT__sensor0__DOT__regresp,7,0);
    VL_SIG8(__Vdly__top__DOT__sensor0__DOT__readcnt,2,0);
    VL_SIG8(__Vdly__top__DOT__sensor0__DOT__sensor_state,1,0);
    VL_SIG8(__Vdly__top__DOT__sensor0__DOT__streamlen,7,0);
    VL_SIG8(__Vdly__top__DOT__sensor0__DOT__stream_firstbyte,0,0);
    VL_SIG8(__Vdly__top__DOT__flash0__DOT__regaddr,7,0);
    VL_SIG8(__Vdly__top__DOT__flash0__DOT__regresp,7,0);
    VL_SIG8(__Vdly__top__DOT__flash0__DOT__flash_state,2,0);
    VL_SIG8(__Vdly__top__DOT__flash0__DOT__page,7,0);
    VL_SIG8(__Vdly__top__DOT__flash0__DOT__offset,7,0);
    VL_SIG8(__Vdlyvset__top__DOT__flash0__DOT__data__v0,0,0);
    VL_SIG8(__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count,2,0);
    VL_SIG8(__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte,7,0);
    VL_SIG8(__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done,0,0);
    VL_SIG8(__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done,0,0);
    VL_SIG8(__Vdly__top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count,2,0);
    VL_SIG8(__Vdly__top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte,7,0);
    VL_SIG8(__Vdly__top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done,0,0);
    VL_SIG8(__Vdly__top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done,0,0);
    VL_SIG8(__VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L,0,0);
    VL_SIG8(__Vclklast__TOP__clk,0,0);
    VL_SIG8(__Vclklast__TOP____VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L,0,0);
    VL_SIG8(__Vclklast__TOP__cs2,0,0);
    VL_SIG8(__Vclklast__TOP__top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk,0,0);
    VL_SIG8(__Vclklast__TOP__cs1,0,0);
    VL_SIG8(__Vchglast__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L,0,0);
    VL_SIG16(__Vdly__top__DOT__sensor0__DOT__dataidx,12,0);
    VL_SIG(__Vm_traceActivity,31,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vtop__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    Vtop& operator= (const Vtop&);  ///< Copying not allowed
    Vtop(const Vtop&);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible WRT DPI scope names.
    Vtop(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vtop();
    /// Trace signals in the model; called by application code
    void trace (VerilatedVcdC* tfp, int levels, int options=0);
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vtop__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vtop__Syms* symsp, bool first);
  private:
    static QData _change_request(Vtop__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__14(Vtop__Syms* __restrict vlSymsp);
    static void _combo__TOP__18(Vtop__Syms* __restrict vlSymsp);
    static void _combo__TOP__5(Vtop__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(Vtop__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vtop__Syms* __restrict vlSymsp);
    static void _eval_settle(Vtop__Syms* __restrict vlSymsp);
    static void _initial__TOP__7(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__1(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__10(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__12(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__13(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__15(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__16(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__17(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__19(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__3(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__4(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__8(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__9(Vtop__Syms* __restrict vlSymsp);
    static void _settle__TOP__11(Vtop__Syms* __restrict vlSymsp);
    static void _settle__TOP__6(Vtop__Syms* __restrict vlSymsp);
    static void traceChgThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__10(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__11(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__12(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__13(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__14(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__2(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__3(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__4(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__5(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__6(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__7(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__8(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__9(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceFullThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceFullThis__1(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceInitThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceInitThis__1(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceInit (VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceFull (VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceChg  (VerilatedVcd* vcdp, void* userthis, uint32_t code);
} VL_ATTR_ALIGNED(128);

#endif // guard
