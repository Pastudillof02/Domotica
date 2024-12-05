/*
 * ModbusDomoboard.cpp
 *
 *  Created on: 11 mar. 2020
 *      Author: jctejero
 *
 *  Modified: 03/04/2021
 *  Modified on: 16/03/2022
 */

#include "ModbusDomoboard.h"

/****************************************************************************/
/***        Variables Locales                                             ***/
/****************************************************************************/

/***************************************************
 * Definici�n Bancos de registros usados en ModBus *
 ***************************************************/
uint16_t	Cregs[MB_O_COILS];		//Registros para "Dicrete Output Coils"
uint16_t	Dregs[MB_I_CONTATCS];	//Registros para "Dicrete Input Contacts"
uint16_t	Aregs[MB_A_REGS];		//Registros para "Analog Output Holding Registers"

ModbusDomoboard mbDomoboard;

ModbusDomoboard::ModbusDomoboard():DomoBoard() {
	//*****  Initialize ModBus Sensors  ****

	//Initialize BOTON1 for ModBus
	BOTON1.Sensor = &(DomoBoard::BOTON1);
	BOTON1.mbRegs = &Dregs[MB_BOTON1];
	BOTON1.Aux = LOW;

	//Initialize BOTON1 for ModBus
	BOTON2.Sensor = &(DomoBoard::BOTON2);
	BOTON2.mbRegs = &Dregs[MB_BOTON2];
	BOTON2.Aux = LOW;

	//Initialize BOTON1 for ModBus
	BTN_OPT.Sensor = &(DomoBoard::BTN_OPT);
	BTN_OPT.mbRegs = &Dregs[MB_BTNOPT];

	SNS_MOV.Sensor = &(DomoBoard::SNS_MOV);
	SNS_MOV.mbRegs = &Dregs[MB_SNSMOV];
	SNS_MOV.Aux = LOW;

	RELE.actuator = &(DomoBoard::RELE);
	RELE.mbRegs = &Cregs[MB_RELE];

	TRIAC.actuator = &(DomoBoard::TRIAC);
	TRIAC.mbRegs = &Cregs[MB_TRIAC];

	Aregs[MB_TIME] = 0x03;
}

void ModbusDomoboard::leerAllSensor(void){
	leerSensor(&BOTON1);
	leerSensor(&BOTON2);
	leerSensor(&BTN_OPT);
	leerSensor(&SNS_MOV);
}

void ModbusDomoboard::leerSensor(TpmbSensor Sensor){

	DomoBoard::leerSensor(Sensor->Sensor);

	//compueba si el valor le�do por el sensor difiere del valor almacenado en el registro correspondiente
	//del banco de registros
	if((int16_t)(*(Sensor->mbRegs)) != Sensor->Sensor->valor){
		//Estado Sensor ha cambiado
		//Se actualiza el registro correspondiente con el nuevo valor le�do en el sensor.
		*(Sensor->mbRegs) = Sensor->Sensor->valor;
		//Se in�cia el evento asociado a la actualizaci�n del banco de registro correpondiente
		if(Sensor->mbSensorEvent != NULL){
			Sensor->mbSensorEvent(Sensor);
		}
	}
}

void	ModbusDomoboard::clear_Actuators(){
	//DomoBoard::clear_Actuators();

	BOTON1.mbActuators.clear();
	BOTON1.mbSensorEvent = NULL;
	BOTON2.mbActuators.clear();
	BOTON2.mbSensorEvent = NULL;
	BTN_OPT.mbActuators.clear();
	BTN_OPT.mbSensorEvent = NULL;

}


void  ModbusDomoboard::setmbActuator(TmbActuator *Actuator, TStateDigitalDev val){
	bool newVal = (bool)val;

	if(val == TOGGLE){

		newVal = !(*Actuator->mbRegs);
	}

	if(*(Actuator->mbRegs) != newVal){
		*(Actuator->mbRegs) = newVal;

		setActuator(Actuator->actuator, *(Actuator->mbRegs));

	}
}

void ModbusDomoboard::setModBusSlave(ModbusSlave *mbSlave){
	mbs = mbSlave;
}

void ModbusDomoboard::manager_mbActuators(TmbActuators *Actuators, TStateDigitalDev val){

	for(int n = 0; n < Actuators->count(); n++){
		setmbActuator(Actuators->peek(n), val);
	}

}
