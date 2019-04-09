#pragma once

///////////////////////////////////////////////////////////////////////////
//Llibreria grafica
#include "lib/libreria.h"
///////////////////////////////////////////////////////////////////////////

//========================================================================
// Mida Pantalla
const int MIDA_X = 520;
const int MIDA_Y = 520;

//========================================================================
// Inici del tauler respecte la cantonada superior esquerre
const int INI_PANTALLA_X = 0;
const int INI_PANTALLA_Y = 0;

//========================================================================
// Fi del tauler respecte la cantonada inferior dreta
const int FI_PANTALLA_X = 520;
const int FI_PANTALLA_Y = 520;

// Mida d'una casella del tauler
const int MIDA_CASELLA = 52;

// Tipos de barcos diferentes
const int kShipTypes = 4;

// Tama�o maximo de un barco
const int kMaxShipSize = 4;

// Cantidad minima de barcos de cada tipo
const int kMinShipQuantity = 1;

// Numero maximo de barcos por jugador
const int kMaxShipsPerPlayer = 10;

void joc();

/*----- END --------------*/