/*****************************************************************************
**
**  Name: mt2260.h
**
**  Description:    Microtune MT2260 Tuner software interface.
**                  Supports tuners with Part/Rev code: 0x85.
**
**  Functions
**  Implemented:    UData_t  MT2260_Open
**                  UData_t  MT2260_Close
**                  UData_t  MT2260_ChangeFreq
**                  UData_t  MT2260_GetLocked
**                  UData_t  MT2260_GetParam
**                  UData_t  MT2260_GetReg
**                  UData_t  MT2260_GetUserData
**                  UData_t  MT2260_ReInit
**                  UData_t  MT2260_SetParam
**                  UData_t  MT2260_SetPowerModes
**                  UData_t  MT2260_SetReg
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
**  CVS ID:         $Id: mt2260.h,v 1.1 2006/05/08 22:05:01 software Exp $
**  CVS Source:     $Source: /export/home/cvsroot/web05/html/software/tuners/MT2260/MT2260B0/mt2260.h,v $
**	               
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
*****************************************************************************/
#if !defined( __MT2260_H )
#define __MT2260_H

#include "mt2260_userdef.h"

#if defined( __cplusplus )     
extern "C"                     /* Use "C" external linkage                  */
{
#endif

/*
**  Parameter for function MT2260_GetParam & MT2260_SetParam that 
**  specifies the tuning algorithm parameter to be read/written.
*/
typedef enum
{
    /*  tuner address                                  set by MT2260_Open() */
    MT2260_IC_ADDR,

    /*  max number of MT2260 tuners       set by MT2260_CNT in mt_userdef.h */
    MT2260_MAX_OPEN,

    /*  current number of open MT2260 tuners           set by MT2260_Open() */
    MT2260_NUM_OPEN,
    
    /*  Number of tuner registers                                           */
    MT2260_NUM_REGS,

    /*  crystal frequency                            (default: 18000000 Hz) */
    MT2260_SRO_FREQ,

    /*  min tuning step size                            (default: 50000 Hz) */
    MT2260_STEPSIZE,

    /*  input center frequency                   set by MT2260_ChangeFreq() */
    MT2260_INPUT_FREQ,

    /*  LO Frequency                             set by MT2260_ChangeFreq() */
    MT2260_LO_FREQ,

    /*  output channel bandwidth                      (default: 8000000 Hz) */
    MT2260_OUTPUT_BW,

    /*  Base band filter calibration RC code                 (default: N/A) */
    MT2260_RC2_VALUE,

    /*  Base band filter nominal cal RC code                 (default: N/A) */
    MT2260_RC2_NOMINAL,

    /*  RF attenuator A/D readback                              (read-only) */
    MT2260_RF_ADC,

    /*  BB attenuator A/D readback                              (read-only) */
    MT2260_BB_ADC,

    /*  RF attenuator setting                             (default: varies) */
    MT2260_RF_ATTN,

    /*  BB attenuator setting                             (default: varies) */
    MT2260_BB_ATTN,

    /*  RF external / internal atten control              (default: varies) */
    MT2260_RF_EXT,

    /*  BB external / internal atten control                   (default: 1) */
    MT2260_BB_EXT,

    /*  LNA gain setting (0-15)                           (default: varies) */
    MT2260_LNA_GAIN,

    /*  Decrement LNA Gain (where arg=min LNA Gain value)                   */
    MT2260_LNA_GAIN_DECR,

    /*  Increment LNA Gain (where arg=max LNA Gain value)                   */
    MT2260_LNA_GAIN_INCR,

    /*  Set for UHF max sensitivity mode                                    */
    MT2260_UHF_MAXSENS,

    /*  Set for UHF normal mode                                             */
    MT2260_UHF_NORMAL,

    MT2260_EOP                    /*  last entry in enumerated list         */
} MT2260_Param;

/*
**  Constants for Specifying Operating Band of the Tuner
*/
#define MT2260_VHF_BAND (0)
#define MT2260_UHF_BAND (1)
#define MT2260_L_BAND   (2)

/*
**  Constants for specifying power modes these values
**  are bit-mapped and can be added/OR'ed to indicate
**  multiple settings.  Examples:
**     MT2260_SetPowerModes(h, MT2260_NO_ENABLES + MT22260_SROsd);
**     MT2260_SetPowerModes(h, MT2260_ALL_ENABLES | MT22260_SRO_NOT_sd);
**     MT2260_SetPowerModes(h, MT2260_NO_ENABLES + MT22260_SROsd);
**     MT2260_SetPowerModes(h, MT2260_SROen + MT22260_LOen + MT2260_ADCen);
*/
#define MT2260_SROen       (0x01)
#define MT2260_LOen        (0x02)
#define MT2260_ADCen       (0x04)
#define MT2260_PDen        (0x08)
#define MT2260_DCOCen      (0x10)
#define MT2260_BBen        (0x20)
#define MT2260_MIXen       (0x40)
#define MT2260_LNAen       (0x80)
#define MT2260_ALL_ENABLES (0xFF)
#define MT2260_NO_ENABLES  (0x00)
#define MT2260_SROsd       (0x100)
#define MT2260_SRO_NOT_sd  (0x000)

/* ====== Functions which are declared in mt2260.c File ======= */

/******************************************************************************
**
**  Name: MT2260_Open
**
**  Description:    Initialize the tuner's register values.
**
**  Usage:          status = MT2260_Open(0xC0, &hMT2260, NULL);
**                  if (MT_IS_ERROR(status))
**                      //  Check error codes for reason
**
**  Parameters:     MT2260_Addr  - Serial bus address of the tuner.
**                  hMT2260      - Tuner handle passed back.
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
UData_t MT2260_Open(UData_t MT2260_Addr,
                    Handle_t* hMT2260,
                    Handle_t hUserData);


/******************************************************************************
**
**  Name: MT2260_Close
**
**  Description:    Release the handle to the tuner.
**
**  Parameters:     hMT2260      - Handle to the MT2260 tuner
**
**  Usage:          status = MT2260_Close(hMT2260);
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
UData_t MT2260_Close(Handle_t hMT2260);


/****************************************************************************
**
**  Name: MT2260_ChangeFreq
**
**  Description:    Change the tuner's tuned frequency to f_in.
**
**  Parameters:     h           - Open handle to the tuner (from MT2260_Open).
**                  f_in        - RF input center frequency (in Hz).
**
**  Usage:          status = MT2260_ChangeFreq(hMT2260, f_in);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_DNC_UNLOCK    - Downconverter PLL unlocked
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_FIN_RANGE     - Input freq out of range
**                      MT_DNC_RANGE     - Downconverter freq out of range
**
**  Dependencies:   MUST CALL MT2260_Open BEFORE MT2260_ChangeFreq!
**
**                  MT_ReadSub       - Read byte(s) of data from the two-wire-bus
**                  MT_WriteSub      - Write byte(s) of data to the two-wire-bus
**                  MT_Sleep         - Delay execution for x milliseconds
**                  MT2260_GetLocked - Checks to see if the PLL is locked
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
******************************************************************************/
UData_t MT2260_ChangeFreq(Handle_t h,
                          UData_t f_in);


/****************************************************************************
**
**  Name: MT2260_GetLocked
**
**  Description:    Checks to see if the PLL is locked.
**
**  Parameters:     h            - Open handle to the tuner (from MT2260_Open).
**
**  Usage:          status = MT2260_GetLocked(hMT2260);
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
UData_t MT2260_GetLocked(Handle_t h);


/****************************************************************************
**
**  Name: MT2260_GetParam
**
**  Description:    Gets a tuning algorithm parameter.
**
**                  This function provides access to the internals of the
**                  tuning algorithm - mostly for testing purposes.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**                  param       - Tuning algorithm parameter 
**                                (see enum MT2260_Param)
**                  pValue      - ptr to returned value
**
**                  param                   Description
**                  ----------------------  --------------------------------
**                  MT2260_IC_ADDR          Serial Bus address of this tuner
**                  MT2260_MAX_OPEN         Max number of MT2260's that can be open
**                  MT2260_NUM_OPEN         Number of MT2260's currently open
**                  MT2260_NUM_REGS         Number of tuner registers
**                  MT2260_SRO_FREQ         crystal frequency
**                  MT2260_STEPSIZE         minimum tuning step size
**                  MT2260_INPUT_FREQ       input center frequency
**                  MT2260_LO_FREQ          LO Frequency
**                  MT2260_OUTPUT_BW        Output channel bandwidth
**                  MT2260_RC2_VALUE        Base band filter cal RC code (method 2)
**                  MT2260_RF_ADC           RF attenuator A/D readback
**                  MT2260_RF_ATTN          RF attenuation (0-255)
**                  MT2260_RF_EXT           External control of RF atten
**                  MT2260_LNA_GAIN         LNA gain setting (0-15)
**                  MT2260_BB_ADC           BB attenuator A/D readback
**                  MT2260_BB_ATTN          Baseband attenuation (0-255)
**                  MT2260_BB_EXT           External control of BB atten
**
**  Usage:          status |= MT2260_GetParam(hMT2260, 
**                                            MT2260_OUTPUT_BW,
**                                            &f_bw);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_NULL      - Null pointer argument passed
**                      MT_ARG_RANGE     - Invalid parameter requested
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
**
**  See Also:       MT2260_SetParam, MT2260_Open
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2260_GetParam(Handle_t     h,
                        MT2260_Param param,
                        UData_t*     pValue);


/****************************************************************************
**
**  Name: MT2260_GetReg
**
**  Description:    Gets an MT2260 register.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**                  reg         - MT2260 register/subaddress location
**                  *val        - MT2260 register/subaddress value
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_NULL      - Null pointer argument passed
**                      MT_ARG_RANGE     - Argument out of range
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
**
**                  Use this function if you need to read a register from
**                  the MT2260.
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2260_GetReg(Handle_t h,
                      U8Data   reg,
                      U8Data*  val);


/****************************************************************************
**
**  Name: MT2260_GetUserData
**
**  Description:    Gets the user-defined data item.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**
**  Usage:          status = MT2260_GetUserData(hMT2260, &hUserData);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_NULL      - Null pointer argument passed
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
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
**  See Also:       MT2260_SetUserData, MT2260_Open
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2260_GetUserData(Handle_t h,
                           Handle_t* hUserData);


/******************************************************************************
**
**  Name: MT2260_ReInit
**
**  Description:    Initialize the tuner's register values.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
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
UData_t MT2260_ReInit(Handle_t h);


/****************************************************************************
**
**  Name: MT2260_SetParam
**
**  Description:    Sets a tuning algorithm parameter.
**
**                  This function provides access to the internals of the
**                  tuning algorithm.  You can override many of the tuning
**                  algorithm defaults using this function.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**                  param       - Tuning algorithm parameter 
**                                (see enum MT2260_Param)
**                  nValue      - value to be set
**
**                  param                   Description
**                  ----------------------  --------------------------------
**                  MT2260_SRO_FREQ         crystal frequency                   
**                  MT2260_STEPSIZE         minimum tuning step size            
**                  MT2260_INPUT_FREQ       Center of input channel             
**                  MT2260_OUTPUT_BW        Output channel bandwidth
**                  MT2260_RF_ATTN          RF attenuation (0-255)
**                  MT2260_RF_EXT           External control of RF atten
**                  MT2260_LNA_GAIN         LNA gain setting (0-15)
**                  MT2260_LNA_GAIN_DECR    Decrement LNA Gain (arg=min)
**                  MT2260_LNA_GAIN_INCR    Increment LNA Gain (arg=max)
**                  MT2260_BB_ATTN          Baseband attenuation (0-255)
**                  MT2260_BB_EXT           External control of BB atten
**                  MT2260_UHF_MAXSENS      Set for UHF max sensitivity mode
**                  MT2260_UHF_NORMAL       Set for UHF normal mode
**
**  Usage:          status |= MT2260_SetParam(hMT2260, 
**                                            MT2260_STEPSIZE,
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
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
**
**  See Also:       MT2260_GetParam, MT2260_Open
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2260_SetParam(Handle_t     h,
                        MT2260_Param param,
                        UData_t      nValue);


/****************************************************************************
**
**  Name: MT2260_SetPowerModes
**
**  Description:    Sets the bits in the MT2260_ENABLES register and the
**                  SROsd bit in the MT2260_SROADC_CTRL register.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**                  flags       - Bit mask of flags to indicate enabled
**                                bits.
**
**  Usage:          status = MT2260_SetPowerModes(hMT2260, flags);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
**
**                  The bits in the MT2260_ENABLES register and the
**                  SROsd bit are set according to the supplied flags.
**
**                  The pre-defined flags are as follows:
**                      MT2260_SROen
**                      MT2260_LOen
**                      MT2260_ADCen
**                      MT2260_PDen
**                      MT2260_DCOCen
**                      MT2260_BBen
**                      MT2260_MIXen
**                      MT2260_LNAen
**                      MT2260_ALL_ENABLES
**                      MT2260_NO_ENABLES
**                      MT2260_SROsd
**                      MT2260_SRO_NOT_sd
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
**  See Also:       MT2260_Open
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2260_SetPowerModes(Handle_t h,
                             UData_t  flags);


/****************************************************************************
**
**  Name: MT2260_SetReg
**
**  Description:    Sets an MT2260 register.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**                  reg         - MT2260 register/subaddress location
**                  val         - MT2260 register/subaddress value
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_RANGE     - Argument out of range
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
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
UData_t MT2260_SetReg(Handle_t h,
                      U8Data   reg,
                      U8Data   val);


#if defined( __cplusplus )
}
#endif

#endif