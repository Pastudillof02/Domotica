/*
 * domoBoard.cpp
 *
 *  Created on: 09/03/2015
 *      Author: jctejero
 *
 *  Modified on: 16/03/2022
 */

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "domoBoard.h"
#include "../debuglog.h"

// Constructors ////////////////////////////////////////////////////////////////

DomoBoard::DomoBoard()
{
	//Definimos pin's DomoBoard.
	pinMode(BUTTON1_P, INPUT);
	pinMode(BUTTON2_P, INPUT);
	pinMode(BTN_OPT_P, INPUT);      	//Pin Entrada Optocoplada

	pinMode(RELE_P, OUTPUT);
	pinMode(TRIAC_P, OUTPUT);

/*
	pinMode(EN_485, OUTPUT);

	RS485_RxTx(RX485_RX);				//Inicialmente, configuramos el RX485 para recibir
*/

	BOTON1.pin 			= BUTTON1_P;
	BOTON1.valor 		= LOW;
	BOTON1.valor_Df 	= LOW;
	BOTON1.Activo 		= true;
	BOTON1.eSensor  	= S_DIGITAL;
	BOTON1.name			= "BOT�N 1";
	BOTON1.SensorEvent  = NULL;

	BOTON2.pin 			= BUTTON2_P;
	BOTON2.valor 		= LOW;
	BOTON2.valor_Df 	= LOW;
	BOTON2.Activo 		= true;
	BOTON2.eSensor  	= S_DIGITAL;
	BOTON2.name			= "BOT�N 2";
	BOTON2.SensorEvent	= NULL;

	BTN_OPT.pin 		= BTN_OPT_P;
	BTN_OPT.valor 		= HIGH;
	BTN_OPT.valor_Df	= HIGH;
	BTN_OPT.Activo 		= true;
	BTN_OPT.eSensor 	= S_DIGITAL;
	BTN_OPT.name		= "Pulsador Optocoplado";
	BTN_OPT.SensorEvent = NULL;

	//Inicializaci�n del sensor de movimiento
	PIR_MOV.pin 		= PIR_P;
	PIR_MOV.valor 		= LOW;
	PIR_MOV.valor_Df 	= LOW;  //HIGH; para el sensor original
	PIR_MOV.Activo 		= true;
	PIR_MOV.eSensor 	= S_DIGITAL;
	PIR_MOV.name 		= "PIR (Sensor de Movimiento)";
	PIR_MOV.SensorEvent = NULL;

	POT1.pin 			= POT1_P;
	POT1.Activo 		= true;
	POT1.eSensor		= S_ANALOGICO;
	POT1.name			= "Potenciometro 1";

	POT2.pin 			= POT2_P;
	POT2.Activo 		= true;
	POT2.eSensor		= S_ANALOGICO;
	POT2.name			= "Potenciometro 2";

	RELE.pin 			= RELE_P;
	RELE.estado 		= LOW;

	TRIAC.pin 			= TRIAC_P;
	TRIAC.estado 		= LOW;
}

void DomoBoard::leerAllSensor(void){
	leerSensor(&BOTON1);
	leerSensor(&BOTON2);
	leerSensor(&BTN_OPT);
	leerSensor(&PIR_MOV);
	leerSensor(&POT1);
	leerSensor(&POT2);
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
			//Serial.print("El estado de "); Serial.print(Sensor->name); Serial.print(" es: "); Serial.println(Sensor->valor);
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
	if(Actuator->estado == val)
		return;

	digitalWrite(Actuator->pin, val);
	Actuator->estado = val;
}

void DomoBoard::manageSensorActuators(TManagerActuators *managerActuators, bool val){
	if(managerActuators->count() > 0){
		for(uint8_t i = 0; i < managerActuators->count(); i++){
			DomoBoard::setActuator(managerActuators->peek(i), val);
		}
	}
}

void DomoBoard::clear_Actuators(){
	BOTON1.managerActuators.clear();
	BOTON1.SensorEvent = NULL;
	BOTON2.managerActuators.clear();
	BOTON2.SensorEvent = NULL;
	BTN_OPT.managerActuators.clear();
	BTN_OPT.SensorEvent = NULL;
	PIR_MOV.managerActuators.clear();
	PIR_MOV.SensorEvent = NULL;
	POT1.SensorEvent = NULL;
	POT1.managerActuators.clear();
	POT2.SensorEvent = NULL;
	POT2.managerActuators.clear();
}

void DomoBoard::RS485_RxTx(TRX485_rxtx rxtx){
	switch(rxtx){
	case RX485_RX:
		while (!(UCSR0A & (1 << TXC0)));
		digitalWrite(EN_485, LOW);
		break;

	case RX485_TX:
		digitalWrite(EN_485, HIGH);
		delay(1);
		break;
	}
}




DomoBoard domoboard;

