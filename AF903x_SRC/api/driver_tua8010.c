/* ============================================================================
** Copyright (C) 1997-2008 Infineon AP All rights reserved.
** ============================================================================
**
** ============================================================================
** Revision Information :
**    File name: driver_tua8010.c
**    Version: V0.1
**    Date: 2008.08.17
**
** ============================================================================
** History: 
** 
** Date         Author  Comment
** ----------------------------------------------------------------------------
**
** 2007.11.06   Walter Pichler    created.
** 2008.08.15   Xie Yonggang      adaption to TUA8010
** ============================================================================
*/

/*============================================================================
Includes
============================================================================*/

#include "driver_tua8010.h"
#include "driver_tua8010_NeededFunctions.h"   /* Note: This function have to be provided by the user */

/*============================================================================
Local compiler keeys         ( usage depends on the application )
============================================================================*/

#define CRYSTAL_26_MHZ
//#define CRYSTAL_19.2_MHZ
//#define CRYSTAL_20.48_MHZ

//#define AGC_BY_IIC
//#define AGC_BY_AGC_BUS
//#define AGC_BY_EXT_PIN


/*============================================================================
Named Constants Definitions    ( usage depends on the application )
============================================================================*/

#define TUNERs_TUA8010_DEVADDR    0xC2

/* Note: The correct device address depends hardware settings. See Datasheet
      and User Manual for details. */

/*============================================================================
Local Named Constants Definitions
============================================================================*/
#define		OPERATIONAL_MODE     	0x03 
#define		CHANNEL_BANDWITH    	0x04
#define		SW_CONTR_TIME_SLICING	0x05
#define		BASEBAND_GAIN_CONTROL	0x06
#define		MANUAL_BASEBAND_GAIN	0x0b
#define		REFERENCE_FREQUENCY 	0x1d
#define		CHANNEL_WORD        	0x1f
#define		CHANNEL_OFFSET	    	0x20
#define		CHANNEL_FILTER_TRIMMING	0x2f
#define		OUTPUT_BUFFER	    	0x32
#define		RF_AGC_CONFIG_A	    	0x36
#define		RF_AGC_CONFIG_B	    	0x37
#define		UHF_LNA_SELECT	    	0x39
#define		LEVEL_DETECTOR	    	0x3a
#define		MIXER_CURRENT	    	0x3b
#define		PORT_CONTROL		    0x3e
#define		CRYSTAL_TRIMMING    	0x41
#define		CHANNEL_FILTER_STATUS	0x60
#define		SIG_STRENGHT_INDICATION	0x62
#define		PLL_LOCK	        	0x69
#define		RECEIVER_STATE	    	0x70
#define		RF_INPUT	        	0x71
#define		BASEBAND_GAIN	    	0x72
#define		CHIP_IDENT_CODE	    	0x7e
#define		CHIP_REVISION	    	0x7f

#define TUNERs_TUA8010_BW_8         0xcf
#define TUNERs_TUA8010_BW_7         0x10
#define TUNERs_TUA8010_BW_6         0x20
#define TUNERs_TUA8010_BW_5         0x30




/*============================================================================
 Types definition
============================================================================*/




/*============================================================================
 Public Functions
============================================================================*/


/**
 * tuner initialisation
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/
 
int initializeTUA8010(void)
{
  unsigned int counter;
  char i2cseq[2];
  tunerReceiverState_t tunerState;

  setRXEN8010   (L_LEVEL);    /* de-asserting RXEN   */
  
  setRESETN8010 (L_LEVEL);    /* de-asserting RESET   */
  
  /* Note: CEN may also be hard wired in the application*/
  setCEN8010    (L_LEVEL);    /* de-asserting Chip enable      */
  
  /* Note: 20µs assumes that all external power supplies are settled. If not, add more time here */
  waitloop8010 (20);          /* wait for 20 uS     */
 
  /* Note: CEN may also be hard wired in the application*/
  setCEN8010    (H_LEVEL);    /* asserting Chip enable      */
 
   /* Note: 20µs assumes that all external power supplies are settled. If not, add more time here */
  waitloop8010 (20);          /* wait for 20 uS     */
   
  setRESETN8010 (H_LEVEL);    /* asserting RESET */

  counter = 7;
  do
    {
    counter --;
    waitloop8010 (1000);      /* wait for 1 mS      */

    }while ((counter));

  /* PGF */  
  i2cseq[0] = 0x00;     
  i2cseq[1] = 0x00;   
  i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x0D, i2cseq, 2); 

  /* Xtal */
  i2cseq[0] = 0x00;
  i2cseq[1] = 0x30;    
  i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x1D, i2cseq, 2);
  
  /* VCO */  
  i2cseq[0] = 0x88;     
  i2cseq[1] = 0x7A;   
  i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x25, i2cseq, 2); 

  /* LNA */
  i2cseq[0] = 0x1c;      
  i2cseq[1] = 0x00;
  i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x2C, i2cseq, 2);

  /* Channel Filter */  
  i2cseq[0] = 0x00;     
  i2cseq[1] = 0x70;   
  i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x32, i2cseq, 2);

  /* Channel Filter */
  i2cseq[0] = 0x02;     
  i2cseq[1] = 0x40;                     
  i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x34, i2cseq, 2);  
 
  /* Low Pwr LNA*/
  i2cseq[0] = 0xC0;      
  i2cseq[1] = 0x13;
  i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x36, i2cseq, 2);
  
  /* RF AGC Release */  
  i2cseq[0] = 0x0F;     
  i2cseq[1] = 0x98;   
  i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x37, i2cseq, 2);

  setRXEN8010   (H_LEVEL);    /* RXEN to low >> IDLE STATE  */
  
  
  return TUNER_OK;
}



/**
 * tuner tune
 * @param IN i_freq   tuning frequency
 * @param IN i_bandwidth  channel  bandwidth
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/

int tuneTUA8010(long i_freq, tunerDriverBW_t i_bandwidth)
{
  char i2cseq[2];
  unsigned int divider_factor;
  unsigned int ch_offset;
  unsigned int counter;
  unsigned int lo_path_settings;
  tunerReceiverState_t tunerState;

 
  /* de-assert RXEN >> IDLE STATE */
  setRXEN8010   (L_LEVEL);          
 

  /* calculate divider factor */
  if (i_freq < 1000000)    /*  divider factor and channel offset for UHF/VHF III */
   {
   ch_offset = 0x1C20;     /* channel offset 150 MHz */
   divider_factor   =  (unsigned int) (((i_freq - 150000) * 48) / 1000);
   lo_path_settings = 0xb6de;
  }

  else                     /* calculate divider factor for L-Band Frequencies */
   {
   ch_offset = 0x5460;     /* channel offset 450 MHz */
   divider_factor   =  (unsigned int) (((i_freq - 450000) * 48) / 1000);
   lo_path_settings = 0xbede;
   }


  // Set for GPIO_0 control
  if (i_freq >= 170000 && i_freq <= 250000)
  {
      i2cseq[0] = 0x51;
      i2cseq[1] = 0x42;
      i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x3E, i2cseq, 2);
  }
  else if (i_freq >= 470000 && i_freq <= 860000)
  {
      i2cseq[0] = 0x5D;
      i2cseq[1] = 0x72;
      i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x3E, i2cseq, 2);
  }

  // Set LO Path
  i2cseq[0] = lo_path_settings >> 8;
  i2cseq[1] = lo_path_settings & 0xff;
  i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x2b, i2cseq, 2);

  // Set channel offset
  i2cseq [0] =  ch_offset >> 8;
  i2cseq [1] =  ch_offset & 0xff;
  i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x20, i2cseq, 2);
  
  // Set Frequency
  i2cseq [0] =  divider_factor >> 8;
  i2cseq [1] =  divider_factor & 0xff;
  i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x1f, i2cseq, 2);
   
  // Set bandwidth
  i2cBusRead8010 (TUNERs_TUA8010_DEVADDR,  0x04, i2cseq, 2);         /* get current register value */
  i2cseq [0] &= TUNERs_TUA8010_BW_8;
 
  switch (i_bandwidth)
    {
    case TUNER_BANDWIDTH_7MHZ: i2cseq [0] |= TUNERs_TUA8010_BW_7;
         break; 
    case TUNER_BANDWIDTH_6MHZ: i2cseq [0] |= TUNERs_TUA8010_BW_6;
         break; 
    case TUNER_BANDWIDTH_5MHZ: i2cseq [0] |= TUNERs_TUA8010_BW_5;
         break; 
    }

  i2cBusWrite8010 (TUNERs_TUA8010_DEVADDR, 0x04, i2cseq, 2);
 
  /* assert RXEN >> RX STATE */
  setRXEN8010   (H_LEVEL);

  counter = 5;
  do
    {
    counter --;
    waitloop8010 (1000);         /* wait for 1 mS      */
    }while ((counter));

  return TUNER_OK;
}


/**
 * Get pll locked state
 * @param OUT o_pll  pll locked state
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/

int getPllLockedStateTUA8010(tunerPllLocked_t *o_pll)
{
  char i2cseq[2];

  i2cBusRead8010 (TUNERs_TUA8010_DEVADDR, 0x69, i2cseq, 2);           /* get current register value */
  
  o_pll[0]  = (i2cseq[1] & 0x08) ? PLL_LOCKED : PLL_NOT_LOCKED;
 
  return TUNER_OK;
}


/**
 * Get tuner state
 * @param OUT o_tunerState tuner state
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/

int getReceiverStateTUA8010(tunerReceiverState_t *o_tunerState)
{
  char i2cseq[2];

  i2cBusRead8010 (TUNERs_TUA8010_DEVADDR, 0x70, i2cseq, 2);           /* get current register value */

  switch (i2cseq[1] & ~0x1f)
     {
     case 0x80: o_tunerState [0] = IDLE;  break;
     case 0x40: o_tunerState [0] = RX;    break;
     case 0x20: o_tunerState [0] = STANDBY; 
     }
 
  return TUNER_OK;
}


/**
 * Get active input
 * @param OUT o_activeInput active input info
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/
 
int getActiveInputTUA8010(tunerActiveInput_t *o_activeInput)
{
  char i2cseq[2];

  i2cBusRead8010 (TUNERs_TUA8010_DEVADDR, 0x71, i2cseq, 2);           /* get current register value */

  switch (i2cseq[1] & ~0x0f)
     {
     case 0x80: o_activeInput [0] = Internal_UHF_LNA; break;
     case 0x40: o_activeInput [0] = External_UHF_LNA; break;
     case 0x20: o_activeInput [0] = Internal_VHF_LNA; break;
     case 0x10: o_activeInput [0] = External_VHF_LNA; 
     }
 
  return TUNER_OK;
}


/**
 * Get baseband gain value
 * @param OUT o_basebandGain  baseband gain value
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int getBasebandGainTUA8010(char *o_basebandGain)
{
  char i2cseq[2];

  i2cBusRead8010 (TUNERs_TUA8010_DEVADDR, 0x72, i2cseq, 2);           /* get current register value */
  o_basebandGain [0] = i2cseq [1];
 
  return TUNER_OK;
}
