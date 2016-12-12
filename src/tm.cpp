/*
 * tm.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: timppa
 */

#include "hardware.h"
#include "i2c.h"
#include "display.h"
#include "delay.h"

#include "tm.h"

// Use these variables if you find them useful
// throw them away if not

#define TEMP_BUFFER 8
int temperatures[TEMP_BUFFER] = {
		0,0,0,0,
		0,0,0,0
};

int temp_index=0;
int sensor_handled_counter = 0;

int temp_sum=0;
int temp_old_sum = 0;

int temp_prev_average=0;
int temp_current_average=0;

display_message_t temp_trend = DISP_MSG_SAME;

void tm_reset_data()
{
	volatile int i=0;
	for(i=0;i<8;i++){
		temperatures[i]=0;
	}
}

void tm_update_average(int temp)
{
	temp_prev_average= temp_current_average;

		int i=0;
		for(i=0;i<8;i++){
			temp_sum=temp_sum+temperatures[i];
		}
		temp_current_average = temp_sum/8;

}

int tm_handle_sensor()
{
	char temperature;
	i2c_read(HW_I2C_TEMP_SENSOR, 0, 0, &temperature, 1);//Assuming this will give the temperature
	temperatures[temp_index] = temperature;
	temp_index++;
	if(temp_index>7){
		temp_index = 0;
	}
	tm_update_average(temperature);
	return -1;
}

display_message_t tm_get_trend()
{

	if(temp_current_average>temp_prev_average){
		return DISP_MSG_UP;
	}else if(temp_current_average<temp_prev_average){
		return DISP_MSG_DOWN;
	}else{
		return DISP_MSG_SAME; // default
	}

}
