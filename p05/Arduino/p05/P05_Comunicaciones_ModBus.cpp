// Do not remove the include below
#include 	"P05_Comunicaciones_ModBus.h"
#include 	"Gest_Modbus.h"
#include	"debuglog.h"
#include	"cfg_loop.h"
#include	"types.h"
#include 	"config_practicas.h"

QueueList<void_callback_f> _loop_callbacks;

void main_loop();

void leerSensors(){
	domoboard.leerAllSensor();
}

void epdRegisterLoop(void_callback_f callback) {
    _loop_callbacks.push(callback);
}


//The setup function is called once at startup of the sketch
void setup()
{
	//Iniciamos Modbus en Modo RTU
	Init_RTU_Modbus();

	Serial.begin(115200);

	//Registramos Lectura de sensores
	epdRegisterLoop(leerSensors);

	//Registramos comprobación comunicaciones ModBus
	epdRegisterLoop(RTU_ModBus);

	//Configuramos los botones
	epdRegisterLoop(config_interruptores);

	DEBUGLNF("P05 Comunicaciones ModBus");

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
