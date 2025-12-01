#include "main.h"

void init_ds1307(void)
{
	unsigned char dummy;

	/* Setting the CH bit of the RTC to Stop the Clock */
	dummy = read_ds1307(SEC_ADDR);
	write_ds1307(SEC_ADDR, dummy | 0x80); 

	/* Seting 12 Hr Format */
	dummy = read_ds1307(HOUR_ADDR);
	write_ds1307(HOUR_ADDR, dummy | 0x40); 

	/* 
	 * Control Register of DS1307
	 * Bit 7 - OUT
	 * Bit 6 - 0
	 * Bit 5 - OSF
	 * Bit 4 - SQWE
	 * Bit 3 - 0
	 * Bit 2 - 0
	 * Bit 1 - RS1
	 * Bit 0 - RS0
	 * 
	 * Seting RS0 and RS1 as 11 to achive SQW out at 32.768 KHz
	 */ 
	write_ds1307(CNTL_ADDR, 0x93); 

	/* Clearing the CH bit of the RTC to Start the Clock */
	dummy = read_ds1307(SEC_ADDR);
	write_ds1307(SEC_ADDR, dummy & 0x7F); 

}

void write_ds1307(unsigned char address, unsigned char data)
{
	i2c_start();               //start the communication
	i2c_write(SLAVE_WRITE);  //check the unique id
	i2c_write(address);    //transmit the address
	i2c_write(data);     //transmit the data
	i2c_stop();        //stop the communication
}

unsigned char read_ds1307(unsigned char address)
{
	unsigned char data;

	i2c_start();                 //start the communication
	i2c_write(SLAVE_WRITE);     //check the unique id
	i2c_write(address);        //transmit the address
	i2c_rep_start();          //repeat the communication
	i2c_write(SLAVE_READ);   //transmit the address
	data = i2c_read();      //store the data into a data variable
	i2c_stop();            //stop the communication

	return data;         //return data
}
