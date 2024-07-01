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

    if(WR==1)
    {
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

		HAL_PWR_EnableBkUpAccess();
		HAL_RTCEx_BKUPWrite(RTCreg, addr, BKP_REG);
		HAL_PWR_DisableBkUpAccess();

    }
    else if(WR==0)
		{
		char returnVector[15];
		returnVector[0]='\0';
		uint32_t shifts=0;

		BKP_REG=HAL_RTCEx_BKUPRead(RTCreg, addr);	//Leo el dato en memoria de 32bits

		shifts=BKP_REG;
		octd=(shifts>>24)&0x000000FF;
		INTOA(octd, octc);		//Se pasa el entero a char y se guarda en octc.

		strncat(data,octc,strlen(octc));
		strncat(data,".",1);

		shifts=BKP_REG;
		octd=(shifts>>16)&0x000000FF;
		INTOA(octd, octc);		//Se pasa el entero a char y se guarda en octc.

		strncat(data,octc,strlen(octc));
		strncat(data,".",1);

		shifts=BKP_REG;
		octd=(shifts>>8)&0x000000FF;
		INTOA(octd, octc);		//Se pasa el entero a char y se guarda en octc.

		strncat(data,octc,strlen(octc));
		strncat(data,".",1);


		shifts=BKP_REG;
		octd=shifts&0x000000FF;
		INTOA(octd, octc);		//Se pasa el entero a char y se guarda en octc.

		strncat(data,octc,strlen(octc));
		}



}

int BKP_RG_2int(RTC_HandleTypeDef *RTCreg, uint8_t WR, uint8_t addr, char * data,char * data2)
{
	uint32_t num,num2=0;

    if(WR==1)
    {
    	num=atoi(data);
    	if (num<65536)
    	{
    		num=num<<16;
    	}
    	num2=atoi(data2);
    	if (num2<65536)
    	{
    		num=num|(num2&0x0000FFFF);
    	}

		HAL_PWR_EnableBkUpAccess();
		HAL_RTCEx_BKUPWrite(RTCreg, addr, num);
		HAL_PWR_DisableBkUpAccess();

    }
    else if(WR==0)
		{
			num=HAL_RTCEx_BKUPRead(RTCreg, addr);
			num2=((num>>16)&0x0000FFFF);
			INTOA(num2, data);
			num2=(num & 0x0000FFFF);
			INTOA(num2,data2);
		}
}

int BKP_RG_BYTE(RTC_HandleTypeDef *RTCreg, uint8_t WR, uint8_t addr , uint8_t byte , char * data)
{
	uint32_t num,num2=0;
	if(byte>3) return(0);
	switch(byte)
	{
		case 0:
		{
			    if(WR==1)
				{
					num2=HAL_RTCEx_BKUPRead(RTCreg, addr);  //leo el registro de 32 bits
					num2=num2|(num2&0xFFFFFF00);			//Pongo el byte todo en 0
					num=atoi(data);
					if (num<256)							//Valido el dato
					{
						num2=num2|num;						//Transfiero el nro al byte seleccionado
					}
					HAL_PWR_EnableBkUpAccess();
					HAL_RTCEx_BKUPWrite(RTCreg, addr, num2);
					HAL_PWR_DisableBkUpAccess();
				}
				else if(WR==0)
					{
						num2=HAL_RTCEx_BKUPRead(RTCreg, addr);
						num=(num2&0x000000FF);
						INTOA(num, data);
					}	
			return(num);
		}
		break;
		case 1:
		{
			    if(WR==1)
				{
					num2=HAL_RTCEx_BKUPRead(RTCreg, addr);  //leo el registro de 32 bits
					num2=num2|(num2&0xFFFF00FF);			//Pongo el byte todo en 0
					num=atoi(data);
					if (num<256)							//Valido el dato
					{
						num=num<<8;							//Me desplazo al byte 1
						num2=num2|num;						//Transfiero el nro al byte seleccionado
					}
					HAL_PWR_EnableBkUpAccess();
					HAL_RTCEx_BKUPWrite(RTCreg, addr, num2);
					HAL_PWR_DisableBkUpAccess();
				}
				else if(WR==0)
					{
						num2=HAL_RTCEx_BKUPRead(RTCreg, addr);
						num=(num2&0x0000FF00);
						num=num>>8;
						INTOA(num, data);
					}	
			return(num);
		}
		break;
		case 2:
		{
			    if(WR==1)
				{
					num2=HAL_RTCEx_BKUPRead(RTCreg, addr);  //leo el registro de 32 bits
					num2=num2|(num2&0xFF00FFFF);			//Pongo el byte todo en 0
					num=atoi(data);
					if (num<256)							//Valido el dato
					{
						num=num<<16;							//Me desplazo al byte 2
						num2=num2|num;						//Transfiero el nro al byte seleccionado
					}
					HAL_PWR_EnableBkUpAccess();
					HAL_RTCEx_BKUPWrite(RTCreg, addr, num2);
					HAL_PWR_DisableBkUpAccess();
				}
				else if(WR==0)
					{
						num2=HAL_RTCEx_BKUPRead(RTCreg, addr);
						num=(num2&0x00FF0000);
						num=num>>16;
						INTOA(num, data);
					}	
			return(num);
		}
		break;
		case 3:
		{
			    if(WR==1)
				{
					num2=HAL_RTCEx_BKUPRead(RTCreg, addr);  //leo el registro de 32 bits
					num2=num2|(num2&0x00FFFFFF);			//Pongo el byte todo en 0
					num=atoi(data);
					if (num<256)							//Valido el dato
					{
						num=num<<24;							//Me desplazo al byte 3
						num2=num2|num;						//Transfiero el nro al byte seleccionado
					}
					HAL_PWR_EnableBkUpAccess();
					HAL_RTCEx_BKUPWrite(RTCreg, addr, num2);
					HAL_PWR_DisableBkUpAccess();
				}
				else if(WR==0)
					{
						num2=HAL_RTCEx_BKUPRead(RTCreg, addr);
						num=(num2&0xFF000000);
						num=num>>24;
						INTOA(num, data);
					}	
			return(num);
		}
		break;

	}
}

BKP_REG_WF_CONN(RTC_HandleTypeDef *RTCreg, uint8_t WR, uint8_t WF, struct BKP_REG * nvs)
{
	int a=0,cdata=0;
	uint32_t num=0,num2=0;
	if(WR==1)
	{
		int i=0,b=0,w=0;
		/* Control para SSID o PASS
		Si WF=10 cdata=13, 
		Si WF=13 cdata=29*/
		if(WF==10)
			{
				cdata=13;
			}
		else if(WF==13)
				{
					cdata=29;
				}
		HAL_PWR_EnableBkUpAccess();
		while(i<cdata)//while(i<13)
		{ 
			while(b<4)
			{
				//num=nvs->_WIFI_PASS[i];
						if(WF==10)
							{
								num=nvs->_WIFI_PASS[i];
							}
						else if(WF==13)
								{
									num=nvs->_WIFI_SSID[i];
								}
				num=num<<24-(b*8);
				num2=num2|num;
				num=0;
				b++;
				i++;
			}
			HAL_RTCEx_BKUPWrite(RTCreg, WF+w, num2);
			w++; //Incrementador de registros de 32 bit
			b=0;
			num2=0;
		}
		HAL_PWR_DisableBkUpAccess();

	}
	else if(WR==0)
			{
				int i=0,b=0,w=0;
						if(WF==10)
							{
								cdata=3;
							}
						else if(WF==13)
								{
									cdata=7;
								}
				while(b<cdata)
				{ 	num=HAL_RTCEx_BKUPRead(RTCreg, WF+b);	//Leo el registro de 32 bits
					while(i<4)
					{
						num2=num>>24-(i*8);
						num2=num2&0x000000FF;
						if(WF==10)
							{
								nvs->_WIFI_PASS[w]=num2;
							}
						else if(WF==13)
								{
									nvs->_WIFI_SSID[w]=num2;
								}	
						i++;
						w++;
						num2=0;
					}
					i=0;
					b++;
				}
			}
}
		/*
		num=nvs->_WIFI_PASS[0];
		num=num<<24;
		num2=num2|num;
		num=0;
		num=nvs->_WIFI_PASS[1];
		num=num<<16;
		num2=num2|num;
		num=0;
		num=nvs->_WIFI_PASS[2];
		num=num<<8;
		num2=num2|num;
		num=0;
		num=nvs->_WIFI_PASS[3];
		num2=num2|num;
		HAL_PWR_EnableBkUpAccess();
		HAL_RTCEx_BKUPWrite(RTCreg, WF, num2);
		num=0;
		num2=0;
		num=nvs->_WIFI_PASS[4];
		num=num<<24;
		num2=num2|num;
		num=0;
		num=nvs->_WIFI_PASS[5];
		num=num<<16;
		num2=num2|num;
		num=0;
		num=nvs->_WIFI_PASS[6];
		num=num<<8;
		num2=num2|num;
		num=0;
		num=nvs->_WIFI_PASS[7];
		num2=num2|num;
		HAL_RTCEx_BKUPWrite(RTCreg, WF+1, num2);
		num=0;
		num2=0;
		num=nvs->_WIFI_PASS[8];
		num=num<<24;
		num2=num2|num;
		num=0;
		num=nvs->_WIFI_PASS[9];
		num=num<<16;
		num2=num2|num;
		num=0;
		num=nvs->_WIFI_PASS[10];
		num=num<<8;
		num2=num2|num;
		num=0;
		num=nvs->_WIFI_PASS[11];
		num2=num2|num;
		HAL_RTCEx_BKUPWrite(RTCreg, WF+2, num2);
		HAL_PWR_DisableBkUpAccess();*/
