/*
 * PlaceValueIRReadControl.h
 *
 * Created: 12/7/2018 10:39:45 AM
 *  Author: Samantha Speer
 */ 


#ifndef PLACEVALUEIRREADCONTROL_H_
#define PLACEVALUEIRREADCONTROL_H_

#include <asf.h>

void select_mux(const bool S0, const bool S1, const bool S2);
uint16_t read_ones();
uint16_t read_tens();
uint16_t read_hndrds();
uint16_t read_misc();

#endif /* PLACEVALUEIRREADCONTROL_H_ */