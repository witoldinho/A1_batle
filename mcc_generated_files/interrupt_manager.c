
#include <xc.h>

/**
    void INTERRUPT_Initialize (void)
*/
void INTERRUPT_Initialize (void)
{
    // Enable Multi Vector Configuration
    INTCONbits.MVEC = 1;
    
    //    CCPI: CCP 4 Input Capture or Output Compare
    //    Priority: 1
        IPC20bits.CCP4IP = 1;
    //    Sub Priority: 0
        IPC20bits.CCP4IS = 0;
    //    CCTI: CCP 4 Timer
    //    Priority: 1
        IPC20bits.CCT4IP = 1;
    //    Sub Priority: 0
        IPC20bits.CCT4IS = 0;
    //    UERI: UART 2 Error
    //    Priority: 1
        IPC14bits.U2EIP = 1;
    //    Sub Priority: 0
        IPC14bits.U2EIS = 0;
    //    UTXI: UART 2 Transmission
    //    Priority: 1
        IPC14bits.U2TXIP = 1;
    //    Sub Priority: 0
        IPC14bits.U2TXIS = 0;
    //    URXI: UART 2 Reception
    //    Priority: 1
        IPC14bits.U2RXIP = 1;
    //    Sub Priority: 0
        IPC14bits.U2RXIS = 0;
//        uart 1 RX prior. 
        IPC13bits.U1RXIP=1;
        IPC13bits.U1RXIS=0;
        
    //    CCPI: CCP 6 Input Capture or Output Compare
    //    Priority: 1
        IPC21bits.CCP6IP = 1;
    //    Sub Priority: 0
        IPC21bits.CCP6IS = 0;
    //    CCTI: CCP 6 Timer
    //    Priority: 1
        IPC21bits.CCT6IP = 1;
    //    Sub Priority: 0
        IPC21bits.CCT6IS = 0;
    //    CNDI: PORT D Change Notification
    //    Priority: 1
        IPC2bits.CNDIP = 1;
    //    Sub Priority: 0
        IPC2bits.CNDIS = 0;
    //    CCPI: CCP 5 Input Capture or Output Compare
    //    Priority: 1
        IPC20bits.CCP5IP = 1;
    //    Sub Priority: 0
        IPC20bits.CCP5IS = 0;
    //    CCTI: CCP 5 Timer
    //    Priority: 1
        IPC20bits.CCT5IP = 1;
    //    Sub Priority: 0
        IPC20bits.CCT5IS = 0;
    //    MICI: I2C 1 Master
    //    Priority: 1
        IPC16bits.I2C1MIP = 1;
    //    Sub Priority: 0
        IPC16bits.I2C1MIS = 0;
    //    SICI: I2C 1 Slave
    //    Priority: 1
        IPC16bits.I2C1SIP = 1;
    //    Sub Priority: 0
        IPC16bits.I2C1SIS = 0;
    //    TI: Timer 2
    //    Priority: 1
        IPC4bits.T2IP = 1;
    //    Sub Priority: 0
        IPC4bits.T2IS = 0;
    //    TI: Timer 1
    //    Priority: 1
        IPC4bits.T1IP = 1;
    //    Sub Priority: 0
        IPC4bits.T1IS = 0;
        
        IPC4bits.T3IP=1; //timer 3 prior & subprior
        IPC4bits.T3IS=0;
      
}
