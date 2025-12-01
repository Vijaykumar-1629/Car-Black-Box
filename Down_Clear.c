#include <xc.h>
#include "main.h"

unsigned char ch=0;
extern unsigned char key;
extern unsigned int screen;
extern unsigned int event_count;
unsigned int fix2=1;

void down_log(void)
{  
   unsigned int c=0;
   unsigned int addres=0;
    // Display a message on the CLCD
   clcd_print("LOGS_ARE        ",LINE1(0));
   clcd_print("DOWNLOADING...  ",LINE2(0));
   
   if(fix2==1 && event_count!=0)
   {
       puts("INDEX    LOGS_TIME    EV    SP\n\r");
        // Iterate through each event
       while(c<event_count) {
           putch(c+48);  // Convert event index to ASCII
           putch('.');// Send a dot as a separator
           puts("       ");
           ch=0;         // Reset character index
           while(ch<14){
               if(ch==8 || ch==11){   // Insert spaces for alignment
                   puts("     ");
               }else{
               putch(read_EEPROM(0X00+addres)); // Read data from EEPROM 
               addres++;   // Increment EEPROM address
               }
               ch++;  // Increment character index
           }
           puts("\n\r");
           c++;   // Move to the next event
       }
      fix2=0;  // Reset the flag to indicate logs have been downloaded
   }
   if(event_count==0 && fix2==1){
       puts("NO EVENTS \n\r");   //no events are happend 
       fix2=0;
   }    
}


void clear_log(void) {
    
    clcd_print("LOGS_ARE CLEAR  ",LINE1(0));
    clcd_print("SUCCESSFULLY....",LINE2(0)); 
    
    //set the event count as 0 to reset the events
    event_count=0; 
}
