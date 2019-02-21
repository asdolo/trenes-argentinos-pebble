#include <pebble.h>

#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include "definitions.h"
#endif

Window *estacion_window;

TextLayer *text_layer_nombre_estacion;
TextLayer *text_layer_nombre_linea;
TextLayer *text_layer_cabecera1;
TextLayer *text_layer_posiciones1_1;
TextLayer *text_layer_posiciones2_1;
TextLayer *text_layer_posiciones3_1;
TextLayer *text_layer_horario1_sentido1;
TextLayer *text_layer_horario2_sentido1;
TextLayer *text_layer_horario3_sentido1;
TextLayer *text_layer_cabecera2;
TextLayer *text_layer_posiciones1_2;
TextLayer *text_layer_posiciones2_2;
TextLayer *text_layer_posiciones3_2;
TextLayer *text_layer_horario1_sentido2;
TextLayer *text_layer_horario2_sentido2;
TextLayer *text_layer_horario3_sentido2;
TextLayer *text_layer_ultima_actualizacion;

static StatusBarLayer *s_status_bar_estacion; //como estoy usando sdk3 tengo que agregar la "status bar"

int lineaID;
int ramalID;
int estacionID;

char ultima_actualizacion[64] = "Últ. actualización:   -";
char t1_sentido1_buffer[64], t2_sentido1_buffer[64], t3_sentido1_buffer[64];
char t1_sentido2_buffer[64], t2_sentido2_buffer[64], t3_sentido2_buffer[64];

static void update_time()
{
    // Get a tm structure
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);

    // Create a long-lived buffer
    static char buffer[] = "00:00";

    // Write the current hours and minutes into the buffer
    if (clock_is_24h_style() == true)
    {
        // Use 24 hour format
        strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
    }
    else
    {
        // Use 12 hour format
        strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
    }

    // Refresh the latest update time
    strcpy(ultima_actualizacion + 22, buffer);
    text_layer_set_text(text_layer_ultima_actualizacion, ultima_actualizacion);
}

// -- COSOS PARA CUANDO RECIBO UN MENSAJE --
void process_tuple(Tuple *t)
{
    //tomo la key
    int key = t->key;

    //decido que hacer
    switch (key)
    {
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

    //obtengo data
    Tuple *t = dict_read_first(iter);
    while (t != NULL)
    {
        process_tuple(t);

        //el siguiente
        t = dict_read_next(iter);
    }

    // Refresco la última vez que se actualizaron los datos
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
    //Every 30 seconds
    if (tick_time->tm_sec % 30 == 0)
    {
        request_tiempos();
    }
}

void estacion_window_load(Window *window)
{
    // Seteo un timer que llama a tick_callback cada un segundo
    tick_timer_service_subscribe(SECOND_UNIT, tick_callback);

    Layer *window_layer = window_get_root_layer(estacion_window);

    // barra de la hora actual/status bar
    s_status_bar_estacion = status_bar_layer_create();
    layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar_estacion));

    text_layer_nombre_estacion = text_layer_create(GRect(0, 16, 144, 16));
    text_layer_set_background_color(text_layer_nombre_estacion, GColorBlack);
    text_layer_set_text_color(text_layer_nombre_estacion, GColorWhite);
    layer_add_child(window_layer, (Layer *)text_layer_nombre_estacion);

    text_layer_nombre_linea = text_layer_create(GRect(0, 16 + 16, 144, 16));
    text_layer_set_background_color(text_layer_nombre_linea, GColorBlack);
    text_layer_set_text_color(text_layer_nombre_linea, GColorWhite);
    layer_add_child(window_layer, (Layer *)text_layer_nombre_linea);

    text_layer_cabecera1 = text_layer_create(GRect(0, 16 + 16 + 16, 144, 16));
    text_layer_set_background_color(text_layer_cabecera1, GColorBlack);
    text_layer_set_text_color(text_layer_cabecera1, GColorWhite);
    layer_add_child(window_layer, (Layer *)text_layer_cabecera1);

    text_layer_posiciones1_1 = text_layer_create(GRect(0, 16 + 16 + 16 + 16, 48, 16));
    text_layer_set_background_color(text_layer_posiciones1_1, GColorWhite);
    text_layer_set_text_color(text_layer_posiciones1_1, GColorBlack);
    layer_add_child(window_layer, (Layer *)text_layer_posiciones1_1);

    text_layer_posiciones2_1 = text_layer_create(GRect(48, 16 + 16 + 16 + 16, 48, 16));
    text_layer_set_background_color(text_layer_posiciones2_1, GColorWhite);
    text_layer_set_text_color(text_layer_posiciones2_1, GColorBlack);
    layer_add_child(window_layer, (Layer *)text_layer_posiciones2_1);

    text_layer_posiciones3_1 = text_layer_create(GRect(96, 16 + 16 + 16 + 16, 48, 16));
    text_layer_set_background_color(text_layer_posiciones3_1, GColorWhite);
    text_layer_set_text_color(text_layer_posiciones3_1, GColorBlack);
    layer_add_child(window_layer, (Layer *)text_layer_posiciones3_1);

    text_layer_horario1_sentido1 = text_layer_create(GRect(0, 16 + 16 + 16 + 16 + 16, 48, 16));
    text_layer_set_background_color(text_layer_horario1_sentido1, GColorWhite);
    text_layer_set_text_color(text_layer_horario1_sentido1, GColorBlack);
    layer_add_child(window_layer, (Layer *)text_layer_horario1_sentido1);

    text_layer_horario2_sentido1 = text_layer_create(GRect(48, 16 + 16 + 16 + 16 + 16, 48, 16));
    text_layer_set_background_color(text_layer_horario2_sentido1, GColorWhite);
    text_layer_set_text_color(text_layer_horario2_sentido1, GColorBlack);
    layer_add_child(window_layer, (Layer *)text_layer_horario2_sentido1);

    text_layer_horario3_sentido1 = text_layer_create(GRect(96, 16 + 16 + 16 + 16 + 16, 48, 16));
    text_layer_set_background_color(text_layer_horario3_sentido1, GColorWhite);
    text_layer_set_text_color(text_layer_horario3_sentido1, GColorBlack);
    layer_add_child(window_layer, (Layer *)text_layer_horario3_sentido1);

    text_layer_cabecera2 = text_layer_create(GRect(0, 16 + 16 + 16 + 16 + 16 + 16, 144, 16));
    text_layer_set_background_color(text_layer_cabecera2, GColorBlack);
    text_layer_set_text_color(text_layer_cabecera2, GColorWhite);
    layer_add_child(window_layer, (Layer *)text_layer_cabecera2);

    text_layer_posiciones1_2 = text_layer_create(GRect(0, 16 + 16 + 16 + 16 + 16 + 16 + 16, 48, 16));
    text_layer_set_background_color(text_layer_posiciones1_2, GColorWhite);
    text_layer_set_text_color(text_layer_posiciones1_2, GColorBlack);
    layer_add_child(window_layer, (Layer *)text_layer_posiciones1_2);

    text_layer_posiciones2_2 = text_layer_create(GRect(48, 16 + 16 + 16 + 16 + 16 + 16 + 16, 48, 16));
    text_layer_set_background_color(text_layer_posiciones2_2, GColorWhite);
    text_layer_set_text_color(text_layer_posiciones2_2, GColorBlack);
    layer_add_child(window_layer, (Layer *)text_layer_posiciones2_2);

    text_layer_posiciones3_2 = text_layer_create(GRect(96, 16 + 16 + 16 + 16 + 16 + 16 + 16, 48, 16));
    text_layer_set_background_color(text_layer_posiciones3_2, GColorWhite);
    text_layer_set_text_color(text_layer_posiciones3_2, GColorBlack);
    layer_add_child(window_layer, (Layer *)text_layer_posiciones3_2);

    text_layer_horario1_sentido2 = text_layer_create(GRect(0, 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16, 48, 16));
    text_layer_set_background_color(text_layer_horario1_sentido2, GColorWhite);
    text_layer_set_text_color(text_layer_horario1_sentido2, GColorBlack);
    layer_add_child(window_layer, (Layer *)text_layer_horario1_sentido2);

    text_layer_horario2_sentido2 = text_layer_create(GRect(48, 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16, 48, 16));
    text_layer_set_background_color(text_layer_horario2_sentido1, GColorWhite);
    text_layer_set_text_color(text_layer_horario2_sentido2, GColorBlack);
    layer_add_child(window_layer, (Layer *)text_layer_horario2_sentido2);

    text_layer_horario3_sentido2 = text_layer_create(GRect(96, 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16, 48, 16));
    text_layer_set_background_color(text_layer_horario3_sentido1, GColorWhite);
    text_layer_set_text_color(text_layer_horario3_sentido2, GColorBlack);
    layer_add_child(window_layer, (Layer *)text_layer_horario3_sentido2);

    text_layer_ultima_actualizacion = text_layer_create(GRect(0, 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 8, 144, 16));
    text_layer_set_background_color(text_layer_ultima_actualizacion, GColorBlack);
    text_layer_set_text_color(text_layer_ultima_actualizacion, GColorWhite);
    layer_add_child(window_layer, (Layer *)text_layer_ultima_actualizacion);
}

/* Un-load all Window sub-elements */
void estacion_window_unload(Window *window)
{

    tick_timer_service_unsubscribe(); // Importante!! Sino el timer sigue funcionando y explota todo

    text_layer_destroy(text_layer_nombre_estacion);
    text_layer_destroy(text_layer_nombre_linea);
    text_layer_destroy(text_layer_cabecera1);
    text_layer_destroy(text_layer_posiciones1_1);
    text_layer_destroy(text_layer_posiciones2_1);
    text_layer_destroy(text_layer_posiciones3_1);
    text_layer_destroy(text_layer_horario1_sentido1);
    text_layer_destroy(text_layer_horario2_sentido1);
    text_layer_destroy(text_layer_horario3_sentido1);
    text_layer_destroy(text_layer_cabecera2);
    text_layer_destroy(text_layer_posiciones1_2);
    text_layer_destroy(text_layer_posiciones2_2);
    text_layer_destroy(text_layer_posiciones3_2);
    text_layer_destroy(text_layer_horario1_sentido2);
    text_layer_destroy(text_layer_horario2_sentido2);
    text_layer_destroy(text_layer_horario3_sentido2);
    text_layer_destroy(text_layer_ultima_actualizacion);

    //window_destroy(window);
}

void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
    // Actualizo la info
    request_tiempos();
}

void click_config_provider(void *context)
{
    // Seteo el handler del botón SELECT del Pebble
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

void inicializar_textos()
{

    // Texto de última actualización
    text_layer_set_text(text_layer_ultima_actualizacion, (char *)&ultima_actualizacion);

    // Texto de línea actual
    text_layer_set_text(text_layer_nombre_linea, getNombreLinea(lineaID));

    // Texto de estación atual
    text_layer_set_text(text_layer_nombre_estacion, getNombreEstacion(lineaID, ramalID, estacionID));

    // Texto de sentido 1
    char *buffer = getNombreEstacion(lineaID, ramalID, 0);

    char *nombre_cabecera_1 = malloc(2 + strlen(buffer) + 1);
    memcpy(nombre_cabecera_1, "A ", 2);
    memcpy(nombre_cabecera_1 + 2, buffer, strlen(buffer) + 1);
    text_layer_set_text(text_layer_cabecera1, nombre_cabecera_1);

    // Texto de sentido 2
    buffer = getNombreEstacion(lineaID, ramalID, cant_estaciones[lineaID][ramalID] - 1); // cambiar 1 por el ultimo indice de la lista!!
    char *nombre_cabecera_2 = malloc(2 + strlen(buffer) + 1);
    memcpy(nombre_cabecera_2, "A ", 2);
    memcpy(nombre_cabecera_2 + 2, buffer, strlen(buffer) + 1);
    text_layer_set_text(text_layer_cabecera2, nombre_cabecera_2);
    
    free(nombre_cabecera_1);
    free(nombre_cabecera_2);

    text_layer_set_text(text_layer_posiciones1_1, "1º:");
    text_layer_set_text(text_layer_posiciones2_1, "2º:");
    text_layer_set_text(text_layer_posiciones3_1, "3º:");

    text_layer_set_text(text_layer_posiciones1_2, "1º:");
    text_layer_set_text(text_layer_posiciones2_2, "2º:");
    text_layer_set_text(text_layer_posiciones3_2, "3º:");
}

void dialog_window_info_estacion_push(int linea_id, int ramal_id, int estacion_id)
{

    lineaID = linea_id;
    ramalID = ramal_id;
    estacionID = estacion_id;

    if (!estacion_window)
    {
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

    // Pido la info por primera vez
    request_tiempos();
}
