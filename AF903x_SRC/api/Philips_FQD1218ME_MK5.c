/*
 * @(#)Philips_FQD1218ME_MK5.cpp
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
#include "Philips_FQD1218ME_MK5_Script.h"


Dword FQD1218ME_MK5_open (
    IN  Demodulator*    demodulator,
    IN  Byte            chip
) {
    Dword error = Error_NO_ERROR;
    Ganymede* ganymede;
    Byte buffer[11] = {0};

    ganymede = (Ganymede*) demodulator;

    buffer[4] = 0x67;
    buffer[5] = 0x1F;
    buffer[6] = 0x01;

    ganymede->tunerDescription->tunerAddress = 0x86;
    error = Standard_writeTunerRegisters (demodulator, chip, 0x0000, 11, buffer);
    ganymede->tunerDescription->tunerAddress = FQD1218ME_MK5_ADDRESS;

    return (error);
}


Dword FQD1218ME_MK5_close (
    IN  Demodulator*    demodulator,
    IN  Byte            chip
) {
    return (Error_NO_ERROR);
}


Dword FQD1218ME_MK5_set (
    IN  Demodulator*    demodulator,
    IN  Byte            chip,
    IN  Word            bandwidth,
    IN  Dword           frequency
) {
    Dword error = Error_NO_ERROR;
    Ganymede* ganymede;
    const typedef enum { CB2 = 0, AB} MK5_1;
    const typedef enum { DB1 = 0, DB2, CB1, BB} MK5_2;
    Byte buffer_1[2] = {0};
    Byte buffer_2[4] = {0};
    Dword LO = 0;
    Word N = 0;

    ganymede = (Ganymede*) demodulator;
    LO = frequency + ganymede->tunerDescription->ifFrequency / 1000;
    N = (Word)(LO * 6 / 1000);
    
    buffer_1[AB] = 0x20;

    buffer_2[DB1] = (Byte)(N >> 8);
    buffer_2[DB2] = (Byte)N;

    if (frequency >= 51000 && frequency <= 157000) {/** Low band*/
        if (LO < 180000) {
            buffer_1[CB2] = 0x9C;
            buffer_2[CB1] = 0xBC;
            buffer_2[BB] = 0x01;
        } else {
            buffer_1[CB2] = 0xDC;
            buffer_2[CB1] = 0xF4;
            buffer_2[BB] = 0x01;
        }
    } else if (frequency >= 164000 && frequency <= 442000) {/** Mid band*/
        if (LO < 366000) {
            buffer_1[CB2] = 0x9C;
            buffer_2[CB1] = 0xBC;
            buffer_2[BB] = 0x02;
        }else {
            buffer_1[CB2] = 0xDC;
            buffer_2[CB1] = 0xF4;
            buffer_2[BB] = 0x02;
        }
    } else if (frequency >= 450000 && frequency <= 866000) {/** High band*/
        if (LO < 662000) {
            buffer_1[CB2] = 0x9C;
            buffer_2[CB1] = 0xBC;
            buffer_2[BB] = 0x04;
        } else if (LO > 840000) {
            buffer_1[CB2] = 0xDC;
            buffer_2[CB1] = 0xFC;
            buffer_2[BB] = 0x04;
        } else {
            buffer_1[CB2] = 0xDC;
            buffer_2[CB1] = 0xF4;
            buffer_2[BB] = 0x04;
        }
    } else {
        error = Error_FREQ_OUT_OF_RANGE;
        goto exit;
    }
    
    error = Standard_writeTunerRegisters (demodulator, chip, 0x0000, 2, buffer_1);
    if (error) goto exit;

    error = Standard_writeTunerRegisters (demodulator, chip, 0x0000, 4, buffer_2);

exit:
    return (error);
}


TunerDescription tuner_FQD1218ME_MK5 = {
    FQD1218ME_MK5_open,
    FQD1218ME_MK5_close,
    FQD1218ME_MK5_set,
    FQD1218ME_MK5_scripts,
    FQD1218ME_MK5_scriptSets,
    FQD1218ME_MK5_ADDRESS,          /** tuner i2c address */
    0,                              /** length of tuner register address */
    36130000,                       /** tuner if */
    True,                           /** spectrum inverse */
    0x30,                           /** tuner id */
};
