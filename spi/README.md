# Serial Peripheral Interface
The project uses [Verilator](https://www.veripool.org/wiki/verilator) to simulate the written
code in a Verilog "peripheral". Since Verilartor is build on C++, we must use a `*.cpp` file for
its input; however, the goal is to use as much C notation and practice as possible.

A bit-banged implementation of SPI communication was implemented as the main
functionality of the project. It is found in `main.cpp`.

## Dependancies
To resolve them all (assuming you're using the APT package manager):
```bash
$ sudo apt-get install verilator gtkwave build-essential sigrok-cli
```
* *verilator* is the package that simulates the C++ through Verilog HDL.
* *gtkwave* is used to view a GUI of `*.vcd ` files, or a signal's "Value Change Dump"
   over time.
* *sigrok-cli* also reads `*.vcd` files, but through the CLI.
* *build-essential* is standard on most Unix distros, but is included for
   thoroghness. It includes things like GCC and standard libraries.

## Execution
To run the simulation in the CLI (with sigrok), use `make decode`. For a
simulation with a GUI (like an O-Scope), use `make waves`.

## Credits
Pretty much all of the content in here is not my own, original though. Much of
it was put together by Dr. Jason Bakos, Charles Daniels and Philip Conrad.

My own thought is within the 'main.cpp' file. The Makefile, Verilog files, and
'support' header and source files are not a product of my work.
