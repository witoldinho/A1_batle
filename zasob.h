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

#define TIMER3_ON  T3CONbits.ON=1
#define TIMER3_OFF T3CONbits.ON=0

#define ramki_dbuf 8
#define kanals_dmx512 512
#define dbuf_fr_mask (ramki_dbuf-1)
#define UDP_RX_Mask (ramki_dbuf -1)
#define DMA_CH0_EN  DCH0CONSET=1<<7;
#define DMA_CH0_DIS  DCH0CONCLR=1<<7;
#define DMA_CH1_EN  DCH1CONSET=1<<7;
#define DMA_CH1_DIS  DCH1CONCLR=1<<7;

#define SYSTEMCLOCK 12000000

#define brejk_time 12
#define MAB_time brejk_time+2
// #define DMX_DIR_TX IO_RB11_SetHigh();

#define DMX_CHANNELS 512
extern  uint8_t channel_data[DMX_CHANNELS];
extern uint8_t datas[DMX_CHANNELS];

//
typedef union 
{
struct 
{
    uint32_t Timeout:1;
    uint32_t Ramka_OK:1;
    uint32_t Error:1;
    uint32_t Res:1;
    uint32_t Fflag:1;
    uint32_t Dummy:27;
};
uint32_t forbajt;

}DMX512_flagi;
extern DMX512_flagi D512_IF;

typedef union
  {
      struct
      {
          uint8_t DMA_RDY:1;
          uint8_t DMA_BSY:1;
          uint8_t DMA_BIS:1; // zmiana na kanał BIS
          uint8_t buf_EMPTY:1;
          uint8_t buf_FULL:1;
          uint8_t UART_RDY:1;
          uint8_t UART_BSY:1;
          uint8_t UART_ERR:1;
      };
      uint8_t bajt;
      
  }Flagi_DMAX512_t;  
  extern volatile Flagi_DMAX512_t DMA_CH0;
 //  extern volatile Flagi_DMAX512_t DMA_CH1;
  
  typedef union
  {
  struct
  {
      uint8_t Head;
      uint8_t Tail;
      uint8_t Bytes;
      uint8_t  Flaga_TX_END:1;
      uint8_t DMX_READY:1 ;
      uint8_t txtime:6;
  };
  uint32_t czterobajt;
  } snake ; 
   extern volatile snake waz;
   //extern volatile snake wezyk;

//#define DMX_DIR_TX IO_RB11_SetHigh();
//#define DMX_DIR_RX IO_RB11_SetLow();

//typedef enum  {tx_brk, tx_mab, tx_trans } Txstan ;     
// extern Txstan txstan;
//typedef enum {tx1_brk, tx1_mab, tx1_trans} TX1_STAN; 
//  extern TX1_STAN tx1_stan;
 //extern bool DMX_READY;
 //extern bool Flaga_TX_END;
 //extern uint8_t LHTtab[512];
 extern  uint8_t dbuf[ramki_dbuf][kanals_dmx512];
// extern uint8_t dbuf1[ramki_dbuf][kanals_dmx512];
//  extern volatile uint8_t UDP_RX_head ;
//extern volatile uint8_t UDP_RX_tail ; 
 extern uint16_t rozmiar;


#ifdef	__cplusplus
extern "C" {
#endif

  
   // */
    //void Transmit_DMX(uint8_t* data_OUT,uint16_t rozmiar);// na razie UART_1 , potem zmiana na drugi
 
    void DMX_OUT(void);
//    void DMX_OUT1(void);
//    uint8_t get_kolo(void);
//    void get_wezyk(void);
     void dmafun(uint8_t *buffer, int num_bytes);
//    void dmafun1(uint8_t *buffer, int num_bytes);
//    void dmafun02(uint8_t *buffer, int num_bytes);
//     void dmafun12(uint8_t *buffer, int num_bytes);
//    uint8_t udp_dmx_data_rdy( void);
//    uint8_t udp_dmx_wezyk_rdy(void);
    extern void __attribute__((used)) delayUs(unsigned int usec);
   extern void __attribute__((used)) delayMs(unsigned int usec);
//    void dmx_handel(void);
//    void aus_handel(void);
//    void Timer3_init(void);
//    void udp_handel(void);
//    void dma_stat(void);

