/*
 * LCDpages.h
 *
 * Created: 8/15/2018 8:55:59 PM
 *  Author: Mahad Jamal
 */ 


#ifndef LCDPAGES_H_
#define LCDPAGES_H_

#include <stdio.h>

enum app_widget_ids {
	/** Event command ID for the slider. */
	SLIDER_ID = 1,
	/** Event command ID for the button. */
	BUTTON_ID_1,
	
	BUTTON_ID_2
};

/** Background color for application */
#define APP_BACKGROUND_COLOR        GFX_COLOR(50, 50, 50)

/** @} */

/**
 * \name Widget sizes and positions
 *
 * @{
 */

/** Label position on top of display */
#define LABEL_POS_X                 10
/** Label position on top of display */
#define LABEL_POS_Y                 10

/** Slider position */
#define SLIDER_POS_X                10
/** Slider position */
#define SLIDER_POS_Y                60
/** Slider size on display */
#define SLIDER_SIZE_X               80
/** Slider size on display */
#define SLIDER_SIZE_Y               40

/** Spacing from slider to progress bar */
#define SLIDER_PB_SPACING_X         10
/** Slider progress bar on display */
#define PB_SIZE_X                   SLIDER_SIZE_X
/** Slider progress bar on display */
#define PB_SIZE_Y                   SLIDER_SIZE_Y

/** @} */

/**
 * \name Widget configurations
 *
 * @{
 */

/** Max value for slider */
#define SLIDER_MAX_VALUE            100

/** @} */

/**
 * \name Static text strings
 *
 * @{
 */

/** Description for label */
const static char *demo_string = "Demonstrating widgets";

/** @} */

/** Pointer to frame for application */
static struct wtk_basic_frame *main_frame;
/** Pointer to slider */
static struct wtk_slider *slider;
/** Pointer to progress bar */
static struct wtk_progress_bar *progress_bar;
/** Frame background bitmap */
static struct gfx_bitmap frame_background;
/** Counter for button */
static uint8_t counter;
/** Pointer to the sub-frame */
static struct wtk_basic_frame *sub_frame;
/** Sub-frame background bitmap */
static struct gfx_bitmap sub_frame_background;

/** @} */






//prototype for function to make and display lcd pages
void LCDpages_mainpage();

void LCDpages_doordevicepage();

void LCDpages_sensordevicepage();

#endif /* LCDPAGES_H_ */