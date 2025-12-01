#include <xc.h>
#include "main.h"

unsigned int event_count=0;

void event_store(char time[9],char str[2],char speed[2])
{
    unsigned int i=0,base_adr;
    unsigned char ch;
    static unsigned int addr=0;
    
    if(event_count<MAX_EVENTS)
    {   
        //write the new speed string to EEPROM
        while(time[i]!='\0'){
            write_EEPROM(0X00+addr,time[i++]);//store each character
            addr++;
        }
        i=0; //reset the i value
        //write the new speed string to EEPROM
        while(str[i]!='\0'){
            write_EEPROM(0X00+addr,str[i++]);//store each character
            addr++;
        }       
        i=0; //reset the i value
        //write the new speed string to EEPROM
        while(speed[i]!='\0'){
            write_EEPROM(0X00+addr,speed[i++]);//store each character
            addr++;
        }
        event_count++; //increment event count
    } 
      //check event count is greater than or equal to 10 events    
    else if(event_count>=MAX_EVENTS){ 
        for(base_adr=12; base_adr<RANGE; base_adr++){
            ch= read_EEPROM(0X00+base_adr);
            write_EEPROM(0X00+addr,ch);
            addr++;
        }
        i=0; //reset the i value
        //write the new time string to EEPROM
        while (time[i] != '\0'){
            write_EEPROM(0X00+addr, time[i]);//store each character
            addr++;
            i++;
        }
        i = 0; //reset the i value
        //write the new event  string to EEPROM
        while (str[i] != '\0'){
            write_EEPROM(0X00+addr, str[i]);  //store each character
            addr++;
            i++;
        }
        i = 0; //reset the i value
        //write the new speed string to EEPROM
        while (speed[i] != '\0'){
            write_EEPROM(0X00+addr, speed[i]); //store each character
            addr++;
            i++;
        }
        if(addr==RANGE)  //address will reach the 120 range
        {
           addr=0; //set the address is 0
        }
    }
}
