/*
 * PlaceValueIRRead.c
 *
 * Created: 12/7/2018 10:26:58 AM
 *  Author: Samantha Speer
 */ 

#include "PlaceValueIRRead.h"
#include <asf.h>

struct adc_module adc_instance;
uint16_t* adc_result = NULL;

void configure_adc()
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	port_pin_set_config(TP1, &config_port_pin);
	
	struct adc_config conf_adc;
	adc_get_config_defaults(&conf_adc);
	adc_result = malloc(sizeof(uint16_t));

	conf_adc.reference			= TP1;
	conf_adc.clock_prescaler	= ADC_CLOCK_PRESCALER_DIV16;
	conf_adc.positive_input		= 6;
	conf_adc.negative_input		= ADC_NEGATIVE_INPUT_GND;
	conf_adc.resolution			= ADC_RESOLUTION_8BIT;
	conf_adc.left_adjust		= true;

	adc_init(&adc_instance, ADC, &conf_adc);
	adc_enable(&adc_instance);
}

void configure_mux_select() {
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(MUX_S0, &config_port_pin);
	port_pin_set_config(MUX_S1, &config_port_pin);
	port_pin_set_config(MUX_S2, &config_port_pin);
}

void configure_ir_led() {
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_CNTRL, &config_port_pin);
}

void turn_on_ir_led(){
	port_pin_set_output_level(LED_CNTRL, true);
}

void turn_off_ir_led(){
	port_pin_set_output_level(LED_CNTRL, false);
}

uint16_t adc_start_read_result(const enum adc_positive_input analogPin)
{
	uint16_t temp = 0;
	adc_set_positive_input(&adc_instance, analogPin );
	adc_start_conversion(&adc_instance);
	while((adc_get_status(&adc_instance) & ADC_STATUS_RESULT_READY) != 1);
	adc_read(&adc_instance, adc_result);
	temp = *adc_result;
	return temp;
}

void ir_sensor_init()
{
	configure_adc();
	configure_mux_select();
	configure_ir_led();
	turn_on_ir_led();
}
