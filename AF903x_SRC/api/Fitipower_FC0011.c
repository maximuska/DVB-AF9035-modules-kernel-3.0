/**
 * @(#)Fitipower_FC0011.cpp
 *
 * ==========================================================
 * Version: 2.1
 * Date:    2009.03.27
 * ==========================================================
 *
 * ==========================================================
 * History:
 *
 * Date         Author      Description
 * ----------------------------------------------------------
 *
 * 2008.07.02   Tom Lin     added tuner version
 * 2009.03.27   Yinding     update tuner register settings
 * ==========================================================
 *
 * Copyright 2008 Afatech, Inc. All rights reserved.
 *
 */


//#include <stdio.h> // for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "Fitipower_FC0011_Script.h"
//#include <math.h> // for Linux


Dword FC0011_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    Dword error = Error_NO_ERROR;

    /** Control tuner enable */
	error = Standard_writeRegisterBits (demodulator, chip, Processor_LINK, p_reg_top_gpiot2_o, reg_top_gpiot2_o_pos, reg_top_gpiot2_o_len, 1);
	if (error) goto exit;
	
	error = Standard_writeRegisterBits (demodulator, chip, Processor_LINK, p_reg_top_gpiot2_en, reg_top_gpiot2_en_pos, reg_top_gpiot2_en_len, 1);
	if (error) goto exit;
	
 	error = Standard_writeRegisterBits (demodulator, chip, Processor_LINK, p_reg_top_gpiot2_on, reg_top_gpiot2_on_pos, reg_top_gpiot2_on_len, 1);
	if (error) goto exit;

	/** Control pin diode **/    
    error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh8_on, 1);
    if (error) goto exit;

    error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh8_en, 1);
    if (error) goto exit;
exit:
    return (error);
}


Dword FC0011_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    Dword error = Error_NO_ERROR;

	/** Control pin diode **/
	error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh8_on, 0);   
    if (error) goto exit;

	error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh8_en, 0);
    if (error) goto exit;

exit:
	return (error);
}


Dword FC0011_set (
	IN  Demodulator*		demodulator,
	IN  Byte			chip,
	IN  Word			bandwidth,
	IN  Dword			frequency
) {
    /* It's necessary for setting frequency and bandwidth*/
    Dword error = Error_NO_ERROR;
    Word fractional, xin;
    Byte  reg[18], floor_xdiv, fp,fa, vco_cal, vco_select, round_xdiv, rc_cal_forcing;
    Dword fvco;

    if ( (frequency < 45000) || (frequency > 1000000) )
    {
		goto exit;
    }
	//=========================== <arios> end


    /***********************************************************/
    /****************** initialization *************************/
    /***********************************************************/

	/**************add by roger****************/
	reg[7] = 0x0f;
	reg[8] = 0x3e;
	reg[10] = 0xb8;
	error = Standard_writeTunerRegisters (demodulator, chip, 7, 1, &reg[7]);
    if (error) goto exit;
	error = Standard_writeTunerRegisters (demodulator, chip, 8, 1, &reg[8]);
    if (error) goto exit;
    error = Standard_writeTunerRegisters (demodulator, chip, 10, 1, &reg[10]);
    if (error) goto exit;
	/**************add by roger****************/

	reg[11] = 0x80;  
    reg[13] = 0x04;
    error = Standard_writeTunerRegisters (demodulator, chip, 11, 1, &reg[11]);
    if (error) goto exit;
	error = Standard_writeTunerRegisters (demodulator, chip, 13, 1, &reg[13]);
    if (error) goto exit;

    /***********************************************************/
    /****************** start frequency setting ****************/
    /***********************************************************/

    /* generate the frequency of VCO and VCO_divider */

    if (frequency < 54000)
    {
	    fvco = frequency * 64;
	    reg[5] = 0x82;
    }
    else if (frequency <108000)
    {
	    fvco = frequency * 32;
	    reg[5] = 0x42;
    }
    else if (frequency <216000)
    {
	    fvco = frequency * 16;
	    reg[5] = 0x22;
    }
    else if (frequency <432000)
    {
	    fvco = frequency * 8;
	    reg[5] = 0x12;
    }
    else 
    {
	    fvco = frequency * 4;
	    reg[5] = 0x0a;
    }

    /* calculate XIN for Fractional PLL with 18 MHz reference frequency */
	floor_xdiv = (Byte)(fvco/18000);
	fractional = (Word)(fvco - (floor_xdiv * 18000));
    fractional = ((fractional<<15)/18000);
    //if (fractional >=(Word)pow(2.0,14.0)) fractional = fractional + (Word)pow(2.0,15.0); /* sign extension */
    if (fractional >=(Word)16384) fractional = fractional + (Word)32768;
    if (fractional == 0) xin = 0;
    else if (fractional >0 && fractional < 511) xin = 0x200;
    else if (fractional > 65025) xin = 0xfe00;
    else xin = fractional;
	    
    reg[3] = (Byte)(xin>>8) ; /* xin with 9 bit resolution */
    reg[4] = (Byte)(xin & 0x00ff);
    
    /* calculate fp and fa */
    if ((fvco-floor_xdiv*18000)>=9000) round_xdiv = floor_xdiv + 1; //round operation
    else round_xdiv = floor_xdiv;
    fp = (Byte)(round_xdiv/8);
    fa = round_xdiv - (fp<<3); 
    if (fa < 2)
    {
	    fp = fp - 1;
	    fa = fa + 8;
    }

	if (fp > 31)
	{
		fp = fp & 0x1f;
		fa = fa & 0x0f;
	}

	if (fa >= fp)
	{
		goto exit;
	}
	//=========================== <arios> end

    reg[1] = fa;
    reg[2] = fp;

	/* select bandwidth */
    if (bandwidth == 8000)	reg[6] = 0x0;
    else if (bandwidth == 7000) reg[6] = 0x40;
    else reg[6] = 0x80;

    /* Rough VCO selection */
    if (fvco < 2320000)
    {
		vco_select = 0;
		reg[6] = reg[6] & ~(0x18);
	}
	else if (fvco < 3080000) 
	{
		vco_select = 1;
		reg[6] = reg[6] & ~(0x18);		// reset VCO select
		reg[6] = reg[6] | 0x10;
	}
    else
    { 
    	vco_select = 2;
		reg[6] = reg[6] & ~(0x18);		// reset VCO select
    	reg[6] = reg[6] | 0x08;
	}

    /* fix clock out */
    reg[6] = reg[6] | 0x20;   

    /** Write freq parameters to tuner */
    error = Standard_writeTunerRegisters (demodulator, chip, 1, 1, &reg[1]);
    if (error) goto exit;
    error = Standard_writeTunerRegisters (demodulator, chip, 2, 1, &reg[2]);
    if (error) goto exit;
    error = Standard_writeTunerRegisters (demodulator, chip, 3, 1, &reg[3]);
    if (error) goto exit;
    error = Standard_writeTunerRegisters (demodulator, chip, 4, 1, &reg[4]);
    if (error) goto exit;
    error = Standard_writeTunerRegisters (demodulator, chip, 5, 1, &reg[5]);
    if (error) goto exit;
    error = Standard_writeTunerRegisters (demodulator, chip, 6, 1, &reg[6]);
    if (error) goto exit;

    /***********************************************************/
    /****************** start VCO selction *********************/
    /***********************************************************/

    /*calibration VCO*/
    vco_cal = 0x80;
    error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal); /* vco_cal restart */
    if (error) goto exit;

    vco_cal = 0x00;
    error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal); /* vco_cal run */
    if (error) goto exit;

    /* read vco calibration value vco_cal Note for read_reg need read twice */
    error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal);
    if (error) goto exit;
	User_delay (demodulator, 10);
    error = Standard_readTunerRegisters (demodulator, chip, 14, 1, &vco_cal);
    if (error) goto exit;

	if ( ((vco_cal) & 0x40) == 0)
	{		
		error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpiot3_on, 1);
		if (error) goto exit;
		error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpiot3_en, 1);
		if (error) goto exit;
		error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpiot3_o, 1);
		if (error) goto exit;
		User_delay (demodulator, 10);
		error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpiot3_o, 0);
		if (error) goto exit;
		User_delay (demodulator, 10);

		error = Standard_writeTunerRegisters (demodulator, chip, 1, 1, &reg[1]);
		if (error) goto exit;
		error = Standard_writeTunerRegisters (demodulator, chip, 2, 1, &reg[2]);
		if (error) goto exit;
		error = Standard_writeTunerRegisters (demodulator, chip, 3, 1, &reg[3]);
		if (error) goto exit;
		error = Standard_writeTunerRegisters (demodulator, chip, 4, 1, &reg[4]);
		if (error) goto exit;
		error = Standard_writeTunerRegisters (demodulator, chip, 5, 1, &reg[5]);
		if (error) goto exit;
		error = Standard_writeTunerRegisters (demodulator, chip, 6, 1, &reg[6]);
		if (error) goto exit;
		error = Standard_writeTunerRegisters (demodulator, chip, 7, 1, &reg[7]);
		if (error) goto exit;
		error = Standard_writeTunerRegisters (demodulator, chip, 8, 1, &reg[8]);
		if (error) goto exit;
		error = Standard_writeTunerRegisters (demodulator, chip, 10, 1, &reg[10]);
		if (error) goto exit;
		error = Standard_writeTunerRegisters (demodulator, chip, 11, 1, &reg[11]);
		if (error) goto exit;
		error = Standard_writeTunerRegisters (demodulator, chip, 13, 1, &reg[13]);
		if (error) goto exit;

		/*calibration VCO*/
		vco_cal = 0x80;
		error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal); /* vco_cal restart */
		if (error) goto exit;

		vco_cal = 0x00;
		error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal); /* vco_cal run */
		if (error) goto exit;

		/* read vco calibration value vco_cal Note for read_reg need read twice */
		error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal);
		if (error) goto exit;
		User_delay (demodulator, 10);
		error = Standard_readTunerRegisters (demodulator, chip, 14, 1, &vco_cal);
		if (error) goto exit;
	}

    /* vco selection */
    vco_cal = vco_cal & 0x3f;
    switch(vco_select) {
	    case 0:
		    if (vco_cal < 0x08)
		    {
		    	reg[6] = reg[6] & ~(0x18); /* reset VCO select */
		    	reg[6] = reg[6] | 0x10; /* vco_select = 1; */
                reg[6] = reg[6] | 0x20;   /* fix clock out */
                error = Standard_writeTunerRegisters (demodulator, chip, 6, 1, &reg[6]);
                if (error) goto exit;

				/* recalibration */
		        vco_cal = 0x80;
                error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal);/* vco_cal restart */
                if (error) goto exit;

				vco_cal = 0x00;
                error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal);/* vco_cal run */
                if (error) goto exit;
                break;
		    }
		    else 
		    {
		    	reg[6] = reg[6] & ~(0x18); /* reset VCO select */
			   	reg[6] = reg[6] | 0x00; /* vco_select = 0; */
                reg[6] = reg[6] | 0x20;   /* fix clock out */
                error = Standard_writeTunerRegisters (demodulator, chip, 6, 1, &reg[6]);
                if (error) goto exit;
                break;
		    }
	     case 1:
		    if (vco_cal < 0x05)
		    {
		    	reg[6] = reg[6] & ~(0x18); /* reset VCO select */
			   	reg[6] = reg[6] | 0x08; /* vco_select = 2; */
                reg[6] = reg[6] | 0x20;   /* fix clock out */
                error = Standard_writeTunerRegisters (demodulator, chip, 6, 1, &reg[6]);
                if (error) goto exit;

				/* recalibration */
                vco_cal = 0x80;
                error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal);/* vco_cal restart */
				if (error) goto exit;

				vco_cal = 0x00;
                error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal);/* vco_cal run */
                if (error) goto exit;
                break;
		    }
		    else if (vco_cal > 0x30)
		    {
		    	reg[6] = reg[6] & ~(0x18); /* reset VCO select */
			   	reg[6] = reg[6] | 0x00; /* vco_select = 0; */
                reg[6] = reg[6] | 0x20;   /* fix clock out */
                error = Standard_writeTunerRegisters (demodulator, chip, 6, 1, &reg[6]);
                if (error) goto exit;

				/* recalibration */
			    vco_cal = 0x80;
                error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal);/*vco_cal restart*/
                if (error) goto exit;

				vco_cal = 0x00;
                error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal);/*vco_cal run*/
                if (error) goto exit;
                break;
		    }
		    else
		    {
                reg[6] = reg[6] & ~(0x18); /* reset VCO select */
			   	reg[6] = reg[6] | 0x10; /* vco_select = 1; */
                reg[6] = reg[6] | 0x20;   /* fix clock out */
			   	error = Standard_writeTunerRegisters (demodulator, chip, 6, 1, &reg[6]);
                if (error) goto exit;
                break;
		    }
	     default:
		    if (vco_cal > 0x35)
		    {
                reg[6] = reg[6] & ~(0x18); /* reset VCO select */
			   	reg[6] = reg[6] | 0x10; /* vco_select = 1; */
                reg[6] = reg[6] | 0x20;   /* fix clock out */
                error = Standard_writeTunerRegisters (demodulator, chip, 6, 1, &reg[6]);
                if (error) goto exit;

				/* recalibration */
			    vco_cal = 0x80;
                error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal);/* vco_cal restart */
                if (error) goto exit;
               
				vco_cal = 0x00;
                error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal);/* vco_cal run */
                if (error) goto exit;
                break;
		    }
		    else
		    {
                reg[6] = reg[6] & ~(0x18); /* reset VCO select */
			   	reg[6] = reg[6] | 0x08; /* vco_select = 2; */
                reg[6] = reg[6] | 0x20;   /* fix clock out */
                error = Standard_writeTunerRegisters (demodulator, chip, 6, 1, &reg[6]);
                if (error) goto exit;
                break;

		    }
    } 

	vco_cal = 0x00;
	error = Standard_writeTunerRegisters (demodulator, chip, 14, 1, &vco_cal);
    if (error) goto exit;
	User_delay (demodulator, 10);
    error = Standard_readTunerRegisters (demodulator, chip, 14, 1, &vco_cal);
    if (error) goto exit;

    reg[16] = 0x0b;
    
	User_delay (demodulator, 10);
    error = Standard_readTunerRegisters (demodulator, chip, 13, 1, &reg[13]);
    if (error) goto exit;

	rc_cal_forcing = reg[13] | 0x10;

	error = Standard_writeTunerRegisters (demodulator, chip, 13, 1, &rc_cal_forcing);
    if (error) goto exit;

	error = Standard_writeTunerRegisters (demodulator, chip, 16, 1, &reg[16]);
    if (error) goto exit;


exit:
	return(error);
}


TunerDescription tuner_FC0011 = {
    FC0011_open,                   /** needed function*/
    FC0011_close,                  /** needed function*/
    FC0011_set,                    /** needed function*/
    FC0011_scripts,                /** Afa's tuner setting */
    FC0011_scriptSets,             /** Afa's tuner setting */
    FC0011_ADDRESS,                /** tuner i2c address */
    1,                             /** length of tuner register address */
    0,                             /** tuner if frequency*/
    True,                          /** spectrum inverse */
    0x28,                          /** tuner id */
};
