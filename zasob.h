/* 
 * File:   zasob.h
 * Author: Witek
 *
 * Created on June 16, 2020, 12:36 PM
 */

#include "mcc_generated_files/pin_manager.h"


#ifndef ZASOB_H
#define	ZASOB_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* ZASOB_H */

#define pin1_hi IO_RB10_SetHigh()
#define pin2_hi IO_RB11_SetHigh()
#define pin3_hi IO_RC3_SetHigh()
#define pin1_lo IO_RB10_SetLow()
#define pin2_lo IO_RB11_SetLow()
#define pin3_lo IO_RC3_SetLow()
#define pin1_tg IO_RB10_Toggle()
#define pin2_tg IO_RB11_Toggle()
#define pin3_tg IO_RC3_Toggle()

#define OK  1
#define NOK 0

#define DMX_CHANNELS 512

//
typedef union 
{
struct 
{
    uint32_t Timeout:1;
    uint32_t Ramka_OK:1;
    uint32_t Error:1;
    uint32_t Res:1;
    uint32_t Dummy:28;
};
uint32_t forbajt;

}DMX512_flagi;
extern DMX512_flagi D512_IF;
void TMR3_Initialize (void);