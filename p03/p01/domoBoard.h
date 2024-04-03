/*
 * domoBoard.h
 *
 *  Created on: 09/03/2015
 *      Author: jctejero
 */

#ifndef DOMOBOARD_H_
#define DOMOBOARD_H_

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include	"Arduino.h"

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef enum
{
	S_DIGITAL,
	S_ANALOGICO
}teSensor;

typedef struct
{
	byte		pin;			//Pin asignado al sensor
	int	    	valor;			//Valor leido
	int			valor_Df;		//Valor Sensor por defecto
	bool		Activo;			//Activar/Desactivas sensor
	teSensor	eSensor;		//Tipos de sensor ANAL�GICO/DIGITAL
	int			Aux;			//Variables para ser usadas en la gesti�n del sensor
	String		name;
}tsSensor;

typedef struct
{
	byte		pin;			//Pin asignado al sensor
	bool	    estado;			//Valor leido
	bool		Activo;			//Activar/Desactivas sensor
	String		name;
}tsActuator;

typedef void (*TSensorEvent)(tsSensor *);

typedef struct
{
	tsSensor			sSensor;
	TSensorEvent		SensorEvent;	//Evento para aplicaci�n asociada
}ptsSensor;

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define 	BUTTON1_P  			3   	   	// Pulsador 1
#define 	BUTTON2_P  			10        	// Pulsador 2

#define 	BTN_OPT_P    		11 	    	// Entrada Optocoplada
#define 	RELE_S				4			// Salida del rele


/****************************************************************************/
/***        Exported Class                                                ***/
/****************************************************************************/
class DomoBoard
{
private:


public:

	DomoBoard(); 						//Constructor

	ptsSensor		BOTON1;
	ptsSensor		BOTON2;
	ptsSensor 		BTN_OPT;
	tsActuator 		RELE;

	void 	leerAllSensor(void);
	void 	leerSensor(ptsSensor *Sensor);
};

extern DomoBoard domoboard;


#endif /* DOMOBOARD_H_ */
