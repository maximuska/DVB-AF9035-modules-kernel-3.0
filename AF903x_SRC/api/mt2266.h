/*****************************************************************************
**
**  Name: mt2266.h
**
**  Copyright 2007 Microtune, Inc. All Rights Reserved
**
**  This source code file contains confidential information and/or trade
**  secrets of Microtune, Inc. or its affiliates and is subject to the
**  terms of your confidentiality agreement with Microtune, Inc. or one of
**  its affiliates, as applicable.
**
*****************************************************************************/

/*****************************************************************************
**
**  Name: mt2266.h
**
**  Description:    Microtune MT2266 Tuner software interface.
**                  Supports tuners with Part/Rev code: 0x85.
**
**  Functions
**  Implemented:    UData_t  MT2266_Open
**                  UData_t  MT2266_Close
**                  UData_t  MT2266_ChangeFreq
**                  UData_t  MT2266_GetLocked
**                  UData_t  MT2266_GetParam
**                  UData_t  MT2266_GetReg
**                  UData_t  MT2266_GetUHFXFreqs
**                  UData_t  MT2266_GetUserData
**                  UData_t  MT2266_ReInit
**                  UData_t  MT2266_SetParam
**                  UData_t  MT2266_SetPowerModes
**                  UData_t  MT2266_SetReg
**                  UData_t  MT2266_SetUHFXFreqs
**                  UData_t  MT2266_Tune
**
**  References:     AN-00010: MicroTuner Serial Interface Application Note
**                  MicroTune, Inc.
**
**  Exports:        None
**
**  Dependencies:   MT_ReadSub(hUserData, IC_Addr, subAddress, *pData, cnt);
**                  - Read byte(s) of data from the two-wire bus.
**
**                  MT_WriteSub(hUserData, IC_Addr, subAddress, *pData, cnt);
**                  - Write byte(s) of data to the two-wire bus.
**
**                  MT_Sleep(hUserData, nMinDelayTime);
**                  - Delay execution for x milliseconds
**
**  CVS ID:         $Id: mt2266.h,v 1.3 2007/10/02 18:43:17 software Exp $
**  CVS Source:     $Source: /export/home/cvsroot/software/tuners/MT2266/mt2266.h,v $
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   05-30-2006    DAD    Ver 1.0: Modified version of mt2260.c (Ver 1.01).
**   N/A   11-01-2006    RSK    Ver 1.02: Adding Get/Set UHFXFreq access functions.
**   118   05-09-2007    RSK    Ver 1.05: Adding Standard MTxxxx_Tune() API.
**
*****************************************************************************/
#if !defined( __MT2266_H )
#define __MT2266_H

#include "mt2266_userdef.h"

#if defined( __cplusplus )
extern "C"                     /* Use "C" external linkage                  */
{
#endif

/*
**  Parameter for function MT2266_GetParam & MT2266_SetParam that
**  specifies the tuning algorithm parameter to be read/written.
*/
typedef enum
{
    /*  tuner address                                  set by MT2266_Open() */
    MT2266_IC_ADDR,

    /*  max number of MT2266 tuners       set by MT2266_CNT in mt_userdef.h */
    MT2266_MAX_OPEN,

    /*  current number of open MT2266 tuners           set by MT2266_Open() */
    MT2266_NUM_OPEN,

    /*  Number of tuner registers                                           */
    MT2266_NUM_REGS,

    /*  crystal frequency                            (default: 18000000 Hz) */
    MT2266_SRO_FREQ,

    /*  min tuning step size                            (default: 50000 Hz) */
    MT2266_STEPSIZE,

    /*  input center frequency                   set by MT2266_ChangeFreq() */
    MT2266_INPUT_FREQ,

    /*  LO Frequency                             set by MT2266_ChangeFreq() */
    MT2266_LO_FREQ,

    /*  output channel bandwidth                      (default: 8000000 Hz) */
    MT2266_OUTPUT_BW,

    /*  Base band filter calibration RC code                 (default: N/A) */
    MT2266_RC2_VALUE,

    /*  Base band filter nominal cal RC code                 (default: N/A) */
    MT2266_RC2_NOMINAL,

    /*  RF attenuator A/D readback                              (read-only) */
    MT2266_RF_ADC,

    /*  BB attenuator A/D readback                              (read-only) */
    MT2266_BB_ADC,

    /*  RF attenuator setting                             (default: varies) */
    MT2266_RF_ATTN,

    /*  BB attenuator setting                             (default: varies) */
    MT2266_BB_ATTN,

    /*  RF external / internal atten control              (default: varies) */
    MT2266_RF_EXT,

    /*  BB external / internal atten control                   (default: 1) */
    MT2266_BB_EXT,

    /*  LNA gain setting (0-15)                           (default: varies) */
    MT2266_LNA_GAIN,

    /*  Decrement LNA Gain (where arg=min LNA Gain value)                   */
    MT2266_LNA_GAIN_DECR,

    /*  Increment LNA Gain (where arg=max LNA Gain value)                   */
    MT2266_LNA_GAIN_INCR,

    /*  Set for UHF max sensitivity mode                                    */
    MT2266_UHF_MAXSENS,

    /*  Set for UHF normal mode                                             */
    MT2266_UHF_NORMAL,

    MT2266_EOP                    /*  last entry in enumerated list         */
} MT2266_Param;


/*
**  Parameter for function MT2266_GetUHFXFreqs & MT2266_SetUHFXFreqs that
**  specifies the particular frequency crossover table to be read/written.
*/
typedef enum
{
    /*  Reference the UHF 0 filter, without any attenuation                 */
    MT2266_UHF0,

    /*  Reference the UHF 1 filter, without any attenuation                 */
    MT2266_UHF1,

    /*  Reference the UHF 0 filter, with attenuation                        */
    MT2266_UHF0_ATTEN,

    /*  Reference the UHF 1 filter, with attenuation                        */
    MT2266_UHF1_ATTEN,

    MT2266_NUMBER_OF_XFREQ_SETS    /*  last entry in enumerated list        */

} MT2266_UHFXFreq_Type;


#define  MT2266_NUM_XFREQS  (16)

typedef  UData_t MT2266_XFreq_Set[ MT2266_NUM_XFREQS ];

/*
**  Constants for Specifying Operating Band of the Tuner
*/
#define MT2266_VHF_BAND (0)
#define MT2266_UHF_BAND (1)
#define MT2266_L_BAND   (2)

/*
**  Constants for specifying power modes these values
**  are bit-mapped and can be added/OR'ed to indicate
**  multiple settings.  Examples:
**     MT2266_SetPowerModes(h, MT2266_NO_ENABLES + MT22266_SROsd);
**     MT2266_SetPowerModes(h, MT2266_ALL_ENABLES | MT22266_SRO_NOT_sd);
**     MT2266_SetPowerModes(h, MT2266_NO_ENABLES + MT22266_SROsd);
**     MT2266_SetPowerModes(h, MT2266_SROen + MT22266_LOen + MT2266_ADCen);
*/
#define MT2266_SROen       (0x01)
#define MT2266_LOen        (0x02)
#define MT2266_ADCen       (0x04)
#define MT2266_PDen        (0x08)
#define MT2266_DCOCen      (0x10)
#define MT2266_BBen        (0x20)
#define MT2266_MIXen       (0x40)
#define MT2266_LNAen       (0x80)
#define MT2266_ALL_ENABLES (0xFF)
#define MT2266_NO_ENABLES  (0x00)
#define MT2266_SROsd       (0x100)
#define MT2266_SRO_NOT_sd  (0x000)

/* ====== Functions which are declared in mt2266.c File ======= */

/******************************************************************************
**
**  Name: MT2266_Open
**
**  Description:    Initialize the tuner's register values.
**
**  Usage:          status = MT2266_Open(0xC0, &hMT2266, NULL);
**                  if (MT_IS_ERROR(status))
**                      //  Check error codes for reason
**
**  Parameters:     MT2266_Addr  - Serial bus address of the tuner.
**                  hMT2266      - Tuner handle passed back.
**                  hUserData    - User-defined data, if needed for the
**                                 MT_ReadSub() & MT_WriteSub functions.
**
**  Returns:        status:
**                      MT_OK             - No errors
**                      MT_TUNER_ID_ERR   - Tuner Part/Rev code mismatch
**                      MT_TUNER_INIT_ERR - Tuner initialization failed
**                      MT_COMM_ERR       - Serial bus communications error
**                      MT_ARG_NULL       - Null pointer argument passed
**                      MT_TUNER_CNT_ERR  - Too many tuners open
**
**  Dependencies:   MT_ReadSub  - Read byte(s) of data from the two-wire bus
**                  MT_WriteSub - Write byte(s) of data to the two-wire bus
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
******************************************************************************/
UData_t MT2266_Open(UData_t MT2266_Addr,
                    Handle_t* hMT2266,
                    Handle_t hUserData);


/******************************************************************************
**
**  Name: MT2266_Close
**
**  Description:    Release the handle to the tuner.
**
**  Parameters:     hMT2266      - Handle to the MT2266 tuner
**
**  Usage:          status = MT2266_Close(hMT2266);
**
**  Returns:        status:
**                      MT_OK         - No errors
**                      MT_INV_HANDLE - Invalid tuner handle
**
**  Dependencies:   mt_errordef.h - definition of error codes
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
******************************************************************************/
UData_t MT2266_Close(Handle_t hMT2266);


/****************************************************************************
**
**  Name: MT2266_ChangeFreq
**
**  Description:    Change the tuner's tuned frequency to f_in.
**
**  Parameters:     h           - Open handle to the tuner (from MT2266_Open).
**                  f_in        - RF input center frequency (in Hz).
**
**  Usage:          status = MT2266_ChangeFreq(hMT2266, f_in);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_DNC_UNLOCK    - Downconverter PLL unlocked
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_FIN_RANGE     - Input freq out of range
**                      MT_DNC_RANGE     - Downconverter freq out of range
**
**  Dependencies:   MUST CALL MT2266_Open BEFORE MT2266_ChangeFreq!
**
**                  MT_ReadSub       - Read byte(s) of data from the two-wire-bus
**                  MT_WriteSub      - Write byte(s) of data to the two-wire-bus
**                  MT_Sleep         - Delay execution for x milliseconds
**                  MT2266_GetLocked - Checks to see if the PLL is locked
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
******************************************************************************/
UData_t MT2266_ChangeFreq(Handle_t h,
                          UData_t f_in);


/****************************************************************************
**
**  Name: MT2266_GetLocked
**
**  Description:    Checks to see if the PLL is locked.
**
**  Parameters:     h            - Open handle to the tuner (from MT2266_Open).
**
**  Usage:          status = MT2266_GetLocked(hMT2266);
**                  if (status & MT_DNC_UNLOCK)
**                      //  error!, PLL is unlocked
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_DNC_UNLOCK    - Downconverter PLL unlocked
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_INV_HANDLE    - Invalid tuner handle
**
**  Dependencies:   MT_ReadSub    - Read byte(s) of data from the serial bus
**                  MT_Sleep      - Delay execution for x milliseconds
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2266_GetLocked(Handle_t h);


/****************************************************************************
**
**  Name: MT2266_GetParam
**
**  Description:    Gets a tuning algorithm parameter.
**
**                  This function provides access to the internals of the
**                  tuning algorithm - mostly for testing purposes.
**
**  Parameters:     h           - Tuner handle (returned by MT2266_Open)
**                  param       - Tuning algorithm parameter
**                                (see enum MT2266_Param)
**                  pValue      - ptr to returned value
**
**                  param                   Description
**                  ----------------------  --------------------------------
**                  MT2266_IC_ADDR          Serial Bus address of this tuner
**                  MT2266_MAX_OPEN         Max number of MT2266's that can be open
**                  MT2266_NUM_OPEN         Number of MT2266's currently open
**                  MT2266_NUM_REGS         Number of tuner registers
**                  MT2266_SRO_FREQ         crystal frequency
**                  MT2266_STEPSIZE         minimum tuning step size
**                  MT2266_INPUT_FREQ       input center frequency
**                  MT2266_LO_FREQ          LO Frequency
**                  MT2266_OUTPUT_BW        Output channel bandwidth
**                  MT2266_RC2_VALUE        Base band filter cal RC code (method 2)
**                  MT2266_RF_ADC           RF attenuator A/D readback
**                  MT2266_RF_ATTN          RF attenuation (0-255)
**                  MT2266_RF_EXT           External control of RF atten
**                  MT2266_LNA_GAIN         LNA gain setting (0-15)
**                  MT2266_BB_ADC           BB attenuator A/D readback
**                  MT2266_BB_ATTN          Baseband attenuation (0-255)
**                  MT2266_BB_EXT           External control of BB atten
**
**  Usage:          status |= MT2266_GetParam(hMT2266,
**                                            MT2266_OUTPUT_BW,
**                                            &f_bw);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_NULL      - Null pointer argument passed
**                      MT_ARG_RANGE     - Invalid parameter requested
**
**  Dependencies:   USERS MUST CALL MT2266_Open() FIRST!
**
**  See Also:       MT2266_SetParam, MT2266_Open
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2266_GetParam(Handle_t     h,
                        MT2266_Param param,
                        UData_t*     pValue);


/****************************************************************************
**
**  Name: MT2266_GetReg
**
**  Description:    Gets an MT2266 register.
**
**  Parameters:     h           - Tuner handle (returned by MT2266_Open)
**                  reg         - MT2266 register/subaddress location
**                  *val        - MT2266 register/subaddress value
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_NULL      - Null pointer argument passed
**                      MT_ARG_RANGE     - Argument out of range
**
**  Dependencies:   USERS MUST CALL MT2266_Open() FIRST!
**
**                  Use this function if you need to read a register from
**                  the MT2266.
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2266_GetReg(Handle_t h,
                      U8Data   reg,
                      U8Data*  val);


/****************************************************************************
**
**  Name: MT2266_GetUHFXFreqs
**
**  Description:    Retrieves the specified set of UHF Crossover Frequencies
**
**  Parameters:     h            - Open handle to the tuner (from MT2266_Open).
**
**  Usage:          MT2266_Freq_Set  tmpFreqs;
**                  status = MT2266_GetUHFXFreqs(hMT2266,
**                                               MT2266_UHF1_WITH_ATTENUATION,
**                                               tmpFreqs );
**                  if (status & MT_ARG_RANGE)
**                      // error, Invalid UHF Crossover Frequency Set requested.
**                  else
**                      for( int i = 0;  i < MT2266_NUM_XFREQS; i++ )
**                         . . .
**
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_ARG_RANGE     - freq_type is out of range.
**                      MT_INV_HANDLE    - Invalid tuner handle
**
**  Dependencies:   freqs_buffer *must* be defined of type MT2266_Freq_Set
**                     to assure sufficient space allocation!
**
**                  USERS MUST CALL MT2266_Open() FIRST!
**
**  See Also:       MT2266_SetUHFXFreqs
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   11-01-2006   RSK     Original.
**
****************************************************************************/
UData_t MT2266_GetUHFXFreqs(Handle_t             h,
                            MT2266_UHFXFreq_Type freq_type,
                            MT2266_XFreq_Set     freqs_buffer);


/****************************************************************************
**
**  Name: MT2266_GetUserData
**
**  Description:    Gets the user-defined data item.
**
**  Parameters:     h           - Tuner handle (returned by MT2266_Open)
**
**  Usage:          status = MT2266_GetUserData(hMT2266, &hUserData);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_NULL      - Null pointer argument passed
**
**  Dependencies:   USERS MUST CALL MT2266_Open() FIRST!
**
**                  The hUserData parameter is a user-specific argument
**                  that is stored internally with the other tuner-
**                  specific information.
**
**                  For example, if additional arguments are needed
**                  for the user to identify the device communicating
**                  with the tuner, this argument can be used to supply
**                  the necessary information.
**
**                  The hUserData parameter is initialized in the tuner's
**                  Open function to NULL.
**
**  See Also:       MT2266_SetUserData, MT2266_Open
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2266_GetUserData(Handle_t  h,
                           Handle_t* hUserData);


/******************************************************************************
**
**  Name: MT2266_ReInit
**
**  Description:    Initialize the tuner's register values.
**
**  Parameters:     h           - Tuner handle (returned by MT2266_Open)
**
**  Returns:        status:
**                      MT_OK             - No errors
**                      MT_TUNER_ID_ERR   - Tuner Part/Rev code mismatch
**                      MT_TUNER_INIT_ERR - Tuner initialization failed
**                      MT_INV_HANDLE     - Invalid tuner handle
**                      MT_COMM_ERR       - Serial bus communications error
**
**  Dependencies:   MT_ReadSub  - Read byte(s) of data from the two-wire bus
**                  MT_WriteSub - Write byte(s) of data to the two-wire bus
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
******************************************************************************/
UData_t MT2266_ReInit(Handle_t h);


/****************************************************************************
**
**  Name: MT2266_SetParam
**
**  Description:    Sets a tuning algorithm parameter.
**
**                  This function provides access to the internals of the
**                  tuning algorithm.  You can override many of the tuning
**                  algorithm defaults using this function.
**
**  Parameters:     h           - Tuner handle (returned by MT2266_Open)
**                  param       - Tuning algorithm parameter
**                                (see enum MT2266_Param)
**                  nValue      - value to be set
**
**                  param                   Description
**                  ----------------------  --------------------------------
**                  MT2266_SRO_FREQ         crystal frequency
**                  MT2266_STEPSIZE         minimum tuning step size
**                  MT2266_INPUT_FREQ       Center of input channel
**                  MT2266_OUTPUT_BW        Output channel bandwidth
**                  MT2266_RF_ATTN          RF attenuation (0-255)
**                  MT2266_RF_EXT           External control of RF atten
**                  MT2266_LNA_GAIN         LNA gain setting (0-15)
**                  MT2266_LNA_GAIN_DECR    Decrement LNA Gain (arg=min)
**                  MT2266_LNA_GAIN_INCR    Increment LNA Gain (arg=max)
**                  MT2266_BB_ATTN          Baseband attenuation (0-255)
**                  MT2266_BB_EXT           External control of BB atten
**                  MT2266_UHF_MAXSENS      Set for UHF max sensitivity mode
**                  MT2266_UHF_NORMAL       Set for UHF normal mode
**
**  Usage:          status |= MT2266_SetParam(hMT2266,
**                                            MT2266_STEPSIZE,
**                                            50000);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_NULL      - Null pointer argument passed
**                      MT_ARG_RANGE     - Invalid parameter requested
**                                         or set value out of range
**                                         or non-writable parameter
**
**  Dependencies:   USERS MUST CALL MT2266_Open() FIRST!
**
**  See Also:       MT2266_GetParam, MT2266_Open
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2266_SetParam(Handle_t     h,
                        MT2266_Param param,
                        UData_t      nValue);


/****************************************************************************
**
**  Name: MT2266_SetPowerModes
**
**  Description:    Sets the bits in the MT2266_ENABLES register and the
**                  SROsd bit in the MT2266_SROADC_CTRL register.
**
**  Parameters:     h           - Tuner handle (returned by MT2266_Open)
**                  flags       - Bit mask of flags to indicate enabled
**                                bits.
**
**  Usage:          status = MT2266_SetPowerModes(hMT2266, flags);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**
**  Dependencies:   USERS MUST CALL MT2266_Open() FIRST!
**
**                  The bits in the MT2266_ENABLES register and the
**                  SROsd bit are set according to the supplied flags.
**
**                  The pre-defined flags are as follows:
**                      MT2266_SROen
**                      MT2266_LOen
**                      MT2266_ADCen
**                      MT2266_PDen
**                      MT2266_DCOCen
**                      MT2266_BBen
**                      MT2266_MIXen
**                      MT2266_LNAen
**                      MT2266_ALL_ENABLES
**                      MT2266_NO_ENABLES
**                      MT2266_SROsd
**                      MT2266_SRO_NOT_sd
**
**                  ONLY the enable bits (or SROsd bit) specified in the
**                  flags parameter will be set.  Any flag which is not
**                  included, will cause that bit to be disabled.
**
**                  The ALL_ENABLES, NO_ENABLES, and SRO_NOT_sd constants
**                  are for convenience.  The NO_ENABLES and SRO_NOT_sd
**                  do not actually have to be included, but are provided
**                  for clarity.
**
**  See Also:       MT2266_Open
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2266_SetPowerModes(Handle_t h,
                             UData_t  flags);


/****************************************************************************
**
**  Name: MT2266_SetReg
**
**  Description:    Sets an MT2266 register.
**
**  Parameters:     h           - Tuner handle (returned by MT2266_Open)
**                  reg         - MT2266 register/subaddress location
**                  val         - MT2266 register/subaddress value
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_RANGE     - Argument out of range
**
**  Dependencies:   USERS MUST CALL MT2266_Open() FIRST!
**
**                  Use this function if you need to override a default
**                  register value
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2266_SetReg(Handle_t h,
                      U8Data   reg,
                      U8Data   val);


/****************************************************************************
**
**  Name: MT2266_SetUHFXFreqs
**
**  Description:    Retrieves the specified set of UHF Crossover Frequencies
**
**  Parameters:     h            - Open handle to the tuner (from MT2266_Open).
**
**  Usage:          MT2266_Freq_Set  tmpFreqs;
**                  status = MT2266_SetUHFXFreqs(hMT2266,
**                                               MT2266_UHF1_WITH_ATTENUATION,
**                                               tmpFreqs );
**                  if (status & MT_ARG_RANGE)
**                      // error, Invalid UHF Crossover Frequency Set requested.
**                  else
**                      for( int i = 0;  i < MT2266_NUM_XFREQS; i++ )
**                         . . .
**
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_ARG_RANGE     - freq_type is out of range.
**                      MT_INV_HANDLE    - Invalid tuner handle
**
**  Dependencies:   freqs_buffer *must* be defined of type MT2266_Freq_Set
**                     to assure sufficient space allocation!
**
**                  USERS MUST CALL MT2266_Open() FIRST!
**
**  See Also:       MT2266_SetUHFXFreqs
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   11_01-2006   RSK     Original.
**
****************************************************************************/
UData_t MT2266_SetUHFXFreqs(Handle_t             h,
                            MT2266_UHFXFreq_Type freq_type,
                            MT2266_XFreq_Set     freqs_buffer);


/****************************************************************************
**
**  Name: MT2266_Tune
**
**  Description:    Change the tuner's tuned frequency to f_in.
**
**  Parameters:     h           - Open handle to the tuner (from MT2266_Open).
**                  f_in        - RF input center frequency (in Hz).
**
**  Usage:          status = MT2266_Tune(hMT2266, f_in);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_DNC_UNLOCK    - Downconverter PLL unlocked
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_FIN_RANGE     - Input freq out of range
**                      MT_DNC_RANGE     - Downconverter freq out of range
**
**  Dependencies:   MUST CALL MT2266_Open BEFORE MT2266_Tune!
**
**                  MT_ReadSub       - Read byte(s) of data from the two-wire-bus
**                  MT_WriteSub      - Write byte(s) of data to the two-wire-bus
**                  MT_Sleep         - Delay execution for x milliseconds
**                  MT2266_GetLocked - Checks to see if the PLL is locked
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   118   05-09-2007   RSK     Original API Introduction (was ChangeFreq).
**
******************************************************************************/
UData_t MT2266_Tune(Handle_t h,
                    UData_t f_in);


#if defined( __cplusplus )
}
#endif

#endif