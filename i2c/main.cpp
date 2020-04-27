/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

/* Used and modified by Austin Staton for CSCE317
 * Project `lab_virti2csingle`
 */

#include "support.h"

#define	TRANS_SUCCESS		0
#define TRANS_ADDRESS_NACK	1
#define TRANS_DATA_NACK		2
#define TRANS_NOTTARGET		3

#define SLAVE_ADDR		0x7A

typedef struct {
	int address;
	int data;
	int status;
	int cycle_width;
	int readwrite;
} I2C_TRANSACT;

#define		WAIT_FOR_START_BIT(s)			{\
											int start;\
											do {\
												int scl,sda,prev_scl,prev_sda;\
												prev_sda = read_io(s,IO_SDA);\
												prev_scl = read_io(s,IO_SCL);\
												delay_cycles(s,1);\
												sda = read_io(s,IO_SDA);\
												scl = read_io(s,IO_SCL);\
												start = (scl==1) && (prev_scl==1) && (prev_sda==1) && (sda==0);\
											} while (!start);\
											}

#define		WAIT_FOR_RISING_SCL(s)			{\
											int rising_edge;\
											do {\
												int scl,prev_scl;\
												prev_scl = read_io(s,IO_SCL);\
												delay_cycles(s,1);\
												scl = read_io(s,IO_SCL);\
												rising_edge = (prev_scl==0) && (scl==1);\
											} while (!rising_edge);\
											}
												
#define		WAIT_FOR_FALLING_SCL(s)			{\
											int falling_edge;\
											do {\
												int scl,prev_scl;\
												prev_scl = read_io(s,IO_SCL);\
												delay_cycles(s,1);\
												scl = read_io(s,IO_SCL);\
												falling_edge = (prev_scl==1) && (scl==0);\
											} while (!falling_edge);\
											}

#define		WAIT_FOR_STOP_BIT(s)			{\
											int stop;\
											do {\
												int scl,sda,prev_scl,prev_sda;\
												prev_sda = read_io(s,IO_SDA);\
												prev_scl = read_io(s,IO_SCL);\
												delay_cycles(s,1);\
												sda = read_io(s,IO_SDA);\
												scl = read_io(s,IO_SCL);\
												stop = (scl==1) && (prev_scl==1) && (prev_sda==0) && (sda==1);\
											} while (!stop);\
											}
											
											
/*
 * \brief accept a read or write operation as a slave on the I2C bus
 *
 * To use, the caller must first allocate an I2C_TRANSACT object
 * but all of its members will serve as outputs for this function:
 *
 * I2C_TRANSACT::address - the address requested by the master
 *   NOTE: this function must check if the requested address matches
 *   the "assigned address" of the peripheral calling this function
 *   (i.e. the address of your code).  This value should be 0x7A.
 * I2C__TRANSACT::cycle_width - you do not need to set this value.
 * I2C_TRANSACT::readwrite - you only need to implement slave write
 *   operations for this lab, so you do not need to write this value
 * I2C_TRANSACT::data - the written data should be placed in here.
 */
int slave_i2c(simulation_state *s,I2C_TRANSACT *mytrans) {
	/* Address Phase */
  WAIT_FOR_START_BIT(s);
	// Get Address-- 7 bits in I2C
  int addr = 0;
  for (int i = 6; i >= 0; --i) {
    WAIT_FOR_RISING_SCL(s);
    addr |= (read_io(s, IO_SDA) << i);
  }
  // Get R/W Bit
  WAIT_FOR_RISING_SCL(s);
	// Update the transaction.
  mytrans->readwrite = (read_io(s, IO_SDA));
  mytrans->address = addr;
	// Check if the address is correct; send acknowledgement.
  if (addr == SLAVE_ADDR) {
    WAIT_FOR_RISING_SCL(s);
    write_io(s, IO_SDA, 0);
    mytrans->status = TRANS_SUCCESS;
  } else {
    mytrans->status = TRANS_ADDRESS_NACK;
    return 1;
	}

  WAIT_FOR_FALLING_SCL(s);
  
  /* Data Phase */
	int data = 0;
  for (int i = 7; i >= 0; --i) {
    WAIT_FOR_RISING_SCL(s);
    data |= (read_io(s, IO_SDA) << i);
  }
	// Send the ACK
  WAIT_FOR_RISING_SCL(s);
  write_io(s, IO_SDA, 0);
  mytrans->status = TRANS_SUCCESS;
  // End transaction.
  WAIT_FOR_STOP_BIT(s);
	// Update data. 
  mytrans->data = data;
  mytrans->status = TRANS_SUCCESS;
}

/*
 * \brief perform a master read or write operation on the I2C bus
 *
 * To use, the caller must first allocate an I2C_TRANSACT object
 * and assign the following members:
 *
 * I2C_TRANSACT::address - the address for which to read or write
 * I2C_TRANSACT::cycle_width - the number of core cycles that comprise
 *   an I2C cycle
 * I2C_TRANSACT::readwrite - set to 1 for read and 0 for write
 * I2C_TRANSACT::data - set only for writes, since this will be
 *   return data for a read
 *
 * The following members will be set upon return:
 * I2C_TRANSACT::data - returned read data, only for reads
 * I2C_TRANSACT::status - will be set to TRANS_SUCCESS on success,
 *   TRANS_ADDRESS_NACK if the targeted slave issues a NACK on
 *   the address phase or the data phase for a write, or
 *   TRANS_DATA_NACK if the targeted slave issues on NAK on the
 *   data phase of a write operation.  TRANS_NOTTARGET is only
 *   used for slave_i2c().
 */
int master_i2c (simulation_state *s,I2C_TRANSACT *mytrans) {
	int cycle_width = mytrans->cycle_width;

	//initialize
	mytrans->status=TRANS_SUCCESS;
	
	// make sure SDa and SCL start as 1 (probably not needed)
	write_io(s,IO_SDA,1);
	write_io(s,IO_SCL,1);
	delay_cycles(s,cycle_width/2);

	// start bit 
	write_io(s,IO_SDA,0);
	delay_cycles(s,cycle_width/2);
	write_io(s,IO_SCL,0);
	delay_cycles(s,cycle_width/2);

	// write address
	for (int i=0;i<7;i++) {
		write_io(s,IO_SDA,(mytrans->address >> (6-i))&1);
		delay_cycles(s,cycle_width/2);
		write_io(s,IO_SCL,1);
		delay_cycles(s,cycle_width/2);
		write_io(s,IO_SCL,0);
		delay_cycles(s,cycle_width/2);
	}

	write_io(s,IO_SDA,mytrans->readwrite); // R/W bit (0 to write)
	delay_cycles(s,cycle_width/2);
	write_io(s,IO_SCL,1); // clock pulse
	delay_cycles(s,cycle_width/2);
	write_io(s,IO_SCL,0);
	delay_cycles(s,cycle_width/2);

	write_io(s,IO_SDA,1); // blank bit (sda_o should acknowledge here -- set to 1 to allow for other end to pull down)
	delay_cycles(s,cycle_width/2);
	write_io(s,IO_SCL,1); // clock pulse
	delay_cycles(s,cycle_width/2);
	write_io(s,IO_SCL,0);
	int ret = read_io(s,IO_SDA);
	delay_cycles(s,cycle_width/2);

	if (ret==1) {
		mytrans->status=TRANS_ADDRESS_NACK;
	}

	if (mytrans->status==TRANS_SUCCESS) {

		// write data
		// initialize SDA
		write_io(s,IO_SDA,1);
		if (mytrans->readwrite==1) mytrans->data=0;

		for (int i=0;i<8;i++) {
			if (mytrans->readwrite==0) write_io(s,IO_SDA,(mytrans->data >> (7-i)) & 1);
			delay_cycles(s,cycle_width/2);
			write_io(s,IO_SCL,1);
			delay_cycles(s,cycle_width/2);
			write_io(s,IO_SCL,0);
			if (mytrans->readwrite==1) mytrans->data |= read_io(s,IO_SDA) << (7-i);
			delay_cycles(s,cycle_width/2);
		}

		if (mytrans->readwrite==1)
			write_io(s,IO_SDA,1); // blank bit (sda_o should acknowledge here)
		else
			write_io(s,IO_SDA,0);
		delay_cycles(s,cycle_width/2);
		write_io(s,IO_SCL,1); // clock pulse
		delay_cycles(s,cycle_width/2);
		write_io(s,IO_SCL,0);
		if (mytrans->readwrite==0 && read_io(s,IO_SDA)==1) {
			mytrans->status=TRANS_DATA_NACK;
		}
		delay_cycles(s,cycle_width/2);
	}

	// prepare for stop bit
	write_io(s,IO_SDA,0);
	write_io(s,IO_SCL,0);
	delay_cycles(s,cycle_width/2);

	// stop bit
	write_io(s,IO_SCL,1); // end transmission
	delay_cycles(s,cycle_width/2);
	write_io(s,IO_SDA,1);
	delay_cycles(s,cycle_width/2);

	if (mytrans->status==TRANS_SUCCESS) return 1;
	return 0;
}

int main(int argc, char **argv) {
	int i,j;

	simulation_state* s = initialize_simulation(argc, argv);

	// set I2C cycle width for master transactions
	// NOTE: this does not apply to slave transactions, since
	// this is controlled by the master
	// NOTE: at 4 cycles per I2C, we expect each I2C transaction
	// to take 4 * 19 = 76 cycles.  currently, the i2c master
	// will initiate every 100 cycles after the read from NPAGE
	// on the slave
	I2C_TRANSACT mytrans;
	mytrans.cycle_width=4;

	// step 1:  read WHO_AM_I from storage device
	// read I2C address 0x1C
	mytrans.address = 0x1C;
	mytrans.readwrite = 1; // read
	master_i2c(s,&mytrans);
	printf ("reading WHO_AM_I (0x1C) from storage device, returned 0x%02X\n",mytrans.data);

	// step 2: determine capacity of the storage device (NPAGE)
	// read I2C address 0x1D
	mytrans.address = 0x1D;
	mytrans.readwrite = 1; // read
	master_i2c(s,&mytrans);
	printf ("reading NPAGE (0x1D) from storage device, returned %d\n",mytrans.data);

	int num_pages = mytrans.data;
	
	// reading NPAGE will trigger the i2c master, so we better get ready
	for (i=0;i<num_pages;i++) {
	
		printf("\nSTARTING PAGE %d\n",i);

		// read number of sensor readings
		slave_i2c(s,&mytrans);

		int number_of_sensor_readings = mytrans.data;
		printf ("number of sensor readings = %d\n",mytrans.data);

		// allocate memory for the sensor readings
		int *sensor_data = (int *)malloc(sizeof(int)*number_of_sensor_readings);

		// write page number to storage
		mytrans.address = 0x1B;
		mytrans.readwrite = 0; // write
		mytrans.data = i;
		master_i2c(s,&mytrans);
		printf ("writing PAGESEL (0x20) to storage device\n");
		
		// receive each reading and then save it
		for (j=0;j<number_of_sensor_readings;j++) {
			// read sensor value
			slave_i2c(s,&mytrans);

			int number_of_sensor_readings = mytrans.data;
			printf ("sensor reading %d = 0x%02X\n",j,mytrans.data);

			sensor_data[j]=mytrans.data;
			
			// write sensor reading to storage
			mytrans.address = 0x1F;
			mytrans.readwrite = 0; // write
			// data will remain the same
			master_i2c(s,&mytrans);
			printf ("writing DATA (0x1F) to storage device\n");
		}
		
		free(sensor_data);
	}

}

