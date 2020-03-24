# UART
Universal asynchronous reciever-transmitter communication, or 'UART' (sometimes USART), was the focus of this project. This protocol is a one-wire, serial communication channel. Its baudrate limitations are not always beneficial for high-level applications; however, UART hardware is found on many microcontrollers and FPGAs. It is a well-known communication protocol in the world of embedded systems and reconfigurable computing.

## Project Deliverables
There were four deliverables produced in this sequence of projects. They were:
 1. A blinking LED controlled with GPIO pins---the embedded "Hello World"
 2. Using the dedicated UART hardware to write "Hello World" to the serial connection.
 3. Again, using the dedicated UART hardware to read and write variable data across the serial connection.
 4. Removing the hardware support from Part 3. So, a GPIO pin was used to create a manual, software-defined implemtation of the UART communication channel. In a "real-world" scenario, some chips (e.g., this one) have only one piece of dedicated UART hardware. Or, what if all communication hardware on the chip is being used for peripherals? In either of these cases, it's possible that a debugging output might be necessary for development purposes;but, isn't available.The easiest fix is to use a software-defined implementation of the needed communication.

#### The Hardware
The Atmel Atmega328p was used for this project. It is:
* a SoC 8-bit microcontroller built on a RISC architecture;
* using the AVR instruction set;
* compatible with dedicated hardware for I2C, SPI, and UART communication.

#### Execution
A Unix development environment was used for this project. To upload/write to the board, clone the repo, connect the board to the computer with a USB, then:
```bash
$ cd uControllers/uart/
$ make burn
```
To see the data passed on the serial connection:
```bash
$ picocom -b 57600 /dev/ttyUSB0
```
The '-b' flag specifies the baudrate, which in this case is 57,600 bps. In part 4, this baudrate was modified to 9,600 bps. Data was corrupted at the high baudrate. Dependancies in the makefile exist for baudrate; change those as well if a lowering is needed. 

## Credits
* These assignments were designed by Dr. Jason Bakos, Charles Daniels, and Phillip Conrad. All copyright on course materials, and some of the framework to the source code belongs to them. This includes the Makefile; that is not my own, original thought.
 * Myself, in combination with Robby Carff, completed the substance of these projects (parts 1-4).
