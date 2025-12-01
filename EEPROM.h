#ifndef EEPROM_H
#define EEPROM_H

#define SLAVE_READ_EEPROM		0xA1  //unique id 1111 0001 8th bit for read
#define SLAVE_WRITE_EEPROM  	0xA0   //unique id 1111 0000 8th bit for write 

void write_EEPROM(unsigned char address1,  unsigned char data);    //write function by using address and data
unsigned char read_EEPROM(unsigned char address1);   //read function by using address

#endif
