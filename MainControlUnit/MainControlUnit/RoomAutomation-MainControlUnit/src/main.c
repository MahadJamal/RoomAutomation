/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_uart_serial.h"
#include "conf_ili9341.h"
#include "conf_spi_master.h"
#include "stdio_serial.h"
#include "conf_sysfont.h"
//#include "AddWidget.h"
#include "LCD.h"
#include "ads7843.h"

#include "widget_gui.h"



void config_console_uart(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
		#endif
		.paritytype = CONF_UART_PARITY,
		#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
		#endif
	};
	
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONSOLE_UART, &uart_serial_options);
	
}

//-------------Write a function which initializes your Connections----//


//--------------------------------------------------------------------//


//----------------Handler Function------------------------------------//
void piohandler(uint32_t p_x, uint32_t p_y)
{
	
	//printf("PIO handler running %d, %d\n", p_x,p_y);
	printf("PIO handle.\n");
}



int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	
	sysclk_init();

	board_init();
	
	config_console_uart();
	
	LCD_init_pins();
	
	LCD_init_functions();
	
	LCD_setup_window();
	
	ads7843_init();
	
	//printf("This is Arduino Console UART Application.\n");
	 char * str ="hello";

	
	//app_widget_launch();
	
		
		uint32_t p_x;
		uint32_t p_y;
	
	ads7843_set_handler(piohandler);
	
	ads7843_enable_interrupt();  //Is redundant
	
	//ads7843_disable_interrupt();

	while (1)
	{
		
		//ili9341_backlight_on();

		
		//ili9341_set_top_left_limit(0, 0);
		//ili9341_set_bottom_right_limit(360, 240);

		//ili9341_duplicate_pixel(ILI9341_COLOR(255, 0, 0), 240UL * 320UL);
		
		//gfx_draw_rect(200,150, 50,70,GFX_COLOR_BLUE);
		
		//gfx_draw_string(str,30, 50, &sysfont  , GFX_COLOR_DK_CYAN, GFX_COLOR_BLACK);
		
		//gfx_draw_string_aligned(str,250, 240, &sysfont  , GFX_COLOR_DK_CYAN, GFX_COLOR_BLACK,TEXT_POS_BOTTOM,TEXT_ALIGN_CENTER);
		
		if(ads7843_is_pressed())
		{
			printf("Touch screen pressed.\n");
			ads7843_get_raw_point(&p_x, &p_y);
			printf("The user touched the screen at x = %d and y = %d",p_x,p_y);

		}
 		printf("This is Arduino Console UART Application.\n");
		
//		area.pos.x = 10;
//		area.pos.y = 150;
//		area.size.x = 90;
//		area.size.y = 40;
//		btn = wtk_button_create(wx, &area, "Click",
//		(win_command_t)1);
//		if (!btn) {
			//goto error_widget;
//		}
//		win_show(wtk_button_as_child(btn));

//		LCD_task_function();
		
		delay_ms(1000);
		

	}


}
