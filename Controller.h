//Controller.h
//Prototypes for functions that receive input from BLYNK and Tachometer
//and output to LCD, BLYNK and Motor
//Logan Crow and Samantha Flaim
//11/14/2018

//Initializes all inputs and outputs
//inputs: none
//outputs: none
void ControllerInit(void);

//Receives input from Blynk and outputs to motor
//inputs: TBD
//outputs: none
void MotorController(void);

//Receives input from Tachometer and outputs to LCD and BLYNK
//inputs: motor speed
//outputs: none
void DisplayController(uint32_t);
