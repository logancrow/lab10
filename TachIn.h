//TachIn.h
//Prototypes for functions that read input from Tachometer
//Logan Crow and Samantha Flaim
//11/14/2018

//Initializes PB0 to be input for tachometer
//inputs: none
//outputs: none
void TachInit(void);

//captures input from tachometer
//inputs: none
//outputs: value from tachometer
uint32_t TachCapture(void);
