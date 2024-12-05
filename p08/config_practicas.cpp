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


/****************************************************************************/
/***                 Functions                                            ***/
/****************************************************************************/

void clear_Actuators(){
	domoboard.clear_Actuators();
	mbDomoboard.clear_Actuators();
	SensoresTemporizados.clear();
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


void config_practica6_apt_3(){
	clear_Actuators();

	mbDomoboard.BOTON1.mbSensorEvent = mbInterruptor;
	mbDomoboard.BOTON1.mbActuators.push(&(mbDomoboard.TRIAC));

	mbDomoboard.BOTON2.mbSensorEvent = mbInterruptor;
	mbDomoboard.BOTON2.mbActuators.push(&(mbDomoboard.RELE));

	mbDomoboard.BTN_OPT.mbSensorEvent = mbInterruptor;
}

void Config_P7_SensorMovimiento(){

	static AsyncWait asyncWait;

	//Borramos los actuadores previos asignado a cada sensor de entrada
	clear_Actuators();

	//Inicialmente, habilitamos el sensor PIR
	mbDomoboard.PIR_MOV.Sensor->Activo = true;		//Habilitamos sensor PIR
	Cregs[MB_ACTPIR] = 0x01;  						//Actualiza registro que monitoriza la habilitación del sensor

	DEBUGLOGLN("Valor MB_TMP_PIR: %d", Aregs[MB_TMP_PIR]);

	asyncWait.startWaiting(&Aregs[MB_TMP_PIR]);		//Configuramos el tiempo de espera al tiempo almacenado
													//en el registro ModBus usado para tal fin
	mbDomoboard.PIR_MOV.asyncWait = &asyncWait;		//Asignamos el elemento de temporización al sensor
	mbDomoboard.PIR_MOV.mbSensorEvent = mbInterruptorTemporizado;
	mbDomoboard.PIR_MOV.mbActuators.push(&(mbDomoboard.TRIAC));

	mbDomoboard.BOTON1.mbSensorEvent = mbConmutador;
	mbDomoboard.BOTON1.mbActuators.push(&(mbDomoboard.RELE));

	mbDomoboard.BOTON2.mbSensorEvent = mbConmutador;
	mbDomoboard.BOTON2.mbActuators.push(&(mbDomoboard.RELE));

	mbDomoboard.BTN_OPT.mbSensorEvent = mbConmutador;
	mbDomoboard.BTN_OPT.mbActuators.push(&(mbDomoboard.RELE));

	SensoresTemporizados.push(&(mbDomoboard.PIR_MOV));
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

		case P6_INTERRUPTOR:
			DEBUGLNF("P6 INTERRUPTOR Seleccionado");
			config_practica6_apt_3();
			break;

		case P7_PIR:
			DEBUGLNF("P07 Seleccionada --> Sensor Movimiento (PIR)");
			Config_P7_SensorMovimiento();
			break;


	}
}

