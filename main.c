#include <xc.h>
#include "main.h"

unsigned char key;
unsigned int screen = 0;
unsigned int fix1=1;
unsigned int fix2=1;
unsigned int once;
unsigned int field;
unsigned int flag=2,flag1=2;
unsigned int gear=0;
extern unsigned int event_count;

void init_config(void) {

    init_clcd();  // Initialize the CLCD 
     
    init_i2c();   // Initialize the I2C
    
    init_uart();  // Initialize the UART
    
    init_ds1307();  // Initialize the RTC
    
    init_matrix_keypad();  // Initialize the matrix keypad
      
    init_adc();   // Initialize the ADC
}

void main(void) {

    init_config();

    while (1) {
        
        key = read_switches(STATE_CHANGE);
         
         // Main dashboard screen, handling user input and screen 
        if (screen == DASH_BOARD) {
             
            
           // Call the dash_board function to display the dashboard
            dash_board();
            
            // When the user presses MK_SW5
            if (key == MK_SW5) {
                
                screen = MAIN_MENU;// Set the screen to MAIN_MENU
            }
        }
        else if (screen == MAIN_MENU) {  // Main menu screen, handles menu options
           
            main_menu();
            // When the user presses MK_SW6, return to the dashboard
            if(key==MK_SW6)
            {
               // gear=1;
                event_count=0;
                screen=DASH_BOARD;// Set the screen to DASH_BOARD
            }
            
        }
        else if(screen==VIEW_LOG)    // View log screen, displays stored logs to the user
        {
            view_log();
            // When the user presses MK_SW6, return to the dashboard
            if(key==MK_SW6)
            {
                flag=2;
                screen = MAIN_MENU;// Set the screen to MAIN_MENU
            }
        }
        else if(screen==DOWN_LOG)  // Download log screen, allows the user to download logs
        {
            down_log();
            // When the user presses MK_SW6, return to the dashboard
            if(key==MK_SW6)
            {
                fix2=1;
                flag=2;
                screen=MAIN_MENU; // Set the screen to MAIN_MENU
            }
        }
        else if(screen==CLEAR_LOG )   // Clear log screen, provides an option to clear stored logs
        {
            clear_log();
            // When the user presses MK_SW6, return to the dashboard
           if(key==MK_SW6)
            {
               flag=2;
                screen =MAIN_MENU;// Set the screen to MAIN_MENU
            }
        }
        else if(screen==SET_TIME)   // Set time screen, allows the user to set the system time
        {
            flag=2;
            set_time();
        }
    }
}
