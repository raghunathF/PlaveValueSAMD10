/*
 * globalVariables.h
 *
 * Created: 1/9/2019 3:46:21 PM
 *  Author: raghu
 */ 


#ifndef GLOBALVARIABLES_H_
#define GLOBALVARIABLES_H_


volatile bool		transferDone		= false;
volatile uint8_t	DMASourceRegister [NOLEDS*NoBytesLED+2*STARTZEROS];

volatile bool sensorsUpdate = false;
volatile uint8_t cubeOutputs[4];


#endif /* GLOBALVARIABLES_H_ */