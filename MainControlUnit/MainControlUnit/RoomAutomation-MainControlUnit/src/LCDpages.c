/*
 * LCDpages.c
 *
 * Created: 8/15/2018 8:56:24 PM
 *  Author: Mahad Jamal
 */ 

#include "LCDpages.h"

#include <asf.h>

static bool widget_frame_command_handler(struct wtk_basic_frame *frame,
win_command_t command_data)
{
	char command = (uintptr_t)command_data;

	switch (command) {
		case SLIDER_ID:
		wtk_progress_bar_set_value(progress_bar,
		wtk_slider_get_value(slider));
		break;

		case BUTTON_ID_1:
		/** \todo Add code here to handle button press. */
		counter++;
		//win_redraw(wtk_basic_frame_as_child(sub_frame));
		break;
		
		case BUTTON_ID_2:
		break;
	}

	return false;
}


static void sub_frame_draw_handler(struct win_window *win,
		struct win_clip_region const *clip)
{
	char buffer[4];

	snprintf(buffer, sizeof(buffer), "%3d", counter);

	/**
	 * \todo Add code here to draw text on screen using the
	 * gfx_draw_string() function.
	 */
	gfx_draw_string(buffer, clip->origin.x + 30, clip->origin.y + 12,
			&sysfont, GFX_COLOR(255, 255, 255),
			GFX_COLOR_TRANSPARENT);
}



void LCDpages_mainpage()
{
	struct win_window *win_root;
	struct win_window *parent;
	struct win_area area;
	struct wtk_label *lbl;
	const static char *mainpage_string = "Following Devices:";
	struct wtk_button *doorbtn;
	//struct wtk_button *sensorbtn;
		
			/* Get pointer to root window */
	win_root = win_get_root();

	/* Application frame */

	/* Create a background bitmap using a solid color. */
	frame_background.type = GFX_BITMAP_SOLID;
	frame_background.data.color = APP_BACKGROUND_COLOR;

	/* Set the area to fill the entire screen */
	area.pos.x = 0;
	area.pos.y = 0;
	area.size.x = gfx_get_width();
	area.size.y = gfx_get_height();

	/*
	 * Create a basic frame with a specified background and command event
	 * handler. Check the return value if an error occurred while creating
	 * the widget.
	 */
	main_frame = wtk_basic_frame_create(win_root, &area,
			&frame_background, NULL,
			widget_frame_command_handler, NULL);
	if (!main_frame) {
		goto error_frame;
	}

	/* Get a pointer to the widget's window for adding sub-widgets. */
	parent = wtk_basic_frame_as_child(main_frame);

	/*
	 * Draw the frame by showing the frame widget's window. Any
	 * child-widgets and windows will not be shown before the parent
	 * widget/window is shown.
	 */
	win_show(parent);

	/* Application label */
	area.pos.x = LABEL_POS_X;
	area.pos.y = LABEL_POS_Y;
	/* Find an optimal size for the widget. */
	wtk_label_size_hint(&area.size, demo_string);

	/*
	 * Create the label and check the return value if an error occurred
	 * while creating the label.
	 */
	lbl = wtk_label_create(parent, &area, mainpage_string,
			GFX_COLOR(255, 255, 255), NULL, false);
	if (!lbl) {
		goto error_widget;
	}
	

	
	/* Draw the label by showing the label widget's window. */
	win_show(wtk_label_as_child(lbl));
	


// 	/* Application slider */
// 	area.pos.x = SLIDER_POS_X;
// 	area.pos.y = SLIDER_POS_Y;
// 	area.size.x = SLIDER_SIZE_X;
// 	area.size.y = SLIDER_SIZE_Y;

	/*
	 * Create the slider and check the return value if an error occurred
	 * while creating the slider.
	 */
//	slider = wtk_slider_create(parent, &area, SLIDER_MAX_VALUE,
//			SLIDER_MAX_VALUE / 2,
//			WTK_SLIDER_HORIZONTAL | WTK_SLIDER_CMD_RELEASE,
//			(win_command_t)SLIDER_ID);
//	if (!slider) {
//		goto error_widget;
//	}

	/* Draw the slider by showing the slider widget's window. */
//	win_show(wtk_slider_as_child(slider));

	/* Application progress bar, placed right of the slider. */
//	area.pos.x += area.size.x + SLIDER_PB_SPACING_X;
//	area.size.x = PB_SIZE_X;
//	area.size.y = PB_SIZE_Y;

	/*
	 * Create the progress bar and check the return value if an error
	 * occurred while creating the progress bar.
	 */
//	progress_bar = wtk_progress_bar_create(parent, &area, SLIDER_MAX_VALUE,
//			SLIDER_MAX_VALUE / 2, GFX_COLOR(255, 255, 0),
//			GFX_COLOR(90, 90, 90), WTK_PROGRESS_BAR_HORIZONTAL);
//	if (!progress_bar) {
//		goto error_widget;
//	}

	/* Draw the progress bar by showing the progress bar widget's window. */
//	win_show(wtk_progress_bar_as_child(progress_bar));

	/** \todo Add code to set up button here. */
	area.pos.x = 10;
	area.pos.y = 30;
	area.size.x = 90;
	area.size.y = 40;

	doorbtn = wtk_button_create(parent, &area, "Click1",
			(win_command_t)BUTTON_ID_2);
	if (!doorbtn) {
		goto error_widget;
	}
	win_show(wtk_button_as_child(doorbtn));
	
	
	area.pos.x = 10;
	area.pos.y = 100;
	area.size.x = 90;
	area.size.y = 40;

	doorbtn = wtk_button_create(parent, &area, "Click2",
	(win_command_t)BUTTON_ID_1);
	if (!doorbtn) {
		goto error_widget;
	}
	win_show(wtk_button_as_child(doorbtn));

	//win_show(parent);
	/** \todo Add code to set up basic frame here. */
//	area.pos.x += area.size.x + 40;

//	sub_frame_background.type = GFX_BITMAP_SOLID;
//	sub_frame_background.data.color = GFX_COLOR(127, 0, 0);

//	sub_frame = wtk_basic_frame_create(parent, &area,
//			&sub_frame_background, sub_frame_draw_handler,
//			NULL, NULL);
//	if (!sub_frame) {
//		goto error_widget;
//	}
//	win_show(wtk_basic_frame_as_child(sub_frame));

	return;

error_widget:
	/* Destroy widget and all sub-widgets. */
	win_destroy(wtk_basic_frame_as_child(main_frame));
error_frame:
	/* Wait forever if an error occurred during setup. */
	while (1) {
	}
	
	
}

void LCDpages_doordevicepage()
{
	
}

void LCDpages_sensordevicepage()
{
	
}


