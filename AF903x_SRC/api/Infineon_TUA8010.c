/**
 * @(#)Infineon_TUA8010.cpp
 *
 * ==========================================================
 * Version: 2.2
 * Date:    2008.10.22
 * ==========================================================
 *
 * ==========================================================
 * History:
 *
 * Date         Author      Description
 * ----------------------------------------------------------
 *
 * 2008.08.19   Tom Lin     added tuner version
 * 2008.10.16   Tom Lin     update driver_TUA8010.cpp
 *                          for U/V band switch
 * 2008.10.22	Tom Lin		enable clock out by tuner reg 0x03
 * ==========================================================
 *
 * Copyright 2008 Afatech, Inc. All rights reserved.
 *
 */


//#include <stdio.h> //for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "driver_tua8010.h"
#include "Infineon_TUA8010_Script.h"


static Demodulator* DemodHandle = NULL;
static Byte DemodChip = 0;

/*========================================================================================================================
 additional needed external funtions ( have to  be provided by the user! )
========================================================================================================================*/

/**
 * set / reset tuner reset input
 * @param i_state   level
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int setRESETN8010 (unsigned int i_state)
{
	Dword error = Error_NO_ERROR;

	if (i_state == H_LEVEL) {
	/* set tuner RXEN pin to "H"  */
		error = Standard_writeRegisterBits (DemodHandle, DemodChip, Processor_LINK, p_reg_top_gpiot3_o, reg_top_gpiot3_o_pos, reg_top_gpiot3_o_len, 1);
		if (error) goto exit;
	} else {
	/* set tuner RXEN pin to "L"  */
		error = Standard_writeRegisterBits (DemodHandle, DemodChip, Processor_LINK, p_reg_top_gpiot3_o, reg_top_gpiot3_o_pos, reg_top_gpiot3_o_len, 0);
		if (error) goto exit;
	}

exit:
	if (error)
		return (TUNER_ERR);
	else
		return (TUNER_OK);
}

/**
 * set / reset tuner receive enable input
 * @param i_state   level
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int setRXEN8010 (unsigned int i_state) 
{
	Dword error = Error_NO_ERROR;

	if (i_state == H_LEVEL) {
	/* set tuner RXEN pin to "H"  */
		error = Standard_writeRegisterBits (DemodHandle, DemodChip, Processor_LINK, p_reg_top_gpiot2_o, reg_top_gpiot2_o_pos, reg_top_gpiot2_o_len, 1);
		if (error) goto exit;
	} else {
	/* set tuner RXEN pin to "L"  */
		error = Standard_writeRegisterBits (DemodHandle, DemodChip, Processor_LINK, p_reg_top_gpiot2_o, reg_top_gpiot2_o_pos, reg_top_gpiot2_o_len, 0);
		if (error) goto exit;
	}

exit:
	if (error)
		return (TUNER_ERR);
	else
		return (TUNER_OK);
}


/**
 * set / reset tuner chiop enable input
 * @param i_state   level
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int setCEN8010 (unsigned int i_state)
 {// wait for H/W design which GPIO to use
 // if (i_state == H_LEVEL) 
 //    /* set tuner CEN pin to "H"  */    
 //  
 // else
 //    /* set tuner CEN pin to "L"  */    
 // 
 return TUNER_OK;
 }


/**
 * waitloop 
 * @param i_looptime   * 1uS
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int waitloop8010 (unsigned int i_looptime)
{
 /* wait time = i_looptime * 1 uS */

	User_delay (DemodHandle, i_looptime/1000);

	return TUNER_OK;
}


/**
 * i2cBusWrite 
 * @param deviceAdress    chip address 
 * @param registerAdress  register address 
 * @param *date           pointer to data source
 * @param length          number of bytes to transmit
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int i2cBusWrite8010 (unsigned char deviceAddress, unsigned char registerAddress, char *date, unsigned int length)
{
  /* I2C write data format */
  /* STA  device_address  ACK  register_address  ACK   H_Byte-Data ACK   L_Byte-Data  !ACK  STO */

  /* STA = start condition, ACK = Acknowledge, STO = stop condition                             */   
  /* *date  = pointer to data source   */
  /* length = number of bytes to write */
    Dword error = Error_NO_ERROR;

	error = Standard_writeTunerRegisters (DemodHandle, DemodChip, (Word)registerAddress, (Byte)length, (Byte*)date);
	if (error) goto exit;

exit:
	if (error)
		return (TUNER_ERR);
	else
		return (TUNER_OK);
}


/**
 * i2cBusRead 
 * @param deviceAdress    chip address 
 * @param registerAdress  register address 
 * @param *date           pointer to data destination
 * @param length          number of bytes to read
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int i2cBusRead8010 (unsigned char deviceAddress, unsigned char registerAddress, char *date, unsigned int length)
{
  /* I2C read data format */
  /* STA  device_address  ACK  register_address  ACK  STA H_Byte-Data ACK  device_address_read  ACK  H_Byte-Data ACK L_Byte-Data  ACKH  STO */

  /* STA = start condition, ACK = Acknowledge (generated by TUA8010), ACKH = Acknowledge (generated by Host), STO = stop condition                             */   
  /* *date  = pointer to data destination   */
  /* length = number of bytes to read       */
	Dword error = Error_NO_ERROR;

	error = Standard_readTunerRegisters (DemodHandle, DemodChip, (Word)registerAddress, (Byte)length, (Byte*)date);
	if (error) goto exit;
	
exit:
	if (error)
		return (TUNER_ERR);
	else
		return (TUNER_OK);
}

/*========================================================================================================================
 end of additional needed external funtions
========================================================================================================================*/

Dword TUA8010_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	Dword error = Error_NO_ERROR;
	Byte buffer[2] = {0,};

	DemodHandle = demodulator;
	DemodChip = chip;

	error = Standard_writeRegisterBits (DemodHandle, DemodChip, Processor_LINK, p_reg_top_gpiot2_en, reg_top_gpiot2_en_pos, reg_top_gpiot2_en_len, 1);
	if (error) goto exit;
	
 	error = Standard_writeRegisterBits (DemodHandle, DemodChip, Processor_LINK, p_reg_top_gpiot2_on, reg_top_gpiot2_on_pos, reg_top_gpiot2_on_len, 1);
	if (error) goto exit;

	error = Standard_writeRegisterBits (DemodHandle, DemodChip, Processor_LINK, p_reg_top_gpiot3_en, reg_top_gpiot3_en_pos, reg_top_gpiot3_en_len, 1);
	if (error) goto exit;
	
 	error = Standard_writeRegisterBits (DemodHandle, DemodChip, Processor_LINK, p_reg_top_gpiot3_on, reg_top_gpiot3_on_pos, reg_top_gpiot3_on_len, 1);
	if (error) goto exit;

 	error = Standard_writeRegister (DemodHandle, DemodChip, Processor_LINK, p_reg_top_agc_od, 0);
	if (error) goto exit;

	error = initializeTUA8010();
	if (error) {
		error = Error_WRITE_TUNER_FAIL;
		goto exit;
	}

	/** Enable clock output */
	error = Standard_readTunerRegisters (DemodHandle, DemodChip, 0x03, 2, buffer);
	if (error) goto exit;

	buffer[0] = buffer[0] | 0x10;

	error = Standard_writeTunerRegisters (DemodHandle, DemodChip, 0x03, 2, buffer);

exit:
	return (error);
}


Dword TUA8010_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	Dword error = Error_NO_ERROR;
	Byte buffer[2] = {0,};

	DemodHandle = demodulator;
	DemodChip = chip;

	/** Disable clock output */
	error = Standard_readTunerRegisters (DemodHandle, DemodChip, 0x03, 2, buffer);
	if (error) goto exit;

	buffer[0] = buffer[0] & 0xEF;

	error = Standard_writeTunerRegisters (DemodHandle, DemodChip, 0x03, 2, buffer);

exit:
	return (error);
}

Dword TUA8010_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  Word			bandwidth,
	IN  Dword			frequency
) {
	Dword error = Error_NO_ERROR;
    DemodChip = chip;

	Word bw = 0;

	if (bandwidth == 8000)
		bw = TUNER_BANDWIDTH_8MHZ;
	else if (bandwidth == 7000)
		bw = TUNER_BANDWIDTH_7MHZ;
	else if (bandwidth == 6000)
		bw = TUNER_BANDWIDTH_6MHZ;
	else
		bw = TUNER_BANDWIDTH_5MHZ;
		
	error = tuneTUA8010 (frequency, (tunerDriverBW_t)bw);
	if (error) {
		error = Error_WRITE_TUNER_FAIL;
		goto exit;
	}

exit:
	return (error);
}


TunerDescription tuner_TUA8010 = {
    TUA8010_open,
    TUA8010_close,
    TUA8010_set,
    TUA8010_scripts,
    TUA8010_scriptSets,
    TUA8010_ADDRESS,        /** tuner i2c address */
    1,                      /** length of tuner register address */
    0,                      /** tuner if */
    True,                   /** spectrum inverse */
    0x27,                   /** tuner id */
};
