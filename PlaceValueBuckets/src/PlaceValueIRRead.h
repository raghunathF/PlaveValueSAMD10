/*
 * PlaceValueIRRead.h
 *
 * Created: 12/7/2018 10:27:32 AM
 *  Author: Samantha Speer
 */ 


#ifndef PLACEVALUEIRREAD_H_
#define PLACEVALUEIRREAD_H_

#include <asf.h>

void configure_adc();
void configure_mux_select();
void turn_off_ir_led();
uint16_t adc_start_read_result(const enum adc_positive_input analogPin);
void ir_sensor_init();

#endif /* PLACEVALUEIRREAD_H_ */