/*
 * utils_domoBoard.h
 *
 *  Created on: 10/03/2015
 *      Author: jctejero
 */

#ifndef UTILS_DOMOBOARD_H_
#define UTILS_DOMOBOARD_H_

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include	"Arduino.h"
#include	"domoBoard.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define 	ON   				HIGH
#define     OFF					LOW

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
void Interruptor(void *Sensor);
void Pulsado_Soltado(void *Sensor);
void conmutador(void *Sensor);
void pulsado_soltado_triac_rele(void *Sensor);
void interruptor_triac_rele(void *Sensor);
void conmutador_triac_rele(void *Sensor);


#endif /* UTILS_DOMOBOARD_H_ */
