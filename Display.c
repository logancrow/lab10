//Display.c
//functions that display Motor Speed on LCD
//Logan Crow and Samantha Flaim
//11/26/2018

#include <stdint.h>
#include "Display.h"
#include "ST7735.h"

//Initializes ST7735 and Sets up diplay to display motor speed
//inputs: none
//outputs: none
void DisplayInit(){
	ST7735_InitR(INITR_REDTAB);
	ST7735_FillScreen(ST7735_BLACK);
}

//Displays current speed on ST7735
//inputs: current speed
//outputs: none
void DisplaySpeed(uint32_t cur_rpm){
	ST7735_SetCursor(0,0);
	ST7735_OutUDec(cur_rpm);
}
