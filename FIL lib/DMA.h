
#pragma once
#include <FilConfig.h>

    /*!
    *   @author Caska
    *   @date 25/01/2022 - last update version DMA
    */
                                        //////////////////////////
                                        ///DMA1 request mapping///
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //            | Stream 0    | Stream 1  | Stream 2    | Stream 3    | Stream 4    | Stream 5    | Stream 6  | Stream 7 |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 0 | SPI3_RX     |     -     | SPI3_RX     | SPI2_RX     | SPI2_TX     | SPI3_TX     |     -     | SPI3_TX  |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 1 | I2C1_RX     |     -     | TIM7_UP     |     -       | TIM7_UP     | I2C1_RX     | I2C1_TX   | I2C1_TX  |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 2 | TIM4_CH1    |     -     | I2S3_EXT_RX | TIM4_CH2    | I2S3_EXT_TX | I2S3_EXT_TX | TIM4_UP   | TIM4_CH3 |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 3 | I2S3_EXT_RX | TIM2_UP   | I2C3_RX     | I2S2_EXT_RX | I2C3_TX     | TIM2_CH1    | TIM2_CH2  | TIM2_UP  |//
    //            |             | TIM2_CH3  |             |             |             |             | TIM2_CH4  | TIM2_CH4 |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 4 | UART5_RX    | USART3_RX | UART4_RX    | USART3_TX   | UART4_TX    | USART2_RX   | USART2_TX | UART5_TX |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 5 |      -      |     -     | TIM3_CH4    |     -       | TIM3_CH1    | TIM3_CH2    |     -     | TIM3_CH3 |//
    //            |             |           | TIM3_UP     |             | TIM3_TRIG   |             |           |          |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 6 | TIM5_CH3    | TIM5_CH4  | TIM5_CH1    | TIM5_CH4    | TIM5_CH2    |     -       | TIM5_UP   |    -     |//
    //            | TIM5_UP     | TIM5_TRIG |             | TIM5_TRIG   |             |             |           |          |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 7 |      -      | TIM6_UP   | I2C2_RX     | I2C2_RX     | USART3_TX   | DAC1        | DAC2      | I2C2_TX  |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                        //////////////////////////
                                        ///DMA2 request mapping///
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //            | Stream 0    | Stream 1  | Stream 2    | Stream 3    | Stream 4    | Stream 5    | Stream 6  | Stream 7 |//
    // -----------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 0 | ADC1        |           | TIM8_CH1    |             | ADC1        |             | TIM1_CH1  |          |//
    //            |             |     -     | TIM8_CH2    |      -      |             |      -      | TIM1_CH2  |    -     |//
    //            |             |           | TIM8_CH3    |             |             |             | TIM1_CH3  |          |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 1 |      -      | DCMI      | ADC2        | ADC2        |      -      |      -      |     -     | DCMI     |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 2 | ADC3        | ADC3      |      -      |      -      |      -      | CRYP_OUT    | CRYP_IN   | HASH_IN  |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 3 | SPI1_RX     |     -     | SPI1_RX     | SPI1_TX     |      -      | SPI1_TX     |     -     |    -     |//
    //            |             |           |             |             |             |             |           |          |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 4 |      -      |     -     | USART1_RX   | SDIO        |      -      | USART1_RX   | SDIO      | USART1_TX|//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 5 |      -      | USART6_RX | USART6_RX   |     -       |      -      |      -      | USART6_TX | USART6_TX|//
    //            |             |           |             |             |             |             |           |          |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 6 | TIM1_TRIG   | TIM1_CH1  | TIM1_CH2    | TIM1_CH1    | TIM1_CH4    | TIM1_UP     | TIM1_CH3  |          |//
    //            |             |           |             |             | TIM1_TRIG   |             |           |    -     |//
    //            |             |           |             |             | TIM1_COM    |             |           |          |//
    //            |             |           |             |             |             |             |           |          |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //  Channel 7 |             | TIM8_UP   | TIM8_CH1    | TIM8_CH2    | TIM8_CH3    |             |           | TIM8_CH4 |//
    //            |      -      |           |             |             |             |      -      |     -     | TIM8_TRIG|//
    //            |             |           |             |             |             |             |           | TIM8_COM |//
    //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    #define dma1 1
    #define dma2 2

    #define DMA_init(dma,event,ndtr,priority,view,address_1,address_2,mpsize)   {      \
                    set_dma_selection(dma,event);                               \
                    conf_dma_par(dma,event,((uint32_t)address_1));              \
                    conf_dma_m0a(dma,event,((uint32_t)address_2));              \
                    conf_dma_dir(dma,event,view);                               \
                    clear_dma_pinc(dma,event);                                  \
                    conf_dma_minc(dma,event,0x1);                               \
                    conf_dma_circ(dma,event,0x1);                               \
                    conf_dma_psize(dma,event,mpsize);                             \
                    conf_dma_msize(dma,event,mpsize);                             \
                    conf_dma_pl(dma,event,0x3);                                 \
                    conf_dma_tcie(dma,event,0x1);                               \
                    conf_dma_ndtr(dma2,ADC_1,(ndtr+1));                         \
                    set_dma_en(dma,event,0x1);                                  }
        /*!
        *   @brief DMA_ADC_init(event,periph_addr,memory_addr) - special Developer function configuration ADC with DMA controller
        *       @value event - special name for Developer(see around of DMA table)
        *       @value periph_addr - target address where getting values
        *       @value receiver_addr - address where values comes
        *           @note Before used this, initialize ADC and sets necessary channels
        */
        #define DMA_ADC_init(event,ndtr,target_addr,receiver_addr)     DMA_init(dma2,event,ndtr,0x3,0x0,target_addr,receiver_addr,0x1)

    // base address in peripheral memory map
    #define dma_base        ((uint32_t)(PERIPH_BASE + 0x00026000))
    #define dma_id(dma)    ((uint32_t)(dma_base + (((dma&0x2) >> 1 ) * ((uint32_t)0x400))))

    // stream address in memory map
    #define default_s 1
    #define fifo_s 2

        /*!
        *   @note Access to events list
        */
        //Timers
        #define TIM1_ch1        0xE
        #define TIM1_ch2        0x30
        #define TIM1_ch3        0x30
        #define TIM1_ch4        0x30
        #define TIM1_trig       0x26
        #define TIM1_up         0x2E
        #define TIM1_com        0x26
        #define TIM2_ch1        0x2B
        #define TIM2_ch2        0x33
        #define TIM2_ch3        0xB
        #define TIM2_ch4        0x33
        #define TIM2_up         0xB
        #define TIM3_ch1        0x25
        #define TIM3_ch2        0x2D
        #define TIM3_ch3        0x3D
        #define TIM3_ch4        0x15
        #define TIM3_trig       0x25
        #define TIM3_up         0x15
        #define TIM4_ch1        0x2
        #define TIM4_ch2        0x1A
        #define TIM4_ch3        0x3A
        #define TIM4_up         0x32
        #define TIM5_ch1        0x16
        #define TIM5_ch2        0x26
        #define tim5_ch3        0x6
        #define TIM5_ch4        0xE
        #define TIM5_trig       0xE
        #define TIM5_up         0x6
        #define TIM6_up         0xF
        #define TIM7_up         0x21
        #define TIM8_ch1        0x10
        #define TIM8_ch2        0x10
        #define TIM8_ch3        0x10
        #define TIM8_ch4        0x3F
        #define TIM8_trig       0x3F
        #define TIM8_up         0xF
        #define TIM8_com        0x3F

        //SPI
        #define SPI1_rx         0x13
        #define SPI1_tx         0x1B
        #define SPI2_rx         0x18
        #define SPI2_tx         0x20
        #define SPI3_rx         0x10
        #define SPI3_tx         0x28

        //ADC
        #define ADC_1           0x0
        #define ADC_2           0x19
        #define ADC_3           0x2

        //DAC
        #define dac1            0x2F
        #define dac2            0x37

        //SDIO
        #define sdio            0x1C

        //DCMI
        #define dcmi            0x39

        //CRYP
        #define cryp_in         0x2A
        #define cryp_out        0x32

        //HASH
        #define hash_in         0x3A

        //USART/UART
        #define usart1_rx       0x14
        #define usart1_tx       0x3C
        #define usart2_rx       0x2C
        #define usart2_tx       0x34
        #define usart3_rx       0xC
        #define usart3_tx       0x1C
        #define uart4_rx        0x14
        #define uart4_tx        0x24
        #define uart5_rx        0x4
        #define uart5_tx        0x3C
        #define usart6_rx       0x15
        #define usart6_tx       0x3D

        //I2C
        #define i2c1_rx         0x1
        #define i2c1_tx         0x39
        #define i2c2_rx         0x17
        #define i2c2_tx         0x3F
        #define i2c3_rx         0x13
        #define i2c3_tx         0x23

        //I2S
        #define i2s2_rx         0x1B
        #define i2s3_rx         0x12
        #define i2s3_tx         0x22

    // calculating stream and channel from event
    #define check_stream(various,event)    ( (uint32_t)(( (various&0x1)*( 0x18 * ( (event&0x38) >> 3) ) ) + (((various&0x2)>>1)*(0x24 * ((event&0x38) >> 3)))) )
    #define parse_channel(event)           (event&0x7)

    // register's addresses
    #define dma_selection(chsel)    ((uint32_t)((chsel) << 25 ))
    #define dma_mburst(mburst)      ((uint32_t)((mburst) << 23 ))
    #define dma_pburst(pburst)      ((uint32_t)((pburst) << 21 ))
    #define dma_ct(ct)              ((uint32_t)((ct) << 19 ))
    #define dma_dbm(dbm)            ((uint32_t)((dbm) << 18 ))
    #define dma_pl(pl)              ((uint32_t)((pl) << 16))
    #define dma_pincos(pincos)      ((uint32_t)((pincos) << 15))
    #define dma_msize(msize)        ((uint32_t)((msize) << 13))
    #define dma_psize(psize)        ((uint32_t)((psize) << 11))
    #define dma_minc(minc)          ((uint32_t)((minc) << 10))
    #define dma_pinc(pinc)          ((uint32_t)((pinc) << 9))
    #define dma_circ(circ)          ((uint32_t)((circ) << 8))
    #define dma_dir(dir)            ((uint32_t)((dir) << 6))
    #define dma_pfctrl(pfctrl)      ((uint32_t)((pfctrl) << 5))
    #define dma_tcie(tcie)          ((uint32_t)((tcie) << 4))
    #define dma_htie(htie)          ((uint32_t)((htie) << 3))
    #define dma_teie(teie)          ((uint32_t)((teie) << 2))
    #define dma_dmeie(dmeie)        ((uint32_t)((dmeie) << 1))
    #define dma_en(en)              ((uint32_t)(en))
    #define dma_ndtr(ndtr)          ((uint16_t)(ndtr))
    #define dma_par(par)            ((uint32_t)(par))
    #define dma_m0a(m0a)            ((uint32_t)(m0a))
    #define dma_m1a(m1a)            ((uint32_t)(m1a))
    #define dma_feie(feie)          ((uint32_t)((feie) << 7))
    #define dma_fs(fs)              ((uint32_t)((fs) << 3))
    #define dma_dmdis(dmdis)        ((uint32_t)((dmdis) << 2))
    #define dma_fth(fth)            ((uint32_t)(fth))


    // set registers in active level
    #define set_dma_selection(dma,event)                      (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_selection(parse_channel(event)))
    #define set_dma_mburst(dma,event,mburst)                  (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_mburst(mburst))
    #define set_dma_pburst(dma,event,pburst)                  (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_pburst(pburst))
    #define set_dma_ct(dma,event,ct)                          (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_ct(ct))
    #define set_dma_dbm(dma,event,dbm)                        (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_dbm(dbm))
    #define set_dma_pl(dma,event,pl)                          (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_pl(pl))
    #define set_dma_pincos(dma,event,pincos)                  (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_pincos(pincos))
    #define set_dma_msize(dma,event,msize)                    (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_msize(msize))
    #define set_dma_psize(dma,event,psize)                    (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_psize(psize))
    #define set_dma_minc(dma,event,minc)                      (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_minc(minc))
    #define set_dma_pinc(dma,event,pinc)                      (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_pinc(pinc))
    #define set_dma_circ(dma,event,circ)                      (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_circ(circ))
    #define set_dma_dir(dma,event,dir)                        (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_dir(dir)))
    #define set_dma_pfctrl(dma,event,pfctrl)                  (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_pfctrl(pfctrl))
    #define set_dma_tcie(dma,event,tcie)                      (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_tcie(tcie))
    #define set_dma_htie(dma,event,htie)                      (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_htie(htie))
    #define set_dma_teie(dma,event,teie)                      (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_teie(teie))
    #define set_dma_dmeie(dma,event,dmeie)                    (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_dmeie(dmeie))
    #define set_dma_en(dma,event,en)                          (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) |= dma_en(en))
    #define set_dma_ndtr(dma,event,ndtr)                      (* (uint32_t *)((dma_id(dma)) + (0x14 + check_stream(default_s,event))) |= dma_ndtr(ndtr))
    #define set_dma_par(dma,event,par)                        (* (uint32_t *)((dma_id(dma)) + (0x18 + check_stream(default_s,event))) |= dma_par(par))
    #define set_dma_m0a(dma,event,m0a)                        (* (uint32_t *)((dma_id(dma)) + (0x1C + check_stream(default_s,event))) |= dma_m0a(m0a))
    #define set_dma_m1a(dma,event,m1a)                        (* (uint32_t *)((dma_id(dma)) + (0x20 + check_stream(default_s,event))) |= dma_m1a(m1a))
    #define set_dma_feie(dma,event,feie)                      (* (uint32_t *)((dma_id(dma)) + (0x24 + check_stream(fifo_s,event))) |= dma_feie(feie))
    #define set_dma_fs(dma,event,fs)                          (* (uint32_t *)((dma_id(dma)) + (0x24 + check_stream(fifo_s,event))) |= dma_fs(fs))
    #define set_dma_dmdis(dma,event,dmdis)                    (* (uint32_t *)((dma_id(dma)) + (0x24 + check_stream(fifo_s,event))) |= dma_dmdis(dmdis))
    #define set_dma_fth(dma,event,fth)                        (* (uint32_t *)((dma_id(dma)) + (0x24 + check_stream(fifo_s,event))) |= dma_fth(fth))

    // clear registers
    #define clear_dma_selection(dma,event)                      (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_selection(0x7)))
    #define clear_dma_mburst(dma,event)                         (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_mburst(0x3)))
    #define clear_dma_pburst(dma,event)                         (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_pburst(0x3)))
    #define clear_dma_ct(dma,event)                             (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_ct(0x1)))
    #define clear_dma_dbm(dma,event)                            (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_dbm(0x1)))
    #define clear_dma_pl(dma,event)                             (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_pl(0x3)))
    #define clear_dma_pincos(dma,event)                         (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_pincos(0x1)))
    #define clear_dma_msize(dma,event)                          (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_msize(0x3)))
    #define clear_dma_psize(dma,event)                          (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_psize(0x3)))
    #define clear_dma_minc(dma,event)                           (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_minc(0x1)))
    #define clear_dma_pinc(dma,event)                           (* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_pinc(0x1)))
    #define clear_dma_circ(dma,event)                           (* (uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_circ(0x1))
    #define clear_dma_dir(dma,event)                            (* (uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_dir(0x3))
    #define clear_dma_pfctrl(dma,event)                         (* (uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_pfctrl(0x1))
    #define clear_dma_tcie(dma,event)                           (* (uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_tcie(0x1))
    #define clear_dma_htie(dma,event)                           (* (uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_htie(0x1))
    #define clear_dma_teie(dma,event)                           (* (uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_teie(0x1))
    #define clear_dma_dmeie(dma,event)                          (* (uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_dmeie(0x1))
    #define clear_dma_en(dma,event)                             (* (uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event))) &= (~dma_en(0x1))
    #define clear_dma_ndtr(dma,ndtr)                            (* (uint32_t *)(dma_id(dma)) + (0x14 + check_stream(default_s,event))) &= (~dma_ndtr(0xFFFF))
    #define clear_dma_par(dma,event)                            (* (uint32_t *)(dma_id(dma)) + (0x18 + check_stream(default_s,event))) &= (~dma_par(0xFFFFFFFF))
    #define clear_dma_m0a(dma,event)                            (* (uint32_t *)(dma_id(dma)) + (0x1C + check_stream(default_s,event))) &= (~dma_m0a(0xFFFFFFFF))
    #define clear_dma_m1a(dma,event)                            (* (uint32_t *)(dma_id(dma)) + (0x20 + check_stream(default_s,event))) &= (~dma_m1a(0xFFFFFFFF))
    #define clear_dma_feie(dma,event)                           (* (uint32_t *)(dma_id(dma)) + (0x24 + check_stream(fifo_s,event))) &= (~dma_feie(0x1))
    #define clear_dma_fs(dma,event)                             (* (uint32_t *)(dma_id(dma)) + (0x24 + check_stream(fifo_s,event))) &= (~dma_fs(0x5))
    #define clear_dma_dmdis(dma,event)                          (* (uint32_t *)(dma_id(dma)) + (0x24 + check_stream(fifo_s,event))) &= (~dma_dmdis(0x1))
    #define clear_dma_fth(dma,event)                            (* (uint32_t *)(dma_id(dma)) + (0x24 + check_stream(fifo_s,event))) &= (~dma_fth(0x2))

    // clear and set in active level registers
    #define conf_dma_selection(dma,event)          {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_selection(0x7)))|dma_selection(parse_channel(event)));}

    #define conf_dma_mburst(dma,event,mburst)      {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_mburst(0x3)))|dma_mburst(mburst));}

    #define conf_dma_pburst(dma,event,pburst)      {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_pburst(0x3)))|dma_pburst(pburst));}

    #define conf_dma_ct(dma,event,ct)              {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_ct(0x1)))|dma_ct(ct));}

    #define conf_dma_dbm(dma,event,dbm)            {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event)))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_dbm(0x1)))|dma_dbm(dbm));}

    #define conf_dma_pl(dma,event,pl)              {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_pl(0x3)))|dma_pl(pl));}

    #define conf_dma_pincos(dma,event,pincos)      {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_pincos(0x1)))|dma_pincos(pincos));}

    #define conf_dma_msize(dma,event,msize)        {* ((uint32_t *)(dma_id(dma) + (0x10) + (check_stream(default_s,event)))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_msize(0x3)))|dma_msize(msize));}

    #define conf_dma_psize(dma,event,psize)        {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_psize(0x3)))|dma_psize(psize));}

    #define conf_dma_minc(dma,event,minc)          {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_minc(0x1)))|dma_minc(minc));}

    #define conf_dma_pinc(dma,event,pinc)          {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_pinc(0x1)))|dma_pinc(pinc));}

    #define conf_dma_circ(dma,event,circ)          {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_circ(0x1)))|dma_circ(circ));}

    #define conf_dma_dir(dma,event,dir)            {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_dir(0x3)))|dma_dir(dir));}

    #define conf_dma_pfctrl(dma,event,pfctrl)      {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_pfctrl(0x1)))|dma_pfctrl(pfctrl));}

    #define conf_dma_tcie(dma,event,tcie)          {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_tcie(0x1)))|dma_tcie(tcie));}

    #define conf_dma_htie(dma,event,htie)          {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_htie(0x1)))|dma_htie(htie));}

    #define conf_dma_teie(dma,event,teie)          {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_teie(0x1)))|dma_teie(teie));}

    #define conf_dma_dmeie(dma,event,dmeie)        {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_dmeie(0x1)))|dma_dmeie(dmeie));}

    #define conf_dma_en(dma,event,en)              {* (uint32_t *)((dma_id(dma)) + (0x10 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x10 + check_stream(default_s,event)))&(~dma_en(0x1)))|dma_en(en));}

    #define conf_dma_ndtr(dma,event,ndtr)          {* (uint32_t *)((dma_id(dma)) + (0x14 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x14 + check_stream(default_s,event)))&(~dma_ndtr(0xFFFF)))|dma_ndtr(ndtr));}

    #define conf_dma_par(dma,event,par)            {* (uint32_t *)((dma_id(dma)) + (0x18 + check_stream(default_s,event))) = \
                                                    ((* (uint32_t *)((dma_id(dma)) + (0x18 + check_stream(default_s,event)))&(~dma_par(0xFFFFFFFF)))|dma_par(par));}

    #define conf_dma_m0a(dma,event,m0a)            {* (uint32_t *)((dma_id(dma)) + (0x1C + check_stream(default_s,event))) = \
                                                    ((* (uint32_t *)((dma_id(dma)) + (0x1C + check_stream(default_s,event)))&(~dma_m0a(0xFFFFFFFF)))|dma_m0a(m0a));}

    #define conf_dma_m1a(dma,event,m1a)            {* (uint32_t *)((dma_id(dma)) + (0x20 + check_stream(default_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x20 + check_stream(default_s,event)))&(~dma_m1a(0xFFFFFFFF)))|dma_m1a(m1a));}

    #define conf_dma_feie(dma,event,feie)          {* (uint32_t *)((dma_id(dma)) + (0x24 + check_stream(fifo_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x24 + check_stream(fifo_s,event))&(~dma_feie(0x1)))|dma_feie(feie));}

    #define conf_dma_fs(dma,event,fs)              {* (uint32_t *)((dma_id(dma)) + (0x24 + check_stream(fifo_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x24 + check_stream(fifo_s,event)))&(~dma_fs(0x5)))|dma_fs(fs));}

    #define conf_dma_dmdis(dma,event,dmdis)        {* (uint32_t *)((dma_id(dma)) + (0x24 + check_stream(fifo_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x24 + check_stream(fifo_s,event)))&(~dma_dmdis(0x1)))|dma_dmdis(dmdis));}

    #define conf_dma_fth(dma,event,fth)            {* (uint32_t *)((dma_id(dma)) + (0x24 + check_stream(fifo_s,event))) = \
                                                    ((* ((uint32_t *)(dma_id(dma)) + (0x24 + check_stream(fifo_s,event)))&(~dma_fth(0x2)))|dma_fth(fth));}



