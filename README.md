# Computer Systems Engineering
These are projects for CSCE 317, Computer Systems Engineering at the University of South Carolina Columbia. The course is lab-based around embedded systems and thier application and development. All code in the course was bare metal code. 

### Execution
Download the repository, connect the board to a the compuer through its bridge, then run the following commands:
```bash
$ cd uart/
$ make clean && make burn
```
To interface with the board, run the below in a separate terminal:
```bash
$ picocom -b 57600 /dev/ttyUSB0 
``` 

#### The Hardware
The Atmel Atmega328 was used for all labs in the course--its [datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf) has more information on its specifications. In summary, it's:
* an 8-bit microcontroller that uses a RISC architecture,
* compatible with SPI, I2C, and USART,
* using the [AVR instruction set](https://gcc.gnu.org/wiki/avr-gcc).

## Credits
This course was taught by Dr. Jason. D. Bakos in the Spring of 2020; the Teaching assistant was Charles Daniels.
