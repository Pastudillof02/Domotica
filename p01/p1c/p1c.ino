#include "Arduino.h"
//The setup function is called once at startup of the sketch

bool conmutator = false;

void setup()
{
	pinMode(3, INPUT);
	pinMode(10, INPUT);
	pinMode(11, INPUT);

	Serial.begin(115200);
	Serial.println("Conmutador ---> OFF");
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
		conmutator = !conmutator;
		if (conmutator) Serial.println("Conmutador ---> ON");
		else Serial.println("Conmutador ---> OFF");
	}

	if(v2 == 1)
	{
		while(v2 == 1) v2 = digitalRead(10);
		conmutator = !conmutator;
		if (conmutator) Serial.println("Conmutador ---> ON");
		else Serial.println("Conmutador ---> OFF");
	}

	if(v3 == 0)
	{

		while(v3 == 0) v3 = digitalRead(11);
		conmutator = !conmutator;
		if (conmutator) Serial.println("Conmutador ---> ON");
		else Serial.println("Conmutador ---> OFF");
	}
}

