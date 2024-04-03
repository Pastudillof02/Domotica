// Do not remove the include below
#include "P3_Rele.h"
#include "QueueList.h"
#include "cfg_loop.h"
#include "debuglog.h"

#include	"config_practicas.h"
#include 	"domoBoard.h"

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
	config_practica4_apt_2();

	Serial.begin(115200);


	DEBUGLNF("P3 Rele");


	epdRegisterLoop(leerSensors);
}

// The loop function is called in an endless loop
void loop()
{
	EXECUTELOOP(){
		UPDATELOOP();

		main_loop();

		domoboard.leerAllSensor();
		if(Serial.available() >= 2){
			if (Serial.read() == '#') // Start of new control message
			{
				char command = Serial.read(); // Commands
				switch(command){
					case '1':
						epdRegisterLoop(config_practica4_apt_2);
						Serial.println("Apartado 2 Seleccionado");
						break;
					case '2':
						epdRegisterLoop(config_practica4_apt_3);
						Serial.println("Apartado 3 Seleccionado");
						break;
					case '3':
						epdRegisterLoop(config_practica4_apt_4);
						Serial.println("Apartado 4 Seleccionado");
						break;
				}
			}
		}

		LOOP_x10ms(3){

		}

		LOOP_x100ms{

		}
	}
}

void main_loop(){
	// Call registered loop callbacks

	for (uint8_t i = 0; i < _loop_callbacks.count(); i++) {
		(_loop_callbacks.peek(i))();
	}

}
