/*******************************************************************************
*	Header para funciones de método http
*
*
*	Autor: Marcelo Garcia
*
******************************************************************************/
#include "main.h"

int BKP_REG_blk(RTC_HandleTypeDef *, uint8_t , uint8_t, uint32_t * );

/****************************************************************
*	Lee o escribe los registros de BackUp del RTC    	  		*
*																*
*	RTC_HandleTypeDef hrtc															*
*	uint8_t		:	0 = Error  1=OK					    		*
*	uint8_t	    :	0 = Escritura  1=Lectura					*
*	uint8_t		:	Cantidad de registros a aceder  			*
*	uint32_t *	:	Vector de blocque de datos					*
*																*
****************************************************************/

