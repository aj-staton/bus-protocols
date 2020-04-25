# Inter-Integrated Circuit
I2C was used to read sensor data and write it to an page in flash memory.

In this project, I was responsible for implementing a read function for I2C. In summary, I:
 * Waited for SCL's start edge,
 * Read the MSB-order 7-bit address on SDA from the master,
 * acknowledged the address if it was correct,
 * Read the next 8-bits on SDA from the master, 
 * send the acknowledgement, and; 
 * waited for the stop edge to end the transaction
 
 ## Structure
 This was another project for the virtual classroom. The sensor and flash memory (created in Verilog) were given to me, then tested in Verilator with various `make` targets.
 
The reference solution is in `refdump.txt`; the way to check to see what you have written to memory can be checked with `make flashdump`.
