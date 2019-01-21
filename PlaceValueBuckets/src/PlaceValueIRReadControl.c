/*
 * PlaceValueIRReadControl.c
 *
 * Created: 12/7/2018 10:39:22 AM
 *  Author: Samantha Speer
 */ 

#include "PlaceValueIRReadControl.h"
#include "PlaceValueIRRead.h"
#include <asf.h>


void select_mux(const bool S2, const bool S1, const bool S0) {
	port_pin_set_output_level(MUX_S0, S0);
	port_pin_set_output_level(MUX_S1, S1);
	port_pin_set_output_level(MUX_S2, S2);
}

uint16_t read_ones() {
	return adc_start_read_result(ONES_CHANNEL);
}

uint16_t read_tens() {
	return adc_start_read_result(TENS_CHANNEL);
}

uint16_t read_hndrds() {
	return adc_start_read_result(HNDRDS_CHANNEL);
}

uint16_t read_misc() {
	return adc_start_read_result(MISC_CHANNEL);
}