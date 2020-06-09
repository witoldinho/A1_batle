

#include <stdio.h>
#include "tmr2.h"

/**
 Section: File specific functions
*/
void (*TMR2_InterruptHandler)(void) = NULL;
void TMR2_CallBack(void);

/**
  Section: Data Type Definitions
*/

/** TMR Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

  Remarks:
    None.
*/

typedef struct _TMR_OBJ_STRUCT
{
    /* Timer Elapsed */
    volatile bool           timerElapsed;
    /*Software Counter value*/
    volatile uint8_t        count;

} TMR_OBJ;

static TMR_OBJ tmr2_obj;

/**
  Section: Driver Interface
*/

void TMR2_Initialize (void)
{
    // Period = 0.1 s; Frequency = 12000000 Hz; PR2 18749; 
    PR2 = 0x493D;
    //  TCKPS 1:64; T32 16 Bit; TCS PBCLK; SIDL disabled; TGATE disabled; ON enabled; 
    T2CON = 0x8060;    

    if(TMR2_InterruptHandler == NULL)
    {
        TMR2_SetInterruptHandler(&TMR2_CallBack);
    }

    IFS0CLR = _IFS0_T2IF_MASK;
    IEC0SET = _IEC0_T2IE_MASK;

    tmr2_obj.timerElapsed = false;

}



void __attribute__ ((vector(_TIMER_2_VECTOR), interrupt(IPL1SOFT))) TMR2_ISR()
{
    /* Check if the Timer Interrupt/Status is set */

    //***User Area Begin

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    if(TMR2_InterruptHandler) 
    { 
        TMR2_InterruptHandler(); 
    }

    //***User Area End

    tmr2_obj.count++;
    tmr2_obj.timerElapsed = true;
    IFS0CLR = _IFS0_T2IF_MASK;
}

void TMR2_Period16BitSet( uint16_t value )
{
    /* Update the counter values */
    PR2 = value;
    /* Reset the status information */
    tmr2_obj.timerElapsed = false;
}

uint16_t TMR2_Period16BitGet( void )
{
    return( PR2 );
}

void TMR2_Counter16BitSet ( uint16_t value )
{
    /* Update the counter values */
    TMR2 = value;
    /* Reset the status information */
    tmr2_obj.timerElapsed = false;
}

uint16_t TMR2_Counter16BitGet( void )
{
    return( TMR2 );
}


void __attribute__ ((weak)) TMR2_CallBack(void)
{
    // Add your custom callback code here
    IO_RB6_Toggle() ;
}

void  TMR2_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC0bits.T2IE = false;
    TMR2_InterruptHandler = InterruptHandler; 
    IEC0bits.T2IE = true;
}

void TMR2_Start( void )
{
    /* Reset the status information */
    tmr2_obj.timerElapsed = false;

    /*Enable the interrupt*/
    IEC0SET = _IEC0_T2IE_MASK;

    /* Start the Timer */
    T2CONSET = _T2CON_ON_MASK;
}

void TMR2_Stop( void )
{
    /* Stop the Timer */
    T2CONCLR = _T2CON_ON_MASK;

    /*Disable the interrupt*/
    IEC0CLR = _IEC0_T2IE_MASK;
}

bool TMR2_GetElapsedThenClear(void)
{
    bool status;
    
    status = tmr2_obj.timerElapsed;

    if(status == true)
    {
        tmr2_obj.timerElapsed = false;
    }
    return status;
}

int TMR2_SoftwareCounterGet(void)
{
    return tmr2_obj.count;
}

void TMR2_SoftwareCounterClear(void)
{
    tmr2_obj.count = 0; 
}

/**
 End of File
*/
