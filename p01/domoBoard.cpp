/*
 * domoBoard.cpp
 *
 *  Created on: 09/03/2015
 *      Author: jctejero
 */

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "domoBoard.h"

// Constructors ////////////////////////////////////////////////////////////////

DomoBoard::DomoBoard()
{
	//Definimos pin's DomoBoard.
	pinMode(BUTTON1_P, INPUT);
	pinMode(BUTTON2_P, INPUT);
	pinMode(BTN_OPT_P, INPUT);      	//Pin Entrada Optocoplada
	pinMode(RELE_S, OUTPUT);

	BOTON1.sSensor.pin 			= BUTTON1_P;
	BOTON1.sSensor.valor 		= LOW;
	BOTON1.sSensor.Activo 		= true;
	BOTON1.sSensor.eSensor  	= S_DIGITAL;
	BOTON1.sSensor.name			= "BOT�N 1";
	BOTON1.sSensor.valor_Df 	= LOW;

	BOTON2.sSensor.pin 			= BUTTON2_P;
	BOTON2.sSensor.valor 		= LOW;
	BOTON2.sSensor.Activo 		= true;
	BOTON2.sSensor.eSensor  	= S_DIGITAL;
	BOTON2.sSensor.name			= "BOT�N 2";
	BOTON2.sSensor.valor_Df 	= LOW;

	BTN_OPT.sSensor.pin 		= BTN_OPT_P;
	BTN_OPT.sSensor.valor 		= HIGH;
	BTN_OPT.sSensor.Activo 		= true;
	BTN_OPT.sSensor.eSensor 	= S_DIGITAL;
	BTN_OPT.sSensor.name		= "Pulsador Optocoplado";
	BTN_OPT.sSensor.valor_Df	= HIGH;

	RELE.pin 			= RELE_S;
	RELE.estado 		= false;
	RELE.Activo 		= true;
	RELE.name			= "Rele";
}

void DomoBoard::leerAllSensor(void){
	leerSensor(&BOTON1);
	leerSensor(&BOTON2);
	leerSensor(&BTN_OPT);
}


void  DomoBoard::leerSensor(ptsSensor *Sensor){
	int valor = 0;

	if(Sensor->sSensor.Activo){
		switch (Sensor->sSensor.eSensor)
		{
		case S_DIGITAL:
			valor = digitalRead(Sensor->sSensor.pin);
			break;

		case S_ANALOGICO:
			valor = analogRead(Sensor->sSensor.pin);
			break;
		}

		if(Sensor->sSensor.valor != valor)
		{
			Sensor->sSensor.valor = valor;

			//Si hay un cambio en el estado del sensor llamamos a la aplicaci�n asociada
			if(Sensor->SensorEvent != NULL)
				Sensor->SensorEvent(&(Sensor->sSensor));
		}
	}
}


DomoBoard domoboard;

