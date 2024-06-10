/*******************************************************************************
*	Funciones de método BKP_REG
*
*
*	Autor: Marcelo Garcia
*
*******************************************************************************/
#include "BKP_REG.h"

int BKP_REG_blk(uint8_t WR, uint8_t regs, uint32_t * data)
{
		  if (WR==1) HAL_PWR_EnableBkUpAccess();	//Habilito el acceso de escriura a los registros

		  if (regs< 20)
		  {
			for(int i=0; i<=regs-1; i++)
				{
					if (WR==0)
					{ HAL_RTCEx_BKUPWrite(&hrtc, i, data[i]); //Escritura en los registros
					}
					else
					{ data[i]=HAL_RTCEx_BKUPRead(&hrtc, i);	//Lectura desde los registros
					}
				}
			if (WR==1)	HAL_PWR_DisableBkUpAccess();	//Deshabilito el acceso de escriura a los registros
			return(1);
		  }
		  else
		  	{return 0}
}