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
#include    "DomoBoard/ModbusDomoboard.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
//Configuración de la conexión MODBUS
#define	ADDR_SLAVE		1		//Dirección Dispositivo Esclavo
#define	SERIAL_BPS		115200  //Velocidad Comunicación serie
#define	SERIAL_PARITY	'n'		//Paridad comunicación serie
#define	TX_EN_PIN		EN_485		//Pin usado para la transmisión RS485; 0 No usado

// La cofiguración de domoboard usando ModBus, será almacenada en la EEPROM.
// Las direccioes de los valores a almacenar se indican acontinuación

#define	ADDR_SELPRACT		0		//Comando de Configuración actual de DomoBoad
#define	ADDR_ACTPIR			1		//Activa/Desactiva PIR
#define ADDR_TIEMPO_PIR_1	2		//Tiempo PIR Activo 1
#define ADDR_TIEMPO_PIR_2	3		//Tiempo PIR Activo 2
#define ADDR_FOTOR_H_1		4
#define ADDR_FOTOR_H_2		5
#define ADDR_FOTOR_L_1		6
#define ADDR_FOTOR_L_2		7
#define ADDR_FOTOT_L_1		8
#define ADDR_FOTOT_L_2		9







/****************************************************************************/
/***        DEFINICIÓN DE FUNCIONES    **************************************/
/****************************************************************************/
void Init_RTU_Modbus();
void RTU_ModBus();
void writeholdingregister();
void load_Config();

extern ModbusSlave mbs;


#endif /* GEST_MODBUS_H_ */
