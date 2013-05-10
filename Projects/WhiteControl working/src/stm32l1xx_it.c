/**
  ******************************************************************************
  * @file    Project/STM32L1xx_StdPeriph_Template/stm32l1xx_it.c
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"
#include "main.h"


/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1);
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1);
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1);
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1);
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1);
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
 /* Go to infinite loop when Hard Fault exception occurs */
  while (1);
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
  while (1);
}



/**
  * @brief  This function handles SysTick interrupts.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	/* TS handler */
  	TSL_Timer_ISR();

    msTicks++;
	if((msTicks%10) ==0){
		gSystemFlags.ms10_flag =1;
		if((msTicks%50) == 0){
			gSystemFlags.ms50_flag = 1;
			
			if((msTicks%100) == 0){
				
				gSystemFlags.ms100_flag = 1;
				if((msTicks%200)==0)
					gSystemFlags.ms200_flag =1;
				if((msTicks%300) == 0)
					gSystemFlags.ms300_flag = 1;
				if((msTicks%500) == 0)
					gSystemFlags.ms500_flag = 1;


			}
		}
	}
	Buzzer_systickISR_timing_ms();
	
}



/**
  * @brief  TIMER 6 used for IR receiver decode, interupt every 50us
  * @param  None
  * @retval None
  */
void TIM6_IRQHandler(void)
{
	//TIME_DEBUG_SET(6);
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET){
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);



	}
	//TIME_DEBUG_RESET(6);

}



/**
  * @brief  This function handles TIM7 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM7_IRQHandler(void)
{
	Buzzer_timerISR_make_sound();
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
}

void EXTI0_IRQHandler(void)
{
  /* Disable general interrupts */
  //disableInterrupts();
  	  //RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
  //RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
  EXTI_ClearITPendingBit(EXTI_Line0);
  //enableInterrupts();
}


void RTC_WKUP_IRQHandler (void)
{


	//LED_ALL ^=1;
	//Buzzer_bip();
	PWR_RTCAccessCmd(ENABLE);
	RTC_ClearITPendingBit(RTC_IT_WUT);
	PWR_RTCAccessCmd(DISABLE);

	EXTI_ClearITPendingBit(EXTI_Line20);

}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_md.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
