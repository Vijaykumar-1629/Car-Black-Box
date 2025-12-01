#ifndef MAIN_H
#define MAIN_H

#include "clcd.h"
#include "adc.h"
#include "ds1307.h"
#include "eeprom.h"
#include "i2c.h"
#include "matrix_keypad.h"
#include "uart.h"


#define DASH_BOARD   0  //screen for dispaly dash_board
#define MAIN_MENU    1  //mode for dispaly main_menu

#define VIEW_LOG     2   //mode for dispaly view_log
#define DOWN_LOG     3   //mode for dispaly down_log
#define CLEAR_LOG    4   //mode for dispaly clear_log
#define SET_TIME     5   //mode for dispaly set_time

#define MAX_EVENTS   10  //max events to store in eeprom
#define RANGE        120 //eeprom memory range for store data

#define SEC_ADDR		0x00  //address for storing seconds
#define MIN_ADDR		0x01  //address for storing minutes
#define HOUR_ADDR		0x02  //address for storing hours

//for dash board 
void display_gear(unsigned char gear);
void dash_board(void);
static void get_time(void);
void display_time(void);
void event_store(char time[8],char str[2],char speed[2]);

//for main menu
void main_menu(void);
void view_log(void);
void down_log(void);
void clear_log(void);
void set_time(void);

#endif
