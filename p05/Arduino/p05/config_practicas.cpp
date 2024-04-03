/*
 * config_practicas.cpp
 *
 *  Created on: 10/03/2015
 *      Author: jctejero
 */

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include	"config_practicas.h"

/****************************************************************************/
/***                 Functions                                            ***/
/****************************************************************************/
void config_interruptores(void){
	domoboard.BOTON1.SensorEvent = Interruptor;

	domoboard.BOTON2.SensorEvent = Interruptor;

	domoboard.BTN_OPT.SensorEvent = NULL;
}

