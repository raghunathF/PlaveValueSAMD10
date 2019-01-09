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

volatile uint16_t ones_val;
volatile uint16_t tens_val;
volatile uint16_t hndrds_val;

volatile uint16_t ones_array [100];
volatile uint16_t tens_array[100];
volatile uint16_t hndrds_array[100];
volatile bool temp_cube = false;

void test() {
	select_mux(false, false, true);
	static uint16_t temp = 0;
	temp_cube = detect_cube(false, true, true, 0);
	//delay_ms(10);
	ones_array[temp] = read_ones();
	tens_array[temp] = read_tens();
	hndrds_array[temp] = read_hndrds();
	temp++;
	read_all_values();
	if(temp > 200)
	{
		temp =0;
		
	}
}

int main (void)
{
	system_init();
	delay_init();
	ir_sensor_init();

	/* Insert application code here, after the board has been initialized. */
	while(true) {
		test();
		delay_ms(10);
	}
}
