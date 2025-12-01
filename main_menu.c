#include <xc.h>
#include "main.h"

extern unsigned char key;
extern unsigned int screen;
extern unsigned int flag=2,flag1=2;

void main_menu(void)
{
    // Display the initial main menu with the first option selected
    if(flag==2){
        clcd_print("*",LINE1(0));
        clcd_print("view_log         ",LINE1(1));
        clcd_print(" ",LINE2(0));
        clcd_print("down_log         ",LINE2(1));
    } 
    if(key==MK_SW2){   // Navigate down through the menu options when MK_SW2 is pressed
        flag++;
        if(flag==3){
            clcd_print(" ",LINE1(0));
            clcd_print("view_log       ",LINE1(1));
            clcd_print("*",LINE2(0));
            clcd_print("down_log       ",LINE2(1));
        }
        else  if(flag==4){
            clcd_print(" ",LINE1(0));
            clcd_print("down_log        ",LINE1(1));
            clcd_print("*",LINE2(0));
            clcd_print("clear_log       ",LINE2(1)); 
        }
        else if(flag==5){
            clcd_print(" ",LINE1(0));
            clcd_print("clear_log       ",LINE1(1));
            clcd_print("*",LINE2(0));
            clcd_print("set_time        ",LINE2(1));
        }
    }                                         
    else if(key==MK_SW1){   // Navigate up through the menu options when MK_SW1 is pressed
       flag1++;         // Increment flag1 to move up       
        if(flag1==2){
            clcd_print(" ",LINE1(0));
            clcd_print("clear_log       ",LINE1(1));
            clcd_print("*",LINE2(0));
            clcd_print("set_time        ",LINE2(1));
        }
        else if(flag1==3){
            clcd_print("*",LINE1(0));
            clcd_print("clear_log       ",LINE1(1));
            clcd_print(" ",LINE2(0));
            clcd_print("set_time         ",LINE2(1));
        }
        else if(flag1==4){
            clcd_print("*",LINE1(0));
            clcd_print("down_log          ",LINE1(1));
            clcd_print(" ",LINE2(0));
            clcd_print("clear_log         ",LINE2(1));
        }
        else if(flag1==5){
            clcd_print("*",LINE1(0));
            clcd_print("view_log         ",LINE1(1));
            clcd_print(" ",LINE2(0));
            clcd_print("down_log         ",LINE2(1));
        }  
    }
    else if(flag>=6 && flag1>=6){   // Reset flags when they exceed the menu range
        flag=2;
        flag1=2;
    }
      
     // main menu  selection when MK_SW5 is pressed
    if(key==MK_SW5 && (flag==VIEW_LOG || flag1==SET_TIME)){
       screen=VIEW_LOG;  // Navigate to the view log screen
    }
    else if((flag==DOWN_LOG || flag1==CLEAR_LOG) && key==MK_SW5){
       screen=DOWN_LOG;  // Navigate to the down log screen
    }
    else if((flag==CLEAR_LOG || flag1==DOWN_LOG)&& key==MK_SW5){
       screen=CLEAR_LOG;  // Navigate to the clear log screen
    }
    else if((flag==SET_TIME || flag1==VIEW_LOG)&& key==MK_SW5){
       screen=SET_TIME;   // Navigate to the Set Time screen
    }
    
    // Return to the dashboard when MK_SW6 is pressed
    if(key==MK_SW6){
       screen=DASH_BOARD;
    }
}
