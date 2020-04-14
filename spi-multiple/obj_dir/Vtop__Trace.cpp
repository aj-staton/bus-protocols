// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


//======================

void Vtop::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vtop* t=(Vtop*)userthis;
    Vtop__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
	t->traceChgThis (vlSymsp, vcdp, code);
    }
}

//======================


void Vtop::traceChgThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
			       | (vlTOPp->__Vm_traceActivity 
				  >> 1U))))) {
	    vlTOPp->traceChgThis__2(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
			       | (vlTOPp->__Vm_traceActivity 
				  >> 5U))))) {
	    vlTOPp->traceChgThis__3(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
			       | (vlTOPp->__Vm_traceActivity 
				  >> 7U))))) {
	    vlTOPp->traceChgThis__4(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((4U & vlTOPp->__Vm_traceActivity))) {
	    vlTOPp->traceChgThis__5(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((1U & ((vlTOPp->__Vm_traceActivity 
				>> 2U) | (vlTOPp->__Vm_traceActivity 
					  >> 4U))))) {
	    vlTOPp->traceChgThis__6(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((8U & vlTOPp->__Vm_traceActivity))) {
	    vlTOPp->traceChgThis__7(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((1U & ((vlTOPp->__Vm_traceActivity 
				>> 3U) | (vlTOPp->__Vm_traceActivity 
					  >> 4U))))) {
	    vlTOPp->traceChgThis__8(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((0x10U & vlTOPp->__Vm_traceActivity))) {
	    vlTOPp->traceChgThis__9(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((0x20U & vlTOPp->__Vm_traceActivity))) {
	    vlTOPp->traceChgThis__10(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((0x40U & vlTOPp->__Vm_traceActivity))) {
	    vlTOPp->traceChgThis__11(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((0x100U & vlTOPp->__Vm_traceActivity))) {
	    vlTOPp->traceChgThis__12(vlSymsp, vcdp, code);
	}
	if (VL_UNLIKELY((0x200U & vlTOPp->__Vm_traceActivity))) {
	    vlTOPp->traceChgThis__13(vlSymsp, vcdp, code);
	}
	vlTOPp->traceChgThis__14(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vtop::traceChgThis__2(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBit  (c+1,(vlTOPp->top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L));
	vcdp->chgBit  (c+2,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk));
    }
}

void Vtop::traceChgThis__3(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBit  (c+3,(vlTOPp->top__DOT__sensor0__DOT__spi0_tx_dv));
	vcdp->chgBus  (c+4,(vlTOPp->top__DOT__sensor0__DOT__regaddr),8);
	vcdp->chgBus  (c+5,(vlTOPp->top__DOT__sensor0__DOT__regresp),8);
	vcdp->chgBus  (c+6,(vlTOPp->top__DOT__sensor0__DOT__dataidx),13);
	vcdp->chgBit  (c+7,(vlTOPp->top__DOT__sensor0__DOT__stream_firstbyte));
	vcdp->chgBus  (c+8,(vlTOPp->top__DOT__sensor0__DOT__sensor_state),2);
	vcdp->chgBit  (c+9,(vlTOPp->top__DOT__flash0__DOT__spi0_tx_dv));
	vcdp->chgBus  (c+10,(vlTOPp->top__DOT__flash0__DOT__page),8);
	vcdp->chgBus  (c+11,(vlTOPp->top__DOT__flash0__DOT__offset),8);
	vcdp->chgBus  (c+12,(vlTOPp->top__DOT__flash0__DOT__dataaddr),16);
	vcdp->chgBus  (c+13,(vlTOPp->top__DOT__flash0__DOT__regaddr),8);
	vcdp->chgBus  (c+14,((0x7fU & (IData)(vlTOPp->top__DOT__flash0__DOT__regaddr))),8);
	vcdp->chgBit  (c+15,((1U & ((IData)(vlTOPp->top__DOT__flash0__DOT__regaddr) 
				    >> 7U))));
	vcdp->chgBus  (c+16,(vlTOPp->top__DOT__flash0__DOT__regresp),8);
	vcdp->chgBus  (c+17,(vlTOPp->top__DOT__flash0__DOT__flash_state),3);
    }
}

void Vtop::traceChgThis__4(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBit  (c+18,(vlTOPp->top__DOT__sensor0__DOT__tx_done));
    }
}

void Vtop::traceChgThis__5(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBus  (c+19,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count),3);
	vcdp->chgBit  (c+20,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_SPI_MISO_Bit));
	vcdp->chgBit  (c+21,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Preload_MISO));
    }
}

void Vtop::traceChgThis__6(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBit  (c+22,((1U & ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Preload_MISO)
				     ? ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte) 
					>> 7U) : (IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_SPI_MISO_Bit)))));
    }
}

void Vtop::traceChgThis__7(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBus  (c+23,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count),3);
	vcdp->chgBit  (c+24,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_SPI_MISO_Bit));
	vcdp->chgBit  (c+25,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Preload_MISO));
    }
}

void Vtop::traceChgThis__8(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBit  (c+26,((1U & ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Preload_MISO)
				     ? ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte) 
					>> 7U) : (IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_SPI_MISO_Bit)))));
    }
}

void Vtop::traceChgThis__9(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBus  (c+27,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte),8);
	vcdp->chgBus  (c+28,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte),8);
    }
}

void Vtop::traceChgThis__10(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBus  (c+29,(vlTOPp->top__DOT__sensor0__DOT__spi0_tx),8);
	vcdp->chgBus  (c+30,(vlTOPp->top__DOT__sensor0__DOT__readcnt),3);
	vcdp->chgBus  (c+31,(vlTOPp->top__DOT__sensor0__DOT__streamlen),8);
	vcdp->chgBus  (c+32,(vlTOPp->top__DOT__flash0__DOT__spi0_tx),8);
	vcdp->chgBit  (c+33,(vlTOPp->top__DOT__flash0__DOT__data_wren));
	vcdp->chgBus  (c+34,(vlTOPp->top__DOT__flash0__DOT__data_value),8);
    }
}

void Vtop::traceChgThis__11(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBit  (c+35,(vlTOPp->top__DOT__sensor0__DOT__spi0_rx_dv));
	vcdp->chgBus  (c+36,(vlTOPp->top__DOT__sensor0__DOT__spi0_rx),8);
	vcdp->chgBit  (c+37,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done));
	vcdp->chgBit  (c+38,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done));
	vcdp->chgBit  (c+39,(vlTOPp->top__DOT__flash0__DOT__spi0_rx_dv));
	vcdp->chgBus  (c+40,(vlTOPp->top__DOT__flash0__DOT__spi0_rx),8);
	vcdp->chgBit  (c+41,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done));
	vcdp->chgBit  (c+42,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done));
    }
}

void Vtop::traceChgThis__12(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBus  (c+43,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count),3);
	vcdp->chgBus  (c+44,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte),8);
	vcdp->chgBus  (c+45,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Byte),8);
	vcdp->chgBit  (c+46,(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Done));
    }
}

void Vtop::traceChgThis__13(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBus  (c+47,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count),3);
	vcdp->chgBus  (c+48,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte),8);
	vcdp->chgBus  (c+49,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Byte),8);
	vcdp->chgBit  (c+50,(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Done));
    }
}

void Vtop::traceChgThis__14(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBit  (c+51,(vlTOPp->clk));
	vcdp->chgBit  (c+52,(vlTOPp->rst));
	vcdp->chgBit  (c+53,(vlTOPp->cs1));
	vcdp->chgBit  (c+54,(vlTOPp->cs2));
	vcdp->chgBit  (c+55,(vlTOPp->sck));
	vcdp->chgBit  (c+56,(vlTOPp->mosi));
	vcdp->chgBit  (c+57,(vlTOPp->miso));
    }
}
