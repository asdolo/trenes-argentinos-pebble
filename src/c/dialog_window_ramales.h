#include <pebble.h>
#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include "definitions.h"
#endif

Window *ramales_window;
MenuLayer *menu_layer_ramales;

static StatusBarLayer *s_status_bar_ramales; //como estoy usando sdk3 tengo que agregar la "status bar"

int lineaID;

// -- RENDERIZADO DEL MENU --
void draw_row_callback_ramales(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
	menu_cell_basic_draw(ctx, cell_layer, getNombreRamal(lineaID, cell_index->row), NULL, NULL);
}

// CANTIDAD DE FILAS DEL MENU
uint16_t num_rows_callback_ramales(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
	return cant_ramales[lineaID];
}

// CLICK LISTENER
void select_click_callback_ramales(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
	dialog_window_estaciones_push(lineaID, cell_index->row); // Abro ventana de estaciones
}

void ramales_window_load(Window *estado_window)
{
	Layer *window_layer = window_get_root_layer(ramales_window);

	menu_layer_ramales = menu_layer_create(GRect(0, PBL_IF_ROUND_ELSE(0, 14), PBL_IF_ROUND_ELSE(180, 144), PBL_IF_ROUND_ELSE(180 - 16, 168 - 16)));

	//para clicks...
	menu_layer_set_click_config_onto_window(menu_layer_ramales, ramales_window);

	//todos los callbacks del menu...
	MenuLayerCallbacks callbacks =
		{
			.draw_row = (MenuLayerDrawRowCallback)draw_row_callback_ramales,
			.get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)num_rows_callback_ramales,
			.select_click = (MenuLayerSelectCallback)select_click_callback_ramales};
	menu_layer_set_callbacks(menu_layer_ramales, NULL, callbacks);

	layer_add_child(window_get_root_layer(estado_window), menu_layer_get_layer(menu_layer_ramales));

	// barra de la hora actual/status bar
	s_status_bar_ramales = status_bar_layer_create();
	layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar_ramales));
}

/* Un-load all Window sub-elements */
void ramales_window_unload(Window *window)
{
}

void dialog_window_ramales_push(int linea_id)
{
 	lineaID = linea_id;

	if (!ramales_window)
	{
		ramales_window = window_create();
		window_set_background_color(ramales_window, GColorWhite);
		window_set_window_handlers(ramales_window, (WindowHandlers){
													   .load = ramales_window_load,
													   .unload = ramales_window_unload,
												   });
	}
	window_stack_push(ramales_window, true);
}