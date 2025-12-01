#include <xc.h>
#include "main.h"
#include "clcd.h"

static unsigned int field = 0; 
extern unsigned int once = 1; 
extern unsigned char time[9]; 
unsigned char clock_reg[3];
extern unsigned char key;
extern unsigned int screen;
extern unsigned int gear;

void set_time(void) {
    
    unsigned char hour,min,sec;
    static unsigned int blink = 0,delay=0;
      
    clcd_print("HH:MM:SS            ", LINE1(0));
    clcd_print(time , LINE2(0));

    // Initialize time display from RTC once
    if (once == 1) {
        clock_reg[0] = read_ds1307(HOUR_ADDR);
        clock_reg[1] = read_ds1307(MIN_ADDR);
        clock_reg[2] = read_ds1307(SEC_ADDR);

        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03); 
        time[1] = '0' + (clock_reg[0] & 0x0F); 
        time[2] = ':';
        time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F); 
        time[4] = '0' + (clock_reg[1] & 0x0F); 
        time[5] = ':';
        time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F); 
        time[7] = '0' + (clock_reg[2] & 0x0F); 
        time[8] = '\0'; 
        once = 0; 
    }
    clcd_print("      ",LINE2(8));

    // Handle key presses for editing fields
    if (key == MK_SW2){ // Move to the next field (hours -> minutes -> seconds)
        field++;
        if (field > 2) {
            field= 0; // Wrap around to hours after seconds
        }
    }
    
    if (blink++ <= 500) {
        if (field == 0){   //blink sec
            clcd_putch(time[6], LINE2(6));
            clcd_putch(time[7], LINE2(7));
        } else if (field == 1){ // Blink minutes
            clcd_putch(time[3], LINE2(3));
            clcd_putch(time[4], LINE2(4));
        } else if (field == 2){ // Blink  hours
            clcd_putch(time[0], LINE2(0));
            clcd_putch(time[1], LINE2(1));
        }
    } else if (blink < 1000) {
        if (field == 0) {
            clcd_print("  ", LINE2(6));
        } else if (field == 1) {
            clcd_print("  ", LINE2(3));
        } else if (field == 2) {
            clcd_print("  ", LINE2(0));
        }
    } else if(blink==2000) {
        blink = 0; // Reset blink
    }


    if (key == MK_SW1){ // Increment the selected field
        if (field == 2){ // selecting the hour field
            time[1]++;
            if (time[1] > '9') {
                time[1] = '0';
                time[0]++;
            }
            if (time[0] == '2' && time[1] == '4'){ // Reset to 00 after 23
                time[0] = '0';
                time[1] = '0';
            }
        } else if (field== 1){ // selecting the min field
            time[4]++;
            if (time[4] > '9') {
                time[4] = '0';
                time[3]++;
            }
            if (time[3] == '6'){ // Reset to 00 after 59
                time[3] = '0';
            }
        } else if (field == 0){ //selecting the sec field
            time[7]++;
            if (time[7] > '9') {
                time[7] = '0';
                time[6]++;
            }
            if (time[6] == '6'){ // Reset to 00 after 59
                time[6] = '0';
            }
        }
    }
    
    hour=((time[0] - '0') << 4)| (time[1] - '0'); // Hours
    min=((time[3] - '0') << 4) | (time[4] - '0'); // Minutes
    sec=((time[6] - '0') << 4) | (time[7] - '0'); // Seconds

    // Save the updated time and exit
    if (key == MK_SW5) {
        write_ds1307(HOUR_ADDR,hour);
        write_ds1307(MIN_ADDR, min);
        write_ds1307(SEC_ADDR, sec); 
        
        for(unsigned int d=3000;d--;)
        clcd_print("Time updated",LINE2(0)); 
        //CLEAR_DISP_SCREEN; 
        gear=0;
        screen=DASH_BOARD;
        
    }
    if(key==MK_SW6){ //without save the time go to main_menu
        
        for(unsigned int d=3000;d--;)
        clcd_print("Time not updated",LINE2(0)); 
       // CLEAR_DISP_SCREEN;
        screen=MAIN_MENU;
    }
}
