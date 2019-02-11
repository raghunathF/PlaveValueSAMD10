/*
 * PlaceValueNeopixel.h
 *
 * Created: 12/18/2018 10:52:38 AM
 *  Author: Raghunath
 */ 


#ifndef PLACEVALUENEOPIXEL_H_
#define PLACEVALUENEOPIXEL_H_

#include "globalDefines.h"

#define CONF_MASTER_MUX_SETTING SPI_SIGNAL_MUX_SETTING_D
#define CONF_MASTER_PINMUX_PAD0 PINMUX_PA14C_SERCOM0_PAD0
#define CONF_MASTER_PINMUX_PAD1 PINMUX_PA15C_SERCOM0_PAD1
#define CONF_MASTER_PINMUX_PAD2 PINMUX_UNUSED
#define CONF_MASTER_PINMUX_PAD3 PINMUX_UNUSED
#define CONF_MASTER_SPI_MODULE  SERCOM0


#define SPIBAUDRATE 2500000

void RGBPI55Init();
void enableLEDSPI();
void disableLEDSPI();
void clearMOSI();
void SPIMasterInit();

struct dma_resource example_resource;
extern volatile bool transferDone;
extern volatile uint8_t DMASourceRegister[NOLEDS*NoBytesLED+2*STARTZEROS];


#endif /* PLACEVALUENEOPIXEL_H_ */