/*
 * PlaceValueNeopxlControl.h
 *
 * Created: 12/18/2018 10:53:28 AM
 *  Author: samie
 */ 


#ifndef PLACEVALUENEOPXLCONTROL_H_
#define PLACEVALUENEOPXLCONTROL_H_

typedef struct
{
	uint8_t RBrightness ;
	uint8_t GBrightness ;
	uint8_t BBrightness ;
}colorInfo;


void RGBPI55SetLED(uint8_t LEDNumber , colorInfo color_led );
void RGBPI55SetAllLED(colorInfo*  colorLED);
void clearLEDS();





#endif /* PLACEVALUENEOPXLCONTROL_H_ */