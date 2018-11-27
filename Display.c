//Display.c
//functions that display Motor Speed on LCD
//Logan Crow and Samantha Flaim
//11/26/2018

#include <stdint.h>
#include "Display.h"
#include "ST7735.h"
#include "Controller.h"

uint32_t j;

//Initializes ST7735 and Sets up diplay to display motor speed
//inputs: none
//outputs: none
void DisplayInit(){
	ST7735_InitR(INITR_REDTAB);
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_SetCursor(0,0);
	ST7735_OutString("RPM = ");
	ST7735_SetCursor(0,1);
	ST7735_OutString("P = ");
	ST7735_SetCursor(0,2);
	ST7735_OutString("I = ");
	j = 0;
}

//Displays current speed on ST7735
//inputs: current speed
//outputs: none
void DisplaySpeed(uint32_t P, uint32_t I){
	ST7735_SetCursor(4,0);
	ST7735_OutUDec(rpm);
	ST7735_SetCursor(3,1);
	ST7735_OutUDec(P);
	ST7735_SetCursor(3,2);
	ST7735_OutUDec(I);
	
	ST7735_PlotPoint(RpmToSpeed());
	if (j < 100) {
		ST7735_PlotNextErase();
	}
	else {
		j = 0;
	}
	j++;
}
