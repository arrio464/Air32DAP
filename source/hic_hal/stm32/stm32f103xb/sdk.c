/**
 * @file    sdk.c
 * @brief
 *
 * DAPLink Interface Firmware
 * Copyright (c) 2017-2017, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stm32f1xx.h"
#include "air32f10x_rcc_ex.h"
#include "DAP_config.h"
#include "gpio.h"
#include "daplink.h"
#include "util.h"
#include "cortex_m.h"

TIM_HandleTypeDef timer;
uint32_t time_count;

static uint32_t tim2_clk_div(uint32_t apb1clkdiv);

//////////////////////////////////////////////////////////////////////////////////////////////

FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
  uint32_t tmp = 0;
  uint32_t statusreg = 0;
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_RCC_FLAG(RCC_FLAG));

  /* Get the RCC register index */
  tmp = RCC_FLAG >> 5;
  if (tmp == 1)               /* The flag to check is in CR register */
  {
    statusreg = RCC->CR;
  }
  else if (tmp == 2)          /* The flag to check is in BDCR register */
  {
    statusreg = RCC->BDCR;
  }
  else                       /* The flag to check is in CSR register */
  {
    statusreg = RCC->CSR;
  }

  /* Get the flag position */
  tmp = RCC_FLAG &  ((uint8_t)0x1F);
  if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the flag status */
  return bitstatus;
}

//////////////////////////////////////////////////////////////////////////////////////////////


/**
    * @brief  Switch the PLL source from HSI to HSE bypass, and select the PLL as SYSCLK
  *         source.
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE bypass)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV1                    = 1
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void sdk_init()
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

    SystemCoreClockUpdate();
    HAL_Init();

    /* Select HSI as system clock source to allow modification of the PLL configuration */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
        /* Initialization Error */
        util_assert(0);
    }

    /* Enable HSE bypass Oscillator, select it as PLL source and finally activate the PLL */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_CR_HSEON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        /* Initialization Error */
        util_assert(0);
    }

    /* Select the PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        /* Initialization Error */
        util_assert(0);
    }

//RCC_DeInit
    /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
  RCC->CFGR &= (uint32_t)0xF8FF0000;
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;

//RCC_HSEConfig
  /* Reset HSEON bit */
  RCC->CR &= ((uint32_t)0xFFFEFFFF);
  /* Reset HSEBYP bit */
  RCC->CR &= ((uint32_t)0xFFFBFFFF);
  /* Configure HSE (RCC_HSE_OFF is already covered by the code section above) */
    RCC->CR |= ((uint32_t)0x00010000);

    while (RCC_GetFlagStatus(((uint8_t)0x31)) == RESET);
    //RCC_PLLCmd(DISABLE);
    *(__IO uint32_t *) (PERIPH_BB_BASE + ((RCC_OFFSET + 0x00) * 32) + (PLLON_BitNumber * 4)) = (uint32_t)0;
    //AIR_RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_27, 1); //配置 PLL,8*27=216MHz
    AIR_RCC_PLLConfig(((uint32_t)0x00010000), ((uint32_t)0x10280000), 1);

    //RCC_PLLCmd(ENABLE); //使能 PLL
    *(__IO uint32_t *) (PERIPH_BB_BASE + ((RCC_OFFSET + 0x00) * 32) + (PLLON_BitNumber * 4)) = (uint32_t)1;
	while (RCC_GetFlagStatus(((uint8_t)0x39)) == RESET)
		; //等待 PLL 就绪
    
    //RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //选择 PLL 作为系统时钟
uint32_t tmpreg = 0;
  /* Check the parameters */
  tmpreg = RCC->CFGR;
  /* Clear SW[1:0] bits */
  tmpreg &= ((uint32_t)0xFFFFFFFC);
  /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
  tmpreg |= ((uint32_t)0x00000002);
  /* Store the new value */
  RCC->CFGR = tmpreg;

  //RCC_HCLKConfig(RCC_SYSCLK_Div1); //配置 AHB 时钟
  tmpreg = 0;
  tmpreg = RCC->CFGR;
  /* Clear HPRE[3:0] bits */
  tmpreg &= ((uint32_t)0xFFFFFF0F);
  /* Set HPRE[3:0] bits according to RCC_SYSCLK value */
  tmpreg |= ((uint32_t)0x00000000);
  /* Store the new value */
  RCC->CFGR = tmpreg;
  //RCC_PCLK1Config(RCC_HCLK_Div2);	 //配置 APB1 时钟
tmpreg = 0;
  tmpreg = RCC->CFGR;
  /* Clear PPRE1[2:0] bits */
  tmpreg &= ((uint32_t)0xFFFFF8FF);
  /* Set PPRE1[2:0] bits according to RCC_HCLK value */
  tmpreg |= ((uint32_t)0x00000400);
  /* Store the new value */
  RCC->CFGR = tmpreg;
  //RCC_PCLK2Config(RCC_HCLK_Div1);	 //配置 APB2 时钟
    tmpreg = 0;
  tmpreg = RCC->CFGR;
  /* Clear PPRE2[2:0] bits */
  tmpreg &= ((uint32_t)0xFFFFC7FF);
  /* Set PPRE2[2:0] bits according to RCC_HCLK value */
  tmpreg |= ((uint32_t)0x00000000) << 3;
  /* Store the new value */
  RCC->CFGR = tmpreg;

    //RCC_LSICmd(ENABLE); //使能内部低速时钟
    *(__IO uint32_t *) CSR_LSION_BB = (uint32_t)1;
	while (RCC_GetFlagStatus(((uint8_t)0x61)) == RESET)
		;				//等待 LSI 就绪
    *(__IO uint32_t *) CR_HSION_BB = (uint32_t)1;
	while (RCC_GetFlagStatus(((uint8_t)0x21)) == RESET)
		; //等待 HSI 就绪
}

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
    HAL_StatusTypeDef ret;
    RCC_ClkInitTypeDef clk_init;
    uint32_t unused;
    uint32_t prescaler;
    uint32_t source_clock;

    HAL_RCC_GetClockConfig(&clk_init, &unused);

    /* Compute the prescaler value to have TIMx counter clock equal to 4000 Hz */
    source_clock = SystemCoreClock / tim2_clk_div(clk_init.APB1CLKDivider);
    prescaler = (uint32_t)(source_clock / 4000) - 1;

    /* Set TIMx instance */
    timer.Instance = TIM2;

    timer.Init.Period            = 0xFFFF;
    timer.Init.Prescaler         = prescaler;
    timer.Init.ClockDivision     = 0;
    timer.Init.CounterMode       = TIM_COUNTERMODE_UP;
    timer.Init.RepetitionCounter = 0;

    __HAL_RCC_TIM2_CLK_ENABLE();

    ret = HAL_TIM_Base_DeInit(&timer);
    if (ret != HAL_OK) {
        return ret;
    }

    time_count = 0;
    ret = HAL_TIM_Base_Init(&timer);
    if (ret != HAL_OK) {
        return ret;
    }

    ret = HAL_TIM_Base_Start(&timer);
    if (ret != HAL_OK) {
        return ret;
    }

    return HAL_OK;
}


void HAL_IncTick(void)
{
    // Do nothing
}

uint32_t HAL_GetTick(void)
{
    cortex_int_state_t state;
    state = cortex_int_get_and_disable();
    const uint32_t ticks = __HAL_TIM_GET_COUNTER(&timer) / 4;
    time_count += (ticks - time_count) & 0x3FFF;
    cortex_int_restore(state);
    return time_count;
}

void HAL_SuspendTick(void)
{
    HAL_TIM_Base_Start(&timer);
}

void HAL_ResumeTick(void)
{
    HAL_TIM_Base_Stop(&timer);
}

static uint32_t tim2_clk_div(uint32_t apb1clkdiv)
{
    switch (apb1clkdiv) {
        case RCC_CFGR_PPRE1_DIV2:
            return 1;
        case RCC_CFGR_PPRE1_DIV4:
            return 2;
        case RCC_CFGR_PPRE1_DIV8:
            return 4;
        case RCC_CFGR_PPRE1_DIV16:
            return 8;
        default:
            return 1;
    }
}
