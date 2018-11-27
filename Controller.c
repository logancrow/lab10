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

uint32_t rpm;
uint32_t speed;

double P;
double I = 0.5;
double U;
double kp1 = 50;
double kp2 = 50;
double ki1 = 200;
double ki2 = 70;
double E = 500; // = Tau

//Initializes all inputs and outputs
//inputs: none
//outputs: none
void ControllerInit(){
	DisplayInit();
	//TachInit();
	Timer0A_Init();
	PWM0A_Init(4000,0);
}

//Receives input from Blynk and outputs to motor
//inputs: TBD
//outputs: none
void MotorController(){
	//use rpm and speed values to create PI equeation for new duty
	P = (kp1 * E) / kp2;
	I = I + (ki1 * E) / ki2;
	U = P + I;
	PWM0A_Duty(U); 
}

//converts rpm to speed
//inputs: rpm (global variable)
//outputs: speed
uint32_t RpmToSpeed() {
	double speed = (double)(rpm * 3.14);
	return speed;
}

//Receives input from Tachometer and outputs to LCD and BLYNK
//inputs: none
//outputs: none
void DisplayController(){
	DisplaySpeed(speed, P, I);
}
