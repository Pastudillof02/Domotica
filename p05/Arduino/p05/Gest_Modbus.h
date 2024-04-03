/*
 * Gest_Modbus.h
 *
 *  Created on: 16/05/2014
 *      Author: jctejero
 *
 *  Modified on: 16/03/2022
 */

#ifndef GEST_MODBUS_H_
#define GEST_MODBUS_H_

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include 	"ModbusSlave/ModbusSlave.h"
#include 	"DomoBoard/domoBoard.h"
#include    "DomoBoard/Modbus_Domoboard.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
//Configuraci�n de la conexi�n MODBUS
#define	ADDR_SLAVE		1		//Direcci�n Dispositivo Esclavo
#define	SERIAL_BPS		115200	//Velocidad Comunicaci�n serie
#define	SERIAL_PARITY	'n'		//Paridad comunicaci�n serie
#define	TX_EN_PIN		0		//Pin usado para la transmisi�n RS485; 0 No usado


/****************************************************************************/
/***        DEFINICI�N DE FUNCIONES    **************************************/
/****************************************************************************/
void Init_RTU_Modbus();
void RTU_ModBus();

extern ModbusSlave mbs;
extern uint16_t	Cregs[MB_O_COILS];


#endif /* GEST_MODBUS_H_ */
