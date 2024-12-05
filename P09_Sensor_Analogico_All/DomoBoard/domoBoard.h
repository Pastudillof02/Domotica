/*
 * domoBoard.h
 *
 *  Created on: 09/03/2015
 *      Author: jctejero
 *
 *  Modified on: 16/03/2022
 */

#ifndef DOMOBOARD_H_
#define DOMOBOARD_H_

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include	"Arduino.h"
#include	"../QueueList.h"

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef void (*TNotifyEvent)(void *);

/* constants */
typedef enum {
	RX485_RX,
	RX485_TX
}TRX485_rxtx;

typedef enum
{
	S_DIGITAL,
	S_ANALOGICO
}teSensor;

typedef struct
{
	byte	pin;
	bool	estado;
}tsActuator, *tpsActuator;

typedef 	QueueList<tpsActuator>		TManagerActuators;

typedef struct
{
	byte					pin;			//Pin asignado al sensor
	int	    				valor;			//Valor leido
	int						valor_Df;		//Valor Sensor por defecto
	bool					Activo;			//Activar/Desactivas sensor
	teSensor				eSensor;		//Tipos de sensor ANAL�GICO/DIGITAL
	int						Aux;			//Variables para ser usadas en la gesti�n del sensor
	String					name;
	TNotifyEvent			SensorEvent;
	TManagerActuators		managerActuators;
}tsSensor, *ptsSensor;

typedef enum
{
	STOP,
	DOWN,
	UP,
	STOP2
}tsPersianaState;



/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define 	BUTTON1_P  				3   	   	// Pulsador 1
#define 	BUTTON2_P  				10        	// Pulsador 2
#define 	RELE_P					4			// RELE 1
#define		ONOFF_P					5			
#define		UPDOWN_P				6			
#define		TRIAC_P					7			// ON/OFF Solid State Triac
#define 	BTN_OPT_P		    	11 	    	// Entrada Optocoplada
#define		EN_485					12			// Bit to enable RS485 Conmunications
#define     PIR_P					13			// Sensor de Movimiento

#define		PHOTORES_P				A0			// Photo resistor SRC
#define		TEMPSEN_P				A2			// Sensor de temperatura
#define		POT1_P					A3
#define		POT2_P					A4
#define		PHOTOTTOR_P				A5			// Sensor de luminosidad (PhotoTransistor)

/****************************************************************************/
/***        Exported Class                                                ***/
/****************************************************************************/
class DomoBoard
{
private:


public:

	DomoBoard(); 						//Constructor
	virtual ~DomoBoard(){};

	tsSensor		BOTON1;
	tsSensor		BOTON2;
	tsSensor 		BTN_OPT;
	tsSensor		PIR_MOV;

	//Sensores Anal�gicos
	tsSensor		POT1;
	tsSensor		POT2;
	tsSensor		PHOTORES;			// Photoresistor SRC
	tsSensor		TEMPSEN;			//Sensor de temperatura
	tsSensor		PHOTOTTOR;			//Foto transistor

	//Salidas
	tsActuator		RELE;
	tsActuator		TRIAC;
	tsActuator		ONOFF;
	tsActuator		UPDOWN;

	void 	leerAllSensor(void);
	void 	leerSensor(ptsSensor Sensor);
	void 	managePersiana(tsPersianaState statePersiana);


	virtual void    clear_Actuators();

	static 	void	setActuator(tsActuator *Actuator, bool val);
	static 	void 	manageSensorActuators(TManagerActuators *managerActuators, bool val);

	static	void 	RS485_RxTx(TRX485_rxtx rxtx);
};

extern DomoBoard domoboard;


#endif /* DOMOBOARD_H_ */
