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

uint32_t rpm;
uint32_t speed;

//Initializes all inputs and outputs
//inputs: none
//outputs: none
void ControllerInit(){
	DisplayInit();
	TachInit();
	PWM0A_Init(4000,0);
}

//Receives input from Blynk and outputs to motor
//inputs: TBD
//outputs: none
void MotorController(){
	//use rpm and speed values to create PI equeation for new duty
	//PWM0A_Duty(duty); 
}

//Receives input from Tachometer and outputs to LCD and BLYNK
//inputs: none
//outputs: none
void DisplayController(){
	DisplaySpeed(rpm);
}
