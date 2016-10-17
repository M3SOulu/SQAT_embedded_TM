/*
 * tm.h
 *
 *  Created on: Oct 11, 2016
 *      Author: timppa
 */

#ifndef TM_H_
#define TM_H_

#define TEMP_ADDR 0x90
#define TEMP_BUFFER 8

int tm_handle_sensor();
display_message_t tm_get_trend();
void tm_reset_data();

#endif /* TM_H_ */
