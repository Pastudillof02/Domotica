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
void config_practica1_apt_1(void){
	domoboard.BOTON1.SensorEvent = Pulsado_Soltado;

	domoboard.BOTON2.SensorEvent = Pulsado_Soltado;

	domoboard.BTN_OPT.SensorEvent = Pulsado_Soltado;
}

void config_practica1_apt_2(void){
	domoboard.BOTON1.SensorEvent = Interruptor;
	domoboard.BOTON1.Aux = OFF;

	domoboard.BOTON2.SensorEvent = Interruptor;
	domoboard.BOTON2.Aux = OFF;

	domoboard.BTN_OPT.SensorEvent = Interruptor;
	domoboard.BTN_OPT.Aux = OFF;
}

void config_practica1_apt_3(void){
	domoboard.BOTON1.SensorEvent = conmutador;

	domoboard.BOTON2.SensorEvent = conmutador;

	domoboard.BTN_OPT.SensorEvent = conmutador;
}

void config_practica3_apt_2(void){
	domoboard.BOTON1.SensorEvent = conmutador;

	domoboard.BOTON2.SensorEvent = conmutador;

	domoboard.BTN_OPT.SensorEvent = conmutador;
}

void config_practica4_apt_2(void)
{
	domoboard.BOTON1.SensorEvent = pulsado_soltado_triac_rele;

	domoboard.BOTON2.SensorEvent = pulsado_soltado_triac_rele;

	domoboard.BTN_OPT.SensorEvent = NULL;

}

void config_practica4_apt_3(void)
{
	domoboard.BOTON1.SensorEvent = interruptor_triac_rele;

	domoboard.BOTON2.SensorEvent = interruptor_triac_rele;

	domoboard.BTN_OPT.SensorEvent = NULL;
}

void config_practica4_apt_4(void)
{
	domoboard.BOTON1.SensorEvent = conmutador_triac_rele;

	domoboard.BOTON2.SensorEvent = conmutador_triac_rele;

	domoboard.BTN_OPT.SensorEvent = conmutador_triac_rele;
}

