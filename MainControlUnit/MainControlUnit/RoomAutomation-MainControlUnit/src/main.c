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



int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	
	sysclk_init();

	board_init();
	
	config_console_uart();
	
	//printf("This is Arduino Console UART Application.\n");
	ili9341_init();
	
	gpio_configure_pin(PIO_PC23_IDX,PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
	gpio_configure_pin(PIO_PC24_IDX,PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
	gpio_configure_pin(PIO_PC25_IDX,PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
	
	while (1)
	{
		//ili9341_backlight_on();
		//delay_ms(500);
		//ili9341_backlight_off();
		//delay_ms(500);
		
			 ili9341_set_top_left_limit(0, 0);
			 ili9341_set_bottom_right_limit(240, 320);

			 ili9341_duplicate_pixel(ILI9341_COLOR(255, 0, 0), 240UL * 320UL);
		//ioport_toggle_pin_level();
		//ioport_toggle_pin_level(CONF_ILI9341_BACKLIGHT_PIN);
		ioport_toggle_pin_level(LED0_GPIO);
		//ILI9341_CMD_COLOR_SET();
		
	}

	/* Insert application code here, after the board has been initialized. */
}
