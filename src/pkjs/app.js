const LINEA_SARMIENTO			= 0;
const LINEA_MITRE				= 1;
const LINEA_ROCA				= 2;
const LINEA_SAN_MARTIN			= 3;
const LINEA_BELGRANO_SUR		= 4;
const LINEA_TREN_DE_LA_COSTA	= 5;

const LINEA_SARMIENTO_RAMAL_ONCE_MORENO	= 0;

const LINEA_MITRE_RAMAL_RETIRO_TIGRE 		= 0;
const LINEA_MITRE_RAMAL_RETIRO_MITRE 		= 1;
const LINEA_MITRE_RAMAL_RETIRO_J_L_SUAREZ	= 2;

const LINEA_ROCA_RAMAL_CONSTITUCION_LA_PLATA		= 0;
const LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_Q		= 1;
const LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_T		= 2;
const LINEA_ROCA_RAMAL_CONSTITUCION_ALEJANDRO_KORN	= 3;
const LINEA_ROCA_RAMAL_CONSTITUCION_EZEIZA			= 4;
const LINEA_ROCA_RAMAL_EZEIZA_CANUELAS				= 5;
const LINEA_ROCA_RAMAL_LA_PLATA_POLICLINICO			= 6;
const LINEA_ROCA_RAMAL_CONSTITUCION_CANUELAS		= 7;

const LINEA_SAN_MARTIN_RAMAL_RETIRO_PILAR	= 0;
const LINEA_SAN_MARTIN_RAMAL_PILAR_CABRED	= 1;

const LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_M_C_G_BELGRANO	= 0;
const LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_GONZALEZ_CATAN	= 1;
const LINEA_BELGRANO_SUR_RAMAL_APEADERO_KM_12_LIBERTAD		= 2;

const LINEA_TREN_DE_LA_COSTA_RAMAL_MAIPU_DELTA = 0;

const API_BASE = 'https://ariedro.dev/api-trenes';

const dict_ramales_url = {
	[LINEA_SARMIENTO]: {
		[LINEA_SARMIENTO_RAMAL_ONCE_MORENO]: 1
	},
	[LINEA_MITRE]: {
		[LINEA_MITRE_RAMAL_RETIRO_TIGRE]: 5,
		[LINEA_MITRE_RAMAL_RETIRO_MITRE]: 7,
		[LINEA_MITRE_RAMAL_RETIRO_J_L_SUAREZ]: 9
	},
	[LINEA_ROCA]: {
		[LINEA_ROCA_RAMAL_CONSTITUCION_LA_PLATA]: 11,
		[LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_Q]: 13,
		[LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_T]: 15,
		[LINEA_ROCA_RAMAL_CONSTITUCION_ALEJANDRO_KORN]: 17,
		[LINEA_ROCA_RAMAL_CONSTITUCION_EZEIZA]: 19,
		[LINEA_ROCA_RAMAL_EZEIZA_CANUELAS]: 37,
		[LINEA_ROCA_RAMAL_LA_PLATA_POLICLINICO]: 39,
		[LINEA_ROCA_RAMAL_CONSTITUCION_CANUELAS]: 43
	},
	[LINEA_SAN_MARTIN]: {
		[LINEA_SAN_MARTIN_RAMAL_RETIRO_PILAR]: 31,
		[LINEA_SAN_MARTIN_RAMAL_PILAR_CABRED]: 59
	},
	[LINEA_BELGRANO_SUR]: {
		[LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_M_C_G_BELGRANO]: 21,
		[LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_GONZALEZ_CATAN]: 25,
		[LINEA_BELGRANO_SUR_RAMAL_APEADERO_KM_12_LIBERTAD]: 63
	},
	[LINEA_TREN_DE_LA_COSTA]: {
		[LINEA_TREN_DE_LA_COSTA_RAMAL_MAIPU_DELTA]: 41
	}
};

// SOFSE station IDs aligned with the watchapp station order in definitions.h
const dict_estaciones_ids = {
	[LINEA_SARMIENTO]: {
		[LINEA_SARMIENTO_RAMAL_ONCE_MORENO]: [293, 50, 139, 140, 423, 234, 84, 327, 169, 279, 70, 186, 347, 269, 300, 278]
	},
	[LINEA_MITRE]: {
		[LINEA_MITRE_RAMAL_RETIRO_TIGRE]: [332, 229, 34, 287, 337, 408, 291, 212, 262, 5, 357, 32, 409, 428, 355, 65, 389],
		[LINEA_MITRE_RAMAL_RETIRO_MITRE]: [332, 1, 272, 91, 35, 90, 346, 200, 141, 119, 273],
		[LINEA_MITRE_RAMAL_RETIRO_J_L_SUAREZ]: [332, 1, 272, 91, 35, 236, 150, 318, 271, 360, 353, 249, 412, 79, 190]
	},
	[LINEA_ROCA]: {
		[LINEA_ROCA_RAMAL_CONSTITUCION_LA_PLATA]: [93, 368, 370, 418, 430, 115, 39, 322, 133, 38, 309, 176, 303, 419, 83, 153, 334, 392, 217],
		[LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_Q]: [93, 368, 370, 418, 430, 115, 39, 322, 133, 38, 420, 328, 380, 43],
		[LINEA_ROCA_RAMAL_CONSTITUCION_BOSQUES_T]: [93, 172, 368, 151, 215, 329, 30, 238, 386, 197, 324, 85, 102, 138, 435, 43],
		[LINEA_ROCA_RAMAL_CONSTITUCION_ALEJANDRO_KORN]: [93, 172, 368, 151, 215, 329, 30, 238, 386, 8, 49, 239, 152, 165, 13],
		[LINEA_ROCA_RAMAL_CONSTITUCION_EZEIZA]: [93, 172, 368, 151, 215, 329, 30, 238, 386, 399, 235, 246, 277, 125, 132],
		[LINEA_ROCA_RAMAL_EZEIZA_CANUELAS]: [132, 400, 396, 64, 265, 407, 14, 21, 333, 60],
		[LINEA_ROCA_RAMAL_LA_PLATA_POLICLINICO]: [217, 25, 179, 267, 304, 113, 311],
		[LINEA_ROCA_RAMAL_CONSTITUCION_CANUELAS]: [93, 172, 368, 151, 215, 329, 30, 238, 386, 399, 235, 246, 277, 125, 132, 400, 396, 64, 265, 407, 14, 21, 333, 60]
	},
	[LINEA_SAN_MARTIN]: {
		[LINEA_SAN_MARTIN_RAMAL_RETIRO_PILAR]: [415, 112, 348, 369, 67, 127, 177, 431, 36, 283, 361, 194, 378, 106, 411, 306],
		[LINEA_SAN_MARTIN_RAMAL_PILAR_CABRED]: [306, 252, 51]
	},
	[LINEA_BELGRANO_SUR]: {
		[LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_M_C_G_BELGRANO]: [525, 427, 313, 422, 424, 260, 385, 12, 354, 195, 203, 184, 325, 270, 232, 259],
		[LINEA_BELGRANO_SUR_RAMAL_BUENOS_AIRES_GONZALEZ_CATAN]: [525, 427, 313, 422, 424, 260, 385, 181, 321, 209, 256, 178, 154],
		[LINEA_BELGRANO_SUR_RAMAL_APEADERO_KM_12_LIBERTAD]: [22, 12, 354, 195, 203, 184, 325, 270, 232]
	},
	[LINEA_TREN_DE_LA_COSTA]: {
		[LINEA_TREN_DE_LA_COSTA_RAMAL_MAIPU_DELTA]: [248, 42, 233, 198, 222, 358, 319, 258, 356, 58, 104]
	}
};

const formatTiempo = function (segundos) {
	if (segundos === null || segundos === undefined || isNaN(segundos)) {
		return '-';
	}

	const minutos = Math.floor(segundos / 60);
	if (minutos <= 0) {
		return 'En andén';
	}

	return minutos.toString() + ' min';
};

const getRamalIDForURL = function (linea_id, ramal_id) {
	return dict_ramales_url[linea_id][ramal_id];
};

const getEstacionIDForURL = function (linea_id, ramal_id, estacion_id) {
	return dict_estaciones_ids[linea_id][ramal_id][estacion_id];
};

const emptyHorarios = function () {
	return ['-', '-', '-'];
};

const padHorarios = function (horarios) {
	return emptyHorarios().map(function (_, index) {
		return horarios[index] || '-';
	});
};

const extractHorariosBySentido = function (results, apiSentido) {
	return padHorarios(
		results
			.filter(function (result) {
				return result && result.servicio && result.servicio.sentido === apiSentido && result.arribo;
			})
			.map(function (result) {
				return formatTiempo(result.arribo.segundos);
			})
			.slice(0, 3)
	);
};

const sendErrorHorarios = function () {
	Pebble.sendAppMessage({
		Horario1Sentido1Response: '-',
		Horario2Sentido1Response: '-',
		Horario3Sentido1Response: '-',
		Horario1Sentido2Response: '-',
		Horario2Sentido2Response: '-',
		Horario3Sentido2Response: '-'
	});
};

const sendInfoEstacion = function (linea_id, ramal_id, estacion_id) {
	const apiRamalId = getRamalIDForURL(linea_id, ramal_id);
	const apiEstacionId = getEstacionIDForURL(linea_id, ramal_id, estacion_id);

	if (!apiRamalId || !apiEstacionId) {
		sendErrorHorarios();
		return;
	}

	const url = API_BASE + '/arribos/estacion/' + apiEstacionId +
		'?ramal=' + apiRamalId +
		'&cantidad=6' +
		'&paraApp=1';

	const request = new XMLHttpRequest();

	request.onload = function () {
		if (request.status < 200 || request.status >= 300) {
			sendErrorHorarios();
			return;
		}

		var data;
		try {
			data = JSON.parse(request.responseText);
		} catch (e) {
			sendErrorHorarios();
			return;
		}

		const results = (data && data.results) ? data.results : [];

		// API sentido 2 = toward cabecera inicial (UI sentido 1 / first station)
		// API sentido 1 = toward cabecera final (UI sentido 2 / last station)
		const sentido1 = extractHorariosBySentido(results, 2);
		const sentido2 = extractHorariosBySentido(results, 1);

		Pebble.sendAppMessage({
			Horario1Sentido1Response: sentido1[0],
			Horario2Sentido1Response: sentido1[1],
			Horario3Sentido1Response: sentido1[2],
			Horario1Sentido2Response: sentido2[0],
			Horario2Sentido2Response: sentido2[1],
			Horario3Sentido2Response: sentido2[2]
		});
	};

	request.onerror = function () {
		sendErrorHorarios();
	};

	request.open('GET', url);
	request.send();
};

Pebble.addEventListener('ready',
	function (e) {
	}
);

Pebble.addEventListener('appmessage',
	function (e) {
		var linea_id = e.payload.LineaRequest;
		var ramal_id = e.payload.RamalRequest;
		var estacion_id = e.payload.EstacionRequest;

		if (linea_id !== undefined && ramal_id !== undefined && estacion_id !== undefined) {
			sendInfoEstacion(linea_id, ramal_id, estacion_id);
		}
	}
);
