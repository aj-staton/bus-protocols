# Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels

VERILATOR=verilator
VERILATOR_ROOT ?= $(shell bash -c 'verilator -V|grep VERILATOR_ROOT | head -1 | sed -e "s/^.*=\s*//"')
VINC := $(VERILATOR_ROOT)/include

all: simulation
.PHONY: all

trace.vcd: simulation
	./simulation 2>&1 | tee simulation.log

filtered.vcd: trace.vcd
	awk -f ./vcdfilter.awk -v MAXDEPTH=1 -v NOSCOPE=1 -v SELECT=cs,sck,miso,mosi < $< > $@

decode: filtered.vcd
	@echo "transmitted from master to slave... "
	sigrok-cli -I vcd -i ./filtered.vcd -A spi=mosi-data -P spi:cpha=1:cpol=1:bitorder=msb-first:miso=miso:mosi=mosi:cs=cs:clk=sck
	@echo "transmitted from slave to master... "
	sigrok-cli -I vcd -i ./filtered.vcd -A spi=miso-data -P spi:cpha=1:cpol=1:bitorder=msb-first:miso=miso:mosi=mosi:cs=cs:clk=sck
.PHONY: decode

waves: trace.vcd
	printf 'gtkwave::addSignalsFromList {TOP.clk TOP.rst TOP.cs TOP.sck TOP.mosi TOP.miso}\n' | gtkwave --wish ./trace.vcd
.PHONY: waves


simulation: main.cpp support.cpp support.h obj_dir/Vtop__ALL.a
	g++ -I$(VINC) -I obj_dir \
		$(VINC)/verilated.cpp \
                $(VINC)/verilated_vcd_c.cpp \
		main.cpp support.cpp obj_dir/Vtop__ALL.a \
		-o simulation

obj_dir/Vtop__ALL.a: obj_dir/Vtop.cpp
	make -C obj_dir -f Vtop.mk

obj_dir/Vtop.cpp: top.sv SPI_Slave.v sensor.sv
	$(VERILATOR) --trace -Wall -cc top.sv

clean:
	rm -rf obj_dir simulation simulation.log trace.vcd filtered.vcd
.PHONY: clean
