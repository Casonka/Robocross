    /*!
    *   --------------------------------------------------------------------------
    *                       ///TIM initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 11/04/2022 - last update version TIM
    *
    *       @note This file for configuration main functional properties of timers
    */
#pragma once
#include "FilConfig.h"

    /*!
    *   @brief TimPWMConfigure(TIM,prescaler,autoreset,ch1,ch2,ch3,ch4) - configuration timer in PWM mode
    *       @arg TIM - number of timer
    *       @arg prescaler - value for increase the input frequency
    *       @arg autoreset - value for set the period of timer
    *       @arg ch<n> - activate/deactivate the channels of timer
    */
    #define TimPWMConfigure(TIM,prescaler,autoreset,ch1,ch2,ch3,ch4) {\
        ConfChannelsTim(TIM,6,6,ch1,ch2,ch3,ch4);                    \
        ConfFreq(TIM,prescaler,autoreset);                           \
        TimStart(TIM);                                               \
        ConfTimMainOutput(TIM,1);                                    \
        ConfTimAutomaticOutput(TIM,1);                               \
        ResetTimCCR1(TIM);                                           \
        ResetTimCCR2(TIM);                                           }

#define FREQ_1_Hz   0x0A
#define FREQ_10_Hz  0x1A
#define FREQ_50_Hz  0x2A

    /*!
    *   @brief TimPIDConfigure(TIM,frequency) - configuration timer in calculating mode
    *   (P-regulation, PI - regulation, PID - regulation and other regulations)
    *       @arg TIM - number of timer
    *       @arg freq - target frequency for calculating
    */
    #define TimPIDConfigure(TIM,freq)       {\
        ResetTimCNT(TIM);                   \
        ConfPIDFreq(TIM,freq);              \
        ConfTimUpdateInterrupt(TIM,1);      \
        TimStart(TIM);                      }

    /*!
    *   @brief TimEncoderConfigure(TIM) - configuration timer with encoder interface
    *       @arg TIM - number of timer
    */
    #define TimEncoderConfigure(TIM)    {\
        ResetTimPSC(TIM);               \
        ConfTimARR(TIM,0xFFFFFFFF);     \
        TimStart(TIM);                  \
        ConfSMS(TIM,0x3);               \
        ConfEtf(TIM,0xF);               }

    /*!
    *   @brief TimPWMInputCaptureConfigure(TIM) - configuration timer for check length of PWM
    *       @arg TIM - number of timer
    */
    #define TimPWMInputCaptureConfigure(TIM)                          {\
        ResetTimPSC(TIM);                                             \
        ConfTimARR(TIM,0xFFFFFFFF);                                   \
        ConfCaptureSelection1(TIM,0x1,0x2,1);                         \
        ConfCapturePolarity(TIM,0x0,0x1,0x0,0x1,1,0);                 \
        ConfCaptureComplementaryPolarity(TIM,0x0,0x1,0x0,0x1,1,0);    \
        ConfTriggerSelection(TIM,0x5);                                \
        ConfSms(TIM,0x4);                                             \
        ConfTimCapture(TIM,0x1,0x1,0,0,1,1,0,0);                      \
        TimStart(TIM);                                                }

    /*!
    *   @brief TimPWMCentralAlignedModeConfigure(TIM,prescaler,autoreset,ch1,ch2,polarity1,ch3,ch4,polarity2) - configuration timer with central aligned mode
    *       @arg TIM - number of timer
    *       @arg prescaler - value for increase the input frequency
    *       @arg autoreset - value for set the period of timer
    *       @arg polarity<n> - set polarity level for PWM output
    *       @arg ch<n> - activate/deactivate the channels of timer
    */
    #define TimPWMCentralAlignedModeConfigure(TIM,prescaler,autoreset,ch1,ch2,polarity1,ch3,ch4,polarity2) {\
        ConfChannelsTim(TIM,polarity1,polarity2,ch1,ch2,ch3,ch4);                                          \
        ConfFreq(TIM,prescaler,autoreset);                                                                 \
        TimStart(TIM);                                                                                     \
        ResetTimCCR1(TIM);                                                                                 \
        ResetTimCCR2(TIM);                                                                                 }

//----------------------------High commands------------------------------------//

    #define ConfChannelsTim(TIM,mode1,mode2,ch1,ch2,ch3,ch4) {\
        ConfTimOutputCompare1(TIM,mode1,mode1,ch1,ch2);       \
        ConfTimOutputCompare2(TIM,mode2,mode2,ch3,ch4);       \
        ConfTimCompareFast1(TIM,1,1,ch1,ch2);                 \
        ConfTimCompareFast2(TIM,1,1,ch3,ch4);                 \
        ConfTimCapture(TIM,1,1,1,1,ch1,ch2,ch3,ch4);          }

    #define ConfPIDFreq(TIM,freq)           {\
        if(freq == FREQ_10_Hz);             \
        ConfTimPSC(TIM,(CalcPSC(freq)));    \
        ConfTimARR(TIM,(CalcARR(freq)));    }

    #define ConfFreq(TIM,prescaler,autoreset)   {\
        ConfTimPSC(TIM,prescaler);              \
        ConfTimARR(TIM,autoreset);              }

    #define ConfTimStart(TIM)           {\
        ConfTimCounter(TIM,0x1);        \
        ConfTimPreloadARR(TIM,0x1);     }

    #define ConfTimCCR(TIM,duty1,duty2,duty3,duty4)
//-----------------------Simple commands reset and set the state-------------------------------------------------------------------------------------------------------------//
    #define ConfTimPSC(TIM,PSC)           {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x28)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x28))&(~TimPSC(0xFFFF)))|TimPSC(PSC));}

    #define ConfTimARR(TIM,ARR)           {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x2C)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x2C))|(~TimARR(0x00000000)))&TimARR(ARR));}

    #define ConfTimCounter(TIM,cen)       {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x00)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x00))&(~TimCEN(0x1)))|TimCEN(cen));}

    #define ConfTimPreloadARR(TIM,arpe)  {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x00)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x00))&(~TimPreloadARR(0x1)))|TimPreloadARR(arpe));}

    #define ConfTimUpdateRequest(TIM,urs)  {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x00)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x00))&(~TimUpdateRequest(0x1)))|TimUpdateRequest(urs));}

    #define ConfTimOutputCompare1(TIM,oc1m,oc2m,ch1,ch2)         {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x18)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x18))&(~TimOutputCompare1(0x7,0x7,1,1)))|TimOutputCompare1(oc1m,oc2m,ch1,ch2));}

    #define ConfTimOutputCompare2(TIM,oc3m,oc4m,ch3,ch4)         {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x1C)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x1C))&(~TimOutputCompare2(0x7,0x7,1,1)))|TimOutputCompare2(oc3m,oc4m,ch3,ch4));}

    #define ConfTimCompareFast1(TIM,oc1fe,oc2fe,ch1,ch2)         {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x18)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x18))&(~TimOutputCompareFast1(0x1,0x1,1,1)))|TimOutputCompareFast1(oc1fe,oc2fe,ch1,ch2));}

    #define ConfTimCompareFast2(TIM,oc3fe,oc4fe,ch3,ch4)         {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x1C)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x1C))&(~TimOutputCompareFast2(0x1,0x1,1,1)))|TimOutputCompareFast2(oc3fe,oc4fe,ch3,ch4));}

    #define ConfTimCapture(TIM,cc1e,cc2e,cc3e,cc4e,ch1,ch2,ch3,ch4) {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x20)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x20))&(~TimCapture(0x1,0x1,0x1,0x1,1,1,1,1)))|TimCapture(cc1e,cc2e,cc3e,cc4e,ch1,ch2,ch3,ch4));}

    #define ConfTimUpdateInterrupt(TIM,uie)  {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x0C)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x0C))&(~TimUpdateInterrupt(0x1)))|TimUpdateInterrupt(uie));}

    #define ConfTimMainOutput(TIM,moe)  {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x44)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x44))&(~TimMainOutput(0x1)))|TimMainOutput(moe));}

    #define ConfTimAutomaticOutput(TIM,aoe)  {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x44)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x44))&(~TimAutomaticOutput(0x1)))|TimAutomaticOutput(aoe));}

    #define ConfTimUpdateGeneration(TIM,ug)  {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x14)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x14))&(~TimUpdateGeneration(0x1)))|TimUpdateGeneration(ug));}

    #define ConfCCR1(TIM,value)         {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x34)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x34))&(~TimCCR1(0xFFFF)))|TimCCR1(value));}

    #define ConfCCR2(TIM,value)         {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x38)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x38))&(~TimCCR2(0xFFFF)))|TimCCR2(value));}

    #define ConfCCR3(TIM,value)         {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x3C)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x3C))&(~TimCCR3(0xFFFF)))|TimCCR3(value));}

    #define ConfCCR4(TIM,value)         {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x40)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x40))&(~TimCCR4(0xFFFF)))|TimCCR4(value));}

    #define ConfSMS(TIM,sms)            {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x08)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x08))&(~TimSMS(0xF)))|TimSMS(sms));}

    #define ConfEtf(TIM,etf)            {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x08)) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x08))&(~TimETF(0x7)))|TimETF(etf));}

    #define ConfCaptureSelection1(TIM,cc1s,cc2s,ch1)   {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x18)) = \
                                                       ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x18))&(~TimCaptureSelection1(0x3,0x3,1)))|TimCaptureSelection1(cc1s,cc2s,ch1));}

    #define ConfCaptureSelection2(TIM,cc3s,cc4s,ch2)   {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x1C)) = \
                                                       ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x1C))&(~TimCaptureSelection2(0x3,0x3,1)))|TimCaptureSelection2(cc3s,cc4s,ch2));}

    #define ConfCapturePolarity(TIM,cc1p,cc2p,cc3p,cc4p,ch1,ch2)  {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x20)) = \
                                                                  ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x20))&(~TimCapturePolarity(0x1,0x1,0x1,0x1,1,1)))|TimCapturePolarity(cc1p,cc2p,cc3p,cc4p,ch1,ch2));}

    #define ConfCaptureComplementaryPolarity(TIM,cc1np,cc2np,cc3np,cc4np,ch1,ch2)    {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x20)) = \
                                                                                     ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x20))&(~TimCaptureComplementaryPolarity(0x1,0x1,0x1,0x1,1,1)))|TimCaptureComplementaryPolarity(cc1np,cc2np,cc3np,cc4np,ch1,ch2));}

    #define ConfTriggerSelection(TIM,ts)  {* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x08)) = \
                                          ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM) + 0x08))&(~TimTriggerSelection(0x7)))|TimTriggerSelection(ts));}

    #define ConfOnePulseMode(TIM,opm)   {* ((uint32_t *)(TimBase(TIM) + TimID(TIM))) = \
                                        ((* ((uint32_t *)(TimBase(TIM) + TimID(TIM)))&(~TimOPM(0x1)))|TimOPM(opm));}
//----------------------------Calculating-------------------------------------//

    #define CalcPSC(FREQ)      ((uint16_t)((current_APB1/(FREQ*MAX_PWM))))
    #define CalcARR(FREQ)      ((uint16_t)(current_APB1/FREQ*(CalcPSC(FREQ))))

//----------------------------Macro numbers of timers------------------------//
    #define Tim1  16
    #define Tim2  0
    #define Tim3  1
    #define Tim4  2
    #define Tim5  3
    #define Tim6  4
    #define Tim7  5
    #define Tim8  17
    #define Tim9  32
    #define Tim10 33
    #define Tim11 34
    #define Tim12 6
    #define Tim13 7
    #define Tim14 8
    #define rtc   10
//---------------------------Calculating address number of timer----------------------------------------//
    #define TimOffset      ((uint32_t)0x00400)
    #define TimBase(TIM)   (PERIPH_BASE +(0x00010000 * ((TIM&0x10)>>4)) + (0x00014000 * ((TIM&0x20)>>5)))
    #define TimID(TIM)     ((uint32_t)((TIM&0xF)*TimOffset))
//------------------------------Registers of timers----------------------------------------------------------------------------------------------------------------------------------//
    #define TimCNT(CNT)                                                     ((uint16_t)(CNT))
    #define TimCEN(CEN)                                                     ((uint16_t)(CEN))
    #define TimPreloadARR(ARPE)                                             ((uint16_t)((ARPE) << 7))
    #define TimUpdateRequest(URS)                                           ((uint16_t)((URS) << 2))
    #define TimPSC(PSC)                                                     ((uint16_t)(PSC))
    #define TimARR(ARR)                                                     ((uint32_t)(ARR))
    #define TimOutputCompare1(OC1M,OC2M,CH1,CH2)                            ((uint16_t)((((OC2M) << 12)*CH2) | (((OC1M) << 4)*CH1)))
    #define TimOutputCompare2(OC3M,OC4M,CH3,CH4)                            ((uint16_t)((((OC4M) << 12)*CH4) | (((OC3M) << 4)*CH3)))
    #define TimOutputCompareFast1(OC1FE,OC2FE,CH1,CH2)                      ((uint16_t)((((OC2FE) << 10)*CH2) | (((OC1FE) << 2)*CH1)))
    #define TimOutputCompareFast2(OC3FE,OC4FE,CH3,CH4)                      ((uint16_t)((((OC4FE) << 10)*CH4) | (((OC3FE) << 2)*CH3)))
    #define TimCapture(CC1E,CC2E,CC3E,CC4E,CH1,CH2,CH3,CH4)                 ((uint16_t)((((CC4E) << 12)*CH4) | (((CC3E) << 8)*CH3)| (((CC2E) << 4)*CH2) | ((CC1E)*CH1)))
    #define TimCaptureSelection1(CC1S,CC2S,CH1)                             ((uint16_t)((((CC2S) << 8)*CH1) | ((CC1S)*CH1)))
    #define TimCaptureSelection2(CC3S,CC4S,CH2)                             ((uint16_t)((((CC4S) << 8)*CH2) | ((CC3S)*CH2)))
    #define TimUpdateInterrupt(UIE)                                         ((uint16_t)(UIE))
    #define TimMainOutput(MOE)                                              ((uint16_t)((MOE) << 15))
    #define TimAutomaticOutput(AOE)                                         ((uint16_t)((AOE) << 14))
    #define TimUpdateGeneration(UG)                                         ((uint16_t)(UG))
    #define TimCCR1(CCR)                                                    ((uint16_t)(CCR))
    #define TimCCR2(CCR)                                                    ((uint16_t)(CCR))
    #define TimCCR3(CCR)                                                    ((uint16_t)(CCR))
    #define TimCCR4(CCR)                                                    ((uint16_t)(CCR))
    #define TimSMS(SMS)                                                     ((uint16_t)(SMS))
    #define TimETF(ETF)                                                     ((uint16_t)((ETF) << 8))
    #define TimCapturePolarity(CC1P,CC2P,CC3P,CC4P,CH1,CH2)                 ((uint16_t)((((CC4P) << 13)*CH2) | (((CC3P) << 9)*CH2)| (((CC2P) << 5)*CH1) | (((CC1P) << 1)*CH1)))
    #define TimCaptureComplementaryPolarity(CC1NP,CC2NP,CC3NP,CC4NP,CH1,CH2) ((uint16_t)((((CC4NP) << 15)*CH2) | (((CC3NP) << 11)*CH2)| (((CC2NP) << 7)*CH1) | (((CC1NP) << 3)*CH1)))
    #define TimTriggerSelection(TS)                                         ((uint16_t)((TS) << 4))
    #define TimSR(SR)                                                       ((uint16_t)(SR))
    #define TimOPM(OPM)                                                     ((uint16_t)(OPM) << 3)

//---------------------------------------Calculating address and reset state---------------------------------------------------//
    #define ResetTimCNT(TIM)        (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x24) &= (~TimCNT(0xFFFFFFFF)))
    #define ResetTimPSC(TIM)        (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x28) &= (~TimPSC(0xFFFFFFFF)))
    #define ResetTimARR(TIM)        (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x2C) |= (~TimARR(0x00000000)))
    #define ResetTimCCR1(TIM)       (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x34) &= (~TimCCR1(0xFFFFFFFF)))
    #define ResetTimCCR2(TIM)       (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x38) &= (~TimCCR2(0xFFFFFFFF)))
    #define ResetTimCCR3(TIM)       (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x3C) &= (~TimCCR3(0xFFFFFFFF)))
    #define ResetTimCCR4(TIM)       (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x40) &= (~TimCCR4(0xFFFFFFFF)))
    #define ResetTimSR(TIM)         (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x10) &= (~TimSR(0xFFFF)))

//----------------------------------------Calculating address and get state----------------------------------------------------//
    #define GetTimCNT(TIM) ((uint32_t)(* (uint32_t *)(TimBase(TIM)+TimID(TIM)+0x24)))
    #define GetTimARR(TIM) ((uint32_t)(* (uint32_t *)(TimBase(TIM)+TimID(TIM)+0x2C)))
    #define GetTimSR(TIM)  ((uint32_t)(* (uint32_t *)(TimBase(TIM)+TimID(TIM)+0x10)))

//----------------------------------------Calculating address and set state-----------------------------------------------------------------------------------------------------------------------------------//
    #define TimStart(TIM)                                   (* (uint32_t *)((TimBase(TIM) + TimID(TIM))) |= 0x1)
    #define SetTimPreloadARR(TIM,ARPE)                      (* (uint32_t *)((TimBase(TIM) + TimID(TIM))) |= TimPreloadARR(ARPE))
    #define SetTimUpdateRequest(TIM,urs)                    (* (uint32_t *)((TimBase(TIM) + TimID(TIM))) |= TimUpdateRequest(urs))
    #define SetTimOnePulseMode(TIM,opm)                     (* (uint32_t *)((TimBase(TIM) + TimID(TIM))) |= TimOPM(opm))
    #define SetTimPSC(TIM,PSC)                              (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x28) |= TimPSC(PSC))
    #define SetTimARR(TIM,ARR)                              (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x2C) &= TimARR(ARR))
    #define SetTimOutputeCompare1(TIM,oc1m,oc2m,ch1,ch2)      (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x18) |= TimOutputCompare1(oc1m,oc2m,ch1,ch2))
    #define SetTimOutputeCompare2(TIM,oc3m,oc4m,ch3,ch4)      (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x1C) |= TimOutputCompare2(oc3m,oc4m,ch3,ch4))
    #define set_compare_fast1(TIM,oc1fe,oc2fe,ch1,ch2)      (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x1C) |= TimOutputCompareFast1(oc1fe,oc2fe,ch1,ch2))
    #define set_compare_fast2(TIM,oc3fe,oc4fe,ch3,ch4)      (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x1C) |= TimOutputCompareFast2(oc3fe,oc4fe,ch3,ch4))
    #define set_capture(TIM,cc1e,cc2e,cc3e,cc4e,ch1,ch2,ch3,ch4)    (* (uint32_t *)((TimBase(TIM) + TimID(TIM) + 0x20)) |= tim_capture(cc1e,cc2e,cc3e,cc4e,ch1,ch2,ch3,ch4))
    #define set_update_interrupt(TIM,uie)                    (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x0C) |= tim_update_interrupt(uie))
    #define set_main_output(TIM,moe)                         (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x44) |= TimMainOutput(moe))
    #define set_automatic_output(TIM,aoe)                    (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x44) |= TimAutomaticOutput(aoe))
    #define set_update_generation(TIM,ug)                    (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x14) |= tim_update_generation(ug))
    #define set_ccr1(TIM,value)                              (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x34) |= TimCCR1(value))
    #define set_ccr2(TIM,value)                              (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x38) |= TimCCR2(value))
    #define set_ccr3(TIM,value)                              (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x3C) |= TimCCR3(value))
    #define set_ccr4(TIM,value)                              (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x40) |= TimCCR4(value))
    #define set_sms(TIM,sms)                                 (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x08) |= tim_sms(sms))
    #define set_etf(TIM,etf)                                 (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x08) |= tim_etf(etf))
    #define set_capture_selection1(TIM,cc1s,cc2s,ch1)        (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x18) |= tim_capture_selection1(cc1s,cc2s,ch1))
    #define set_capture_selection2(TIM,cc3s,cc4s,ch2)        (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x1C) |= tim_capture_selection1(cc3s,cc4s,ch2))
    #define set_capture_polarity(TIM,cc1p,cc2p,cc3p,cc4p,ch1,ch2)   (* (uint32_t *)((TimBase(TIM) + TimID(TIM) + 0x20)) |= tim_capture(cc1p,cc2p,cc3p,cc4p,ch1,ch2))
    #define set_capture_complementary_polarity(TIM,cc1np,cc2np,cc3np,cc4np,ch1,ch2) (* (uint32_t *)((TimBase(TIM) + TimID(TIM) + 0x20)) |= tim_capture_complementary_polarity(cc1np,cc2np,cc3np,cc4np,ch1,ch2))
    #define set_trigger_selection(TIM,ts)                    (* (uint32_t *)((TimBase(TIM) + TimID(TIM)) + 0x08) |= tim_trigger_selection(ts))

