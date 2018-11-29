//Controller.c
//functions that receive input from BLYNK and Tachometer
//and output to LCD, BLYNK and Motor
//Logan Crow and Samantha Flaim
//11/26/2018

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "controller.h"
#include "Display.h"
#include "TachIn.h"
#include "PWM.h"
#include "Timer0A.h"
#include "ST7735.h"

uint32_t rpm;
uint32_t speed;
uint32_t kp1;
uint32_t kp2;
uint32_t ki1;
uint32_t ki2;

int32_t P;
int32_t I = 0;
uint16_t U;
int32_t E;

//Initializes all inputs and outputs
//inputs: none
//outputs: none
void ControllerInit(){
	//TachInit();
	Timer0A_Init();
	PWM0B_Init(40000,1000);
	DisplayInit();
}

//Receives input from Blynk and outputs to motor
//inputs: TBD
//outputs: none
void MotorController(){
	//use rpm and speed values to create PI equeation for new duty
	//20,00 <= U <= 39,000
	//50% <= duty cycle <= 97.5%
	E = speed - rpm;
	P = (kp1 * E) / kp2;
	I = I + (ki1 * E) / ki2;
	U = P + I;
	if (U > 39000) {
		PWM0B_Duty(39000);
	}
	else if (U < 20000) {
		PWM0B_Duty(20000);
	}
	else {
		PWM0B_Duty(U);
	}
}

//converts rpm to speed
//inputs: rpm (global variable)
//outputs: speed
uint32_t RpmToSpeed() {
	double out = (double)(rpm * 3.14);
	return out;
}

//Receives input from Tachometer and outputs to LCD and BLYNK
//inputs: none
//outputs: none
void DisplayController(){
	DisplaySpeed(P, I);
}
