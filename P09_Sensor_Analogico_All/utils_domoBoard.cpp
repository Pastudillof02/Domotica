/*
 * utils_domoBoard.cpp
 *
 *  Created on: 10/03/2015
 *      Author: jctejero
 *
 *  Modified on: 16/03/2022
 */

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "utils_domoBoard.h"
#include "HardwareSerial.h"
#include "config_practicas.h"

/******************************************************************/
/***                      Variables Locales                     ***/
/******************************************************************/
//Lista de sensores temporizados
QueueList<TpmbSensor>		SensoresTemporizados;

#define	STEP_CTRL_BLIND		5
#define PERCENTAGE(x)		((x % STEP_CTRL_BLIND) > 2) ? x + (STEP_CTRL_BLIND-(x % STEP_CTRL_BLIND)) : x - (x % STEP_CTRL_BLIND);
#define V_PERCENTAGE(x)    	PERCENTAGE((((TPCtrlTime)x)->tiempoActivo)*100/(*((TPCtrlTime)x)->tiempoFinal));

const uint16_t tiempoEspera = 1;
const uint16_t tiempoApertura = 5;

/*============================================*/
/*		 		  INTERRUPTOR                 */
/*============================================*/
void Interruptor(void *Sensor)
{
	if(((ptsSensor)Sensor)->valor_Df == ((ptsSensor)Sensor)->valor){
		Serial.print(((ptsSensor)Sensor)->name);
		Serial.print(" : Interruptor --> ");
		if(((ptsSensor)Sensor)->Aux == OFF){
			((ptsSensor)Sensor)->Aux = ON;
			DEBUGLNF("ON");
		}else{
			((ptsSensor)Sensor)->Aux = OFF;
			DEBUGLNF("OFF");
		}
	}

	DomoBoard::manageSensorActuators(&((ptsSensor)Sensor)->managerActuators, ((ptsSensor)Sensor)->Aux);
}

/*============================================*/
/*		 		    PULSADOR                  */
/*============================================*/
void Pulsado_Soltado(void *Sensor){
	ptsSensor sensor = reinterpret_cast<ptsSensor>(Sensor);

	Serial.print(sensor->name);
	if(sensor->valor_Df == sensor->valor){
		DEBUGLNF(" --> Soltado");
	}else{
		DEBUGLNF(" --> Pulsado");
	}

	DomoBoard::manageSensorActuators(&(sensor->managerActuators), !(sensor->valor_Df == sensor->valor));
}

/*============================================*/
/*		     	   CONMUTADOR                 */
/*============================================*/
void conmutador(void *Sensor)
{
	static int valor = OFF;

	ptsSensor sensor = reinterpret_cast<ptsSensor>(Sensor);

	if(sensor->valor_Df == sensor->valor){
		DEBUGF("Conmutador --> ");
		if(valor == OFF){
			valor = ON;
			DEBUGLNF("ON");
		}else{
			valor = OFF;
			DEBUGLNF("OFF");
		}

		//Actualiza Actuadores
		//DomoBoard::setActuator(&domoboard.RELE, valor);

		DomoBoard::manageSensorActuators(&(sensor->managerActuators), valor);
	}
}

/*============================================*/
/*		      INTERRUPTOR MODBUS              */
/*============================================*/
void mbInterruptor(void *mbSensor)
{
	TpmbSensor sensor = reinterpret_cast<TpmbSensor>(mbSensor);

	if(sensor->Sensor->valor_Df == sensor->Sensor->valor){
		mbDomoboard.manager_mbActuators(&(sensor->mbActuators), TOGGLE);
	}
}


/*============================================*/
/*		 	   CONMUTADOR MODBUS              */
/*============================================*/
void mbConmutador(void *mbSensor)
{
	TpmbSensor sensor = reinterpret_cast<TpmbSensor>(mbSensor);

	if(sensor->Sensor->valor_Df == sensor->Sensor->valor){
		//Estado del sensor ha cambiado
		mbDomoboard.manager_mbActuators(&(sensor->mbActuators), TOGGLE);
	}
}

/*========================================================*/
/*		      INTERRUPTOR TEMPORIZADO MODBUS              */
/*========================================================*/

/*
 * Este sensor ser� activado mediante Sensor (Variable de control) y aunque se vuelva inactivo,
 * el interruptor, permanecer� activo durante el tiempo que indique el temporizador.
 * Si durante el tiempo que el interruptor est� activo, la variable de control permanece inactiva,
 * o se activa de nuevo, el tiempo que el interruptor permanece activo se
 * ir� actualizando, de tal forma que el tiempo que el interruptor permanece ativo,
 * siempre se cuenta desde la �ltima vez que el sensor se activo.
 *
 */

void	mbInterruptorTemporizado(void *Sensor){

	TpmbSensor sensor = reinterpret_cast<TpmbSensor>(Sensor);

	if(sensor->Sensor->valor_Df != sensor->Sensor->valor){
		sensor->asyncWait->restart();

		mbDomoboard.manager_mbActuators(&(sensor->mbActuators), (TStateDigitalDev)ON);

	}else{
		if(!sensor->asyncWait->isWaiting() && !sensor->asyncWait->isVerified()){

			DEBUGLNF("ASYNWAIT TERMINADO");

			sensor->asyncWait->setVerified();
			mbDomoboard.manager_mbActuators(&(sensor->mbActuators), (TStateDigitalDev)OFF);
		}
	}

}

/*****************************************************************************************/
/***********************************  Leer Temperatura ***********************************/
/*****************************************************************************************/
//mas/menos 1 - 2�C de exactitud para el TMP36, por lo que escribimos valores decimales
void Calc_Temperatura(void *Sensor){
	float valTMP;
	int   temp;

	TpmbSensor sensor = reinterpret_cast<TpmbSensor>(Sensor);

	valTMP = sensor->Sensor->valor*.004882812;	//Conviere resultado convertidor a voltios

	valTMP = (valTMP - .5)*100;          //Convierte Temperatura de 10 mV por grado con 500 mV de Offset


	temp = (valTMP - (int)valTMP)*100;

    if(temp < 50) temp = 0;
    //else if ((25 < temp)&&(temp < 75)) temp = 5;
    //else if ((75 < temp)&&(temp <= 99)){
    else{
    	temp = 0;
    	valTMP = (int)valTMP +1;
    }

	*(sensor->mbRegs) = (((int)valTMP & 0xff) << 8) | (temp & 0xff);

#ifdef DEBUG_TEMP
    static float vT = 0;

    if(vT != valTMP){
    	vT = valTMP;
    	/*
    	DEBUGF("Temperatura = " );
    	Serial.print((int)valTMP,DEC);
    	Serial.print(".");
    	Serial.println(temp,DEC);
    	*/
    	DEBUGLOG("Temperatura = %d.%d\n", (int)valTMP, temp);

    //	Serial.print("Temperatura F -> ");
    //	Serial.println(Sensor->Regs_App[Sensor->MBReg_App],BIN);
    }
#endif
}

/*============================================*/
/*			  INTERRUPTOR LUMINOSIDAD         */
/*============================================*/
/*
 * Interruptor por nivel de luminosidad. funcionar� con una histeresis, es decir,
 * Si el interruptor est� desactivado, se activar� cuando alcance el "highlevel".
 *
 * Si el interruptor est� ativado, se desactivar� cuando alcanze el "lowlevel".
 */
void	interruptor_SRC(void *Sensor){
	TpmbSensor sensor = reinterpret_cast<TpmbSensor>(Sensor);

	if((int)*(sensor->ctrlLevelPtr.lInf) > (int)*(sensor->ctrlLevelPtr.lSup))
		return;

	int state = sensor->Sensor->Aux;

	switch(state){
	case 1:
		if(sensor->Sensor->valor <= (int)*(sensor->ctrlLevelPtr.lInf)){
			state = 2;
			//Estado del sensor ha cambiado
			mbDomoboard.manager_mbActuators(&(sensor->mbActuators), (TStateDigitalDev)ON);
		}

		break;

	case 2:
		if(sensor->Sensor->valor >= (int)*(sensor->ctrlLevelPtr.lSup)){
			state = 1;
			mbDomoboard.manager_mbActuators(&(sensor->mbActuators), (TStateDigitalDev)OFF);
		}

		break;

	default:
		state = 2;
		mbDomoboard.set_coilRegister(MB_TRIAC, OFF);
	}

	sensor->Sensor->Aux = state;
}

/*============================================*/
/*			  TRIGGER WITH LUMINOSIDAD        */
/*============================================*/
/*
 * tRIGGER por nivel de luminosidad. Dispara un evento cuando el nivel del sensor
 * se encuentra por debajo de un determinado nivel
 */
void	trigger_Level(void *Sensor){
	TpmbSensor sensor = reinterpret_cast<TpmbSensor>(Sensor);

	uint16_t limInfe = *(sensor->ctrlLevelPtr.lInf);

	if(((uint16_t) sensor->Sensor->valor <= limInfe)){
		if(sensor->Sensor->Aux == 0){
			mbDomoboard.manager_mbActuators(&(sensor->mbActuators), (TStateDigitalDev)ON);
			sensor->Sensor->Aux = 1;
		}
	} else sensor->Sensor->Aux = 0;
}

/*====================================================================================
 * Llamada regular usada para gestionar los temporizadores usados por la aplicaci�n. =
 * es llamada cada LOOP_TIME (10 ms)
 *====================================================================================*/
void AccionesTemporizadas(void){

	TpmbSensor pmbSensor;

	for(int n=0; n<SensoresTemporizados.count(); n++){

		pmbSensor = SensoresTemporizados.peek(n);

		pmbSensor->mbSensorEvent(pmbSensor);
	}
}

void Persiana(void *Sensor){

	TpmbSensor sensor = reinterpret_cast<TpmbSensor>(Sensor);

	for(int n = 0; n < sensor->mbActuators.count(); n++){
		*(sensor->mbActuators.peek(n))->mbRegs = (sensor->Sensor->valor) != (sensor->Sensor->valor_Df);
	}

	UpDown();
}

void UpDown(){
	bool up, down;
	tsPersianaState state = (tsPersianaState)(Aregs[MB_STATE_PERS]&0xFF);

	up = (bool)(*mbDomoboard.PERSIANA_UP.mbRegs);
	down = (bool)(*mbDomoboard.PERSIANA_DOWN.mbRegs);

    switch(state){
    	case STOP:
    		if (up) state = UP; 
    		if (down) state = DOWN;
    		break;

    	case UP: 
    		if(!up && !down) state = STOP;
    		if(!up && down) state = STOP2;
    		break;

    	case DOWN:
    		if(!up && !down) state = STOP;
    		if(up && !down) state = STOP2;
    		break;

    	case STOP2:
    		if(!up && !down) state = STOP;
    		break;

    }

    if(Aregs[MB_STATE_PERS] != state)
    {
    	Aregs[MB_STATE_PERS] = state;
    	Ctrl_PosicionPersiana(&ctrlPersiana, tsPersianaState(Aregs[MB_STATE_PERS]&0xFF));
    	mbDomoboard.managePersiana(tsPersianaState(Aregs[MB_STATE_PERS]&0xFF));
    }

    //Serial.print("El estado de la persiana es: "); Serial.print(Iregs[MB_PERCEN_PERS]); Serial.println("%");
}

void Ctrl_PosicionPersiana(TPCtrlTime ctrlPersiana, tsPersianaState state){
	static tsPersianaState lastState = STOP;

	auto actualizeTime = [&](int8_t sign){

		ctrlPersiana->tiempoActivo = ctrlPersiana->tiempoActivo + sign*(millis() - ctrlPersiana->inicio);

		if(ctrlPersiana->tiempoActivo < 0){
			ctrlPersiana->tiempoActivo = 0;
		}else if(uint16_t(ctrlPersiana->tiempoActivo) > *ctrlPersiana->tiempoFinal){
			ctrlPersiana->tiempoActivo = *ctrlPersiana->tiempoFinal;
		}

		uint8_t per = PERCENTAGE(((ctrlPersiana->tiempoActivo)/(*ctrlPersiana->tiempoFinal))*100);
		uint8_t per2 = V_PERCENTAGE(ctrlPersiana);


		if(per2 != Iregs[MB_PERCEN_PERS]){
			Iregs[MB_PERCEN_PERS] = per2;
		}
	};

	switch(state){
		case STOP:
			ctrlPersiana->activa = false;
			switch(lastState){
				case DOWN:
					actualizeTime(-1);
					break;
				case UP:
					actualizeTime(1);
					break;
				default:
					break;
			}
			break;

		case DOWN:
			if(ctrlPersiana->activa){
				actualizeTime(-1);
			}else{
				ctrlPersiana->activa = true;
			}
			ctrlPersiana->inicio = millis();
			break;

		case UP:
			if(ctrlPersiana->activa){
				actualizeTime(1);
			}else{
				ctrlPersiana->activa = true;
			}
			ctrlPersiana->inicio = millis();
			break;

		case STOP2:
			ctrlPersiana->activa = false;
			switch(lastState){
				case DOWN:
					actualizeTime(-1);
					break;
				case UP:
					actualizeTime(1);
					break;
				default:
					break;
			}
			break;

	}

	lastState = state;
}



void Garaje(void  *Sensor){
	DEBUGLOGLN("Cregs en utils-> %d",Cregs[MB_GARAJE]);

	TpmbSensor sensor = reinterpret_cast<TpmbSensor>(Sensor);

	static uint8_t state = 'A';
	tsPersianaState statePer = (tsPersianaState)(Aregs[MB_STATE_PERS]&0xFF);

	TmbRSensores *relatedSensores = (TmbRSensores *)sensor->rSensores;

	auto leerSensores = [&](){

		if(Cregs[MB_GARAJE]){
			return true;
		}else if(sensor->asyncWait != NULL){
			if(sensor->Sensor->valor != sensor->Sensor->valor_Df){
				Cregs[MB_GARAJE] = true;
				return true;
			}
		}else{
			uint16_t limInf = *(sensor->ctrlLevelPtr.lInf);

			if(((uint16_t) sensor->Sensor->valor) <= limInf){
				return true;
			}
		}

		return false;
	};


	auto Init = [&](uint16_t *time = NULL){
		if(sensor->asyncWait != NULL){
			sensor->asyncWait->startWaiting(time);
		}else if(relatedSensores->mbRSensores.count() > 0){
			relatedSensores->mbRSensores.peek(0)->asyncWait->startWaiting(time);
		}
	};

	switch(state){
	case 'A':
		DEBUGLNF("1");
		if(sensor->asyncWait != NULL){
			DEBUGLNF("2");
			//DEBUGLOGLN("mbReg -> %d",((uint8_t)*(sensor->mbRegs)));
			DEBUGLOGLN("Cregs -> %d",((uint8_t)Cregs[MB_GARAJE]));

			if(*(sensor->mbRegs) || Cregs[MB_GARAJE]){
				DEBUGLNF("3");

				Cregs[MB_GARAJE] = false;
				state = 'B';
				statePer = UP;
				DEBUGLNF("3.2");
			}
			DEBUGLNF("2.2");
		}
		DEBUGLNF("1.2");
		break;

	case 'B':

		if(Iregs[MB_PERCEN_PERS] >= 100){
			state = 'C';
			statePer = STOP;

			Init((uint16_t *)&tiempoApertura);
		}
		break;

	case 'C':

		if(leerSensores()){
			Cregs[MB_GARAJE] = false;
			Init((uint16_t *)&tiempoApertura);
		}else{
			if(sensor->asyncWait != NULL){
				if(!sensor->asyncWait->isWaiting()){
					state = 'D';
					statePer = DOWN;
				}
			}
		}
		break;

	case 'D':

		if(leerSensores()){
			Cregs[MB_GARAJE] = false;
			state = 'E';
			statePer = STOP;

			Init((uint16_t *)&tiempoEspera);

		}else{
			if(Iregs[MB_GARAJE] == 0){
				state = 'A';
				statePer = STOP;
			}
		}
		break;

	case 'E':

		if(sensor->asyncWait != NULL){
			if(!sensor->asyncWait->isWaiting()){
				state = 'B';
				statePer = UP;
			}
		}
		break;

	default:
		break;
	}

	if(Aregs[MB_STATE_PERS] != statePer){
		mbDomoboard.set_holdingRegister(MB_STATE_PERS, statePer);
	}
}






