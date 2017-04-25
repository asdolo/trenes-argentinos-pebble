/* -------------------------------------- *
 * Subte Buenos Aires (pebble)            *
 * v0.6                                   *
 *										  *
 * main.c <-- menu principal 			  *
 *										  *
 * Benjamin Smith                         *
 * -------------------------------------- */

#include <pebble.h>
#include "dialog_window_info_estacion.h"
#include "dialog_window_estaciones.h"
#include "dialog_window_ramales.h"

#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include "definitions.h"
#endif


Window* window;
MenuLayer *menu_layer;

static StatusBarLayer *s_status_bar;//como estoy usando sdk3 tengo que agregar la "status bar"

// -- COSOS PARA CREAR EL MENU -- 
void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  menu_cell_basic_draw(ctx, cell_layer, lineas_trenes[cell_index->row], NULL, NULL);    
}

uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
	return (sizeof(lineas_trenes)/32); // Cantidad de lineas de trenes
}

void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{ 
	switch(cell_index->row)
	{
		case 0: // Linea Sarmiento, no tiene ramales
    case 4: // Linea San Martin, no tiene ramales
    case 5: // Tren de la Costa, no tiene ramales
      dialog_window_estaciones_push(cell_index->row); // Abro ventana de estaciones
		break;
		case 1: // Linea Mitre, tiene ramales
    case 2: // Linea Roca, tiene ramales
    case 3: // Linea Roca, tiene ramales
      dialog_window_ramales_push(cell_index->row); // Abro ventana de ramales    
		break;
	}
  
}

// -- COSOS PARA CARGAR LA PANTALLA PRINCIPAL --
void window_load(Window *window)
{
	//coso para hora 
	Layer *window_layer = window_get_root_layer(window);
	//creo menu (puse 0,14 para dejar espacio para la status bar)
	menu_layer = menu_layer_create(GRect(0, PBL_IF_ROUND_ELSE(0, 14),PBL_IF_ROUND_ELSE(180, 144), PBL_IF_ROUND_ELSE(180-16,168-16)));

	//para clicks...
	menu_layer_set_click_config_onto_window(menu_layer, window);

	//todos los callbacks del menu...
	MenuLayerCallbacks callbacks = 
	{
		.draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
		.get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
		.select_click = (MenuLayerSelectCallback) select_click_callback
	};
	menu_layer_set_callbacks(menu_layer, NULL, callbacks);
	//agrego el menu a la window
	layer_add_child(window_get_root_layer(window), menu_layer_get_layer(menu_layer));
	//para la status bar (lo pongo hasta el final para que quede arriba de las otras  layers)
	s_status_bar = status_bar_layer_create();
	layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar));
}
// ------------------------------------------------------
void window_unload(Window *window)
{
 //por ahora creo que no va nada aca...
}

void init()
{
	window = window_create();
	WindowHandlers handlers = 
	{
		.load = window_load,
		.unload = window_unload
	};
	//-----------------------------------------
	//cosos para comunicarme con el celu
	app_message_register_inbox_received(in_received_handler);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());  
	//-----------------------------------------  
	window_set_window_handlers(window, (WindowHandlers) handlers);
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