/*
 * config_practicas.cpp
 *
 *  Created on: 10/03/2015
 *      Author: jctejero
 *
 *  Modified on: 16/03/2022
 */

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include	"config_practicas.h"
#include 	"utils_domoboard.h"

/****************************************************************************/
/***                 Functions                                            ***/
/****************************************************************************/

void clear_Actuators(){
	domoboard.clear_Actuators();
	mbDomoboard.clear_Actuators();
}

void config_practica1_apt_1(void){

	clear_Actuators();

	domoboard.BOTON1.SensorEvent = Pulsado_Soltado;

	domoboard.BOTON2.SensorEvent = Pulsado_Soltado;

	domoboard.BTN_OPT.SensorEvent = Pulsado_Soltado;
}

void config_practica1_apt_2(void){

	clear_Actuators();

	domoboard.BOTON1.SensorEvent = Interruptor;
	domoboard.BOTON1.Aux = OFF;

	domoboard.BOTON2.SensorEvent = Interruptor;
	domoboard.BOTON2.Aux = OFF;

	domoboard.BTN_OPT.SensorEvent = Interruptor;
	domoboard.BTN_OPT.Aux = OFF;
}

void config_practica1_apt_3(void){

	clear_Actuators();

	domoboard.BOTON1.SensorEvent = conmutador;

	domoboard.BOTON2.SensorEvent = conmutador;

	domoboard.BTN_OPT.SensorEvent = conmutador;
}

void config_practica3_apt_2(void){
	clear_Actuators();

	domoboard.BOTON1.SensorEvent = conmutador;
	domoboard.BOTON1.managerActuators.push(&(domoboard.RELE));

	domoboard.BOTON2.SensorEvent = conmutador;
	domoboard.BOTON2.managerActuators.push(&(domoboard.RELE));

	domoboard.BTN_OPT.SensorEvent = conmutador;
	domoboard.BTN_OPT.managerActuators.push(&(domoboard.RELE));
}

void config_practica4_apt_1(void){

	clear_Actuators();

	domoboard.BOTON1.SensorEvent = Pulsado_Soltado;
	domoboard.BOTON1.managerActuators.push(&(domoboard.RELE));

	domoboard.BOTON2.SensorEvent = Pulsado_Soltado;
	domoboard.BOTON2.managerActuators.push(&(domoboard.TRIAC));

	domoboard.BTN_OPT.SensorEvent = Pulsado_Soltado;
}

void config_practica4_apt_2(void){

	clear_Actuators();

	domoboard.BOTON1.SensorEvent = Interruptor;
	domoboard.BOTON1.managerActuators.push(&(domoboard.RELE));


	domoboard.BOTON2.SensorEvent = Interruptor;
	domoboard.BOTON2.managerActuators.push(&(domoboard.TRIAC));

	domoboard.BTN_OPT.SensorEvent = Interruptor;
}

void config_practica4_apt_3(void){

	clear_Actuators();

	domoboard.BOTON1.SensorEvent = conmutador;
	domoboard.BOTON1.managerActuators.push(&(domoboard.RELE));
	domoboard.BOTON1.managerActuators.push(&(domoboard.TRIAC));

	domoboard.BOTON2.SensorEvent = conmutador;
	domoboard.BOTON2.managerActuators.push(&(domoboard.RELE));
	domoboard.BOTON2.managerActuators.push(&(domoboard.TRIAC));

	domoboard.BTN_OPT.SensorEvent = conmutador;
	domoboard.BTN_OPT.managerActuators.push(&(domoboard.RELE));
	domoboard.BTN_OPT.managerActuators.push(&(domoboard.TRIAC));
}


void config_practica5_apt_4(){
	clear_Actuators();

	mbDomoboard.BOTON1.mbSensorEvent = mbInterruptor;
	mbDomoboard.BOTON1.mbActuators.push(&mbDomoboard.RELE);

	mbDomoboard.BOTON2.mbSensorEvent = mbInterruptor;
	mbDomoboard.BOTON2.mbActuators.push(&mbDomoboard.TRIAC);
}


void config_practica7(){
	clear_Actuators();
	/*
	mbDomoboard.BOTON1.mbSensorEvent = mbInterruptor;
	mbDomoboard.BOTON1.mbActuators.push(&(mbDomoboard.TRIAC));

	mbDomoboard.BOTON2.mbSensorEvent = mbInterruptor;
	mbDomoboard.BOTON2.mbActuators.push(&(mbDomoboard.RELE));

	mbDomoboard.BTN_OPT.mbSensorEvent = mbInterruptor;
	*/
	mbDomoboard.BOTON1.mbSensorEvent = mbInterruptor;
	mbDomoboard.BOTON1.mbActuators.push(&(mbDomoboard.RELE));

	temporizador.tiempoLimite = &Aregs[MB_TIME];

	mbDomoboard.BOTON2.mbSensorEvent = mbInterruptor;
	mbDomoboard.BOTON2.mbActuators.push(&(mbDomoboard.RELE));

	mbDomoboard.SNS_MOV.mbSensorEvent = mbInterruptorTemporizador;
	mbDomoboard.SNS_MOV.mbActuators.push(&(mbDomoboard.TRIAC));
}

void SelectionConfiguration(uint8_t selConf){
	static uint8_t actConf = 0x00;

	if(selConf == actConf)
		return;

	actConf = selConf;

	switch(selConf){
		case P1_PULSADORES:
			DEBUGLNF("P1 PULSADORES Seleccionado");
			config_practica1_apt_1();
			break;

		case P1_INTERRUPTOR:
			DEBUGLNF("P1 INTERRUPTOR Seleccionado");
			config_practica1_apt_2();
			break;

		case P1_CONMUTADOR:
			DEBUGLNF("P1 CONMUTADOR Seleccionado");
			config_practica1_apt_3();
			break;

		case P3_CONMUTADOR:
			DEBUGLNF("P3 CONMUTADOR Seleccionado");
			config_practica3_apt_2();
			break;

		case P4_PULSADORES:
			Serial.println("P4 PULSADORES Seleccionado ");
			config_practica4_apt_1();
			break;

		case P4_INTERRUPTOR:
			DEBUGLNF("P4 INTERRUPTOR Seleccionado");
			config_practica4_apt_2();
			break;

		case P4_CONMUTADOR:
			DEBUGLNF("P4 CONMUTADOR Seleccionado");
			config_practica4_apt_3();
			break;

		case P5_INTERRUPTOR:
			DEBUGLNF("P5 INTERRUPTOR Seleccionado");
			config_practica5_apt_4();
			break;

		case P7_INTERRUPTORTEMPORIZADO:
			DEBUGLNF("P7 INTERRUPTOR TEMPORIZADO Seleccionado");
			config_practica7();
			break;

	}
}

