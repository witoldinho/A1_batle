

// FDEVOPT
#pragma config SOSCHP = OFF    //Secondary Oscillator High Power Enable bit->SOSC oprerates in normal power mode.
#pragma config ALTI2C = OFF    //Alternate I2C1 Pins Location Enable bit->Primary I2C1 pins are used
#pragma config FUSBIDIO = OFF    //USBID pin control->USBID pin is controlled by the USB module
#pragma config FVBUSIO = OFF    //VBUS Pin Control->VBUS pin is controlled by the USB module

// FICD
#pragma config JTAGEN = OFF    //JTAG Enable bit->JTAG is disabled
#pragma config ICS = PGx1    //ICE/ICD Communication Channel Selection bits->Communicate on PGEC1/PGED1

// FPOR
#pragma config BOREN = BOR3    //Brown-out Reset Enable bits->Brown-out Reset enabled in hardware; SBOREN bit disabled
#pragma config RETVR = OFF    //Retention Voltage Regulator Enable bit->Retention regulator is disabled
#pragma config LPBOREN = ON    //Downside Voltage Protection Enable bit->Low power BOR is enabled, when main BOR is disabled

// FWDT
#pragma config SWDTPS = PS1048576    //Sleep Mode Watchdog Timer Postscale Selection bits->1:1048576
#pragma config FWDTWINSZ = PS25_0    //Watchdog Timer Window Size bits->Watchdog timer window size is 25%
#pragma config WINDIS = OFF    //Windowed Watchdog Timer Disable bit->Watchdog timer is in non-window mode
#pragma config RWDTPS = PS1048576    //Run Mode Watchdog Timer Postscale Selection bits->1:1048576
#pragma config RCLKSEL = LPRC    //Run Mode Watchdog Timer Clock Source Selection bits->Clock source is LPRC (same as for sleep mode)
#pragma config FWDTEN = OFF    //Watchdog Timer Enable bit->WDT is disabled

// FOSCSEL
#pragma config FNOSC = FRCDIV    //Oscillator Selection bits->FRCDIV
#pragma config PLLSRC = FRC    //System PLL Input Clock Selection bit->FRC oscillator is selected as PLL reference input on device reset
#pragma config SOSCEN = OFF    //Secondary Oscillator Enable bit->Secondary oscillator is disabled
#pragma config IESO = ON    //Two Speed Startup Enable bit->Two speed startup is enabled
#pragma config POSCMOD = OFF    //Primary Oscillator Selection bit->Primary oscillator is disabled
#pragma config OSCIOFNC = ON    //System Clock on CLKO Pin Enable bit->System clock is connected to CLKO/OSC2 pin
#pragma config SOSCSEL = ON    //Secondary Oscillator External Clock Enable bit->SCLKI pin configured for Digital mode
#pragma config FCKSM = CSECMD    //Clock Switching and Fail-Safe Clock Monitor Enable bits->Clock switching is enabled; Fail-safe clock monitor is disabled

// FSEC
#pragma config CP = OFF    //Code Protection Enable bit->Code protection is disabled

#include "pin_manager.h"
#include "clock.h"
#include "system.h"
#include "uart2.h"
#include "uart1.h"
#include "sccp5_compare.h"
#include "sccp4_compare.h"
#include "i2c1.h"
#include "sccp6_compare.h"
#include "interrupt_manager.h"
#include "exceptions.h"
#include "tmr1.h"
#include "tmr2.h"
#include "uart1.h"
#include "uart2.h"
#include "../zasob.h"

    void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    CLOCK_Initialize();
    SCCP4_COMPARE_Initialize();
    SCCP5_COMPARE_Initialize();
    SCCP6_COMPARE_Initialize();
    UART2_Initialize();
    I2C1_Initialize();
    UART1_Initialize();
    TMR2_Initialize();
    TMR1_Initialize();
    TMR3_Initialize();
    DMACONbits.ON=1; //dma ON 4kanały
    INTERRUPT_GlobalEnable();
}

/**
 End of File
////*/