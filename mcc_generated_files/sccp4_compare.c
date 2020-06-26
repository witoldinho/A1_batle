

#include "sccp4_compare.h"
#include "../zasob.h"

/** OC Mode.

  @Summary
    Defines the OC Mode.

  @Description
    This data type defines the OC Mode of operation.

*/

static uint16_t         gSCCP4Mode;

/**
  Section: Driver Interface
*/


void SCCP4_COMPARE_Initialize (void)
{
    // ON enabled; MOD Dual Edge Compare; ALTSYNC disabled; SIDL disabled; OPS Each Time Base Period Match; CCPSLP disabled; TMRSYNC disabled; RTRGEN disabled; CCSEL disabled; ONESHOT disabled; TRIGEN disabled; T32 16 Bit; SYNC None; OPSSRC Timer Interrupt Event; TMRPS 1:64; CLKSEL SYSCLK; 
    CCP4CON1 = (0x80C4 & 0xFFFF7FFF); //Disabling CCPON bit
    //ASDGM disabled; ICGSM Level-Sensitive mode; ICS ICM4; SSDG disabled; AUXOUT Disabled; ASDG 0; PWMRSEN disabled; OCAEN enabled; OENSYNC disabled; 
    CCP4CON2 = 0x1000000;
    //OETRIG disabled; OSCNT None; POLACE disabled; PSSACE Tri-state; 
    CCP4CON3 = 0x00;
    //SCEVT disabled; TRSET disabled; ICOV disabled; ASEVT disabled; ICGARM disabled; RBWIP disabled; TRCLR disabled; RAWIP disabled; TMRHWIP disabled; TMRLWIP disabled; PRLWIP disabled; 
    CCP4STAT = 0x00;
    //TMRL 0; TMRH 0; 
    CCP4TMR = 0x00;
    //PRH 0; PRL 3750; 
    CCP4PR = 0xEA6;
    //CMPA 0; 
    CCP4RA = 0x00;
    //CMPB 512; 
    CCP4RB = 0x200;
    //BUFL 0; BUFH 0; 
    CCP4BUF = 0x00;

    CCP4CON1bits.ON = 0x1; //Enabling CCP

    gSCCP4Mode = CCP4CON1bits.MOD;
    // Clearing IF flag before enabling the interrupt.
    IFS2CLR= 1 << _IFS2_CCP4IF_POSITION;
    // Enabling SCCP4 interrupt.
    IEC2bits.CCP4IE = 1;

    // Clearing IF flag before enabling the interrupt.
    IFS2CLR= 1 << _IFS2_CCT4IF_POSITION;
    // Enabling SCCP4 interrupt.
    IEC2bits.CCT4IE = 1;
}

void __attribute__ ((weak)) SCCP4_COMPARE_CallBack(void)
{
    // Add your custom callback code here
 /*    if(D512_IF.Ramka_OK)
    {
        D512_IF.Ramka_OK=NOK;
        // SCCP4_COMPARE_DualEdgeBufferedConfig( 0,channel_data[2]*10  )  ;
        CCP4RB=10+channel_data[2]*10;
                 
    }
  * */
}

void __attribute__ ( ( vector ( _CCP4_VECTOR ), interrupt ( IPL1SOFT ))) CCP4_ISR (void)
{
    if(IFS2bits.CCP4IF)
    {
		// SCCP4 COMPARE callback function 
		SCCP4_COMPARE_CallBack();
		
        IFS2CLR= 1 << _IFS2_CCP4IF_POSITION;
    }
}

void __attribute__ ((weak)) SCCP4_COMPARE_TimerCallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ( ( vector ( _CCT4_VECTOR ), interrupt ( IPL1SOFT ))) CCT4_ISR (void)
{
    if(IFS2bits.CCT4IF)
    {
		// SCCP4 COMPARE Timer callback function 
		SCCP4_COMPARE_TimerCallBack();
	
        IFS2CLR= 1 << _IFS2_CCT4IF_POSITION;
    }
}

void SCCP4_COMPARE_Start( void )
{
    /* Start the Timer */
    CCP4CON1SET = (1 << _CCP4CON1_ON_POSITION);
}

void SCCP4_COMPARE_Stop( void )
{
    /* Start the Timer */
    CCP4CON1CLR = (1 << _CCP4CON1_ON_POSITION);
}

void SCCP4_COMPARE_SingleCompare16ValueSet( uint16_t value )
{   
    CCP4RA = value;
}


void SCCP4_COMPARE_DualCompareValueSet( uint16_t priVal, uint16_t secVal )
{

    CCP4RA = priVal;

    CCP4RB = secVal;
}

void SCCP4_COMPARE_DualEdgeBufferedConfig( uint16_t priVal, uint16_t secVal )
{

    CCP4RA = priVal;

    CCP4RB = secVal;
}

void SCCP4_COMPARE_CenterAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{

    CCP4RA = priVal;

    CCP4RB = secVal;
}

void SCCP4_COMPARE_EdgeAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{

    CCP4RA = priVal;

    CCP4RB = secVal;
}

void SCCP4_COMPARE_VariableFrequencyPulseConfig( uint16_t priVal )
{
    CCP4RA = priVal;
}

bool SCCP4_COMPARE_IsCompareCycleComplete( void )
{
    return(IFS2bits.CCP4IF);
}

bool SCCP4_COMPARE_TriggerStatusGet( void )
{
    return( CCP4STATbits.CCPTRIG );
    
}

void SCCP4_COMPARE_TriggerStatusSet( void )
{
    CCP4STATSET = (1 << _CCP4STAT_TRSET_POSITION);
}

void SCCP4_COMPARE_TriggerStatusClear( void )
{
    /* Clears the trigger status */
    CCP4STATCLR = (1 << _CCP4STAT_TRCLR_POSITION);
}

bool SCCP4_COMPARE_SingleCompareStatusGet( void )
{
    return( CCP4STATbits.SCEVT );
}

void SCCP4_COMPARE_SingleCompareStatusClear( void )
{
    /* Clears the trigger status */
    CCP4STATCLR = (1 << _CCP4STAT_SCEVT_POSITION);
    
}
/**
 End of File
*/
