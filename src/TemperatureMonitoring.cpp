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
	int temptotal = 0;
	int tempaverage = 0;
	int i;
	for( i=0; i<9; i++){
		tm_handle_sensor();
		delay_1s();
		char buffer;
		i2c_read(0x90, 0, 0, &buffer, 1);
		temptotal =+ buffer;
		tempaverage = temptotal/(i+1);

		if (tempaverage < buffer){
			char x[] = {0,62,1,115,2,0,3,0,4,0};
			i2c_write(0x70, x, 10);
		}else if(tempaverage == buffer){
			char y[] = {0,109,1,119,2,0,3,55,4,121};
			i2c_write(0x70, y, 10);
		}else {
			char z[] = {0,94,1,40,2,0,3,40,4,40};
			i2c_write(0x70, z, 10);
		}



	}
	display_message_t trend = tm_get_trend();
	disp_show_message( trend );
	/**
	 * TODO: Oscar to remove until here
	 */
	while( 1 ){
		/**
		 * TODO: Oscar to remove this
		 */

		tm_handle_sensor();
		trend = tm_get_trend();
		disp_show_message( trend );
		/**
		 * TODO: Oscar to remove until here
		 */
	}
    return 0 ;
}
