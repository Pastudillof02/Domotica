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
#include 	"utils_domoBoard.h"

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
	 * 19200 bps, 8E1, two-device network */
	/* Second step MBS: configure */
	/* the Modbus slave configuration parameters */
	const unsigned char 	SLAVE 	= ADDR_SLAVE;		//Address SLAVE
	const long 				BAUD 	= SERIAL_BPS;
	const char 				PARITY 	= SERIAL_PARITY;
	//const char 				TXENPIN = 0; //EN_485;
	const char 				TXENPIN = TX_EN_PIN;

	//Para la conexi�n 485/ModBus usamos
	Serial485 = &Serial;

	//We configure the ModBus Register Banks
	mbs.set_BankCoils(Cregs, Oregs, MB_O_COILS, MB_I_COILS);

	mbs.configure(SLAVE,BAUD,PARITY,TXENPIN);

	//Sets up event that occurred when Output Discrete register are updated
	//mbs.writecoil = writecoil;
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

		}
	}
}




void RTU_ModBus()
{

	if(mbs.update()){
		writecoil();
	}
}

