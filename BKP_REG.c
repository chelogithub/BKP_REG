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
	int lng_data=0,io=0,nocteto=1;
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
    		//i++;
    		if(io==4) return(1); //Error en longitud de caracteres
    	}
    	*data++;
    	//i++;
    	octc[io]='\0';
    	octd=atoi(octc);
    	BKP_REG=octd;

    	io=0;
    	while(*data != '.' )
    	{
    		octc[io]=*data;
    		*data++;
    		io++;
    		//i++;
    		if(io==4) return(1); //Error en longitud de caracteres
    	}
    	*data++;
    	//i++;
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
    		//i++;
    		if(io==4) return(1); //Error en longitud de caracteres
    	}
    	*data++;
    	//i++;
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
    		//i++;
    		if(io==4) return(1); //Error en longitud de caracteres
    	}
    	*data++;
    	//i++;
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
		data[0]='\0';  //240107

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
		data[strlen(data)]='\0'; //240107
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
	uint32_t num=0,num2=0;
	if(byte>3) return(0);
	switch(byte)
	{
		case 0:
		{
			    if(WR==1)
				{
					num2=HAL_RTCEx_BKUPRead(RTCreg, addr);  //leo el registro de 32 bits
					num2=num2&0xFFFFFF00;//num2=num2|(num2&0xFFFFFF00);			//Pongo el byte todo en 0
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
						data[0]='\0'; //240107
						INTOA(num, data);
						data[strlen(data)]='\0'; //240107
					}	
			return(num);
		}
		break;
		case 1:
		{
			    if(WR==1)
				{
					num2=HAL_RTCEx_BKUPRead(RTCreg, addr);  //leo el registro de 32 bits
					num2=num2&0xFFFF00FF;//num2=num2|(num2&0xFFFF00FF);			//Pongo el byte todo en 0
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
						data[0]='\0'; //240107
						INTOA(num, data);
						data[strlen(data)]='\0'; //240107
					}	
			return(num);
		}
		break;
		case 2:
		{
			    if(WR==1)
				{
					num2=HAL_RTCEx_BKUPRead(RTCreg, addr);  //leo el registro de 32 bits
					num2=num2&0xFF00FFFF;//num2=num2|(num2&0xFF00FFFF);			//Pongo el byte todo en 0
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
						data[0]='\0'; //240107
						INTOA(num, data);
						data[strlen(data)]='\0'; //240107
					}	
			return(num);
		}
		break;
		case 3:
		{
			    if(WR==1)
				{
					num2=HAL_RTCEx_BKUPRead(RTCreg, addr);  //leo el registro de 32 bits
					num2=num2&0x00FFFFFF;//num2=num2|(num2&0x00FFFFFF);			//Pongo el byte todo en 0
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
						data[0]='\0'; //240107
						INTOA(num, data);
						data[strlen(data)]='\0'; //240107
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

BKP_REG_RW(RTC_HandleTypeDef *RTCreg, uint8_t WR,struct BKP_REG * NVS )
{
	if(WR==1)
	{
		  BKP_RG_IP(RTCreg,  WRITE, WIFI_IP		, NVS->_WIFI_IP);
		  BKP_RG_IP(RTCreg,	 WRITE, WIFI_MSK	, NVS->_WIFI_MASK);
		  BKP_RG_2int(RTCreg,WRITE, PORT 		, NVS->_WIFI_PORT ,NVS->_ETH_PORT);
		  BKP_RG_IP(RTCreg,  WRITE, ETH_IP		, NVS->_ETH_IP);
		  BKP_RG_IP(RTCreg,  WRITE, ETH_TRGT_IP	, NVS->_ETH_TRGT_IP);
		  BKP_RG_IP(RTCreg,  WRITE, ETH_MSK		, NVS->_ETH_MASK);
		  BKP_RG_IP(RTCreg,  WRITE, SERVER		, NVS->_SERVER);
		  BKP_RG_BYTE(RTCreg, WRITE, LORA 		, BAND 	, NVS->_LORA_BAND);
		  BKP_RG_BYTE(RTCreg, WRITE, LORA 		, NCPIN , NVS->_LORA_NCPIN);
		  BKP_RG_BYTE(RTCreg, WRITE, LORA 		, NET_ID, NVS->_LORA_NET_ID);
		  BKP_RG_BYTE(RTCreg, WRITE, LORA 		, ADDR 	, NVS->_LORA_ADDR);
		  BKP_RG_BYTE(RTCreg, WRITE, MODBUS 		, SRVR 	, NVS->_MBUS_SRVR);
		  BKP_RG_BYTE(RTCreg, WRITE, MODBUS 		, CODE 	, NVS->_MBUS_CODE);
		  BKP_RG_BYTE(RTCreg, WRITE, MODBUS 		, ID	, NVS->_MBUS_ID);
		  BKP_RG_BYTE(RTCreg, WRITE, MODBUS 		, REG 	, NVS->_MBUS_REG);
		  BKP_REG_WF_CONN(RTCreg,WRITE, PASS, NVS);
		  BKP_REG_WF_CONN(RTCreg,WRITE, SSID, NVS);

	}
	else if(WR==0)
		{
			  BKP_RG_IP(RTCreg,   READ, WIFI_IP		, NVS->_WIFI_IP);
			  BKP_RG_IP(RTCreg,	  READ, WIFI_MSK		, NVS->_WIFI_MASK);
			  BKP_RG_2int(RTCreg, READ, PORT 		, NVS->_WIFI_PORT ,NVS->_ETH_PORT);
			  BKP_RG_IP(RTCreg,   READ, ETH_IP		, NVS->_ETH_IP);
			  BKP_RG_IP(RTCreg,   READ, ETH_TRGT_IP	, NVS->_ETH_TRGT_IP);
			  BKP_RG_IP(RTCreg,   READ, ETH_MSK		, NVS->_ETH_MASK);
			  BKP_RG_IP(RTCreg,   READ, SERVER		, NVS->_SERVER);
			  BKP_RG_BYTE(RTCreg, READ, LORA 		, BAND 	, NVS->_LORA_BAND);
			  BKP_RG_BYTE(RTCreg, READ, LORA 		, NCPIN , NVS->_LORA_NCPIN);
			  BKP_RG_BYTE(RTCreg, READ, LORA 		, NET_ID, NVS->_LORA_NET_ID);
			  BKP_RG_BYTE(RTCreg, READ, LORA 		, ADDR 	, NVS->_LORA_ADDR);
			  BKP_RG_BYTE(RTCreg, READ, MODBUS 		, SRVR 	, NVS->_MBUS_SRVR);
			  BKP_RG_BYTE(RTCreg, READ, MODBUS 		, CODE 	, NVS->_MBUS_CODE);
			  BKP_RG_BYTE(RTCreg, READ, MODBUS 		, ID	, NVS->_MBUS_ID);
			  BKP_RG_BYTE(RTCreg, READ, MODBUS 		, REG 	, NVS->_MBUS_REG);
			  strcpy(NVS->_WIFI_PASS,"AAAAAAAAAAA");
			  strcpy(NVS->_WIFI_SSID,"BBBBBBBBBBBBBBBBBBBBBBBBBB");
			  BKP_REG_WF_CONN(RTCreg,READ, PASS, NVS);
			  BKP_REG_WF_CONN(RTCreg,READ, SSID, NVS);
		}
}

void BKP_REG_SHW(struct BKP_REG * NVS,UART_HandleTypeDef *PORTSER, uint8_t SEND)
{ 
	char data[4096];
	strcpy(data,"\r\n SYS-Valores de configuracion");
	strcat(data,"\r\n\r\nCONEXION Wi-Fi\r\n");
	strcat(data,"\r\nSSID: ");
	strcat(data,NVS->_WIFI_SSID);
	strcat(data,"\r\nPASS: ");
	strcat(data,NVS->_WIFI_PASS);
	strcat(data,"\r\n\r\nCONFIGRACION DE INTEFAZ Wi-Fi\r\n");
	strcat(data,"\r\nIP: ");
	strcat(data,NVS->_WIFI_IP);
	strcat(data,"\r\nMASK: ");
	strcat(data,NVS->_WIFI_MASK);
	strcat(data,"\r\nPORT: ");
	strcat(data,NVS->_WIFI_PORT);
	strcat(data,"\r\n\r\nCONFIGRACION DE INTEFAZ ETHERNET\r\n");
	strcat(data,"\r\nPORT: ");
	strcat(data,NVS->_ETH_PORT);
	strcat(data,"\r\nIP: ");
	strcat(data,NVS->_ETH_IP);
	strcat(data,"\r\nDEST IP: ");
	strcat(data,NVS->_ETH_TRGT_IP);
	strcat(data,"\r\nMASK: ");
	strcat(data,NVS->_ETH_MASK);
	strcat(data,"\r\nSERVER IP: ");
	strcat(data,NVS->_SERVER);
	strcat(data,"\r\n\r\nCONFIGRACION DE DISPOSITIVO LORA\r\n");
	strcat(data,"\r\nDIRECCION: ");
	strcat(data,NVS->_LORA_ADDR);
	strcat(data,"\r\nRED: ");
	strcat(data,NVS->_LORA_NET_ID);
	strcat(data,"\r\nCRIPTO: ");
	strcat(data,NVS->_LORA_NCPIN);
	strcat(data,"\r\nBANDA: ");
	strcat(data,NVS->_LORA_BAND);
	strcat(data,"\r\n\r\nCONFIGRACION MODBus\r\n");
	strcat(data,"\r\nREGISTROS: ");
	strcat(data,NVS->_MBUS_REG);
	strcat(data,"\r\nID: ");
	strcat(data,NVS->_MBUS_ID);
	strcat(data,"\r\nCODIGO: ");
	strcat(data,NVS->_MBUS_CODE);
	strcat(data,"\r\nID SERVER: ");
	strcat(data,NVS->_MBUS_SRVR);
	ITM0_Write(data,strlen(data));
	if(SEND==1) HAL_UART_Transmit(PORTSER, data, strlen(data), 100);
	free(data);
}

uint8_t BKP_AP_EXTRACT(struct BKP_REG * NVS, char * a, int qty)
{
	char vect[32];
    int pos=0;

    //----------1 IP SERVER----------//
	while (*a!='=')
	{ *a++;}
	a++;
		pos=0;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_SERVER,vect);
	pos=0;
    //----------0 IP SERVER----------//
    //----------1 EP KEY----------//
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_EPKEY,vect);
	pos=0;
    //----------0 EP KEY----------//
    //----------1 ETH IP----------//
	while (*a!='=')
	{ *a++;}
	a++;
		pos=0;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_ETH_IP,vect);
	pos=0;
    //----------0 ETH IP----------//
    //----------1 ETH MASK----------//
	while (*a!='=')
	{ *a++;}
	a++;
		pos=0;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_ETH_MASK,vect);
	pos=0;
    //----------0 ETH MASK----------//
    //----------1 ETH PORT----------//
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_ETH_PORT,vect);
	pos=0;
    //----------0 ETH PORT----------//
    //----------1 WF SSID----------//
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_WIFI_SSID,vect);
	pos=0;
    //----------0 WF SSID----------//
    //----------1 WF PASS----------//
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_WIFI_PASS,vect);
	pos=0;
    //----------0 WF PASS----------//
    //----------1 WF IP----------//
	while (*a!='=')
	{ *a++;}
	a++;
		pos=0;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_WIFI_IP,vect);
	pos=0;
    //----------0 WF IP----------//
    //----------1 WF MASK----------//
	while (*a!='=')
	{ *a++;}
	a++;
		pos=0;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='.';
		pos++;
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_WIFI_MASK,vect);
	pos=0;
    //----------0 WF MASK----------//
    //----------1 WF PORT----------//
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_WIFI_PORT,vect);
	pos=0;
    //----------0 WF PORT----------//
    //----------1 LR ADDR----------//
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_LORA_ADDR,vect);
	pos=0;
    //----------0 LR ADDR----------//
    //----------1 LR NID----------//
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_LORA_NET_ID,vect);
	pos=0;
    //----------0 LR NID----------//
    //----------1 LR NCP----------//
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!='&');
		vect[pos]='\0';

	strcpy(NVS->_LORA_NCPIN,vect);
	pos=0;
    //----------0 LR NCP----------//
    //----------1 LR BAND----------//
	while (*a!='=')
	{ *a++;}
	a++;
		do
		{
			vect[pos]=*a++;
			pos++;
		}
		while(*a!=' ');
		vect[pos]='\0';

	strcpy(NVS->_LORA_BAND,vect);
	pos=0;
    //----------0 LR BAND----------//
}
