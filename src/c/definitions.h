#include <pebble.h>

enum {
	KEY_CONSULTA_RAMAL_COMPLETO = 0,
  KEY_RESPUESTA_HORARIO1_SENTIDO1 = 1,
  KEY_RESPUESTA_HORARIO2_SENTIDO1 = 2,
  KEY_RESPUESTA_HORARIO3_SENTIDO1 = 3,
  KEY_RESPUESTA_HORARIO1_SENTIDO2 = 4,
  KEY_RESPUESTA_HORARIO2_SENTIDO2 = 5,
  KEY_RESPUESTA_HORARIO3_SENTIDO2 = 6,
  KEY_CONSULTA_ESTACION_PARTICULAR = 7
};



enum lineas {LINEA_SARMIENTO,
             LINEA_MITRE,
             LINEA_ROCA,
             LINEA_BELGRANO_SUR,
             LINEA_SAN_MARTIN,
             TREN_DE_LA_COSTA};

enum ramales_lineas {LINEA_SARMIENTO_SARMIENTO,
                     LINEA_MITRE_RETIRO_TIGRE,
                     LINEA_MITRE_RETIRO_MITRE,
                     LINEA_MITRE_RETIRO_SUAREZ,
                     LINEA_ROCA_CONSTITUCION_LA_PLATA,
                     LINEA_ROCA_CONSTITUCION_CLAYPOLE,
                     LINEA_ROCA_CLAYPOLE_GUTIERREZ,
                     LINEA_ROCA_CONSTITUCION_ALEJANDRO_KORN,
                     LINEA_ROCA_CONSTITUCION_EZEIZA,
                     LINEA_ROCA_TEMPERLEY_HAEDO,
                     LINEA_ROCA_EZEIZA_CANUELAS,
                     LINEA_BELGRANO_SUR_BUENOS_AIRES_BELGRANO,
                     LINEA_BELGRANO_PTE_ALSINA_ALDO_BONZI,
                     LINEA_BELGRANO_BUENOS_AIRES_GONZALEZ_CATAN,             
                     LINEA_SAN_MARTIN_SAN_MARTIN,
                     TREN_DE_LA_COSTA_TREN_DE_LA_COSTA};


enum estaciones {ESTACION_SARMIENTO_ONCE,
                 ESTACION_SARMIENTO_CABALLITO, // Linea Sarmiento
                 ESTACION_SARMIENTO_FLORES,
                 ESTACION_SARMIENTO_FLORESTA,
                 ESTACION_SARMIENTO_VILLA_LURO,
                 ESTACION_SARMIENTO_LNIERS,
                 ESTACION_SARMIENTO_CIUDADELA,
                 ESTACION_SARMIENTO_RAMOS_MEJIA,
                 ESTACION_SARMIENTO_HAEDO,
                 ESTACION_SARMIENTO_MORON,
                 ESTACION_SARMIENTO_CASTELAR,
                 ESTACION_SARMIENTO_ITUZAINGO,
                 ESTACION_SARMIENTO_PADUA,
                 ESTACION_SARMIENTO_MERLO,
                 ESTACION_SARMIENTO_PASO_DEL_REY,
                 ESTACION_SARMIENTO_MORENO,
                 ESTACION_MITRE_TIGRE_RETIRO, // Linea Mitre Ramal Tigre
                 ESTACION_MITRE_TIGRE_LISANDRO_DE_LA_TORRE,
                 ESTACION_MITRE_TIGRE_BELGRANO_C,
                 ESTACION_MITRE_TIGRE_NUNEZ,
                 ESTACION_MITRE_TIGRE_RIVADAVIA,
                 ESTACION_MITRE_TIGRE_VICENTE_LOPEZ,
                 ESTACION_MITRE_TIGRE_OLIVOS,
                 ESTACION_MITRE_TIGRE_LA_LUCILA,
                 ESTACION_MITRE_TIGRE_MARTINEZ,
                 ESTACION_MITRE_TIGRE_ACASSUSO,
                 ESTACION_MITRE_TIGRE_SAN_ISIDRO_C,
                 ESTACION_MITRE_TIGRE_BECCAR,
                 ESTACION_MITRE_TIGRE_VICTORIA,
                 ESTACION_MITRE_TIGRE_VIRREYES,
                 ESTACION_MITRE_TIGRE_SAN_FERNANDO_C,
                 ESTACION_MITRE_TIGRE_CARUPA,
                 ESTACION_MITRE_TIGRE_TIGRE,
                 ESTACION_MITRE_MITRE_RETIRO, // Linea Mitre Ramal Mitre
                 ESTACION_MITRE_MITRE_3_DE_FEBRERO,
                 ESTACION_MITRE_MITRE_MINISTRO_CARRANZA,
                 ESTACION_MITRE_MITRE_COLEGIALES,
                 ESTACION_MITRE_MITRE_BELGRANO_R,
                 ESTACION_MITRE_MITRE_COGHLAN,
                 ESTACION_MITRE_MITRE_SAAVEDRA,
                 ESTACION_MITRE_MITRE_JUAN_B_JUSTO,
                 ESTACION_MITRE_MITRE_FLORIDA,
                 ESTACION_MITRE_MITRE_CETRANGOLO,
                 ESTACION_MITRE_MITRE_MITRE,
                 ESTACION_MITRE_SUAREZ_RETIRO, // Linea Mitre Ramal Suarez
                 ESTACION_MITRE_SUAREZ_3_DE_FEBRERO,
                 ESTACION_MITRE_SUAREZ_MINISTRO_CARRANZA,
                 ESTACION_MITRE_SUAREZ_COLEGIALES,
                 ESTACION_MITRE_SUAREZ_BELGRANO_R,
                 ESTACION_MITRE_SUAREZ_DRAGO,
                 ESTACION_MITRE_SUAREZ_URQUIZA,
                 ESTACION_MITRE_SUAREZ_PUEYRREDON,
                 ESTACION_MITRE_SUAREZ_MIGUELETE,
                 ESTACION_MITRE_SUAREZ_SAN_MARTIN,
                 ESTACION_MITRE_SUAREZ_SAN_ANDRES,
                 ESTACION_MITRE_SUAREZ_MALAVER,
                 ESTACION_MITRE_SUAREZ_VILLA_BALLESTER,
                 ESTACION_MITRE_SUAREZ_CHILAVERT,
                 ESTACION_MITRE_SUAREZ_SUAREZ,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_CONSTITUCION, // Linea Roca Ramal Constitucion - La Plata
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_SANTILLAN_Y_KOSTEKI,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_SARANDI,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_VILLA_DOMINICO,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_WILDER,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_DON_BOSCO,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_BERNAL,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_QUILMES,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_EZPELETA,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_BERAZATEGUI,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_PLATANOS,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_HUDSON,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_PEREYRA,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_VILLA_ELISA,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_CITY_BELL,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_GONNET,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_RINGUELET,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_TOLOSA,
                 ESTACION_ROCA_CONSTITUCION_LA_PLATA_LA_PLATA,
                 ESTACION_ROCA_CONSTITUCION_CLAYPOLE_CONSTITUCION, // Linea Roca Ramal Constitucion - Claypole
                 ESTACION_ROCA_CONSTITUCION_CLAYPOLE_HIPOLITO_YRIGOYEN,
                 ESTACION_ROCA_CONSTITUCION_CLAYPOLE_SANTILLAN_Y_KOSTEKI,
                 ESTACION_ROCA_CONSTITUCION_CLAYPOLE_GERLI,
                 ESTACION_ROCA_CONSTITUCION_CLAYPOLE_LANUS,
                 ESTACION_ROCA_CONSTITUCION_CLAYPOLE_REMEDIOS_DE_ESCALADA,
                 ESTACION_ROCA_CONSTITUCION_CLAYPOLE_BANDFIELD,
                 ESTACION_ROCA_CONSTITUCION_CLAYPOLE_LOMAS_DE_ZAMORA,
                 ESTACION_ROCA_CONSTITUCION_CLAYPOLE_TEMPERLEY,
                 ESTACION_ROCA_CONSTITUCION_CLAYPOLE_JOSE_MARMOL,
                 ESTACION_ROCA_CONSTITUCION_CLAYPOLE_RAFAEL_CALZADA,
                 ESTACION_ROCA_CONSTITUCION_CLAYPOLE_CLAYPOLE,
                 ESTACION_ROCA_CLAYPOLE_GUTIERREZ_CLAYPOLE, // Linea Roca Ramal Claypole - Gutierrez
                 ESTACION_ROCA_CLAYPOLE_GUTIERREZ_DANTE_ARDIGO,
                 ESTACION_ROCA_CLAYPOLE_GUTIERREZ_FLORENCIO_VARELA,
                 ESTACION_ROCA_CLAYPOLE_GUTIERREZ_ZEBALLOS,
                 ESTACION_ROCA_CLAYPOLE_GUTIERREZ_BOSQUES,
                 ESTACION_ROCA_CLAYPOLE_GUTIERREZ_SANTA_SOFIA,
                 ESTACION_ROCA_CLAYPOLE_GUTIERREZ_GUTIERREZ,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_CONSTITUCION, // Linea Roca Ramal Constitucion - Alejandro Korn
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_HIPOLITO_YRIGOYEN,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_SANTILLAN_Y_KOSTEKI,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_GERLI,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_LANUS,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_REMEDIOS_DE_ESCALADA,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_BANDFIELD,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_LOMAS_DE_ZAMORA,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_TEMPERLEY,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_ADROGUE,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_BURZACO,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_LONGCHAMPS,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_GLEW,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_GUERNICA,
                 ESTACION_ROCA_CONSTITUCION_ALEJANDRO_KORN_ALEJANDRO_KORN,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_CONSTITUCION, // Linea Roca Ramal Constitucion - Ezeiza
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_HIPOLITO_YRIGOYEN,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA__SANTILLAN_Y_KOSTEKI,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA__GERLI,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_LANUS,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_REMEDIOS_DE_ESCALADA,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_BANDFIELD,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_LOMAS_DE_ZAMORA,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_TEMPERLEY,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_TURDERA,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_LLAVALLOL,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_LUIS_GUILLON,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_MONTE_GRANDE,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_EL_JAGUEL,
                 ESTACION_ROCA_CONSTITUCION_EZEIZA_EZEIZA,
                 ESTACION_ROCA_TEMPERLEY_HAEDO_TEMPERLEY, // Linea Roca Ramal Temperley - Haedo
                 ESTACION_ROCA_TEMPERLEY_HAEDO_HOSPITAL_ESPANOL,
                 ESTACION_ROCA_TEMPERLEY_HAEDO_SANTA_CATALINA,
                 ESTACION_ROCA_TEMPERLEY_HAEDO_JUAN_XXIII,
                 ESTACION_ROCA_TEMPERLEY_HAEDO_KM_34,
                 ESTACION_ROCA_TEMPERLEY_HAEDO_TURNER,
                 ESTACION_ROCA_TEMPERLEY_HAEDO_AGUSTIN_DE_ELIA,
                 ESTACION_ROCA_TEMPERLEY_HAEDO_TABLADA,
                 ESTACION_ROCA_TEMPERLEY_HAEDO_SAN_JUSTO,
                 ESTACION_ROCA_TEMPERLEY_HAEDO_INGENIERO_S_BRIAN,
                 ESTACION_ROCA_TEMPERLEY_HAEDO_HAEDO,
                 ESTACION_ROCA_EZEIZA_CANUELAS_EZEIZA, // Linea Roca Ramal Ezeiza - Cañuelas
                 ESTACION_ROCA_EZEIZA_CANUELAS_UNION_FERROVIARIA,
                 ESTACION_ROCA_EZEIZA_CANUELAS_TRISTAN_SUAREZ,
                 ESTACION_ROCA_EZEIZA_CANUELAS_CARLOS_SPEGAZZINI,
                 ESTACION_ROCA_EZEIZA_CANUELAS_MAXIMO_PAZ,
                 ESTACION_ROCA_EZEIZA_CANUELAS_VICENTE_CASARES,
                 ESTACION_ROCA_EZEIZA_CANUELAS_ALEJANDRO_PETION,
                 ESTACION_ROCA_EZEIZA_CANUELAS_APEADERO_KLOOSTERMAN,
                 ESTACION_ROCA_EZEIZA_CANUELAS_RICARDO_LEVENE,
                 ESTACION_ROCA_EZEIZA_CANUELAS_CANUELAS,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_BUENOS_AIRES, // Linea Belgrano Sur Ramal Buenos Aires - M.C.G. Belgrano
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_DR_SAENZ,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_VILLA_SOLDATI,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_PRESIDENTE_ILLIA,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_VILLA_LUGANO,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_VILLA_MADERO,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_MARINOS_DEL_FOURNIER,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_TAPIALES,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_ALDO_BONZI,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_SANCHEZ_DE_MENDEVILLE,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_JOSE_INGENIEROS,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_JUSTO_VILLEGAS,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_ISIDRO_CASANOVA,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_RAFAEL_CASTILLO,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_MERLO_GOMEZ,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_LIBERTAD,
                 ESTACION_BELGRANO_SUR_BUENOS_AIRES_BELGRANO_MARINOS_BELGRANO,
                };
                 
                 
                 
                 
//titulos de lineas
char lineas_trenes[6][20] = {"Sarmiento",
                             "Mitre",
                             "Roca",
                             "Belgrano Sur",
                             "San Martín",
                             "Tren de la Costa"};

//titulos de ramales...
char ramales_mitre[3][32] = {"Retiro - Tigre",
                             "Retiro - Mitre",
                             "Retiro - J.L. Suárez"};

char ramales_roca[8][32] = {"Constitución - La Plata",
                            "Constitución - Claypole",
                            "Retiro - J.L. Suárez",
                            "Claypole - Gutierrez",
                            "Constitución - Alejandro Korn",
                            "Constitución - Ezeiza",
                            "Temperley - Haedo",
                            "Ezeiza - Cañuelas"};

char ramales_belgrano_sur[3][32] = {"Buenos Aires - M.C.G. Belgrano",
                                    "Pte Alsina - Aldo Bonzi",
                                    "Buenos Aires - Gonzalez Catán"};

//titulos de estaciones
char estaciones_sarmiento[16][32] = {"Once",
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
                                     "Moreno"
                                    };

char estaciones_mitre_retiro_tigre[17][32] = {"Retiro",
                                              "Lisandro de la Torre",
                                              "Belgrano C",
                                              "Núñez",
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

char estaciones_mitre_retiro_mitre[11][32] = {"Retiro",
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

char estaciones_mitre_retiro_suarez[15][32] = {"Retiro",
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

//TODO: PASAR ESTOS A ARREGLO:
char estacionConstitucion[32] = "Constitución";
char estacionSantillanYKosteki[32] = "Santillán y Kosteki";
char estacionSarandi[32] = "Sarandí";
char estacionVillaDominico[32] = "Villa Domínico";
char estacionWilde[32] = "Wilde";
char estacionDonBosco[32] = "Don Bosco";
char estacionBernal[32] = "Bernal";
char estacionQuilmes[32] = "Quilmes";
char estacionEzpeleta[32] = "Ezpeleta";
char estacionBerazategui[32] = "Berazategui";
char estacionPlatanos[32] = "Plátanos";
char estacionHudson[32] = "Hudson";
char estacionPereyra[32] = "Pereyra";
char estacionVillaElisa[32] = "Villa Elisa";
char estacionCityBell[32] = "City Bell";
char estacionGonnet[32] = "Gonnet";
char estacionRinguelet[32] = "Ringuelet";
char estacionTolosa[32] = "Tolosa";
char estacionLaPlata[32] = "La Plata";

char estacionHipolitoYrigoyen[32] = "Hipólito Yrigoyen";
char estacionGerli[32] = "Gerli";
char estacionLanus[32] = "Lanús";
char estacionRemediosDeEscalada[32] = "Remedios de Escalada";
char estacionBandfield[32] = "Bandfield";
char estacionLomasDeZamora[32] = "LomasDeZamora";
char estacionTemperley[32] = "Temperley";
char estacionJoseMarmol[32] = "José mármol";
char estacionRafaelCalzada[32] = "Rafael Calzada";
char estacionClaypole[32] = "Claypole";

char estacionDanteArdigo[32] = "Dante Ardigó";
char estacionFlorencioVarela[32] = "Florencio Varela";
char estacionZeballos[32] = "Zeballos";
char estacionBosques[32] = "Bosques";
char estacionSantaSofia[32] = "Santa Sofía";
char estacionGutierrez[32] = "Gutiérrez";

char estacionAdrogue[32] = "Adrogué";
char estacionBurzaco[32] = "Burzaco";
char estacionLongchamps[32] = "Longchamps";
char estacionGlew[32] = "Glew";
char estacionGuernica[32] = "Guernica";
char estacionAlejandroKorn[32] = "Alejandro Korn";

char estacionTurdera[32] = "Turdera";
char estacionLlavallol[32] = "Llavallol";
char estacionLuisGuillon[32] = "Luis Guillón";
char estacionMonteGrande[32] = "Monte Grande";
char estacionElJaguel[32] = "El Jagüel";
char estacionEzeiza[32] = "Ezeiza";

char estacionHospitalEspanol[32] = "Hospital Español";
char estacionSantaCatalina[32] = "Santa Catalina";
char estacionJuanXXIII[32] = "Juan XXIII";
char estacionKM34[32] = "KM 34";
char estacionPTurner[32] = "P. Turner";
char estacionAgustinDeElia[32] = "Agustín de Elía";
char estacionTablada[32] = "Tablada";
char estacionSanJusto[32] = "San Justo";
char estacionIngenieroSBrian[32] = "Ingeniero S. Brian";

char estacionUnionFerroviaria[32] = "Unión Ferroviaria";
char estacionTristanSuarez[32] = "Tristán Suárez";
char estacionCarlosSpegazzini[32] = "Carlos Spegazzini";
char estacionMaximoPaz[32] = "Máximo Paz";
char estacionVicenteCasares[32] = "Vicente Casares";
char estacionAlejandroPetion[32] = "Alejandro Petión";
char estacionApeaderoKloosterman[32] = "Apeadero Kloosterman";
char estacionRicardoLavene[32] = "Ricardo Lavene";
char estacionCauelas[32] = "Cañuelas";

char estacionBuenosAires[32] = "Buenos Aires";
char estacionDrSaenz[32] = "Dr. Sáenz";
char estacionVillaSoldati[32] = "Villa Soldati";
char estacionPresidenteIllia[32] = "Presidente Illia";
char estacionVillaLugano[32] = "Villa Lugano";
char estacionVillaMadero[32] = "Villa Madero";
char estacionMarinosDelFournier[32] = "Marinos del Fournier";
char estacionTapiales[32] = "Tapiales";
char estacionAldoBonzi[32] = "Aldo Bonzi";
char estacionSanchezDeMendeville[32] = "Sánchez de Mendeville";
char estacionJoseIngenieros[32] = "José Ingenieros";
char estacionJustoVillegas[32] = "Justo Villegas";
char estacionIsidroCasanova[32] = "Isidro Casanova";
char estacionRafaelCastillo[32] = "Rafael Castillo";
char estacionMerloGomez[32] = "Merlo Gómez";
char estacionLibertad[32] = "Libertad";
char estacionMarinosCGBelgrano[32] = "Marinos C. G. Belgrano";
                 
                 
                 