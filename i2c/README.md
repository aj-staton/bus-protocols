# Inter-Integrated Circuit
I2C was used to read sensor data and write it to an page in flash memory.

In this project, I was responsible for implementing a read function for I2C. In summary, I:
 * Waited for SCL's start edge,
 * Read the MSB-order 7-bit address on SDA from the master,
 * acknowledged the address if it was correct,
 * Read the next 8-bits on SDA from the master, 
 * send the acknowledgement, and; 
 * waited for the stop edge to end the transaction.
