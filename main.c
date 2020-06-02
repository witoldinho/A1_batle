
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/uart1.h"

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    while (1)
    {
        // Add your application code
        UART1_Write(UART1_Read());
    }
    return 1; 
}
/**
 End of File
*/

