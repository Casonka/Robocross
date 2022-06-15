#include "RCR_SetupCustom.h"


void BoardStart(void)
{
    ClocksInit;
    __disable_irq();
    InitPeriph;
    InterruptsEnable;
    TimPWMConfigure(Tim4,26,200,1,1,1,1);
    TimEngineClutchConfigure();
    TimEncoderConfigure(Tim8);
    TimEncoderConfigure(Tim1);
    TimEncoderConfigure(Tim3);
    TimEncoderConfigure(Tim2);
    TimPIDConfigure(Tim6,10);
    // 14 ћ√ц примерно
    // 2500 - буквы не показывает (примерно 4800 бод)   16% ошибка
    // 2916 - все ок ( почти 4800 бод ) 0.02% ошибка
    // 2187 - все плохо
    // 1458 - вроде ок ( около 9600 бод)  0.02% ошибка
    // 1250 - все плохо
    // 857 - все хорошо ( около 14400 бод )
    // 729 - все хорошо ( около 19200 бод)
    // 121 - все хорошо (около 115200 бод) 0.4% ошибка
    USARTBothConfigure(usart3, 121 , 0, 1);


}


void TimEngineClutchConfigure(void)
{
    ConfChannelsTim(Tim11,7,0,0,0,1,0,0,0);
    ConfFreq(Tim11,52,200);
    SetTimOnePulseMode(Tim11,1);
    ConfTimMainOutput(Tim11,1);
    ResetTimCCR1(Tim11);
    TimStart(Tim11);
    SetPWM(4,0.5);
}
