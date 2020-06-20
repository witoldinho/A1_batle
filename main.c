
#include "mcc_generated_files/system.h"
#include "zasob.h"

/*
                         Main application
 */
DMX512_flagi D512_IF;
volatile uint8_t channel_data[DMX_CHANNELS];

static void kickstart(void);

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    kickstart();
    while (1)
    {
        // Add your application code
      //  pin2_lo;
        if(D512_IF.Ramka_OK)
        {
            DMX_OUT_2();
        }
        
    }
    return 1; 
}

void kickstart(void)
{
        pin1_lo;
        pin2_lo;
        pin3_lo;
        D512_IF.forbajt=0x0;  
    
}

/**
 End of File
*/

