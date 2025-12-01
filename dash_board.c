#include <xc.h>
#include "main.h"

unsigned int delay = 0;
extern unsigned int gear;
unsigned int a,b;
unsigned int  adc_reg;
unsigned char store[3]; //array to store the gear events
unsigned char speed[3];//array to store spped
unsigned char clock_reg[3];  
unsigned char time[9]; //array to store the time
extern unsigned char key;

void display_gear(unsigned char gear) { 
    if (gear == 7) { 
        clcd_print("  GN", LINE2(8));    // Display 'GN' for gear neutral
        store[0]='G';
        store[1]='N';      
    } else if (gear == 6) {  
        clcd_print("  GR", LINE2(8));    // Display 'GR' for gear reverse
        store[0]='G';
        store[1]='R';
    } else if (gear < 6) { 
        clcd_print("  G", LINE2(8));
        clcd_putch(gear + 48, LINE2(11)); // Display gear 1-5 for gear neutral
        store[0]='G';
        store[1]=gear+48;
    }
    store[2]='\0';
    event_store(time,store,speed);  //call the event store fun
}
static void get_time(void){
     // Read hours, minutes, and seconds from RTC
    clock_reg[0] = read_ds1307(HOUR_ADDR);
    clock_reg[1] = read_ds1307(MIN_ADDR);
    clock_reg[2] = read_ds1307(SEC_ADDR);

    if (clock_reg[0] & 0x40)  //bit 6 set as 1 for 12 hrs
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    else  //bit 6 set as 0 for 24 hrs
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    time[2] = ':';
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);  //storeing the tens place of min value in time string
    time[4] = '0' + (clock_reg[1] & 0x0F);   //storeing the ones place of min value in time string
    time[5] = ':';
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F); //tens place of seconds
    time[7] = '0' + (clock_reg[2] & 0x0F); //ones place of seconds
    time[8] = '\0';
}
    
void display_time(void){
	clcd_print(time, LINE2(0));  //printing the time in clcd by sending the time string address in line2
}

void dash_board(void) {   
    clcd_print("  TIME    EV  SP", LINE1(0));  // Display "TIME EVENT SPEED" labels
 
    get_time();       // get the  current time
    display_time();   // Display the current time
    
    clcd_print("  ",LINE2(8)); //space between time and event
       
    // Calculate and display car speed
    adc_reg = (read_adc(CHANNEL4)) / 10.33;
    a = (adc_reg / 10);
    b = (adc_reg % 10);
    clcd_putch(a + 48, LINE2(14));// Display tens place
    clcd_putch(b + 48, LINE2(15));// Display ones place
    
    speed[0]=a+48;
    speed[1]=b+48;
    speed[2]='\0';
    
    // Handle event based on key input
    if (key == MK_SW1 && gear <= 7) {  //increase gear
        gear++;
        display_gear(gear);
    }
    else if (key == MK_SW2 && gear > 1) { //decrease the gear
        gear--;
        display_gear(gear);
    }
    else if (key == MK_SW3) {   // crash  will display
        clcd_print("C_", LINE2(10));    // Display 'C_' for crash
        store[0]='C';
        store[1]='_';
        store[2]='\0'; 
        event_store(time,store,speed);  //call the event store fun
    } else if(gear == 0) // Car is ON but no gear
    {
        clcd_print("ON", LINE2(10));
    }
}
