/*
 * PlaceValueI2CSlave.c
 *
 * Created: 2/5/2019 3:08:36 PM
 *  Author: raghu
 */ 

#include <asf.h>
#include "PlaceValueI2CSlave.h"
#include "globalDefines.h"

void configure_i2c_slave(void);
void configure_i2c_slave_callbacks(void);

struct i2c_slave_packet packet;
struct i2c_slave_packet rd_packet;

#define SLAVE_ADDRESS			  0x12
#define DATA_LENGTH_SENSORS		  4
#define CONF_I2C_SLAVE_MODULE     SERCOM2


static uint8_t write_buffer[DATA_LENGTH_SENSORS] = {0x00, 0x00,0x00,0x00};
extern volatile bool sensorsUpdate;


struct i2c_slave_module i2c_slave_instance;

extern volatile bool I2CWriteComplete;
extern volatile bool I2CReadComplete;

extern  volatile uint8_t cubeOutputs[4];

static uint8_t test[2] = {0x44, 0x55};



bool readI2CSelectLine()
{
	volatile bool state = false;
	state = port_pin_get_input_level(DETECT_PIN);
	return state;
}

void i2c_read_request_callback(struct i2c_slave_module *const module)
{
	static uint8_t count = 0;
	static uint8_t tempCubeOutputs[4];
	//if( port_pin_get_input_level(DETECT_PIN) == false)
	//{
		
		//delay_cycles_us(2);
		if(sensorsUpdate == false)
		{
			tempCubeOutputs[0]	   = cubeOutputs[0];
			tempCubeOutputs[1]	   = cubeOutputs[1];
			tempCubeOutputs[2]	   = cubeOutputs[2];
			tempCubeOutputs[3]	   = cubeOutputs[3];
			//tempCubeOutputs[0]	   = 0xAA;
			//tempCubeOutputs[1]	   = 0xBB;
			//tempCubeOutputs[2]	   = 0x77;
			//tempCubeOutputs[3]	   = 0x11;
		}
		
		//rd_packet.data_length = DATA_LENGTH_SENSORS;
		rd_packet.data_length = DATA_LENGTH_SENSORS;
		rd_packet.data        = tempCubeOutputs;
		i2c_slave_write_packet_job(module, &rd_packet);
	//}
	
	
}


void i2c_write_request_callback()
{
	//if( readI2CSelectLine() == false)
	//{
		//I2CWriteComplete = true;
	//}
	
}

void i2c_read_complete_callback()
{
	//if( readI2CSelectLine() == false)
	//{
		//I2CWriteComplete = true;
	//}
	
}

//! [initialize_i2c]
void configure_i2c_slave(void)
{
	struct i2c_slave_config config_i2c_slave;
	i2c_slave_get_config_defaults(&config_i2c_slave);
    
	config_i2c_slave.generator_source = GCLK_GENERATOR_3;
	config_i2c_slave.address      = SLAVE_ADDRESS;
	config_i2c_slave.address_mode = I2C_SLAVE_ADDRESS_MODE_MASK;
	
	config_i2c_slave.pinmux_pad0 =  PINMUX_PA22D_SERCOM2_PAD0;
	config_i2c_slave.pinmux_pad1 =  PINMUX_PA23D_SERCOM2_PAD1;
	
	i2c_slave_init(&i2c_slave_instance, CONF_I2C_SLAVE_MODULE , &config_i2c_slave);
	i2c_slave_enable(&i2c_slave_instance);
	
}

void configure_i2c_slave_callbacks(void)
{
	i2c_slave_register_callback(&i2c_slave_instance, i2c_read_request_callback,I2C_SLAVE_CALLBACK_READ_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance,I2C_SLAVE_CALLBACK_READ_REQUEST);
}

