/*
 * Gest_Modbus.cpp
 *
 *  Created on: 16/05/2014
 *      Author: jctejero
 *
 *  Modified on: 16/03/2022
 */

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include	<Arduino.h>
#include	"Gest_Modbus.h"
#include	"config_practicas.h"
#include    "libraries/EEPROM/src/EEPROM.h"

/****************************************************************************/
/***        Variables Locales                                             ***/
/****************************************************************************/
/* First step MBS: create an instance */
ModbusSlave mbs;

/****************************************************************************/
/***                 Definici�n de funciones                              ***/
/****************************************************************************/
//void writecoil(unsigned int addrReg);

/****************************************************************************/
/***                 Functions                                            ***/
/****************************************************************************/
void Init_RTU_Modbus()
{
	/* configure modbus communication
	 * 115200 bps, 8E1, two-device network */
	/* Second step MBS: configure */
	/* the Modbus slave configuration parameters */
	const unsigned char 	SLAVE 	= ADDR_SLAVE;		//Address SLAVE
	const long 				BAUD 	= SERIAL_BPS;
	const char 				PARITY 	= SERIAL_PARITY;
	//const char 				TXENPIN = 0; //EN_485;
	const char 				TXENPIN = TX_EN_PIN;

	//Para la conexi�n 485/ModBus usamos
	Serial485 = &Serial;

	mbs.set_BankCoils(Cregs, MB_O_COILS);
	mbs.set_BankDiscreteInputs(Dregs, MB_I_CONTATCS);
	mbs.set_BankOutputHoldingRegister(Aregs, MB_A_REGS);
	mbs.set_BankInputAnalogRegister(Iregs, MB_I_REGS);


	mbs.configure(SLAVE,BAUD,PARITY,TXENPIN);
}


/*
 *
 */

//void writecoil(unsigned int addrReg){
void writecoil(){
	for (int addrReg = 0; addrReg < MB_O_COILS; addrReg++) {

		switch (addrReg) {
		case MB_RELE:
			domoboard.setActuator(&domoboard.RELE, Cregs[MB_RELE] != 0x00);
			break;

		case MB_TRIAC:
			domoboard.setActuator(&domoboard.TRIAC, Cregs[MB_TRIAC] != 0x00);
			break;

		case   MB_ACTPIR:
			mbDomoboard.PIR_MOV.Sensor->Activo = Cregs[addrReg]!=0x00;

			//Save PIR Activation
			EEPROM.update(ADDR_ACTPIR, Cregs[addrReg] != 0x00);

			break;

		}
	}
}

/*
 *
 */

void writeholdingregister(){
	//char msg[50];

	for (int addrReg = 0; addrReg < MB_A_REGS; addrReg++) {
		switch (addrReg) {
		case MB_SELPRACT:
			//Save pratice selected
			EEPROM.update(ADDR_SELPRACT, Aregs[ADDR_SELPRACT]&0xFF);

			//Go To Selecction Configuration
			SelectionConfiguration((uint8_t) (Aregs[MB_SELPRACT] & 0xFF));
			break;

		case MB_TMP_PIR:
			//Almacenar Tiempo de activaci�n Sensor PIR (Big Endian)
			EEPROM.update(ADDR_TIEMPO_PIR_1, (Aregs[MB_TMP_PIR]>>8)&0xFF);
			EEPROM.update(ADDR_TIEMPO_PIR_2, (Aregs[MB_TMP_PIR]&0xFF));
			break;
		}
	}
}


void RTU_ModBus()
{

	if(mbs.update()){
		writecoil();

		writeholdingregister();
	}
}

/*
 * void load_config().- load initial configuration for arduino aplication
 */
void load_Config(){
	//Leemos configuraci�n Actual "Selecci�n Pr�ctica"
	Aregs[MB_SELPRACT] = EEPROM.read(ADDR_SELPRACT);	//Read EEPROM

	Aregs[MB_SELPRACT] = Aregs[MB_SELPRACT] != 0x00 ? Aregs[MB_SELPRACT] : 0x11;	//Seleccionamos la pr�ctica 1 apartado 1 por defecto

	DEBUGLOGLN("Pr�ctica Seleccionada: 0x%X", Aregs[MB_SELPRACT]);

	/*
	 * Config PIR
	 */
	//Leer activaci�n del PIR
	Cregs[MB_ACTPIR] = EEPROM.read(ADDR_ACTPIR);

	DEBUGLOGLN("PIR activado: %d", Cregs[MB_ACTPIR]);

	//Leer Tiempo activaci�n PIR
	Aregs[MB_TMP_PIR] = ((EEPROM.read(ADDR_TIEMPO_PIR_1)&0xFF) << 8) + (EEPROM.read(ADDR_TIEMPO_PIR_2)&0xFF) ;

	DEBUGLOGLN("Tiempo Activaci�n del PIR: %d Segundos", Aregs[MB_TMP_PIR]);
}


