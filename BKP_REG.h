/*******************************************************************************
*	Header para funciones de método http
*
*
*	Autor: Marcelo Garcia
*
******************************************************************************/
#include "main.h"

enum
{
	READ,
	WRITE
};

int BKP_REG_blk(RTC_HandleTypeDef *, uint8_t , uint8_t, uint32_t * );

/****************************************************************
*	Lee o escribe los registros de BackUp del RTC    	  		*
*																*
*	RTC_HandleTypeDef hrtc															*
*	uint8_t		:	0 = Error  1=OK					    		*
*	uint8_t	    :	0 = Escritura  1=Lectura					*
*	uint8_t		:	Cantidad de registros a acceder  			*
*	uint32_t *	:	Vector de blocque de datos					*
*																*
****************************************************************/

int BKP_RG_IP(RTC_HandleTypeDef *RTCreg, uint8_t WR, uint8_t addr, char * data);

/****************************************************************
*	Lee o escribe datos de IP en     	  						*
*																*
*	RTC_HandleTypeDef hrtc										*
*	uint8_t		:	1 = Escritura  0=Lectura			  		*
*	uint8_t	    :	Dirección a la que se quiere acceder		*
*	char *		:	Vector que entrega o recibe los datos  		*
*																*
****************************************************************/

