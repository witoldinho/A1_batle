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
        UART2_Write(channel_data[x]); 
    }
   
    
}


void __attribute__ ( ( vector ( _DMA0_VECTOR ) , interrupt ( IPL1SOFT ) ) ) DMA0_ISR( void )
{
    DMA_CH0.DMA_BSY=0;
//    DMA_CH0.DMA_RDY=0;
//    DMA_CH0.UART_BSY=0;
//    DMA_CH0.UART_RDY=0;
  //  DMA_CH0.buf_FULL=0;
    
//    waz.Flaga_TX_END=1; // Flaga_TX_END=true;
    
   DMA_CH0_DIS; // DCH0CONCLR=1<<7;
    
    
   DCH0INTCLR = 0xFF;
#ifdef p12R40
   LED2_OFF;
#endif
#ifdef p12r50
   LED0_OFF;
#endif
   
//   DMA_CH0.DMA_BIS=1; // zmiana na dch0/2
    //Clear flag
    IFS3CLR= 1 << _IFS3_DMA0IF_POSITION;
}


void dmafun(uint8_t *buffer, int num_bytes)
{
    //DMA_BUSY=1;
 //   IFS0bits.T2IF=0;
   DMA_CH0.DMA_BSY=1;
    
    IEC3bits.DMA0IE = 0 ; /*disable DMA0 interrupt, datasheet page 66*/
IFS3bits.DMA0IF = 0 ; /*clear any existing DMA channel 0 interrupt flag, datasheet page 66*/

//DMACONbits.ON = 1; /*enable the DMA controller*/
DCH0CONbits.CHEN = 0; /* channel off*/
DCH0CONbits.CHPRI = 3; /*channel priority 3*/
//DCH0CONbits.CHAEN=1; 

DCH0ECON=0; /*no start or stop IRQs, no pattern match*/
DCH0ECONbits.CHSIRQ=17 ;//_timer
//DCH0ECONbits.CHAIRQ = _UART1_ERR_VECTOR;

DCH0SSA = ((uint32_t)buffer & 0x1FFFFFFF); // Convert virtual address to physical address
DCH0DSA = ((uint32_t)&U2TXREG & 0x1FFFFFFF); // Convert virtual address to physical address

DCH0SSIZ = 512 ;//num_bytes; /*source size*/
DCH0DSIZ = 1; /*desination size, one byte per SPI transfer */
DCH0CSIZ = 1; //sizeof(tab2); /*cell size*/

DCH0INTCLR = 0xFF;      /*clear existing all Interrupt flag*/
//DCH0INTbits.CHCCIE = 1; /*Channel Cell Transfer Complete Interrupt Enable bit*/
DCH0INTbits.CHSDIE=1;
//DCH0INTbits.CHDDIE=1;
DCH0ECONbits.SIRQEN=1;
 DCH0ECONbits.AIRQEN=0; 

IPC24bits.DMA0IP = 1 ; /*set interrupt priority*/
IPC24bits.DMA0IS = 0 ; /*set interrupt subpriority*/
DCH0CONbits.CHEN = 0; /*channel on*/
 
 IEC3bits.DMA0IE = 1; /*enable DMA0 interrupt, datasheet page 66*/
 IFS3bits.DMA0IF = 0;
//IEC0bits.T2IE=1;
//IFS0bits.T2IF=0;
// DMA_CH0.UART_RDY=1;
// DMA_CH0.DMA_RDY=1;
// DMA_CH0.DMA_BSY=0;
}

void DMX_OUT(void)
{
  //   uint16_t kanal=0;
  //  uint8_t dupa; // keine dupa
    delayUs(100);
     while(!U1STAbits.TRMT);
    waz.DMX_READY=1; // true =1
#ifdef p12R40
    LED2_ON; 
#endif
    
#ifdef p12r50
    LED0_ON;
#endif
    
     
    
 /*   switch(txstan)
    {
        case tx_brk:
          //  U1STAbits.UTXINV=1;
            break;
        case tx_mab:
     //      U1STAbits.UTXINV=0;
         //  txstan=tx_trans;
           
            break;
        case tx_trans:
  */
     U1STAbits.UTXINV=1;
   //  DMX_DIR_TX;
    delayUs(176);
   // while(TMR1_SoftwareCounterGet()<V_BREAK);
    U1STAbits.UTXINV=0;
    delayUs(16);
           
           //  U1STAbits.UTXINV=0;
             UART1_Write(0);
             
            DMA_CH0_EN; //DCH0CONSET=1<<7;   
             DMA_CH0.DMA_RDY=0;
             DMA_CH0.UART_RDY=0;
//             break;
    //
}

 void __attribute__((used)) delayUs(unsigned int usec)
{
    unsigned int tWait, tStart;

    tWait=(SYSTEMCLOCK/2000000)*usec; 
    tStart=_mfc0(9,0);
    while((_mfc0(9,0)-tStart)<tWait);        // wait for the time to pass
}

  void __attribute__((used)) delayMs(unsigned int usec)
{
    unsigned int tWait, tStart;

    tWait=(SYSTEMCLOCK/2000)*usec; 
    tStart=_mfc0(9,0);
    while((_mfc0(9,0)-tStart)<tWait);        // wait for the time to pass
}