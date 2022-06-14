    /*!
    *   --------------------------------------------------------------------------
    *                       ///RCC initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 20/01/2022 - last update version RCC
    *
    *       @note This file for configuration main functional properties of reset clock configuration
    */
#pragma once

#if (_DefaultSectorIncludeHandler != 0)
    //DMA
    #define set_dma1        (* (uint32_t *)(RCC_BASE + 0x30) |= (1 << 21))
    #define set_dma2        (* (uint32_t *)(RCC_BASE + 0x30) |= (1 << 22))
    //TIM
    #define set_tim1        (* (uint32_t *)(RCC_BASE + 0x44) |= 1)
    #define set_tim2        (* (uint32_t *)(RCC_BASE + 0x40) |= 1)
    #define set_tim3        (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 1))
    #define set_tim4        (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 2))
    #define set_tim5        (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 3))
    #define set_tim6        (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 4))
    #define set_tim7        (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 5))
    #define set_tim8        (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 1))
    #define set_tim9        (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 16))
    #define set_tim10       (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 17))
    #define set_tim11       (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 18))
    #define set_tim12       (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 6))
    #define set_tim13       (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 7))
    #define set_tim14       (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 8))
    //GPIO
    #define set_gpioa       (* (uint32_t *)(RCC_BASE + 0x30) |= 1)
    #define set_gpiob       (* (uint32_t *)(RCC_BASE + 0x30) |= (1 << 1))
    #define set_gpioc       (* (uint32_t *)(RCC_BASE + 0x30) |= (1 << 2))
    #define set_gpiod       (* (uint32_t *)(RCC_BASE + 0x30) |= (1 << 3))
    #define set_gpioe       (* (uint32_t *)(RCC_BASE + 0x30) |= (1 << 4))
    #define set_gpiof       (* (uint32_t *)(RCC_BASE + 0x30) |= (1 << 5))
    #define set_gpiog       (* (uint32_t *)(RCC_BASE + 0x30) |= (1 << 6))
    #define set_gpioh       (* (uint32_t *)(RCC_BASE + 0x30) |= (1 << 7))
    #define set_gpioi       (* (uint32_t *)(RCC_BASE + 0x30) |= (1 << 8))
    #define set_gpioj       (* (uint32_t *)(RCC_BASE + 0x30) |= (1 << 9))
    #define set_gpiok       (* (uint32_t *)(RCC_BASE + 0x30) |= (1 << 10))
    //USART
    #define set_usart1      (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 4))
    #define set_usart2      (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 17))
    #define set_usart3      (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 18))
    #define set_usart4      (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 19))
    #define set_usart5      (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 20))
    #define set_usart6      (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 5))
    #define set_usart7      (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 30))
    #define set_usart8      (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 31))
    //I2C
    #define set_i2c1        (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 21))
    #define set_i2c2        (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 22))
    #define set_i2c3        (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 23))
    //ADC
    #define set_adc1        (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 8))
    #define set_adc2        (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 9))
    #define set_adc3        (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 10))
    //DAC
    #define set_dac         (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 29))
    //CAN
    #define set_can1        (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 25))
    #define set_can2        (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 26))
    //PWR
    #define set_pwr         (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 28))
    //SPI
    #define set_spi1        (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 12))
    #define set_spi2        (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 14))
    #define set_spi3        (* (uint32_t *)(RCC_BASE + 0x40) |= (1 << 15))
    #define set_spi4        (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 13))
    #define set_spi5        (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 20))
    #define set_spi6        (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 21))
    //SDIO
    #define set_sdio        (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 11))
    //SYSCFG
    #define set_syscfg      (* (uint32_t *)(RCC_BASE + 0x44) |= (1 << 14))

    /*!
     *   @brief get_{name} - get clock part of the periphery
     *
     *       @value name - the part name of the periphery
     */
    #define get_sws     ((uint32_t)((*((uint32_t *)((RCC_BASE) + 0x08)))& RCC_CFGR_SWS))
    #define get_pllsrc  ((uint32_t)(((*((uint32_t *)((RCC_BASE) + 0x04)))&(RCC_PLLCFGR_PLLSRC)) >> 22))
    #define get_pllm    ((uint32_t)((*((uint32_t *)((RCC_BASE) + 0x04)))&(RCC_PLLCFGR_PLLM)))
    #define get_plln    ((uint32_t)(((*((uint32_t *)((RCC_BASE) + 0x04)))&(RCC_PLLCFGR_PLLN)) >> 6))
    #define get_pllp    ((uint32_t)(((((*((uint32_t *)((RCC_BASE) + 0x04)))&(RCC_PLLCFGR_PLLP)) >> 16) + 1) * 2))
    #define get_hpre    ((uint32_t)(((*((uint32_t *)((RCC_BASE) + 0x08)))&(RCC_CFGR_HPRE)) >> 4))
    #define get_ppre1   ((uint8_t)(((*((uint32_t *)((RCC_BASE) + 0x08)))&(RCC_CFGR_PPRE1)) >> 10))
    #define get_ppre2   ((uint8_t)(((*((uint32_t *)((RCC_BASE) + 0x08)))&(RCC_CFGR_PPRE2)) >> 13))

    #if (_AdvancedCalculatingRCC == 1)
        __attribute__((unused)) static uint8_t prescaler_table[16] =   {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
            /*!
             *   @brief current_systick - get system clock frequency
             *
             *   @brief current_AHB - get AHB bus frequency
             *
             *   @brief current_APB1 - get APB1 bus frequency
             *
             *   @brief current_APB2 - get APB2 bus frequency
             */
        #define calc_pllvco         ((((HSE_VALUE*get_pllsrc) + (HSI_VALUE*(!get_pllsrc))) / get_pllm) * (get_plln))
        #define current_Systick     (((calc_pllvco / get_pllp)*((get_sws)>>3)) + (HSI_VALUE*(((get_sws)>>2)&0x1) ) + (HSE_VALUE*(!((get_sws >> 3)|(get_sws >> 2))) ))
        #define current_AHB         current_Systick >> prescaler_table[get_hpre]
        #define current_APB1        (uint32_t)(current_AHB >> prescaler_table[get_ppre1])
        #define current_APB2        current_AHB >> prescaler_table[get_ppre2]
    #endif /*_AdvancedCalculatingRCC*/
#endif /*_DefaultSectorIncludeHandler */
