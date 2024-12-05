/*
 * ModbusDomoboard.h
 *
 *  Created on: 11 mar. 2020
 *      Author: jctej
 *
 *  Modified: 03/04/2021
 *  Modified on: 16/03/2022
 */

#ifndef DOMOBOARD_MODBUSDOMOBOARD_H_
#define DOMOBOARD_MODBUSDOMOBOARD_H_

/**********************************************************************/
/***                         Include Files                          ***/
/**********************************************************************/
#include "domoBoard.h"
#include "../ModbusSlave/ModBusSlave.h"
#include "../AsyncWait.h"

/**********************************************************************/
/***                         enums Definitions                      ***/
/**********************************************************************/
/* slave registers */

//Discrete Output Coils
enum {
	MB_RELE,
	MB_TRIAC,
	MB_ACTPIR,					//Salida virtual para Activar/Desactivar PIR
	MB_ACTSRC,					//Salida virtual para Activar/Desactivar SRC --> PhotoResistor
	MB_ACTTOR,					//Salida virtual para Activar/Desactivar Trigger --> PhotoTransistor
	MB_UP,					
	MB_DOWN,		
	MB_GARAJE,
	MB_O_COILS
};

//Discrete Input Contacts
enum {
	MB_BOTON1,
	MB_BOTON2,
	MB_BTNOPT,
	MB_PIRMOV,
	MB_I_CONTATCS
};

//Registros ModBus para variables anal�gicas "Analog Output Holding Register"
enum{
	MB_SELPRACT,		// Registro ModBus Para seleccionar la configuraci�n del sistema
	MB_TMP_PIR,			// Registro para controlar el tiempo activo del sensor PIR (Segundos)
	MB_SRC_HL,			// Registro para controlar el nivel superior de activaci�n SRC
	MB_SRC_LL,			// Registro para controlar el nivel Inferior de activaci�n SRC
	MB_TTOR_LL,			// Registro para controlar el nivel Inferior de activaci�n del PHOTOTTOR
	MB_STATE_PERS,
	MB_A_REGS			// Total de registros Anal�gicos
};

//Registros Anal�gicos de Entrada
enum{
	MB_POT1,			// POTENCI�METRO 1
	MB_POT2,			// POTENCI�METRO 2
	MB_PHOTORES,		// PhotoResistor
	MB_TEMPSEN,			// Sensor de Temperatura
	MB_PHOTOTTOR,		// Photo Transistor
	MB_PERCEN_PERS,
	MB_I_REGS			// Total de registros de Entrada
};

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
//State Actuator
typedef enum{
	OFF,
	ON,
	TOGGLE
}TStateDigitalDev;

typedef struct
{
	tpsActuator		actuator;
	uint16_t 		*mbRegs;			//Registro asociado para comunicaciones ModBus
}TmbActuator, *TpmbActuator;

typedef 	QueueList<TpmbActuator>		TmbActuators;

//Estructura para usar niveles.
typedef struct{
	uint16_t	*lSup;					//puntero al valor del nivel superior
	uint16_t	*lInf;					//puntero al valor del nivel inferior
}TctrlLevel, *TctrlLevelPtr;

typedef struct{
	ptsSensor			Sensor;			//Sensor asociado
	int					Aux;			//Variable auxiliar, a la espera de definir el banco de registros digitales de entrada
	uint16_t 			*mbRegs;		//Registro asociado para comunicaciones ModBus
	TmbActuators		mbActuators;	//Listado de actuadores manejados por el sensor
	TNotifyEvent		mbSensorEvent;	//Evento para aplicaci�n asociada
	AsyncWait			*asyncWait;		//Para controlar si el evento asociado al sensor tiene un componente temporizado
	TctrlLevel			ctrlLevelPtr;   //Estructura para controlar utilidades que requieran de niveles
	void 				*rSensores;
}TmbSensor, *TpmbSensor;

typedef struct{
	bool			activa;
	uint32_t 		inicio;			
	uint16_t		*tiempoFinal;			
	int32_t			tiempoActivo;
}TCtrlTime, *TPCtrlTime;

typedef struct{
	QueueList<TpmbSensor> mbRSensores;
}TmbRSensores;

/*************************************************************/
/***                         CLASS                         ***/
/*************************************************************/
class ModbusDomoboard: public DomoBoard {
private:
	ModbusSlave	*mbs = NULL;

public:

	//Sensores Digitales
	TmbSensor	BOTON1;
	TmbSensor	BOTON2;
	TmbSensor	BTN_OPT;
	TmbSensor	PIR_MOV;

	//Sensores Anal�gicos
	TmbSensor	POT1;				// Potenci�metro 1
	TmbSensor	POT2;				// Potenci�metro 2
	TmbSensor	PHOTORES;			// Photoresistor
	TmbSensor	TEMPSEN;			// Sensor Temperatura
	TmbSensor	PHOTOTTOR;			// Photo Transistor

	TmbActuator RELE;
	TmbActuator TRIAC;

	TmbActuator PERSIANA_UP;				
	TmbActuator PERSIANA_DOWN;			

	ModbusDomoboard();
	virtual ~ModbusDomoboard(){};

	void 	leerAllSensor(void);
	void 	leerSensor(TpmbSensor Sensor);

	void 	setmbActuator(TmbActuator *Actuator, TStateDigitalDev val);
	void 	manager_mbActuators(TmbActuators *Actuators, TStateDigitalDev val);
	void 	setModBusSlave(ModbusSlave *mbSlave);
	void    clear_Actuators();

	void 	set_coilRegister(uint16_t addReg, uint16_t value);
	void 	set_holdingRegister(uint16_t addReg, uint16_t value);

};

extern ModbusDomoboard mbDomoboard;
extern uint16_t	Cregs[MB_O_COILS];
extern uint16_t	Dregs[MB_I_CONTATCS];	//Registros para "Dicrete Input Contacts"
extern uint16_t	Aregs[MB_A_REGS];		//Registros para "Analog Output Holding Registers"
extern uint16_t	Iregs[MB_I_REGS];		//Registros para "Analog Input Registers"

#endif /* DOMOBOARD_MODBUSDOMOBOARD_H_ */
