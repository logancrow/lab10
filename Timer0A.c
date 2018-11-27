// Timer0A.c
// Runs on LM4F120/TM4C123
// Use Timer0A in periodic mode to request interrupts at a particular
// period.
// Daniel Valvano
// September 11, 2013

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers"
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2015
   Volume 1, Program 9.8

  "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014
   Volume 2, Program 7.5, example 7.6

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
#include <stdint.h>
#include <time.h>
#include "..//inc//tm4c123gh6pm.h"
#include "controller.h"
#include "Timer0A.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

clock_t start; //time of last revolution
uint32_t count; //count of number of PB0 +edges
// 8 (0...1...2...3...4...5...6...7) --> 1 revolution

// ***************** Timer0A_Init ****************
// Activate TIMER0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq), 32 bits
// Outputs: none
void Timer0A_Init(){
	volatile uint32_t delay;
	DisableInterrupts();
	start = clock();
	count = 0;
  SYSCTL_RCGCTIMER_R |= 0x01; // activate TIMER0
	SYSCTL_RCGCTIMER_R |= 0x02; 			// activate GPIO Port B
	delay = SYSCTL_RCGCTIMER_R;       // allow time to finish activating
	GPIO_PORTB_DIR_R &= ~0x01;				// PB0 = input
	GPIO_PORTB_AFSEL_R |= 0x01;				// enable alt function on PB0
	GPIO_PORTB_DEN_R |= 0x01;					// configure PB0 as T0CCP0
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0x0F0FFFFFF) + 0x07000000;
  TIMER0_CTL_R &= ~0x01;    			  // disable TIMER0A during setup
  TIMER0_CFG_R = 0;					        // configure for 32-bit capture mode
  TIMER0_TAMR_R = 0x07;             // configure for rising edge event
  TIMER0_CTL_R &= ~0x0C;            // rising edge
	TIMER0_TAILR_R = 0x0FFFF;      // start value
  TIMER0_TAPR_R = 0xFF;             // activate prescale, creating 24-bit
  TIMER0_IMR_R = 0x04;        // enable capture match interrupt
  TIMER0_ICR_R = 0x04;        // clear TIMER0A capture match flag
  TIMER0_CTL_R |= 0x01;             // timer0A 24-bit, +edge, interrupts
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; // priority 2
  NVIC_EN0_R = 1<<19;           // enable IRQ 19 in NVIC
  TIMER0_CTL_R = 0x01;    // enable TIMER0A
}

void Timer0A_Handler(void){
	TIMER0_ICR_R = 0x04;      // acknowledge timer0A
	count++;
	if (count == 7) {
		rpm = (uint32_t)((double)(60 / ((double)(clock() - start) / CLOCKS_PER_SEC)));
		count = 0;
		start = clock();
	}
}
