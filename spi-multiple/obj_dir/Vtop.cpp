// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop.h"              // For This
#include "Vtop__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vtop) {
    Vtop__Syms* __restrict vlSymsp = __VlSymsp = new Vtop__Syms(this, name());
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vtop::__Vconfigure(Vtop__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vtop::~Vtop() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vtop::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtop::eval\n"); );
    Vtop__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    while (VL_LIKELY(__Vchange)) {
	VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
	vlSymsp->__Vm_activity = true;
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (VL_UNLIKELY(++__VclockLoop > 100)) VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Verilated model didn't converge");
    }
}

void Vtop::_eval_initial_loop(Vtop__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    int __VclockLoop = 0;
    QData __Vchange = 1;
    while (VL_LIKELY(__Vchange)) {
	_eval_settle(vlSymsp);
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (VL_UNLIKELY(++__VclockLoop > 100)) VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Verilated model didn't DC converge");
    }
}

//--------------------
// Internal Methods

VL_INLINE_OPT void Vtop::_sequent__TOP__1(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__1\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done 
	= vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done;
    vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done 
	= vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done;
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done 
	= vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done;
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done 
	= vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done;
}

VL_INLINE_OPT void Vtop::_sequent__TOP__3(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__3\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__readcnt 
	= vlTOPp->top__DOT__sensor0__DOT__readcnt;
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__streamlen 
	= vlTOPp->top__DOT__sensor0__DOT__streamlen;
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__regaddr 
	= vlTOPp->top__DOT__sensor0__DOT__regaddr;
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__regresp 
	= vlTOPp->top__DOT__sensor0__DOT__regresp;
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__dataidx 
	= vlTOPp->top__DOT__sensor0__DOT__dataidx;
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__sensor_state 
	= vlTOPp->top__DOT__sensor0__DOT__sensor_state;
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__stream_firstbyte 
	= vlTOPp->top__DOT__sensor0__DOT__stream_firstbyte;
    vlTOPp->__Vdly__top__DOT__flash0__DOT__regresp 
	= vlTOPp->top__DOT__flash0__DOT__regresp;
    vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state 
	= vlTOPp->top__DOT__flash0__DOT__flash_state;
    vlTOPp->__Vdlyvset__top__DOT__flash0__DOT__data__v0 = 0U;
    vlTOPp->__Vdly__top__DOT__flash0__DOT__page = vlTOPp->top__DOT__flash0__DOT__page;
    vlTOPp->__Vdly__top__DOT__flash0__DOT__offset = vlTOPp->top__DOT__flash0__DOT__offset;
    vlTOPp->__Vdly__top__DOT__flash0__DOT__regaddr 
	= vlTOPp->top__DOT__flash0__DOT__regaddr;
}

VL_INLINE_OPT void Vtop::_sequent__TOP__4(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__4\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__tx_done 
	= vlTOPp->top__DOT__sensor0__DOT__tx_done;
}

VL_INLINE_OPT void Vtop::_combo__TOP__5(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_combo__TOP__5\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk 
	= (1U & (~ (IData)(vlTOPp->sck)));
}

void Vtop::_settle__TOP__6(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_settle__TOP__6\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk 
	= (1U & (~ (IData)(vlTOPp->sck)));
    vlTOPp->miso__out1 = (1U & ((((((~ (IData)(vlTOPp->cs1)) 
				    & ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Preload_MISO)
				        ? ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte) 
					   >> 7U) : (IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_SPI_MISO_Bit))) 
				   & (~ (IData)(vlTOPp->cs1))) 
				  & (~ (IData)(vlTOPp->cs1))) 
				 & (~ (IData)(vlTOPp->cs1))) 
				| (((((~ (IData)(vlTOPp->cs2)) 
				      & ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Preload_MISO)
					  ? ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte) 
					     >> 7U)
					  : (IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_SPI_MISO_Bit))) 
				     & (~ (IData)(vlTOPp->cs2))) 
				    & (~ (IData)(vlTOPp->cs2))) 
				   & (~ (IData)(vlTOPp->cs2)))));
    vlTOPp->top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L 
	= (1U & (~ (IData)(vlTOPp->rst)));
    vlTOPp->miso = ((IData)(vlTOPp->miso__out1) & (
						   (~ (IData)(vlTOPp->cs1)) 
						   | (~ (IData)(vlTOPp->cs2))));
}

void Vtop::_initial__TOP__7(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_initial__TOP__7\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIGW(__Vtemp1,127,0,4);
    // Body
    // INITIAL at vd002.sv:63
    __Vtemp1[0U] = 0x2e686578U;
    __Vtemp1[1U] = 0x64617461U;
    __Vtemp1[2U] = 0x6e736f72U;
    __Vtemp1[3U] = 0x7365U;
    VL_READMEM_W (true,8,8192, 0,4, __Vtemp1, vlTOPp->top__DOT__sensor0__DOT__sensordata
		  ,0,~0);
    vlTOPp->top__DOT__sensor0__DOT__dataidx = 0U;
    // INITIAL at vd002.sv:77
    vlTOPp->top__DOT__sensor0__DOT__sensor_state = 0U;
    vlTOPp->top__DOT__sensor0__DOT__spi0_tx_dv = 0U;
    vlTOPp->top__DOT__sensor0__DOT__regaddr = 0U;
    vlTOPp->top__DOT__sensor0__DOT__regresp = 0U;
    vlTOPp->top__DOT__sensor0__DOT__tx_done = 0U;
    vlTOPp->top__DOT__sensor0__DOT__stream_firstbyte = 0U;
    // INITIAL at vd003.sv:76
    vlTOPp->top__DOT__flash0__DOT__flash_state = 0U;
    vlTOPp->top__DOT__flash0__DOT__spi0_tx_dv = 0U;
    vlTOPp->top__DOT__flash0__DOT__regaddr = 0U;
    vlTOPp->top__DOT__flash0__DOT__regresp = 0U;
    vlTOPp->top__DOT__flash0__DOT__page = 0U;
    vlTOPp->top__DOT__flash0__DOT__offset = 0U;
}

VL_INLINE_OPT void Vtop::_sequent__TOP__8(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__8\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at vd002.sv:86
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__tx_done 
	= vlTOPp->top__DOT__sensor0__DOT__spi0_rx_dv;
}

VL_INLINE_OPT void Vtop::_sequent__TOP__9(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__9\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count,2,0);
    // Body
    vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count 
	= vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count;
    vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte 
	= vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte;
    __Vdly__top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count 
	= vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count;
    // ALWAYS at SPI_Slave.v:152
    vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Preload_MISO 
	= vlTOPp->cs2;
    // ALWAYS at SPI_Slave.v:168
    if (vlTOPp->cs2) {
	__Vdly__top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count = 7U;
	vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_SPI_MISO_Bit 
	    = (1U & ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte) 
		     >> 7U));
    } else {
	__Vdly__top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count 
	    = (7U & ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count) 
		     - (IData)(1U)));
	vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_SPI_MISO_Bit 
	    = (1U & ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte) 
		     >> (IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count)));
    }
    vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count 
	= __Vdly__top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count;
}

VL_INLINE_OPT void Vtop::_sequent__TOP__10(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__10\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count,2,0);
    // Body
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count 
	= vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count;
    vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte 
	= vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte;
    __Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count 
	= vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count;
    // ALWAYS at SPI_Slave.v:152
    vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Preload_MISO 
	= vlTOPp->cs1;
    // ALWAYS at SPI_Slave.v:168
    if (vlTOPp->cs1) {
	__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count = 7U;
	vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_SPI_MISO_Bit 
	    = (1U & ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte) 
		     >> 7U));
    } else {
	__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count 
	    = (7U & ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count) 
		     - (IData)(1U)));
	vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_SPI_MISO_Bit 
	    = (1U & ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte) 
		     >> (IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count)));
    }
    vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count 
	= __Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count;
}

void Vtop::_settle__TOP__11(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_settle__TOP__11\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top__DOT__flash0__DOT__dataaddr = (((IData)(vlTOPp->top__DOT__flash0__DOT__page) 
						<< 8U) 
					       | (IData)(vlTOPp->top__DOT__flash0__DOT__offset));
    vlTOPp->top__DOT__flash0__DOT__wren = (1U & ((IData)(vlTOPp->top__DOT__flash0__DOT__regaddr) 
						 >> 7U));
    vlTOPp->top__DOT__flash0__DOT__effaddr = (0x7fU 
					      & (IData)(vlTOPp->top__DOT__flash0__DOT__regaddr));
}

VL_INLINE_OPT void Vtop::_sequent__TOP__12(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__12\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at SPI_Slave.v:188
    if (vlTOPp->top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L) {
	if (vlTOPp->top__DOT__flash0__DOT__spi0_tx_dv) {
	    vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte 
		= vlTOPp->top__DOT__flash0__DOT__spi0_tx;
	} else {
	    if (vlTOPp->cs2) {
		vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte = 0U;
	    }
	}
    } else {
	vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte = 0U;
    }
    // ALWAYS at SPI_Slave.v:188
    if (vlTOPp->top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L) {
	if (vlTOPp->top__DOT__sensor0__DOT__spi0_tx_dv) {
	    vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte 
		= vlTOPp->top__DOT__sensor0__DOT__spi0_tx;
	} else {
	    if (vlTOPp->cs1) {
		vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte = 0U;
	    }
	}
    } else {
	vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte = 0U;
    }
}

VL_INLINE_OPT void Vtop::_sequent__TOP__13(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__13\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdlyvval__top__DOT__flash0__DOT__data__v0,7,0);
    VL_SIG16(__Vdlyvdim0__top__DOT__flash0__DOT__data__v0,12,0);
    // Body
    // ALWAYS at vd003.sv:85
    vlTOPp->top__DOT__flash0__DOT__data_wren = 0U;
    if (vlTOPp->rst) {
	vlTOPp->top__DOT__flash0__DOT__spi0_tx_dv = 0U;
	vlTOPp->__Vdly__top__DOT__flash0__DOT__regaddr = 0U;
	vlTOPp->__Vdly__top__DOT__flash0__DOT__regresp = 0U;
    } else {
	if ((0U == (IData)(vlTOPp->top__DOT__flash0__DOT__flash_state))) {
	    vlTOPp->top__DOT__flash0__DOT__spi0_tx_dv = 0U;
	    vlTOPp->__Vdly__top__DOT__flash0__DOT__regaddr = 0U;
	    vlTOPp->__Vdly__top__DOT__flash0__DOT__regresp = 0U;
	    if (vlTOPp->top__DOT__flash0__DOT__spi0_rx_dv) {
		vlTOPp->__Vdly__top__DOT__flash0__DOT__regaddr 
		    = vlTOPp->top__DOT__flash0__DOT__spi0_rx;
		vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 1U;
	    }
	} else {
	    if ((1U == (IData)(vlTOPp->top__DOT__flash0__DOT__flash_state))) {
		if ((0xfU == (IData)(vlTOPp->top__DOT__flash0__DOT__effaddr))) {
		    vlTOPp->__Vdly__top__DOT__flash0__DOT__regresp = 0x36U;
		    vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 2U;
		} else {
		    if ((1U == (IData)(vlTOPp->top__DOT__flash0__DOT__effaddr))) {
			vlTOPp->__Vdly__top__DOT__flash0__DOT__regresp = 0x20U;
			vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 2U;
		    } else {
			if (((0x10U == (IData)(vlTOPp->top__DOT__flash0__DOT__effaddr)) 
			     & (IData)(vlTOPp->top__DOT__flash0__DOT__wren))) {
			    vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 3U;
			} else {
			    if (((0x10U == (IData)(vlTOPp->top__DOT__flash0__DOT__effaddr)) 
				 & (~ (IData)(vlTOPp->top__DOT__flash0__DOT__wren)))) {
				vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 2U;
				vlTOPp->__Vdly__top__DOT__flash0__DOT__regresp 
				    = vlTOPp->top__DOT__flash0__DOT__page;
			    } else {
				if (((0x11U == (IData)(vlTOPp->top__DOT__flash0__DOT__effaddr)) 
				     & (IData)(vlTOPp->top__DOT__flash0__DOT__wren))) {
				    vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 4U;
				} else {
				    if (((0x11U == (IData)(vlTOPp->top__DOT__flash0__DOT__effaddr)) 
					 & (~ (IData)(vlTOPp->top__DOT__flash0__DOT__wren)))) {
					vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 2U;
					vlTOPp->__Vdly__top__DOT__flash0__DOT__regresp 
					    = vlTOPp->top__DOT__flash0__DOT__offset;
				    } else {
					if (((0x12U 
					      == (IData)(vlTOPp->top__DOT__flash0__DOT__effaddr)) 
					     & (IData)(vlTOPp->top__DOT__flash0__DOT__wren))) {
					    vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 5U;
					} else {
					    if (((0x12U 
						  == (IData)(vlTOPp->top__DOT__flash0__DOT__effaddr)) 
						 & (~ (IData)(vlTOPp->top__DOT__flash0__DOT__wren)))) {
						vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 2U;
						vlTOPp->__Vdly__top__DOT__flash0__DOT__regresp 
						    = 
						    vlTOPp->top__DOT__flash0__DOT__data
						    [
						    (0x1fffU 
						     & (IData)(vlTOPp->top__DOT__flash0__DOT__dataaddr))];
					    } else {
						vlTOPp->__Vdly__top__DOT__flash0__DOT__regresp = 0xeeU;
						vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 0U;
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    } else {
		if ((2U == (IData)(vlTOPp->top__DOT__flash0__DOT__flash_state))) {
		    vlTOPp->top__DOT__flash0__DOT__spi0_tx 
			= vlTOPp->top__DOT__flash0__DOT__regresp;
		    vlTOPp->top__DOT__flash0__DOT__spi0_tx_dv = 1U;
		    vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 0U;
		} else {
		    if ((3U == (IData)(vlTOPp->top__DOT__flash0__DOT__flash_state))) {
			if (vlTOPp->top__DOT__flash0__DOT__spi0_rx_dv) {
			    vlTOPp->__Vdly__top__DOT__flash0__DOT__page 
				= vlTOPp->top__DOT__flash0__DOT__spi0_rx;
			    vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 0U;
			}
		    } else {
			if ((4U == (IData)(vlTOPp->top__DOT__flash0__DOT__flash_state))) {
			    if (vlTOPp->top__DOT__flash0__DOT__spi0_rx_dv) {
				vlTOPp->__Vdly__top__DOT__flash0__DOT__offset 
				    = vlTOPp->top__DOT__flash0__DOT__spi0_rx;
				vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 0U;
			    }
			} else {
			    if ((5U == (IData)(vlTOPp->top__DOT__flash0__DOT__flash_state))) {
				if (vlTOPp->top__DOT__flash0__DOT__spi0_rx_dv) {
				    vlTOPp->top__DOT__flash0__DOT__data_wren = 1U;
				    vlTOPp->top__DOT__flash0__DOT__data_value 
					= vlTOPp->top__DOT__flash0__DOT__spi0_rx;
				    __Vdlyvval__top__DOT__flash0__DOT__data__v0 
					= vlTOPp->top__DOT__flash0__DOT__spi0_rx;
				    vlTOPp->__Vdlyvset__top__DOT__flash0__DOT__data__v0 = 1U;
				    __Vdlyvdim0__top__DOT__flash0__DOT__data__v0 
					= (0x1fffU 
					   & (IData)(vlTOPp->top__DOT__flash0__DOT__dataaddr));
				    vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 0U;
				}
			    } else {
				vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state = 0U;
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at vd002.sv:92
    if (vlTOPp->rst) {
	vlTOPp->top__DOT__sensor0__DOT__spi0_tx_dv = 0U;
	vlTOPp->__Vdly__top__DOT__sensor0__DOT__regaddr = 0U;
	vlTOPp->__Vdly__top__DOT__sensor0__DOT__regresp = 0U;
	vlTOPp->__Vdly__top__DOT__sensor0__DOT__readcnt = 0U;
    } else {
	if (vlTOPp->cs1) {
	    if ((3U == (IData)(vlTOPp->top__DOT__sensor0__DOT__sensor_state))) {
		vlTOPp->__Vdly__top__DOT__sensor0__DOT__dataidx 
		    = (0x1fffU & ((IData)(vlTOPp->top__DOT__sensor0__DOT__dataidx) 
				  + (IData)(vlTOPp->top__DOT__sensor0__DOT__streamlen)));
		vlTOPp->__Vdly__top__DOT__sensor0__DOT__sensor_state = 0U;
		vlTOPp->__Vdly__top__DOT__sensor0__DOT__streamlen = 0U;
	    }
	} else {
	    if ((0U == (IData)(vlTOPp->top__DOT__sensor0__DOT__sensor_state))) {
		vlTOPp->top__DOT__sensor0__DOT__spi0_tx_dv = 0U;
		vlTOPp->__Vdly__top__DOT__sensor0__DOT__regaddr = 0U;
		vlTOPp->__Vdly__top__DOT__sensor0__DOT__regresp = 0U;
		if (vlTOPp->top__DOT__sensor0__DOT__spi0_rx_dv) {
		    vlTOPp->__Vdly__top__DOT__sensor0__DOT__regaddr 
			= vlTOPp->top__DOT__sensor0__DOT__spi0_rx;
		    vlTOPp->__Vdly__top__DOT__sensor0__DOT__sensor_state = 1U;
		}
	    } else {
		if ((1U == (IData)(vlTOPp->top__DOT__sensor0__DOT__sensor_state))) {
		    if ((0xfU == (IData)(vlTOPp->top__DOT__sensor0__DOT__regaddr))) {
			vlTOPp->__Vdly__top__DOT__sensor0__DOT__regresp = 0x35U;
			vlTOPp->__Vdly__top__DOT__sensor0__DOT__sensor_state = 2U;
		    } else {
			if ((0x10U == (IData)(vlTOPp->top__DOT__sensor0__DOT__regaddr))) {
			    vlTOPp->__Vdly__top__DOT__sensor0__DOT__readcnt 
				= (7U & ((IData)(1U) 
					 + (IData)(vlTOPp->top__DOT__sensor0__DOT__readcnt)));
			    vlTOPp->__Vdly__top__DOT__sensor0__DOT__streamlen 
				= vlTOPp->top__DOT__sensor0__DOT__sensordata
				[vlTOPp->top__DOT__sensor0__DOT__dataidx];
			    vlTOPp->__Vdly__top__DOT__sensor0__DOT__stream_firstbyte = 1U;
			    vlTOPp->__Vdly__top__DOT__sensor0__DOT__sensor_state = 3U;
			    vlTOPp->__Vdly__top__DOT__sensor0__DOT__dataidx 
				= (0x1fffU & ((IData)(1U) 
					      + (IData)(vlTOPp->top__DOT__sensor0__DOT__dataidx)));
			} else {
			    if ((0x11U == (IData)(vlTOPp->top__DOT__sensor0__DOT__regaddr))) {
				vlTOPp->__Vdly__top__DOT__sensor0__DOT__regresp 
				    = vlTOPp->top__DOT__sensor0__DOT__sensordata
				    [vlTOPp->top__DOT__sensor0__DOT__dataidx];
				vlTOPp->__Vdly__top__DOT__sensor0__DOT__sensor_state = 2U;
			    } else {
				vlTOPp->__Vdly__top__DOT__sensor0__DOT__regresp = 0xeeU;
				vlTOPp->__Vdly__top__DOT__sensor0__DOT__sensor_state = 0U;
			    }
			}
		    }
		} else {
		    if ((2U == (IData)(vlTOPp->top__DOT__sensor0__DOT__sensor_state))) {
			vlTOPp->top__DOT__sensor0__DOT__spi0_tx 
			    = vlTOPp->top__DOT__sensor0__DOT__regresp;
			vlTOPp->top__DOT__sensor0__DOT__spi0_tx_dv = 1U;
			vlTOPp->__Vdly__top__DOT__sensor0__DOT__sensor_state = 0U;
		    } else {
			if ((3U == (IData)(vlTOPp->top__DOT__sensor0__DOT__sensor_state))) {
			    if (((IData)(vlTOPp->top__DOT__sensor0__DOT__tx_done) 
				 | (IData)(vlTOPp->top__DOT__sensor0__DOT__stream_firstbyte))) {
				vlTOPp->top__DOT__sensor0__DOT__spi0_tx 
				    = vlTOPp->top__DOT__sensor0__DOT__sensordata
				    [vlTOPp->top__DOT__sensor0__DOT__dataidx];
				vlTOPp->top__DOT__sensor0__DOT__spi0_tx_dv = 1U;
				vlTOPp->__Vdly__top__DOT__sensor0__DOT__tx_done = 0U;
				vlTOPp->__Vdly__top__DOT__sensor0__DOT__stream_firstbyte = 0U;
				vlTOPp->__Vdly__top__DOT__sensor0__DOT__streamlen 
				    = (0xffU & ((IData)(vlTOPp->top__DOT__sensor0__DOT__streamlen) 
						- (IData)(1U)));
				vlTOPp->__Vdly__top__DOT__sensor0__DOT__dataidx 
				    = (0x1fffU & ((
						   (0U 
						    == 
						    ((IData)(vlTOPp->top__DOT__sensor0__DOT__streamlen) 
						     - (IData)(1U))) 
						   & (0U 
						      == 
						      vlTOPp->top__DOT__sensor0__DOT__sensordata
						      [
						      (0x1fffU 
						       & ((IData)(1U) 
							  + (IData)(vlTOPp->top__DOT__sensor0__DOT__dataidx)))]))
						   ? 0U
						   : 
						  ((IData)(1U) 
						   + (IData)(vlTOPp->top__DOT__sensor0__DOT__dataidx))));
				vlTOPp->__Vdly__top__DOT__sensor0__DOT__sensor_state 
				    = ((0U == ((IData)(vlTOPp->top__DOT__sensor0__DOT__streamlen) 
					       - (IData)(1U)))
				        ? 0U : 3U);
			    }
			} else {
			    vlTOPp->__Vdly__top__DOT__sensor0__DOT__sensor_state = 0U;
			}
		    }
		}
	    }
	}
    }
    vlTOPp->top__DOT__flash0__DOT__regresp = vlTOPp->__Vdly__top__DOT__flash0__DOT__regresp;
    vlTOPp->top__DOT__flash0__DOT__flash_state = vlTOPp->__Vdly__top__DOT__flash0__DOT__flash_state;
    // ALWAYSPOST at vd003.sv:178
    if (vlTOPp->__Vdlyvset__top__DOT__flash0__DOT__data__v0) {
	vlTOPp->top__DOT__flash0__DOT__data[__Vdlyvdim0__top__DOT__flash0__DOT__data__v0] 
	    = __Vdlyvval__top__DOT__flash0__DOT__data__v0;
    }
    vlTOPp->top__DOT__flash0__DOT__page = vlTOPp->__Vdly__top__DOT__flash0__DOT__page;
    vlTOPp->top__DOT__flash0__DOT__offset = vlTOPp->__Vdly__top__DOT__flash0__DOT__offset;
    vlTOPp->top__DOT__flash0__DOT__regaddr = vlTOPp->__Vdly__top__DOT__flash0__DOT__regaddr;
    vlTOPp->top__DOT__sensor0__DOT__streamlen = vlTOPp->__Vdly__top__DOT__sensor0__DOT__streamlen;
    vlTOPp->top__DOT__sensor0__DOT__readcnt = vlTOPp->__Vdly__top__DOT__sensor0__DOT__readcnt;
    vlTOPp->top__DOT__sensor0__DOT__regaddr = vlTOPp->__Vdly__top__DOT__sensor0__DOT__regaddr;
    vlTOPp->top__DOT__sensor0__DOT__regresp = vlTOPp->__Vdly__top__DOT__sensor0__DOT__regresp;
    vlTOPp->top__DOT__sensor0__DOT__dataidx = vlTOPp->__Vdly__top__DOT__sensor0__DOT__dataidx;
    vlTOPp->top__DOT__sensor0__DOT__sensor_state = vlTOPp->__Vdly__top__DOT__sensor0__DOT__sensor_state;
    vlTOPp->top__DOT__sensor0__DOT__stream_firstbyte 
	= vlTOPp->__Vdly__top__DOT__sensor0__DOT__stream_firstbyte;
    vlTOPp->top__DOT__flash0__DOT__dataaddr = (((IData)(vlTOPp->top__DOT__flash0__DOT__page) 
						<< 8U) 
					       | (IData)(vlTOPp->top__DOT__flash0__DOT__offset));
    vlTOPp->top__DOT__flash0__DOT__wren = (1U & ((IData)(vlTOPp->top__DOT__flash0__DOT__regaddr) 
						 >> 7U));
    vlTOPp->top__DOT__flash0__DOT__effaddr = (0x7fU 
					      & (IData)(vlTOPp->top__DOT__flash0__DOT__regaddr));
}

VL_INLINE_OPT void Vtop::_combo__TOP__14(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_combo__TOP__14\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->miso__out1 = (1U & ((((((~ (IData)(vlTOPp->cs1)) 
				    & ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Preload_MISO)
				        ? ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte) 
					   >> 7U) : (IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_SPI_MISO_Bit))) 
				   & (~ (IData)(vlTOPp->cs1))) 
				  & (~ (IData)(vlTOPp->cs1))) 
				 & (~ (IData)(vlTOPp->cs1))) 
				| (((((~ (IData)(vlTOPp->cs2)) 
				      & ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Preload_MISO)
					  ? ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte) 
					     >> 7U)
					  : (IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_SPI_MISO_Bit))) 
				     & (~ (IData)(vlTOPp->cs2))) 
				    & (~ (IData)(vlTOPp->cs2))) 
				   & (~ (IData)(vlTOPp->cs2)))));
    vlTOPp->miso = ((IData)(vlTOPp->miso__out1) & (
						   (~ (IData)(vlTOPp->cs1)) 
						   | (~ (IData)(vlTOPp->cs2))));
}

VL_INLINE_OPT void Vtop::_sequent__TOP__15(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__15\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at SPI_Slave.v:120
    if (vlTOPp->top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L) {
	vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done 
	    = vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done;
	if (((~ (IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done)) 
	     & (IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done))) {
	    vlTOPp->top__DOT__flash0__DOT__spi0_rx_dv = 1U;
	    vlTOPp->top__DOT__flash0__DOT__spi0_rx 
		= vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Byte;
	} else {
	    vlTOPp->top__DOT__flash0__DOT__spi0_rx_dv = 0U;
	}
	vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done 
	    = vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Done;
    } else {
	vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done = 0U;
	vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done = 0U;
	vlTOPp->top__DOT__flash0__DOT__spi0_rx_dv = 0U;
	vlTOPp->top__DOT__flash0__DOT__spi0_rx = 0U;
    }
    // ALWAYS at SPI_Slave.v:120
    if (vlTOPp->top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L) {
	vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done 
	    = vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done;
	if (((~ (IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done)) 
	     & (IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done))) {
	    vlTOPp->top__DOT__sensor0__DOT__spi0_rx_dv = 1U;
	    vlTOPp->top__DOT__sensor0__DOT__spi0_rx 
		= vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Byte;
	} else {
	    vlTOPp->top__DOT__sensor0__DOT__spi0_rx_dv = 0U;
	}
	vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done 
	    = vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Done;
    } else {
	vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done = 0U;
	vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done = 0U;
	vlTOPp->top__DOT__sensor0__DOT__spi0_rx_dv = 0U;
	vlTOPp->top__DOT__sensor0__DOT__spi0_rx = 0U;
    }
    vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done 
	= vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done;
    vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done 
	= vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done;
    vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done 
	= vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done;
    vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done 
	= vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done;
}

VL_INLINE_OPT void Vtop::_sequent__TOP__16(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__16\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top__DOT__sensor0__DOT__tx_done = vlTOPp->__Vdly__top__DOT__sensor0__DOT__tx_done;
}

VL_INLINE_OPT void Vtop::_sequent__TOP__17(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__17\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at SPI_Slave.v:86
    if (vlTOPp->cs2) {
	vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count = 0U;
	vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Done = 0U;
    } else {
	vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count 
	    = (7U & ((IData)(1U) + (IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count)));
	vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte 
	    = ((0xfeU & ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte) 
			 << 1U)) | (IData)(vlTOPp->mosi));
	if ((7U == (IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count))) {
	    vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Done = 1U;
	    vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Byte 
		= ((0xfeU & ((IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte) 
			     << 1U)) | (IData)(vlTOPp->mosi));
	} else {
	    if ((2U == (IData)(vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count))) {
		vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Done = 0U;
	    }
	}
    }
    vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count 
	= vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count;
    vlTOPp->top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte 
	= vlTOPp->__Vdly__top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte;
}

VL_INLINE_OPT void Vtop::_combo__TOP__18(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_combo__TOP__18\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L 
	= (1U & (~ (IData)(vlTOPp->rst)));
}

VL_INLINE_OPT void Vtop::_sequent__TOP__19(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__19\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at SPI_Slave.v:86
    if (vlTOPp->cs1) {
	vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count = 0U;
	vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Done = 0U;
    } else {
	vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count 
	    = (7U & ((IData)(1U) + (IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count)));
	vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte 
	    = ((0xfeU & ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte) 
			 << 1U)) | (IData)(vlTOPp->mosi));
	if ((7U == (IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count))) {
	    vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Done = 1U;
	    vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Byte 
		= ((0xfeU & ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte) 
			     << 1U)) | (IData)(vlTOPp->mosi));
	} else {
	    if ((2U == (IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count))) {
		vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Done = 0U;
	    }
	}
    }
    vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count 
	= vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count;
    vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte 
	= vlTOPp->__Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte;
}

void Vtop::_eval(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
	 | ((~ (IData)(vlTOPp->__VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L)) 
	    & (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L)))) {
	vlTOPp->_sequent__TOP__1(vlSymsp);
    }
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
	vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    if (((IData)(vlTOPp->clk) ^ (IData)(vlTOPp->__Vclklast__TOP__clk))) {
	vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    vlTOPp->_combo__TOP__5(vlSymsp);
    vlTOPp->__Vm_traceActivity = (2U | vlTOPp->__Vm_traceActivity);
    if (((~ (IData)(vlTOPp->clk)) & (IData)(vlTOPp->__Vclklast__TOP__clk))) {
	vlTOPp->_sequent__TOP__8(vlSymsp);
    }
    if ((((IData)(vlTOPp->cs2) & (~ (IData)(vlTOPp->__Vclklast__TOP__cs2))) 
	 | ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk) 
	    & (~ (IData)(vlTOPp->__Vclklast__TOP__top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk))))) {
	vlTOPp->_sequent__TOP__9(vlSymsp);
	vlTOPp->__Vm_traceActivity = (4U | vlTOPp->__Vm_traceActivity);
    }
    if ((((IData)(vlTOPp->cs1) & (~ (IData)(vlTOPp->__Vclklast__TOP__cs1))) 
	 | ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk) 
	    & (~ (IData)(vlTOPp->__Vclklast__TOP__top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk))))) {
	vlTOPp->_sequent__TOP__10(vlSymsp);
	vlTOPp->__Vm_traceActivity = (8U | vlTOPp->__Vm_traceActivity);
    }
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
	 | ((~ (IData)(vlTOPp->__VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L)) 
	    & (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L)))) {
	vlTOPp->_sequent__TOP__12(vlSymsp);
	vlTOPp->__Vm_traceActivity = (0x10U | vlTOPp->__Vm_traceActivity);
    }
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
	vlTOPp->_sequent__TOP__13(vlSymsp);
	vlTOPp->__Vm_traceActivity = (0x20U | vlTOPp->__Vm_traceActivity);
    }
    vlTOPp->_combo__TOP__14(vlSymsp);
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
	 | ((~ (IData)(vlTOPp->__VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L)) 
	    & (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L)))) {
	vlTOPp->_sequent__TOP__15(vlSymsp);
	vlTOPp->__Vm_traceActivity = (0x40U | vlTOPp->__Vm_traceActivity);
    }
    if (((IData)(vlTOPp->clk) ^ (IData)(vlTOPp->__Vclklast__TOP__clk))) {
	vlTOPp->_sequent__TOP__16(vlSymsp);
	vlTOPp->__Vm_traceActivity = (0x80U | vlTOPp->__Vm_traceActivity);
    }
    if ((((IData)(vlTOPp->cs2) & (~ (IData)(vlTOPp->__Vclklast__TOP__cs2))) 
	 | ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk) 
	    & (~ (IData)(vlTOPp->__Vclklast__TOP__top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk))))) {
	vlTOPp->_sequent__TOP__17(vlSymsp);
	vlTOPp->__Vm_traceActivity = (0x100U | vlTOPp->__Vm_traceActivity);
    }
    vlTOPp->_combo__TOP__18(vlSymsp);
    if ((((IData)(vlTOPp->cs1) & (~ (IData)(vlTOPp->__Vclklast__TOP__cs1))) 
	 | ((IData)(vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk) 
	    & (~ (IData)(vlTOPp->__Vclklast__TOP__top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk))))) {
	vlTOPp->_sequent__TOP__19(vlSymsp);
	vlTOPp->__Vm_traceActivity = (0x200U | vlTOPp->__Vm_traceActivity);
    }
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L 
	= vlTOPp->__VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L;
    vlTOPp->__Vclklast__TOP__cs2 = vlTOPp->cs2;
    vlTOPp->__Vclklast__TOP__top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk 
	= vlTOPp->top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk;
    vlTOPp->__Vclklast__TOP__cs1 = vlTOPp->cs1;
    vlTOPp->__VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L 
	= vlTOPp->top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L;
}

void Vtop::_eval_initial(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval_initial\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__7(vlSymsp);
    vlTOPp->__Vm_traceActivity = (1U | vlTOPp->__Vm_traceActivity);
}

void Vtop::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::final\n"); );
    // Variables
    Vtop__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vtop::_eval_settle(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval_settle\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__6(vlSymsp);
    vlTOPp->__Vm_traceActivity = (1U | vlTOPp->__Vm_traceActivity);
    vlTOPp->_settle__TOP__11(vlSymsp);
}

VL_INLINE_OPT QData Vtop::_change_request(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_change_request\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    __req |= ((vlTOPp->top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L ^ vlTOPp->__Vchglast__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L));
    VL_DEBUG_IF( if(__req && ((vlTOPp->top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L ^ vlTOPp->__Vchglast__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L))) VL_DBG_MSGF("        CHANGE: SPI_Slave.v:37: top.sensor0.__Vcellinp__spi0__i_Rst_L\n"); );
    // Final
    vlTOPp->__Vchglast__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L 
	= vlTOPp->top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L;
    return __req;
}

#ifdef VL_DEBUG
void Vtop::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
	Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst & 0xfeU))) {
	Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((cs1 & 0xfeU))) {
	Verilated::overWidthError("cs1");}
    if (VL_UNLIKELY((cs2 & 0xfeU))) {
	Verilated::overWidthError("cs2");}
    if (VL_UNLIKELY((sck & 0xfeU))) {
	Verilated::overWidthError("sck");}
    if (VL_UNLIKELY((mosi & 0xfeU))) {
	Verilated::overWidthError("mosi");}
}
#endif // VL_DEBUG

void Vtop::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst = VL_RAND_RESET_I(1);
    cs1 = VL_RAND_RESET_I(1);
    cs2 = VL_RAND_RESET_I(1);
    sck = VL_RAND_RESET_I(1);
    mosi = VL_RAND_RESET_I(1);
    miso = VL_RAND_RESET_I(1);
    miso__out1 = VL_RAND_RESET_I(1);
    top__DOT__sensor0__DOT__spi0_rx_dv = VL_RAND_RESET_I(1);
    top__DOT__sensor0__DOT__spi0_rx = VL_RAND_RESET_I(8);
    top__DOT__sensor0__DOT__spi0_tx_dv = VL_RAND_RESET_I(1);
    top__DOT__sensor0__DOT__spi0_tx = VL_RAND_RESET_I(8);
    top__DOT__sensor0__DOT__tx_done = VL_RAND_RESET_I(1);
    top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L = VL_RAND_RESET_I(1);
    top__DOT__sensor0__DOT__regaddr = VL_RAND_RESET_I(8);
    top__DOT__sensor0__DOT__regresp = VL_RAND_RESET_I(8);
    top__DOT__sensor0__DOT__readcnt = VL_RAND_RESET_I(3);
    top__DOT__sensor0__DOT__streamlen = VL_RAND_RESET_I(8);
    top__DOT__sensor0__DOT__dataidx = VL_RAND_RESET_I(13);
    top__DOT__sensor0__DOT__stream_firstbyte = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<8192; ++__Vi0) {
	    top__DOT__sensor0__DOT__sensordata[__Vi0] = VL_RAND_RESET_I(8);
    }}
    top__DOT__sensor0__DOT__sensor_state = VL_RAND_RESET_I(2);
    top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk = VL_RAND_RESET_I(1);
    top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count = VL_RAND_RESET_I(3);
    top__DOT__sensor0__DOT__spi0__DOT__r_TX_Bit_Count = VL_RAND_RESET_I(3);
    top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte = VL_RAND_RESET_I(8);
    top__DOT__sensor0__DOT__spi0__DOT__r_RX_Byte = VL_RAND_RESET_I(8);
    top__DOT__sensor0__DOT__spi0__DOT__r_RX_Done = VL_RAND_RESET_I(1);
    top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done = VL_RAND_RESET_I(1);
    top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done = VL_RAND_RESET_I(1);
    top__DOT__sensor0__DOT__spi0__DOT__r_TX_Byte = VL_RAND_RESET_I(8);
    top__DOT__sensor0__DOT__spi0__DOT__r_SPI_MISO_Bit = VL_RAND_RESET_I(1);
    top__DOT__sensor0__DOT__spi0__DOT__r_Preload_MISO = VL_RAND_RESET_I(1);
    top__DOT__flash0__DOT__spi0_rx_dv = VL_RAND_RESET_I(1);
    top__DOT__flash0__DOT__spi0_rx = VL_RAND_RESET_I(8);
    top__DOT__flash0__DOT__spi0_tx_dv = VL_RAND_RESET_I(1);
    top__DOT__flash0__DOT__spi0_tx = VL_RAND_RESET_I(8);
    top__DOT__flash0__DOT__page = VL_RAND_RESET_I(8);
    top__DOT__flash0__DOT__offset = VL_RAND_RESET_I(8);
    { int __Vi0=0; for (; __Vi0<8192; ++__Vi0) {
	    top__DOT__flash0__DOT__data[__Vi0] = VL_RAND_RESET_I(8);
    }}
    top__DOT__flash0__DOT__dataaddr = VL_RAND_RESET_I(16);
    top__DOT__flash0__DOT__regaddr = VL_RAND_RESET_I(8);
    top__DOT__flash0__DOT__effaddr = VL_RAND_RESET_I(8);
    top__DOT__flash0__DOT__wren = VL_RAND_RESET_I(1);
    top__DOT__flash0__DOT__regresp = VL_RAND_RESET_I(8);
    top__DOT__flash0__DOT__data_wren = VL_RAND_RESET_I(1);
    top__DOT__flash0__DOT__data_value = VL_RAND_RESET_I(8);
    top__DOT__flash0__DOT__flash_state = VL_RAND_RESET_I(3);
    top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count = VL_RAND_RESET_I(3);
    top__DOT__flash0__DOT__spi0__DOT__r_TX_Bit_Count = VL_RAND_RESET_I(3);
    top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte = VL_RAND_RESET_I(8);
    top__DOT__flash0__DOT__spi0__DOT__r_RX_Byte = VL_RAND_RESET_I(8);
    top__DOT__flash0__DOT__spi0__DOT__r_RX_Done = VL_RAND_RESET_I(1);
    top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done = VL_RAND_RESET_I(1);
    top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done = VL_RAND_RESET_I(1);
    top__DOT__flash0__DOT__spi0__DOT__r_TX_Byte = VL_RAND_RESET_I(8);
    top__DOT__flash0__DOT__spi0__DOT__r_SPI_MISO_Bit = VL_RAND_RESET_I(1);
    top__DOT__flash0__DOT__spi0__DOT__r_Preload_MISO = VL_RAND_RESET_I(1);
    __Vdly__top__DOT__sensor0__DOT__tx_done = VL_RAND_RESET_I(1);
    __Vdly__top__DOT__sensor0__DOT__regaddr = VL_RAND_RESET_I(8);
    __Vdly__top__DOT__sensor0__DOT__regresp = VL_RAND_RESET_I(8);
    __Vdly__top__DOT__sensor0__DOT__readcnt = VL_RAND_RESET_I(3);
    __Vdly__top__DOT__sensor0__DOT__dataidx = VL_RAND_RESET_I(13);
    __Vdly__top__DOT__sensor0__DOT__sensor_state = VL_RAND_RESET_I(2);
    __Vdly__top__DOT__sensor0__DOT__streamlen = VL_RAND_RESET_I(8);
    __Vdly__top__DOT__sensor0__DOT__stream_firstbyte = VL_RAND_RESET_I(1);
    __Vdly__top__DOT__flash0__DOT__regaddr = VL_RAND_RESET_I(8);
    __Vdly__top__DOT__flash0__DOT__regresp = VL_RAND_RESET_I(8);
    __Vdly__top__DOT__flash0__DOT__flash_state = VL_RAND_RESET_I(3);
    __Vdly__top__DOT__flash0__DOT__page = VL_RAND_RESET_I(8);
    __Vdly__top__DOT__flash0__DOT__offset = VL_RAND_RESET_I(8);
    __Vdlyvset__top__DOT__flash0__DOT__data__v0 = VL_RAND_RESET_I(1);
    __Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_RX_Bit_Count = VL_RAND_RESET_I(3);
    __Vdly__top__DOT__sensor0__DOT__spi0__DOT__r_Temp_RX_Byte = VL_RAND_RESET_I(8);
    __Vdly__top__DOT__sensor0__DOT__spi0__DOT__r3_RX_Done = VL_RAND_RESET_I(1);
    __Vdly__top__DOT__sensor0__DOT__spi0__DOT__r2_RX_Done = VL_RAND_RESET_I(1);
    __Vdly__top__DOT__flash0__DOT__spi0__DOT__r_RX_Bit_Count = VL_RAND_RESET_I(3);
    __Vdly__top__DOT__flash0__DOT__spi0__DOT__r_Temp_RX_Byte = VL_RAND_RESET_I(8);
    __Vdly__top__DOT__flash0__DOT__spi0__DOT__r3_RX_Done = VL_RAND_RESET_I(1);
    __Vdly__top__DOT__flash0__DOT__spi0__DOT__r2_RX_Done = VL_RAND_RESET_I(1);
    __VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L = VL_RAND_RESET_I(1);
    __Vclklast__TOP__clk = VL_RAND_RESET_I(1);
    __Vclklast__TOP____VinpClk__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L = VL_RAND_RESET_I(1);
    __Vclklast__TOP__cs2 = VL_RAND_RESET_I(1);
    __Vclklast__TOP__top__DOT__sensor0__DOT__spi0__DOT__w_SPI_Clk = VL_RAND_RESET_I(1);
    __Vclklast__TOP__cs1 = VL_RAND_RESET_I(1);
    __Vchglast__TOP__top__DOT__sensor0__DOT____Vcellinp__spi0__i_Rst_L = VL_RAND_RESET_I(1);
    __Vm_traceActivity = VL_RAND_RESET_I(32);
}
