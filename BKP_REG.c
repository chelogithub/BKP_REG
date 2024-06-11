/*******************************************************************************
*	Funciones de método BKP_REG
*
*
*	Autor: Marcelo Garcia
*
*******************************************************************************/
#include "BKP_REG.h"
#include "main.h"

int BKP_REG_blk(RTC_HandleTypeDef *RTCreg, uint8_t WR, uint8_t regs, uint32_t * data)
{
		  if (WR == 1) HAL_PWR_EnableBkUpAccess();	//Habilito el acceso de escriura a los registros

		  if (regs <= 20)
		  {
			for(int i=0; i<= (regs-1); i++)
				{
					if (WR==1)
					{ HAL_RTCEx_BKUPWrite(RTCreg, i, data[i]); //Escritura en los registros
					}
					else
					{ data[i]=HAL_RTCEx_BKUPRead(RTCreg, i);	//Lectura desde los registros
					}
				}
			if (WR == 1)	HAL_PWR_DisableBkUpAccess();	//Deshabilito el acceso de escriura a los registros
			return(1);
		  }
		  else
		  	{return (0);}
}

int BKP_RG_IP(RTC_HandleTypeDef *RTCreg, uint8_t WR, uint8_t addr, char * data)
{
	int lng_data=0,i=0,io=0,nocteto=1;
	uint32_t BKP_REG=0;
	uint32_t octd,octe2,octe3,octe4;
	char octc[4],oct2[4],oct3[4],oct4[4];

	lng_data=strlen(data);


	octd=0;
	while(*data != '.' )
	{
		octc[io]=*data;
		*data++;
		io++;
		i++;
		if(i==4) return(1); //Error en longitud de caracteres
	}
	*data++;
	i++;
	octc[io]='\0';
	octd=atoi(octc);
	BKP_REG=octd;

	io=0;
	while(*data != '.' )
	{
		octc[io]=*data;
		*data++;
		io++;
		i++;
		if(i==4) return(1); //Error en longitud de caracteres
	}
	*data++;
	i++;
	octc[io]='\0';
	octd=atoi(octc);


	BKP_REG=BKP_REG<<8;
	BKP_REG=BKP_REG | octd;

	io=0;
	while(*data != '.' )
	{
		octc[io]=*data;
		*data++;
		io++;
		i++;
		if(i==4) return(1); //Error en longitud de caracteres
	}
	*data++;
	i++;
	octc[io]='\0';
	octd=atoi(octc);


	BKP_REG=BKP_REG<<8;
	BKP_REG=BKP_REG | octd;

	io=0;
	while(*data != '\0' )
	{
		octc[io]=*data;
		*data++;
		io++;
		i++;
		if(i==4) return(1); //Error en longitud de caracteres
	}
	*data++;
	i++;
	octc[io]='\0';
	octd=atoi(octc);


	BKP_REG=BKP_REG<<8;
	BKP_REG=BKP_REG | octd;

	if(WR==1)
	{
		HAL_PWR_EnableBkUpAccess();
		HAL_RTCEx_BKUPWrite(RTCreg, addr, BKP_REG);
		HAL_PWR_DisableBkUpAccess();

	}

}
