/**
 * @(#)Afa_E4000.cpp
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
 * Copyright 2005 Afatech, Inc. All rights reserved.
 *
 */

//#include <stdio.h> //for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "e4000.h"
#include "Elonics_E4000.h"
#include "Elonics_E4000_Script.h"


Demodulator* E4000_demodulator;
Byte E4000_chip;
Word E4000_bandwidth;
Dword E4000_frequency; 
Dword Ref_clk=26000;  //Tuner reference clock frequency (kHz)

Dword E4000_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
	) {
	E4000_demodulator = demodulator;
	E4000_chip = chip;

    E4000_tunerreset ();
    E4000_Tunerclock();
   // E4000_filtercal();
    E4000_Qpeak();
    E4000_DCoffloop();
    //E4000_commonmode();
    E4000_GainControlinit();
	return (Error_NO_ERROR);
}


Dword E4000_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
	) 
{
	E4000_demodulator = demodulator;
	E4000_chip = chip;
	Dword error = 0;
	Byte buffer[1];
	buffer[0] = 0x00;
	error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x00, 1, buffer);
	//Powers down tuner (will recover if tuner initialisation is subsequently run)
	return (Error_NO_ERROR);
}


Dword E4000_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  Word			bandwidth,
	IN  Dword			frequency
) {
	E4000_demodulator = demodulator;
	E4000_chip = chip;
	E4000_bandwidth=bandwidth;
	E4000_frequency=frequency;
	E4000_Gainmanual();
	E4000_PLL();
	E4000_LNAfilter();
	E4000_IFfilter();
	E4000_freqband();
	E4000_DCoffLUT();
    E4000_Gainauto();
	Dword error = 0;
return (Error_NO_ERROR);	
}




TunerDescription tuner_E4000 = {
    E4000_open,
    E4000_close,
    E4000_set,
    E4000_scripts,
    E4000_scriptSets,
    0xC8,                              /** tuner i2c address */
    1,                              /** length of tuner register address */
    0,                       /** tuner if */
    False,                           /** spectrum inverse */
    0xFF,                           /** tuner id */
};
