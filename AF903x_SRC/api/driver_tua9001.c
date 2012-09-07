/* ============================================================================
** Copyright (C) 1997-2007 Infineon AG All rights reserved.
** ============================================================================
**
** ============================================================================
** Revision Information :
**    File name: driver_tua9001.c
**    Version:  V 1.01
**    Date: 
**
** ============================================================================
** History: 
** 
** Date         Author  Comment
** ----------------------------------------------------------------------------
**
** 2007.11.06   Walter Pichler    created.
** 2008.04.08   Walter Pichler    adaption to TUA 9001E
**
** ============================================================================
*/

/*============================================================================
Includes
============================================================================*/

#include "driver_tua9001.h"
#include "driver_tua9001_NeededFunctions.h"   /* Note: This function have to be provided by the user */

/*============================================================================
Local compiler keeys         ( usage depends on the application )
============================================================================*/

#define CRYSTAL_26_MHZ
//#define CRYSTAL_19.2_MHZ
//#define CRYSTAL_20.48_MHZ

//#define AGC_BY_IIC
#define AGC_BY_AGC_BUS
//#define AGC_BY_EXT_PIN


/*============================================================================
Named Constants Definitions    ( usage depends on the application )
============================================================================*/

#define TUNERs_TUA9001_DEVADDR    0xC0

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

#define TUNERs_TUA9001_BW_8         0xcf
#define TUNERs_TUA9001_BW_7         0x10
#define TUNERs_TUA9001_BW_6         0x20
#define TUNERs_TUA9001_BW_5         0x30




/*============================================================================
 Types definition
============================================================================*/




/*============================================================================
 Public Functions
============================================================================*/


/**
 * tuner initialisation
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/
 
int initializeTua9001 (void)
{
  unsigned int counter;
  char i2cseq[2];
  tunerReceiverState_t tunerState;

  /* Note: CEN may also be hard wired in the application*/
  setCEN    (H_LEVEL);    /* asserting Chip enable      */

  setRESETN (L_LEVEL);    /* asserting RESET            */
  
  setRXEN   (L_LEVEL);    /* RXEN to low >> IDLE STATE  */
  
  /* Note: 20µs assumes that all external power supplies are settled. If not, add more time here */
  waitloop (20);          /* wait for 20 uS     */
  
  setRESETN (H_LEVEL);    /* de-asserting RESET */

  /* This is to wait for the Crystal Oscillator to settle .. wait until IDLE mode is reached */  
  counter = 7;
  do
    {
    counter --;
    waitloop (1000);      /* wait for 1 mS      */

    }while ((counter));  


  /**** Overwrite default register value ****/ 
  i2cseq[0] = 0x65;    /* Waiting time before PLL cal. start */
  i2cseq[1] = 0x12;   
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x1e, i2cseq, 2);

  i2cseq[0] = 0xB8;    /* VCO Varactor bias fine tuning */
  i2cseq[1] = 0x88;   
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x25, i2cseq, 2);

  i2cseq[0] = 0x54;    /* LNA switching Threshold for UHF1/2 */
  i2cseq[1] = 0x60;
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x39, i2cseq, 2);

  i2cseq[0] = 0x00;    
  i2cseq[1] = 0xC0;
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x3b, i2cseq, 2);

  i2cseq[0] = 0xF0;    /* LO- Path Set LDO output voltage */
  i2cseq[1] = 0x00;
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x3a, i2cseq, 2);
  
  i2cseq[0] = 0x00;    /* Set EXTAGC interval */
  i2cseq[1] = 0x00;               
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x08, i2cseq, 2);
  
  i2cseq[0] = 0x00;    /* Set max. capacitive load */
  i2cseq[1] = 0x30;   
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x32, i2cseq, 2);


  /**** Set Crystal Reference Frequency an Trim value ****/
#if defined(CRYSTAL_26_MHZ)       /*  Frequency 26 MHz */
  i2cseq[0] = 0x01;
  i2cseq[1] = 0xB0;    
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x1d, i2cseq, 2);

  i2cseq[0] = 0x70;              /* NDK 3225 series 26 MHz XTAL */
  i2cseq[1] = 0x3a;
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x41, i2cseq, 2);
  i2cseq[0] = 0x1C;
  i2cseq[1] = 0x78;
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x40, i2cseq, 2);

//#elif defined(CRYSTAL_19.2_MHZ)   /*  Frequency 19.2 MHz */
//  i2cseq[0] = 0x01;
//  i2cseq[1] = 0xA0;    
//  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x1d, i2cseq, 2);
  /* Note: Insert optimised register values for 0x40 / 0x41 for used crystal */
  /* contact application support for further information */
//#elif defined(CRYSTAL_20.48_MHZ)   /*  Frequency 20,48 MHz */
//  i2cseq[0] = 0x01;
//  i2cseq[1] = 0xA8;    
//  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x1d, i2cseq, 2);
  /* Note: Insert optimised register values for 0x40 / 0x41 for used crystal */
  /* contact application support for further information */
#endif



 /**** Set desired Analog Baseband AGC mode ****/ 
#if defined (AGC_BY_IIC)
  i2cseq[0] = 0x00;                /* Bypass AGC controller >>  IIC based AGC */
  i2cseq[1] = 0x40;                     
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x06, i2cseq, 2);
#elif defined(AGC_BY_AGC_BUS)      
  i2cseq[0] = 0x00;                /* Digital AGC bus */               
  i2cseq[1] = 0x00;                /* 0,5 dB steps    */                    
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x06, i2cseq, 2);
#elif defined(AGC_BY_EXT_PIN)      
  i2cseq[0] = 0x40;                /* Ext. AGC pin     */               
  i2cseq[1] = 0x00;                                    
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x06, i2cseq, 2);
#endif 

 
  /**** set desired RF AGC parameter *****/
  i2cseq[0] = 0x1c;      /* Set Wideband Detector Current (100 uA) */
  i2cseq[1] = 0x00;
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x2c, i2cseq, 2);
 
  i2cseq[0] = 0xC0;      /* Set RF AGC Threshold (-32.5dBm) */
  i2cseq[1] = 0x13;
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x36, i2cseq, 2);

  i2cseq[0] = 0x6f;      /* RF AGC Parameter */
  i2cseq[1] = 0x18;   
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x37, i2cseq, 2);

  i2cseq[0] = 0x00;      /* aditional VCO settings  */
  i2cseq[1] = 0x08;   
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x27, i2cseq, 2);

  i2cseq[0] = 0x00;      /* aditional PLL settings  */
  i2cseq[1] = 0x01;   
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x2a, i2cseq, 2);

  i2cseq[0] = 0x0a;      /* VCM correction         */
  i2cseq[1] = 0x40;   
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x34, i2cseq, 2);

  return TUNER_OK;
}



/**
 * tuner tune
 * @param i_freq   tuning frequency
 * @param i_bandwidth  channel  bandwidth
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int tuneTua9001 (long i_freq, tunerDriverBW_t i_bandwidth)
{
  char i2cseq[2];
  unsigned int divider_factor;
  unsigned int ch_offset;
  unsigned int counter;
  unsigned int lo_path_settings;
  tunerReceiverState_t tunerState;


 
  /* de-assert RXEN >> IDLE STATE */
  setRXEN   (L_LEVEL);          
 

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


  // Set LO Path
  i2cseq[0] = lo_path_settings >> 8;
  i2cseq[1] = lo_path_settings & 0xff;
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x2b, i2cseq, 2);

  // Set channel offset
  i2cseq [0] =  ch_offset >> 8;
  i2cseq [1] =  ch_offset & 0xff;
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x20, i2cseq, 2);
  
  // Set Frequency
  i2cseq [0] =  divider_factor >> 8;
  i2cseq [1] =  divider_factor & 0xff;
  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x1f, i2cseq, 2);
   
  // Set bandwidth
 
  i2cseq [0] = 0;
  switch (i_bandwidth)
    {
    case TUNER_BANDWIDTH_8MHZ: i2cseq [0] |= TUNERs_TUA9001_BW_8;
         break; 
    case TUNER_BANDWIDTH_7MHZ: i2cseq [0] |= TUNERs_TUA9001_BW_7;
         break; 
    case TUNER_BANDWIDTH_6MHZ: i2cseq [0] |= TUNERs_TUA9001_BW_6;
         break; 
    case TUNER_BANDWIDTH_5MHZ: i2cseq [0] |= TUNERs_TUA9001_BW_5;
         break; 
    }

  i2cBusWrite (TUNERs_TUA9001_DEVADDR, 0x04, i2cseq, 2);
 
  /* assert RXEN >> RX STATE */
  setRXEN   (H_LEVEL);

  /* This is to wait for the RX state to settle .. wait until RX mode is reached */  
  counter = 5;
  do
    {
    counter --;
    waitloop (1000);         /* wait for 1 mS      */
    }while ((counter));  


  return TUNER_OK;
}


/**
 * Get pll locked state
 * @param o_pll  pll locked state
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int getPllLockedStateTua9001 (tunerPllLocked_t *o_pll)
{
  char i2cseq[2];

  i2cBusRead (TUNERs_TUA9001_DEVADDR, 0x69, i2cseq, 2);           /* get current register value */
  
  o_pll[0]  = (i2cseq[1] & 0x08) ? PLL_LOCKED : PLL_NOT_LOCKED;
 
  return TUNER_OK;
}


/**
 * Get tuner state
 * @param o_tunerState tuner state
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int getReceiverStateTua9001 (tunerReceiverState_t *o_tunerState)
{
  char i2cseq[2];

  i2cBusRead (TUNERs_TUA9001_DEVADDR, 0x70, i2cseq, 2);           /* get current register value */

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
 * @param o_activeInput active input info
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/
 
int getActiveInputTua9001 (tunerActiveInput_t *o_activeInput)
{
  char i2cseq[2];

  i2cBusRead (TUNERs_TUA9001_DEVADDR, 0x71, i2cseq, 2);           /* get current register value */

  switch (i2cseq[1] & ~0x0f)
     {
     case 0x80: o_activeInput [0] = L_INPUT_ACTIVE;   break;
     case 0x20: o_activeInput [0] = UHF_INPUT_ACTIVE; break;
     case 0x10: o_activeInput [0] = VHF_INPUT_ACTIVE; 
     }
 
  return TUNER_OK;
}


/**
 * Get baseband gain value
 * @param o_basebandGain  baseband gain value
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int getBasebandGainTua9001 (char *o_basebandGain)
{
  char i2cseq[2];

  i2cBusRead (TUNERs_TUA9001_DEVADDR, 0x72, i2cseq, 2);           /* get current register value */
  o_basebandGain [0] = i2cseq [1];
 
  return TUNER_OK;
}
