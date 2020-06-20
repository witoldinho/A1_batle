#include "zasob.h"
#include "mcc_generated_files/uart2.h"
//#include "mcc_generated_files/pin_manager.h"

void TMR3_Initialize (void)
{
    // Period = 0.000088 s; Frequency = 12000000 Hz; PR1 131; 
   // PR1 = 0x83;
    PR3=46875; // 0,5 Hz przebieg z togle , prawie 1 s
    
    
    //  TCKPS 1:8; TWDIS disabled; TCS PBCLK; TECS SOSC; SIDL disabled; TSYNC disabled; TWIP disabled; TGATE disabled; ON enabled; 
   // T1CON = 0x8010;    

    T3CONbits.TCKPS=7;
//    T3CONbits.ON=1;
T3CONbits.ON=0;
      IEC0bits.T3IE=true;
    
    IFS0CLR = _IFS0_T3IF_MASK;
    IEC0SET = _IEC0_T3IE_MASK;
    

 //   tmr1_obj.timerElapsed = false;

}


void __attribute__ ((vector(_TIMER_3_VECTOR), interrupt(IPL1SOFT))) TMR3_ISR()
{
    //pin1_tg;
    D512_IF.Timeout=1;
    //pin2_tg;
  //  pin3_tg;
    
    IFS0CLR = _IFS0_T3IF_MASK;
}
void DMX_OUT_2(void)
{
    uint16_t x;
    D512_IF.Ramka_OK=NOK;
    for(x=0;x<DMX_CHANNELS;x++){
        UART2_Write(channel_data[x++]); 
    }
   
    
}