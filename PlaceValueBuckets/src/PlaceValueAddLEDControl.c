/*
 * PlaceValueNeopxlControl.c
 *
 * Created: 12/18/2018 10:53:10 AM
 *  Author: Raghunath
 */ 
#include <asf.h>
#include "PlaceValueAddLED.h"
#include "PlaceValueAddLEDControl.h"

#define SIZE_LED_VALUES 48

#define NO_LEDS 3
#define COLORS  3

#define HIGH_0	1
#define LOW_0	1

#define HIGH_1	1
#define LOW_1	1

static	uint8_t		led_delays[3][48];

#define TWOBITSPIVALUES {0x88,0x8E,0xE8,0xEE}
const	uint8_t SPIDataConertConsArray[] = TWOBITSPIVALUES;


static uint8_t* convertColorSPIData(colorInfo* colorData )
{
	volatile static uint8_t SPIData[NoBytesLED];
	volatile uint8_t i =0;
	uint8_t countSPIData = 0;
	volatile uint8_t temp =0;
	volatile uint8_t twoBitValue = 0;
	for(i=0;i<4;i++)
	{
		twoBitValue = (colorData->GBrightness & (0xC0>>i*2))>>(6-2*i);
		SPIData[countSPIData] = SPIDataConertConsArray[twoBitValue];
		countSPIData++;
	}
	for(i=0;i<4;i++)
	{
		//temp = (0x30>>(i*2));
		twoBitValue = (colorData->RBrightness & (0xC0>>i*2))>>(6-2*i);
		SPIData[countSPIData] = SPIDataConertConsArray[twoBitValue];
		countSPIData++;
	}
	for(i=0;i<4;i++)
	{
		twoBitValue = (colorData->BBrightness & (0xC0>>i*2))>>(6-2*i);
		SPIData[countSPIData] = SPIDataConertConsArray[twoBitValue];
		countSPIData++;
	}
	return SPIData;
}

void RGBPI55SetAllLED(colorInfo*  colorLED)
{
	uint8_t* LEDSPIData = NULL;
	static bool transferOngoing = false;
	uint16_t startArrayAddress = 0;
	static uint8_t counter = 31;
	uint8_t i,j =0;
	//SPIMasterInit();
	for(j = 0 ; j < NOLEDS ; j++)
	{
		LEDSPIData			= convertColorSPIData(&colorLED[j]);
		startArrayAddress   = j*NoBytesLED + STARTZEROS ;
		for(i = 0 ; i < NoBytesLED ; i++)
		{
			DMASourceRegister[i+startArrayAddress]   = LEDSPIData[i] ;
		}
	}
	
	//port_pin_set_output_level(PROFILE_PIN,true);
	while(transferOngoing == true);
	while(dma_start_transfer_job(&example_resource) == STATUS_OK);
	/*
	while(transferDone == false)
	{
		
		if(counter>30)
		{
			
			//delay_cycles_us(1);
			counter = 0;
			while(dma_start_transfer_job(&example_resource) == STATUS_OK);
			
		}
		counter++;
		delay_cycles_us(30);
	}
	
	*/
	//disableLEDSPI();
	//clearMOSI();
	//port_pin_set_output_level(PROFILE_PIN,false);
	
	
	//{
	//	 errr= dma_start_transfer_job(&example_resource);
	//	delay_cycles_ms(1);
	//}
	
	transferOngoing = false;
	transferDone = false;
}


void RGBPI55SetLED(uint8_t LEDNumber , colorInfo color_led )
{
	uint8_t i =0;
	static bool transferOngoing = false;
	uint16_t startArrayAddress = 0;
	uint8_t* LEDSPIData = NULL;
	uint8_t  LEDNU[12];
	//enable SPI
	SPIMasterInit();
	startArrayAddress = LEDNumber*NoBytesLED + STARTZEROS ;
	LEDSPIData = convertColorSPIData(&color_led);
	for(i = 0 ; i < NoBytesLED ; i++)
	{
		DMASourceRegister[i+startArrayAddress]   = LEDSPIData[i] ;
	}
	
	while(transferOngoing == true);
	dma_start_transfer_job(&example_resource);
	while(transferDone == false);
	//disable SPI
	disableLEDSPI();
	clearMOSI();
	transferOngoing = false;
	transferDone = false;
}

void clearLEDS()
{
	static colorInfo colorLED[3];
	uint8_t i =0;
	for(i=0;i<3;i++)
	{
		colorLED[i].RBrightness = 0;
		colorLED[i].GBrightness = 0;
		colorLED[i].BBrightness = 0;
	}
	RGBPI55SetAllLED(colorLED);
}