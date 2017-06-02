/*******************************************************************************
Name		: JLX280-012-PC TFT module
Vendors		: www.jlxlcd.cn
Driver IC	: ILI9341
Author		: longcd
*******************************************************************************/
#ifndef _TFT_H
#define _TFT_H

void ILI9341_writeParam(u8 cmd, u8 *pParam, u16 size);
void ILI9341_readParam(u8 cmd, u8 *pParam, u16 size);
void ILI9341_init(void);


#endif

