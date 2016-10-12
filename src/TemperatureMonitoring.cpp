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

int main(void)
{
#if defined (__USE_LPCOPEN)
    SystemCoreClockUpdate();
#endif

    swm_config_i2c();
    i2c_reset();
	disp_on( DISP_SHOW_NONE );
	disp_reset( DISP_SHOW_NONE );

	tm_reset_data();
	/**
	 * TODO: Oscar to remove this
	 */
	int i;

	// So i went completely wrong direction forgetting the scope rules

	for( i=0; i<9; i++){
		temperatures[temp_index]=tm_handle_sensor();
	}
	tm_update_average();
	display_message_t trend = tm_get_trend();
	disp_show_message( trend );
	/**
	 * TODO: Oscar to remove until here
	 */
	while( 1 ){

		temperatures[temp_index] = tm_handle_sensor();
		tm_update_average();
		trend = tm_get_trend();
		disp_show_message( trend );
		delay_1s();
	}
    return 0 ;
}
