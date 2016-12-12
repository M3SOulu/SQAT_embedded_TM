/*
 * display.cpp
 *
 *  Created on: Jun 6, 2016
 *      Author: timppa
 */

#include "i2c.h"
#include "hardware.h"
#include "ht16k33.h"
#include "display.h"

int disp_off()
{
	const int addr = HW_I2C_ADDR_HT16K33;
	char data[10];
	int rc=0;

	data[0] = HT16K33_CMD_OSCILLATOR_OFF;
	data[1]=0;

	rc = i2c_write( addr,data,1 );
	return rc;
}

static char disp_msg_data[10]={
		0,0,
		1,0,
		2,0,
		3,0,
		4,0,
};

static int disp_last_message = DISP_MSG_FIRST;

//
// set all display data to either "all on" or "all off"
//
static void disp_set_all(int alloff)
{
	char value = 0;
	switch( alloff ){
	case DISP_SHOW_NONE:
		value = SEGMENTS_NONE;
		break;
	case DISP_SHOW_ALL:
		value = SEGMENTS_ALL;
		break;
	default:
		return;
	}
	disp_msg_data[1] = value;
	disp_msg_data[3] = value;
	disp_msg_data[5] = value;
	disp_msg_data[7] = value;
	disp_msg_data[9] = value;
}

//
// reset display data to all off/on
// clear display message value
//
void disp_reset(int alloff)
{
	disp_set_all( alloff );
	disp_last_message = DISP_MSG_FIRST;
}

//
// power on display, set the clocking and initial data
// - data is all off/on
//
int disp_on(int alloff)
{
	const int addr = HW_I2C_ADDR_HT16K33;
	char disp_cmd_data[10];
	int rc=0;

	disp_cmd_data[0] = HT16K33_CMD_OSCILLATOR_ON;
	disp_cmd_data[1]=0;

	rc = i2c_write( addr,disp_cmd_data,1 );
	if ( 0 <= rc ){
		disp_cmd_data[0] = HT16K33_BLINK_CMD | 0x01;
		rc = i2c_write( addr,disp_cmd_data,1 );
	} else {
		return rc;
	}
	if ( 0 <= rc ){
		disp_cmd_data[0] = HT16K33_CMD_BRIGHTNESS | 0x08;
		rc = i2c_write( addr,disp_cmd_data,1 );
	} else {
		return rc;
	}
	disp_set_all( alloff );
	rc = i2c_write( addr,disp_msg_data,10 );

	return rc;
}

/************************************************************************
 *
 *   IMPLEMENTATION BELOW
 *
 ************************************************************************/

static void rotate_message_left()
{
	int tempfrst = disp_msg_data[FRST_NUM];
	disp_msg_data[FRST_NUM] = disp_msg_data[SEC_NUM];
	disp_msg_data[SEC_NUM] = disp_msg_data[THRD_NUM];
	disp_msg_data[THRD_NUM] = disp_msg_data[FRTH_NUM];
	disp_msg_data[FRTH_NUM] = tempfrst;
}

//
// display message of:
//   - DISP_MSG_DOWN
//   - DISP_MSG_SAME
//   - DISP_MSG_UP
// if message is same as previous then rotate left
//
int disp_show_message(display_message_t message)
{
	const int addr = HW_I2C_ADDR_HT16K33;

	switch (message) {
	case DISP_MSG_UP:
		disp_set_all( DISP_SHOW_NONE );

		disp_msg_data[THRD_NUM] = disp_msg_data[THRD_NUM] | U_CHAR;
		disp_msg_data[FRTH_NUM] = disp_msg_data[FRTH_NUM] | P_CHAR;
		break;
	case DISP_MSG_DOWN:
		disp_set_all( DISP_SHOW_NONE );

		disp_msg_data[FRST_NUM] = disp_msg_data[FRST_NUM]	| D_CHAR;
		disp_msg_data[SEC_NUM]	= disp_msg_data[SEC_NUM]	| O_CHAR;
		disp_msg_data[THRD_NUM] = disp_msg_data[THRD_NUM]	| W_CHAR;
		disp_msg_data[FRTH_NUM] = disp_msg_data[FRTH_NUM]	| N_CHAR;
		break;
	case DISP_MSG_SAME:
		rotate_message_left();
		break;
	};

	return i2c_write( addr, disp_msg_data,10 );
}
