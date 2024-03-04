#include "Arduino.h"
//The setup function is called once at startup of the sketch

int aux1 = 0, aux2 = 0, aux3 = 1;
void setup()
{
	pinMode(3, INPUT);
	pinMode(10, INPUT);
	pinMode(11, INPUT);

	Serial.begin(115200);
}

// The loop function is called in an endless loop
void loop()
{
	int v1 = digitalRead(3);
	int v2 = digitalRead(10);
	int v3 = digitalRead(11);

	if(v1 != aux1)
	{
		aux1 = v1;
		if (v1 == 1) Serial.println("Boton 1 ---> Pulsado");
		else Serial.println("Boton 1 ---> Soltado");
	}

	if(v2 != aux2)
	{
		aux2 = v2;
		if (v2 == 1) Serial.println("Boton 2 ---> Pulsado");
		else Serial.println("Boton 2 ---> Soltado");
	}

	if(v3 != aux3)
	{
		aux3 = v3;
		if (v3 == 0) Serial.println("Boton 3 ---> Pulsado");
		else Serial.println("Boton 3 ---> Soltado");
	}
}

