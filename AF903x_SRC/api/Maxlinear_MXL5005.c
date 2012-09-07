/**
 * @(#)Maxlinear_MXL5005.cpp
 *
 * ==========================================================
 * Version: 2.1
 * Date:    2009.02.10
 * ==========================================================
 *
 * ==========================================================
 * History:
 *
 * Date         Author      Description
 * ----------------------------------------------------------
 *
 * 2008.07.02   Tom Lin     added tuner version
 * 2009.02.10   Yinding     update tuner code
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
#include "MXL5005.h"
#include "Maxlinear_MXL5005_Script.h"


Dword MXL_WriteI2C(
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  Byte*			pAddress,
	IN  Byte*			pData,
	IN  Dword			count
) {
    Dword error = Error_NO_ERROR;                /* Status to be returned        */
    Byte buffer[25];
    Byte numberOfRegisters = 9;
    Byte i;
    
#if (0)         /** single write */
    for (i = 0; i < count; i++) {
        buffer[0] = *(pAddress + i);
        buffer[1] = *(pData + i);
        buffer[2] = 0xFE;  /** Latch CMD request by MXL5005 Confidential Datasheet */
		error = Standard_writeTunerRegisters (demodulator, chip, buffer[0], 2, &buffer[1]);
        if (error) goto exit;
    }
#else           /** burst write (Buf <= 19 byte) */
    Byte j;
    Byte blocks;
    Byte remains;

    blocks = (Byte)(count / numberOfRegisters);
    remains = (Byte)(count % numberOfRegisters);

    for (i = 0; i < blocks; i++) {
        for (j = 0; j < numberOfRegisters * 2; j += 2) {
            buffer[j] = pAddress[i * numberOfRegisters + j / 2]; 
			buffer[j + 1] = pData[i * numberOfRegisters + j / 2];
        }
		if ((remains == 0) && (blocks == i + 1)) {  
			buffer[j]=0xFE; // Latch CMD
			error = Standard_writeTunerRegisters (demodulator, chip, buffer[0], (numberOfRegisters * 2 ) + 1, &buffer[1]);
		} else {
			error = Standard_writeTunerRegisters (demodulator, chip, buffer[0], (numberOfRegisters * 2 ), &buffer[1]);
		}
        if (error) goto exit;
    }

    if (remains) {
        for (j = 0; j< remains * 2; j += 2) {
            buffer[j] = pAddress[i * numberOfRegisters + j / 2]; 
			buffer[j + 1] = pData[i * numberOfRegisters + j / 2];
        }
        buffer[j] = 0xFE; /** Latch CMD */
		error = Standard_writeTunerRegisters (demodulator, chip, buffer[0], (remains * 2) + 1, &buffer[1]);
        if (error) goto exit;
    }  
#endif
exit:
    return (error);
}


Dword MXL5005_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    return (Error_NO_ERROR);
}


Dword MXL5005_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    return (Error_NO_ERROR);
}


Dword MXL5005_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  Word			bandwidth,
	IN  Dword			frequency
) {
    Dword status = 0;
    Tuner_struct tuner;
    Dword if_divval_temp;
    Dword error = Error_NO_ERROR;        

    Byte AGC_MASTER_BYTE;
    Byte address[104];
    Byte data[104];
    Byte temp[10];
    int count;

    AGC_Mode agc_mode;
    Tuner_Mode mode;
    Tuner_IF_Mode if_mode;   
    Dword bandwidthInHz;
    Dword if_out;
    Dword fxtal;
    Word top;
    Word if_out_load;
    Tuner_Clock_Out clock_out;
    Tuner_Div_Out div_out;
    Tuner_Cap_Select capselect;
    Tuner_RSSI en_rssi;
    Byte mod_type;
    Byte TF_Type;		
    Dword frequencyInHz;
    
    mode = MXL_DIGITAL_MODE;
    if_mode = MXL_ZERO_IF;
    bandwidthInHz = bandwidth * 1000;
    if_out = 4570000;
    fxtal = 16000000;
    agc_mode = MXL_SINGLE_AGC;
    top = 252;
    if_out_load = 200;
    clock_out = MXL_CLOCK_OUT_DISABLE;
    div_out = MXL_DIV_OUT_4;
    capselect = MXL_CAP_SEL_ENABLE;
    en_rssi = MXL_RSSI_ENABLE;
    mod_type = MXL_DVBT;
    TF_Type = MXL_TF_OFF;
    frequencyInHz = frequency * 1000;

    if (agc_mode == MXL_DUAL_AGC) /** DUAL AGC */
        AGC_MASTER_BYTE = 0x04;
    else
        AGC_MASTER_BYTE = 0x00;

    status += MXL_GetMasterControl(data, MC_SYNTH_RESET);
    address[0] = MASTER_CONTROL_ADDR;
    data[0] |= AGC_MASTER_BYTE;
    data[1] = 0xFE; /** Latch CMD */

	error = Standard_writeTunerRegisters (demodulator, chip, address[0], 2, &data[0]);
	if (error) goto exit;
        
    status += MXL5005_TunerConfig( &tuner, mode, if_mode, bandwidth, if_out, fxtal, agc_mode, top, if_out_load, 
        clock_out, div_out, capselect, en_rssi, mod_type, TF_Type);

    /**
     * retrieve the init registers to write to tuner
     */
    status += MXL_GetInitRegister(&tuner, address, data, &count);

    /**
     * End Init
     * Write Init Registers to tuner
     */
    error = MXL_WriteI2C (demodulator, chip, address, data, count);        

    /** 
     * Determine if the tuner is in Zero-IF mode or Analog Low-IF mode
     */
    if (if_mode == MXL_ZERO_IF) /** Analog or Digital Zero IF mode */
    {
        /**
         * Set MasterControl = Synth_Reset
         */
        
        status += MXL_GetMasterControl(data, MC_SYNTH_RESET);
        address[0] = MASTER_CONTROL_ADDR;
        data[0] |= AGC_MASTER_BYTE;
        data[1] = 0xFE; /** Latch CMD */

		error = Standard_writeTunerRegisters (demodulator, chip, address[0], 2, &data[0]);
        
        /** RF Tune */
        status += MXL_TuneRF(&tuner, frequencyInHz);

        /**
         * Store the calculated IF_DIVVAL value into IF_Divval
         */
        status += MXL_ControlRead(&tuner, IF_DIVVAL, &if_divval_temp);
        status += MXL_ControlWrite(&tuner, SEQ_FSM_PULSE, 0);
        status += MXL_ControlWrite(&tuner, SEQ_EXTPOWERUP, 1);
        status += MXL_ControlWrite(&tuner, IF_DIVVAL, 8);
        status += MXL_GetCHRegister(&tuner, address, data, &count);

        /**
         * Set MasterControl = Load_Start
         */
        status += MXL_GetMasterControl(temp, MC_LOAD_START);
        address[count] = MASTER_CONTROL_ADDR;
        temp[0] |= AGC_MASTER_BYTE;
        data[count] = temp[0];
        error = MXL_WriteI2C (demodulator, chip, address, data, count + 1);          

        /** Wait 30 ms for calibration to complete */
        User_delay (demodulator, 30);

        status += MXL_ControlWrite(&tuner, SEQ_FSM_PULSE, 1);
        status += MXL_ControlWrite(&tuner, IF_DIVVAL, if_divval_temp);
        status += MXL_GetCHRegister_ZeroIF(&tuner, address, data, &count);

        /**
         * Set MasterControl = Load_Start
         */
        status += MXL_GetMasterControl(temp, MC_LOAD_START);
        address[count] = MASTER_CONTROL_ADDR;
        data[count] = temp[0] | AGC_MASTER_BYTE;

        /**
         * Set MasterControl = Load_Start
         * Write all the data into chip and Latch
         */ 
        error = MXL_WriteI2C (demodulator, chip, address, data, count + 1);  
               
    }
    else /** Analog Low IF mode */
    {
        /** RF Tune;  */
        status += MXL_TuneRF(&tuner, frequencyInHz);

        status += MXL_ControlWrite(&tuner, SEQ_EXTPOWERUP, 1);
        status += MXL_ControlWrite(&tuner, SEQ_FSM_PULSE, 0);
        status += MXL_GetCHRegister(&tuner, address, data, &count);

        /** Write Chan Change Registers to tuner */
        error = MXL_WriteI2C (demodulator, chip, address, data, count);  
        /**
         * Set MasterControl = Load_Start
         */
        status += MXL_GetMasterControl(data, MC_LOAD_START);
        address[0] = MASTER_CONTROL_ADDR;
        data[0] |= AGC_MASTER_BYTE;
        data[1] = 0xFE; /** Latch CMD */
		error = Standard_writeTunerRegisters (demodulator, chip, address[0], 2, &data[0]);

        User_delay (demodulator, 100);

        /**
         * Set MasterControl = Seq_Off
         */
        status += MXL_GetMasterControl(data, MC_SEQ_OFF);
        address[0] = MASTER_CONTROL_ADDR;
        data[0] |= AGC_MASTER_BYTE;
        data[1] = 0xFE; /** Latch CMD */
		error = Standard_writeTunerRegisters (demodulator, chip, address[0], 2, &data[0]);

        status += MXL_ControlWrite(&tuner, SEQ_EXTPOWERUP, 0);
        status += MXL_GetCHRegister_LowIF(&tuner, address, data, &count);

        /** Write Chan Change Registers to tuner for Seq 3 */
		/*status += Write_I2C(DeviceID, address, data, count);*/
        error = MXL_WriteI2C (demodulator, chip, address, data, count);  
    }

exit:
    return(error);
}


Dword SwPowerCtrlMXL5005(
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  Byte			control			/** 0 for power down mode, 1 for normal operation mode */
)
{
    Dword 	status = 0;
    Dword      	error = Error_NO_ERROR;   
    Byte    		AGC_MASTER_BYTE = 0x00;  /** For Single AGC =0 */
	Byte    		address[104];
    Byte    		data[104];
    
	if (control) {
    	/** SetTuner will wake up tuner once it is called and so users don't have to call this function */
    	/** in order to wake-up MXL5005/5003S */
	} else {
	    status 	    += MXL_GetMasterControl(data, MC_POWER_DOWN);
	    address[0]  = MASTER_CONTROL_ADDR;
	    data[0] |= AGC_MASTER_BYTE;
	    data[1]  = 0xFE; /** Latch CMD */
		error = Standard_writeTunerRegisters (demodulator, chip, address[0], 2, &data[0]);
	    if (error) goto exit;
    }

exit:
    return (error);
}


TunerDescription tuner_MXL5005 = {
    MXL5005_open,
    MXL5005_close,
    MXL5005_set,
    MXL5005_scripts,
    MXL5005_scriptSets,
    MXL5005_ADDRESS,                /** tuner i2c address */
    1,                              /** length of tuner register address */
    4570000,                        /** tuner if */
    True,                          /** spectrum inverse */
    0x0D,                           /** tuner id */
};
