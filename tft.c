/*******************************************************************************
Name		: JLX280-012-PC TFT module
Vendors		: www.jlxlcd.cn
Driver IC	: ILI9341
Author		: longcd
*******************************************************************************/


#define IM3IM2IM1IM0_0000
#ifdef IM3IM2IM1IM0_0000
	//8-bit 8080-I bus
	#define RES_high()		do{}while(0)
	#define RES_low()		do{}while(0)
	#define CS_high()		do{}while(0)
	#define CS_low()		do{}while(0)
	#define WR_high()		do{}while(0)
	#define WR_low()		do{}while(0)
	#define RD_high()		do{}while(0)
	#define RD_low()		do{}while(0)
	#define DC_high()		do{}while(0)
	#define DC_low()		do{}while(0)
	#define DATA_out(Data)	do{}while(0)
	#define SendData()		DC_high()
	#define SendCmd()		DC_low()
	#define DATA_HiZ()		do{}while(0)
	#define DATA_output()	do{}while(0)
	#define DATA_in()		()
#endif

#define timingDelay()


#define COLUMN_NUM		320U
#define	ROW_NUM			240U
/******************************************************************************/

void ILI9341_delay(u32 cnt)
{
	while(cnt--);
}

#ifdef IM3IM2IM1IM0_0000
void ILI9341_writeParam(u8 cmd, u8 *pParam, u16 size)
{
	DATA_output();
	CS_low();
	RD_high();
	DC_low();
	timingDelay();
	
	DATA_out(cmd);
	WR_low();
	timingDelay();
	WR_high();
	timingDelay();

	DC_high();
	for( ; size > 0; size--){
		DATA_out(*pParam++);
		WR_low();
		timingDelay();
		WR_high();
		timingDelay();
	}

	CS_high();
}

void ILI9341_readParam(u8 cmd, u8 *pParam, u16 size)
{
	DATA_output();
	CS_low();
	RD_high();
	DC_low();
	timingDelay();
	
	DATA_out(cmd);
	WR_low();
	timingDelay();
	WR_high();
	timingDelay();

	DATA_HiZ();
	DC_high();
	RD_low();
	timingDelay();	//first invalid data
	RD_high();
	timingDelay();
	for( ; size > 0; size--){
		RD_low();
		timingDelay();
	
		*pParam++ = DATA_in();
		RD_high();
		timingDelay();
	}

	CS_high();
}
#endif

void ILI9341_init(void)
{
	u8	param[8];

	RES_low();
	ILI9341_delay(50);
	RES_high();
	ILI9341_delay(50);

	param[0] = 0X00;	//fixed value
	param[1] = 0X99;	//power control
	param[2] = 0X30;	//ESD protection
	ILI9341_writeParam(0xCF, param, 3);

	param[0] = 0X64;	//soft start control
	param[1] = 0X03;	//power on sequence control
	param[2] = 0X12;	//power on sequence control
	param[3] = 0X81;	//DDVDH enhance mode
	ILI9341_writeParam(0xED, param, 4);

	param[0] = 0X85;	//gate driver non-overlap timing control
	param[1] = 0X00;	//EQ and CR timing control
	param[2] = 0X78;	//pre-charge timing control
	ILI9341_writeParam(0xE8, param, 3);

	param[0] = 0X39;	//fixed value
	param[1] = 0X2C;	//fixed value
	param[2] = 0X00;	//fixed value
	param[3] = 0X34;	//vcore = 1.6V
	param[4] = 0X02;	//DDVDH = 5.6V
	ILI9341_writeParam(0xCB, param, 5);

	param[0] = 0X20;	//DDVDH = 2xVCI
	ILI9341_writeParam(0xF7, param, 1);

	param[0] = 0X00;	//gate driver timing control
	param[1] = 0X00;	//fixed value
	ILI9341_writeParam(0xEA, param, 2);

	param[0] = 0X1B;	//GVDD = 4.2V
	ILI9341_writeParam(0xC0, param, 1);

	param[0] = 0X12;	//Select the optimal step-up factor for the operating voltage
	ILI9341_writeParam(0xC1, param, 1);

	param[0] = 0X32;	//VCOMH = 3.95V
	param[1] = 0X3C;	//VCOML = -1V
	ILI9341_writeParam(0xC5, param, 2);

	param[0] = 0X9D;	//Set the VCOM offset voltage
	ILI9341_writeParam(0xC7, param, 1);
	
	param[0] = 0X68;	//Set the VCOM offset voltage
	ILI9341_writeParam(0x36, param, 1);

}


void ILI9341_writeRAM_262K(u8 *pData,u16 size)
{
	ILI9341_writeParam(0X2C, pData, size);
}


