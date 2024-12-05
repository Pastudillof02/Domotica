// Do not remove the include below
#include "P07A3_eeprom.h"

#include 	"Gest_Modbus.h"
#include	"debuglog.h"
#include	"cfg_loop.h"
#include	"types.h"
#include	"config_practicas.h"

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

	//Leer Configuraci�n actual
	load_Config();

	//Registramos Lectura de sensores
	epdRegisterLoop(leerSensors);

	//Registramos comprobaci�n comunicaciones ModBus
	epdRegisterLoop(RTU_ModBus);

	//Registramos la gesti�n de las acciones temporizadas.
	epdRegisterLoop(AccionesTemporizadas);

	DEBUGLNF("P08 - Potenciometros");

	Serial.flush();
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
