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




/*delay_1s();
		i2c_write(0x70, ones, I2C_WRITE_LEN);
		delay_1s();
		i2c_write(0x70, empty, I2C_WRITE_LEN);
		delay_1s();
		i2c_write(0x70, first_o, I2C_WRITE_LEN);*/



/*void empty_msg(char msg *) {

}*/

/*void choose_msg(display_message_t a_trend, char * msg) {
	empty_msg(msg);
	//msg[10] = {0, 0, 1, 0, 2, 0, 3, 0, 4, 0};

	// for testing
	char ones[10] = {0, 6, 1, 6, 2, 0, 3, 6, 4, 6};
	return ;

	switch (a_trend) {
	case DISP_MSG_UP:

		break;
	case DISP_MSG_DOWN:
		return retmsg[SEC_NUM] | O_CHAR;
		break;
	case DISP_MSG_SAME:
		break;
	};

	return retmsg;
}*/

int main(void)
{
#if defined (__USE_LPCOPEN)
    SystemCoreClockUpdate();
#endif

    char msg[10];
	char empty[10] = {0, 0, 1, 0, 2, 0, 3, 0, 4, 0};
	char ones[10] = {0, 6, 1, 6, 2, 0, 3, 6, 4, 6};
	/*char first_o[10] = {0, 0, 1, 0, 2, 0, 3, 0, 4, 0};
	first_o[1] = first_o[1] | O_CHAR;*/

    swm_config_i2c();
    i2c_reset();
	disp_on( DISP_SHOW_NONE );
	disp_reset( DISP_SHOW_NONE );

	tm_reset_data();
	/**
	 * TODO: Oscar to remove this
	 */
	int i;
	for( i=0; i<9; i++){
		tm_handle_sensor();
	}
	display_message_t trend = tm_get_trend();
	disp_show_message( trend );
	/**
	 * TODO: Oscar to remove until here
	 */



	// turn screen off until 9 measurements collected was done already
	/*i2c_write(0x70, empty, I2C_WRITE_LEN);

	for (int i = 0; i < 9; i++) {
		while (read_val < 0 || read_val > 99) {
			read_val = tm_handle_sensor();
		}
	}*/

	while( 1 ){
		int read_val = -1;
		/**
		 * TODO: Oscar to remove this
		 */

		delay_1s();

		while (read_val < 0 || read_val > 99) {
			read_val = tm_handle_sensor();
		}

		trend = tm_get_trend();
		disp_show_message( trend );




		// CHOOSE MESSAGE
		//choose_msg(trend, msg);

		/**
		 * TODO: Oscar to remove until here
		 */
	}
    return 0 ;
}
