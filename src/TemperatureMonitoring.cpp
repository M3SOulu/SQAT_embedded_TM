/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#include "swm.h"
#include "delay.h"
#include "i2c.h"
#include "display.h"
//
#include "tm.h"
#define I2C_WRITE_LEN 10
#define DEFAULT_TEMP_READ_LEN 1

int main(void)
{
#if defined (__USE_LPCOPEN)
    SystemCoreClockUpdate();
#endif
    swm_config_i2c();
    i2c_reset();
	disp_off();
	disp_reset( DISP_SHOW_NONE );

	tm_reset_data();
	int i = 0;
	int read_val = -1;

	for (i = 0; i < 9; i++) {
		read_val = -1;
		while (read_val < 0 || read_val > 99) {
			read_val = tm_handle_sensor();
		}
	}

	disp_on( DISP_SHOW_NONE );

	display_message_t trend = tm_get_trend();
	disp_show_message( trend );

	while( 1 ){
		read_val = -1;
		delay_1s();

		while (read_val < 0 || read_val > 99) {
			read_val = tm_handle_sensor();
		}

		trend = tm_get_trend();
		disp_show_message( trend );
	}
    return 0 ;
}
