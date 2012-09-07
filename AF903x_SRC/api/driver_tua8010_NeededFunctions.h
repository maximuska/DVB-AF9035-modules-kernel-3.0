/* ============================================================================
** Copyright (C) 1997-2008 Infineon AP All rights reserved.
** ============================================================================
**
** ============================================================================
** Revision Information :
**    File name: driver_tua8010_NeededFunctions.h
**    Version: v0.1
**    Date: 2008.08.17
**
** ============================================================================
** History: 
** 
** Date         Author  Comment
** ----------------------------------------------------------------------------
** 2007.11.06   Walter Pichler    created.
** 2008.08.15   Xie Yonggang      adaption to TUA8010
**
** ============================================================================
*/

/*========================================================================================================================
 additional needed external funtions ( have to  be provided by the user! )
========================================================================================================================*/

/**
 * set / reset tuner reset input
 * @param IN i_state   level
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/

int setRESETN8010 (unsigned int i_state);



/**
 * set / reset tuner receive enable input
 * @param IN i_state   level
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/

int setRXEN8010 (unsigned int i_state);


/**
 * set / reset tuner chiop enable input
 * @param IN i_state   level
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/

int setCEN8010 (unsigned int i_state);



/**
 * waitloop 
 * @param IN i_looptime   * 1uS
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/

int waitloop8010 (unsigned int i_looptime);



/**
 * i2cBusWrite 
 * @param IN deviceAdress    chip address 
 * @param IN registerAdress  register address 
 * @param IN *data           pointer to data source
 * @param IN length          number of bytes to transmit
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/

 int i2cBusWrite8010 (unsigned char deviceAddress, unsigned char registerAddress, char *data, unsigned int length);



/**
 * i2cBusRead 
 * @param IN deviceAdress    chip address 
 * @param IN registerAdress  register address 
 * @param OUT *data           pointer to data destination
 * @param IN length          number of bytes to read
 * @retval TUNER_OK No error
 * @retval TUNER_ERROR Error
*/

 int i2cBusRead8010 (unsigned char deviceAddress, unsigned char registerAddress, char *data, unsigned int length);


/*========================================================================================================================
 end of additional needed external funtions
========================================================================================================================*/
