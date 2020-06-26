
#include "mcc_generated_files/system.h"
#include "zasob.h"
#include "mcc_generated_files/uart2.h"

/*
                         Main application
 */
DMX512_flagi D512_IF;
uint8_t channel_data[DMX_CHANNELS];

uint8_t datas[DMX_CHANNELS];

volatile snake waz;
volatile Flagi_DMAX512_t DMA_CH0;

static void kickstart(void);
static void outd(void);
void dm(void);
void cccp(void);


int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    kickstart();
    while (1)
    {
     // outd();
     //   dm();
      // cccp();
    //  delayMs(2);
       //UART2_Write('A');
      //  pin2_lo;
    
//   * */
        
    }
    return 1; 
}

void kickstart(void)
{
        pin1_lo;
        pin2_lo;
        pin3_lo;
        D512_IF.forbajt=0x0; 
        DMA_CH0.bajt=0;
    
}

void outd(void)
{
 if(D512_IF.Ramka_OK && !DMA_CH0.DMA_BSY)
      {
        D512_IF.Ramka_OK=NOK;
         dmafun(channel_data, DMX_CHANNELS);
         DMA_CH0_EN;
      }
    
}

void dm(void)
{
    if( !DMA_CH0.DMA_BSY)
    {
        dmafun(datas, DMX_CHANNELS);
           DMA_CH0_EN;
    }
         
}

void cccp(void)
{
    if(D512_IF.Ramka_OK)
    {
        D512_IF.Ramka_OK=NOK;
        // SCCP4_COMPARE_DualEdgeBufferedConfig( 0,channel_data[2]*10  )  ;
       SCCP4_COMPARE_DualCompareValueSet( 0, 10+channel_data[2]*10 );

                 
    }
    
}
/**
 End of File
*/

