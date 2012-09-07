/*
 * @(#)Xceive_XC3028L.cpp
 *
 * ==========================================================
 * Version: 2.0
 * Date:    2008.07.02
 * ==========================================================
 *
 * ==========================================================
 * History:
 *
 * Date         Author      Description
 * ----------------------------------------------------------
 *
 * 2008.07.02   Tom Lin     added tuner version
 * ==========================================================
 *
 * Copyright 2006 Afatech, Inc. All rights reserved.
 *
 */

//#include <stdio.h> //for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "xc3028_control.h"
#include "Xceive_XC3028L_Script.h"


static Demodulator* XC3028LHandle = NULL;
static Byte XC3028LChip = 0;


extern XC3028_TV_MODE XC3028_tv_mode_dtv6_afatech_qam_4_56mhz;
extern XC3028_TV_MODE XC3028_tv_mode_dtv7_afatech_4_56mhz;
extern XC3028_TV_MODE XC3028_tv_mode_dtv8_afatech_4_56mhz;
extern XC3028_CHANNEL_MAP XC3028_channel_map_digital_air;


int xc3028_send_i2c_data (
	unsigned char *bytes_to_send,
	int nb_bytes_to_send
) {
    Dword error = Error_NO_ERROR;

    error = Standard_writeTunerRegisters (XC3028LHandle, XC3028LChip, 0x0000, nb_bytes_to_send, bytes_to_send);
    if (error) goto exit;

exit:
	return (error);
}


int xc3028_read_i2c_data (
	unsigned char *bytes_received,
	int nb_bytes_to_receive
) {
    Dword error = Error_NO_ERROR;
   
    error = Standard_readTunerRegisters (XC3028LHandle, XC3028LChip, 0x0000, nb_bytes_to_receive, bytes_received);
    if (error) goto exit;

exit:
    return (error);
}


int xc3028_reset (
) {
	Dword error = Error_NO_ERROR;

	error = Standard_writeRegisterBits (XC3028LHandle, XC3028LChip, Processor_LINK, p_reg_top_gpiot2_o, reg_top_gpiot2_o_pos, reg_top_gpiot2_o_len, 0);
	if (error) goto exit;
	
	error = Standard_writeRegisterBits (XC3028LHandle, XC3028LChip, Processor_LINK, p_reg_top_gpiot2_en, reg_top_gpiot2_en_pos, reg_top_gpiot2_en_len, 1);
	if (error) goto exit;
	
 	error = Standard_writeRegisterBits (XC3028LHandle, XC3028LChip, Processor_LINK, p_reg_top_gpiot2_on, reg_top_gpiot2_on_pos, reg_top_gpiot2_on_len, 1);
	if (error) goto exit;

	User_delay (XC3028LHandle, 250);

	error = Standard_writeRegisterBits (XC3028LHandle, XC3028LChip, Processor_LINK, p_reg_top_gpiot2_o, reg_top_gpiot2_o_pos, reg_top_gpiot2_o_len, 1);
	if (error) goto exit;

exit:
    return (error);
}


int xc3028_wait (
	int wait_ms
) {
	User_delay (XC3028LHandle, (Dword)wait_ms);
	return (Error_NO_ERROR);
}


Dword XC3028L_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	return (Error_NO_ERROR);
}


Dword XC3028L_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
) {
	Dword error = Error_NO_ERROR;

	XC3028LHandle = demodulator;
	XC3028LChip = chip;

    /** Set I2C master clock speed. */
    error = Standard_writeRegister (demodulator, 0, Processor_LINK, p_reg_one_cycle_counter_tuner, 85);
    if (error) goto exit;

	if (bandwidth == 6000) 
	{
		frequency -= 1750;
		error = xc3028_initialize (&XC3028_tv_mode_dtv6_afatech_qam_4_56mhz, 
						(XC3028_CHANNEL_MAP*) &XC3028_channel_map_digital_air);
		if (error) goto exit;
	}

	if (bandwidth == 7000) 
	{
		frequency -= 2250;
		error = xc3028_initialize (&XC3028_tv_mode_dtv7_afatech_4_56mhz, 
						(XC3028_CHANNEL_MAP*) &XC3028_channel_map_digital_air);
		if (error) goto exit;
	}

	if (bandwidth == 8000)
	{
		frequency -= 2750;
		error = xc3028_initialize (&XC3028_tv_mode_dtv8_afatech_4_56mhz, 
						(XC3028_CHANNEL_MAP*) &XC3028_channel_map_digital_air);
    	if (error) goto exit;
	}
	
	frequency *= 1000;
	error = xc3028_set_frequency (frequency);
    if (error) goto exit;

    /** Set I2C master clock speed. */
    error = Standard_writeRegister (demodulator, 0, Processor_LINK, p_reg_one_cycle_counter_tuner, User_I2C_SPEED);
    if (error) goto exit;

exit:
    return (error);
}


Dword XC3028L_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	return (Error_NO_ERROR);
}


TunerDescription tuner_XC3028L = {
    XC3028L_open,
    XC3028L_close,
    XC3028L_set,
    XC3028L_scripts,
	XC3028L_scriptSets,
    XC3028L_ADDRESS,                 /** tuner i2c address */
    0,                               /** length of tuner register address */
    4560000,                         /** tuner if */
    True,                            /** spectrum inverse */
    0x26,                            /** tuner id */
};
