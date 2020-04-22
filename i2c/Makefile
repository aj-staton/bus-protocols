# Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels

VERILATOR=verilator
VERILATOR_ROOT ?= $(shell bash -c 'verilator -V|grep VERILATOR_ROOT | head -1 | sed -e "s/^.*=\s*//"')
VINC := $(VERILATOR_ROOT)/include

SIGROK_URL ?= https://sigrok.org/download/binary/sigrok-cli/sigrok-cli-0.7.1-x86_64.AppImage
USE_SIGROK_APPIMAGE ?= YES
SIGROK = ./sigrok-cli

all: simulation
.PHONY: all

trace.vcd: simulation
	./simulation 2>&1 | tee simulation.log

filtered.vcd: trace.vcd
	awk -f ./vcdfilter.awk -v MAXDEPTH=1 -v NOSCOPE=1 -v SELECT=sda,scl < $< > $@


flashio.vcd: trace.vcd
	awk -f ./vcdfilter.awk -v MAXDEPTH=99 -v NOSCOPE=0 -v SELECT=data_wren,dataaddr,data_value < $< > $@

flashdump: flashio.vcd
	python3 flashdump.py < flashio.vcd
.PHONY: flashdump

decode: filtered.vcd sigrok
	./sigrok-cli -I vcd -i ./filtered.vcd -P i2c:sda=sda:scl=scl -A i2c=address-read:address-write:data-read:data-write
.PHONY: decode

waves: trace.vcd
	printf 'gtkwave::addSignalsFromList {TOP.clk TOP.rst TOP.scl_i TOP.scl TOP.sda_i TOP.sda}\n' | gtkwave --wish ./trace.vcd
.PHONY: waves


simulation: main.cpp support.cpp support.h obj_dir/Vtop__ALL.a
	g++ -I$(VINC) -I obj_dir -g \
		$(VINC)/verilated.cpp \
                $(VINC)/verilated_vcd_c.cpp \
		main.cpp support.cpp obj_dir/Vtop__ALL.a \
		-o simulation

obj_dir/Vtop__ALL.a: obj_dir/Vtop.cpp
	make -C obj_dir -f Vtop.mk

obj_dir/Vtop.cpp: top.sv i2c_slave.v i2c_master.sv
	$(VERILATOR) -Wno-fatal --trace -Wall -cc top.sv

clean:
	rm -rf obj_dir simulation simulation.log trace.vcd filtered.vcd flashio.vcd
.PHONY: clean

sigrok:
	if [ "$(USE_SIGROK_APPIMAGE)" = "YES" ] ; then if [ ! -x ./sigrok-cli ] ; then wget "$(SIGROK_URL)" -O ./sigrok-cli ; chmod +x ./sigrok-cli ; fi ; fi
.PHONY: sigrok
