#include <xc.h>
#include "main.h"

//extern variables defined in other source file
extern unsigned int screen;
extern unsigned char key;
extern unsigned int event_count;
extern unsigned int fix1;
unsigned int log=1;


void view_log(void){
    
    unsigned int k=0,address=0,i;
    static unsigned int v=0;
    unsigned char str[10][17];
    clcd_print("#VIEW_LOG       ",LINE1(0));
    
    
    if(fix1==1 && event_count!=0){
      // Loop through each event to fetch and format data from EEPROM
     while(k<event_count){
         i=0;
         str[k][i]=k+48;  //for index value
         i++;
         str[k][i]='.';  
         i++;
         while(i<16){  //i value upto 14
             if(i==10 || i==13){ //to insert  spaces
                str[k][i]=' ';
                i++;
             }else{
             str[k][i]=read_EEPROM(0X00+address); //read the data in specific address
             address++; //increment EEPROM address
             i++;
             }
         }
         str[k][i]='\0';
         k++;//move to next event
       } 
     fix1=0;  //reset the flag as 0
    }
    
     //if event counts will be 0 means display the no events occured
    if(event_count==0){
        clcd_print("NO EVENTS       ",LINE2(0)); 
    }
    else{
        if(key==MK_SW1){//key pressed means scroll up the events 
            if(v>0){
                v=v-1; //move to previous event
            }
        }
        if(key==MK_SW2){//key pressed means scroll down the events 
            if(v<event_count-1){
                v=v+1;//move to the next event
            }
        }
        //display the event in CLCD
        clcd_print(str[v],LINE2(0));
    }
}
