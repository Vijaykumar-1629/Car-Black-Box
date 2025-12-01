#include "main.h"


void write_EEPROM(unsigned char address, unsigned char data)
{
	i2c_start();               //start the communication
	i2c_write(SLAVE_WRITE_EEPROM);  //check the unique id
	i2c_write(address);    //transmit the address
	i2c_write(data);     //transmit the data
	i2c_stop();        //stop the communication
    for(int wait = 3000;wait--;);
}

unsigned char read_EEPROM(unsigned char address)
{
	unsigned char data;

	i2c_start();                  //start the communication
	i2c_write(SLAVE_WRITE_EEPROM);     //check the unique id
	i2c_write(address);        //transmit the address
	i2c_rep_start();          //repeat the communication
	i2c_write(SLAVE_READ_EEPROM);   //transmit the address
	data = i2c_read();      //store the data into a data variable
	i2c_stop();            //stop the communication

	return data;         //return data
}
