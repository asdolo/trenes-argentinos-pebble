var dict;

var getInfoEstacion = function(ramal_id, estacion_id) {
  
  console.log("HTTPGET: http://trenes.sofse.gob.ar/apps/api_tiempos_temp.php?ramal=" + ramal_id);
  var method = 'GET';
  var url = 'http://trenes.sofse.gob.ar/apps/api_tiempos_temp.php?ramal=' + ramal_id;
  
  // Create the request
  var request = new XMLHttpRequest();
  
  // Specify the callback for when the request is completed
  request.onload = function() {
    // The request was successfully completed!
    console.log('Got response: ' + this.responseText);
    
    console.log("Hecho!");
    
    //lo convierto a JSON
    var json = JSON.parse(this.responseText);
   
    var cantEstacionesLinea = json.intermedias.length + 2;
    console.log("cantEstacionesLinea = " + cantEstacionesLinea);
    
    var tiempo1_sentido1 = 0;
    var tiempo2_sentido1 = 0;
    var tiempo3_sentido1 = 0;
    var tiempo1_sentido2 = 0;
    var tiempo2_sentido2 = 0;
    var tiempo3_sentido2 = 0;
    
    if (estacion_id  == 1)
    {
      
      tiempo1_sentido1= json.salidas[0].min;
      tiempo2_sentido1 = json.salidas[1].min;
      tiempo3_sentido1 = json.salidas[2].min;
    }
    else if (estacion_id == cantEstacionesLinea)
    {
      tiempo1_sentido1 = json.salidas2[0].min;
      tiempo2_sentido1 = json.salidas2[1].min;
      tiempo3_sentido1 = json.salidas2[2].min;
    }
    else
    {
      tiempo1_sentido1 = json.intermedias[estacion_id - 2].min_1;
      tiempo2_sentido1 = json.intermedias[estacion_id - 2].min_2;
      tiempo3_sentido1 = json.intermedias[estacion_id - 2].min_3;
      tiempo1_sentido2 = json.intermedias[estacion_id - 2].min_4;
      tiempo2_sentido2 = json.intermedias[estacion_id - 2].min_5;
      tiempo3_sentido2 = json.intermedias[estacion_id - 2].min_6;
      
      if (tiempo1_sentido1 === '0')
      {
        tiempo1_sentido1 = 'ANDÉN';
      }
      else if(tiempo1_sentido1 === '-1')
      {
        tiempo1_sentido1 = '-';
      }
      else
      {
        tiempo1_sentido1 += ' min';
      }
      
      if (tiempo2_sentido1 === '0')
      {
        tiempo2_sentido1 = 'ANDÉN';
      }
      else if(tiempo2_sentido1 === '-1')
      {
        tiempo2_sentido1 = '-';
      }
      else
      {
        tiempo2_sentido1 += ' min';
      }
      
      if (tiempo3_sentido1 === '0')
      {
        tiempo3_sentido1 = 'ANDÉN';
      }
      else if(tiempo3_sentido1 === '-1')
      {
        tiempo3_sentido1 = '-';
      }
      else
      {
        tiempo3_sentido1 += ' min';
      }
      
      if (tiempo1_sentido2 === '0')
      {
        tiempo1_sentido2 = 'ANDÉN';
      }
      else if(tiempo1_sentido2 === '-1')
      {
        tiempo1_sentido2 = '-';
      }
      else
      {
        tiempo1_sentido2 += ' min';
      }
      
      if (tiempo2_sentido2 === '0')
      {
        tiempo2_sentido2 = 'ANDÉN';
      }
      else if(tiempo2_sentido2 === '-1')
      {
        tiempo2_sentido2 = '-';
      }
      else
      {
        tiempo2_sentido2 += ' min';
      }
      
      if (tiempo3_sentido2 === '0')
      {
        tiempo3_sentido2 = 'ANDÉN';
      }
      else if(tiempo3_sentido2 === '-1')
      {
        tiempo3_sentido2 = '-';
      }
      else
      {
        tiempo3_sentido2 += ' min';
      }
      
    }
    
    /*
    console.log("tiempo1_sentido1 = " + tiempo1_sentido1);
    console.log("tiempo2_sentido1 = " + tiempo2_sentido1);
    console.log("tiempo3_sentido1 = " + tiempo3_sentido1);
    console.log("--------------------------------------");
    console.log("tiempo1_sentido2 = " + tiempo1_sentido2);
    console.log("tiempo2_sentido2 = " + tiempo2_sentido2);
    console.log("tiempo3_sentido2 = " + tiempo3_sentido2);
    */
    
    if (estacion_id == 1 || estacion_id == cantEstacionesLinea)
    {
      dict = {"KEY_RESPUESTA_HORARIO1_SENTIDO1" : tiempo1_sentido1,
              "KEY_RESPUESTA_HORARIO2_SENTIDO1" : tiempo2_sentido1,
              "KEY_RESPUESTA_HORARIO3_SENTIDO1" : tiempo3_sentido1
             };
    }
    else
    {
      dict = {"KEY_RESPUESTA_HORARIO1_SENTIDO1" : tiempo1_sentido1,
              "KEY_RESPUESTA_HORARIO2_SENTIDO1" : tiempo2_sentido1,
              "KEY_RESPUESTA_HORARIO3_SENTIDO1" : tiempo3_sentido1,
              "KEY_RESPUESTA_HORARIO1_SENTIDO2" : tiempo1_sentido2,
              "KEY_RESPUESTA_HORARIO2_SENTIDO2" : tiempo2_sentido2,
              "KEY_RESPUESTA_HORARIO3_SENTIDO2" : tiempo3_sentido2,
             };
    }
  
    // envio los datos al reloj
    Pebble.sendAppMessage(dict);
    
  };
  
  // Send the request
  request.open(method, url);
  request.send();
};
 
Pebble.addEventListener("ready",
  function(e) {
    
  }
);

Pebble.addEventListener("appmessage",
  function(e) {
    //Se refresca la información
	/*
    console.log("e.payload.KEY_CONSULTA_RAMAL_COMPLETO = " + e.payload.KEY_CONSULTA_RAMAL_COMPLETO);
    console.log("e.payload.KEY_CONSULTA_ESTACION_PARTICULAR = " + e.payload.KEY_CONSULTA_ESTACION_PARTICULAR);
	*/
    var ramal=e.payload.KEY_CONSULTA_RAMAL_COMPLETO;
    var estacion=e.payload.KEY_CONSULTA_ESTACION_PARTICULAR;
    if (estacion !== 0)
    {
      getInfoEstacion(ramal, estacion);
    }
    else
    {
        //getInfoRamal(ramal);
    }

  }
);
