// Do not remove the include below
#include 	"P1_DomoBoard_Pulsadores.h"
#include	"config_practicas.h"

#define 	LOOP_TMP		10	//miliseconds

//The setup function is called once at startup of the sketch
void setup()
{
	config_practica3();

	Serial.begin(115200);

	Serial.println("P3 Domoboard Rele");		// Incluye tambien la p1

	//Serial.flush();
}

// The loop function is called in an endless loop
void loop()
{
	static uint32_t tmp_loop = 0;

	if((millis()-tmp_loop) > LOOP_TMP){
		tmp_loop = millis();

		domoboard.leerAllSensor();

		if(Serial.available() >= 2){

			if (Serial.read() == '#') // Start of new control message
			{
				char command = Serial.read(); // Commands
				switch(command){
				case '1':
					config_practica1_apt_1();
					Serial.println("Apartado 1 Seleccionado");
					break;
				case '2':
					config_practica1_apt_2();
					Serial.println("Apartado 2 Seleccionado");
					break;
				case '3':
					config_practica1_apt_3();
					Serial.println("Apartado 3 Seleccionado");
					break;
				case '4':
					config_practica3();
					Serial.println("Práctica 3 seleccionada");
				}
			}
		}
	}
}
