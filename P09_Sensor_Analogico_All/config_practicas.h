/*
 * config_practicas.h
 *
 *  Created on: 10/03/2015
 *      Author: jctejero
 *
 *  Modified on: 16/03/2022
 */

#ifndef CONFIG_PRACTICAS_H_
#define CONFIG_PRACTICAS_H_
/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include	"debuglog.h"
#include	"utils_domoBoard.h"
#include	"DomoBoard/domoBoard.h"
#include	"DomoBoard/ModbusDomoboard.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
//Defininici�n de comando de configuraci�n
#define	P1_PULSADORES				0x11
#define	P1_INTERRUPTOR				0x12
#define	P1_CONMUTADOR				0x13
#define	P3_CONMUTADOR				0x32
#define	P4_PULSADORES				0x41
#define	P4_INTERRUPTOR				0x42
#define	P4_CONMUTADOR				0x43
#define PRACTICAS_MODBUS			0x50
#define	P5_INTERRUPTOR				0x54
#define	P6_INTERRUPTOR				0x62
#define P7_PIR						0x70
#define P9_ALL						0x90
#define P10_PER						0xA0
#define P10_GARAJE					0xA1

void SelectionConfiguration(uint8_t selConf);

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
void config_practica3_apt_2();

void config_practica4_apt_1();
void config_practica4_apt_2();
void config_practica4_apt_3();

void config_practica5_apt_4();

void Config_P10_garaje();

void SelectionConfiguration(uint8_t selConf);

extern TCtrlTime ctrlPersiana;

#endif /* CONFIG_PRACTICAS_H_ */
