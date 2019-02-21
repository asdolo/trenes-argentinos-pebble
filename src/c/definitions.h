#include <pebble.h>

#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))
#define LENGTH_NOMBRE_LINEA 20
#define LENGTH_NOMBRE_RAMAL 32
#define LENGTH_NOMBRE_ESTACION 32

enum
{
	LineaRequest,
	RamalRequest,
	EstacionRequest,
	Horario1Sentido1Response,
	Horario2Sentido1Response,
	Horario3Sentido1Response,
	Horario1Sentido2Response,
	Horario2Sentido2Response,
	Horario3Sentido2Response
};

// Lineas de trenes
#define CANT_LINEAS 6

enum lineas
{
	LINEA_SARMIENTO,
	LINEA_MITRE,
	LINEA_ROCA,
	LINEA_SAN_MARTIN,
	LINEA_BELGRANO_SUR,
	LINEA_TREN_DE_LA_COSTA
};

char nombres_lineas[CANT_LINEAS][LENGTH_NOMBRE_LINEA] = {
	"Sarmiento",
	"Mitre",
	"Roca",
	"San Martín",
	"Belgrano Sur",
	"Tren de la Costa"};

char *getNombreLinea(int lineaID)
{
	return nombres_lineas[lineaID];
}

// Ramales

// Ramales de la linea Sarmiento
#define CANT_RAMALES_LINEA_SARMIENTO 1

enum ramales_linea_sarmiento
{
	LINEA_SARMIENTO_RAMAL_ONCE_MORENO
};

char nombres_ramales_linea_sarmiento[CANT_RAMALES_LINEA_SARMIENTO][LENGTH_NOMBRE_RAMAL] = {
	"Once - Moreno"};

// Ramales de la linea Mitre
#define CANT_RAMALES_LINEA_MITRE 3

enum ramales_linea_mitre
{
	LINEA_MITRE_RAMAL_RETIRO_TIGRE,
	LINEA_MITRE_RAMAL_RETIRO_MITRE,
	LINEA_MITRE_RAMAL_RETIRO_J_L_SUAREZ
};

char nombres_ramales_linea_mitre[CANT_RAMALES_LINEA_MITRE][LENGTH_NOMBRE_RAMAL] = {
	"Retiro - Tigre",
	"Retiro - Mitre",
	"Retiro - J.L. Suárez"};

// Ramales de la linea Roca
#define CANT_RAMALES_LINEA_ROCA 8

enum ramales_linea_roca
{
	LINEA_ROCA_RAMAL_CONSTITUCION_LA_PLATA,
	LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_Q,
	LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_T,
	LINEA_ROCA_RAMAL_CONSTITUCION_ALEJANDRO_KORN,
	LINEA_ROCA_RAMAL_CONSTITUCION_EZEIZA,
	LINEA_ROCA_RAMAL_EZEIZA_CANUELAS,
	LINEA_ROCA_RAMAL_LA_PLATA_POLICLINICO,
	LINEA_ROCA_RAMAL_CONSTITUCION_CANUELAS
};

char nombres_ramales_linea_roca[CANT_RAMALES_LINEA_ROCA][LENGTH_NOMBRE_RAMAL] = {
	"Constitución - La Plata",
	"Constitución - Bosques (Q)",
	"Constitución - Bosques (T)",
	"Constitución - Alejandro Korn",
	"Constitución - Ezeiza",
	"Ezeiza - Cañuelas",
	"La plata - Policlínico",
	"Constitución - Cañuelas"};

// Ramales de la linea San Martin
#define CANT_RAMALES_LINEA_SAN_MARTIN 2

enum ramales_linea_san_martin
{
	LINEA_SAN_MARTIN_RAMAL_RETIRO_PILAR,
	LINEA_SAN_MARTIN_RAMAL_PILAR_CABRED
};

char nombres_ramales_linea_san_martin[CANT_RAMALES_LINEA_SAN_MARTIN][LENGTH_NOMBRE_RAMAL] = {
	"Retiro - Pilar",
	"Pilar - Cabred"};

// Ramales de la linea Belgrano Sur
#define CANT_RAMALES_LINEA_BELGRANO_SUR 3

enum ramales_linea_belgrano_sur
{
	LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_M_C_G_BELGRANO,
	LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_GONZALEZ_CATAN,
	LINEA_BELGRANO_SUR_RAMAL_APEADERO_KM_12_LIBERTAD
};

char nombres_ramales_linea_belgrano_sur[CANT_RAMALES_LINEA_BELGRANO_SUR][LENGTH_NOMBRE_RAMAL] = {
	"Buenos Aires - M.C.G. Belgrano",
	"Buenos Aires - Gonzalez Catán",
	"Apeadero Km 12 - Libertad"};

// Ramales de la linea Tren de La Costa
#define CANT_RAMALES_LINEA_TREN_DE_LA_COSTA 1

enum ramales_linea_tren_de_la_costa
{
	LINEA_TREN_DE_LA_COSTA_RAMAL_MAIPU_DELTA
};

char nombres_ramales_linea_tren_de_la_costa[CANT_RAMALES_LINEA_TREN_DE_LA_COSTA][LENGTH_NOMBRE_RAMAL] = {
	"Maipú - Delta"};

int cant_ramales[CANT_LINEAS] = {
	CANT_RAMALES_LINEA_SARMIENTO,
	CANT_RAMALES_LINEA_MITRE,
	CANT_RAMALES_LINEA_ROCA,
	CANT_RAMALES_LINEA_SAN_MARTIN,
	CANT_RAMALES_LINEA_BELGRANO_SUR,
	CANT_RAMALES_LINEA_TREN_DE_LA_COSTA};

char *getNombreRamal(int lineaID, int ramalID)
{
	switch (lineaID)
	{
	case LINEA_SARMIENTO:
		return nombres_ramales_linea_sarmiento[ramalID];
	case LINEA_MITRE:
		return nombres_ramales_linea_mitre[ramalID];
	case LINEA_ROCA:
		return nombres_ramales_linea_roca[ramalID];
	case LINEA_SAN_MARTIN:
		return nombres_ramales_linea_san_martin[ramalID];
	case LINEA_BELGRANO_SUR:
		return nombres_ramales_linea_belgrano_sur[ramalID];
	case LINEA_TREN_DE_LA_COSTA:
		return nombres_ramales_linea_tren_de_la_costa[ramalID];
	}

	return NULL;
}

// Estaciones

// Estaciones Linea Sarmiento/Ramal Once - Moreno
#define CANT_ESTACIONES_LINEA_SARMIENTO_RAMAL_ONCE_MORENO 16

char nombres_estaciones_linea_sarmiento_ramal_once_moreno[CANT_ESTACIONES_LINEA_SARMIENTO_RAMAL_ONCE_MORENO][LENGTH_NOMBRE_ESTACION] = {
	"Once",
	"Caballito",
	"Flores",
	"Floresta",
	"Villa Luro",
	"Liniers",
	"Ciudadela",
	"Ramos Mejía",
	"Haedo",
	"Morón",
	"Castelar",
	"Ituzaingó",
	"S.A. de Padua",
	"Merlo",
	"Paso del Rey",
	"Moreno"};

// Estaciones Linea Mitre/Ramal Retiro - Tigre
#define CANT_ESTACIONES_LINEA_MITRE_RAMAL_RETIRO_TIGRE 17

char nombres_estaciones_linea_mitre_ramal_retiro_tigre[CANT_ESTACIONES_LINEA_MITRE_RAMAL_RETIRO_TIGRE][LENGTH_NOMBRE_ESTACION] = {
	"Retiro",
	"L. de la Torre",
	"Belgrano C",
	"Nuñez",
	"Rivadavia",
	"Vicente López",
	"Olivos",
	"La Lucila",
	"Martínez",
	"Acassuso",
	"San Isidro C",
	"Béccar",
	"Victoria",
	"Virreyes",
	"San Fernando C",
	"Carupá",
	"Tigre"};

// Estaciones Linea Mitre/Ramal Retiro - Mitre
#define CANT_ESTACIONES_LINEA_MITRE_RAMAL_RETIRO_MITRE 11

char nombres_estaciones_linea_mitre_ramal_retiro_mitre[CANT_ESTACIONES_LINEA_MITRE_RAMAL_RETIRO_MITRE][LENGTH_NOMBRE_ESTACION] = {
	"Retiro",
	"3 de Febrero",
	"Ministro Carranza",
	"Colegiales",
	"Belgrano R",
	"Coghlan",
	"Saavedra",
	"Juan B. Justo",
	"Florida",
	"Dr. Cetrángolo",
	"Mitre"};

// Estaciones Linea Mitre/Ramal Retiro - J.L. Suarez
#define CANT_ESTACIONES_LINEA_MITRE_RAMAL_RETIRO_J_L_SUAREZ 15

char nombres_estaciones_linea_mitre_ramal_retiro_j_l_suarez[CANT_ESTACIONES_LINEA_MITRE_RAMAL_RETIRO_J_L_SUAREZ][LENGTH_NOMBRE_ESTACION] = {
	"Retiro",
	"3 de Febrero",
	"Ministro Carranza",
	"Colegiales",
	"Belgrano R",
	"L.M. Drago",
	"Urquiza",
	"Pueyrredón",
	"Miguelete",
	"San Martín",
	"San Andrés",
	"Malaver",
	"Villa Ballester",
	"Chilavert",
	"J.L. Suárez"};

// Estaciones Linea Roca/Ramal Constitución - La Plata
#define CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_LA_PLATA 19

char nombres_estaciones_linea_roca_ramal_constitucion_la_plata[CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_LA_PLATA][LENGTH_NOMBRE_ESTACION] = {
	"Constitución",
	"Santillán y Kosteki",
	"Sarandí",
	"Villa Domínico",
	"Wilde",
	"Don Bosco",
	"Bernal",
	"Quilmes",
	"Ezpeleta",
	"Berazategui",
	"Plátanos",
	"Hudson",
	"Pereyra",
	"Villa Elisa",
	"City Bell",
	"Gonnet",
	"Ringuelet",
	"Tolosa",
	"La Plata"};

// Estaciones Linea Roca/Ramal Constitución - Bosques (Q)
#define CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_Q 14

char nombres_estaciones_linea_roca_ramal_constitucion_bosques_q[CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_Q][LENGTH_NOMBRE_ESTACION] = {
	"Constitución",
	"Santillán y Kosteki",
	"Sarandí",
	"Villa Domínico",
	"Wilde",
	"Don Bosco",
	"Bernal",
	"Quilmes",
	"Ezpeleta",
	"Berazategui",
	"Villa España",
	"Ranelagh",
	"Sourigues",
	"Bosques"};

// Estaciones Linea Roca/Ramal Constitución - Bosques (T)
#define CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_T 16

char nombres_estaciones_linea_roca_ramal_constitucion_bosques_t[CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_T][LENGTH_NOMBRE_ESTACION] = {
	"Constitución",
	"Hipólito Yrigoyen",
	"Santillán y Kosteki",
	"Gerli",
	"Lanús",
	"Remedios de Escalada",
	"Banfield",
	"Lomas de Zamora",
	"Temperley",
	"José Mármol",
	"Rafael Calzada",
	"Claypole",
	"Dante Ardigó",
	"Florencio Varela",
	"Zeballos",
	"Bosques"};

// Estaciones Linea Roca/Ramal Constitución - Alejandro Korn
#define CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_ALEJANDRO_KORN 15

char nombres_estaciones_linea_roca_ramal_constitucion_alejandro_korn[CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_ALEJANDRO_KORN][LENGTH_NOMBRE_ESTACION] = {
	"Constitución",
	"Hipólito Yrigoyen",
	"Santillán y Kosteki",
	"Gerli",
	"Lanús",
	"Remedios de Escalada",
	"Banfield",
	"Lomas de Zamora",
	"Temperley",
	"Adrogué",
	"Burzaco",
	"Longchamps",
	"Glew",
	"Guernica",
	"Alejandro Korn"};

// Estaciones Linea Roca/Ramal Constitución - Ezeiza
#define CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_EZEIZA 15

char nombres_estaciones_linea_roca_ramal_constitucion_ezeiza[CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_EZEIZA][LENGTH_NOMBRE_ESTACION] = {
	"Constitución",
	"Hipólito Yrigoyen",
	"Santillán y Kosteki",
	"Gerli",
	"Lanús",
	"Remedios de Escalada",
	"Banfield",
	"Lomas de Zamora",
	"Temperley",
	"Turdera",
	"Llavallol",
	"Luis Guillón",
	"Monte Grande",
	"El Jagüel",
	"Ezeiza"};

// Estaciones Linea Roca/Ramal Ezeiza - Cañuelas
#define CANT_ESTACIONES_LINEA_ROCA_RAMAL_EZEIZA_CANUELAS 10

char nombres_estaciones_linea_roca_ramal_ezeiza_canuelas[CANT_ESTACIONES_LINEA_ROCA_RAMAL_EZEIZA_CANUELAS][LENGTH_NOMBRE_ESTACION] = {
	"Ezeiza",
	"Unión Ferroviaria",
	"Tristán Suárez",
	"Carlos Spegazzini",
	"Máximo Paz",
	"Vicente Casares",
	"Alejandro Petión",
	"Apeadero Kloosterman",
	"Ricardo Levene",
	"Cañuelas"};

// Estaciones Linea Roca/Ramal La Plata - Policlínico
#define CANT_ESTACIONES_LINEA_ROCA_RAMAL_LA_PLATA_POLICLINICO 7

char nombres_estaciones_linea_roca_ramal_la_plata_policlinico[CANT_ESTACIONES_LINEA_ROCA_RAMAL_LA_PLATA_POLICLINICO][LENGTH_NOMBRE_ESTACION] = {
	"La Plata",
	"Arquitectura",
	"Informática",
	"Medicina",
	"Periodismo",
	"Diagonal 73",
	"Policlínico"};

// Estaciones Linea Roca/Ramal Constitución - Cañuelas
#define CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_CANUELAS 24

char nombres_estaciones_linea_roca_ramal_constitucion_canuelas[CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_CANUELAS][LENGTH_NOMBRE_ESTACION] = {
	"Constitución",
	"Hipólito Yrigoyen",
	"Santillán y Kosteki",
	"Gerli",
	"Lanús",
	"Remedios de Escalada",
	"Banfield",
	"Lomas de Zamora",
	"Temperley",
	"Turdera",
	"Llavallol",
	"Luis Guillón",
	"Monte Grande",
	"El Jagüel",
	"Ezeiza",
	"Unión Ferroviaria",
	"Tristán Suárez",
	"Carlos Spegazzini",
	"Máximo Paz",
	"Vicente Casares",
	"Alejandro Petión",
	"Apeadero Kloosterman",
	"Ricardo Levene",
	"Cañuelas"};

// Estaciones Linea San Martín/Ramal Retiro - Pilar
#define CANT_ESTACIONES_LINEA_SAN_MARTIN_RAMAL_RETIRO_PILAR 16

char nombres_estaciones_linea_san_martin_ramal_retiro_pilar[CANT_ESTACIONES_LINEA_SAN_MARTIN_RAMAL_RETIRO_PILAR][LENGTH_NOMBRE_ESTACION] = {
	"Villa del Parque",
	"Devoto",
	"Saenz Peña",
	"Santos Lugares",
	"Caseros",
	"El Palomar",
	"Hurlingham",
	"William Morris",
	"Bella Vista",
	"Muñiz",
	"San Miguel",
	"José C Paz",
	"Sol y Verde",
	"Derqui",
	"Villa Astolfi",
	"Pilar"};

// Estaciones Linea San Martín/Ramal Pilar - Cabred
#define CANT_ESTACIONES_LINEA_SAN_MARTIN_RAMAL_PILAR_CABRED 3

char nombres_estaciones_linea_san_martin_ramal_pilar_cabred[CANT_ESTACIONES_LINEA_SAN_MARTIN_RAMAL_PILAR_CABRED][LENGTH_NOMBRE_ESTACION] = {
	"Pilar",
	"Manzanares",
	"Cabred"};

// Estaciones Linea Belgrano Sur/Ramal Buenos Aires - M.C.G. Belgrano
#define CANT_ESTACIONES_LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_M_C_G_BELGRANO 16

char nombres_estaciones_linea_belgrano_sur_ramal_buenos_aires_m_c_g_belgrano[CANT_ESTACIONES_LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_M_C_G_BELGRANO][LENGTH_NOMBRE_ESTACION] = {
	"Dr Sáenz",
	"Villa Soldati",
	"Presidente Illia",
	"Villa Lugano",
	"Villa Madero",
	"Marinos del Fournier",
	"Tapiales",
	"Aldo Bonzi",
	"Sanchez de Mendeville",
	"José Ingenieros",
	"Justo Villegas",
	"Isidro Casanova",
	"Rafael Castillo",
	"Merlo Gomez",
	"Libertad",
	"Marinos C. G Belgrano"};

// Estaciones Linea Belgrano Sur/Ramal Buenos Aires - Gonzalez Catán
#define CANT_ESTACIONES_LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_GONZALEZ_CATAN 13

char nombres_estaciones_linea_belgrano_sur_ramal_buenos_aires_gonzalez_catan[CANT_ESTACIONES_LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_GONZALEZ_CATAN][LENGTH_NOMBRE_ESTACION] = {
	"Dr Sáenz",
	"Villa Soldati",
	"Presidente Illia",
	"Villa Lugano",
	"Villa Madero",
	"Marinos del Fournier",
	"Tapiales",
	"Ingeniero Castello",
	"Querandí",
	"Laferrere",
	"María Eva Duarte",
	"Independencia",
	"González Catán"};

// Estaciones Linea Belgrano Sur/Ramal Apeadero Km 12 - Libertad
#define CANT_ESTACIONES_LINEA_BELGRANO_SUR_RAMAL_APEADERO_KM_12_LIBERTAD 9

char nombres_estaciones_linea_belgrano_sur_ramal_apeadero_km_12_libertad[CANT_ESTACIONES_LINEA_BELGRANO_SUR_RAMAL_APEADERO_KM_12_LIBERTAD][LENGTH_NOMBRE_ESTACION] = {
	"Apeadero Km 12",
	"Aldo Bonzi",
	"Sanchez de Mendeville",
	"José Ingenieros",
	"Justo Villegas",
	"Isidro Casanova",
	"Rafael Castillo",
	"Merlo Gomez",
	"Libertad"};

// Estaciones Linea Tren de La Costa/Ramal Maipú - Delta
#define CANT_ESTACIONES_LINEA_TREN_DE_LA_COSTA_RAMAL_MAIPU_DELTA 11

char nombres_estaciones_linea_tren_de_la_costa_ramal_maipu_delta[CANT_ESTACIONES_LINEA_TREN_DE_LA_COSTA_RAMAL_MAIPU_DELTA][LENGTH_NOMBRE_ESTACION] = {
	"Maipú",
	"Borges",
	"Libertador",
	"Juan Anchorena",
	"Las Barrancas",
	"San Isidro R",
	"Punta Chica",
	"Marina Nueva",
	"San Fernando R",
	"Canal San Fernando",
	"Delta"};

int cant_estaciones_linea_sarmiento[CANT_RAMALES_LINEA_SARMIENTO] = {
	CANT_ESTACIONES_LINEA_SARMIENTO_RAMAL_ONCE_MORENO};

int cant_estaciones_linea_mitre[CANT_RAMALES_LINEA_MITRE] = {
	CANT_ESTACIONES_LINEA_MITRE_RAMAL_RETIRO_TIGRE,
	CANT_ESTACIONES_LINEA_MITRE_RAMAL_RETIRO_MITRE,
	CANT_ESTACIONES_LINEA_MITRE_RAMAL_RETIRO_J_L_SUAREZ};

int cant_estaciones_linea_roca[CANT_RAMALES_LINEA_ROCA] = {
	CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_LA_PLATA,
	CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_Q,
	CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_T,
	CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_ALEJANDRO_KORN,
	CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_EZEIZA,
	CANT_ESTACIONES_LINEA_ROCA_RAMAL_EZEIZA_CANUELAS,
	CANT_ESTACIONES_LINEA_ROCA_RAMAL_LA_PLATA_POLICLINICO,
	CANT_ESTACIONES_LINEA_ROCA_RAMAL_CONSTITUCION_CANUELAS};

int cant_estaciones_linea_san_martin[CANT_RAMALES_LINEA_SAN_MARTIN] = {
	CANT_ESTACIONES_LINEA_SAN_MARTIN_RAMAL_RETIRO_PILAR,
	CANT_ESTACIONES_LINEA_SAN_MARTIN_RAMAL_PILAR_CABRED};

int cant_estaciones_linea_belgrano_sur[CANT_RAMALES_LINEA_BELGRANO_SUR] = {
	CANT_ESTACIONES_LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_M_C_G_BELGRANO,
	CANT_ESTACIONES_LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_GONZALEZ_CATAN,
	CANT_ESTACIONES_LINEA_BELGRANO_SUR_RAMAL_APEADERO_KM_12_LIBERTAD};

int cant_estaciones_linea_tren_de_la_costa[CANT_RAMALES_LINEA_TREN_DE_LA_COSTA] = {
	CANT_ESTACIONES_LINEA_TREN_DE_LA_COSTA_RAMAL_MAIPU_DELTA};

int *cant_estaciones[CANT_LINEAS] = {
	cant_estaciones_linea_sarmiento,
	cant_estaciones_linea_mitre,
	cant_estaciones_linea_roca,
	cant_estaciones_linea_san_martin,
	cant_estaciones_linea_belgrano_sur,
	cant_estaciones_linea_tren_de_la_costa};

char *getNombreEstacion(int lineaID, int ramalID, int estacionID)
{
	switch (lineaID)
	{
	case LINEA_SARMIENTO:
		switch (ramalID)
		{
		case LINEA_SARMIENTO_RAMAL_ONCE_MORENO:
			return nombres_estaciones_linea_sarmiento_ramal_once_moreno[estacionID];
		}
	case LINEA_MITRE:
		switch (ramalID)
		{
		case LINEA_MITRE_RAMAL_RETIRO_TIGRE:
			return nombres_estaciones_linea_mitre_ramal_retiro_tigre[estacionID];
		case LINEA_MITRE_RAMAL_RETIRO_MITRE:
			return nombres_estaciones_linea_mitre_ramal_retiro_mitre[estacionID];
		case LINEA_MITRE_RAMAL_RETIRO_J_L_SUAREZ:
			return nombres_estaciones_linea_mitre_ramal_retiro_j_l_suarez[estacionID];
		}
	case LINEA_ROCA:
		switch (ramalID)
		{
		case LINEA_ROCA_RAMAL_CONSTITUCION_LA_PLATA:
			return nombres_estaciones_linea_roca_ramal_constitucion_la_plata[estacionID];
		case LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_Q:
			return nombres_estaciones_linea_roca_ramal_constitucion_bosques_q[estacionID];
		case LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_T:
			return nombres_estaciones_linea_roca_ramal_constitucion_bosques_t[estacionID];
		case LINEA_ROCA_RAMAL_CONSTITUCION_ALEJANDRO_KORN:
			return nombres_estaciones_linea_roca_ramal_constitucion_alejandro_korn[estacionID];
		case LINEA_ROCA_RAMAL_CONSTITUCION_EZEIZA:
			return nombres_estaciones_linea_roca_ramal_constitucion_ezeiza[estacionID];
		case LINEA_ROCA_RAMAL_EZEIZA_CANUELAS:
			return nombres_estaciones_linea_roca_ramal_ezeiza_canuelas[estacionID];
		case LINEA_ROCA_RAMAL_LA_PLATA_POLICLINICO:
			return nombres_estaciones_linea_roca_ramal_la_plata_policlinico[estacionID];
		case LINEA_ROCA_RAMAL_CONSTITUCION_CANUELAS:
			return nombres_estaciones_linea_roca_ramal_constitucion_canuelas[estacionID];
		}
	case LINEA_SAN_MARTIN:
		switch (ramalID)
		{
		case LINEA_SAN_MARTIN_RAMAL_RETIRO_PILAR:
			return nombres_estaciones_linea_san_martin_ramal_retiro_pilar[estacionID];
		case LINEA_SAN_MARTIN_RAMAL_PILAR_CABRED:
			return nombres_estaciones_linea_san_martin_ramal_pilar_cabred[estacionID];
		}
	case LINEA_BELGRANO_SUR:
		switch (ramalID)
		{
		case LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_M_C_G_BELGRANO:
			return nombres_estaciones_linea_belgrano_sur_ramal_buenos_aires_m_c_g_belgrano[estacionID];
		case LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_GONZALEZ_CATAN:
			return nombres_estaciones_linea_belgrano_sur_ramal_buenos_aires_gonzalez_catan[estacionID];
		case LINEA_BELGRANO_SUR_RAMAL_APEADERO_KM_12_LIBERTAD:
			return nombres_estaciones_linea_belgrano_sur_ramal_apeadero_km_12_libertad[estacionID];
		}
	case LINEA_TREN_DE_LA_COSTA:
		switch (ramalID)
		{
		case LINEA_TREN_DE_LA_COSTA_RAMAL_MAIPU_DELTA:
			return nombres_estaciones_linea_tren_de_la_costa_ramal_maipu_delta[estacionID];
		}
	}

	return NULL;
}