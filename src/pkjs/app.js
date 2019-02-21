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

const formatTiempo = function (str) {
	const cleanString = str.substring(4).replace(/ .*/,'');

	if (cleanString === "-") {
		return cleanString;
	}
	else 
	{
		const tiempo = Number(cleanString);
		return tiempo === 0 ? "En andén" : tiempo.toString() + " min"
	}
};

const getRamalIDForURL = function (linea_id, ramal_id) {
	return dict_ramales_url[linea_id][ramal_id];
};

const getEstacionIDForURL = function (linea_id, ramal_id, estacion_id) {
	return estacion_id + 1;
};

const sendInfoEstacion = function (linea_id, ramal_id, estacion_id) {
	
	var method = 'GET';
	var url = 'http://trenesendirecto.sofse.gob.ar/iframe/horarios.php?id_ramal=' + getRamalIDForURL(linea_id, ramal_id) + '&id_estacion=' + getEstacionIDForURL(linea_id, ramal_id, estacion_id);

	// Create the request
	var request = new XMLHttpRequest();
	
	// Specify the callback for when the request is completed
	request.onload = function () {
		// The request was successfully completed!
		// console.log('Got response: ' + this.responseText);
		
		const sentido1Tiempos =
			this.responseText.substring(
					this.responseText.indexOf("<ol>") + 4, 
					this.responseText.indexOf("</ol>")
			)
			.split("</li>");

		const sentido2Tiempos =
			this.responseText.substring(
				this.responseText.lastIndexOf("<ol>") + 4, 
				this.responseText.lastIndexOf("</ol>")
			)
			.split("</li>");

		const responseDict = {
			Horario1Sentido1Response: sentido1Tiempos[0].substring(4).replace(/ .*/,''),
			Horario2Sentido1Response: sentido1Tiempos[1].substring(4).replace(/ .*/,''),
			Horario3Sentido1Response: sentido1Tiempos[2].substring(4).replace(/ .*/,''),

			Horario1Sentido2Response: sentido2Tiempos[0].substring(4),
			Horario2Sentido2Response: sentido2Tiempos[1].substring(4),
			Horario3Sentido2Response: sentido2Tiempos[2].substring(4)
		}

		// envio los datos al reloj
		Pebble.sendAppMessage(responseDict);
	};
	
	// Send the request
	request.open(method, url);
	request.send();
};

Pebble.addEventListener("ready",
	function (e) {
		
	}
);

Pebble.addEventListener("appmessage",
	function (e) {
		var linea_id = e.payload.LineaRequest;
		var ramal_id = e.payload.RamalRequest;
		var estacion_id = e.payload.EstacionRequest;

		if (linea_id !== undefined && ramal_id !== undefined  && estacion_id !== undefined ) {
			sendInfoEstacion(linea_id, ramal_id, estacion_id);
		}
	}
);
