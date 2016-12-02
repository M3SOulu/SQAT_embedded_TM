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
//display_message_t temp_trend = DISP_MSG_UP;
//display_message_t temp_trend = DISP_MSG_DOWN;

void tm_reset_data()
{

}

void tm_update_average(int temp)
{
	temperatures[temp_index] = temp;
	for(int i = 0; i < TEMP_BUFFER; i++) {
		temp_sum = temp_sum + temperatures[i];
	}
	temp_current_average = temp_sum / TEMP_BUFFER;
	temp_index++;
}

int tm_handle_sensor()
{
	int rc = i2c_read(0x90, 0, 0, &data);
	tm_update_average(rc);
	return rc;
}

display_message_t tm_get_trend()
{
	if(temp_current_average < temp_prev_average) {
		return DISP_MSG_UP;
	} else if(temp_current_average > temp_prev_average) {
		return DISP_MSG_DOWN;
	}
	return DISP_MSG_SAME; // default
}


