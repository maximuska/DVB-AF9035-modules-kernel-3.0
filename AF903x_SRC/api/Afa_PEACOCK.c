/**
 * @(#)Afa_PEACOCK.cpp
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
 * Copyright 2007 Afatech, Inc. All rights reserved.
 *
 */


//#include <stdio.h> //for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "Afa_Peacock_Script.h"


Dword PEACOCK_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	return (Error_NO_ERROR);
}


Dword PEACOCK_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	return (Error_NO_ERROR);
}


Dword PEACOCK_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  Word			bandwidth,
	IN  Dword			frequency
) {
	Dword error = Error_NO_ERROR;
	Long ckxtal;
	Byte l_band;
	Byte lna_band;
	Byte lna_cap;
	Word n_div;
	Long n;
	Word m_lo;
	Word lo_freq;
	Byte lo_freq_15_10;
	Byte lo_freq_9_4;
	Byte lo_freq_3_0;
	Long i;
	Byte readTmp;
	Byte lo_cap;
	Long lo_cap_min = -1;
	Long lo_cap_max = -1;
	Byte lpf_cap = 0x0c;
	Byte lpf_bw;
#if 1
	Byte lna_gain = 7;
	Byte pgc_gain = 6;
	Byte pga_gain = 0;
	Byte ofsi = 0x20;
	Byte ofsq = 0x20;
#endif
	Byte tmp = 0;

	Ganymede* ganymede;

	ganymede = (Ganymede*) demodulator;

	ckxtal = (Long) ganymede->crystalFrequency;
	if (ckxtal == 0) {
		error = Error_INVALID_XTAL_FREQ;
		goto exit;
	}

	
	/////////////////////////////////////////////////// set debug port
	
	tmp = 0;
	error = Standard_writeTunerRegisters (demodulator, chip, 0x07, 1, &tmp); // dgb_port 0:off
	if (error) goto exit;

	/////////////////////////////////////////////////// set frequency

	if (frequency <= 400000) {
		error = Error_FREQ_OUT_OF_RANGE;
		goto exit;
	} else if (frequency > 400000 && frequency <= 440000) {
		l_band = 0;
		lna_band = 0;
	} else if (frequency > 440000 && frequency <= 484000) {
		l_band = 0;
		lna_band = 1;
	} else if (frequency > 484000 && frequency <= 533000) {
		l_band = 0;
		lna_band = 2;
	} else if (frequency > 533000 && frequency <= 587000) {
		l_band = 0;
		lna_band = 3;
	} else if (frequency > 587000 && frequency <= 645000) {
		l_band = 0;
		lna_band = 4;
	} else if (frequency > 645000 && frequency <= 710000) {
		l_band = 0;
		lna_band = 5;
	} else if (frequency > 710000 && frequency <= 782000) {
		l_band = 0;
		lna_band = 6;
	} else if (frequency > 782000 && frequency <= 860000) {
		l_band = 0;
		lna_band = 7;
	} else if (frequency > 860000 && frequency <= 1450000) {
		error = Error_FREQ_OUT_OF_RANGE;
		goto exit;
	} else if (frequency > 1450000 && frequency <= 1492000) {
		l_band = 1;
		lna_band = 0;
	} else if (frequency > 1492000 && frequency <= 1660000) {
		error = Error_FREQ_OUT_OF_RANGE;
		goto exit;
	} else if (frequency > 1660000 && frequency <= 1685000) {
		l_band = 1;
		lna_band = 1;
	} else { // frequency > 1685000
		error = Error_FREQ_OUT_OF_RANGE;
		goto exit;
	}

	// set l_band
	error = Standard_writeTunerRegisters (demodulator, chip, 0x09, 1, &l_band);
	if (error) goto exit;

	// set lna_band
	error = Standard_writeTunerRegisters (demodulator, chip, 0x14, 1, &lna_band);
	if (error) goto exit;

	switch (lna_band)
	{
	case 0:
		lna_cap = 0;
		break;
	case 1:
		lna_cap = 7;
		break;
	case 2:
		lna_cap = 15;
		break;
	case 3:
		lna_cap = 23;
		break;
	case 4:
		lna_cap = 32;
		break;
	case 5:
		lna_cap = 39;
		break;
	case 6:
		lna_cap = 48;
		break;
	case 7:
		lna_cap = 55;
		break;
	}

	// set lna_cap
	error = Standard_writeTunerRegisters (demodulator, chip, 0x13, 1, &lna_cap);
	if (error) goto exit;

	if (frequency <= 49000) {
		error = Error_FREQ_OUT_OF_RANGE;
		goto exit;
	} else if (frequency > 49000 && frequency <= 74000) {
		n_div = 48;
		n = 0;
	} else if (frequency > 74000 && frequency <= 111000) {
		n_div = 32;
		n = 1;
	} else if (frequency > 111000 && frequency <= 148000) {
		n_div = 24;
		n = 2;
	} else if (frequency > 148000 && frequency <= 222000) {
		n_div = 16;
		n = 3;
	} else if (frequency > 222000 && frequency <= 296000) {
		n_div = 12;
		n = 4;
	} else if (frequency > 296000 && frequency <= 445000) {
		n_div = 8;
		n = 5;
	} else if (frequency > 445000 && frequency <= 560000) {
		n_div = 6;
		n = 6;
	} else if (frequency > 560000 && frequency <= 890000) {
		n_div = 4;
		n = 7;
	} else if (frequency > 1187000 && frequency <= 1780000) {
		n_div = 2;
		n = 0;
	} else { // frequency >1780000
		error = Error_FREQ_OUT_OF_RANGE;
		goto exit;
	}

	// calculate frequency value
	m_lo = (Word) (n_div * 32  * frequency / ckxtal);
	lo_freq = (Word) n << 13;
	lo_freq += m_lo;
	lo_freq_15_10 = (lo_freq & (Word) 0xfc00) >> 10;
	lo_freq_9_4 = (lo_freq & (Word) 0x03f0) >> 4;
	lo_freq_3_0 = lo_freq & (Word) 0x000f;

	// set lo_freq_15_10
	error = Standard_writeTunerRegisters (demodulator, chip, 0x0d, 1, &lo_freq_15_10);
	if (error) goto exit;

	// set lo_freq_9_4
	error = Standard_writeTunerRegisters (demodulator, chip, 0x0e, 1, &lo_freq_9_4);
	if (error) goto exit;
	
	// set lo_freq_3_0
	error = Standard_writeTunerRegisters (demodulator, chip, 0x0f, 1, &lo_freq_3_0);
	if (error) goto exit;

	// write
	error = Standard_writeTunerRegisters (demodulator, chip, 0x3f, 1, &tmp);
	if (error) goto exit;

	// calculate lo_cap
	for (i = 0; i < 32; i++) {
		
		// set 0x10
		tmp = (Byte) i;
		error = Standard_writeTunerRegisters (demodulator, chip, 0x10, 1, &tmp);
		if (error) goto exit;

		// write
		tmp = 0;
		error = Standard_writeTunerRegisters (demodulator, chip, 0x3f, 1, &tmp);
		if (error) goto exit;

		// read
		tmp = 0;
		error = Standard_writeTunerRegisters (demodulator, chip, 0x01, 1, &tmp);
		if (error) goto exit;

		// get 0x02
		error = Standard_readTunerRegisters (demodulator, chip, 0x02, 1, &readTmp);
		if (error) goto exit;



		readTmp = readTmp >> 6 & 0x03;

		if (readTmp == 0 && lo_cap_min == -1)
			lo_cap_min = i;

		if (readTmp != 0 && lo_cap_min != -1 && lo_cap_max == -1)
			lo_cap_max = i - 1;
	}

	if (lo_cap_min != -1 && lo_cap_max == -1)
		lo_cap = (Byte) lo_cap_min;
	else if (lo_cap_min == -1 && lo_cap_max == -1 && readTmp == 1)
		lo_cap = 0;
	else if (lo_cap_min == -1 && lo_cap_max == -1 && readTmp == 2)
		lo_cap = 31;
	else
		lo_cap = (Byte) (lo_cap_min + lo_cap_max) / 2;

	// set lo_cap
	error = Standard_writeTunerRegisters (demodulator, chip, 0x10, 1, &lo_cap);
	if (error) goto exit;

	// set lpf_cap
	tmp = lpf_cap;
	error = Standard_writeTunerRegisters (demodulator, chip, 0x18, 1, &tmp);
	if (error) goto exit;

	// write
	tmp = 0;
	error = Standard_writeTunerRegisters (demodulator, chip, 0x3f, 1, &tmp);
	if (error) goto exit;


	/////////////////////////////////////////////////// select BW

	if (bandwidth == 5000)
		lpf_bw = 0;
	else if (bandwidth == 5500)
		lpf_bw = 1;
	else if (bandwidth == 6000)
		lpf_bw = 2;
	else if (bandwidth == 6500)
		lpf_bw = 3;
	else if (bandwidth == 7000)
		lpf_bw = 4;
	else if (bandwidth == 7500)
		lpf_bw = 5;
	else if (bandwidth == 8000)
		lpf_bw = 6;
	else if (bandwidth == 8500)
		lpf_bw = 7;
	else {
		error = Error_INVALID_BW;
		goto exit;
	}
	
	// set bandwidth
	error = Standard_writeTunerRegisters (demodulator, chip, 0x19, 1, &lpf_bw);
	if (error) goto exit;

	// write
	tmp = 0;
	error = Standard_writeTunerRegisters (demodulator, chip, 0x3f, 1, &tmp);
	if (error) goto exit;


	/////////////////////////////////////////////////// tune gain
#if 1
	// set lna_gain
	tmp = lna_gain;
	error = Standard_writeTunerRegisters (demodulator, chip, 0x12, 1, &tmp);
	if (error) goto exit;

	// set pgc_gain
	tmp = pgc_gain;
	error = Standard_writeTunerRegisters (demodulator, chip, 0x17, 1, &tmp);
	if (error) goto exit;

	// set pga_gain
	tmp = pga_gain;
	error = Standard_writeTunerRegisters (demodulator, chip, 0x15, 1, &tmp);
	if (error) goto exit;

	// set 0x22
	tmp = 0x02;
	error = Standard_writeTunerRegisters (demodulator, chip, 0x22, 1, &tmp);
	if (error) goto exit;

	// set ofsi
	tmp = ofsi;
	error = Standard_writeTunerRegisters (demodulator, chip, 0x1a, 1, &tmp);
	if (error) goto exit;

	// set ofsq
	tmp = ofsq;
	error = Standard_writeTunerRegisters (demodulator, chip, 0x1b, 1, &tmp);
	if (error) goto exit;

	// set 1c
	tmp = 0x2f;
	error = Standard_writeTunerRegisters (demodulator, chip, 0x1c, 1, &tmp);
	if (error) goto exit;

	// write
	tmp = 0;
	error = Standard_writeTunerRegisters (demodulator, chip, 0x3f, 1, &tmp);
	if (error) goto exit;
#endif

exit:

	return error;
}


TunerDescription tuner_PEACOCK = {
    PEACOCK_open,
    PEACOCK_close,
    PEACOCK_set,
    PEACOCK_scripts,
    PEACOCK_scriptSets,
    PEACOCK_ADDRESS,                /** tuner i2c address */
    1,                              /** length of tuner register address */
    0,                              /** tuner if */
    True,                           /** spectrum inverse */
    0x25,                           /** tuner id */
};
