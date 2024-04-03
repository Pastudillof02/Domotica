/*
 * utils_domoBoard.cpp
 *
 *  Created on: 10/03/2015
 *      Author: jctejero
 */

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "utils_domoBoard.h"
#include "HardwareSerial.h"

void Interruptor(void *Sensor)
{
	if(((ptsSensor)Sensor)->valor_Df == ((ptsSensor)Sensor)->valor){
		Serial.print(((ptsSensor)Sensor)->name);
		Serial.print(" : Interruptor --> ");
		if(((ptsSensor)Sensor)->Aux == OFF){
			((ptsSensor)Sensor)->Aux = ON;
			Serial.println("ON");
		}else{
			((ptsSensor)Sensor)->Aux = OFF;
			Serial.println("OFF");
		}
	}
}

void Pulsado_Soltado(void *Sensor){
	ptsSensor sensor = reinterpret_cast<ptsSensor>(Sensor);

	Serial.print(sensor->name);
	if(sensor->valor_Df == sensor->valor){
		Serial.println(" --> Soltado");
	}else{
		Serial.println(" --> Pulsado");
	}
}

void conmutador(void *Sensor)
{
	static int valor = OFF;

	ptsSensor sensor = reinterpret_cast<ptsSensor>(Sensor);

	if(sensor->valor_Df == sensor->valor){
		Serial.print("Conmutador --> ");
		if(valor == OFF){
			valor = ON;
			Serial.println("ON");
		}else{
			valor = OFF;
			Serial.println("OFF");
		}
		//Actualiza Actuadores
		DomoBoard::setActuator(&domoboard.RELE, valor);
	}
}

void pulsado_soltado_triac_rele(void *Sensor){
	ptsSensor sensor = reinterpret_cast<ptsSensor>(Sensor);

	Serial.print(sensor->name);
	if(sensor->valor_Df == sensor->valor)
	{
		Serial.println(" --> Soltado");
		if(sensor->pin == 3)
		{
			DomoBoard::setActuator(&domoboard.RELE, OFF);
		}
		else if(sensor->pin == 10)
		{
			DomoBoard::setActuator(&domoboard.TRIAC, OFF);
		}
	}
	else
	{
		Serial.println(" --> Pulsado");
		if(sensor->pin == 3)
		{
			DomoBoard::setActuator(&domoboard.RELE, ON);
		}
		else if(sensor->pin == 10)
		{
			DomoBoard::setActuator(&domoboard.TRIAC, ON);
		}
	}
}

void interruptor_triac_rele(void *Sensor)
{
	if(((ptsSensor)Sensor)->valor_Df == ((ptsSensor)Sensor)->valor){
			Serial.print(((ptsSensor)Sensor)->name);
			Serial.print(" : Interruptor --> ");
			if(((ptsSensor)Sensor)->Aux == OFF){
				((ptsSensor)Sensor)->Aux = ON;
				Serial.println("ON");
				if(((ptsSensor)Sensor)->pin == 3)
				{
					DomoBoard::setActuator(&domoboard.RELE, ON);
				}
				else if(((ptsSensor)Sensor)->pin == 10)
				{
					DomoBoard::setActuator(&domoboard.TRIAC, ON);
				}
			}else{
				((ptsSensor)Sensor)->Aux = OFF;
				Serial.println("OFF");
				if(((ptsSensor)Sensor)->pin == 3)
				{
					DomoBoard::setActuator(&domoboard.RELE, OFF);
				}
				else if(((ptsSensor)Sensor)->pin == 10)
				{
					DomoBoard::setActuator(&domoboard.TRIAC, OFF);
				}
			}
		}
}

void conmutador_triac_rele(void *Sensor)
{
	static int valor = OFF;

	ptsSensor sensor = reinterpret_cast<ptsSensor>(Sensor);

	if(sensor->valor_Df == sensor->valor){
		Serial.print("Conmutador --> ");
		if(valor == OFF){
			valor = ON;
			Serial.println("ON");
		}else{
			valor = OFF;
			Serial.println("OFF");
		}
		//Actualiza Actuadores
		DomoBoard::setActuator(&domoboard.RELE, valor);
		DomoBoard::setActuator(&domoboard.TRIAC, valor);
	}
}







