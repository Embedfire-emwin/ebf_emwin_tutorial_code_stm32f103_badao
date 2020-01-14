/**
  ******************************************************************************
  * @file    FSMC���ⲿSRAM
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   sramӦ������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-�Ե� STM32  ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include <stdio.h>

/* FATFS */
#include "ff.h"
#include "diskio.h"
#include "integer.h"
/* ������Ӳ��bspͷ�ļ� */
#include "./led/bsp_led.h"
#include "./usart/bsp_usart.h"
#include "./key/bsp_key.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./lcd/bsp_xpt2046_lcd.h"
#include "./flash/bsp_spi_flash.h"
#include "./sram/bsp_fsmc_sram.h"
#include "./TPad/bsp_tpad.h"
#include "./beep/bsp_beep.h" 
#include "./SysTick/bsp_SysTick.h"
/* STemWINͷ�ļ� */
#include "GUI.h"
#include "DIALOG.h"

FATFS   fs;			/* FatFs�ļ�ϵͳ���� */
FIL     file;		/* file objects */
UINT    bw;     /* File R/W count */
FRESULT result; 
FILINFO fno;
DIR dir;

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{
  /*CRC��emWinû�й�ϵ��ֻ������Ϊ�˿�ı��������ģ�����STemWin�Ŀ�ֻ������ST��оƬ���棬���оƬ���޷�ʹ�õġ� */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
  
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	
  
  /* ��ʼ����ʱ�� */
	SysTick_Init();
  
  /* ��������ʼ�� */
  Beep_Init();
	
  /* ������ʼ��	*/
  Key_GPIO_Config();
  
	/* ��ʼ������ */
	USART_Config();
	
	/* ���ڵ�����Ϣ */
	printf("emWin demo\r\n");
  
  /* SRAM��ʼ�� */
  FSMC_SRAM_Init();
  
  /* ��������ʼ�� */
  XPT2046_Init();
  
//  /* �����ļ�ϵͳ������ʱ���SD����ʼ�� */
//  result = f_mount(&fs,"0:",1);
//	if(result != FR_OK)
//	{
//		printf("SD����ʼ��ʧ�ܣ���ȷ��SD������ȷ���뿪���壬��һ��SD�����ԣ�\n");
//		while(1);
//	}
  
	/* ��ʼ��GUI */
	GUI_Init();
  
  while(1)
  {
    MainTask();
  }
}



/*********************************************END OF FILE**********************/
