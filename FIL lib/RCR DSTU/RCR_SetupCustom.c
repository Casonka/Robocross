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
    // 14 ��� ��������
    // 2500 - ����� �� ���������� (�������� 4800 ���)   16% ������
    // 2916 - ��� �� ( ����� 4800 ��� ) 0.02% ������
    // 2187 - ��� �����
    // 1458 - ����� �� ( ����� 9600 ���)  0.02% ������
    // 1250 - ��� �����
    // 857 - ��� ������ ( ����� 14400 ��� )
    // 729 - ��� ������ ( ����� 19200 ���)
    // 121 - ��� ������ (����� 115200 ���) 0.4% ������
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
