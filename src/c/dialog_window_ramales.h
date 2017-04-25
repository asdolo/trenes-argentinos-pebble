#include <pebble.h>
#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include "definitions.h"
#endif

Window* ramales_window;
MenuLayer *menu_layer_ramales;

static StatusBarLayer *s_status_bar_ramales; //como estoy usando sdk3 tengo que agregar la "status bar"

int lineaSeleccionada;

// -- RENDERIZADO DEL MENU -- 
void draw_row_callback_ramales(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
	switch(lineaSeleccionada)
	{
		case LINEA_MITRE:
			menu_cell_basic_draw(ctx, cell_layer, ramales_mitre[cell_index->row], NULL, NULL);
			break;
		case LINEA_ROCA:
			menu_cell_basic_draw(ctx, cell_layer, ramales_roca[cell_index->row], NULL, NULL);
			break;
		case LINEA_BELGRANO_SUR:
			menu_cell_basic_draw(ctx, cell_layer, ramales_belgrano_sur[cell_index->row], NULL, NULL);
			break;
	}
  
}

// CANTIDAD DE COLUMNAS DEL MENU
uint16_t num_rows_callback_ramales(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
	switch (lineaSeleccionada)
	{
		case LINEA_MITRE:
			return (sizeof(ramales_mitre) / 32);
			break;
		case LINEA_ROCA:
			return (sizeof(ramales_roca) / 32);
			break;
		case LINEA_BELGRANO_SUR:
			return (sizeof(ramales_belgrano_sur) / 32);
			break;
		default:
			return 0;
			break;
	}	
}

// CLICK LISTENER
void select_click_callback_ramales(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{ 
	switch(lineaSeleccionada)
	{
		case LINEA_MITRE:
			switch(cell_index->row)
			{
				case 0:
					dialog_window_estaciones_push(LINEA_MITRE_RETIRO_TIGRE); // Abro ventana de estaciones
					break;
				case 1:
					dialog_window_estaciones_push(LINEA_MITRE_RETIRO_MITRE); // Abro ventana de estaciones
					break;
				case 2:
					dialog_window_estaciones_push(LINEA_MITRE_RETIRO_SUAREZ); // Abro ventana de estaciones
					break;              
			}
			break;

		case LINEA_ROCA:
			switch(cell_index->row)
			{
				case 0:
					dialog_window_estaciones_push(LINEA_ROCA_CONSTITUCION_LA_PLATA); // Abro ventana de estaciones
					break;
				case 1:
					dialog_window_estaciones_push(LINEA_ROCA_CONSTITUCION_CLAYPOLE); // Abro ventana de estaciones
					break;
				case 2:
					dialog_window_estaciones_push(LINEA_ROCA_CLAYPOLE_GUTIERREZ); // Abro ventana de estaciones
					break;
				case 3:
					dialog_window_estaciones_push(LINEA_ROCA_CONSTITUCION_ALEJANDRO_KORN); // Abro ventana de estaciones
					break;
				case 4:
					dialog_window_estaciones_push(LINEA_ROCA_CONSTITUCION_EZEIZA); // Abro ventana de estaciones
					break;
				case 5:
					dialog_window_estaciones_push(LINEA_ROCA_TEMPERLEY_HAEDO); // Abro ventana de estaciones
					break;
				case 6:
					dialog_window_estaciones_push(LINEA_ROCA_EZEIZA_CANUELAS); // Abro ventana de estaciones
					break; 
			}
			break;

		case LINEA_BELGRANO_SUR:
			switch(cell_index->row)
			{
				case 0:
					dialog_window_estaciones_push(LINEA_BELGRANO_SUR_BUENOS_AIRES_BELGRANO); // Abro ventana de estaciones
					break;
				case 1:
					dialog_window_estaciones_push(LINEA_BELGRANO_PTE_ALSINA_ALDO_BONZI); // Abro ventana de estaciones
					break;
				case 2:
					dialog_window_estaciones_push(LINEA_BELGRANO_BUENOS_AIRES_GONZALEZ_CATAN); // Abro ventana de estaciones
					break;              
			}
			break;
	}
 
}

void ramales_window_load(Window *estado_window)
{
	Layer *window_layer = window_get_root_layer(ramales_window);
	
	menu_layer_ramales = menu_layer_create(GRect(0, PBL_IF_ROUND_ELSE(0, 14),PBL_IF_ROUND_ELSE(180, 144), PBL_IF_ROUND_ELSE(180-16,168-16)));

	//para clicks...
	menu_layer_set_click_config_onto_window(menu_layer_ramales, ramales_window);

	//todos los callbacks del menu...
	MenuLayerCallbacks callbacks = 
	{
		.draw_row = (MenuLayerDrawRowCallback) draw_row_callback_ramales,
		.get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback_ramales,
		.select_click = (MenuLayerSelectCallback) select_click_callback_ramales
	};
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

void dialog_window_ramales_push(int linea) {
	
  lineaSeleccionada = linea;
  
	if(!ramales_window) 
	{
		ramales_window = window_create();
		window_set_background_color(ramales_window, GColorWhite);
		window_set_window_handlers(ramales_window, (WindowHandlers) 
	{
		.load = ramales_window_load,
		.unload = ramales_window_unload,        
	});
	}
	window_stack_push(ramales_window, true);
}