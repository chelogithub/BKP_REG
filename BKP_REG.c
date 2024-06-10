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

}
