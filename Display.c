//Display.c
//functions that display Motor Speed on LCD
//Logan Crow and Samantha Flaim
//11/26/2018

#include <stdint.h>
#include "Display.h"
#include "ST7735.h"
#include "Controller.h"
#include "fixed.h"

uint32_t j;
int32_t saveY[127];

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
	PlotInit("Speed vs. Time:", 0, 127, 400, 2000);
	j = 0;
	for (int i = 0; i < 127; i++) {
		saveY[i] = 100;
	}
}

//Displays current speed on ST7735
//inputs: current speed
//outputs: none
void DisplaySpeed(uint32_t P, uint32_t I){
	ST7735_SetCursor(6,0);
	ST7735_OutUDec(rpm);
	ST7735_OutString("         ");
	ST7735_SetCursor(4,1);
	ST7735_OutUDec(P);
	ST7735_OutString("       ");
	ST7735_SetCursor(4,2);
	ST7735_OutUDec(I);
	ST7735_OutString("      ");
	
	if (j < 127) {
		ClearPoint(j, saveY[j]);
		PlotPoint(j, rpm);		
	}
	else {
		j = 0;
	}
	j++;
}

int16_t minX, maxX, minY, maxY;

/**************ST7735_XYplotInit***************
 Specify the X and Y axes for an x-y scatter plot
 Draw the title and clear the plot area
 Inputs:  title  ASCII string to label the plot, null-termination
          minX   smallest X data value allowed, resolution= 0.001
          maxX   largest X data value allowed, resolution= 0.001
          minY   smallest Y data value allowed, resolution= 0.001
          maxY   largest Y data value allowed, resolution= 0.001
 Outputs: none
 assumes minX < maxX, and miny < maxY
*/
void PlotInit(char *title, int32_t in_minX, int32_t in_maxX, int32_t in_minY, int32_t in_maxY) {
	//ClearPlot();
	ST7735_DrawString(0, 3, title, ST7735_WHITE); 
	minX = in_minX;
	maxX = in_maxX;
	minY = in_minY;
	maxY = in_maxY;
}

void PlotPoint(int32_t x, int32_t iny) {
	uint16_t y = 42 + (117 * (maxY - iny) / (maxY - minY));
	saveY[j] = y;
	ST7735_DrawPixel(x, y, ST7735_BLUE);
	ST7735_DrawPixel(x+1, y, ST7735_BLUE);
	ST7735_DrawPixel(x, y+1, ST7735_BLUE);
	ST7735_DrawPixel(x+1, y+1, ST7735_BLUE);
	ST7735_DrawPixel(x-1, y, ST7735_BLUE);
	ST7735_DrawPixel(x, y-1, ST7735_BLUE);
	ST7735_DrawPixel(x-1, y-1, ST7735_BLUE);
	ST7735_DrawPixel(x+1, y-1, ST7735_BLUE);
	ST7735_DrawPixel(x-1, y+1, ST7735_BLUE);
}

void ClearPoint(int32_t x, int32_t y) {
	ST7735_DrawPixel(x,y,ST7735_BLACK);
	ST7735_DrawPixel(x+1,y,ST7735_BLACK);
	ST7735_DrawPixel(x,y+1,ST7735_BLACK);
	ST7735_DrawPixel(x+1,y+1,ST7735_BLACK);
	ST7735_DrawPixel(x-1,y,ST7735_BLACK);
	ST7735_DrawPixel(x,y-1,ST7735_BLACK);
	ST7735_DrawPixel(x-1,y-1,ST7735_BLACK);
	ST7735_DrawPixel(x+1,y-1,ST7735_BLACK);
	ST7735_DrawPixel(x-1,y+1,ST7735_BLACK);
}

