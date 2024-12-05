/*
 * utils_domoBoard.cpp
 *
 *  Created on: 10/03/2015
 *      Author: jctejero
 *
 *  Modified on: 16/03/2022
 */

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "utils_domoBoard.h"
#include "HardwareSerial.h"
#include	"Gest_Modbus.h"
#include "DomoBoard/domoBoard.h"


void Interruptor(void *Sensor)
{
	if(((ptsSensor)Sensor)->valor_Df == ((ptsSensor)Sensor)->valor){
		Serial.print(((ptsSensor)Sensor)->name);
		Serial.print(" : Interruptor --> ");
		if(((ptsSensor)Sensor)->pin == domoboard.BOTON1.pin)
		{
			Serial.println(Cregs[MB_RELE]);
			switch (Cregs[MB_RELE])
			{
				case 0x00:
					Cregs[MB_RELE] = 0xFF;
					break;
				default:
					Cregs[MB_RELE] = 0x00;
					break;
			}
			mbs.writecoil(MB_RELE);

		}
		else if(((ptsSensor)Sensor)->pin == domoboard.BOTON2.pin)
		{
			Serial.println(Cregs[MB_TRIAC]);
			switch (Cregs[MB_TRIAC])
			{
				case 0x00:
					Cregs[MB_TRIAC] = 0xFF;
					break;
				default:
					Cregs[MB_TRIAC] = 0x00;
					break;
			}
			mbs.writecoil(MB_TRIAC);

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

	DomoBoard::manageSensorActuators(&(sensor->managerActuators), !(sensor->valor_Df == sensor->valor));
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
		//DomoBoard::setActuator(&domoboard.RELE, valor);

		DomoBoard::manageSensorActuators(&(sensor->managerActuators), valor);
	}
}







