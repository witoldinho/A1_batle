

#ifndef _SCCP4_COMPARE_H
#define _SCCP4_COMPARE_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>


#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
/**
  Section: Interface Routines
*/

/**
  @Summary
    This function initializes MCCP/SCCP instance : 4

  @Description
    This routine initializes the SCCP4 driver instance for : 4
    index, making it ready for clients to open and use it.
    This routine must be called before any other SCCP4 routine is called.
	
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Comment
    
 
  @Example
    <code>
    uint16_t priVal,secVal;
    bool completeCycle = false;
    priVal = 0x1000;
    secVal = 0x2000;

    SCCP4_COMPARE_Initializer();
    
    SCCP4_COMPARE_CenterAlignedPWMConfig( priVal, secVal );
  
    SCCP4_COMPARE_Start();

    while(1)
    {
       
        completeCycle = SCCP4_COMPARE_IsCompareCycleComplete( void );
        if(completeCycle)
        {
            SCCP4_COMPARE_Stop();
        }
    }
    </code>
*/

void SCCP4_COMPARE_Initialize (void);


/**
  @Summary
    Callback for SCCP4 COMPARE.

  @Description
    This routine is callback for SCCP4 COMPARE

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to SCCP4_Initialize(); for an example
*/
void SCCP4_COMPARE_CallBack(void);


/**
  @Summary
    Callback for SCCP4 COMPARE Timer.

  @Description
    This routine is callback for SCCP4 COMPARE Timer

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to SCCP4_Initialize(); for an example
*/
void SCCP4_COMPARE_TimerCallBack(void);


/**
  @Summary
    Enables the OC module with the corresponding operation mode.

  @Description
    This routine enables the OC module with the corresponding operation mode.

  @Preconditions
    SCCP4_COMPARE_Initializer function should have been called 

  @Param
    None.
 
  @Returns
    None.

  @Example 
    Refer to SCCP4_COMPARE_Initializer() for an example	
 
*/

void SCCP4_COMPARE_Start( void );

/**
  @Summary
    Disables the OC module.

  @Description
    This routine disables the OC module.

  @Preconditions
    SCCP4_COMPARE_Initializer function should have been called 

  @Param
    None.

  @Returns
    None.

*/

void SCCP4_COMPARE_Stop( void );
/**
  @Summary
    Sets the primary compare value.

  @Description
    This routine sets the primary compare value.

  @Preconditions
    SCCP4_COMPARE_Initializer function should have been called 

  @Param
    value - 16 bit primary compare value.

  @Returns
    None.

  @Example 
    <code>
        uint16_t value = 0x1000;
        SCCP4_COMPARE_SingleCompareValueSet( value );
    <code>
	
*/
void SCCP4_COMPARE_SingleCompare16ValueSet( uint16_t value );

/**
  @Summary
    Sets the primary and secondary compare value.

  @Description
    This routine sets the primary and secondary compare value.

  @Preconditions
    SCCP4_COMPARE_Initializer function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	

  @Returns
    None.

  @Example 
    <code>
        uint16_t priVal = 0x1000;
        uint16_t secVal = 0x2000;
        SCCP4_COMPARE_DualCompareValueSet( priVal,secVal );
    <code>
  	
*/

void SCCP4_COMPARE_DualCompareValueSet( uint16_t priVal, uint16_t secVal );

/**
  @Summary
    Sets the primary and secondary compare value for Dual Edge Buffered mode.

  @Description
    This routine sets the primary and secondary compare value for for Dual Edge Buffered mode.

  @Preconditions
    SCCP4_COMPARE_Initializer function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	
	
  @Returns
    None.

  @Example 
    <code>
        uint16_t priVal = 0x1000;
        uint16_t secVal = 0x2000;
        void SCCP4_COMPARE_DualEdgeBufferedConfig( priVal, secVal );
    <code>
*/

void SCCP4_COMPARE_DualEdgeBufferedConfig( uint16_t priVal, uint16_t secVal );

/**
  @Summary
    Sets the primary and secondary compare value for Center Aligned PWM

  @Description
    This routine sets the primary and secondary compare value for Center Aligned PWM.

  @Preconditions
    SCCP4_COMPARE_Initializer function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	
	
  @Returns
    None.

  @Example 
    Refer to SCCP4_COMPARE_Initializer() for an example

*/

void SCCP4_COMPARE_CenterAlignedPWMConfig( uint16_t priVal, uint16_t secVal );

/**
  @Summary
    Sets the primary and secondary compare value for Edge Aligned PWM.

  @Description
    This routine sets the primary and secondary compare value for Edge Aligned PWM.

  @Preconditions
    SCCP4_COMPARE_Initializer function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	

  @Returns
    None.

  @Example 
    <code>
        uint16_t priVal = 0x1000;
        uint16_t secVal = 0x2000;
        SCCP4_COMPARE_EdgeAlignedPWMConfig( priVal,secVal );
    <code> 
 	
*/

void SCCP4_COMPARE_EdgeAlignedPWMConfig( uint16_t priVal, uint16_t secVal );

/**
  @Summary
    Sets the primary compare value for Variable Frequency Pulse mode.

  @Description
    This routine sets the primary compare value for Frequency Pulse mode.

  @Preconditions
    SCCP4_COMPARE_Initializer function should have been called 

  @Param
    priVal - 16 bit primary compare value.

  @Returns
    None.

  @Example 
    <code>
        uint16_t priVal = 0x1000;
        void SCCP4_COMPARE_VariableFrequencyPulseConfig( priVal );
    <code> 
*/

void SCCP4_COMPARE_VariableFrequencyPulseConfig( uint16_t priVal );

/**
  @Summary
    Gets the status of the compare cycle completion.

  @Description
    This routine gets the status of the compare cycle completion.

  @Preconditions
    SCCP4_COMPARE_Initializer function should have been called 

  @Param
    None.

  @Returns
    Boolean value describing the current status of the cycle completion. Returns
    true  : When the compare cycle has completed. 
    false : When the compare cycle has not completed. 

  @Example 
    Refer to SCCP4_COMPARE_Initializer() for an example
	

*/

bool SCCP4_COMPARE_IsCompareCycleComplete( void );

/**
  @Summary
    Gets the status of the timer trigger.

  @Description
    This routine gets the status of the timer trigger source if it has been triggered.
	
  @Preconditions
    SCCP4_COMPARE_Initializer function should have been called 
	
  @Param
    None
	
  @Returns
    Boolean value describing the timer trigger status.
    true  : When the timer source has triggered and is running 
    false : When the timer has not triggered and being held clear 

   @Example 
    <\code>	
    if(SCCP4_COMPARE_TriggerStatusGet())
    {
        SCCP4_COMPARE_TriggerStatusClear();
    }
    <\code>	
*/

bool SCCP4_COMPARE_TriggerStatusGet( void );

/**
  @Summary
    Sets the status of the timer trigger.

  @Description
    This routine sets the status of the timer trigger source.
	
  @Preconditions
    SCCP4_COMPARE_Initializer function should have been called 
	
  @Param
    None.
	
  @Returns
    None.

   @Example 
    <\code>	
        SCCP4_COMPARE_TriggerStatusSet();
    <\code>	
*/

void SCCP4_COMPARE_TriggerStatusSet( void );

/**
  @Summary
    Clears the status of the timer trigger.

  @Description
    This routine clears the status of the timer trigger.
	
  @Preconditions
    SCCP4_COMPARE_Initializer function should have been called

  @Param
    None.

  @Returns
    None.
	
  @Example 
    Refer to SCCP4_COMPARE_TriggerStatusGet() for an example	

*/

void SCCP4_COMPARE_TriggerStatusClear( void );

/**
  @Summary
    Gets the status of the timer trigger.

  @Description
    This routine gets the status of the timer trigger source if it has been triggered.

  @Param
    None.

  @Returns
    Gets the status of the single compare set
*/

bool SCCP4_COMPARE_SingleCompareStatusGet( void );

/**
  @Summary
    Clears the status of the timer trigger source.

  @Description
    This routine clears the status of the timer trigger source.

  @Param
    None.

  @Returns
    None.
*/

void SCCP4_COMPARE_SingleCompareStatusClear( void );

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_SCCP4_H
    
/**
 End of File
*/
