/*
 * tm.h
 *
 *  Created on: Oct 11, 2016
 *      Author: timppa
 */

#ifndef TM_H_
#define TM_H_

int tm_handle_sensor();
display_message_t tm_get_trend();
void tm_reset_data();
char shift_right(char* a, int length);

#endif /* TM_H_ */
