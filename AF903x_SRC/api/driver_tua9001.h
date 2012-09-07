/* ============================================================================
** Copyright (C) 1997-2007 Infineon AG All rights reserved.
** ============================================================================
**
** ============================================================================
** Revision Information :
**    File name: driver_tua9001.h
**    Version: 
**    Date: 
**
** ============================================================================
** History: 
** 
** Date         Author  Comment
** ----------------------------------------------------------------------------
**
** 2007.11.06   Walter Pichler    created.
** ============================================================================
*/

 
/*============================================================================
 Named Constants Definitions
============================================================================*/

#define TUNER_OK                       0
#define TUNER_ERR                      0xff

#define H_LEVEL                        1
#define L_LEVEL                        0


/*============================================================================
 Types definition
============================================================================*/


typedef enum {
        TUNER_BANDWIDTH_8MHZ,
        TUNER_BANDWIDTH_7MHZ,
        TUNER_BANDWIDTH_6MHZ,
        TUNER_BANDWIDTH_5MHZ,
        } tunerDriverBW_t;


typedef enum {
        PLL_LOCKED,
        PLL_NOT_LOCKED
        }tunerPllLocked_t;


typedef enum {
        STANDBY,
        IDLE,
        RX
        } tunerReceiverState_t;


typedef enum {
        L_INPUT_ACTIVE,
        UHF_INPUT_ACTIVE,
        VHF_INPUT_ACTIVE
        } tunerActiveInput_t;

 

/*============================================================================
 Public functions
============================================================================*/

/**
 * tuner initialisation
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/
extern int initializeTua9001 (void);


/**
 * tuner tune
 * @param i_freq   tuning frequency
 * @param i_bandwidth  channel  bandwidth
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/
extern int tuneTua9001 (long i_freq, tunerDriverBW_t i_bandwidth);


/**
 * Get tuner state
 * @param o_tunerState tuner state
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/
extern int getReceiverStateTua9001 (tunerReceiverState_t *o_tunerState);

/**
 * Get active input
 * @param o_activeInput active input info
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/
extern int getActiveInputTua9001 (tunerActiveInput_t *o_activeInput);


/**
 * Get baseband gain value
 * @param o_basebandGain  baseband gain value
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/
extern int getBasebandGainTua9001 (char *o_basebandGain);
