/**
  ******************************************************************************
  * @file    Project/STM32L1xx_StdPeriph_Template/main.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    13-September-2011
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"
#include "GTSV_RTC.h"
#include "GTSV_LCD.h"
#include "buzzer.h"
#include "GTSV_TSense.h"
#include <stdio.h>

/* Exported types ------------------------------------------------------------*/
struct SystemConfig {
	uint8_t sys_clk_src; //0x00: MSI | 0x04:HSI | 0x08:HSE | 0x0C: PLL --> used as sysclk source
	RCC_ClocksTypeDef RCC_Clk;
	unsigned RCC_FLAG_HSIRDY1:1;
	unsigned RCC_FLAG_MSIRDY1:1;
	unsigned RCC_FLAG_HSERDY1:1;
	unsigned RCC_FLAG_PLLRDY1:1;
	unsigned RCC_FLAG_LSERDY1:1;
	unsigned RCC_FLAG_LSIRDY1:1; //LSI oscillator clock ready
    unsigned RCC_FLAG_OBLRST1:1;  // Option Byte Loader (OBL) reset 
	unsigned RCC_FLAG_PINRST1:1;// Pin reset
	unsigned RCC_FLAG_PORRST1:1;// POR/PDR reset
	unsigned RCC_FLAG_SFTRST1:1;// Software reset
	unsigned RCC_FLAG_IWDGRST1:1;// Independent Watchdog reset
	unsigned RCC_FLAG_WWDGRST1:1;// Window Watchdog reset
	unsigned RCC_FLAG_LPWRRST1:1;// Low Power reset

};


//can toggle light on/off in every state by light button.
enum System_state_enum_t {
	SYS_STATE_INITIAL,
	SYS_STATE_OFF, //can change state to: blowing (PW), DTime_Adj(minus), clear C R time 
	SYS_STATE_BLOWING,  //change system default blowing speed. Change to APO state(hold PW) change to off state(PW)
	SYS_STATE_APO_BLOWING,//change Sys_def_blowing_spd. change to off state
	SYS_STATE_APO_DTIME_ADJ  //change sys_def_APO_DTIME. change to offstate(3s or pw)
	
};

struct SystemFlags {
	unsigned ms10_flag:1;
	unsigned ms50_flag:1;
	unsigned ms100_flag:1;
	unsigned ms200_flag:1;
	unsigned ms500_flag:1;
	unsigned ms300_flag:1;
	unsigned fanRotate:2;

	unsigned light_state:1;
	unsigned led_backlight:1;
	unsigned time_adj_stage:1;
	uint8_t  time_adj_delay;
	uint8_t  tmp_hour;
	uint8_t  tmp_min;
	uint8_t  blower_apo_mins_tmp;
	uint8_t  blower_apo_mins;
	uint8_t  blower_fan_speed;
	enum System_state_enum_t sys_state;
	RTC_TimeTypeDef blower_apo_begin;
	RTC_TimeTypeDef blower_apo_end;
	
	
};


extern uint16_t msTicks;
extern struct SystemFlags gSystemFlags;


/* Exported constants --------------------------------------------------------*/
#define DEBUG

/* Exported macro ------------------------------------------------------------*/

#ifndef BITBAND_PERI
#define BITBAND_PERI(a,b) ((PERIPH_BB_BASE + (a-PERIPH_BASE)*32 + (b*4)))
#endif
#ifndef BITBAND_SRAM
#define BITBAND_SRAM(a,b) ((PERIPH_BB_BASE + (a-PERIPH_BASE)*32 + (b*4)))
#endif


#define BITBAND_POINTER_AT(a,b)\
			*((volatile unsigned char *)(BITBAND_PERI(a,b)))



//this is for toggle pin
#ifndef ODR_REG_OFFSET
#define ODR_REG_OFFSET		0x14
#endif
#ifndef BSRRL_REG_OFFSET	
#define BSRRL_REG_OFFSET		0x18
#endif
#ifndef BSRRH_REG_OFFSET	
#define BSRRH_REG_OFFSET		0x1A
#endif

#define LED_ALL	BITBAND_POINTER_AT(GPIOA_BASE + ODR_REG_OFFSET, 11)
#define LED_ALL_ON	BITBAND_POINTER_AT(GPIOA_BASE + BSRRL_REG_OFFSET, 11) = 1
#define LED_ALL_OFF BITBAND_POINTER_AT(GPIOA_BASE + BSRRH_REG_OFFSET, 11) = 1

#define LED_LIGHT_BT	BITBAND_POINTER_AT(GPIOB_BASE + ODR_REG_OFFSET, 13)
#define LED_LIGHT_BT_ON	BITBAND_POINTER_AT(GPIOB_BASE + BSRRL_REG_OFFSET, 13)=1
#define LED_LIGHT_BT_OFF BITBAND_POINTER_AT(GPIOB_BASE + BSRRH_REG_OFFSET, 13)=1

#define LED_TIMER_BT	BITBAND_POINTER_AT(GPIOB_BASE + ODR_REG_OFFSET, 14)
#define LED_PLUS_BT		BITBAND_POINTER_AT(GPIOA_BASE + ODR_REG_OFFSET, 2)
#define LED_MINUS_BT	BITBAND_POINTER_AT(GPIOA_BASE + ODR_REG_OFFSET, 4)
#define LED_AUTO_BT		BITBAND_POINTER_AT(GPIOA_BASE + ODR_REG_OFFSET, 1)

#define MAIN_LAMP		BITBAND_POINTER_AT(GPIOB_BASE + ODR_REG_OFFSET, 7)
#define MAIN_LAMP_ON	BITBAND_POINTER_AT(GPIOB_BASE + BSRRL_REG_OFFSET, 7) = 1
#define MAIN_LAMP_OFF	BITBAND_POINTER_AT(GPIOB_BASE + BSRRH_REG_OFFSET, 7) = 1

#define BLOWER_FAN1		BITBAND_POINTER_AT(GPIOC_BASE + ODR_REG_OFFSET, 2)
#define BLOWER_FAN2		BITBAND_POINTER_AT(GPIOC_BASE + ODR_REG_OFFSET, 3)
#define BLOWER_FAN3		BITBAND_POINTER_AT(GPIOC_BASE + ODR_REG_OFFSET, 1)
#define BLOWER_FAN4		BITBAND_POINTER_AT(GPIOC_BASE + ODR_REG_OFFSET, 0)






/* Exported functions ------------------------------------------------------- */

//void TimingDelay_Decrement(void);
//void Delay(__IO uint32_t nTime);


void Cpu_to_default_config(void);
void Get_system_clk_config(void);
void Ports_to_default_config(void);
void Timers_to_default_config(void);



#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/