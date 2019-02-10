/*
 * PlaceValueCountCubes.c
 *
 * Created: 12/17/2018 1:01:22 PM
 *  Author: Samantha Speer
 */ 
/*
 * True if the cube is in the place specified by S2,S1,S0
 * Place is between 0 and 3
 */

#include "PlaceValueIRReadControl.h"
#include "globalDefines.h"
#include <asf.h>

static volatile uint32_t cubes_detected = 0;
extern  volatile uint8_t cubeOutputs[4];



bool detect_cube(bool S0, bool S1, bool S2, uint8_t place) {
	uint16_t value = 0;
	
	select_mux(S0, S1, S2);
	switch (place)
	{
		case 0:
			value = read_ones();
			break;
		case 1:
			value = read_tens();
			break;
		case 2:
			value = read_hndrds();
			break;
		case 3:
			value = read_misc();
			break;
		default:
			break;
	}
	
	if (value > CUBE_DETECT_THRESHOLD) {
		return true;
	} else {
		return false;
	}
}

void formatData(uint32_t cubes_detected)
{
	uint8_t i = 0;
	uint32_t temp = 0;
	for(i=0;i<4;i++)
	{
		cubeOutputs[i] = (uint8_t)((cubes_detected >> (24 - 8*i)) & 0xFF) ;
	}
	
}

/*
 * Reads through all different values, detects the cube, 
 * creates an number in the form of the values
 */
void read_all_values(){
	uint8_t i, place;
	uint8_t ind;
	static bool S0;
	static bool S1;
	static bool S2;
    volatile bool cube = false;
	volatile uint32_t cubes_detected = 0;
	
	for (i = 0; i < 8; i++)
	{
		S0 = (bool) (i & 0x1);
		S1 = (bool) ((i >> 1) & 0x1);
		S2 = (bool) ((i >> 2) & 0x1);
		for (place = 0; place < 3; place++)
		{
			ind = 2 + i + place*10;
			// Put boolean value from detect cube at place indicated by ind
			//delay_ms(10);
			cube = detect_cube(S0, S1, S2, place);
			//delay_ms(10);
			if(cube == true)
			{
				cubes_detected = cubes_detected | ( (((uint32_t)cube) & 0x1) << ind );
				cube = false;
			}
			//delay_ms(10);
		}
	}
	
	for (i = 0; i < 6; i++)
	{
		S0 = (bool) (i & 0x1);
		S1 = (bool) ((i >> 1) & 0x1);
		S2 = (bool) ((i >> 2) & 0x1);
		place = 3;
		ind = i + ((i/2)*8);
		// Put boolean value from detect cube at place indicated by ind
		cube = detect_cube(S0, S1, S2, place);
		cubes_detected = cubes_detected | ( (((uint32_t)cube) & 0x1) << ind );
	}
	formatData(cubes_detected);
}




/*
void readAllColumns()
{
	uint8_t i =0;
	for(i=0;i<)
	{
		for(j=0;)
		{
			select_mux(S0, S1, S2);
			= detectCube();
			 = read_ones();
			 = read_tens();
			 = read_hndrds();
		}
	}
}
*/