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

int temp_sum=0;
int temp_old_sum = 0;

int temp_prev_average=0;
int temp_current_average=0;

display_message_t temp_trend = DISP_MSG_SAME;

void tm_reset_data()
{
 i2c_reset();
}

void tm_update_average(int temp)
{

	if (temp_index>7)
	{
		for ( int i=0;i<temp_index;++i)
			temp_sum+=temperatures[i];

		temp_prev_average= temp_current_average;
		temp_current_average=temp_sum/8;
		temp_sum=0;

		//trend is---
		if (temp_prev_average==temp_current_average)
			temp_trend=DISP_MSG_SAME;
		else if (temp_prev_average>temp_current_average)
			temp_trend=DISP_MSG_DOWN;
		else
			temp_trend=DISP_MSG_UP;

		// discard the oldest and insert the next temperature as the latest
		for (int i=0;i<7;i++)
		{
			temperatures[i]=temperatures[i+1];

		}
		temperatures[7]=temp;

	}
	else
		temp_index++;
		temperatures[temp_index]=temp;


}

int tm_handle_sensor()
{
	char temperature='0';
	char dummy;

	int rc = i2c_read(0x90, &dummy,0,&temperature,1);
	tm_update_average(temperature);

	delay_1s();
	return -1;

//	return temperature;
}

display_message_t tm_get_trend()
{
	return temp_trend; // default
}
