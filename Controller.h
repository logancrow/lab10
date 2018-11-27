//Controller.h
//Prototypes for functions that receive input from BLYNK and Tachometer
//and output to LCD, BLYNK and Motor
//Logan Crow and Samantha Flaim
//11/14/2018

#include <stdint.h>

//Initializes all inputs and outputs
//inputs: none
//outputs: none
void ControllerInit(void);

//Receives input from Blynk and outputs to motor
//inputs: TBD
//outputs: none
void MotorController(void);

//Receives input from Tachometer and outputs to LCD and BLYNK
//inputs: none
//outputs: none
void DisplayController(void);

//converts rpm to speed
//inputs: rpm (global variable)
//outputs: speed
uint32_t RpmToSpeed(void);

extern uint32_t rpm;
extern uint32_t speed;
extern uint32_t kp1;
extern uint32_t kp2;
extern uint32_t ki1;
extern uint32_t ki2;
extern uint32_t E;
