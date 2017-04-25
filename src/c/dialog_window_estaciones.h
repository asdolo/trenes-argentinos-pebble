#include <pebble.h>
#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include "definitions.h"
#endif



Window* estaciones_window;
MenuLayer *menu_layer_estaciones;

static StatusBarLayer *s_status_bar_estaciones;

int linea_ramal_seleccionado;

// -- RENDERIZADO DEL MENU -- 
void draw_row_callback_estaciones(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
	switch(linea_ramal_seleccionado)
  {
    case LINEA_SARMIENTO_SARMIENTO:
		menu_cell_basic_draw(ctx, cell_layer, estaciones_sarmiento[cell_index->row], NULL, NULL);
		break;
    case LINEA_MITRE_RETIRO_TIGRE:
		menu_cell_basic_draw(ctx, cell_layer, estaciones_mitre_retiro_tigre[cell_index->row], NULL, NULL);
		break;
   case LINEA_MITRE_RETIRO_MITRE:
		menu_cell_basic_draw(ctx, cell_layer, estaciones_mitre_retiro_mitre[cell_index->row], NULL, NULL);
		break;
    case LINEA_MITRE_RETIRO_SUAREZ:
		menu_cell_basic_draw(ctx, cell_layer, estaciones_mitre_retiro_suarez[cell_index->row], NULL, NULL);
		break;
    case LINEA_ROCA_CONSTITUCION_LA_PLATA:
		break;    
    case LINEA_ROCA_CONSTITUCION_CLAYPOLE:
		break;
    case LINEA_ROCA_CLAYPOLE_GUTIERREZ:
		break;
    case LINEA_ROCA_CONSTITUCION_ALEJANDRO_KORN:
		break;
    case LINEA_ROCA_CONSTITUCION_EZEIZA:
		break;
    case LINEA_ROCA_TEMPERLEY_HAEDO:
		break;
    case LINEA_ROCA_EZEIZA_CANUELAS:
		break;
    case LINEA_BELGRANO_SUR_BUENOS_AIRES_BELGRANO:
		break;
    case LINEA_BELGRANO_PTE_ALSINA_ALDO_BONZI:
		break;
    case LINEA_BELGRANO_BUENOS_AIRES_GONZALEZ_CATAN:
		break;
    case LINEA_SAN_MARTIN_SAN_MARTIN:
		break;
    case TREN_DE_LA_COSTA_TREN_DE_LA_COSTA:
		break;
     
  }
  
}

// CANTIDAD DE COLUMNAS DEL MENU
uint16_t num_rows_callback_estaciones(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
	switch (linea_ramal_seleccionado)
	{
		case LINEA_SARMIENTO_SARMIENTO:
			return (sizeof(estaciones_sarmiento) / 32);
			break;
		case LINEA_MITRE_RETIRO_TIGRE:
			return (sizeof(estaciones_mitre_retiro_tigre) / 32);
			break;
		case LINEA_MITRE_RETIRO_MITRE:
			return (sizeof(estaciones_mitre_retiro_mitre) / 32);
			break;
		case LINEA_MITRE_RETIRO_SUAREZ:
			return (sizeof(estaciones_mitre_retiro_suarez) / 32);
			break;
		case LINEA_ROCA_CONSTITUCION_LA_PLATA:
			return 19;
			break;
		case LINEA_ROCA_CONSTITUCION_CLAYPOLE:
			return 12;
			break;
		case LINEA_ROCA_CLAYPOLE_GUTIERREZ:
			return 7;
			break;
		case LINEA_ROCA_CONSTITUCION_ALEJANDRO_KORN:
			return 15;
			break;
		case LINEA_ROCA_CONSTITUCION_EZEIZA:
			return 15;
			break;
		case LINEA_ROCA_TEMPERLEY_HAEDO:
			return 11;
			break;
		case LINEA_ROCA_EZEIZA_CANUELAS:
			return 10;
			break;
		case LINEA_BELGRANO_SUR_BUENOS_AIRES_BELGRANO:
			return 17;
			break;
		case LINEA_BELGRANO_PTE_ALSINA_ALDO_BONZI:
			return 8;
			break;
		case LINEA_BELGRANO_BUENOS_AIRES_GONZALEZ_CATAN:
			return 14;
			break;
		case LINEA_SAN_MARTIN_SAN_MARTIN:
			return 22;
			break;
		case TREN_DE_LA_COSTA_TREN_DE_LA_COSTA:
			return 11;
			break;
		default:
			return 0;
			break;
	}	  
}

// CLICK LISTENER
void select_click_callback_estaciones(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{ 
	int indiceEstacion = cell_index->row;
	dialog_window_info_estacion_push(linea_ramal_seleccionado, indiceEstacion);
}

void estaciones_window_load(Window *window)
{
	Layer *window_layer = window_get_root_layer(estaciones_window);
	
	menu_layer_estaciones = menu_layer_create(GRect(0, PBL_IF_ROUND_ELSE(0, 14),PBL_IF_ROUND_ELSE(180, 144), PBL_IF_ROUND_ELSE(180-16,168-16)));

	menu_layer_set_click_config_onto_window(menu_layer_estaciones, estaciones_window);

	MenuLayerCallbacks callbacks = 
	{
		.draw_row = (MenuLayerDrawRowCallback) draw_row_callback_estaciones,
		.get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback_estaciones,
		.select_click = (MenuLayerSelectCallback) select_click_callback_estaciones
	};
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

void dialog_window_estaciones_push(int ramal_linea) {	
 
  linea_ramal_seleccionado = ramal_linea;
    
  if(!estaciones_window) 
	{
		estaciones_window = window_create();
		window_set_background_color(estaciones_window, GColorWhite);
		window_set_window_handlers(estaciones_window, (WindowHandlers) 
	{
		.load = estaciones_window_load,
		.unload = estaciones_window_unload,        
	});
	}
	window_stack_push(estaciones_window, true);
}