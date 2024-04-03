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

	pinMode(RELE_P, OUTPUT);
	pinMode(TRIAC_P, OUTPUT);

	BOTON1.pin 			= BUTTON1_P;
	BOTON1.valor 		= LOW;
	BOTON1.valor_Df 	= LOW;
	BOTON1.Activo 		= true;
	BOTON1.eSensor  	= S_DIGITAL;
	BOTON1.name			= "BOT�N 1";

	BOTON2.pin 			= BUTTON2_P;
	BOTON2.valor 		= LOW;
	BOTON2.valor_Df 	= LOW;
	BOTON2.Activo 		= true;
	BOTON2.eSensor  	= S_DIGITAL;
	BOTON2.name			= "BOT�N 2";

	BTN_OPT.pin 		= BTN_OPT_P;
	BTN_OPT.valor 		= HIGH;
	BTN_OPT.valor_Df	= HIGH;
	BTN_OPT.Activo 		= true;
	BTN_OPT.eSensor 	= S_DIGITAL;
	BTN_OPT.name		= "Pulsador Optocoplado";



	RELE.pin 			= RELE_P;
	RELE.estado 		= LOW;

	TRIAC.pin			= TRIAC_P;
	TRIAC.estado 		= LOW;
}

void DomoBoard::leerAllSensor(void){
	leerSensor(&BOTON1);
	leerSensor(&BOTON2);
	leerSensor(&BTN_OPT);
}


void  DomoBoard::leerSensor(ptsSensor Sensor){
	int valor = 0;

	if(Sensor->Activo){
		switch (Sensor->eSensor)
		{
		case S_DIGITAL:
			valor = digitalRead(Sensor->pin);
			break;

		case S_ANALOGICO:
			valor = analogRead(Sensor->pin);
			break;
		}

		if(Sensor->valor != valor)
		{
			Sensor->valor = valor;

			//Si hay un cambio en el estado del sensor llamamos a la aplicaci�n asociada
			if(Sensor->SensorEvent != NULL)
				Sensor->SensorEvent(Sensor);
		}
	}
}

void  DomoBoard::setActuator(tsActuator *Actuator, bool val){
	digitalWrite(Actuator->pin, val);
	Actuator->estado = val;
}


DomoBoard domoboard;

