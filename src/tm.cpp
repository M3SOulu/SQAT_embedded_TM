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
char temperatures[TEMP_BUFFER] = {
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
	for ( int i = 0;  i < 8; i++) {
		temperatures[i] = 0;
	}
}

void tm_update_average(int currTemp, int oldTemp)
{
	temp_old_sum = temp_sum;
	temp_sum = temp_sum + currTemp - oldTemp;
	temp_prev_average = temp_old_sum / TEMP_BUFFER;
	temp_current_average = temp_sum / TEMP_BUFFER;
}

int tm_handle_sensor()
{
	int oldTemp = (int)shift_right(temperatures, TEMP_BUFFER);
	i2c_read(HW_I2C_TEMP_SENSOR, 0, 0, temperatures, 1);
	int currTemp = (int)temperatures[0];
	//temperatures[0] = currTemp; done by i2c_read

	tm_update_average(currTemp, oldTemp);

	delay_1s();
	//int rc;  ?????
	return -1;
}

// Shifts the array right one step and returns the rightmost element
char shift_right(char* a, int length) {
   int i;
   char last = a[length-1];
   for(i = 0; i < length-2; i++){
      a[i+1] = a[i];
   }
   a[0] = 0;
   return last;
}

display_message_t tm_get_trend()
{
	if(temp_prev_average < temp_current_average)
		return DISP_MSG_UP;
	else if(temp_prev_average > temp_current_average)
		return DISP_MSG_DOWN;
	else
		return DISP_MSG_SAME;
}
