// Do not remove the include below
#include 	"Gest_Modbus.h"
#include	"debuglog.h"
#include	"cfg_loop.h"
#include	"types.h"
#include	"config_practicas.h"
#include "P06A2_OutputHoldingRegister.h"

QueueList<void_callback_f> _loop_callbacks;

void main_loop();

void leerSensors(){
	if(Aregs[MB_SELPRACT] < PRACTICAS_MODBUS){
		domoboard.leerAllSensor();
	}else mbDomoboard.leerAllSensor();
}

/*
void leerSensors(){
	mbDomoboard.leerAllSensor();
}
*/

void epdRegisterLoop(void_callback_f callback) {
    _loop_callbacks.push(callback);
}

//The setup function is called once at startup of the sketch
void setup()
{
	//Iniciamos Modbus en Modo RTU
	Init_RTU_Modbus();

	//Configura pr�ctica
	Aregs[MB_SELPRACT] = P1_PULSADORES;
	writeholdingregister();

	//Registramos Lectura de sensores
	epdRegisterLoop(leerSensors);

	//Registramos comprobaci�n comunicaciones ModBus
	epdRegisterLoop(RTU_ModBus);

	DEBUGLNF("P06A2 Output Holding Register");
}

// The loop function is called in an endless loop
void loop()
{

	EXECUTELOOP(){
		UPDATELOOP();

		main_loop();

	}
}

void main_loop(){

	// Call registered loop callbacks
	for (uint8_t i = 0; i < _loop_callbacks.count(); i++) {
		(_loop_callbacks.peek(i))();
	}

}
