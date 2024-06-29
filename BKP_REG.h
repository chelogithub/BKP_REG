/*******************************************************************************
*	Header para funciones de método http
*
*
*	Autor: Marcelo Garcia
*
******************************************************************************/
#include "main.h"

#define WIFI_IP 	0
#define	WIFI_MSK	1
#define	PORT		2
#define	ETH_IP		3
#define	ETH_TRGT_IP	4
#define	ETH_MSK		5
#define	SERVER		6
#define	LORA		7
#define	MODBUS		8
#define	LR_SRVR		9
#define	END_KEY		9

#define BAND	 	0
#define	NCPIN		1
#define	NET_ID		2
#define	ADDR		3

#define SRVR	 	0
#define	CODE		1
#define	ID			2
#define	REG			3

#define	LR_SRVR_BT	3


enum
{
	READ,
	WRITE
};

int BKP_REG_blk(RTC_HandleTypeDef *, uint8_t , uint8_t, uint32_t * );

/****************************************************************
*	Lee o escribe los registros de BackUp del RTC    	  		*
*																*
*	RTC_HandleTypeDef hrtc										*
*	uint8_t		:	0 = Error  1=OK					    		*
*	uint8_t	    :	0 = Escritura  1=Lectura					*
*	uint8_t		:	Cantidad de registros a acceder  			*
*	uint32_t *	:	Vector de blocque de datos					*
*																*
****************************************************************/

int BKP_RG_IP(RTC_HandleTypeDef *, uint8_t , uint8_t , char * );

/****************************************************************
*	Lee o escribe datos de IP en     	  						*
*																*
*	RTC_HandleTypeDef hrtc										*
*	uint8_t		:	1 = Escritura  0=Lectura			  		*
*	uint8_t	    :	Dirección a la que se quiere acceder		*
*	char *		:	Vector que entrega o recibe los datos  		*
*																*
****************************************************************/

int BKP_RG_2int(RTC_HandleTypeDef *, uint8_t , uint8_t , char * ,char * );

/****************************************************************
*	Lee o escribe dos enteros de 16 bits en nuna de 32			*
*																*
*	RTC_HandleTypeDef hrtc										*
*	uint8_t		:	1 = Escritura  0=Lectura			  		*
*	uint8_t	    :	Dirección a la que se quiere acceder		*
*	char *		:	Vector que entrega o recibe los datos  		*
*	char *		:	Vector que entrega o recibe los datos  		*
*																*
****************************************************************/
int BKP_RG_BYTE(RTC_HandleTypeDef *, uint8_t , uint8_t ,uint8_t , char *);

/****************************************************************
*	Lee o escribe dos enteros de 16 bits en nuna de 32			*
*																*
*	RTC_HandleTypeDef hrtc										*
*	uint8_t		:	1 = Escritura  0=Lectura					*
*	uint8_t	    :	Dirección a la que se quiere acceder   		*
*	uint8_t	    :	Byte al que se quiere acceder 3-0			*
*	char *		:	Vector que entrega o recibe los datos  		*
*	char *		:	Vector que entrega o recibe los datos  		*
*																*
****************************************************************/
