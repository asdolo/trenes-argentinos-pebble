#include <pebble.h>
#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include "definitions.h"
#endif

Window *estaciones_window;
MenuLayer *menu_layer_estaciones;

static StatusBarLayer *s_status_bar_estaciones;

int lineaID;
int ramalID;

// -- RENDERIZADO DEL MENU --
void draw_row_callback_estaciones(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
	menu_cell_basic_draw(ctx, cell_layer, getNombreEstacion(lineaID, ramalID, cell_index->row), NULL, NULL);
}

// CANTIDAD DE FILAS DEL MENU
uint16_t num_rows_callback_estaciones(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
	return cant_estaciones[lineaID][ramalID];
}

// CLICK LISTENER
void select_click_callback_estaciones(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
	dialog_window_info_estacion_push(lineaID, ramalID, cell_index->row);
}

void estaciones_window_load(Window *window)
{
	Layer *window_layer = window_get_root_layer(estaciones_window);

	menu_layer_estaciones = menu_layer_create(GRect(0, PBL_IF_ROUND_ELSE(0, 14), PBL_IF_ROUND_ELSE(180, 144), PBL_IF_ROUND_ELSE(180 - 16, 168 - 16)));

	menu_layer_set_click_config_onto_window(menu_layer_estaciones, estaciones_window);

	MenuLayerCallbacks callbacks =
		{
			.draw_row = (MenuLayerDrawRowCallback)draw_row_callback_estaciones,
			.get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)num_rows_callback_estaciones,
			.select_click = (MenuLayerSelectCallback)select_click_callback_estaciones};
	menu_layer_set_callbacks(menu_layer_estaciones, NULL, callbacks);

	layer_add_child(window_get_root_layer(estaciones_window), menu_layer_get_layer(menu_layer_estaciones));

	// barra de la hora actual/status bar
	s_status_bar_estaciones = status_bar_layer_create();
	layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar_estaciones));
}

/* Un-load all Window sub-elements */
void estaciones_window_unload(Window *window)
{
}

void dialog_window_estaciones_push(int linea_id, int ramal_id)
{

	lineaID = linea_id;
	ramalID = ramal_id;

	if (!estaciones_window)
	{
		estaciones_window = window_create();
		window_set_background_color(estaciones_window, GColorWhite);
		window_set_window_handlers(estaciones_window, (WindowHandlers){
														  .load = estaciones_window_load,
														  .unload = estaciones_window_unload,
													  });
	}
	window_stack_push(estaciones_window, true);
}