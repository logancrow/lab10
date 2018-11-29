//Display.h
//Prototypes for functions that display Motor Speed on LCD
//Logan Crow and Samantha Flaim
//11/14/2018

#include <stdint.h>

//Initializes ST7735 and Sets up diplay to display motor speed
//inputs: none
//outputs: none
void DisplayInit(void);

//Displays current speed on ST7735
//inputs: current speed
//outputs: none
void DisplaySpeed(uint32_t P, uint32_t I);

//Initializes plot area
//inputs: title of plot, min/max values for x/y axes 
//outputs: none
void PlotInit(char *title, int32_t in_minX, int32_t in_maxX, int32_t in_minY, int32_t in_maxY);

//Plots one (x,y) point in the plot area
//inputs: x and y coordinates
//outputs: none	
void PlotPoint(int32_t x, int32_t iny);

//clears all points in the plot
//inputs: x and y coordinates
//outputs: none
void ClearPoint(int32_t x, int32_t y);
