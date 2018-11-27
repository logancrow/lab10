//TachIn.c
//functions that read input from Tachometer
//Logan Crow and Samantha Flaim
//11/26/2018

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "TachIn.h"

//Initializes PB0 to be input for tachometer
//inputs: none
//outputs: none
void TachInit(){
	volatile uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x00000002;  // 1) activate clock for Port B
  delay = SYSCTL_RCGCGPIO_R;        // allow time for clock to start
  GPIO_PORTB_AMSEL_R &=~ 0x01;        // 3) disable analog on PB0
  GPIO_PORTB_PCTL_R &=~ 0x00000001;   // 4) PCTL GPIO on PB0
  GPIO_PORTB_DIR_R &=~ 0x01;          // 5) PB0 in
  GPIO_PORTB_AFSEL_R &=~ 0x01;        // 6) disable alt funct on PB0
  GPIO_PORTB_DEN_R |= 0x01;          // 7) enable digital I/O on PB0
}

//captures input from tachometer
//inputs: none
//outputs: value from tachometer
uint32_t TachCapture(){
	uint32_t cur_rpm;
	return cur_rpm;
}
