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
	for (int i = 0; i < 8; i++) {
		temperatures[i] = 0;
	}
}

void tm_update_average(int temp)
{
	temp = 0;
	for (int i = 0; i < 8; i++) {
		temp = temp + temperatures[i];
	}
	for (int j = 7; j > 1; j-- ) {
		temperatures [j] = temperatures[j - 1];
	}
	//i2c_read(0x90, 0, 0, &data, 1);
}

int tm_handle_sensor()
{
	int rc;
	return -1;
}

display_message_t tm_get_trend()
{
	return DISP_MSG_SAME; // default
}
