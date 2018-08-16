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
#include "atmel_logo_small.h"
#include "AddWidget.h"



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


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	
	sysclk_init();

	board_init();
	
	config_console_uart();
	
	//printf("This is Arduino Console UART Application.\n");
	
	
		//GPIOS INITIALIZATION AS OUTPUT FOR DC/RESET/LED <- Will go into the function to init my connections
		pmc_enable_periph_clk(ID_PIOC);
		pmc_enable_periph_clk(ID_PIOA);
		
		gpio_configure_pin(PIO_PC23_IDX,PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
		gpio_configure_pin(PIO_PC24_IDX,PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
		gpio_configure_pin(PIO_PC25_IDX,PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
		gpio_configure_pin(PIO_PC28_IDX,PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
		
		pio_set_peripheral(PIOA,PIO_PERIPH_A, PIO_PA25A_SPI0_MISO);
		pio_set_peripheral(PIOA,PIO_PERIPH_A, PIO_PA26A_SPI0_MOSI);
		pio_set_peripheral(PIOA,PIO_PERIPH_A, PIO_PA27A_SPI0_SPCK);
		pio_set_peripheral(PIOA,PIO_PERIPH_A, PIO_PA28A_SPI0_NPCS0);
		
		pmc_enable_periph_clk(ID_SPI0);
		
		
		spi_master_init(SPI0);
		
		//gpio_configure_pin(SPI0_NPCS0_GPIO ,SPI0_NPCS0_FLAGS);
	
	
	 char * str ="hello";
	 membag_init();
	 
	ili9341_init();
	
	gfx_init();
	//spi_select_device(SPI0, 0);
	
	//spi_enable_clock(SPI0);
	spi_enable(SPI0);
	
	//struct win_window wx;
	
	win_init();
	
	struct win_attributes root_attr;
	struct win_window *win_root;

	win_root = win_get_root();
	root_attr = *win_get_attributes(win_root);
	root_attr.background = &atmel_logo_small;
	win_set_attributes(win_root, &root_attr, WIN_ATTR_BACKGROUND);

	win_show(win_root);
	
	//wx = win_get_root();
	
	app_widget_launch();
	
	
//	struct wtk_button btn;
	
//	struct win_area area;
	
	//wx = win_get_parent(wx)
	//ili9341_set_orientation(ILI9341_SWITCH_XY);
	while (1)
	{
		
		ili9341_backlight_on();

		
		//ili9341_set_top_left_limit(0, 0);
		//ili9341_set_bottom_right_limit(360, 240);

		//ili9341_duplicate_pixel(ILI9341_COLOR(255, 0, 0), 240UL * 320UL);
		
		//gfx_draw_rect(200,150, 50,70,GFX_COLOR_BLUE);
		
		//gfx_draw_string(str,30, 50, &sysfont  , GFX_COLOR_DK_CYAN, GFX_COLOR_BLACK);
		
		//gfx_draw_string_aligned(str,250, 240, &sysfont  , GFX_COLOR_DK_CYAN, GFX_COLOR_BLACK,TEXT_POS_BOTTOM,TEXT_ALIGN_CENTER);
		
		
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
		
		delay_ms(1000);
		

		//spi_disable(SPI0);
		//ioport_toggle_pin_level();
		//ioport_toggle_pin_level(CONF_ILI9341_BACKLIGHT_PIN);
		//ioport_toggle_pin_level(LED0_GPIO);
		//ILI9341_CMD_COLOR_SET();
		
	}

	/* Insert application code here, after the board has been initialized. */
}
