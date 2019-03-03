/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "PlaceValueIRReadControl.h"
#include "PlaceValueIRRead.h"
#include "PlaceValueCountCubes.h"
#include "PlaceValueAddLEDControl.h"
#include "PlaceValueAddLED.h"
#include "PlaceValueI2CSlave.h"
#include "globalDefines.h"
#include "globalVariables.h"
#include "test.h"

volatile uint16_t ones_val;
volatile uint16_t tens_val;
volatile uint16_t hndrds_val;

volatile uint16_t ones_array [200];
volatile uint16_t tens_array[200];
volatile uint16_t hndrds_array[200];
volatile bool temp_cube = false;

void test() 
{
	static uint8_t tempCount = 0;
	uint32_t readALL[200];
	
	//select_mux(false, false, true);
	static uint16_t temp = 0;
	//temp_cube           = detect_cube(false, false, false, 0);
	select_mux(false, false, false);
	//delay_ms(10);
	ones_array[temp]    = read_ones();
	tens_array[temp]    = read_tens();
	hndrds_array[temp]  = read_hndrds();
	temp++;
	//read_all_values();
	if(temp > 190)
	{
		temp =0;
	}

}

void readI2CDetect()
{
	volatile bool readDetect = false;
	readDetect= port_pin_get_input_level(DETECT_PIN);
	if(readDetect == false)
	{
		readDetect = true;
	}

}

void setI2CDetect()
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_NONE;
	port_pin_set_config(DETECT_PIN, &config_port_pin);
}


int main (void)
{
	system_init();
	delay_init();
	
	ir_sensor_init();
	RGBPI55Init();
	//delay_cycles_ms(1000);
	setI2CDetect();
	
	
	configure_i2c_slave();
	configure_i2c_slave_callbacks();
	testTimer();
   
	/* Insert application code here, after the board has been initialized. */
	while(true) {
		//fadeREDControlled();
		updaeteADDLED();
		read_all_values();
		//testADDLED();
		//fadeREDControlled();
		//readI2CDetect();
		//fadeRED();
		delay_ms(10);
	}
}
