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
	for(int i = 0; i != TEMP_BUFFER; i++)
		temperatures[i] = 0;

}

void tm_update_average(void)
{
	temp_old_sum = temp_sum;
	temp_prev_average = temp_current_average;

	// calculate current average temp
	for(int i = 0; i != TEMP_BUFFER; i++)
		temp_sum += temperatures[i];

	temp_current_average = temp_sum / 8;

	// discard the oldest

	for(int i = 0; i != TEMP_BUFFER-1; i++)
	{
		temperatures[i]=temperatures[i+1];
	}
	temperatures[TEMP_BUFFER-1] = 0;
	temp_index = 6;

}

int tm_handle_sensor()
{
	int rc = 0;
	char buff = -1;
	i2c_read(0x90, 0, 0, &buff, 1);
	rc = (int)buff;
	temp_index++;
	if(rc < 0 || rc > 99)
		return -1;
	return rc;
}

display_message_t tm_get_trend()
{
	if(temp_current_average > temp_prev_average)
		return DISP_MSG_UP;
	if(temp_current_average < temp_prev_average)
		return DISP_MSG_DOWN;
	return DISP_MSG_SAME; // default
}
