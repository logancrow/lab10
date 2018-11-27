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
