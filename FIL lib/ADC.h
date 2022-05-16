
#pragma once
#include <FilConfig.h>

#if(_DefaultSectorIncludeHandler != 0)

    #define ADCScanConfigure(ADC,LENGTH,                                            \
            ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8,ch9,ch10,ch11,ch12,ch13,ch14,ch15,ch16, \
            numb_smpr,cycles)     {                                                 \
        ConfADCSmpr(ADC,NUMBER,CYCLES)                                              \
        SetADCLength(ADC,LENGTH);                                                   \
        SetADCScan(ADC);                                                            \
        SetADCCont(ADC);                                                            \
        SetADCDMA(adc);                                                             \
        SetADCDDS(adc);                                                             \
        SetADCAdon(adc);                                                            \
        SetADCSWStart(adc);        }

    #define SetADCSMP1(ADC,CYCLES)          (* (uint32_t *)((ADC) + 0x0C) |= ADCSmpr1(CYCLES)

    #define SetADCSMP2(ADC,CYCLES)          (* (uint32_t *)((ADC) + 0x10) |= ADCSmpr2(CYCLES)

    #define SetADCLength(ADC,LENGTH)        (* (uint32_t *)((ADC) + 0x2C) |= ADCLength(LENGTH))

    #define SetADCSQ1(ADC,CH1,CH2,CH3,CH4)  (* (uint32_t *)((ADC) + 0x2C) |= ADCSQ1(CH1,CH2,CH3,CH4)

    #define SetADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10) (* (uint32_t *)((ADC) + 0x30) |= ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10)

    #define SetADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16) (* (uint32_t *)((ADC) + 0x34) |= ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16)

    #define SetADCScan(ADC)                 (* (uint32_t *)((ADC) + 0x04) |= 0x1)

    #define SetADCResolution(adc,RES)       (* (uint32_t *)((ADC) + 0x04) |= adc_resolution(RES))

    #define SetADCDMA(ADC)                  (* (uint32_t *)((ADC) + 0x08) |= 0x1)

    #define SetADCCont(ADC)                 (* (uint32_t *)((ADC) + 0x08) |= 0x1)

    #define SetADCDDS(ADC)                  (* (uint32_t *)((ADC) + 0x08) |= 0x1)

    #define SetADCAdon(ADC)                 (* (uint32_t *)((ADC) + 0x08) |= 0x1)

    #define SetADCSWStart(ADC)              (* (uint32_t *)((ADC) + 0x08) |= 0x1)

    #define ConfADCLength(ADC,LENGTH)                       {* ((uint32_t *)((ADC) + 0x2C)) = \
                                                            ((* ((uint32_t *)((ADC) + 0x2C))&(~(0xF)))|ADCLength(LENGTH));}

    #define ConfADCSQ1(ADC,CH1,CH2,CH3,CH4)                 {* ((uint32_t *)((ADC) + 0x2C)) = \
                                                            ((* ((uint32_t *)((ADC) + 0x2C))&(~(0xFFFFF)))|ADCSQ1(CH1,CH2,CH3,CH4));}

    #define ConfADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10)        {* ((uint32_t *)((ADC) + 0x30)) = \
                                                            ((* ((uint32_t *)((ADC) + 0x30))&(~(0x3FFFFFFF)))|ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10));}

    #define ConfADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16)   {* ((uint32_t *)((ADC) + 0x34)) = \
                                                            ((* ((uint32_t *)((ADC) + 0x34))&(~(0x3FFFFFFF)))|ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16));}

    #define ConfADCSmpr1(ADC,CYCLES)                        {* ((uint32_t *)((ADC) + 0x0C)) = \
                                                            ((* ((uint32_t *)((ADC) + 0x0C))&(~(0x7FFFFFF)))|ADCSmpr1(CYCLES));}

    #define ConfADCSmpr2(ADC,CYCLES)                        {* ((uint32_t *)((ADC) + 0x10)) = \
                                                            ((* ((uint32_t *)((ADC) + 0x10))&(~(0x3FFFFFFF)))|ADCSmpr2(CYCLES));}

    #define ConfADCSmpr(ADC,NUMBER,CYCLES) {\
        (NUMBER > 0) (ConfADCSmpr2(ADC,CYCLES)) : \
        (NUMBER > 10) (ConfADCSmpr1(ADC,CYCLES)); }


#if(_DeveloperDeprecatedFunctions == 1)
    /*!
    *   @brief This block include deprecated functions for configuration ADC channels
    */
    #define set_adc_sq1_6(adc,number,ch1,ch2,ch3,ch4,ch5,ch6)       (* (uint32_t *)((adc) + 0x34) |= numb_sq1_conf(number,ch1,ch2,ch3,ch4,ch5,ch6))

    #define set_adc_sq7_12(adc,number,ch7,ch8,ch9,ch10,ch11,ch12)   (* (uint32_t *)((adc) + 0x30) |= numb_sq2_conf(number,ch7,ch8,ch9,ch10,ch11,ch12))

    #define set_adc_sq13_16(adc,number,ch13,ch14,ch15,ch16)         (* (uint32_t *)((adc) + 0x2C) |= numb_sq3_conf(number,ch13,ch14,ch15,ch16))

    #define numb_sq1_conf(number,ch1,ch2,ch3,ch4,ch5,ch6)           ((((number&0x20) >> 5)*(ch6 << 25))|(((number&0x10) >> 4)*(ch5 << 20))|(((number&0x8) >> 3)*(ch4 << 15))|(((number&0x4) >> 2)*(ch3 << 10))|(((number&0x2) >> 1)*(ch2 << 5))|((number&0x1)*ch1))

    #define numb_sq2_conf(number,ch7,ch8,ch9,ch10,ch11,ch12)        ((((number&0x800) >> 11)*(ch12 << 25))|(((number&0x400) >> 4)*(ch11 << 20))|(((number&0x200) >> 3)*(ch10 << 15))|(((number&0x100) >> 2)*(ch9 << 10))|(((number&0x80) >> 1)*(ch8 << 5))|((number&0x40)*ch7))

    #define numb_sq3_conf(number,ch13,ch14,ch15,ch16)               ((((number&0x8000) >> 15)*(ch16 << 15))|(((number&0x4000) >> 14)*(ch15 << 10))|(((number&0x2000) >> 13)*(ch14 << 5))|(((number&1000) >> 12)*(ch13)))

    #define set_adc_smp10_18(adc,number,smp)    (* (uint32_t *)((adc) + 0x0C) |= numb_smpr1_conf(number,smp))

    #define set_adc_smp0_9(adc,number,smp)      (* (uint32_t *)((adc) + 0x10) |= numb_smpr2_conf(number,smp))

    #define numb_smpr2_conf(number,value)  ((((number&0x200) >> 9)*(value << 28))|(((number&0x100) >> 8)*(value << 25))|(((number&0x80) >> 7)*(value << 22))|(((number&0x40) >> 6)*(value << 19))|(((number&0x20) >> 5)*(value << 16))|(((number&0x10) >> 4)*(value << 13))|(((number&0x8) >> 3)*(value << 10))|(((number&0x4) >> 2)*(value << 7))|(((number&0x2) >> 1)*(value << 4))|((number&0x1)*value))

    #define numb_smpr1_conf(number,value)  ((((number&0x40000) >> 18)*(value << 25))|(((number&0x20000) >> 17)*(value << 22))|(((number&0x10000) >> 16)*(value << 19))|(((number&0x8000) >> 15)*(value << 16))|(((number&0x4000) >> 14)*(value << 13))|(((number&0x2000) >> 13)*(value << 10))|(((number&0x1000) >> 12)*(value << 7))|(((number&0x800) >> 11)*(value << 4))|(((number&0x400) >> 10)*value))

    #define config_conversions(adc,number,ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8,ch9,ch10,ch11,ch12,ch13,ch14,ch15,ch16)    {\
        set_adc_sq1_6(adc,number,ch1,ch2,ch3,ch4,ch5,ch6);                                                                \
        set_adc_sq7_12(adc,number,ch7,ch8,ch9,ch10,ch11,ch12);                                                            \
        set_adc_sq13_16(adc,number,ch13,ch14,ch15,ch16);                 }

    #define config_smpr(adc,number,value)   {   \
        set_adc_smp0_9(adc,number,value);       \
        set_adc_smp10_18(adc,number,value);     }

#endif /*_DeveloperDeprecatedFunctions*/

    #define ADCLength(LENGTH)              ((uint32_t)((LENGTH) << 20))

    #define ADCScan(scan)                  ((uint32_t)((scan) << 8))

    #define ADCCont(cont)                  ((uint32_t)((cont) << 1))

    #define ADCDMA(dma)                    ((uint32_t)((dma) << 14))

    #define ADCAdon(adon)                  ((uint32_t)(adon))

    #define ADCSWStart(SWS)                 ((uint32_t)((SWS) << 30))

    #define ADCDDS(dds)                    ((uint32_t)((dds) << 13))

    #define ADCSQ1(CH1,CH2,CH3,CH4)                             (CH1 << 15) | (CH2 << 10) |  \
                                                                (CH3 << 5)  | (CH4)


    #define ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10)                    (CH5 << 25) | (CH6 << 20) |  \
                                                                (CH7 << 15) | (CH8 << 10) |  \
                                                                (CH9 << 5)  | (CH10)


    #define ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16)               (CH11 << 25) | (CH12 << 20) |  \
                                                                (CH13 << 15) | (CH14 << 10) |  \
                                                                (CH15 << 5)  | (CH16)

    #define ADCSmpr1(CYCLES)                                    (CYCLES << 24) | (CYCLES << 21) | (CYCLES << 18) | \
                                                                (CYCLES << 15) | (CYCLES << 12) | (CYCLES << 9) | \
                                                                (CYCLES << 6) | (CYCLES << 3) | (CYCLES)

    #define ADCSmpr2(CYCLES)                                    (CYCLES << 27) | (CYCLES << 24) | (CYCLES << 21) | \
                                                                (CYCLES << 18) | (CYCLES << 15) | (CYCLES << 12) | \
                                                                (CYCLES << 9) | (CYCLES << 6) | (CYCLES << 3) | (CYCLES)

    #define ADCOverrun(ovr)                ((uint32_t)((ovr) << 5))

    #define ADCStrt(strt)                  ((uint32_t)((strt) << 4))

    #define ADCJstrt(jstrt)                ((uint32_t)((jstrt) << 3))

    #define ADCJeoc(jeoc)                  ((uint32_t)((jeoc) << 2))

    #define ADCEoc(eoc)                    ((uint32_t)((eoc) << 1))

    #define ADCAwd(awd)                    ((uint32_t)(awd))

    #define ADCOverIe(overie)              ((uint32_t)((overie) << 26))

    #define ADCRes(res)                    ((uint32_t)((res) << 24))

    #define ADCAwden(awden)                ((uint32_t)((awden) << 23))

    #define ADCJawden(jawden)              ((uint32_t)((jawden) << 22))

    #define ADCDiscnum(discnum)            ((uint32_t)((discnum) << 13))

    #define ADCJdiscen(jdiscen)            ((uint32_t)((jdiscen) << 12))

    #define ADCDiscen(discen)              ((uint32_t)((discen) << 11))

    #define ADCJauto(jauto)                ((uint32_t)((jauto) << 10))

    #define ADCAwdsgl(awdsgl)              ((uint32_t)((awdsgl) << 9))

    #define ADCJeocIe(jeocie)              ((uint32_t)((jeocie) << 7))

    #define ADCAwdIe(awdie)                ((uint32_t)((awdie) << 6))

    #define ADCEocIe(eocie)                ((uint32_t)((eocie) << 5))

    #define ADCAwdch(awdch)                ((uint32_t)(awdch))

    #define ADCExtern(exten)               ((uint32_t)((exten) << 28))

    #define ADCExtsel(extsel)              ((uint32_t)((extsetl) << 23))

    #define ADCJSWStart(jswstart)          ((uint32_t)((jswstart) << 22))

    #define ADCJiextern(jiexten)           ((uint32_t)((jiexten) << 21))

    #define ADCJiexsel(jiexsel)            ((uint32_t)((jiexsel) << 16))

    #define ADCAlign(align)                ((uint32_t)((align) << 11))

    #define ADCEocs(eocs)                  ((uint32_t)((eocs) << 10))

    #define ADCJofsset(joffset)            ((uint32_t)joffset)

    #define ADCHt(ht)                      ((uint32_t)(ht))

    #define ADCLtr(ltr)                    ((uint32_t)(ltr))

    #define ADCJl(jl)                      ((uint32_t)((jl) << 20))

    #define ADCJdata(jdata)                ((uint32_t)(jdata))

    #define ADCDR(dr)                      ((uint32_t)(dr))

    #define ADCOvr3(ovr3)                  ((uint32_t)((ovr3) << 21))

    #define ADCStrt3(strt3)                ((uint32_t)((strt3) << 20))

    #define ADCJstrt3(jstrt3)              ((uint32_t)((jstrt3) << 19))

    #define ADCJeoc3(jeoc3)                ((uint32_t)((jeoc3) << 18))

    #define ADCEoc3(eoc3)                  ((uint32_t)((eoc3) << 17))

    #define ADCAwd3(awd3)                  ((uint32_t)((awd3) << 16))

    #define ADCOvr2(ovr2)                  ((uint32_t)((ovr2) << 13))

    #define ADCStrt2(strt2)                ((uint32_t)((strt2) << 12))

    #define ADCJstrt2(jstrt2)              ((uint32_t)((jstrt2) << 11))

    #define ADCJeoc2(jeoc2)                ((uint32_t)((jeoc2) << 10))

    #define ADCEoc2(eoc2)                  ((uint32_t)((eoc2) << 9))

    #define ADCAwd2(awd2)                  ((uint32_t)((awd2) << 8))

    #define ADCOvr1(ovr1)                  ((uint32_t)((ovr1) << 5))

    #define ADCStrt1(strt1)                ((uint32_t)((strt1) << 4))

    #define ADCJstrt1(jstrt1)              ((uint32_t)((jstrt1) << 3))

    #define ADCJeoc1(jeoc1)                ((uint32_t)((jeoc1) << 2))

    #define ADCEoc1(eoc1)                  ((uint32_t)((eoc1) << 1))

    #define ADCAwd1(awd1)                  ((uint32_t)(awd1))

    #define ADCTsvrefe(tsvrefe)            ((uint32_t)((tsvrefe) << 23))

    #define ADCVbate(vbate)                ((uint32_t)((vbate) << 22))

    #define ADCAdcpre(adcpre)              ((uint32_t)((adcpre) << 16))

    #define ADCDelay(delay)                ((uint32_t)((delay) << 8))

    #define ADCMulti(multi)                ((uint32_t)(multi))

    #define ADCData1(data1)                ((uint32_t)(data1))

    #define ADCData2(data2)                ((uint32_t)((data2) << 16))

#endif /*_DefaultSectorIncludeHandler*/
