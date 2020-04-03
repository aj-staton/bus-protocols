# Microcontrollers
These are projects for CSCE 317, Computer Systems Engineering at the University of South Carolina, Columbia. The course is lab-based around embedded systems and thier communication protocols.

During my time in this course, the unfortunate events of COVID-19 occured globally. This forced instruction to be moved online. 
The [UART](#UART) project was completed in-person, with the Atmel Atmega 328p. The other projects, in the "virtual classroom," were written locally and them simulated/tested with SystemVerilog. 

## UART
Wrote a software-defined implementation of UART communication using GPIO pins on the AVR-based Atmel Atmega 328p microcontroller.

## Accelerometer
Communicated via SPI between the 328p and an LIS3DH accelerometer. This project ended, and is __incomplete__, due to the tragic COVID-19 outbreak. I kept the materials so I can go back and finish it as a personal project when I return to campus in the next semester.   

## SPI
Wrote a software-defined implementation of SPI comunication which was tested by simulations in Verilator that created `*.vcd` (value change dump) files. These files were then sent to Sigrok to read.

### Credits
This course was taught by Dr. Jason. D. Bakos in the Spring of 2020; the Teaching Assistant was Charles Daniels.
