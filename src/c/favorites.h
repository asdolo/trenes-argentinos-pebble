#pragma once

#include <pebble.h>
#include <string.h>

#define FAVORITES_MAX 8
#define FAVORITES_PERSIST_KEY 1

typedef struct {
	int8_t linea;
	int8_t ramal;
	int8_t estacion;
} Favorite;

typedef struct {
	uint8_t count;
	Favorite items[FAVORITES_MAX];
} FavoritesStore;

static FavoritesStore s_favorites;

static void favorites_save(void)
{
	persist_write_data(FAVORITES_PERSIST_KEY, &s_favorites, sizeof(s_favorites));
}

static void favorites_load(void)
{
	s_favorites.count = 0;
	memset(s_favorites.items, 0, sizeof(s_favorites.items));

	if (!persist_exists(FAVORITES_PERSIST_KEY)) {
		return;
	}

	const int read = persist_read_data(FAVORITES_PERSIST_KEY, &s_favorites, sizeof(s_favorites));
	if (read != (int)sizeof(s_favorites) || s_favorites.count > FAVORITES_MAX) {
		s_favorites.count = 0;
		memset(s_favorites.items, 0, sizeof(s_favorites.items));
	}
}

static int favorites_find(int linea, int ramal, int estacion)
{
	uint8_t i = 0;
	while (i < s_favorites.count) {
		const Favorite *item = &s_favorites.items[i];
		if (item->linea == linea && item->ramal == ramal && item->estacion == estacion) {
			return (int)i;
		}
		i++;
	}
	return -1;
}

static bool favorites_is_favorite(int linea, int ramal, int estacion)
{
	return favorites_find(linea, ramal, estacion) >= 0;
}

static bool favorites_add(int linea, int ramal, int estacion)
{
	if (favorites_is_favorite(linea, ramal, estacion)) {
		return true;
	}
	if (s_favorites.count >= FAVORITES_MAX) {
		return false;
	}

	s_favorites.items[s_favorites.count] = (Favorite){
		.linea = (int8_t)linea,
		.ramal = (int8_t)ramal,
		.estacion = (int8_t)estacion,
	};
	s_favorites.count++;
	favorites_save();
	return true;
}

static bool favorites_remove_at(int index)
{
	if (index < 0 || index >= (int)s_favorites.count) {
		return false;
	}

	uint8_t i = (uint8_t)index;
	while (i + 1 < s_favorites.count) {
		s_favorites.items[i] = s_favorites.items[i + 1];
		i++;
	}
	s_favorites.count--;
	favorites_save();
	return true;
}

static bool favorites_toggle(int linea, int ramal, int estacion)
{
	const int index = favorites_find(linea, ramal, estacion);
	if (index >= 0) {
		favorites_remove_at(index);
		return false;
	}

	favorites_add(linea, ramal, estacion);
	return true;
}

static uint8_t favorites_count(void)
{
	return s_favorites.count;
}

static const Favorite *favorites_get(int index)
{
	if (index < 0 || index >= (int)s_favorites.count) {
		return NULL;
	}
	return &s_favorites.items[index];
}
