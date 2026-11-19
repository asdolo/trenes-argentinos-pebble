#include <pebble.h>
#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include "definitions.h"
#endif
#include "favorites.h"

Window *favoritos_window;
MenuLayer *menu_layer_favoritos;
static StatusBarLayer *s_status_bar_favoritos;
static char s_fav_subtitle[64];

static void draw_row_callback_favoritos(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
	(void)callback_context;

	if (favorites_count() == 0) {
		menu_cell_basic_draw(ctx, cell_layer, "Sin favoritos", "Hold Select en una estación", NULL);
		return;
	}

	const Favorite *fav = favorites_get(cell_index->row);
	if (!fav) {
		return;
	}

	snprintf(s_fav_subtitle, sizeof(s_fav_subtitle), "%s · %s",
			 getNombreLinea(fav->linea),
			 getNombreRamal(fav->linea, fav->ramal));
	menu_cell_basic_draw(ctx, cell_layer,
						 getNombreEstacion(fav->linea, fav->ramal, fav->estacion),
						 s_fav_subtitle,
						 NULL);
}

static uint16_t num_rows_callback_favoritos(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
	(void)menu_layer;
	(void)section_index;
	(void)callback_context;
	const uint8_t count = favorites_count();
	return count == 0 ? 1 : count;
}

static void select_click_callback_favoritos(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
	(void)menu_layer;
	(void)callback_context;

	if (favorites_count() == 0) {
		return;
	}

	const Favorite *fav = favorites_get(cell_index->row);
	if (!fav) {
		return;
	}

	dialog_window_info_estacion_push(fav->linea, fav->ramal, fav->estacion);
}

static void select_long_click_callback_favoritos(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
	(void)callback_context;

	if (favorites_count() == 0) {
		return;
	}

	if (!favorites_remove_at(cell_index->row)) {
		return;
	}

	vibes_short_pulse();
	menu_layer_reload_data(menu_layer);
	menu_layer_set_selected_index(menu_layer, (MenuIndex){.section = 0, .row = 0}, MenuRowAlignCenter, true);
}

static void favoritos_window_load(Window *window)
{
	Layer *window_layer = window_get_root_layer(window);

	menu_layer_favoritos = menu_layer_create(GRect(
		0,
		PBL_IF_ROUND_ELSE(0, STATUS_BAR_LAYER_HEIGHT),
		PBL_DISPLAY_WIDTH,
		PBL_IF_ROUND_ELSE(PBL_DISPLAY_HEIGHT, PBL_DISPLAY_HEIGHT - STATUS_BAR_LAYER_HEIGHT)));

	menu_layer_set_click_config_onto_window(menu_layer_favoritos, favoritos_window);

	MenuLayerCallbacks callbacks = {
		.draw_row = (MenuLayerDrawRowCallback)draw_row_callback_favoritos,
		.get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)num_rows_callback_favoritos,
		.select_click = (MenuLayerSelectCallback)select_click_callback_favoritos,
		.select_long_click = (MenuLayerSelectCallback)select_long_click_callback_favoritos,
	};
	menu_layer_set_callbacks(menu_layer_favoritos, NULL, callbacks);
	layer_add_child(window_layer, menu_layer_get_layer(menu_layer_favoritos));

	s_status_bar_favoritos = status_bar_layer_create();
	layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar_favoritos));
}

static void favoritos_window_appear(Window *window)
{
	(void)window;
	menu_layer_reload_data(menu_layer_favoritos);
}

static void favoritos_window_unload(Window *window)
{
	(void)window;
	menu_layer_destroy(menu_layer_favoritos);
	status_bar_layer_destroy(s_status_bar_favoritos);
	favoritos_window = NULL;
	menu_layer_favoritos = NULL;
}

void dialog_window_favoritos_push(void)
{
	if (!favoritos_window) {
		favoritos_window = window_create();
		window_set_background_color(favoritos_window, GColorWhite);
		window_set_window_handlers(favoritos_window, (WindowHandlers){
														 .load = favoritos_window_load,
														 .appear = favoritos_window_appear,
														 .unload = favoritos_window_unload,
													 });
	}
	window_stack_push(favoritos_window, true);
}
