// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


//======================

void Vtop::trace (VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addCallback (&Vtop::traceInit, &Vtop::traceFull, &Vtop::traceChg, this);
}
void Vtop::traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->open()
    Vtop* t=(Vtop*)userthis;
    Vtop__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (!Verilated::calcUnusedSigs()) VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    vcdp->scopeEscape(' ');
    t->traceInitThis (vlSymsp, vcdp, code);
    vcdp->scopeEscape('.');
}
void Vtop::traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vtop* t=(Vtop*)userthis;
    Vtop__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    t->traceFullThis (vlSymsp, vcdp, code);
}

//======================


void Vtop::traceInitThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    vcdp->module(vlSymsp->name());  // Setup signal names
    // Body
    {
	vlTOPp->traceInitThis__1(vlSymsp, vcdp, code);
    }
}

void Vtop::traceFullThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vlTOPp->traceFullThis__1(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vtop::traceInitThis__1(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->declBit  (c+51,"clk",-1);
	vcdp->declBit  (c+52,"rst",-1);
	vcdp->declBit  (c+53,"cs1",-1);
	vcdp->declBit  (c+54,"cs2",-1);
	vcdp->declBit  (c+55,"sck",-1);
	vcdp->declBit  (c+56,"mosi",-1);
	vcdp->declBit  (c+57,"miso",-1);
	vcdp->declBit  (c+51,"top clk",-1);
	vcdp->declBit  (c+52,"top rst",-1);
	vcdp->declBit  (c+53,"top cs1",-1);
	vcdp->declBit  (c+54,"top cs2",-1);
	vcdp->declBit  (c+55,"top sck",-1);
	vcdp->declBit  (c+56,"top mosi",-1);
	vcdp->declBit  (c+57,"top miso",-1);
	vcdp->declBit  (c+51,"top sensor0 clk",-1);
	vcdp->declBit  (c+52,"top sensor0 rst",-1);
	vcdp->declBit  (c+53,"top sensor0 cs",-1);
	vcdp->declBit  (c+55,"top sensor0 sck",-1);
	vcdp->declBit  (c+56,"top sensor0 mosi",-1);
	vcdp->declBit  (c+57,"top sensor0 miso",-1);
	vcdp->declBit  (c+35,"top sensor0 spi0_rx_dv",-1);
	vcdp->declBus  (c+36,"top sensor0 spi0_rx",-1,7,0);
	vcdp->declBit  (c+3,"top sensor0 spi0_tx_dv",-1);
	vcdp->declBus  (c+29,"top sensor0 spi0_tx",-1,7,0);
	vcdp->declBit  (c+18,"top sensor0 tx_done",-1);
	vcdp->declBus  (c+4,"top sensor0 regaddr",-1,7,0);
	vcdp->declBus  (c+5,"top sensor0 regresp",-1,7,0);
	vcdp->declBus  (c+30,"top sensor0 readcnt",-1,2,0);
	vcdp->declBus  (c+31,"top sensor0 streamlen",-1,7,0);
	vcdp->declBus  (c+6,"top sensor0 dataidx",-1,12,0);
	vcdp->declBit  (c+7,"top sensor0 stream_firstbyte",-1);
	// Tracing: top sensor0 sensordata // Ignored: Wide memory > --trace-max-array ents at vd002.sv:62
	vcdp->declBus  (c+8,"top sensor0 sensor_state",-1,1,0);
	vcdp->declBus  (c+58,"top sensor0 spi0 SPI_MODE",-1,31,0);
	vcdp->declBit  (c+1,"top sensor0 spi0 i_Rst_L",-1);
	vcdp->declBit  (c+51,"top sensor0 spi0 i_Clk",-1);
	vcdp->declBit  (c+35,"top sensor0 spi0 o_RX_DV",-1);
	vcdp->declBus  (c+36,"top sensor0 spi0 o_RX_Byte",-1,7,0);
	vcdp->declBit  (c+3,"top sensor0 spi0 i_TX_DV",-1);
	vcdp->declBus  (c+29,"top sensor0 spi0 i_TX_Byte",-1,7,0);
	vcdp->declBit  (c+55,"top sensor0 spi0 i_SPI_Clk",-1);
	vcdp->declBit  (c+57,"top sensor0 spi0 o_SPI_MISO",-1);
	vcdp->declBit  (c+56,"top sensor0 spi0 i_SPI_MOSI",-1);
	vcdp->declBit  (c+53,"top sensor0 spi0 i_SPI_CS_n",-1);
	vcdp->declBit  (c+59,"top sensor0 spi0 w_CPOL",-1);
	vcdp->declBit  (c+59,"top sensor0 spi0 w_CPHA",-1);
	vcdp->declBit  (c+2,"top sensor0 spi0 w_SPI_Clk",-1);
	vcdp->declBit  (c+26,"top sensor0 spi0 w_SPI_MISO_Mux",-1);
	vcdp->declBus  (c+47,"top sensor0 spi0 r_RX_Bit_Count",-1,2,0);
	vcdp->declBus  (c+23,"top sensor0 spi0 r_TX_Bit_Count",-1,2,0);
	vcdp->declBus  (c+48,"top sensor0 spi0 r_Temp_RX_Byte",-1,7,0);
	vcdp->declBus  (c+49,"top sensor0 spi0 r_RX_Byte",-1,7,0);
	vcdp->declBit  (c+50,"top sensor0 spi0 r_RX_Done",-1);
	vcdp->declBit  (c+37,"top sensor0 spi0 r2_RX_Done",-1);
	vcdp->declBit  (c+38,"top sensor0 spi0 r3_RX_Done",-1);
	vcdp->declBus  (c+27,"top sensor0 spi0 r_TX_Byte",-1,7,0);
	vcdp->declBit  (c+24,"top sensor0 spi0 r_SPI_MISO_Bit",-1);
	vcdp->declBit  (c+25,"top sensor0 spi0 r_Preload_MISO",-1);
	vcdp->declBit  (c+51,"top flash0 clk",-1);
	vcdp->declBit  (c+52,"top flash0 rst",-1);
	vcdp->declBit  (c+54,"top flash0 cs",-1);
	vcdp->declBit  (c+55,"top flash0 sck",-1);
	vcdp->declBit  (c+56,"top flash0 mosi",-1);
	vcdp->declBit  (c+57,"top flash0 miso",-1);
	vcdp->declBit  (c+39,"top flash0 spi0_rx_dv",-1);
	vcdp->declBus  (c+40,"top flash0 spi0_rx",-1,7,0);
	vcdp->declBit  (c+9,"top flash0 spi0_tx_dv",-1);
	vcdp->declBus  (c+32,"top flash0 spi0_tx",-1,7,0);
	vcdp->declBus  (c+10,"top flash0 page",-1,7,0);
	vcdp->declBus  (c+11,"top flash0 offset",-1,7,0);
	// Tracing: top flash0 data // Ignored: Wide memory > --trace-max-array ents at vd003.sv:33
	vcdp->declBus  (c+12,"top flash0 dataaddr",-1,15,0);
	vcdp->declBus  (c+13,"top flash0 regaddr",-1,7,0);
	vcdp->declBus  (c+14,"top flash0 effaddr",-1,7,0);
	vcdp->declBit  (c+15,"top flash0 wren",-1);
	vcdp->declBus  (c+16,"top flash0 regresp",-1,7,0);
	vcdp->declBit  (c+33,"top flash0 data_wren",-1);
	vcdp->declBus  (c+34,"top flash0 data_value",-1,7,0);
	vcdp->declBus  (c+17,"top flash0 flash_state",-1,2,0);
	vcdp->declBus  (c+58,"top flash0 spi0 SPI_MODE",-1,31,0);
	vcdp->declBit  (c+1,"top flash0 spi0 i_Rst_L",-1);
	vcdp->declBit  (c+51,"top flash0 spi0 i_Clk",-1);
	vcdp->declBit  (c+39,"top flash0 spi0 o_RX_DV",-1);
	vcdp->declBus  (c+40,"top flash0 spi0 o_RX_Byte",-1,7,0);
	vcdp->declBit  (c+9,"top flash0 spi0 i_TX_DV",-1);
	vcdp->declBus  (c+32,"top flash0 spi0 i_TX_Byte",-1,7,0);
	vcdp->declBit  (c+55,"top flash0 spi0 i_SPI_Clk",-1);
	vcdp->declBit  (c+57,"top flash0 spi0 o_SPI_MISO",-1);
	vcdp->declBit  (c+56,"top flash0 spi0 i_SPI_MOSI",-1);
	vcdp->declBit  (c+54,"top flash0 spi0 i_SPI_CS_n",-1);
	vcdp->declBit  (c+59,"top flash0 spi0 w_CPOL",-1);
	vcdp->declBit  (c+59,"top flash0 spi0 w_CPHA",-1);
	vcdp->declBit  (c+2,"top flash0 spi0 w_SPI_Clk",-1);
	vcdp->declBit  (c+22,"top flash0 spi0 w_SPI_MISO_Mux",-1);
	vcdp->declBus  (c+43,"top flash0 spi0 r_RX_Bit_Count",-1,2,0);
	vcdp->declBus  (c+19,"top flash0 spi0 r_TX_Bit_Count",-1,2,0);
	vcdp->declBus  (c+44,"top flash0 spi0 r_Temp_RX_Byte",-1,7,0);
	vcdp->declBus  (c+45,"top flash0 spi0 r_RX_Byte",-1,7,0);
	vcdp->declBit  (c+46,"top flash0 spi0 r_RX_Done",-1);
	vcdp->declBit  (c+41,"top flash0 spi0 r2_RX_Done",-1);
	vcdp->declBit  (c+42,"top flash0 spi0 r3_RX_Done",-1);
	vcdp->declBus  (c+28,"top flash0 spi0 r_TX_Byte",-1,7,0);
	vcdp->declBit  (c+20,"top flash0 spi0 r_SPI_MISO_Bit",-1);
	vcdp->declBit  (c+21,"top flash0 spi0 r_Preload_MISO",-1);
    }
}

void Vtop::traceFullThis__1(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->fullBit  (c+1,(vlTOPp->top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L));
	vcdp->fullBit  (c+2,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk));
	vcdp->fullBit  (c+3,(vlTOPp->top__DOT__sensor0__DOT__spi0_tx_dv));
	vcdp->fullBus  (c+4,(vlTOPp->top__DOT__sensor0__DOT__regaddr),8);
	vcdp->fullBus  (c+5,(vlTOPp->top__DOT__sensor0__DOT__regresp),8);
	vcdp->fullBus  (c+6,(vlTOPp->top__DOT__sensor0__DOT__dataidx),13);
	vcdp->fullBit  (c+7,(vlTOPp->top__DOT__sensor0__DOT__stream_firstbyte));
	vcdp->fullBus  (c+8,(vlTOPp->top__DOT__sensor0__DOT__sensor_state),2);
	vcdp->fullBit  (c+9,(vlTOPp->top__DOT__flash0__DOT__spi0_tx_dv));
	vcdp->fullBus  (c+10,(vlTOPp->top__DOT__flash0__DOT__page),8);
	vcdp->fullBus  (c+11,(vlTOPp->top__DOT__flash0__DOT__offset),8);
	vcdp->fullBus  (c+12,(vlTOPp->top__DOT__flash0__DOT__dataaddr),16);
	vcdp->fullBus  (c+13,(vlTOPp->top__DOT__flash0__DOT__regaddr),8);
	vcdp->fullBus  (c+14,((0x7fU & (IData)(vlTOPp->top__DOT__flash0__DOT__regaddr))),8);
	vcdp->fullBit  (c+15,((1U & ((IData)(vlTOPp->top__DOT__flash0__DOT__regaddr) 
				     >> 7U))));
	vcdp->fullBus  (c+16,(vlTOPp->top__DOT__flash0__DOT__regresp),8);
	vcdp->fullBus  (c+17,(vlTOPp->top__DOT__flash0__DOT__flash_state),3);
	vcdp->fullBit  (c+18,(vlTOPp->top__DOT__sensor0__DOT__tx_done));
	vcdp->fullBus  (c+19,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count),3);
	vcdp->fullBit  (c+20,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_SPI_MISO_Bit));
	vcdp->fullBit  (c+21,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Preload_MISO));
	vcdp->fullBit  (c+22,((1U & ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Preload_MISO)
				      ? ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte) 
					 >> 7U) : (IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_SPI_MISO_Bit)))));
	vcdp->fullBus  (c+23,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count),3);
	vcdp->fullBit  (c+24,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_SPI_MISO_Bit));
	vcdp->fullBit  (c+25,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Preload_MISO));
	vcdp->fullBit  (c+26,((1U & ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Preload_MISO)
				      ? ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte) 
					 >> 7U) : (IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_SPI_MISO_Bit)))));
	vcdp->fullBus  (c+27,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte),8);
	vcdp->fullBus  (c+28,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte),8);
	vcdp->fullBus  (c+29,(vlTOPp->top__DOT__sensor0__DOT__spi0_tx),8);
	vcdp->fullBus  (c+30,(vlTOPp->top__DOT__sensor0__DOT__readcnt),3);
	vcdp->fullBus  (c+31,(vlTOPp->top__DOT__sensor0__DOT__streamlen),8);
	vcdp->fullBus  (c+32,(vlTOPp->top__DOT__flash0__DOT__spi0_tx),8);
	vcdp->fullBit  (c+33,(vlTOPp->top__DOT__flash0__DOT__data_wren));
	vcdp->fullBus  (c+34,(vlTOPp->top__DOT__flash0__DOT__data_value),8);
	vcdp->fullBit  (c+35,(vlTOPp->top__DOT__sensor0__DOT__spi0_rx_dv));
	vcdp->fullBus  (c+36,(vlTOPp->top__DOT__sensor0__DOT__spi0_rx),8);
	vcdp->fullBit  (c+37,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done));
	vcdp->fullBit  (c+38,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done));
	vcdp->fullBit  (c+39,(vlTOPp->top__DOT__flash0__DOT__spi0_rx_dv));
	vcdp->fullBus  (c+40,(vlTOPp->top__DOT__flash0__DOT__spi0_rx),8);
	vcdp->fullBit  (c+41,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done));
	vcdp->fullBit  (c+42,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done));
	vcdp->fullBus  (c+43,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count),3);
	vcdp->fullBus  (c+44,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte),8);
	vcdp->fullBus  (c+45,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Byte),8);
	vcdp->fullBit  (c+46,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Done));
	vcdp->fullBus  (c+47,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count),3);
	vcdp->fullBus  (c+48,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte),8);
	vcdp->fullBus  (c+49,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Byte),8);
	vcdp->fullBit  (c+50,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Done));
	vcdp->fullBit  (c+51,(vlTOPp->clk));
	vcdp->fullBit  (c+52,(vlTOPp->rst));
	vcdp->fullBit  (c+53,(vlTOPp->cs1));
	vcdp->fullBit  (c+54,(vlTOPp->cs2));
	vcdp->fullBit  (c+55,(vlTOPp->sck));
	vcdp->fullBit  (c+56,(vlTOPp->mosi));
	vcdp->fullBit  (c+57,(vlTOPp->miso));
	vcdp->fullBus  (c+58,(3U),32);
	vcdp->fullBit  (c+59,(1U));
    }
}
