/* ============================================================================
** Copyright (C) 1997-2008 Infineon AP All rights reserved.
** ============================================================================
**
** ============================================================================
** Revision Information :
**    File name: driver_tua8010.h
**    Version: 2008.08.17
**    Date: V0.1
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
	      Internal_UHF_LNA,
	      External_UHF_LNA,
        Internal_VHF_LNA,
        External_VHF_LNA
        } tunerActiveInput_t;

 

/*============================================================================
 Public functions
============================================================================*/

/**
 * tuner initialisation
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/
extern int initializeTUA8010(void);


/**
 * tuner tune
 * @param IN i_freq   tuning frequency
 * @param IN i_bandwidth  channel  bandwidth
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/
extern int tuneTUA8010(long i_freq, tunerDriverBW_t i_bandwidth);


/**
 * Get tuner state
 * @param OUT o_tunerState tuner state
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/
extern int getReceiverStateTUA8010(tunerReceiverState_t *o_tunerState);

/**
 * Get active input
 * @param OUT o_activeInput active input info
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/
extern int getActiveInputTUA8010(tunerActiveInput_t *o_activeInput);


/**
 * Get baseband gain value
 * @param OUT o_basebandGain  baseband gain value
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/
extern int getBasebandGainTUA8010(char *o_basebandGain);
