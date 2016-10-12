/*
 * display.h
 *
 *  Created on: Jun 6, 2016
 *      Author: timppa
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

/*
 * two different modes for compiling the DISP_show()
 */
#ifdef __cplusplus
extern "C" {
#endif

#define DISP_ERR_OVERFLOW  -1
#define DISP_ERR_UNDERFLOW -2
#define DISP_ERR_ILLEGAL   -3

int disp_off();

#define DISP_SHOW_ALL   1
#define DISP_SHOW_NONE  0

int disp_on(int alloff);
void disp_reset(int alloff);

typedef enum display_message_e {
	DISP_MSG_FIRST=-2,
	DISP_MSG_DOWN = -1,
	DISP_MSG_SAME = 0,
	DISP_MSG_UP   = 1,
	DISP_MSG_LAST
} display_message_t;

int disp_show_message( display_message_t message );

#ifdef __cplusplus
}
#endif

#endif /* DISPLAY_H_ */
