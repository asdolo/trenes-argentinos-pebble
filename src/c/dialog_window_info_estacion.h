#include <pebble.h>

#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include "definitions.h"
#endif

Window* estacion_window;

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


int linea_for_url;
int estacion_elegida;

char ultima_actualizacion[64] = "Últ. actualización:   -";
char t1_sentido1_buffer[64], t2_sentido1_buffer[64], t3_sentido1_buffer[64];
char t1_sentido2_buffer[64], t2_sentido2_buffer[64], t3_sentido2_buffer[64];

static void update_time() {
    // Get a tm structure
    time_t temp = time(NULL); 
    struct tm *tick_time = localtime(&temp);

    // Create a long-lived buffer
    static char buffer[] = "00:00";

    // Write the current hours and minutes into the buffer
    if(clock_is_24h_style() == true) {
        // Use 24 hour format
        strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
    } else {
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
  APP_LOG(APP_LOG_LEVEL_DEBUG, "process_tuple");
  
	//tomo la key
	int key = t->key;
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "string_value = %s", t->value->cstring);
  
	//decido que hacer 
	switch(key) 
	{
		case KEY_RESPUESTA_HORARIO1_SENTIDO1:
			text_layer_set_text(text_layer_horario1_sentido1, t->value->cstring);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Escribí %s en text_layer_horario1_sentido1", t->value->cstring);
			break;
    case KEY_RESPUESTA_HORARIO2_SENTIDO1:
			text_layer_set_text(text_layer_horario2_sentido1, t->value->cstring);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Escribí %s en text_layer_horario2_sentido1", t->value->cstring);
			break;
    case KEY_RESPUESTA_HORARIO3_SENTIDO1:
			text_layer_set_text(text_layer_horario3_sentido1, t->value->cstring);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Escribí %s en text_layer_horario3_sentido1", t->value->cstring);
			break;
    case KEY_RESPUESTA_HORARIO1_SENTIDO2:
			text_layer_set_text(text_layer_horario1_sentido2, t->value->cstring);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Escribí %s en text_layer_horario1_sentido2", t->value->cstring);
			break;
    case KEY_RESPUESTA_HORARIO2_SENTIDO2:
			text_layer_set_text(text_layer_horario2_sentido2, t->value->cstring);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Escribí %s en text_layer_horario2_sentido2", t->value->cstring);
			break;
    case KEY_RESPUESTA_HORARIO3_SENTIDO2:
			text_layer_set_text(text_layer_horario3_sentido2, t->value->cstring);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Escribí %s en text_layer_horario3_sentido2", t->value->cstring);
			break;
	}
  
}

static void in_received_handler(DictionaryIterator *iter, void *context)
{
  APP_LOG(APP_LOG_LEVEL_DEBUG, "in_received_handler");

	(void) context;
	 
	//obtengo data
	Tuple *t = dict_read_first(iter);
	while(t != NULL)
	{
		process_tuple(t);
		 
		//el siguiente
		t = dict_read_next(iter);
	}
  
  // Refresco la última vez que se actualizaron los datos
  update_time();
	
}




void send_ints(int value1, int value2)
{
	DictionaryIterator *iter;
 	app_message_outbox_begin(&iter);
 	
 	dict_write_int(iter, KEY_CONSULTA_RAMAL_COMPLETO, &value1, sizeof(int), true);
  dict_write_int(iter, KEY_CONSULTA_ESTACION_PARTICULAR, &value2, sizeof(int), true);
 	dict_write_end(iter);
  
 	app_message_outbox_send();
}




void tick_callback(struct tm *tick_time, TimeUnits units_changed)
{
	
	//Every 30 seconds
	if(tick_time->tm_sec % 30 == 0)
	{
		send_ints(linea_for_url,estacion_elegida);
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
	layer_add_child(window_layer, (Layer*) text_layer_nombre_estacion);
  
	text_layer_nombre_linea = text_layer_create(GRect(0, 16+16, 144, 16));
	text_layer_set_background_color(text_layer_nombre_linea, GColorBlack);
	text_layer_set_text_color(text_layer_nombre_linea, GColorWhite);
	layer_add_child(window_layer, (Layer*) text_layer_nombre_linea);
                  
	text_layer_cabecera1 = text_layer_create(GRect(0, 16+16+16, 144, 16));
	text_layer_set_background_color(text_layer_cabecera1, GColorBlack);
	text_layer_set_text_color(text_layer_cabecera1, GColorWhite);
	layer_add_child(window_layer, (Layer*) text_layer_cabecera1);
    
	text_layer_posiciones1_1 = text_layer_create(GRect(0, 16+16+16+16, 48, 16));
	text_layer_set_background_color(text_layer_posiciones1_1, GColorWhite);
	text_layer_set_text_color(text_layer_posiciones1_1, GColorBlack);
	layer_add_child(window_layer, (Layer*) text_layer_posiciones1_1);
  
	text_layer_posiciones2_1 = text_layer_create(GRect(48, 16+16+16+16, 48, 16));
	text_layer_set_background_color(text_layer_posiciones2_1, GColorWhite);
	text_layer_set_text_color(text_layer_posiciones2_1, GColorBlack);
	layer_add_child(window_layer, (Layer*) text_layer_posiciones2_1);
  
	text_layer_posiciones3_1 = text_layer_create(GRect(96, 16+16+16+16, 48, 16));
	text_layer_set_background_color(text_layer_posiciones3_1, GColorWhite);
	text_layer_set_text_color(text_layer_posiciones3_1, GColorBlack);
	layer_add_child(window_layer, (Layer*) text_layer_posiciones3_1);
  
	text_layer_horario1_sentido1 = text_layer_create(GRect(0, 16+16+16+16+16, 48, 16));
	text_layer_set_background_color(text_layer_horario1_sentido1, GColorWhite);
	text_layer_set_text_color(text_layer_horario1_sentido1, GColorBlack);
	layer_add_child(window_layer, (Layer*) text_layer_horario1_sentido1);
  
	text_layer_horario2_sentido1 = text_layer_create(GRect(48, 16+16+16+16+16, 48, 16));
	text_layer_set_background_color(text_layer_horario2_sentido1, GColorWhite);
	text_layer_set_text_color(text_layer_horario2_sentido1, GColorBlack);
	layer_add_child(window_layer, (Layer*) text_layer_horario2_sentido1);
  
	text_layer_horario3_sentido1 = text_layer_create(GRect(96, 16+16+16+16+16, 48, 16));
	text_layer_set_background_color(text_layer_horario3_sentido1, GColorWhite);
	text_layer_set_text_color(text_layer_horario3_sentido1, GColorBlack);
	layer_add_child(window_layer, (Layer*) text_layer_horario3_sentido1);
  
	text_layer_cabecera2 = text_layer_create(GRect(0, 16+16+16+16+16+16, 144, 16));
	text_layer_set_background_color(text_layer_cabecera2, GColorBlack);
	text_layer_set_text_color(text_layer_cabecera2, GColorWhite);
	layer_add_child(window_layer, (Layer*) text_layer_cabecera2);
  
	text_layer_posiciones1_2 = text_layer_create(GRect(0, 16+16+16+16+16+16+16, 48, 16));
	text_layer_set_background_color(text_layer_posiciones1_2, GColorWhite);
	text_layer_set_text_color(text_layer_posiciones1_2, GColorBlack);
	layer_add_child(window_layer, (Layer*) text_layer_posiciones1_2);
  
	text_layer_posiciones2_2 = text_layer_create(GRect(48, 16+16+16+16+16+16+16, 48, 16));
	text_layer_set_background_color(text_layer_posiciones2_2, GColorWhite);
	text_layer_set_text_color(text_layer_posiciones2_2, GColorBlack);
	layer_add_child(window_layer, (Layer*) text_layer_posiciones2_2);
  
	text_layer_posiciones3_2 = text_layer_create(GRect(96, 16+16+16+16+16+16+16, 48, 16));
	text_layer_set_background_color(text_layer_posiciones3_2, GColorWhite);
	text_layer_set_text_color(text_layer_posiciones3_2, GColorBlack);
	layer_add_child(window_layer, (Layer*) text_layer_posiciones3_2);
  
	text_layer_horario1_sentido2 = text_layer_create(GRect(0, 16+16+16+16+16+16+16+16, 48, 16));
	text_layer_set_background_color(text_layer_horario1_sentido2, GColorWhite);
	text_layer_set_text_color(text_layer_horario1_sentido2, GColorBlack);
	layer_add_child(window_layer, (Layer*) text_layer_horario1_sentido2);
  
	text_layer_horario2_sentido2 = text_layer_create(GRect(48, 16+16+16+16+16+16+16+16, 48, 16));
	text_layer_set_background_color(text_layer_horario2_sentido1, GColorWhite);
	text_layer_set_text_color(text_layer_horario2_sentido2, GColorBlack);
	layer_add_child(window_layer, (Layer*) text_layer_horario2_sentido2);
  
	text_layer_horario3_sentido2 = text_layer_create(GRect(96, 16+16+16+16+16+16+16+16, 48, 16));
	text_layer_set_background_color(text_layer_horario3_sentido1, GColorWhite);
	text_layer_set_text_color(text_layer_horario3_sentido2, GColorBlack);
	layer_add_child(window_layer, (Layer*) text_layer_horario3_sentido2);
  
	text_layer_ultima_actualizacion = text_layer_create(GRect(0, 16+16+16+16+16+16+16+16+16+8, 144, 16));
	text_layer_set_background_color(text_layer_ultima_actualizacion, GColorBlack);
	text_layer_set_text_color(text_layer_ultima_actualizacion, GColorWhite);
	layer_add_child(window_layer, (Layer*) text_layer_ultima_actualizacion);
}


/* Un-load all Window sub-elements */
void estacion_window_unload(Window *window)
{
	
  tick_timer_service_unsubscribe();	// Importante!! Sino el timer sigue funcionando y explota todo
  
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


int getLineaForUrl(int linea)
{
	
	// Esto corresponde al numerito que va en la URL de la página de los trenes, lo harcodeo...
	switch (linea)
	{
		case LINEA_SARMIENTO_SARMIENTO:
			return 1;
			break;
		case LINEA_MITRE_RETIRO_TIGRE:
			return 5;
			break;
		case LINEA_MITRE_RETIRO_MITRE:
			return 7;
			break;
		case LINEA_MITRE_RETIRO_SUAREZ:
			return 9;
			break;
		case LINEA_ROCA_CONSTITUCION_LA_PLATA:
			return 11;
			break;
		case LINEA_ROCA_CONSTITUCION_CLAYPOLE:
			return 15;
			break;
		case LINEA_ROCA_TEMPERLEY_HAEDO:
			return 27;
			break;
		case LINEA_ROCA_EZEIZA_CANUELAS:
			return 37;
			break;
		case LINEA_SAN_MARTIN_SAN_MARTIN:
			return 31;
			break;
		case TREN_DE_LA_COSTA_TREN_DE_LA_COSTA:
			return 41;
			break;    

		// NI IDEA ESTOS RAMALES!!!!!!!!!!!!!!
		case LINEA_ROCA_CLAYPOLE_GUTIERREZ:
		case LINEA_ROCA_CONSTITUCION_ALEJANDRO_KORN:
		case LINEA_ROCA_CONSTITUCION_EZEIZA:
		case LINEA_BELGRANO_SUR_BUENOS_AIRES_BELGRANO:
		case LINEA_BELGRANO_PTE_ALSINA_ALDO_BONZI:
		case LINEA_BELGRANO_BUENOS_AIRES_GONZALEZ_CATAN:
			return 0;
			break;
	}
	return 0;
  
}

void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
	// Actualizo la info
	send_ints(linea_for_url, estacion_elegida);
}

void click_config_provider(void *context) 
{
	// Seteo el handler del botón SELECT del Pebble
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

void inicializar_textos(int linea, int linea_ramal, int estacion)
{
	/*
	APP_LOG(APP_LOG_LEVEL_DEBUG, "void inicializar_textos");
	APP_LOG(APP_LOG_LEVEL_DEBUG, "int linea = %d", linea);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "int linea_ramal = %d", linea_ramal);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "int estacion = %d", estacion);
	*/
	
	// Texto de última actualización
	text_layer_set_text(text_layer_ultima_actualizacion, (char*) &ultima_actualizacion);

	// Texto de línea actual
	text_layer_set_text(text_layer_nombre_linea, lineas_trenes[linea]);

	// Textos de estación actual y cabeceras
	switch(linea_ramal)
	{
		case LINEA_SARMIENTO_SARMIENTO:
			text_layer_set_text(text_layer_nombre_estacion, estaciones_sarmiento[estacion]);
			text_layer_set_text(text_layer_cabecera1, "A Moreno");
			text_layer_set_text(text_layer_cabecera2, "A Once");
			break;
		case LINEA_MITRE_RETIRO_TIGRE:
			text_layer_set_text(text_layer_nombre_estacion, estaciones_mitre_retiro_tigre[estacion]);
			text_layer_set_text(text_layer_cabecera1, "A Tigre");
			text_layer_set_text(text_layer_cabecera2, "A Retiro");
			break;
		case LINEA_MITRE_RETIRO_MITRE:
			text_layer_set_text(text_layer_nombre_estacion, estaciones_mitre_retiro_mitre[estacion]);
			text_layer_set_text(text_layer_cabecera1, "A Mitre");
			text_layer_set_text(text_layer_cabecera2, "A Retiro");
			break;
		case LINEA_MITRE_RETIRO_SUAREZ:
			text_layer_set_text(text_layer_nombre_estacion, estaciones_mitre_retiro_suarez[estacion]);
			text_layer_set_text(text_layer_cabecera1, "A J.L. Suárez");
			text_layer_set_text(text_layer_cabecera2, "A Retiro");
			break;
		case LINEA_ROCA_CONSTITUCION_LA_PLATA:

			text_layer_set_text(text_layer_cabecera1, "A La Plata");
			text_layer_set_text(text_layer_cabecera2, "A Constitución");
			break;    
		case LINEA_ROCA_CONSTITUCION_CLAYPOLE:

			text_layer_set_text(text_layer_cabecera1, "A Claypole");
			text_layer_set_text(text_layer_cabecera2, "A Constitución");
			break;
		case LINEA_ROCA_CLAYPOLE_GUTIERREZ:

			text_layer_set_text(text_layer_cabecera1, "A Gutiérrez");
			text_layer_set_text(text_layer_cabecera2, "A Claypole");
			break;
		case LINEA_ROCA_CONSTITUCION_ALEJANDRO_KORN:

			text_layer_set_text(text_layer_cabecera1, "A Alejandro Korn");
			text_layer_set_text(text_layer_cabecera2, "A Constitución");
			break;
		case LINEA_ROCA_CONSTITUCION_EZEIZA:

			text_layer_set_text(text_layer_cabecera1, "A Ezeiza");
			text_layer_set_text(text_layer_cabecera2, "A Constitución");
			break;
		case LINEA_ROCA_TEMPERLEY_HAEDO:

			text_layer_set_text(text_layer_cabecera1, "A Haedo");
			text_layer_set_text(text_layer_cabecera2, "A Temperley");
			break;
		case LINEA_ROCA_EZEIZA_CANUELAS:

			text_layer_set_text(text_layer_cabecera1, "A Cañuelas");
			text_layer_set_text(text_layer_cabecera2, "A Ezeiza");
			break;
		case LINEA_BELGRANO_SUR_BUENOS_AIRES_BELGRANO:

			text_layer_set_text(text_layer_cabecera1, "A Marinos C.G. Belgrano");
			text_layer_set_text(text_layer_cabecera2, "A Buenos Aires");
			break;
		case LINEA_BELGRANO_PTE_ALSINA_ALDO_BONZI:

			text_layer_set_text(text_layer_cabecera1, "A Aldo Bonzi");
			text_layer_set_text(text_layer_cabecera2, "A Puente Alsina");
			break;
		case LINEA_BELGRANO_BUENOS_AIRES_GONZALEZ_CATAN:

			text_layer_set_text(text_layer_cabecera1, "A González Catán");
			text_layer_set_text(text_layer_cabecera2, "A Buenos Aires");
			break;
		case LINEA_SAN_MARTIN_SAN_MARTIN:
			
			text_layer_set_text(text_layer_cabecera1, "A Cabred");
			text_layer_set_text(text_layer_cabecera2, "A Retiro");
			break;
		case TREN_DE_LA_COSTA_TREN_DE_LA_COSTA:

			text_layer_set_text(text_layer_cabecera1, "A Delta");
			text_layer_set_text(text_layer_cabecera2, "A Maipú");
			break;
	}

	text_layer_set_text(text_layer_posiciones1_1, "1º:");
	text_layer_set_text(text_layer_posiciones2_1, "2º:");
	text_layer_set_text(text_layer_posiciones3_1, "3º:");

	text_layer_set_text(text_layer_posiciones1_2, "1º:");
	text_layer_set_text(text_layer_posiciones2_2, "2º:");
	text_layer_set_text(text_layer_posiciones3_2, "3º:");
	
}

int getLineaFromLineaRamal(int linea_ramal)
{
	// Busco la línea de tren correspondiente a cierto ramal
	switch(linea_ramal)
	{
	case LINEA_SARMIENTO_SARMIENTO:
		return LINEA_SARMIENTO;
	case LINEA_MITRE_RETIRO_TIGRE:
	case LINEA_MITRE_RETIRO_MITRE:
	case LINEA_MITRE_RETIRO_SUAREZ:
		return LINEA_MITRE;
	case LINEA_ROCA_CONSTITUCION_LA_PLATA:
	case LINEA_ROCA_CONSTITUCION_CLAYPOLE:
	case LINEA_ROCA_CLAYPOLE_GUTIERREZ:
	case LINEA_ROCA_CONSTITUCION_ALEJANDRO_KORN:
	case LINEA_ROCA_CONSTITUCION_EZEIZA:
	case LINEA_ROCA_TEMPERLEY_HAEDO:
	case LINEA_ROCA_EZEIZA_CANUELAS:
		return LINEA_ROCA;
	case LINEA_BELGRANO_SUR_BUENOS_AIRES_BELGRANO:
	case LINEA_BELGRANO_PTE_ALSINA_ALDO_BONZI:
	case LINEA_BELGRANO_BUENOS_AIRES_GONZALEZ_CATAN:
		return LINEA_BELGRANO_SUR;
	case LINEA_SAN_MARTIN_SAN_MARTIN:
		return LINEA_SAN_MARTIN;
	case TREN_DE_LA_COSTA_TREN_DE_LA_COSTA:
		return TREN_DE_LA_COSTA;
	}
  
  return 0;
}

void dialog_window_info_estacion_push(int linea_ramal, int estacion) {	
 
	linea_for_url = getLineaForUrl(linea_ramal);
	estacion_elegida = estacion + 1;

	if(!estacion_window) 
	{
		estacion_window = window_create();
		window_set_background_color(estacion_window, GColorWhite);
		window_set_click_config_provider(estacion_window, click_config_provider);
		window_set_window_handlers(estacion_window, (WindowHandlers)
		{
			.load = estacion_window_load,
			.unload = estacion_window_unload,        
		});
	}


	window_stack_push(estacion_window, true);
	inicializar_textos(getLineaFromLineaRamal(linea_ramal), linea_ramal, estacion);

	// Pido la info por primera vez
	send_ints(linea_for_url, estacion_elegida);
}
