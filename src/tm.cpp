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

#define TEMP_ADDR 0x70
#define TEMP_BUFFER 8
int temperatures[TEMP_BUFFER] = {0,0,0,0,0,0,0,0};

int temp_index=0;

int temp_sum=0;
int temp_old_sum = 0;

int temp_prev_average=0;
int temp_current_average=0;

display_message_t temp_trend = DISP_MSG_SAME;

void tm_reset_data()
{
	for (int i = 0; i < TEMP_BUFFER; i++) {
		temperatures[i] = 0;
	}
}

void tm_update_average(int temp)
{
	temp_old_sum = temp_sum;
	temp_sum = 0;
	temperatures[temp_index] = temp;
	temp_index = (temp_index + 1) % TEMP_BUFFER;
	for (int i = 0; i < TEMP_BUFFER; i++) {
		temp_sum = temp_sum + temperatures[i];
	}

	temp_prev_average = temp_current_average;
	temp_current_average = temp_sum / TEMP_BUFFER;

	//if ()
}

int tm_handle_sensor()
{
	int rc;
	char *data;

	i2c_read(TEMP_ADDR, 0, 0, data, 1);

	if (!(*data < 0 || *data > 99))
		tm_update_average(*data);

	return *data;
}

display_message_t tm_get_trend()
{
	// at first return msg_first. then should show empty

	if (temp_prev_average == temp_current_average) {
		return DISP_MSG_SAME;
	} else if (temp_prev_average > temp_current_average) {
		return DISP_MSG_DOWN;
	} else if (temp_prev_average < temp_current_average) {
		return DISP_MSG_UP;
	}

	return DISP_MSG_SAME; // default
}
