#include <pebble.h>
#include <stdio.h>
#include <string.h>

#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include "definitions.h"
#endif
#include "favorites.h"

Window *estacion_window;

TextLayer *text_layer_nombre_estacion;
TextLayer *text_layer_cabecera1;
TextLayer *text_layer_horario1_sentido1;
TextLayer *text_layer_horario2_sentido1;
TextLayer *text_layer_horario3_sentido1;
TextLayer *text_layer_cabecera2;
TextLayer *text_layer_horario1_sentido2;
TextLayer *text_layer_horario2_sentido2;
TextLayer *text_layer_horario3_sentido2;
TextLayer *text_layer_footer;

static StatusBarLayer *s_status_bar_estacion;

int lineaID;
int ramalID;
int estacionID;

static char cabecera1_buf[LENGTH_NOMBRE_ESTACION + 4];
static char cabecera2_buf[LENGTH_NOMBRE_ESTACION + 4];
static char nombre_estacion_buf[LENGTH_NOMBRE_ESTACION + 4];
static char footer_buf[64] = "-";

static void estacion_refresh_title(void)
{
	const char *name = getNombreEstacion(lineaID, ramalID, estacionID);
	if (favorites_is_favorite(lineaID, ramalID, estacionID)) {
		snprintf(nombre_estacion_buf, sizeof(nombre_estacion_buf), "* %s", name);
	} else {
		snprintf(nombre_estacion_buf, sizeof(nombre_estacion_buf), "%s", name);
	}
	text_layer_set_text(text_layer_nombre_estacion, nombre_estacion_buf);
}

static void estacion_refresh_footer(const char *time_text)
{
	snprintf(footer_buf, sizeof(footer_buf), "%s · %s", getNombreLinea(lineaID), time_text);
	text_layer_set_text(text_layer_footer, footer_buf);
}

static void update_time()
{
	time_t temp = time(NULL);
	struct tm *tick_time = localtime(&temp);

	static char buffer[] = "00:00";

	if (clock_is_24h_style() == true) {
		strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
	} else {
		strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
	}

	estacion_refresh_footer(buffer);
}

void process_tuple(Tuple *t)
{
	int key = t->key;

	switch (key) {
	case Horario1Sentido1Response:
		text_layer_set_text(text_layer_horario1_sentido1, t->value->cstring);
		break;
	case Horario2Sentido1Response:
		text_layer_set_text(text_layer_horario2_sentido1, t->value->cstring);
		break;
	case Horario3Sentido1Response:
		text_layer_set_text(text_layer_horario3_sentido1, t->value->cstring);
		break;
	case Horario1Sentido2Response:
		text_layer_set_text(text_layer_horario1_sentido2, t->value->cstring);
		break;
	case Horario2Sentido2Response:
		text_layer_set_text(text_layer_horario2_sentido2, t->value->cstring);
		break;
	case Horario3Sentido2Response:
		text_layer_set_text(text_layer_horario3_sentido2, t->value->cstring);
		break;
	}
}

static void in_received_handler(DictionaryIterator *iter, void *context)
{
	(void)context;

	Tuple *t = dict_read_first(iter);
	while (t != NULL) {
		process_tuple(t);
		t = dict_read_next(iter);
	}

	update_time();
}

void request_tiempos()
{
	DictionaryIterator *iter;
	app_message_outbox_begin(&iter);

	dict_write_int(iter, LineaRequest, &lineaID, sizeof(int), true);
	dict_write_int(iter, RamalRequest, &ramalID, sizeof(int), true);
	dict_write_int(iter, EstacionRequest, &estacionID, sizeof(int), true);
	dict_write_end(iter);

	app_message_outbox_send();
}

void tick_callback(struct tm *tick_time, TimeUnits units_changed)
{
	(void)units_changed;
	if (tick_time->tm_sec % 30 == 0) {
		request_tiempos();
	}
}

static TextLayer *estacion_make_label(GRect frame, GColor bg, GColor fg, GFont font, GTextAlignment align)
{
	TextLayer *layer = text_layer_create(frame);
	text_layer_set_background_color(layer, bg);
	text_layer_set_text_color(layer, fg);
	text_layer_set_font(layer, font);
	text_layer_set_text_alignment(layer, align);
	text_layer_set_overflow_mode(layer, GTextOverflowModeTrailingEllipsis);
	return layer;
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
	(void)recognizer;
	(void)context;
	request_tiempos();
}

static void select_long_click_handler(ClickRecognizerRef recognizer, void *context)
{
	(void)recognizer;
	(void)context;

	const bool now_favorite = favorites_toggle(lineaID, ramalID, estacionID);
	estacion_refresh_title();
	if (now_favorite) {
		vibes_double_pulse();
	} else {
		vibes_short_pulse();
	}
}

void click_config_provider(void *context)
{
	(void)context;
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_long_click_subscribe(BUTTON_ID_SELECT, 700, select_long_click_handler, NULL);
}

void estacion_window_load(Window *window)
{
	tick_timer_service_subscribe(SECOND_UNIT, tick_callback);

	Layer *window_layer = window_get_root_layer(window);
	const GRect bounds = layer_get_bounds(window_layer);
	const int width = bounds.size.w;
	const int top = PBL_IF_ROUND_ELSE(0, STATUS_BAR_LAYER_HEIGHT);
	const int view_h = bounds.size.h - top;
	const int col = width / 3;

	// 6 bands fill the screen: station, dir1, times1, dir2, times2, footer.
	const int rows = 6;
	const int row = view_h / rows;
	const GFont font = fonts_get_system_font(
		row >= 24 ? FONT_KEY_GOTHIC_18_BOLD : FONT_KEY_GOTHIC_14_BOLD);
	const GFont font_plain = fonts_get_system_font(
		row >= 24 ? FONT_KEY_GOTHIC_18 : FONT_KEY_GOTHIC_14);

	s_status_bar_estacion = status_bar_layer_create();
	layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar_estacion));

	int y = top;

	text_layer_nombre_estacion = estacion_make_label(GRect(0, y, width, row), GColorBlack, GColorWhite, font, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(text_layer_nombre_estacion));
	y += row;

	text_layer_cabecera1 = estacion_make_label(GRect(0, y, width, row), GColorBlack, GColorWhite, font, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(text_layer_cabecera1));
	y += row;

	text_layer_horario1_sentido1 = estacion_make_label(GRect(0, y, col, row), GColorWhite, GColorBlack, font_plain, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(text_layer_horario1_sentido1));
	text_layer_horario2_sentido1 = estacion_make_label(GRect(col, y, col, row), GColorWhite, GColorBlack, font_plain, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(text_layer_horario2_sentido1));
	text_layer_horario3_sentido1 = estacion_make_label(GRect(col * 2, y, width - col * 2, row), GColorWhite, GColorBlack, font_plain, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(text_layer_horario3_sentido1));
	y += row;

	text_layer_cabecera2 = estacion_make_label(GRect(0, y, width, row), GColorBlack, GColorWhite, font, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(text_layer_cabecera2));
	y += row;

	text_layer_horario1_sentido2 = estacion_make_label(GRect(0, y, col, row), GColorWhite, GColorBlack, font_plain, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(text_layer_horario1_sentido2));
	text_layer_horario2_sentido2 = estacion_make_label(GRect(col, y, col, row), GColorWhite, GColorBlack, font_plain, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(text_layer_horario2_sentido2));
	text_layer_horario3_sentido2 = estacion_make_label(GRect(col * 2, y, width - col * 2, row), GColorWhite, GColorBlack, font_plain, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(text_layer_horario3_sentido2));
	y += row;

	text_layer_footer = estacion_make_label(GRect(0, y, width, bounds.size.h - y), GColorBlack, GColorWhite, font_plain, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(text_layer_footer));
}

void estacion_window_unload(Window *window)
{
	(void)window;

	tick_timer_service_unsubscribe();

	text_layer_destroy(text_layer_nombre_estacion);
	text_layer_destroy(text_layer_cabecera1);
	text_layer_destroy(text_layer_horario1_sentido1);
	text_layer_destroy(text_layer_horario2_sentido1);
	text_layer_destroy(text_layer_horario3_sentido1);
	text_layer_destroy(text_layer_cabecera2);
	text_layer_destroy(text_layer_horario1_sentido2);
	text_layer_destroy(text_layer_horario2_sentido2);
	text_layer_destroy(text_layer_horario3_sentido2);
	text_layer_destroy(text_layer_footer);
	status_bar_layer_destroy(s_status_bar_estacion);
}

void inicializar_textos()
{
	estacion_refresh_title();
	estacion_refresh_footer("--:--");

	snprintf(cabecera1_buf, sizeof(cabecera1_buf), "A %s", getNombreEstacion(lineaID, ramalID, 0));
	text_layer_set_text(text_layer_cabecera1, cabecera1_buf);

	snprintf(cabecera2_buf, sizeof(cabecera2_buf), "A %s",
			 getNombreEstacion(lineaID, ramalID, cant_estaciones[lineaID][ramalID] - 1));
	text_layer_set_text(text_layer_cabecera2, cabecera2_buf);

	// Columns are 1º / 2º / 3º left to right.
	text_layer_set_text(text_layer_horario1_sentido1, "1º");
	text_layer_set_text(text_layer_horario2_sentido1, "2º");
	text_layer_set_text(text_layer_horario3_sentido1, "3º");
	text_layer_set_text(text_layer_horario1_sentido2, "1º");
	text_layer_set_text(text_layer_horario2_sentido2, "2º");
	text_layer_set_text(text_layer_horario3_sentido2, "3º");
}

void dialog_window_info_estacion_push(int linea_id, int ramal_id, int estacion_id)
{
	lineaID = linea_id;
	ramalID = ramal_id;
	estacionID = estacion_id;

	if (!estacion_window) {
		estacion_window = window_create();
		window_set_background_color(estacion_window, GColorWhite);
		window_set_click_config_provider(estacion_window, click_config_provider);
		window_set_window_handlers(estacion_window, (WindowHandlers){
														.load = estacion_window_load,
														.unload = estacion_window_unload,
													});
	}

	window_stack_push(estacion_window, true);
	inicializar_textos();
	request_tiempos();
}
