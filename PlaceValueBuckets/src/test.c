/*
 * test.c
 *
 * Created: 2/5/2019 4:12:04 PM
 *  Author: raghu
 */ 

#include <asf.h>
#include "PlaceValueAddLEDControl.h"

struct  tc_module    tcTest;
static  updateLED = false;

void fadeRED()
{
	volatile static colorInfo test_color;
	uint8_t i = 0;
	test_color.GBrightness = 0;
	test_color.RBrightness = 0;
	test_color.BBrightness = 0;
	for(i=0;i<255;i++)
	{
		test_color.RBrightness = i;
		test_color.GBrightness = i;
		test_color.BBrightness = i;
		RGBPI55SetLED(0,test_color);
		RGBPI55SetLED(1,test_color);
		RGBPI55SetLED(2,test_color);
		delay_ms(1);
	}
	
	for(i=255;i>0;i--)
	{
		test_color.RBrightness = i;
		test_color.GBrightness = i;
		test_color.BBrightness = i;
		RGBPI55SetLED(0,test_color);
		RGBPI55SetLED(1,test_color);
		RGBPI55SetLED(2,test_color);
		delay_ms(1);
	}
}



void fadeREDControlled()
{
	volatile static colorInfo testColor[3];
	uint8_t i,j,k =0;
	for(k=0;k<3;k++)
	{
		for(i=0;i<255;i++)
		{
			for(j=0;j<3;j++)
			{
				
				if(k==j)
				{
					testColor[j].RBrightness =	i;
					testColor[j].GBrightness =	i;
					testColor[j].BBrightness =	i;
				}
				else
				{
					testColor[j].RBrightness =	0;
					testColor[j].GBrightness =	0;
					testColor[j].BBrightness =	0;
				}
			}
			RGBPI55SetAllLED(testColor);
			delay_ms(1);
		}
	}
}

void testADDLED()
{
	fadeRED();
}

void updaeteADDLED()
{
	
	static colorInfo testColor[3];
	static uint8_t count = 0;
	static bool increment = true;
	if(updateLED == true)
	{
		updateLED = false;
		testColor[0].RBrightness =	count;
		testColor[0].GBrightness =	count;
		testColor[0].BBrightness =	count;
	
		testColor[1].RBrightness =	count;
		testColor[1].GBrightness =	count;
		testColor[1].BBrightness =  count;
	
		testColor[2].RBrightness =	count;
		testColor[2].GBrightness =	count;
		testColor[2].BBrightness =	count;
	
		//count++;
		RGBPI55SetAllLED(testColor);
		if(increment == true)
		{
			count++;
			if(count > 50 )
			{
				increment = false;
				
			}
		}
		else
		{
			count --;
			if(count < 1)
			{
				increment = true;
			}
			
		}
		
	}
	
	
}

void updateLEDMatrix()
{
	
	updateLED = true;
	
	//port_pin_toggle_output_level(NEOPXL);
	//updateSPIValues();
}

void initTimerCallbacks()
{
	tc_register_callback(&tcTest, updateLEDMatrix,TC_CALLBACK_OVERFLOW);
	tc_enable_callback(&tcTest, TC_CALLBACK_OVERFLOW);
}

void initTimer()
{
	struct tc_config config_tc;
	tc_get_config_defaults(&config_tc);
	struct tc_events config_events;
	config_tc.enable_capture_on_channel[0]		=		true;
	config_tc.counter_size						=		TC_COUNTER_SIZE_16BIT; //8
	config_tc.clock_source						=		GCLK_GENERATOR_0 ;
	config_tc.clock_prescaler					=		TC_CLOCK_PRESCALER_DIV8; //1024
	config_tc.counter_8_bit.period				=		0xFF;
	tc_init(&tcTest, TC1 , &config_tc);
	tc_enable(&tcTest);
}

void setTestPin()
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(NEOPXL, &config_port_pin);
}
void testTimer()
{
	//Set a test pin as output
	//setTestPin();
	//inittimer
	initTimer();
	initTimerCallbacks();
	
}