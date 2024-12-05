#include "Arduino.h"
//The setup function is called once at startup of the sketch

bool state1 = false, state2 = false, state3 = false;
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

	if(v1 == 1)
	{
		while(v1 == 1) v1 = digitalRead(3);
		state1 = !state1;
		if (state1) Serial.println("Boton 1 ---> ON");
		else Serial.println("Boton 1 ---> OFF");
	}

	if(v2 == 1)
	{
		while(v2 == 1) v2 = digitalRead(10);
		state2 = !state2;
		if (state2) Serial.println("Boton 2 ---> ON");
		else Serial.println("Boton 2 ---> OFF");
	}

	if(v3 == 0)
	{

		while(v3 == 0) v3 = digitalRead(11);
		state3 = !state3;
		if (state3) Serial.println("Boton 3 ---> ON");
		else Serial.println("Boton 3 ---> OFF");
	}
}


