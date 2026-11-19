/* -------------------------------------- *
 * Trenes Argentinos (pebble)             *
 *										  *
 * main.c <-- menu principal 			  *
 * -------------------------------------- */

#include <pebble.h>
#include "dialog_window_info_estacion.h"
#include "dialog_window_estaciones.h"
#include "dialog_window_ramales.h"
#include "dialog_window_favoritos.h"

#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include "definitions.h"
#endif

Window *window;
MenuLayer *menu_layer;

static StatusBarLayer *s_status_bar;

enum {
	MAIN_ROW_FAVORITOS = 0,
	MAIN_ROW_LINES_OFFSET = 1,
};

void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
	(void)callback_context;

	if (cell_index->row == MAIN_ROW_FAVORITOS) {
		menu_cell_basic_draw(ctx, cell_layer, "Favoritos", NULL, NULL);
		return;
	}

	menu_cell_basic_draw(ctx, cell_layer, nombres_lineas[cell_index->row - MAIN_ROW_LINES_OFFSET], NULL, NULL);
}

uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
	(void)menu_layer;
	(void)section_index;
	(void)callback_context;
	return MAIN_ROW_LINES_OFFSET + CANT_LINEAS;
}

void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
	(void)menu_layer;
	(void)callback_context;

	if (cell_index->row == MAIN_ROW_FAVORITOS) {
		dialog_window_favoritos_push();
		return;
	}

	dialog_window_ramales_push(cell_index->row - MAIN_ROW_LINES_OFFSET);
}

void window_load(Window *window)
{
	Layer *window_layer = window_get_root_layer(window);
	menu_layer = menu_layer_create(GRect(
		0,
		PBL_IF_ROUND_ELSE(0, STATUS_BAR_LAYER_HEIGHT),
		PBL_DISPLAY_WIDTH,
		PBL_IF_ROUND_ELSE(PBL_DISPLAY_HEIGHT, PBL_DISPLAY_HEIGHT - STATUS_BAR_LAYER_HEIGHT)));

	menu_layer_set_click_config_onto_window(menu_layer, window);

	MenuLayerCallbacks callbacks = {
		.draw_row = (MenuLayerDrawRowCallback)draw_row_callback,
		.get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)num_rows_callback,
		.select_click = (MenuLayerSelectCallback)select_click_callback};
	menu_layer_set_callbacks(menu_layer, NULL, callbacks);
	layer_add_child(window_get_root_layer(window), menu_layer_get_layer(menu_layer));

	s_status_bar = status_bar_layer_create();
	layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar));
}

void window_unload(Window *window)
{
	(void)window;
}

void init()
{
	favorites_load();

	window = window_create();
	WindowHandlers handlers = {
		.load = window_load,
		.unload = window_unload};

	app_message_register_inbox_received(in_received_handler);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

#if defined(PBL_TOUCH)
	app_touch_navigation_enable(true);
#endif
	window_set_window_handlers(window, (WindowHandlers)handlers);
	window_stack_push(window, true);
}

void deinit()
{
	menu_layer_destroy(menu_layer);
	status_bar_layer_destroy(s_status_bar);
	window_destroy(window);
}

int main(void)
{
	init();
	app_event_loop();
	deinit();
}
