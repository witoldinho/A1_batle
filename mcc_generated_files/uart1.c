
#include <xc.h>
#include <string.h>
#include <proc/PIC32MM-GPM-0XX/p32mm0256gpm048.h>
#include "uart1.h"
#include "../zasob.h"
//#include "uart2.h"



/**
  Section: UART1 APIs
*/

void UART1_Initialize(void)
{
    // Set the UART1 module to the options selected in the user interface.
 IEC1bits.U1TXIE = 0;
    IEC1bits.U1RXIE = 0;
    // STSEL 2; PDSEL 8N; RTSMD disabled; OVFDIS disabled; ACTIVE disabled; RXINV disabled; WAKE disabled; BRGH enabled; IREN disabled; ON enabled; SLPEN disabled; SIDL disabled; ABAUD disabled; LPBACK disabled; UEN TX_RX; CLKSEL PBCLK; 
    // Data Bits = 8; Parity = None; Stop Bits = 2;
    U1MODE = (0x8009 & ~(1<<15));  // disabling UARTEN bit
    // UTXISEL TX_ONE_CHAR; UTXINV disabled; ADDR 0; MASK 0; URXEN disabled; OERR disabled; URXISEL RX_ONE_CHAR; UTXBRK disabled; UTXEN disabled; ADDEN disabled; 
    U1STA = 0x00;
    // BaudRate = 250000; Frequency = 12000000 Hz; BRG 11; 
    U1BRG = 0x0B;
    
        IEC1bits.U1RXIE = 1;
    //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U1STASET = _U1STA_UTXEN_MASK;
    U1MODESET = _U1MODE_ON_MASK;   // enabling UART ON bit
    U1STASET = _U1STA_URXEN_MASK;
}

uint8_t UART1_Read(void)
{
    while(!(U1STAbits.URXDA == 1))
    {
        
    }

    if ((U1STAbits.OERR == 1))
    {
        U1STACLR = _U1STA_OERR_MASK;
    }
    
    return U1RXREG;
}

void UART1_Write(uint8_t txData)
{
    while(U1STAbits.UTXBF == 1)
    {
        
    }

    U1TXREG = txData;    // Write the data byte to the USART.
}

bool UART1_IsRxReady(void)
{
    return U1STAbits.URXDA;
}

bool UART1_IsTxReady(void)
{
    return ((!U1STAbits.UTXBF) && U1STAbits.UTXEN );
}

bool UART1_IsTxDone(void)
{
    return U1STAbits.TRMT;
}

void __attribute__ ((vector(_UART1_RX_VECTOR), interrupt(IPL1SOFT))) _UART1_RX( void )
{
    static enum {DS_BREAK, DS_START , DS_DATA} dmxstate=DS_BREAK;//dmxstate
    static uint16_t cd_addr=0;
  //  pin2_hi;
    
   // volatile uint8_t c= U1RXREG;
 //   while(U1STAbits.URXDA == 1);
        
    
   // uint32_t s=(uint32_t)U1STA;
     if(U1STAbits.FERR==1 )
     {
       // pin1_hi;
        D512_IF.Fflag=OK;
        D512_IF.Ramka_OK=NOK;
        D512_IF.Timeout=NOK;
        dmxstate=DS_BREAK;
        TIMER3_ON ; //        T3CONbits.ON=1; 
        
       //  pin1_hi;
     }
   while(U1STAbits.URXDA == 0);
    
         
             if(dmxstate==DS_BREAK && D512_IF.Fflag)
             {
                  if(U1STAbits.URXDA == 1)
                    {
                       
                        if(!U1RXREG)
                        {
                            dmxstate=DS_START;
                            
                        }
                        else
                        {
                            dmxstate=DS_BREAK;
                            
                            
                        }
                    }
             }   
                  
             switch(dmxstate)
             {
                 case DS_START:
                   
               //   pin2_hi;
                      D512_IF.Fflag=NOK;
                      pin2_hi;
                      if(D512_IF.Timeout)
                      {
                          dmxstate=DS_BREAK;
                          TIMER3_OFF;
                          D512_IF.Timeout=NOK;
                      }
                          else
                          {
                          dmxstate=DS_DATA;
                        
                          } 
                 
                      break;
                 case   DS_DATA:
                     channel_data[cd_addr++]=U1RXREG;
                            pin3_hi;
                            if(cd_addr==DMX_CHANNELS)
                            {
                                D512_IF.Ramka_OK=OK;
                              //  memcpy(datas,channel_data,DMX_CHANNELS);
                                dmxstate=DS_BREAK;
                            }
                     break;
                      
             }
             
   
     
      piny_lo();
        IFS1CLR= 1 << _IFS1_U1RXIF_POSITION;
    
}      

/*void __attribute__ ((vector(_UART1_RX_VECTOR), interrupt(IPL1SOFT))) _UART1_RX( void )
{
    static enum {DS_BREAK, DS_START , DS_DATA} dmxstate=DS_BREAK;//dmxstate
    static uint16_t cd_addr=0;
    //pin1_hi;
    
    volatile uint8_t c;
 //   while(U1STAbits.URXDA == 1);
        
    
   // uint32_t s=(uint32_t)U1STA;
      
    
     if(U1STAbits.FERR==1 )
     {
        pin1_hi;
        D512_IF.Fflag=OK;
        D512_IF.Ramka_OK=NOK;
        D512_IF.Timeout=NOK;
        dmxstate=DS_BREAK;
        TIMER3_ON ; //        T3CONbits.ON=1; 
       // while (U1STAbits.URXDA == 0);
        //  IFS1CLR= 1 << _IFS1_U1RXIF_POSITION;
       //  piny_lo();
       //  pin1_hi;
     }
     
 // while( U1STAbits.URXDA==0);
    
    // c= UART1_Read();
          while (U1STAbits.URXDA == 1)
          {
              pin2_hi;
              
          }
    
                c=U1RXREG; 
    
    
         
             if(dmxstate==DS_BREAK && D512_IF.Fflag )
             {                  
                        if(!c)
                        {
                            dmxstate=DS_START;                  
                        }
                        else
                        {
                            dmxstate=DS_BREAK; 
                        }
             }      
     
                     switch(dmxstate)
             {
                 case DS_START:
                   
                  pin2_hi;
                      D512_IF.Fflag=NOK;
                     
                      if(D512_IF.Timeout)
                      {
                          dmxstate=DS_BREAK;
                          TIMER3_OFF;
                          D512_IF.Timeout=NOK;
                      }
                          else
                          {
                          dmxstate=DS_DATA;
                        
                          } 
                 
                      break;
                 case   DS_DATA:
                     channel_data[cd_addr++]=c;
                            
                            if(cd_addr==DMX_CHANNELS)
                            {
                                D512_IF.Ramka_OK=OK;
                              //  memcpy(datas,channel_data,DMX_CHANNELS);
                                dmxstate=DS_BREAK;
                                pin3_hi;
                            }
                     break;
                      
             }
        
      
    
    
    piny_lo();
        IFS1CLR= 1 << _IFS1_U1RXIF_POSITION;
}
         
    */
 //   volatile uint8_t c= U1RXREG;
    //UART2_Write(c);
     
     
     //if(U1STAbits.PERR) pin2_hi;
    // if(!c)pin2_hi;
  /*   
    if(U1STAbits.FERR==1 )
    {
        T3CONbits.ON=1;
        dmxstate=c?DS_BREAK:DS_START;
       // pin1_tg;
        pin1_hi;
    }
    else
    {
       if(D512_IF.Timeout) // IFS0bits.T3IF przepełnienie licznika t3
       {
           dmxstate=DS_BREAK;
      //     IFS0bits.T3IF=0;
           
           T3CONbits.ON=0;
           D512_IF.Timeout=0;
          // pin2_tg;
         //  pin2_hi;
       }
     switch(dmxstate)
     {
         case DS_START:
             dmxstate=c?DS_BREAK:DS_DATA;
             
             break;
             
         case DS_DATA:
             channel_data[cd_addr]=c;
             if(++cd_addr==DMX_CHANNELS)
             {
                 dmxstate=DS_BREAK;
             }
             
             break;
             
         default:
             break;
         
     }
     if(dmxstate!=DS_DATA && cd_addr)
     {
     //    UART2_Write(channel_data[1]);
         //CCP4RB=10+channel_data[1]*(10);
         //CCP5RB=10+channel_data[2]*(10);
         //CCP6RB=10+channel_data[3]*(10);
       //  pin3_tg;
        
         
         cd_addr=0;
     }
     
       
        
    }
   */ 
 


/*******************************************************************************

  !!! Deprecated API !!!
  !!! These functions will not be supported in future releases !!!

*******************************************************************************/

uint32_t __attribute__((deprecated)) UART1_StatusGet (void)
{
    return U1STA;
}

void __attribute__((deprecated)) UART1_Enable(void)
{
    U1STASET = _U1STA_UTXEN_MASK;
    U1STASET = _U1STA_URXEN_MASK;
    U1MODESET = _U1MODE_ON_MASK;
}

void __attribute__((deprecated)) UART1_Disable(void)
{
    U1STACLR = _U1STA_UTXEN_MASK;
    U1STACLR = _U1STA_URXEN_MASK;
    U1MODECLR = _U1MODE_ON_MASK;
}

inline void piny_lo(void)
{
      pin1_lo;
    pin2_lo;
    pin3_lo;  
}
 