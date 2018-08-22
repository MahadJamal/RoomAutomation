
#include <asf.h>

#include "atmel_logo_small.h"
#include "LCDpages.h"


enum showPage{
	MainPage,
	DoorDevicePage,
	SensorDevicePage,
};


bool updatedisplay = true;

enum showPage pagetoshow = MainPage;

//Initialize LCD PINS
void LCD_init_pins()
{
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
	
}

//Initialize all the necessary libraries and functions

void LCD_init_functions()
{
		 membag_init();
		 
		 ili9341_init();
		 
		 gfx_init();
		
		 win_init();
		 
	
}

//we need a base window

void LCD_setup_window()
{
		struct win_attributes root_attr;
		struct win_window *win_root;

		win_root = win_get_root();
		root_attr = *win_get_attributes(win_root);
		root_attr.background = &atmel_logo_small;
		win_set_attributes(win_root, &root_attr, WIN_ATTR_BACKGROUND);

		win_show(win_root);
	
}



//Add the task function for LCD Task
void LCD_task_function()
{
	
	
	while(1)
	{
		if (updatedisplay)
		{
			switch (pagetoshow)
			{
				case MainPage:
				LCDpages_mainpage();
				updatedisplay = false;
				break;
				
				case DoorDevicePage:
				LCDpages_doordevicepage();
				break;
				
				case SensorDevicePage:
				LCDpages_sensordevicepage();
				break;
				
			}
			
		}
		
	}	
}


//Below function will handle events from touch events
/*
static bool widget_frame_command_handler(struct wtk_basic_frame *frame,
win_command_t command_data)
{
	char command = (uintptr_t)command_data;

	switch (command) {
		case SLIDER_ID:
		wtk_progress_bar_set_value(progress_bar,
		wtk_slider_get_value(slider));
		break;

		case BUTTON_ID:
		//todo Add code here to handle button press. 
		counter++;
		win_redraw(wtk_basic_frame_as_child(sub_frame));
		break;
	}

	return false;
}
*/