/**
 * $Header: 
 * (C) Copyright 2001 Philips Semiconductors, All rights reserved
 *
 * This source code and any compilation or derivative thereof is the sole
 * property of Philips Corporation and is provided pursuant to a Software
 * License Agreement.  This code is the proprietary information of Philips
 * Corporation and is confidential in nature.  Its use and dissemination by
 * any party other than Philips Corporation is strictly limited by the
 * confidential information provisions of the Agreement referenced above.
 *-----------------------------------------------------------------------------
 * FILE NAME:    tmbslTDA18291.c
 *
 * DESCRIPTION:  Function for the digimob tuner TDATDA18291
 *
 * DOCUMENT REF: DigiMob - ObjectiveSpecification_V4.2.doc - 21 April 2005
 *
 * NOTES:
 *-----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 * Standard include files:
 *-----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 * Project include files:
 *-----------------------------------------------------------------------------
 */
#include "TDA18291local.h"
#include "standard.h"

/*-----------------------------------------------------------------------------
 * Types and defines:
 *-----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 * Global data:
 *-----------------------------------------------------------------------------
 */


/* default instance */
tm18291object_t g18291Instance[] = 
{
    {
		{
			Null,   /* Demodulator */
			0x01    /* chip */
		},

        False,						/* init [False : instance is not initialized] */
        0,							/* uHwAddress [HwId not set] */
        {   Null, Null/*, Null,*/	/* systemFunc [system function not initialized] */
            /*Null, Null, Null*/
        },
        tmPowerOff,						/* default power state		 */
        {
			CUSTOM_BOARD_DEF,			/* uBoard [default configuration structure] */
			TDA18291_NB_AGC_RANGES,	/* Nb [number of lines] */
			0,							/* Index [start index] */
			{
				{0,0},
				{5,1},
				{10,2},
				{15,3},
				{20,4},
				{25,5},
				{30,6},
				{35,7},
				{40,8},
				{45,9},
				{50,10},
				{55,11},
				{60,12},
				{65,13},
				{70,14},
				{75,15},
				{80,64},
				{85,65},
				{90,66},
				{95,67},
				{100,68},
				{105,69},
				{110,70},
				{115,71},
				{120,72},
				{125,73},
				{130,74},
				{135,75},
				{140,76},
				{145,77},
				{150,78},
				{155,79},
				{160,192},
				{165,193},
				{170,194},
				{175,195},
				{180,196},
				{185,197},
				{190,198},
				{195,199},
				{200,200},
				{205,201},
				{210,202},
				{215,203},
				{220,204},
				{225,205},
				{230,206},
				{235,207},
				{240,320},
				{245,321},
				{250,322},
				{255,323},
				{260,324},
				{265,325},
				{270,326},
				{275,327},
				{280,328},
				{285,329},
				{290,330},
				{295,331},
				{300,332},
				{305,333},
				{310,334},
				{315,335},
				{320,448},
				{325,449},
				{330,450},
				{335,451},
				{340,452},
				{345,453},
				{350,454},
				{355,455},
				{360,456},
				{365,457},
				{370,458},
				{375,459},
				{380,460},
				{385,461},
				{390,462},
				{395,463},
				{400,464},
				{405,465},
				{410,466},
				{415,467},
				{420,468},
				{425,469},
				{430,470},
				{435,471},
				{440,472},
				{445,473},
				{450,474},
				{455,475},
				{460,476},
				{465,477},
				{470,478},
				{475,479},
				{480,480},
				{485,481},
				{490,482},
				{495,483},
				{500,484},
				{505,485},
				{510,486},
				{515,487},
				{520,488},
				{525,489},
				{530,490},
				{535,491},
				{540,492},
				{545,493},
				{550,494},
				{555,495},
				{560,496},
				{565,497},
				{570,498},
				{575,499},
				{580,500},
				{585,501},
				{590,502},
				{595,503},
				{600,504},
				{605,505},
				{610,506},
				{615,507},
				{620,508},
				{625,509},
				{630,510},
				{635,511},
			},
		},
		{	
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,		/* pTunerReg[register default values]; */
			0x00,0x00,0x00,0x00,0x00,0x00,0x00		
        },
        0,							/* LO_FreqProg [RF programmed] */
        0,							/* uTickEnd [end tick value] */
		{	
			1,1,0,0,1,365,3,	/* UserData [tm18291UserData_t] */
			0,0,0,0,0,0,0,0,
			0x01,0x0C,0x00,0x02,0x01,0x00,0x80,0x00,0x90,0x86,
			0,0,0,0,0,26000,
			0,0,0,0,0,0,0,
			2,1,0
		}
	}
};

/*-----------------------------------------------------------------------------
 * Internal Prototypes:
 *-----------------------------------------------------------------------------
 */
Bool_
TDA18291Init (
    tmUnitSelect_t TunerUnit    /* I: Tuner unit number */
    );
        
Bool_
TDA18291CalcPLL (
    tmUnitSelect_t  TunerUnit,	/*  I: Tuner unit number */
    UInt32          LO_Freq		/*  I: Frequency in hertz */
    );

Bool_ 
TDA18291GetGainIndex(
    ptm18291object_t pObject,	/*  I: Tuner object */
    UInt32          *uIndex		/*  O: Gain */
    );

Bool_ 
TDA18291WaitTick(
    ptm18291object_t pObj   /* I: Tuner unit number */
    );

Bool_ 
TDA18291InitTick(
    ptm18291object_t pObj,  /* I: Tuner unit number */
    UInt16          wTime					/* I: time to wait for */
    );

/*-----------------------------------------------------------------------------
 * Exported functions:
 *-----------------------------------------------------------------------------
 */
Bool_    SY_Write2(UInt32  uAddress,
                 UInt32  uSubAddress,
                 UInt32  uNbData,
                 UInt32* pDataBuff)
{
	Bool_					RetStatus = False;
	ptm18291object_t		pObj;
	UInt32					dwError = 0;
	UInt8					uBuffer[39];
	UInt32					i;

	for (i = 0; i < uNbData; i++)
	{
		uBuffer[i] = (UInt8)pDataBuff[i];
	}

	pObj = &g18291Instance[0];
	dwError = Standard_writeTunerRegisters (pObj->AFAInfo.demodulator, pObj->AFAInfo.chip,
	                                        (unsigned short)uSubAddress, (UInt8)uNbData, uBuffer);
    if (dwError == 0) RetStatus = True;

	return (RetStatus);
};

Bool_    SY_Read2(UInt32  uAddress,
                UInt32  uSubAddress,
                UInt32  uNbData,
                UInt32* pDataBuff)
{
	Bool_					RetStatus = False;
	ptm18291object_t		pObj;
	UInt32					dwError = 0;
	UInt8					uBuffer[39];
	UInt32					i;

	pObj = &g18291Instance[0];
        dwError = Standard_readTunerRegisters (pObj->AFAInfo.demodulator, pObj->AFAInfo.chip, (UInt16)uSubAddress, (UInt8)uNbData, uBuffer);
	if (dwError == 0)
	{
		RetStatus = True;
	
		for (i = 0; i < uNbData; i++)
		{
			pDataBuff[i] = (UInt32)uBuffer[i];
		}
	}

	return (RetStatus);
};

/*-----------------------------------------------------------------------------
 * FUNCTION:    tmbslTDA18291Init:
 *
 * DESCRIPTION: create an instance of a TDA18291 tuner
 *
 * RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
 *              TM_OK
 *  
 * NOTES:
 *-----------------------------------------------------------------------------
 */
tmErrorCode_t
tmbslTDA18291Init(
    tmUnitSelect_t     TunerUnit,    /*  I: Tuner unit number */
    tmbslTuParam_t     Param         /*  I: setup parameters */
    )
{
    /*----------------------
     * test input parameters
     *----------------------
     * test the max number
	 */
    if (TunerUnit > TDA18291_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    /*----------------------
     * initialize the object
     *----------------------
     * return if already initialized
	 */
    if(g18291Instance[TunerUnit].init == True)
        return TM_OK;

    /*----------------
     * init the object
     *----------------
     * initialize the object by default values
	 */
    g18291Instance[TunerUnit].uHwAddress = Param.uHwAddress;
    g18291Instance[TunerUnit].systemFunc = Param.systemFunc;
    g18291Instance[TunerUnit].init = True;

    return TM_OK;
}


/*-----------------------------------------------------------------------------
 * FUNCTION:    tmbslTDA18291DeInit:
 *
 * DESCRIPTION: destroy an instance of a TDA18291 tuner
 *
 * RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
 *              TMBSL_ERR_TUNER_NOT_INITIALIZED
 *              TM_OK
 *
 * NOTES:
 *-----------------------------------------------------------------------------
 */
tmErrorCode_t 
tmbslTDA18291DeInit (
    tmUnitSelect_t  TunerUnit     /*  I: Tuner unit number */
    )
{
    /*----------------------
     * test input parameters
     *----------------------
     * test the instance number
	 */
    if (TunerUnit > TDA18291_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    /* test the object */
    if (g18291Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

    /*-------------------------
     * De-initialize the object
     *-------------------------
	 */
    g18291Instance[TunerUnit].init = False;

    return TM_OK;
}


/*-----------------------------------------------------------------------------
 * FUNCTION:    tmbslTDA18291GetSWVersion:
 *
 * DESCRIPTION: Return the version of this device
 *
 * RETURN:      TM_OK
 *
 * NOTES:       Values defined in the tmTDA18291local.h file
 *-----------------------------------------------------------------------------
 */
tmErrorCode_t
tmbslTDA18291GetSWVersion (
    ptmSWVersion_t     pSWVersion        /*  I: Receives SW Version */
    )
{
    pSWVersion->compatibilityNr = TDA18291_BSL_COMP_NUM;
    pSWVersion->majorVersionNr  = TDA18291_BSL_MAJOR_VER;
    pSWVersion->minorVersionNr  = TDA18291_BSL_MINOR_VER;

    return TM_OK;
}


/*-----------------------------------------------------------------------------
 * FUNCTION:    tmbslTDA18291SetPowerState:
 *
 * DESCRIPTION: Set the power state of this device.
 *
 * RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
 *              TMBSL_ERR_TUNER_NOT_INITIALIZED
 *              TM_OK
 *
 * NOTES:       NOT implemented - inputs from stephane needed
 *-----------------------------------------------------------------------------
 */
tmErrorCode_t
tmbslTDA18291SetPowerState (
    tmUnitSelect_t  TunerUnit,   /*  I: Tuner unit number */
    tmPowerState_t  powerState   /*  I: Power state of this device */
)
{
	ptm18291UserData_t	pUserData;
	ptm18291object_t		pObj; 
    
    /*----------------------
     * test input parameters
     *----------------------
     * test the instance number
	 */
    if (TunerUnit > TDA18291_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    /* test the object */
    if (g18291Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;
    

	/* pObj & pUserData initialisation */
	pObj = &g18291Instance[TunerUnit];
	pUserData = &(pObj->UserData);

    /*--------------------------------------------------------------------------
     * set the value
     * 4 possble values:  tmPowerOn  tmPowerOff  tmPowerStandy  tmPowerSuspend
	 *--------------------------------------------------------------------------
	 */

    switch (powerState)
	{
		case tmPowerOn:
			pUserData->PDIC = 0;		/* IC is active */
			pUserData->PDIF = 0;		/* IF output is active	 */
			pUserData->h03b5 = 1;		/* default value */
			pUserData->PDRF = 0;		/* RF is active */
			pUserData->PDRefBuff = 0;	/* REFBUFF is active */
			pUserData->PDSYNTH = 0;		/* SYNTH is active */
			pUserData->PDVCO = 0;		/* VCO is active */
			pUserData->PD_Xtout = 0;	/* default value */
			break;
	
		case tmPowerOff:
			pUserData->PDIC = 1;		/* IC is off */
			pUserData->PDIF = 1;		/* IF output is off	*/
			pUserData->h03b5 = 1;		/* default value */
			pUserData->PDRF = 1;		/* RF is off */
			pUserData->PDRefBuff = 1;	/* REFBUFF is off */
			pUserData->PDSYNTH = 1;		/* SYNTH is off */
			pUserData->PDVCO = 1;		/* VCO is off */
			pUserData->PD_Xtout = 0;	/* default value */
			break;
        case tmPowerStandby:
        case tmPowerSuspend:
            break;            
	}
    pObj->curPowerState = powerState;

    return TM_OK;
}


/*-----------------------------------------------------------------------------
 * FUNCTION:    tmbslTDA18291GetPowerState:
 *
 * DESCRIPTION: Get the power state of this device.
 *
 * RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
 *              TMBSL_ERR_TUNER_NOT_INITIALIZED
 *              TM_OK
 *
 * NOTES:
 *-----------------------------------------------------------------------------
 */
tmErrorCode_t
tmbslTDA18291GetPowerState (
    tmUnitSelect_t      TunerUnit,      /*  I: Tuner unit number */
    tmPowerState_t   *pPowerState       /*  O: Power state of this device */
)
{
    /*----------------------
     * test input parameters
     *----/------------------
     * test the instance number
	 */
    if (TunerUnit > TDA18291_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    /* test the object */
    if (g18291Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

    /*--------------
     * get the value
     *--------------
	 */
    *pPowerState = g18291Instance[TunerUnit].curPowerState;

    return TM_OK;
}


/*-----------------------------------------------------------------------------
 * FUNCTION:    tmbslTDA18291Write:
 *
 * DESCRIPTION: Write in the tuner.
 *
 * RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
 *              TMBSL_ERR_TUNER_NOT_INITIALIZED
 *              TMBSL_ERR_IIC_ERR
 *              TM_OK
 *
 * NOTES:      uIndex: IN parameter containing the HW Sub Address as specified in 
 *			   the datasheet (i.e. looks like 0xX0)      
 *-----------------------------------------------------------------------------
 */
tmErrorCode_t
tmbslTDA18291Write (
    tmUnitSelect_t      TunerUnit,      /*  I: Tuner unit number */
    UInt32              uIndex,         /*  I: Start index to write */
    UInt32              uNbBytes,       /*  I: Number of bytes to write */
    UInt32*             puBytes         /*  I: Pointer on an array of bytes */
)
{
	
    UInt32   uCounter;
	
    /*----------------------
     * test input parameters
     *----------------------
     * test the instance number
	 */
    if (TunerUnit > TDA18291_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    /* test the object */
    if (g18291Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

    /* test the parameters. uIndex is: 0x0X */
    if ((uIndex + uNbBytes) > TDA18291_NB_REGISTERS)
        return TMBSL_ERR_TUNER_BAD_PARAMETER;

    /*--------------
     * set the value
     *--------------
     * save the values written in the tuner
	 */
	 for (uCounter = 0; uCounter < uNbBytes; uCounter++)
       g18291Instance[TunerUnit].pTunerReg[uCounter+uIndex] = puBytes[uCounter];

    /* write in the tuner */
    if (g18291Instance[TunerUnit].systemFunc.SY_Write(
        g18291Instance[TunerUnit].uHwAddress,
        uIndex, uNbBytes, &(g18291Instance[TunerUnit].pTunerReg[uIndex])) != 1)
        return TMBSL_ERR_IIC_ERR;
	

    return TM_OK;
}


/*-----------------------------------------------------------------------------
 * FUNCTION:    tmbslTDA18291WriteBit:
 *
 * DESCRIPTION: Write in the tuner.
 *
 * RETURN:      TM_ERR_NOT_SUPPORTED
 *
 * NOTES:
 *-----------------------------------------------------------------------------
 */
tmErrorCode_t
tmbslTDA18291WriteBit (
    tmUnitSelect_t      TunerUnit,      /*  I: Tuner unit number */
    UInt32              uIndex,         /*  I: Start index to write */
    UInt32              uBitMask,       /*  I: bit mask */
    UInt32              uBitValue       /*  I: bit value */
)
{
    return TM_ERR_NOT_SUPPORTED;
}


/*-----------------------------------------------------------------------------
 * FUNCTION:    tmbslTDA18291Read:
 *
 * DESCRIPTION: Read in the tuner.
 *
 * RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
 *              TMBSL_ERR_TUNER_NOT_INITIALIZED
 *              TMBSL_ERR_TUNER_BAD_PARAMETER
 *              TMBSL_ERR_IIC_ERR
 *              TM_OK
 *
 * NOTES:       
 *-----------------------------------------------------------------------------
 */
tmErrorCode_t
tmbslTDA18291Read (
    tmUnitSelect_t      TunerUnit,      /*  I: Tuner unit number */
    UInt32              uIndex,         /*  I: Start index to read */
    UInt32              uNbBytes,       /*  I: Number of bytes to read */
    UInt32*             puBytes         /*  I: Pointer on an array of bytes */
)
{
	
    /*----------------------
     * test input parameters
     *----------------------
     * test the instance number
	 */
    if (TunerUnit > TDA18291_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    /* test the object */
    if (g18291Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

    /* test the object */
    if (uNbBytes > TDA18291_NB_REGISTERS)
        return TMBSL_ERR_TUNER_BAD_PARAMETER;

    /*--------------
     * get the value
     *--------------
	 */
    if (uIndex == -1)
    {

		/* read the status byte if index is -1 */
		/* Return the complete register. Mask is applied in higher layer */
        if (g18291Instance[TunerUnit].systemFunc.SY_Read(
            g18291Instance[TunerUnit].uHwAddress,
            0, uNbBytes, puBytes) != 1) return TMBSL_ERR_IIC_ERR;
    }
    else
    {
        UInt32 uCounter;

        /* return value previously written */
        for (uCounter = uIndex; (uCounter < uIndex + uNbBytes) && (uCounter < TDA18291_NB_REGISTERS); uCounter++)
            puBytes[uCounter-uIndex] = g18291Instance[TunerUnit].pTunerReg[uCounter];
		
    }

    return TM_OK;
}


/*-----------------------------------------------------------------------------
 * FUNCTION:    tmbslTDA18291SetRf:
 *
 * DESCRIPTION: Calculate i2c register & write in TDA18291
 *
 * RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
 *              TMBSL_ERR_TUNER_NOT_INITIALIZED
 *              TMBSL_ERR_TUNER_BAD_PARAMETER
 *              TMBSL_ERR_IIC_ERR
 *              TM_OK
 *
 * NOTES:       
 *-----------------------------------------------------------------------------
 */
tmErrorCode_t
tmbslTDA18291SetRf(
    tmUnitSelect_t		TunerUnit,  /*  I: Tuner unit number */
    UInt32				LO_Freq     /*  I: Frequency in hertz */
)
{	
	UInt8	uCounter = 0;
	
	ptm18291object_t		pObj;
	ptm18291UserData_t	pUserData;

	/* pObj & pUserData initialisation */
	pObj = &g18291Instance[TunerUnit];
	pUserData = &(pObj->UserData);
		
	/*----------------------
     * test input parameters
     *----------------------
     * test the instance number
	 */
    if (TunerUnit > TDA18291_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    /* test the object */
    if (g18291Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;
	
	/*--------------
     * set the value
     *--------------
	 * Bytes h05 h06 h07 h08 h09
	 * initialised in TDA18291CalcPLL
	 * calculate the tuner reg h5X h6X h7X h8X h9X
	 */
	pUserData->Flo_max08 = 987000;
	pUserData->Flo_max09 = 877000;
	pUserData->Flo_max10 = 790000;
	pUserData->Flo_max11 = 718000;
	pUserData->Flo_max12 = 658000;
	pUserData->Flo_max13 = 607000;
	pUserData->Flo_max14 = 564000;
	pUserData->Flo_max15 = 526000;
    TDA18291CalcPLL(TunerUnit, LO_Freq);
    	
	/* Byte h03 */
	pUserData->PDIC = 0;		/* IC is active */
	pUserData->PDIF = 0;		/* IF output is active */	
	pUserData->h03b5 = 1;		/* default value */
    pUserData->PDRF = 0;		/* RF is active */
    pUserData->PDRefBuff = 0;	/* REFBUFF is active */
	pUserData->PDSYNTH = 0;		/* SYNTH is active */
	pUserData->PDVCO = 0;		/* VCO is active */
	pUserData->PD_Xtout = 0;	/* Xtout is active */
	pObj->pTunerReg[TDA18291_REG_H03] = pUserData->PDIC << 7 | pUserData->PDIF << 6 | pUserData->h03b5 << 5 | pUserData->PDRF << 4 | pUserData->PDRefBuff << 3 | pUserData->PDSYNTH << 2 | pUserData->PDVCO << 1 | pUserData->PD_Xtout << 0;
	
	/* Byte h04 */
	pUserData->h04b3tob0 = 0x0C; /* enable xtal out (bit3)*/
	pObj->pTunerReg[TDA18291_REG_H04] = pUserData->Ref_Freq << 6 | pUserData->AGCBusEn << 5 | pUserData->AGCext << 4 | pUserData->h04b3tob0 << 0;

    /* Bytes h05 h06 h07 h08 h09 */
	/* calculated in TDA18291CalcPLL function */
	pUserData->h09b7tob6 = 0;	/* default value */
	pObj->pTunerReg[TDA18291_REG_H09] = pUserData->h09b7tob6 << 6 | pObj->pTunerReg[TDA18291_REG_H09] << 0;
     
	/* Bytes h0A h0B */
	/* Search for the agc range corresponding to wanted gain */
    while (pUserData->AGCGain > pObj->config.Map[uCounter].uGain)
		uCounter++;
	pUserData->AGCBB = pObj->config.Map[uCounter].uAGC_BB;
	pUserData->h0Ab7 = pUserData->Enable_LNA;	/* enable or disable the LNA	 */
	pUserData->h0Ab1tob0 = 0x02;	/* default value */
	pUserData->h0Bb7tob6 = 0;	    /* default value */
	pObj->pTunerReg[TDA18291_REG_H0A] = pUserData->h0Ab7 << 7 | (UInt8)(pUserData->AGCBB >> 6) << 4 | pUserData->FC << 2 | pUserData->h0Ab1tob0 << 0 ;
	pObj->pTunerReg[TDA18291_REG_H0B] = pUserData->h0Bb7tob6 << 6 | (UInt8)(pUserData->AGCBB << 2) >> 2;

    /* Byte h0C */
	pUserData->h0C = 0x80;		/* default value */
	pObj->pTunerReg[TDA18291_REG_H0C] = pUserData->h0C << 0;
     
	/* Byte h0D */
	pUserData->h0D = 0x00;			/* default value */
	pObj->pTunerReg[TDA18291_REG_H0D] = pUserData->h0D << 0;
	
	/* Byte h0E */
	pUserData->h0E = 0x90;		/* default value */
	pObj->pTunerReg[TDA18291_REG_H0E] = pUserData->h0E << 0;

	/* Byte h0F */
	pUserData->h0F = 0x86;		/* default value */
	pObj->pTunerReg[TDA18291_REG_H0F] = pUserData->h0F << 0;
		

	if (pUserData->FlagI2CWrite){
		/* Write h03 to h0F */
		if (pObj->systemFunc.SY_Write(
			pObj->uHwAddress,
			3, 0x0d, &(pObj->pTunerReg[TDA18291_REG_H03])) != 1)

			return TMBSL_ERR_IIC_ERR;
		}
	

	/* return value	 */
    return TM_OK;
}


/*-----------------------------------------------------------------------------
 * FUNCTION:    tmbslTDA18291GetRf:
 *
 * DESCRIPTION: Get the frequency programmed in the tuner
 *
 * RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
 *              TMBSL_ERR_TUNER_NOT_INITIALIZED
 *              TM_OK
 *
 * NOTES:       The value returned is the one stored in the object
 *-----------------------------------------------------------------------------
 */
tmErrorCode_t
tmbslTDA18291GetRf(
    tmUnitSelect_t  TunerUnit,     /*  I: Tuner unit number */
    UInt32*         pLO_Freq       /*  O: Frequency in hertz */
    )
{
    /*----------------------
     * test input parameters
     *----------------------
     * test the instance number
	 */
    if (TunerUnit > TDA18291_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    /* test the object */
    if (g18291Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

    /*--------------
     * get the value
     *--------------
     * the read function can't be used
	 */
    *pLO_Freq = g18291Instance[TunerUnit].LO_FreqProg*1000;

    return TM_OK;
}


/*-----------------------------------------------------------------------------
 * FUNCTION:    tmbslTDA18291SetConfig:
 *
 * DESCRIPTION: Set the config of the TDA18291
 *
 * RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
 *              TMBSL_ERR_TUNER_NOT_INITIALIZED
 *              TM_ERR_NOT_SUPPORTED
 *              TMBSL_ERR_TUNER_BAD_PARAMETER
 *              TM_OK
 *
 * NOTES:
 *-----------------------------------------------------------------------------
 */
tmErrorCode_t
tmbslTDA18291SetConfig(
    tmUnitSelect_t     TunerUnit,  /*  I: TunerUnit number */
    UInt32             uItemId,    /*  I: Identifier of the item to modify */
    UInt32             uValue      /*  I: Value to set for the config item */
    )
{

    /*----------------------
     * test input parameters
     *----------------------
     * test the instance number
	 */
    if (TunerUnit > TDA18291_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    /* test the object*/
    if (g18291Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

    /*--------------
     * set the value
     *--------------
	 */
    switch((tm18291cfgIndex_t)uItemId)
    {
		case BOARD:
		switch (uValue & 0xffff0000)
		{
			case OM5768_BOARD_DEF:
				/* Default Xtal Freq is 26 MHz */
				g18291Instance[TunerUnit].UserData.Ref_Freq = 2;
				g18291Instance[TunerUnit].UserData.LO_XTALFreq = gTableXtalFreq[2];
				/* Default Xtal Out Mode is OFF */
				/*g18291Instance[TunerUnit].UserData.h04b3tob0 = 4; */
                g18291Instance[TunerUnit].UserData.PDRefBuff = 0;
                g18291Instance[TunerUnit].UserData.PD_Xtout = 0;
				/* Default AGC control is from external pin */
				g18291Instance[TunerUnit].UserData.AGCBusEn = 0;
				g18291Instance[TunerUnit].UserData.AGCext = 1;				

				break;
			case CUSTOM_BOARD_DEF:
				/* do nothing more than setting the default values */
				break;                
        	default:
			/* board not supported */
			return TM_ERR_NOT_SUPPORTED;
		}
	    /* store board */
		g18291Instance[TunerUnit].config.uBoard = uValue;
		break;

		case SET_CUTOFF_FREQ:	
			/* Cut-off Frequency, added by max */
			g18291Instance[TunerUnit].UserData.FC = (UInt8)uValue;
			break;
			
		/* backdoor functions */
		case FEINIT:	
			TDA18291Init( TunerUnit );
			break;

		case AGC_BUS_ENABLE:
			g18291Instance[TunerUnit].UserData.AGCBusEn = (UInt8)uValue;
			break;

		case AGC_EXT:
			g18291Instance[TunerUnit].UserData.AGCext = (UInt8)uValue;
			break;

		case AGC_GAIN_VALUE:
			g18291Instance[TunerUnit].UserData.AGCGain = (UInt32)uValue;
			break;	
			
		case LO_XTAL_FREQ_INDEX:
			if ((UInt8)uValue==3)
			{
				uValue=1;
			}
			g18291Instance[TunerUnit].UserData.Ref_Freq = (UInt8)uValue;
			g18291Instance[TunerUnit].UserData.LO_XTALFreq = gTableXtalFreq[uValue];
			break;

		case XTAL_MODE:
			if (uValue)
			{
				/* Activate XTout */
                g18291Instance[TunerUnit].UserData.PDRefBuff = 0;
                g18291Instance[TunerUnit].UserData.PD_Xtout = 0;
			}
			else
			{
				/* Disable XTout */
                g18291Instance[TunerUnit].UserData.PDRefBuff = 1;
                g18291Instance[TunerUnit].UserData.PD_Xtout = 1;            
			}
			break;
		case CUT_OFF_IND:
			g18291Instance[TunerUnit].UserData.CutOffIndex = (UInt8)uValue;
			g18291Instance[TunerUnit].UserData.FC   = gTableCutOffVal[uValue];
			break;

		case ENABLE_LNA:
			g18291Instance[TunerUnit].UserData.Enable_LNA = (UInt8)uValue;
			break;
	}
    return TM_OK;
}


/*-----------------------------------------------------------------------------
 * FUNCTION:    tmbslTDA18291GetConfig:
 *
 * DESCRIPTION: Get the config of the TDA18291
 *
 * RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
 *              TMBSL_ERR_TUNER_NOT_INITIALIZED
 *              TM_OK
 *
 * NOTES:       
 *-----------------------------------------------------------------------------
 */
tmErrorCode_t
tmbslTDA18291GetConfig(
    tmUnitSelect_t     TunerUnit,  /*  I: Tuner unit number */
    UInt32             uItemId,    /*  I: Identifier of the item to modify */
    UInt32*            puValue     /*  I: Value to set for the config item */
    )
{
	UInt32 uCounter = 0;

    /*----------------------
     * test input parameters
     *----------------------
     * test the instance number
	 */
    if (TunerUnit > TDA18291_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    /* test the object */
    if (g18291Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

    /*--------------
     * set the value
     *--------------
	 */
    switch((tm18291cfgIndex_t)uItemId)
    {
		case BOARD:
			*puValue = g18291Instance[TunerUnit].config.uBoard;
			break;

		case AGC_BUS_ENABLE:
			*puValue = g18291Instance[TunerUnit].UserData.AGCBusEn;
			break;

		case AGC_EXT:
			*puValue = g18291Instance[TunerUnit].UserData.AGCext;
			break;

		case AGC_GAIN_INDEX:
			if ( g18291Instance[TunerUnit].UserData.AGCBusEn )
			{
				/* Return the index of the field of type tm18291agcMap_t */
				/* that corresponds to the current setting of gain */
				uCounter = 0;
				while ( g18291Instance[TunerUnit].config.Map[uCounter].uGain < g18291Instance[TunerUnit].UserData.AGCGain)
					uCounter ++;

				*puValue = uCounter;
			}
			else
				/* Return the index of the field of type tm18291agcMap_t */
				/* that corresponds to the gain read in the tuner */
				TDA18291GetGainIndex(&g18291Instance[TunerUnit], puValue);
			break;	

		case AGC_GAIN_VALUE:
			if ( g18291Instance[TunerUnit].UserData.AGCBusEn )
				*puValue = g18291Instance[TunerUnit].UserData.AGCGain;
			else
			{
					
				TDA18291GetGainIndex(&g18291Instance[TunerUnit], &uCounter);
				*puValue = g18291Instance[TunerUnit].config.Map[uCounter].uGain;/*g18291Instance[TunerUnit].config.Map[uCounter].uGain; */
				
			}
			break;
			
		case LO_XTAL_FREQ_INDEX:
			
			*puValue = g18291Instance[TunerUnit].UserData.Ref_Freq;
			break;

		case LO_XTAL_FREQ_VALUE:
			*puValue = g18291Instance[TunerUnit].UserData.LO_XTALFreq;
			break;

		case XTAL_MODE:
			*puValue = g18291Instance[TunerUnit].UserData.PD_Xtout;
			break;

		case ENABLE_LNA:
			*puValue = g18291Instance[TunerUnit].UserData.Enable_LNA;
			break;
	}

    return TM_OK;
}


/*-----------------------------------------------------------------------------
 * Internal functions:
 *-----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 * FUNCTION:    TDA18291Init:
 *
 * DESCRIPTION: Initialisation of the tuner
 *				The protocol used to initialise the tuner is the same as for the 
 *				programming of the tuner to a new RF
 *
 * RETURN:      always True
 *
 * NOTES:       
 *-----------------------------------------------------------------------------
 */
Bool_
TDA18291Init (
    tmUnitSelect_t  TunerUnit   /* I: tuner object */
    )
{ 
	UInt32 uDefaultFreq = 600000000; /* Default LO frequency; */

	tmbslTDA18291SetRf( TunerUnit ,uDefaultFreq);

	return TM_TRUE;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    TDA18291CalcPLL:
 *
 * DESCRIPTION: Calculate the LO fractionnal PLL settings
 *
 * RETURN:      Always True
 *
 * NOTES:       This function doesn't write in the tuner
 *-----------------------------------------------------------------------------
 */
Bool_
TDA18291CalcPLL (
    tmUnitSelect_t  TunerUnit,      /*  Tuner unit number */
    UInt32          LO_Freq         /*  Local oscillator frequency in hertz */
    )
{   
    UInt8   LO_PostdivTmp;
    UInt32  LO_IntTmp;
    UInt32  LO_FracTmp;
    UInt32  LO_FreqTmp;

    ptm18291object_t          pObj;
    ptm18291UserData_t        pUserData;

    /* pObj & pUserData initialisation */
    pObj = &g18291Instance[TunerUnit];
    pUserData = &(pObj->UserData);

        /* LO Postdiv calculation */
    if      (LO_Freq > 493500000)
        pUserData->LO_Postdiv = 1;  
    else if (LO_Freq > 246750000)
        pUserData->LO_Postdiv = 2;
    else if (LO_Freq > 123374000)
        pUserData->LO_Postdiv = 4;
    else if (LO_Freq > 61687000)
        pUserData->LO_Postdiv = 8;
    else                
        pUserData->LO_Postdiv = 16;
         
    /* LO Prescaler calculation */
    LO_FreqTmp = (LO_Freq / 1000) * pUserData->LO_Postdiv;
    if (pUserData->LO_Postdiv >= 1)
    {   
        if      (LO_FreqTmp > pUserData->Flo_max09)
            pUserData->LO_Presc = 8;    
        else if (LO_FreqTmp > pUserData->Flo_max10)
                pUserData->LO_Presc = 9;
        else if (LO_FreqTmp > pUserData->Flo_max11)
            pUserData->LO_Presc = 10;
        else if (LO_FreqTmp > pUserData->Flo_max12)
            pUserData->LO_Presc = 11;
        else if (LO_FreqTmp > pUserData->Flo_max13)
            pUserData->LO_Presc = 12;
        else if (LO_FreqTmp > pUserData->Flo_max14)
            pUserData->LO_Presc = 13;
        else if (LO_FreqTmp >= pUserData->Flo_max15)
            pUserData->LO_Presc = 14;
        else if (LO_FreqTmp < pUserData->Flo_max15)
            pUserData->LO_Presc = 15;
    }
    else
    {   
        pUserData->LO_Postdiv = 1;
        pUserData->LO_Presc = 8;
    }
    
    /* VCO Frequency calculation */
    pUserData->LO_VCOFreq = (LO_FreqTmp * pUserData->LO_Presc);
    
    /* LO_IntTmp calculation */
    LO_IntTmp = pUserData->LO_VCOFreq / (4 * pUserData->LO_XTALFreq);
        
    /* LO_FracTmp calculation */
    LO_FracTmp = (pUserData->LO_VCOFreq * 100) / 4;
    LO_FracTmp -= (LO_IntTmp * pUserData->LO_XTALFreq * 100);
    LO_FracTmp /= (pUserData->LO_XTALFreq / 100);
            
    /* LO_Int & LO_Frac correction */
    if (LO_FracTmp > 7500) {
        pUserData->LO_Int  = 2 * (LO_IntTmp) + 1 - 128;
        pUserData->LO_Frac = ((LO_FracTmp - 5000) * 83886) / 100;
    }    
    else if (LO_FracTmp >= 2500){
        pUserData->LO_Int  = 2 * (LO_IntTmp) - 128;   
        pUserData->LO_Frac = (LO_FracTmp * 83886) / 100;
    }
    else if (LO_FracTmp < 2500){
        pUserData->LO_Int  = 2 * (LO_IntTmp - 1 ) + 1 - 128;  
        pUserData->LO_Frac = ((LO_FracTmp + 5000) * 83886) / 100;
    }

    /* LO_Postdiv bits inversion correction */
    switch (pUserData->LO_Postdiv){
        case 1:
                LO_PostdivTmp = 1;
            break;
        case 2: LO_PostdivTmp = 2;
            break;
        case 4: LO_PostdivTmp = 3;
            break;
        case 8: LO_PostdivTmp = 4;
            break;
        case 16:LO_PostdivTmp = 5;
            break;
        default:LO_PostdivTmp = 0;
            break;
        }

    /* Bytes h5X h6X h7X h8X h9X */
    pObj->pTunerReg[TDA18291_REG_H05] = (UInt8)(pUserData->LO_Int >> 1);
    pObj->pTunerReg[TDA18291_REG_H06] = (UInt8)(pUserData->LO_Int << 7) | (UInt8)(pUserData->LO_Frac >> 16);
    pObj->pTunerReg[TDA18291_REG_H07] = (UInt8)(pUserData->LO_Frac >> 8);
    pObj->pTunerReg[TDA18291_REG_H08] = (UInt8)(pUserData->LO_Frac);
    pObj->pTunerReg[TDA18291_REG_H09] = (UInt8)(pUserData->LO_Presc << 5) >> 2 | LO_PostdivTmp;

    /* return value */
    return True;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    TDA18291GetGainIndex
 *
 * DESCRIPTION: this function will read the gain AGCBB of the TDA18291
 *				( i.e. combination of AGC1 and AGC2)
 *				and will determine the associated element of the Map table 
 *				of the object config and return its index				
 *
 * RETURN:      nothing
 *
 * NOTES:       
 *-----------------------------------------------------------------------------
 */
Bool_ 
TDA18291GetGainIndex(
    ptm18291object_t pObject,	/*  I: Tuner object */
    UInt32          *uIndex		/*  O: Gain */
    )
{
	UInt32 puBytes[16];
	UInt8 uGainReg[2];
	UInt8 uGainMsb;
	UInt32 uCounter, uGainTemp;

   if 	(pObject->systemFunc.SY_Read(
			pObject->uHwAddress,
            0, 16, puBytes) != 1) return False;

	uGainReg[0] = (UInt8) (puBytes[1] & 0x1F);
	uGainReg[1] = (UInt8) (puBytes[2] >> 4);

	/* Get bit AGC1[2] */
	uGainMsb = (uGainReg[0] & 0x10) >> 4;
	/* keep bits AGC1[1], AGC1[0] and AGC2[5] AGC1[4] */
	uGainReg[0] = (uGainReg[0] & 0x0F);

	uGainTemp = (uGainMsb << 8) | (uGainReg[0] << 4) | uGainReg[1];

	uCounter = 0;
	while ( pObject->config.Map[uCounter].uAGC_BB < uGainTemp)
		uCounter ++;

	*uIndex = uCounter;

	return True;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    TDA18291InitTick
 *
 * DESCRIPTION: this function will delay for the number of millisecond
 *
 * RETURN:      nothing
 *
 * NOTES:       
 *-----------------------------------------------------------------------------
 */
#if 0
Bool_ 
TDA18291InitTick(
    ptm18291object_t pObj,    /*  I: Tuner unit number */
    UInt16          wTime       /*  I: time to wait for */
)
{
    /* get current tick */
    UInt32 uCurrentTick = pObj->systemFunc.SY_GetTickTime();

    /* calculate end tick */
    pObj->uTickEnd = (UInt32)wTime;
    pObj->uTickEnd += pObj->systemFunc.SY_GetTickPeriod()/2;
    pObj->uTickEnd /= pObj->systemFunc.SY_GetTickPeriod();
    pObj->uTickEnd += uCurrentTick;

    /* always add 1 because of rounding issue */
    if (wTime)
        pObj->uTickEnd++;

    /* test overflow */
    if (pObj->uTickEnd < uCurrentTick)
        return False;
    else
        return True;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    TDA18291WaitTick
 *
 * DESCRIPTION: this function will block for the number of millisecond
 *
 * RETURN:      True if time has elapsed else False
 *
 * NOTES:       
 *-----------------------------------------------------------------------------
 */

Bool_ 
TDA18291WaitTick(
    ptm18291object_t pObj     /* I: Tuner unit number */
)
{
    /* test if time has elapsed */
    if (pObj->systemFunc.SY_GetTickTime() >= pObj->uTickEnd)
        return True;
    else
        return False;
}
#endif
