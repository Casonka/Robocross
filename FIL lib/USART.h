
#pragma once
#include <FilConfig.h>
        #define usart1  64
        #define usart2  17
        #define usart3  18
        #define usart4  19
        #define usart5  20
        #define usart6  65
        #define usart7  34
        #define usart8  35

        //статусы регистра SR
        #define transmitter_data_empty  ((uint32_t)(1 << 7))
        #define transmission_complete  ((uint32_t)(1 << 6))
        #define receiver_data_notEmpty  ((uint32_t)(1 << 5))
        #define overrun_error  ((uint32_t)(1 << 3))
        #define framing_error   ((uint32_t)(1 << 1))
        #define parity_error   ((uint32_t)(1))

        #define usart_offset        ((uint32_t)0x00400)
        #define usart_base(usart)   (PERIPH_BASE +(0x00004000 * ((usart&0x10)>>4)) + (0x00007000 * ((usart&0x20)>>5)) + (0x00011000 * ((usart&0x40) >> 6)))
        #define usart_id(usart)     ((uint32_t)((usart&0xF)*usart_offset))

        //адрес значения
        #define usart_enable(ue)                      ((uint16_t)((ue) << 13))
        #define usart_word_length(m)                  ((uint16_t)((m) << 12))
        #define usart_stop_bits(stop)                 ((uint16_t)((stop) << 12))
        #define usart_dmat(dmat)                      ((uint16_t)((dmat) << 7))
        #define usart_dmar(dmar)                      ((uint16_t)((dmar) << 6))
        #define usart_baud(baud)                      ((uint16_t)(baud))
        #define usart_transmitter(te)                 ((uint16_t)((te) << 3))
        #define usart_receiver(re)                    ((uint16_t)((re) << 2))
        #define usart_data(dr)                        ((uint16_t)(dr))
        #define usart_rxneie(rxneie)                  ((uint16_t)((rxneie) << 5))
        #define usart_txneie(txneie)                  ((uint16_t)((txneie) << 7))
        #define usart_over8(over8)                    ((uint16_t)((over8) << 15))
        //вычисление адреса и установление значения
        #define set_usart_baud(usart,baud)           (* (uint32_t *)((usart_base(usart) + usart_id(usart)) + 0x08) |= usart_baud(baud))
        #define set_usart_ue(usart,ue)               (* (uint32_t *)((usart_base(usart) + usart_id(usart)) + 0x0C) |= usart_enable(ue))
        #define set_usart_mbit(usart,m)              (* (uint32_t *)((usart_base(usart) + usart_id(usart)) + 0x0C) |= usart_word_length(m))
        #define set_usart_stopbit(usart,stop)        (* (uint32_t *)((usart_base(usart) + usart_id(usart)) + 0x10) |= usart_stop_bits(stop))
        #define set_usart_dmat(dmat)                 (* (uint32_t *)((usart_base(usart) + usart_id(usart)) + 0x14) |= usart_dmat(dmat))
        #define set_usart_dmar(dmar)                 (* (uint32_t *)((usart_base(usart) + usart_id(usart)) + 0x14) |= usart_dmar(dmar))
        #define set_usart_transmitter(te)            (* (uint32_t *)((usart_base(usart) + usart_id(usart)) + 0x0C) |= usart_transmitter(te))
        #define set_usart_receiver(re)               (* (uint32_t *)((usart_base(usart) + usart_id(usart)) + 0x0C) |= usart_receiver(re))
        #define set_usart_rxneie(rxneie)             (* (uint32_t *)((usart_base(usart) + usart_id(usart)) + 0x0C) |= usart_rxneie(rxneie))
        #define set_usart_txneie(txneie)             (* (uint32_t *)((usart_base(usart) + usart_id(usart)) + 0x0C) |= usart_txneie(txneie))
        #define set_usart_over8(over8)               (* (uint32_t *)((usart_base(usart) + usart_id(usart)) + 0x0C) |= usart_over8(over8))

        //вычисление адреса, очистка и установка значения
        #define conf_usart_baud(usart,baud)         {* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x08)) = \
                                                    ((* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x08))&(~usart_baud(0xFFFFFFFF)))|usart_baud(baud));}

        #define conf_usart_ue(usart,ue)             {* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C)) = \
                                                    ((* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C))&(~usart_enable(0x1)))|usart_enable(ue));}

        #define conf_usart_mbit(usart,m)            {* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C)) = \
                                                    ((* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C))&(~usart_word_length(0x1)))|usart_word_length(m));}

        #define conf_usart_stop(usart,stop)         {* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x10)) = \
                                                    ((* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x10))&(~usart_stop_bits(stop)))|usart_stop_bits(stop));}

        #define conf_usart_dmat(usart,dmat)         {* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x14)) = \
                                                    ((* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x14))&(~usart_dmat(0x1)))|usart_dmat(dmat));}

        #define conf_usart_dmar(usart,dmar)         {* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x14)) = \
                                                    ((* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x14))&(~usart_dmar(0x1)))|usart_dmar(dmar));}

        #define conf_usart_transmitter(usart,te)    {* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C)) = \
                                                    ((* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C))&(~usart_transmitter(0x1)))|usart_transmitter(te));}

        #define conf_usart_receiver(usart,re)       {* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C)) = \
                                                    ((* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C))&(~usart_receiver(0x1)))|usart_receiver(re));}

        #define conf_usart_rxneie(usart,rxneie)       {* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C)) = \
                                                    ((* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C))&(~usart_rxneie(0x1)))|usart_rxneie(rxneie));}

        #define conf_usart_txneie(usart,txneie)       {* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C)) = \
                                                    ((* ((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C))&(~usart_txneie(0x1)))|usart_txneie(txneie));}

        //вычисление адреса и проверка статуса
        #define get_status(usart,state)             (( (* (uint32_t *)((usart_base(usart) + usart_id(usart)) + 0x00)))&((uint32_t)state))
        #define get_usart_over8(usart)              ((uint32_t)((*((uint32_t *)(usart_base(usart) + usart_id(usart) + 0x0C)))&((uint16_t)0x8000)))

        //расчеты
        #define divider_over8(usart)                ((get_usart_over8(usart)*4)+((!get_usart_over8(usart)*2)))
        #define integer_divider(usart,baud)         ((uint32_t)((25*sourse_calc(usart))/((divider_over8(usart)*2)*baud)))
        #define tmpreg(usart,baud)                  ((uint32_t)((integer_divider(usart,baud)/100) << 4))
        #define fractional_divider(usart,baud)      ((uint32_t)(integer_divider(usart,baud) - (100*(tmpreg(usart,baud) >> 4))))
        #define calc_baud(usart,baud)               ((uint16_t)(tmpreg(usart,baud)|((((fractional_divider(usart,baud)*(4*divider_over8(usart))) + 50) / 100) & ((uint8_t)((0x07*get_usart_over8(usart)) + (0x0F*(~get_usart_over8(usart))))))))
        #define sourse_calc(usart)                  ((uint32_t)((((usart&0x40) >> 6)*current_APB1)+((((usart&0x20)>>5)+((usart&0x30)>>4))*current_APB2)))
        #define callc_baud(usart,baud)              ((uint16_t)(sourse_calc(usart)/baud))


        #define usartReceiverConfigure(usart,baud)   {     \
            conf_usart_baud(usart,calc_baud(usart,baud));  \
            conf_usart_dmar(usart,0x1);                    \
            conf_usart_receiver(usart,0x1);                \
            conf_usart_rxneie(usart,0x1);                  \
            conf_usart_ue(usart,0x1);                }

        #define usartTransmitterConfigure(usart,baud)   {   \
            conf_usart_baud(usart,calc_baud(usart,baud));  \
            conf_usart_dmat(usart,0x1);             \
            conf_usart_transmitter(usart,0x1);      \
            conf_usart_txneie(usart,0x1);           \
            conf_usart_ue(usart,0x1);             }

        #define usartBothConfigure(usart,baud)      {  \
            conf_usart_baud(usart,callc_baud(usart,baud));  \
            conf_usart_dmar(usart,0x1);             \
            conf_usart_dmat(usart,0x1);             \
            conf_usart_transmitter(usart,0x1);      \
            conf_usart_receiver(usart,0x1);         \
            conf_usart_rxneie(usart,0x1);           \
            conf_usart_txneie(usart,0x1);           \
            conf_usart_ue(usart,0x1);         }
