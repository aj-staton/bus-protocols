# Copyright 2019 Charles Daniels, Jason Bakos, Philip Conrad

include config.mk

F_CPU_DEF=-DF_CPU=$(F_CPU)
UART_BAUDRATE_DEF=-DUART_BAUDRATE=$(UART_BAUDRATE)
DEFS=$(F_CPU_DEF) $(UART_BAUDRATE_DEF)

CC = avr-gcc
CFLAGS = $(OPTIMIZATION) -mmcu=$(MCUNAME) $(DEFS) -std=c99

.PHONY: clean all burn

all: main.elf main.lst main.hex main.map

main.elf: main.o  # add more objects HERE
	$(CC) $(CFLAGS) -o main.elf $^

# generate an assembler dump from the C code
main.lst: main.elf
	avr-objdump -C -g -d -h -S main.elf > main.lst

# generate the memory map of the ELF file
main.map: main.elf
	$(CC) $(CFLAGS) -Wl,-Map,main.map *.o

# generate an avrdude-compatible hex file
main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size main.hex

# generic rules to generate object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

# flash the AVR with the generate hex file
burn: main.hex
	@printf "Burn Baby Burn...\n"
	avrdude -p $(PARTNO) -c $(AVRDUDE_PROGRAMMER) -U flash:w:main.hex:i


clean:
	rm -f *.o *.lst *.elf *.map *.hex a.out

