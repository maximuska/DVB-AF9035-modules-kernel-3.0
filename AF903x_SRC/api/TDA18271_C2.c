//-----------------------------------------------------------------------------
// $Header: 
// (C) Copyright 2001 NXP Semiconductors, All rights reserved
//
// This source code and any compilation or derivative thereof is the sole
// property of NXP Corporation and is provided pursuant to a Software
// License Agreement.  This code is the proprietary information of NXP
// Corporation and is confidential in nature.  Its use and dissemination by
// any party other than NXP Corporation is strictly limited by the
// confidential information provisions of the Agreement referenced above.
//-----------------------------------------------------------------------------
// FILE NAME:    tmbslTDA18271_C2.c
//
// DESCRIPTION:  Function for the Hybrid silicon tuner TDA18271
//
// DOCUMENT REF: 
//
// NOTES:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// Standard include files:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// Project include files:
//-----------------------------------------------------------------------------
//
#include "TDA18271local_C2.h"
#include "TDA18271_C2.h"
#include "TDA18271StaticInstance_C2.h"
#include "standard.h"

//-----------------------------------------------------------------------------
// Types and defines:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// Global data:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// Internal Prototypes:
//-----------------------------------------------------------------------------
//
Bool_    SY_Write_C2(UInt32  uAddress,
                 UInt32  uSubAddress,
                 UInt32  uNbData,
                 UInt32* pDataBuff)
{
	Bool_					RetStatus = False;
	ptmTDA18271Object_t_C2		pObj;
	UInt32					dwError = 0;
	UInt8					uBuffer[39];
	UInt32					i;

	for (i = 0; i < uNbData; i++)
	{
		uBuffer[i] = (UInt8)pDataBuff[i];
	}

	pObj = &gTDA18271Instance_C2[0];

   	dwError = Standard_writeTunerRegisters (pObj->AFAInfo_C2.demodulator, pObj->AFAInfo_C2.chip,
                                    (unsigned short)uSubAddress, (UInt8)uNbData, uBuffer);

	if (dwError == 0) RetStatus = True;

	return (RetStatus);
};

Bool_    SY_Read_C2(UInt32  uAddress,
                UInt32  uSubAddress,
                UInt32  uNbData,
                UInt32* pDataBuff)
{
	Bool_					RetStatus = False;
	ptmTDA18271Object_t_C2		pObj;
	UInt32					dwError = 0;
	UInt8					uBuffer[39];
	UInt32					i;

	pObj = &gTDA18271Instance_C2[0];

    dwError = Standard_readTunerRegisters (pObj->AFAInfo_C2.demodulator, pObj->AFAInfo_C2.chip, (UInt16)uSubAddress, (UInt8)uNbData, uBuffer);
	
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


Bool_    SY_Write_Slave_C2(UInt32  uAddress,
                 UInt32  uSubAddress,
                 UInt32  uNbData,
                 UInt32* pDataBuff)
{
	Bool_					RetStatus = False;
	ptmTDA18271Object_t_C2		pObj;
	UInt32					dwError = 0;
	UInt8					uBuffer[39];
	UInt32					i;

	for (i = 0; i < uNbData; i++)
	{
		uBuffer[i] = (UInt8)pDataBuff[i];
	}

	pObj = &gTDA18271Instance_C2[1];
		
	dwError = Standard_writeTunerRegisters (pObj->AFAInfo_C2.demodulator, pObj->AFAInfo_C2.chip,
	                                        (unsigned short)uSubAddress, (UInt8)uNbData, uBuffer);

    if (dwError == 0) RetStatus = True;

	return (RetStatus);
};

Bool_    SY_Read_Slave_C2(UInt32  uAddress,
                UInt32  uSubAddress,
                UInt32  uNbData,
                UInt32* pDataBuff)
{
	Bool_					RetStatus = False;
	ptmTDA18271Object_t_C2		pObj;
	UInt32					dwError = 0;
	UInt8					uBuffer[39];
	UInt32					i;

	pObj = &gTDA18271Instance_C2[1];

    dwError = Standard_readTunerRegisters (pObj->AFAInfo_C2.demodulator, pObj->AFAInfo_C2.chip, (UInt16)uSubAddress, (UInt8)uNbData, uBuffer);
	
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
//-----------------------------------------------------------------------------
// Exported functions:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271Init:
//
// DESCRIPTION: create an instance of a TDA18271_C2 Tuner
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TM_OK
//  
// NOTES:
//-----------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271Init_C2
(
 tmUnitSelect_t     TunerUnit,    //  I: Tuner unit number
 tmbslTuParam_t_C2     Param         //  I: setup parameters
 )
{
	ptmTDA18271Object_t_C2		pObj = Null;
	tmErrorCode_t			ret  = TM_OK;

	//----------------------
	// test input parameters
	//----------------------
	// test the max number
	if (TunerUnit > TDA18271_MAX_UNITS_C2)
		return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2;

	//----------------------
	// initialize the Object
	//----------------------
	// pObj initialization
	getInstance_C2(TunerUnit, &pObj);

	// return if already initialized
	if (pObj != Null && pObj->init == True)
		return TM_OK;

	//----------------
	// init the Object
	//----------------
	// initialize the Object
//	if (pObj == Null)
//	{
		ret = allocInstance_C2(TunerUnit, &pObj);
		if (ret != TM_OK || pObj == Null)
			return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;		

		// initialize the Object by default values
		pObj->SystemFunc = Param.systemFunc;
		pObj->uHwAddress = Param.uHwAddress;
		pObj->init = True;
//	}

	return TM_OK;
}


//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271DeInit:
//
// DESCRIPTION: destroy an instance of a TDA18271 Tuner
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_OK
//
// NOTES:
//-----------------------------------------------------------------------------
//
tmErrorCode_t 
tmbslTDA18271DeInit_C2
(
 tmUnitSelect_t  TunerUnit     //  I: Tuner unit number
 )
{
	ptmTDA18271Object_t_C2		pObj = Null;
	tmErrorCode_t			ret  = TM_OK;

	//----------------------
	// test input parameters
	//----------------------
	// test the instance number
	if (TunerUnit > TDA18271_MAX_UNITS_C2)
		return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2;

	//----------------------
	// De-initialize the Object
	//----------------------
	// pObj initialization
	getInstance_C2(TunerUnit, &pObj);

	// return if already initialized
	if (pObj == Null || pObj->init == False)
		return TM_OK;

	//----------------
	// Deinit the Object
	//----------------
	// initialize the Object
	if (pObj != Null)
	{
		pObj->init = False;
		ret = deAllocInstance_C2(TunerUnit);
	}

	return ret;
}

//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271GetSWVersion:
//
// DESCRIPTION: Return the version of this device
//
// RETURN:      TM_OK
//
// NOTES:       Values defined in the tmTDA18271Local.h file
//-----------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271GetSWVersion_C2
(
 ptmSWVersion_t_C2     pSWVersion        //  I: Receives SW Version 
 )
{
	pSWVersion->compatibilityNr = TDA18271_BSL_COMP_NUM_C2;
	pSWVersion->majorVersionNr  = TDA18271_BSL_MAJOR_VER_C2;
	pSWVersion->minorVersionNr  = TDA18271_BSL_MINOR_VER_C2;

	return TM_OK;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271SetPowerState_C2:
//
// DESCRIPTION: Set the power state of this device.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271SetPowerState_C2
(
 tmUnitSelect_t			TunerUnit,		//  I: Tuner unit number
 tmTDA18271PowerState_t_C2	powerState_C2		//  I: Power state of this device
 )
{
	ptmTDA18271Object_t_C2		pObj = Null;
	tmErrorCode_t			ret  = TM_OK;

	//----------------------
	// test input parameters
	//----------------------
	// test the max number
	if (TunerUnit > TDA18271_MAX_UNITS_C2)
		return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2;

	// pObj initialization
	ret = getInstance_C2(TunerUnit, &pObj);
	if (ret != TM_OK)
		return ret;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	// set power state
	return TDA18271SetPowerState_C2(pObj, powerState_C2);
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271SetPowerState_C2:
//
// DESCRIPTION: Set the power state of this device.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
TDA18271SetPowerState_C2(
								  ptmTDA18271Object_t_C2		pObj,		// I: tuner Object
								  tmTDA18271PowerState_t_C2		powerState	// I: Power state of this device
								  )
{
	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	switch (powerState)
	{
	case tmPowerNormalMode_C2:					
		// set SM bits
		pObj->I2CMap.uBx05.bF.SM = 0x00;
		pObj->I2CMap.uBx05.bF.SM_LT = 0x00;
		pObj->I2CMap.uBx05.bF.SM_XT = 0x00;
		break;

	case tmPowerSleepMode_C2:
		// set SM bits
		pObj->I2CMap.uBx05.bF.SM = 0x01;
		pObj->I2CMap.uBx05.bF.SM_LT = 0x01;
		pObj->I2CMap.uBx05.bF.SM_XT = 0x01;
		break;

	case tmPowerStandbyWith16MHz_C2:
		// set SM bits
		pObj->I2CMap.uBx05.bF.SM = 0x01;
		pObj->I2CMap.uBx05.bF.SM_LT = 0x01;
		pObj->I2CMap.uBx05.bF.SM_XT = 0x00;
		break;

	case tmPowerStandbyWith16MHzAndLoopThrough_C2:
		// set SM bits
		pObj->I2CMap.uBx05.bF.SM = 0x01;
		pObj->I2CMap.uBx05.bF.SM_LT = 0x00;
		pObj->I2CMap.uBx05.bF.SM_XT = 0x00;
		break;

	case tmPowerStandbyWithLoopThrough_C2:
		// set SM bits
		pObj->I2CMap.uBx05.bF.SM = 0x01;
		pObj->I2CMap.uBx05.bF.SM_LT = 0x00;
		pObj->I2CMap.uBx05.bF.SM_XT = 0x01;
		break;

	default:
		// power state not supported
		return TM_ERR_NOT_SUPPORTED_C2;
	}

	// store powerstate 
	pObj->curPowerState = powerState;

	return TM_OK;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271GetPowerState_C2:
//
// DESCRIPTION: Get the power state of this device.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_OK
//
// NOTES:
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271GetPowerState_C2
(
 tmUnitSelect_t				TunerUnit,		//  I: Tuner unit number
 tmTDA18271PowerState_t_C2	*pPowerState_C2	//  O: Power state of this device
 )
{
	ptmTDA18271Object_t_C2		pObj = Null;
	tmErrorCode_t			ret  = TM_OK;

	//------------------------------
	// test input parameters
	//------------------------------
	// test the instance number
	if (TunerUnit > TDA18271_MAX_UNITS_C2)
		return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2;

	// pObj initialization
	ret = getInstance_C2(TunerUnit, &pObj);
	if (ret != TM_OK)
		return ret;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	// get power state
	return TDA18271GetPowerState_C2(pObj, pPowerState_C2);
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271GetPowerState_C2:
//
// DESCRIPTION: Get the power state of this device.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_OK
//
// NOTES:
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
TDA18271GetPowerState_C2(
								  ptmTDA18271Object_t_C2		pObj,		// I: tuner Object
								  tmTDA18271PowerState_t_C2	*pPowerState// I: Power state of this device
								  )
{
	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	//----------------------
	// get the value
	//----------------------
	if ((pObj->I2CMap.uBx05.bF.SM == 0x00) && (pObj->I2CMap.uBx05.bF.SM_LT == 0x00) && (pObj->I2CMap.uBx05.bF.SM_XT == 0x00))
		*pPowerState = tmPowerNormalMode_C2;
	else if ((pObj->I2CMap.uBx05.bF.SM == 0x01) && (pObj->I2CMap.uBx05.bF.SM_LT == 0x01) && (pObj->I2CMap.uBx05.bF.SM_XT == 0x01))
		*pPowerState = tmPowerSleepMode_C2;
	else if ((pObj->I2CMap.uBx05.bF.SM == 0x01) && (pObj->I2CMap.uBx05.bF.SM_LT == 0x01) && (pObj->I2CMap.uBx05.bF.SM_XT == 0x00))
		*pPowerState = tmPowerStandbyWith16MHz_C2;
	else if ((pObj->I2CMap.uBx05.bF.SM == 0x01) && (pObj->I2CMap.uBx05.bF.SM_LT == 0x00) && (pObj->I2CMap.uBx05.bF.SM_XT == 0x00))
		*pPowerState = tmPowerStandbyWith16MHzAndLoopThrough_C2;
	else if ((pObj->I2CMap.uBx05.bF.SM == 0x01) && (pObj->I2CMap.uBx05.bF.SM_LT == 0x00) && (pObj->I2CMap.uBx05.bF.SM_XT == 0x01))
		*pPowerState = tmPowerStandbyWithLoopThrough_C2;
	else
		*pPowerState = tmPowerNotSupported_C2;

	return TM_OK;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271SetStandardMode_C2:
//
// DESCRIPTION: Set the standard mode of this device.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271SetStandardMode_C2
(
 tmUnitSelect_t					TunerUnit,		//  I: Tuner unit number
 tmTDA18271StandardMode_t_C2		StandardMode	//  I: Standard mode of this device
 )
{
	ptmTDA18271Object_t_C2		pObj = Null;
	tmErrorCode_t			ret  = TM_OK;

	//----------------------
	// test input parameters
	//----------------------
	// test the max number
	if (TunerUnit > TDA18271_MAX_UNITS_C2)
		return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2;

	// pObj initialization
	ret = getInstance_C2(TunerUnit, &pObj);
	if (ret != TM_OK)
		return ret;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	// set standard mode
	return TDA18271SetStandardMode_C2(pObj, StandardMode);
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271SetStandardMode_C2:
//
// DESCRIPTION: Set the standard mode of this device.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
TDA18271SetStandardMode_C2(
									ptmTDA18271Object_t_C2			pObj,		// I: tuner Object
									tmTDA18271StandardMode_t_C2	StandardMode//  I: Standard mode of this device
									)
{
	Bool_ customIF = FALSE;
	Bool_ customLPFc = FALSE;
	UInt8 stdValue = 0;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	// set custom IF flag
	if (((pObj->Config.uPROTOCOLSTEP & 0x02) >> 1) == 0x01)
		customIF = TRUE;

	// set custom LPFc flag
	if (((pObj->Config.uPROTOCOLSTEP & 0x01) >> 0) == 0x01)
		customLPFc = TRUE;

	// set uIF & Std
	switch (StandardMode)
	{
	case tmDigital_TV_ATSC_6MHz_C2:
		// set IF frequency 			
		if (!customIF)
			pObj->Config.uIF = 3250000;
		// set Std bit
		stdValue = 0x1C;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;

	case tmDigital_TV_DVBT_7MHz_C2:
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 3500000;
		// set Std bit
		stdValue = 0x1C;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;

	case tmDigital_TV_DVBT_8MHz_C2:
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 4000000;	
		// set Std bit
		stdValue = 0x1D;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;

	case tmAnalog_TV_MN_C2:
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 5400000;
		// set Std bit
		stdValue = 0x0C;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;

	case tmAnalog_TV_B_C2:
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 6000000;
		// set Std bit
		stdValue = 0x0D;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;

	case tmAnalog_TV_GH_C2:
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 7100000;
		// set Std bit
		stdValue = 0x0E;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;

	case tmAnalog_TV_I_C2:			
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 7250000;
		// set Std bit
		stdValue = 0x0E;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;

	case tmAnalog_TV_DK_C2:
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 6900000;
		// set Std bit
		stdValue = 0x0E;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;

	case tmAnalog_TV_L_C2:			
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 6900000;
		// set Std bit
		stdValue = 0x0E;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;

	case tmAnalog_TV_LL_C2:
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 1250000;
		// set Std bit
		stdValue = 0x0E;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;

	case tmAnalog_FM_Radio_C2:
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 1250000;
		// set Std bit
		stdValue = 0x18;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x01;
		break;

	case tmDigital_CAL_C2:
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 1250000;
		// set Std bit
		stdValue = 0x18;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x01;
		break;

	case tmDigital_TV_QAM_6MHz_C2:
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 4000000;
		// set Std bit
		stdValue = 0x1D;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;

	case tmDigital_TV_QAM_8MHz_C2:
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 5000000;
		// set Std bit
		stdValue = 0x1F;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;

	case tmDigital_TV_ISDBT_6MHz_C2:
		// set IF frequency 
		if (!customIF)
			pObj->Config.uIF = 4063000;
		// set Std bit
		stdValue = 0x1D;
		pObj->I2CMap.uBx05.bF.Std = (!customLPFc) ? stdValue : (pObj->I2CMap.uBx05.bF.Std & 0xE3) | (stdValue & 0x1C);
		// set FM_RFn bit
		pObj->I2CMap.uBx06.bF.FM_RFn = 0x00;
		break;
	}

	// set CAL_Mode to normal mode
	pObj->I2CMap.uBx06.bF.CAL_Mode = 0x00;

	// set IF_Level & IF_notch & RFAGC_Top & IFAGC_Top
	switch (StandardMode)
	{
	case tmDigital_TV_ATSC_6MHz_C2:
	case tmDigital_TV_DVBT_7MHz_C2:
	case tmDigital_TV_DVBT_8MHz_C2:
	case tmDigital_TV_QAM_6MHz_C2:
	case tmDigital_TV_QAM_8MHz_C2:
	case tmDigital_TV_ISDBT_6MHz_C2:
		// set IF_Level
		pObj->I2CMap.uBx06.bF.IF_Level = 0x01;
		// set IF_notch
		pObj->I2CMap.uBx0C.bF.IF_notch = 0x01;
		// set RFAGC_Top & IFAGC_Top
		pObj->I2CMap.uBx25.EXTENDED_BYTE_22 = 0x37;
		break;

	case tmAnalog_TV_MN_C2:
	case tmAnalog_TV_B_C2:
	case tmAnalog_TV_GH_C2:
	case tmAnalog_TV_I_C2:
	case tmAnalog_TV_DK_C2:
	case tmAnalog_TV_L_C2:					
	case tmAnalog_TV_LL_C2:
	case tmAnalog_FM_Radio_C2:
	case tmDigital_CAL_C2:
		// set IF_Level
		pObj->I2CMap.uBx06.bF.IF_Level = 0x00;
		// set IF_notch
		pObj->I2CMap.uBx0C.bF.IF_notch = 0x00;
		// set RFAGC_Top & IFAGC_Top
		pObj->I2CMap.uBx25.EXTENDED_BYTE_22 = 0x2C;
		break;

	default:
		// standard mode not supported
		return TM_ERR_NOT_SUPPORTED_C2;
	}

	// store standard mode 
	pObj->StandardMode = StandardMode;

	return TM_OK;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271GetStandardMode_C2:
//
// DESCRIPTION: Get the standard mode of this device.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_OK
//
// NOTES:
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271GetStandardMode_C2
(
 tmUnitSelect_t					TunerUnit,		//  I: Tuner unit number
 tmTDA18271StandardMode_t_C2		*pStandardMode	//  O: Standard mode of this device
 )
{
	ptmTDA18271Object_t_C2		pObj = Null;
	tmErrorCode_t			ret  = TM_OK;

	//------------------------------
	// test input parameters
	//------------------------------
	// test the instance number
	if (TunerUnit > TDA18271_MAX_UNITS_C2)
		return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2;

	// pObj initialization
	ret = getInstance_C2(TunerUnit, &pObj);
	if (ret != TM_OK)
		return ret;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	// get standard mode
	return TDA18271GetStandardMode_C2(pObj, pStandardMode);
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271GetStandardMode_C2:
//
// DESCRIPTION: Get the standard mode of this device.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_OK
//
// NOTES:
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
TDA18271GetStandardMode_C2
(
 ptmTDA18271Object_t_C2			pObj,			// I: tuner Object
 tmTDA18271StandardMode_t_C2	*pStandardMode	//  O: Standard mode of this device
 )
{
	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_BAD_PARAMETER_C2;

	//----------------------
	// get the value
	//----------------------
	*pStandardMode = pObj->StandardMode;

	return TM_OK;
}

//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271Write_C2:
//
// DESCRIPTION: Write in the Tuner.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TMBSL_ERR_IIC_ERR
//              TM_OK
//
// NOTES:      uIndex: IN parameter containing the HW Sub Address as specified in 
//			   the datasheet (i.e. looks like 0xX0)      
//-----------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271Write_C2
(
 tmUnitSelect_t      TunerUnit,      //  I: Tuner unit number
 UInt32              uIndex,         //  I: Start index to write
 UInt32              uNbBytes,       //  I: Number of bytes to write
 UInt32*             puBytes         //  I: Pointer on an array of bytes
 )
{

	UInt32	uCounter;
	UInt8*	pI2CMap;

	ptmTDA18271Object_t_C2		pObj = Null;
	tmErrorCode_t			ret  = TM_OK;

	//------------------------------
	// test input parameters
	//------------------------------
	// test the instance number
	if (TunerUnit > TDA18271_MAX_UNITS_C2)
		return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2;

	// pObj initialization
	ret = getInstance_C2(TunerUnit, &pObj);
	if (ret != TM_OK)
		return ret;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	// test the parameters. uIndex is: 0x0X
	if ((uIndex + uNbBytes) > TDA18271_NB_BYTES_C2)
		return TMBSL_ERR_TUNER_BAD_PARAMETER_C2;

	// pI2CMap initialization
	pI2CMap = &(pObj->I2CMap.uBx00.ID_BYTE) + uIndex;

	//--------------
	// set the value
	//--------------	
	// save the values written in the Tuner
	for (uCounter = 0; uCounter < uNbBytes; uCounter++)
	{
		*pI2CMap = (UInt8)(puBytes[uCounter]);
		pI2CMap ++;
	}

	// write in the Tuner
	if (TDA18271Write_C2(pObj,(UInt8)(uIndex),(UInt8)(uNbBytes)) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	return TM_OK;
}

//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271WriteBit_C2:
//
// DESCRIPTION: Write in the Tuner.
//
// RETURN:      TM_ERR_NOT_SUPPORTED
//
// NOTES:
//-----------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271WriteBit_C2
(
 tmUnitSelect_t      TunerUnit,      //  I: Tuner unit number
 UInt32              uIndex,         //  I: Start index to write
 UInt32              uBitMask,       //  I: bit mask
 UInt32              uBitValue       //  I: bit value
 )
{
	return TM_ERR_NOT_SUPPORTED_C2;
}

//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271Read_C2:
//
// DESCRIPTION: Read in the Tuner.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TMBSL_ERR_TUNER_BAD_PARAMETER
//              TMBSL_ERR_IIC_ERR
//              TM_OK
//
// NOTES:       
//-----------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271Read_C2
(
 tmUnitSelect_t      TunerUnit,      //  I: Tuner unit number
 UInt32              uIndex,         //  I: Start index to read
 UInt32              uNbBytes,       //  I: Number of bytes to read
 UInt32*             puBytes         //  I: Pointer on an array of bytes
 )
{
	UInt32	uCounter;
	UInt8*	pI2CMap;

	ptmTDA18271Object_t_C2		pObj = Null;
	tmErrorCode_t			ret  = TM_OK;

	//----------------------
	// test input parameters
	//----------------------
	// test the instance number
	if (TunerUnit > TDA18271_MAX_UNITS_C2)
		return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2;

	// pObj initialization
	ret = getInstance_C2(TunerUnit, &pObj);
	if (ret != TM_OK)
		return ret;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	// test the parameters
	if (uNbBytes > TDA18271_NB_BYTES_C2)
		return TMBSL_ERR_TUNER_BAD_PARAMETER_C2;

	// test uIndex
	if (uIndex == -1)
		uIndex = 0;

	// pI2CMap initialization
	pI2CMap = &(pObj->I2CMap.uBx00.ID_BYTE) + uIndex;

	//--------------
	// get the value
	//--------------
	// read from the Tuner
	if (TDA18271Read_C2(pObj,(UInt8)(uIndex),(UInt8)(uNbBytes)) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// copy readen values to puBytes
	for (uCounter = 0; uCounter < uNbBytes; uCounter++)
	{
		*puBytes = (UInt32)(*pI2CMap);
		pI2CMap ++;
		puBytes ++;
	}
	return TM_OK;
}

//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271SetConfig_C2:
//
// DESCRIPTION: Set the Config of the TDA18271_C2
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_ERR_NOT_SUPPORTED
//              TMBSL_ERR_TUNER_BAD_PARAMETER
//              TM_OK
//
// NOTES:
//-----------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271SetConfig_C2
(
 tmUnitSelect_t     TunerUnit,  //  I: TunerUnit number
 UInt32             uItemId,    //  I: Identifier of the item to modify
 UInt32             uValue      //  I: Value to set for the Config item
 )
{
	ptmTDA18271Object_t_C2		pObj = Null;
	UInt8*					pI2CMap;
	UInt32*					pDataMap;
	tmErrorCode_t			ret  = TM_OK;

	//----------------------
	// test input parameters
	//----------------------
	// test the instance number
	if (TunerUnit > TDA18271_MAX_UNITS_C2)
		return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2;

	// pObj initialization
	ret = getInstance_C2(TunerUnit, &pObj);
	if (ret != TM_OK)
		return ret;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	//--------------
	// set the value
	//--------------
	switch((tmTDA18271cfgIndex_t_C2)uItemId)
	{
	case BOARD_C2:
		switch (uValue & 0xffff0000)
		{
		case OM5776_BOARD_DEF:
		case OM5780_BOARD_DEF:
		case OM5782_BOARD_DEF:
		case OM5764_BOARD_DEF:
			/*pObj->Config.uXTOUT = 1;
			pObj->I2CMap.XTout_ON = 1;*/
			break;				
		case OM5770C2_BOARD_DEF & 0xffff0000:
		case OM5775_BOARD_DEF:
		case OM5777_BOARD_DEF:
		case CUSTOM_BOARD_DEF:
			// do nothing more than setting the default values
			break;                
		default:
			// board not supported
			return TM_ERR_NOT_SUPPORTED_C2;
		}
		// store board
		gTDA18271Instance_C2[TunerUnit].Config.uBoard = uValue;
		break;

	case FEINIT_C2:
		if(TDA18271Init_C2(TunerUnit) == TMBSL_ERR_IIC_ERR_C2)
			return TMBSL_ERR_IIC_ERR_C2;
		break;

	case RF_C2:
		// set RF_C2 frequency 
		pObj->Config.uRF = uValue;	
		break;

	case IF_C2:
		// set IF_C2 frequency 
		pObj->Config.uIF = uValue;	
		break;

	case PLMODE_C2:
		// set uPLMODE_C2
		pObj->Config.uPLMODE = uValue;
		// write byte EASY_PROG_BYTE_1
		if (TDA18271Write_C2(pObj,0x03,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;
		break;

	case PLRUN_C2:
		// switch AGC2_C2 power detector on
		pObj->I2CMap.uBx1B.bF.PD_AGC2_Det = 0x00;
		// write byte EXTENDED_BYTE_12
		if (TDA18271Write_C2(pObj,0x1B,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;

		// switch power level indicator on
		pObj->Config.uPLMODE = 0x00;
		// write byte EASY_PROG_BYTE_1
		if (TDA18271Write_C2(pObj,0x03,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;

		// wait 20 ms for charge pump source
		if (TDA18271Wait_C2(pObj,20) == False)
			return TM_FALSE;

		// read bytes 0x00 to 0x0F
		if (TDA18271Read_C2 (pObj, 0x00, 16) != True)
			return TMBSL_ERR_IIC_ERR_C2;

		// switch power level indicator off
		pObj->Config.uPLMODE = 0x01;
		// write byte EASY_PROG_BYTE_1
		if (TDA18271Write_C2(pObj,0x03,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;

		// switch AGC2 power detector off
		pObj->I2CMap.uBx1B.bF.PD_AGC2_Det = 0x01;
		// write byte EXTENDED_BYTE_12
		if (TDA18271Write_C2(pObj,0x1B,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;

		break;

	case POWERSTATE_C2:
		// set POWERSTATE
		TDA18271SetPowerState_C2 (pObj, (tmTDA18271PowerState_t_C2)uValue);
		// set CAL_Mode to normal mode
		pObj->I2CMap.uBx06.bF.CAL_Mode = 0x00;
		// write byte EASY_PROG_BYTE_3
		if (TDA18271Write_C2(pObj,0x05,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;
		break;

	case STANDARDMODE_C2:
		// set STANDARDMODE_C2
		TDA18271SetStandardMode_C2 (pObj, (tmTDA18271StandardMode_t_C2)uValue);
		// set CAL_Mode to normal mode
		pObj->I2CMap.uBx06.bF.CAL_Mode = 0x00;
		// write bytes EASY_PROG_BYTE_3 & EASY_PROG_BYTE_4
		if (TDA18271Write_C2(pObj,0x05,2) != True)
			return TMBSL_ERR_IIC_ERR_C2;
		// write MAIN_POST_DIV_BYTE
		if (TDA18271Write_C2(pObj,0x0C,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;
		// write byte EXTENDED_BYTE_22
		if (TDA18271Write_C2(pObj,0x25,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;
		break;

	case LPFC_C2:
		// set LP_Fc_C2
		pObj->I2CMap.uBx05.bF.Std = (pObj->I2CMap.uBx05.bF.Std & 0xFC) | ((UInt8)uValue & 0x03);
		// write byte EASY_PROG_BYTE_3
		if (TDA18271Write_C2(pObj,0x05,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;
		break;

	case XTOUT_C2:
		// set XTout_ON_C2
		pObj->I2CMap.uBx06.bF.XTout_ON = (UInt8)(uValue) >> 1;
		// set Xtout_400mV
		pObj->I2CMap.uBx06.bF.Xtout_400mV = (UInt8)(uValue) & 0x01;
		// write byte EASY_PROG_BYTE_4
		if (TDA18271Write_C2(pObj,0x06,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;
		break;

	case IFLEVEL_C2:
		// set IF_Level_C2
		pObj->I2CMap.uBx06.bF.IF_Level = (UInt8)uValue; 
		// write byte EASY_PROG_BYTE_4
		if (TDA18271Write_C2(pObj,0x06,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;
		break;

	case EXTENDEDREG_C2:
		// set Extended_Reg_C2
		pObj->I2CMap.uBx07.bF.Extended_Reg = (UInt8)uValue;
		// write byte EASY_PROG_BYTE_5
		if (TDA18271Write_C2(pObj,0x07,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;
		break;

	case MAPNAME_C2:
		// set map name 
		pObj->Config.uMAPNAME = uValue;
		break;

	case MAPCOLUMN_C2:	
		// set map x 
		pObj->Config.uMAPCOLUMN = uValue;
		break;

	case MAPROW_C2:	
		// set map y 
		pObj->Config.uMAPROW = uValue;
		break;

	case MAPVALUE_C2:
		// set pointer on wanted cell
		switch (pObj->Config.uMAPNAME)
		{
		case tmTDA18271_IR_MEAS_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_IR_MEAS_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_IR_MEAS_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.IR_MEAS_Map[pObj->Config.uMAPROW].uRF_Max);
			break;	

		case tmTDA18271_IR_CAL_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_IR_CAL_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_IR_CAL_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.IR_CAL_Map[pObj->Config.uMAPROW].uRF);
			break;

		case tmTDA18271_BP_FILTER_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_BP_FILTER_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_BP_FILTER_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.BP_FILTER_Map[pObj->Config.uMAPROW].uRF_Max);
			break;

		case tmTDA18271_RF_BAND_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_BAND_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_RF_BAND_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.RF_BAND_Map[pObj->Config.uMAPROW].uRF_Max);
			break;	

		case tmTDA18271_GAIN_TAPER_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_GAIN_TAPER_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_GAIN_TAPER_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.GAIN_TAPER_Map[pObj->Config.uMAPROW].uRF_Max);
			break;

		case tmTDA18271_RF_CAL_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_CAL_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_RF_CAL_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.RF_CAL_Map[pObj->Config.uMAPROW].uRF_Max);
			break;

		case tmTDA18271_RF_CAL_DC_OVER_DT_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_CAL_DC_OVER_DT_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_RF_CAL_DC_OVER_DT_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.RF_CAL_DC_OVER_DT_Map[pObj->Config.uMAPROW].uRF_Max);
			break;

		case tmTDA18271_RF_CAL_KMCO_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_CAL_KMCO_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_RF_CAL_KMCO_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.RF_CAL_KMCO_Map[pObj->Config.uMAPROW].uRF_Max);
			break;

		case tmTDA18271_RF_CAL_CID_TARGET_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_CAL_CID_TARGET_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_RF_CAL_CID_TARGET_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.RF_CAL_CID_TARGET_Map[pObj->Config.uMAPROW].uRF_Max);
			break;

		case tmTDA18271_THERMOMETER_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_THERMOMETER_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_THERMOMETER_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.THERMOMETER_Map[pObj->Config.uMAPROW].uTM_D);
			break;

		case tmTDA18271_CAL_PLL_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_CAL_PLL_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_CAL_PLL_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.CAL_PLL_Map[pObj->Config.uMAPROW].uLO_Max);
			break;

		case tmTDA18271_MAIN_PLL_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_MAIN_PLL_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_MAIN_PLL_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.MAIN_PLL_Map[pObj->Config.uMAPROW].uLO_Max);
			break;

		case tmTDA18271_I2C_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > 0) || (pObj->Config.uMAPROW > TDA18271_NB_BYTES_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pI2CMap initialization
			pI2CMap = &(pObj->I2CMap.uBx00.ID_BYTE) + pObj->Config.uMAPROW;
			break;
		}

		// set cell value
		if  (pObj->Config.uMAPNAME == tmTDA18271_I2C_Map_C2)
			*(pI2CMap + (UInt8)pObj->Config.uMAPCOLUMN) = (UInt8)uValue;
		else
			*(pDataMap + pObj->Config.uMAPCOLUMN) = uValue;
		break;

	case PROTOCOLSTEP_C2:
		// set channel configuration protocol steps to execute
		pObj->Config.uPROTOCOLSTEP = uValue; 
		break;

	case READINIT_C2:
		// read bytes 0x00 to 0x26
		if (TDA18271Read_C2 (pObj,0x00,39) != True)
			return TMBSL_ERR_IIC_ERR_C2;

		if (uValue == 1)
		{
			// initialize device
			if(TDA18271Init_C2(TunerUnit) == TMBSL_ERR_IIC_ERR_C2)
				return TMBSL_ERR_IIC_ERR_C2;
		}
		break;
	}
	return TM_OK;
}


//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271GetConfig_C2:
//
// DESCRIPTION: Get the Config of the TDA18271_C2
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_OK
//
// NOTES:       
//-----------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271GetConfig_C2
(
 tmUnitSelect_t     TunerUnit,  //  I: Tuner unit number
 UInt32             uItemId,    //  I: Identifier of the item to get value
 UInt32*            puValue     //  I: Address of the variable to output the Config item value
 )
{
	UInt32 uCounter = 0;

	ptmTDA18271Object_t_C2		pObj = Null;
	UInt8*					pI2CMap;
	UInt32*					pDataMap;
	UInt32					uByte=0; 
	tmErrorCode_t			ret  = TM_OK;
	//------------------------------
	// test input parameters
	//------------------------------
	// pObj initialization
	ret = getInstance_C2(TunerUnit, &pObj);
	if (ret != TM_OK)
		return ret;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	//--------------
	// get the value
	//--------------
	switch((tmTDA18271cfgIndex_t_C2)uItemId)
	{
	case BOARD_C2:
		// get board
		*puValue = pObj->Config.uBoard;
		break;

	case RF_C2:
		// get RF_C2 frequency
		*puValue = pObj->Config.uRF;
		break;

	case IF_C2:
		// get IF frequency
		*puValue = pObj->Config.uIF;
		break;

	case STATUSBYTE_C2:
		// read bytes 0x00 to 0x26
		if (TDA18271Read_C2 (pObj,0x00,39) != True)
			return TMBSL_ERR_IIC_ERR_C2;
		break;

	case GETNBOFUNIT_C2:
		*puValue = TDA18271_MAX_UNITS_C2;
		break;

	case ID_C2:
		// get ID_C2 value
		*puValue = pObj->I2CMap.uBx00.bF.ID;
		break;

	case POR_C2:
		// get POR_C2 value
		*puValue = pObj->I2CMap.uBx01.bF.POR;
		break;

	case MAINLOCK_C2:
		// get MAINLOCK value
		*puValue = TunerUnit == 0 ? pObj->I2CMap.uBx01.bF.MAIN_Lock : pObj->I2CMap.uBx16.bF.CAL_Lock;
		break;

	case TMVALUE_C2:
		// read byte THERMO_BYTE
		if (TDA18271ThermometerRead_C2(pObj, puValue) != TM_OK || pObj->I2CMap.uBx05.bF.SM == 1)
			return TMBSL_ERR_IIC_ERR_C2;
		break;

	case PLMODE_C2:
		// get PLMODE value
		*puValue = pObj->Config.uPLMODE;
		break;

	case PLAGC1_C2:
		// get PLAGC1 value
		*puValue = 3 * (2 + ((pObj->I2CMap.uBx02.bF.Power_Level_7_to_0 & 0x7F) >> 5));
		break;

	case PLAGC2_C2:
		// get PLAGC2 value
		*puValue = 3 * (2 + (3 - (pObj->I2CMap.uBx03.bF.Power_Level_8 << 1 | pObj->I2CMap.uBx02.bF.Power_Level_7_to_0 >> 7)));
		break;

	case PLRFAGC_C2:
		// get PLRFAGC value (PLRFAGC = PLRFAGC - 11)
		if (((pObj->I2CMap.uBx25.EXTENDED_BYTE_22 & 0x7F) >> 4) < 5)
			*puValue = 11 + (92 + 2 * ((pObj->I2CMap.uBx25.EXTENDED_BYTE_22 & 0x7F) >> 4)) - (103 - (pObj->I2CMap.uBx02.bF.Power_Level_7_to_0 & 0x1F));
		else
			*puValue = 11 + 102 - (103 - (pObj->I2CMap.uBx02.bF.Power_Level_7_to_0 & 0x1F));
		// limit PLRFAGC value
		if (*puValue > 33)
			*puValue = 33;
		else if (*puValue < 1)
			*puValue = 1;
		break;

	case RFCALOK_C2:
		// get RFCALOK value
		*puValue = pObj->I2CMap.uBx03.bF.RF_CAL_OK;
		break;

	case RFCAL_TCOMP_C2:
		// get RFCAL_TCOMP value
		*puValue = pObj->Config.uRFCAL_TCOMP;
		break;

	case IRCALOK_C2:
		// get IRCALOK value
		*puValue = pObj->I2CMap.uBx03.bF.IR_CAL_OK;
		break;

	case BPFILTER_C2:
		// get BPFILTER value
		*puValue = pObj->I2CMap.uBx03.bF.BP_Filter;
		break;

	case RFBAND_C2:
		// get RFBAND_C2 value
		*puValue = pObj->I2CMap.uBx04.bF.RF_Band;
		break;

	case GAINTAPER_C2:
		// get GAINTAPER_C2 value
		*puValue = pObj->I2CMap.uBx04.bF.Gain_Taper;
		break;

	case POWERSTATE_C2:
		// get POWERSTATE_C2
		TDA18271GetPowerState_C2(pObj,(ptmTDA18271PowerState_t_C2)puValue);
		break;

	case LPFC_C2:
		// get LPFC_C2 value
		*puValue = pObj->I2CMap.uBx05.bF.Std & 0x03;
		break;

	case FMRFN_C2:
		// get FMRFN_C2 value
		*puValue = pObj->I2CMap.uBx06.bF.FM_RFn;
		break;

	case STANDARDMODE_C2:
		// get STANDARDMODE_C2
		TDA18271GetStandardMode_C2(pObj, (ptmTDA18271StandardMode_t_C2)puValue);
		break;

	case XTOUT_C2:
		// get XTout_ON & Xtout_400mV value
		*puValue = (UInt32)(pObj->I2CMap.uBx06.bF.XTout_ON << 1 | pObj->I2CMap.uBx06.bF.Xtout_400mV);
		break;

	case IFLEVEL_C2:
		// get IFLEVEL_C2 value
		*puValue = pObj->I2CMap.uBx06.bF.IF_Level;
		break;

	case EXTENDEDREG_C2:
		// get EXTENDEDREG_C2 value
		*puValue = pObj->I2CMap.uBx07.bF.Extended_Reg;
		break;

	case CALPOSTDIV_C2:
		// get CALPOSTDIV_C2 value
		*puValue = pObj->I2CMap.uBx08.CAL_POST_DIV_BYTE & 0x7F;
		break;

	case CALDIV_C2:
		// get CALDIV_C2 value
		*puValue = pObj->I2CMap.uBx09.bF.CAL_Div_22_to_16 << 16 | pObj->I2CMap.uBx0A.bF.CAL_Div_15_to_8 << 8 | pObj->I2CMap.uBx0B.bF.CAL_Div_7_to_0;
		break;

	case MAINPOSTDIV_C2:
		// get MAINPOSTDIV_C2 value
		*puValue = pObj->I2CMap.uBx0C.bF.MAIN_Post_Div;
		break;

	case MAINDIV_C2:
		// get MAINDIV_C2 value
		*puValue = pObj->I2CMap.uBx0D.bF.MAIN_Div_22_to_16 << 16 | pObj->I2CMap.uBx0E.bF.MAIN_Div_15_to_8 << 8 | pObj->I2CMap.uBx0F.bF.MAIN_Div_7_to_0;
		break;

	case MAPVALUE_C2:
		// set pointer on wanted cell
		switch (pObj->Config.uMAPNAME)
		{
		case tmTDA18271_IR_MEAS_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_IR_MEAS_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_IR_MEAS_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.IR_MEAS_Map[pObj->Config.uMAPROW].uRF_Max);
			break;	

		case tmTDA18271_IR_CAL_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_IR_CAL_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_IR_CAL_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.IR_CAL_Map[pObj->Config.uMAPROW].uRF);
			break;

		case tmTDA18271_BP_FILTER_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_BP_FILTER_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_BP_FILTER_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.BP_FILTER_Map[pObj->Config.uMAPROW].uRF_Max);
			break;

		case tmTDA18271_RF_BAND_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_BAND_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_RF_BAND_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.RF_BAND_Map[pObj->Config.uMAPROW].uRF_Max);
			break;	

		case tmTDA18271_GAIN_TAPER_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_GAIN_TAPER_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_GAIN_TAPER_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.GAIN_TAPER_Map[pObj->Config.uMAPROW].uRF_Max);
			break;

		case tmTDA18271_RF_CAL_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_CAL_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_RF_CAL_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.RF_CAL_Map[pObj->Config.uMAPROW].uRF_Max);
			break;

		case tmTDA18271_RF_CAL_DC_OVER_DT_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_CAL_DC_OVER_DT_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_RF_CAL_DC_OVER_DT_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.RF_CAL_DC_OVER_DT_Map[pObj->Config.uMAPROW].uRF_Max);
			break;

		case tmTDA18271_RF_CAL_KMCO_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_CAL_KMCO_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_RF_CAL_KMCO_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.RF_CAL_KMCO_Map[pObj->Config.uMAPROW].uRF_Max);
			break;

		case tmTDA18271_RF_CAL_CID_TARGET_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_CAL_CID_TARGET_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_RF_CAL_CID_TARGET_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.RF_CAL_CID_TARGET_Map[pObj->Config.uMAPROW].uRF_Max);
			break;

		case tmTDA18271_THERMOMETER_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_THERMOMETER_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_THERMOMETER_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.THERMOMETER_Map[pObj->Config.uMAPROW].uTM_D);
			break;	

		case tmTDA18271_CAL_PLL_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_CAL_PLL_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_CAL_PLL_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.CAL_PLL_Map[pObj->Config.uMAPROW].uLO_Max);
			break;	

		case tmTDA18271_MAIN_PLL_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > TDA18271_MAIN_PLL_NB_COLUMNS_C2 - 1) || (pObj->Config.uMAPROW > TDA18271_MAIN_PLL_NB_ROWS_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pDataMap initialization
			pDataMap = &(pObj->Config.MAIN_PLL_Map[pObj->Config.uMAPROW].uLO_Max);
			break;

		case tmTDA18271_I2C_Map_C2:
			// test map column & row
			if ((pObj->Config.uMAPCOLUMN > 0) || (pObj->Config.uMAPROW > TDA18271_NB_BYTES_C2 - 1))
				return TM_ERR_NOT_SUPPORTED_C2;
			// pI2CMap initialization
			pI2CMap = &(pObj->I2CMap.uBx00.ID_BYTE) + pObj->Config.uMAPROW;
			break;
		}
		// get cell value
		if  (pObj->Config.uMAPNAME == tmTDA18271_I2C_Map_C2)
			*puValue = *(pI2CMap + pObj->Config.uMAPCOLUMN);
		else
			*puValue = *(pDataMap + pObj->Config.uMAPCOLUMN);
		break;

	case PROTOCOLSTEP_C2:
		// get channel configuration protocol steps
		*puValue = pObj->Config.uPROTOCOLSTEP; 
		break;

		// backdoor functions
	case IDENTITY_C2:
		_SYSTEMFUNC.SY_Read_C2( pObj->uHwAddress, TDA18271_IDENTITY_IND_C2, 1, &uByte); 
		/*if (uByte != 0x82) 
		*puValue = False; 
		else 
		*puValue = True; 
		*/
		switch (pObj->Config.uBoard & 0xffff0000)
		{ 
		case 0x57750000: 
			*puValue = True; 
			break;
		default:
			*puValue = False;
			break;
		}
		break;

	}
	return TM_OK;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271SetRf_C2:
//
// DESCRIPTION: Calculate i2c I2CMap & write in TDA18271_C2
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TMBSL_ERR_TUNER_BAD_PARAMETER
//              TMBSL_ERR_IIC_ERR
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271SetRf_C2
(
 tmUnitSelect_t		TunerUnit,  //  I: Tuner unit number
 UInt32				uRF			//  I: RF frequency in hertz
 )
{	
	ptmTDA18271Object_t_C2		pObj;
	tmErrorCode_t			ret  = TM_OK;

	UInt32	uCounter = 0;
	UInt32	uTMVALUE_CURRENT = 0;
	UInt8	utmpStd = 0;

	UInt8	uCprog_table = 0;
	Int32	uCapprox = 0;
	Int32	uCprog_signed = 0;


	//------------------------------
	// test input parameters
	//------------------------------
	// pObj initialization
	ret = getInstance_C2(TunerUnit, &pObj);
	if (ret != TM_OK)
		return ret;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	// Config.uRF update
	pObj->Config.uRF = uRF;

	//----------------------
	// configuration reset
	//----------------------
	// set power level indicator to off
	pObj->Config.uPLMODE = 1;

	//----------------------
	// normal mode restore
	//----------------------
	// power up in calibration standard
	pObj->I2CMap.uBx05.bF.SM = 0x00;
	pObj->I2CMap.uBx05.bF.SM_LT = 0x00;
	pObj->I2CMap.uBx05.bF.SM_XT = 0x00;
	// write byte EASY_PROG_BYTE_3
	if (TDA18271Write_C2(pObj,0x5,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	//----------------------
	// RF tracking filter correction
	//----------------------
	// sense temperature
	ret = TDA18271ThermometerRead_C2(pObj, &uTMVALUE_CURRENT);
	if (ret != TM_OK)
		return ret;

	//----------------------
	// frequency dependent parameters update
	//----------------------
	// search for uCprog_table corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (uRF > pObj->Config.RF_CAL_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_CAL_NB_ROWS_C2);
	uCprog_table = (UInt8)pObj->Config.RF_CAL_Map[uCounter - 1].uRFC_Cprog;

	// search for sub-band corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (uRF > pObj->Config.RF_BAND_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_BAND_NB_ROWS_C2);

	// calculate Capprox
	if (pObj->Config.RF_BAND_Map[uCounter - 1].uRF1 == 0)
	{
		// Capprox = uCprog_table
		uCapprox = (Int32)uCprog_table;
	}
	else if ((pObj->Config.RF_BAND_Map[uCounter - 1].uRF3 != 0) && (uRF >= pObj->Config.RF_BAND_Map[uCounter - 1].uRF2))
	{
		// Capprox = A2 * (uRF - uRF2) + B2 + uCprog_table
		uCapprox = (Int32)(((pObj->Config.RF_BAND_Map[uCounter - 1].uRF_A2 * ((Int32)(uRF - pObj->Config.RF_BAND_Map[uCounter - 1].uRF2) / 1000000)) / 1000000)
			+ pObj->Config.RF_BAND_Map[uCounter - 1].uRF_B2 + uCprog_table);
	}
	else
	{
		// Capprox = A1 * (uRF - uRF1) + B1 + uCprog_table
		uCapprox = (Int32)(((pObj->Config.RF_BAND_Map[uCounter - 1].uRF_A1 * ((Int32)(uRF - pObj->Config.RF_BAND_Map[uCounter - 1].uRF1) / 1000000)) / 1000000)
			+ pObj->Config.RF_BAND_Map[uCounter - 1].uRF_B1 + uCprog_table);
	}

	// search for udC_Over_dT corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (uRF > pObj->Config.RF_CAL_DC_OVER_DT_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_CAL_DC_OVER_DT_NB_ROWS_C2);

	// calculate CTcomp
	pObj->Config.uRFCAL_TCOMP = (Int32)(pObj->Config.RF_CAL_DC_OVER_DT_Map[uCounter - 1].udC_Over_dT * (uTMVALUE_CURRENT - pObj->Config.uTMVALUE_RFCAL)) / 1000;

	// calculate Cprog
	uCprog_signed = uCapprox + pObj->Config.uRFCAL_TCOMP;
	if (uCprog_signed < 0) uCprog_signed = 0;
	if (uCprog_signed > 255) uCprog_signed = 255;
	pObj->I2CMap.uBx1D.RFC_Cprog = (UInt8)uCprog_signed;

	// write byte RFC_Cprog
	if (TDA18271Write_C2(pObj,0x1D,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	//----------------------
	// standard mode update
	//----------------------
	// update TV broadcast parameters
	ret = TDA18271SetStandardMode_C2(pObj, pObj->StandardMode);
	if (ret != TM_OK)
		return ret;

	// switch RFAGC to high speed mode (store current value)
	utmpStd = pObj->I2CMap.uBx05.bF.Std;
	pObj->I2CMap.uBx05.bF.Std &= 0x1B;

	// write byte EASY_PROG_BYTE_3
	if (TDA18271Write_C2(pObj,0x5,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

#ifdef TMBSL_TDA18271_FREEZE_AGC_C2
	/////////////////////////////////////////////
	//----------------------
	// unfreeze AGC 1&2 detectors for secam L only
	//----------------------    
	switch (StandardMode)
	{	
	case tmAnalog_TV_L:					
	case tmAnalog_TV_LL:
		// switch to digital mode
		pObj->I2CMap.uBx05.bF.Std |= 0x10;

		// start AGC1
		pObj->I2CMap.uBx1B.bF.PD_AGC1_Det = 0x00;
		pObj->I2CMap.uBx21.bF.AGC1_loop_off = 0x00;

		// start AGC2
		pObj->I2CMap.uBx1B.bF.PD_AGC2_Det = 0x00;
		pObj->I2CMap.uBx24.bF.AGC2_loop_off = 0x00;

		// write byte EASY_PROG_BYTE_3
		if (TDA18271Write_C2(pObj,0x05,1) != True)
			return TMBSL_ERR_IIC_ERR;
		break;

	default:
		// start AGC1
		pObj->I2CMap.uBx1B.bF.PD_AGC1_Det = 0x00;
		pObj->I2CMap.uBx21.bF.AGC1_loop_off = 0x00;

		// freeze AGC2 (set AGC2Gain = -6dB)
		pObj->I2CMap.uBx1B.bF.PD_AGC2_Det = 0x01;
		pObj->I2CMap.uBx24.bF.AGC2_loop_off = 0x01;
		pObj->I2CMap.uBx24.bF.AGC2_Gain = 0x03;
		break;
	}

	// write byte EXTENDED_BYTE_12
	if (TDA18271Write_C2(pObj,0x1B,1) != True)
		return TMBSL_ERR_IIC_ERR;

	// write byte EXTENDED_BYTE_18
	if (TDA18271Write_C2(pObj,0x21,1) != True)
		return TMBSL_ERR_IIC_ERR;
#endif // TMBSL_TDA18271_FREEZE_AGC_C2

	// write bytes EXTENDED_BYTE_21 to EXTENDED_BYTE_23
	if (TDA18271Write_C2(pObj,0x24,3) != True)
		return TMBSL_ERR_IIC_ERR_C2;
#ifdef TMBSL_TDA18271_FREEZE_AGC_C2
	switch (StandardMode)
	{	
	case tmAnalog_TV_L:					
	case tmAnalog_TV_LL:
		// wait 1 s for AGC 1&2 startup
		Wait(1000);
		break;
	}
	/////////////////////////////////////////////
#endif // TMBSL_TDA18271_FREEZE_AGC_C2

	//----------------------
	// update frequency dependent parameters
	//----------------------
	// search for IR_Meas corresponding to wanted frequency
	uCounter = 0;
	do uCounter ++;
	while (uRF > pObj->Config.IR_MEAS_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_IR_MEAS_NB_ROWS_C2);
	pObj->I2CMap.uBx07.bF.IR_Meas = (UInt8)pObj->Config.IR_MEAS_Map[uCounter - 1].uIR_Meas;

	// search for BP_Filter corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (uRF > pObj->Config.BP_FILTER_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_BP_FILTER_NB_ROWS_C2);
	pObj->I2CMap.uBx03.bF.BP_Filter = (UInt8)pObj->Config.BP_FILTER_Map[uCounter - 1].uBP_Filter;

	// search for RF_BAND corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (uRF > pObj->Config.RF_BAND_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_BAND_NB_ROWS_C2);
	pObj->I2CMap.uBx04.bF.RF_Band = (UInt8)pObj->Config.RF_BAND_Map[uCounter - 1].uRF_Band;

	// search for Gain_Taper corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (uRF > pObj->Config.GAIN_TAPER_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_GAIN_TAPER_NB_ROWS_C2);
	pObj->I2CMap.uBx04.bF.Gain_Taper = (UInt8)pObj->Config.GAIN_TAPER_Map[uCounter - 1].uGain_Taper;

	//---------------------
	// dual tuner and AGC1 extra configuration management
	//---------------------
	// use MAIN VCO when master, CAL VCO when slave
	pObj->I2CMap.uBx10.bF.CALVCO_forLOn = (TunerUnit == 0) ? 1 : 0;

	// AGC1 & AGC2 management
	pObj->I2CMap.uBx10.bF.AGC1_always_mastern = 0x00;
	pObj->I2CMap.uBx10.bF.AGC1_firstn = 0x00;

	// write byte EXTENDED_BYTE_1
	if (TDA18271Write_C2(pObj,0x10,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	//---------------------
	// tune to wanted channel frequency
	//---------------------
	// use MAIN VCO when master, CAL VCO when slave
	if (TunerUnit == 0) // master
	{
		// calculate MAIN PLL
		if (TDA18271CalcMAINPLL_C2(pObj, uRF + pObj->Config.uIF) == False)
			return TM_FALSE;

		// write bytes 0x01 to 0x0F
		if (TDA18271Write_C2(pObj,0x01,15) != True)
			return TMBSL_ERR_IIC_ERR_C2;    

		// MAIN pll charge pump source
		pObj->I2CMap.uBx13.bF.LO_ForceSrce = 0x01;
		// write byte EXTENDED_BYTE_4
		if (TDA18271Write_C2(pObj,0x13,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;

		// wait 1 ms for charge pump source
		if (TDA18271Wait_C2(pObj,1) == False)
			return TM_FALSE;

		// MAIN pll normal operation
		pObj->I2CMap.uBx13.bF.LO_ForceSrce = 0x00;
		// write byte EXTENDED_BYTE_4
		if (TDA18271Write_C2(pObj,0x13,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;
	}
	else // slave
	{		
		// calculate CAL PLL
		if (TDA18271CalcCALPLL_C2(pObj, uRF + pObj->Config.uIF) == False)
			return TM_FALSE;

		// copy CAL PLL PostDiv to MAIN PLL Post Div
		pObj->I2CMap.uBx0C.bF.MAIN_Post_Div = pObj->I2CMap.uBx08.CAL_POST_DIV_BYTE & 0x77;

		// write bytes 0x01 to 0x0F
		if (TDA18271Write_C2(pObj,0x01,15) != True)
			return TMBSL_ERR_IIC_ERR_C2;    

		// CAL pll charge pump source
		pObj->I2CMap.uBx16.bF.CAL_ForceSrce = 0x01;
		// write byte EXTENDED_BYTE_7
		if (TDA18271Write_C2(pObj,0x16,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;

		// wait 1 ms for charge pump source
		if (TDA18271Wait_C2(pObj,1) == False)
			return TM_FALSE;

		// CAL pll normal operation
		pObj->I2CMap.uBx16.bF.CAL_ForceSrce = 0x00;
		// write byte EXTENDED_BYTE_7
		if (TDA18271Write_C2(pObj,0x16,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;
	}

	// wait 20 ms for pll locking
	if (TDA18271Wait_C2(pObj,20) == False)
		return TM_FALSE;

	// switch RFAGC to normal mode (restore previous value)
	pObj->I2CMap.uBx05.bF.Std = utmpStd;

	// write byte EASY_PROG_BYTE_3
	if (TDA18271Write_C2(pObj,0x5,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;
#ifdef TMBSL_TDA18271_FREEZE_AGC_C2
	/////////////////////////////////////////////
	//----------------------
	// freeze AGC 1&2 detectors for secam L only
	//----------------------    
	switch (StandardMode)
	{	
	case tmAnalog_TV_L:					
	case tmAnalog_TV_LL:
		// switch back to analog mode
		pObj->I2CMap.uBx05.bF.Std &= 0xEF;

		// freeze AGC1
		pObj->I2CMap.uBx1B.bF.PD_AGC1_Det = 0x01;
		pObj->I2CMap.uBx21.bF.AGC1_loop_off = 0x01;

		// freeze AGC2
		pObj->I2CMap.uBx1B.bF.PD_AGC2_Det = 0x01;
		pObj->I2CMap.uBx24.bF.AGC2_loop_off = 0x01;
		break;

		// write byte EASY_PROG_BYTE_3
		if (TDA18271Write_C2(pObj,0x05,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// write byte EXTENDED_BYTE_12
		if (TDA18271Write_C2(pObj,0x1B,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// write byte EXTENDED_BYTE_18
		if (TDA18271Write_C2(pObj,0x21,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// write bytes EXTENDED_BYTE_21
		if (TDA18271Write_C2(pObj,0x24,1) != True)
			return TMBSL_ERR_IIC_ERR;
		break;
	}
	/////////////////////////////////////////////
#endif // TMBSL_TDA18271_FREEZE_AGC_C2

	// read bytes 0x00 to 0x26
	if (TDA18271Read_C2 (pObj,0x00,39) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	return TM_OK;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271GetRf_C2:
//
// DESCRIPTION: Get the frequency programmed in the tuner
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_OK
//
// NOTES:       The value returned is the one stored in the Object
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271GetRf_C2
(
 tmUnitSelect_t		TunerUnit,		//  I: Tuner unit number
 UInt32*				pRF				//  O: RF frequency in hertz
 )
{
	ptmTDA18271Object_t_C2		pObj = Null;
	tmErrorCode_t			ret  = TM_OK;

	//------------------------------
	// test input parameters
	//------------------------------
	// pObj initialization
	ret = getInstance_C2(TunerUnit, &pObj);
	if (ret != TM_OK)
		return ret;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	//----------------------
	// get the value
	//----------------------
	// the read function can't be used
	*pRF = pObj->Config.uRF;

	return TM_OK;
}

//-----------------------------------------------------------------------------
// Internal functions:
//-----------------------------------------------------------------------------
//
#ifndef NXPFE
//-----------------------------------------------------------------------------
// FUNCTION:    allocInstance:
//
// DESCRIPTION: allocate new instance
//
// RETURN:      
//
// NOTES:       
//-----------------------------------------------------------------------------
//
tmErrorCode_t
allocInstance_C2 (
						   UInt32					DeviceUnit,	// I: Device unit number
						   pptmTDA18271Object_t_C2	ppDrvObject	// I: Device Object
						   )
{ 
	//----------------------
	// test input parameters
	//----------------------
	// test the max number
	if (DeviceUnit > TDA18271_MAX_UNITS_C2)
		return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2;

	// return value
	return getInstance_C2(DeviceUnit, ppDrvObject);
}

//-----------------------------------------------------------------------------
// FUNCTION:    deAllocInstance:
//
// DESCRIPTION: deallocate instance
//
// RETURN:      always TM_OK
//
// NOTES:       
//-----------------------------------------------------------------------------
//
tmErrorCode_t
deAllocInstance_C2 (
							 UInt32					DeviceUnit	// I: Device unit number
							 )
{ 	
	//----------------------
	// test input parameters
	//----------------------
	// test the max number
	if (DeviceUnit > TDA18271_MAX_UNITS_C2)
		return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2;

	// return value
	return TM_OK;
}

//-----------------------------------------------------------------------------
// FUNCTION:    getInstance:
//
// DESCRIPTION: get the instance
//
// RETURN:      always True
//
// NOTES:       
//-----------------------------------------------------------------------------
//
tmErrorCode_t
getInstance_C2 (
						 tmUnitSelect_t			DeviceUnit,	// I: Device unit number
						 pptmTDA18271Object_t_C2		ppDrvObject	// I: Device Object
						 )
{ 	
	//----------------------
	// test input parameters
	//----------------------
	// test the max number
	if (DeviceUnit > TDA18271_MAX_UNITS_C2)
		return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2;

	// get instance
	*ppDrvObject = &gTDA18271Instance_C2[DeviceUnit];

	// return value
	return TM_OK;
}
#endif // NXPFE

//-----------------------------------------------------------------------------
// FUNCTION:    TDA18271Init_C2:
//
// DESCRIPTION: initialization of the Tuner
//
// RETURN:      always True
//
// NOTES:       
//-----------------------------------------------------------------------------
//
tmErrorCode_t
TDA18271Init_C2 (
						  tmUnitSelect_t			TunerUnit	// I: Tuner Object
						  )
{ 	
	ptmTDA18271Object_t_C2		pObj = Null;
	tmErrorCode_t			ret  = TM_OK;

	//------------------------------
	// test input parameters
	//------------------------------
	// pObj initialization
	ret = getInstance_C2(TunerUnit, &pObj);
	if (ret != TM_OK)
		return ret;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	//----------------------
	// configuration reset
	//----------------------
	// set power level indicator to off
	pObj->Config.uPLMODE = 1;

	//----------------------
	// I2C map initialization
	//----------------------
	// set & write all bytes
	pObj->I2CMap.uBx01.THERMO_BYTE = 0x08;
	pObj->I2CMap.uBx02.POWER_LEVEL_BYTE = 0x80;
	pObj->I2CMap.uBx03.EASY_PROG_BYTE_1 = 0xC6;
	pObj->I2CMap.uBx04.EASY_PROG_BYTE_2 = 0xDF;
	pObj->I2CMap.uBx05.EASY_PROG_BYTE_3 = 0x16;
	pObj->I2CMap.uBx06.EASY_PROG_BYTE_4 = 0x60;
	pObj->I2CMap.uBx07.EASY_PROG_BYTE_5 = 0x80;
	pObj->I2CMap.uBx08.CAL_POST_DIV_BYTE = 0x80;
	pObj->I2CMap.uBx09.CAL_DIV_BYTE_1 = 0x00;
	pObj->I2CMap.uBx0A.CAL_DIV_BYTE_2 = 0x00;
	pObj->I2CMap.uBx0B.CAL_DIV_BYTE_3 = 0x00;
	pObj->I2CMap.uBx0C.MAIN_POST_DIV_BYTE = 0x00;
	pObj->I2CMap.uBx0D.MAIN_DIV_BYTE_1 = 0x00;
	pObj->I2CMap.uBx0E.MAIN_DIV_BYTE_2 = 0x00;
	pObj->I2CMap.uBx0F.MAIN_DIV_BYTE_3 = 0x00;
	pObj->I2CMap.uBx10.EXTENDED_BYTE_1 = 0xFC;
	pObj->I2CMap.uBx11.EXTENDED_BYTE_2 = 0x01;
	pObj->I2CMap.uBx12.EXTENDED_BYTE_3 = 0x84;
	pObj->I2CMap.uBx13.EXTENDED_BYTE_4 = 0x41;
	pObj->I2CMap.uBx14.EXTENDED_BYTE_5 = 0x01;
	pObj->I2CMap.uBx15.EXTENDED_BYTE_6 = 0x84;
	pObj->I2CMap.uBx16.EXTENDED_BYTE_7 = 0x40;
	pObj->I2CMap.uBx17.EXTENDED_BYTE_8 = 0x07;
	pObj->I2CMap.uBx18.EXTENDED_BYTE_9 = 0x00;
	pObj->I2CMap.uBx19.EXTENDED_BYTE_10 = 0x00;
	pObj->I2CMap.uBx1A.EXTENDED_BYTE_11 = 0x96;
	pObj->I2CMap.uBx1B.EXTENDED_BYTE_12 = 0x3F;
	pObj->I2CMap.uBx1C.EXTENDED_BYTE_13 = 0xC1;
	pObj->I2CMap.uBx1D.EXTENDED_BYTE_14 = 0x00;
	pObj->I2CMap.uBx1E.EXTENDED_BYTE_15 = 0x8F;
	pObj->I2CMap.uBx1F.EXTENDED_BYTE_16 = 0x00;
	pObj->I2CMap.uBx20.EXTENDED_BYTE_17 = 0x00;
	pObj->I2CMap.uBx21.EXTENDED_BYTE_18 = 0x8C;
	pObj->I2CMap.uBx22.EXTENDED_BYTE_19 = 0x00;
	pObj->I2CMap.uBx23.EXTENDED_BYTE_20 = 0x20;
	pObj->I2CMap.uBx24.EXTENDED_BYTE_21 = 0xB3;
	pObj->I2CMap.uBx25.EXTENDED_BYTE_22 = 0x48;
	pObj->I2CMap.uBx26.EXTENDED_BYTE_23 = 0xB0;
	if (TDA18271Write_C2(pObj,0x01,38) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	//----------------------
	// AGC1 gain setup
	//----------------------
	// AGC1_Gain_do
	// update & write EXTENDED_BYTE_17
	pObj->I2CMap.uBx20.EXTENDED_BYTE_17 = 0x00;	// set gain_do address
	if (TDA18271Write_C2(pObj,0x20,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;
	pObj->I2CMap.uBx20.EXTENDED_BYTE_17 = 0x03;	// keep gain_do address, set gain_do 
	if (TDA18271Write_C2(pObj,0x20,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// AGC1_Gain_up
	// update & write EXTENDED_BYTE_17
	pObj->I2CMap.uBx20.EXTENDED_BYTE_17 = 0x43;	// set gain_up address, keep gain_do 
	if (TDA18271Write_C2(pObj,0x20,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;
	pObj->I2CMap.uBx20.EXTENDED_BYTE_17 = 0x4C;	// keep gain_up address, set gain_up 
	if (TDA18271Write_C2(pObj,0x20,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	//----------------------
	// image rejection calibration - low band
	//----------------------
	// initialisation
	pObj->I2CMap.uBx05.EASY_PROG_BYTE_3 = 0x1F;
	pObj->I2CMap.uBx06.EASY_PROG_BYTE_4 = 0x66;
	pObj->I2CMap.uBx07.EASY_PROG_BYTE_5 = 0x81;
	pObj->I2CMap.uBx08.CAL_POST_DIV_BYTE = 0xCC;
	pObj->I2CMap.uBx09.CAL_DIV_BYTE_1 = 0x6C;
	pObj->I2CMap.uBx0A.CAL_DIV_BYTE_2 = 0x00;
	pObj->I2CMap.uBx0B.CAL_DIV_BYTE_3 = 0x00;
	pObj->I2CMap.uBx0C.MAIN_POST_DIV_BYTE = 0xC5;
	pObj->I2CMap.uBx0D.MAIN_DIV_BYTE_1 = 0x77;
	pObj->I2CMap.uBx0E.MAIN_DIV_BYTE_2 = 0x08;
	pObj->I2CMap.uBx0F.MAIN_DIV_BYTE_3 = 0x00;
	// write bytes EASY_PROG_BYTE_2 to MAIN_DIV_BYTE_3
	if (TDA18271Write_C2(pObj,0x04,12) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 5 ms for pll locking
	if (TDA18271Wait_C2(pObj,5) == False)
		return TM_FALSE;

	// launch detector
	// write byte EASY_PROG_BYTE_1
	if (TDA18271Write_C2(pObj,0x03,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 5 ms for wanted measurement
	if (TDA18271Wait_C2(pObj,5) == False)
		return TM_FALSE;

	// CAL pll update
	pObj->I2CMap.uBx07.EASY_PROG_BYTE_5 = 0x85;
	pObj->I2CMap.uBx08.CAL_POST_DIV_BYTE = 0xCB; 
	pObj->I2CMap.uBx09.CAL_DIV_BYTE_1 = 0x66;
	pObj->I2CMap.uBx0A.CAL_DIV_BYTE_2 = 0x70;

	// write bytes EASY_PROG_BYTE_3 to CAL_DIV_BYTE_3
	if (TDA18271Write_C2(pObj,0x05,7) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 5 ms for pll locking
	if (TDA18271Wait_C2(pObj,5) == False)
		return TM_FALSE;

	// launch optimisation algorithm
	// write byte EASY_PROG_BYTE_2
	if (TDA18271Write_C2(pObj,0x04,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 30 ms for image optimization completion
	if (TDA18271Wait_C2(pObj,30) == False)
		return TM_FALSE;

	//----------------------
	// image rejection calibration - mid band
	//----------------------
	// initialisation
	pObj->I2CMap.uBx07.EASY_PROG_BYTE_5 = 0x82;
	pObj->I2CMap.uBx08.CAL_POST_DIV_BYTE = 0xA8;
	pObj->I2CMap.uBx0A.CAL_DIV_BYTE_2 = 0x00;
	pObj->I2CMap.uBx0C.MAIN_POST_DIV_BYTE = 0xA1;
	pObj->I2CMap.uBx0D.MAIN_DIV_BYTE_1 = 0x73;
	pObj->I2CMap.uBx0E.MAIN_DIV_BYTE_2 = 0x1A;
	// write bytes EASY_PROG_BYTE_3 to MAIN_DIV_BYTE_3
	if (TDA18271Write_C2(pObj,0x05,11) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 5 ms for pll locking
	if (TDA18271Wait_C2(pObj,5) == False)
		return TM_FALSE;

	// launch detector
	// write byte EASY_PROG_BYTE_1
	if (TDA18271Write_C2(pObj,0x03,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 5 ms for wanted measurement
	if (TDA18271Wait_C2(pObj,5) == False)
		return TM_FALSE;

	// CAL pll update
	pObj->I2CMap.uBx07.EASY_PROG_BYTE_5 = 0x86;
	pObj->I2CMap.uBx08.CAL_POST_DIV_BYTE = 0xA8;
	pObj->I2CMap.uBx09.CAL_DIV_BYTE_1 = 0x66;
	pObj->I2CMap.uBx0A.CAL_DIV_BYTE_2 = 0xA0;

	// write bytes EASY_PROG_BYTE_3 to CAL_DIV_BYTE_3
	if (TDA18271Write_C2(pObj,0x05,7) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 5 ms for pll locking
	if (TDA18271Wait_C2(pObj,5) == False)
		return TM_FALSE;

	// launch optimisation algorithm
	// write byte EASY_PROG_BYTE_2
	if (TDA18271Write_C2(pObj,0x04,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 30 ms for image optimization completion
	if (TDA18271Wait_C2(pObj,30) == False)
		return TM_FALSE;

	//----------------------
	// image rejection calibration - high band
	//----------------------
	// initialisation
	pObj->I2CMap.uBx07.EASY_PROG_BYTE_5 = 0x83;
	pObj->I2CMap.uBx08.CAL_POST_DIV_BYTE = 0x98;
	pObj->I2CMap.uBx09.CAL_DIV_BYTE_1 = 0x65;
	pObj->I2CMap.uBx0A.CAL_DIV_BYTE_2 = 0x00;
	pObj->I2CMap.uBx0C.MAIN_POST_DIV_BYTE = 0x91;
	pObj->I2CMap.uBx0D.MAIN_DIV_BYTE_1 = 0x71;
	pObj->I2CMap.uBx0E.MAIN_DIV_BYTE_2 = 0xCD;		
	// write bytes EASY_PROG_BYTE_3 to CAL_DIV_BYTE_3
	if (TDA18271Write_C2(pObj,0x05,11) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 5 ms for pll locking
	if (TDA18271Wait_C2(pObj,5) == False)
		return TM_FALSE;

	// launch detector
	// write byte EASY_PROG_BYTE_1
	if (TDA18271Write_C2(pObj,0x03,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 5 ms for wanted measurement
	if (TDA18271Wait_C2(pObj,5) == False)
		return TM_FALSE;

	// CAL pll update
	pObj->I2CMap.uBx07.EASY_PROG_BYTE_5 = 0x87;
	pObj->I2CMap.uBx09.CAL_DIV_BYTE_1 = 0x65;
	pObj->I2CMap.uBx0A.CAL_DIV_BYTE_2 = 0x50;

	// write bytes EASY_PROG_BYTE_3 to CAL_DIV_BYTE_3
	if (TDA18271Write_C2(pObj,0x05,7) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 5 ms for pll locking
	if (TDA18271Wait_C2(pObj,5) == False)
		return TM_FALSE;

	// launch optimisation algorithm
	// write byte EASY_PROG_BYTE_2
	if (TDA18271Write_C2(pObj,0x04,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 30 ms for image optimization completion
	if (TDA18271Wait_C2(pObj,30) == False)
		return TM_FALSE;

	//----------------------
	// back to normal mode
	//----------------------
	// update & write byte EASY_PROG_BYTE_4
	pObj->I2CMap.uBx06.EASY_PROG_BYTE_4 = 0x64;
	if (TDA18271Write_C2(pObj,0x06,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// synchronization
	// write byte EASY_PROG_BYTE_1
	if (TDA18271Write_C2(pObj,0x03,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	//----------------------
	// RF tracking filters calibration
	//----------------------
	ret = TDA18271CalcRFFilterCurve_C2(pObj);
	if (ret != TM_OK)
		return ret;

	//----------------------
	// back to POR mode
	//----------------------
	// power up detector 1
	pObj->I2CMap.uBx1B.bF.PD_AGC1_Det = 0x00;
	// write byte EXTENDED_BYTE_12
	if (TDA18271Write_C2(pObj,0x1B,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// turn AGC1 loop on
	pObj->I2CMap.uBx21.bF.AGC1_loop_off = 0x00;
	// set AGC1Gain = 6dB
	pObj->I2CMap.uBx21.bF.AGC1_Gain = 0x00;
	// write byte EXTENDED_BYTE_18
	if (TDA18271Write_C2(pObj,0x21,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// set AGC2Gain = -6dB
	pObj->I2CMap.uBx24.bF.AGC2_Gain = 0x03;

	// swicth to POR mode
	pObj->I2CMap.uBx05.bF.SM = 0x01;
	pObj->I2CMap.uBx05.bF.SM_LT = 0x00;
	pObj->I2CMap.uBx05.bF.SM_XT = 0x00;
	// write byte EASY_PROG_BYTE_3
	if (TDA18271Write_C2(pObj,0x5,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// disable 1.5MHz low pass filter
	pObj->I2CMap.uBx26.bF.ForceLP_Fc2_En = 0x00;
	pObj->I2CMap.uBx26.bF.LP_Fc = 0x00;

	// write bytes EXTENDED_BYTE_21 to EXTENDED_BYTE_23
	if (TDA18271Write_C2(pObj,0x24,3) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	return TM_OK;
}


//-----------------------------------------------------------------------------
// FUNCTION:    TDA18271InitTick_C2
//
// DESCRIPTION: this function will delay for the number of millisecond
//
// RETURN:      nothing
//
// NOTES:       
//-----------------------------------------------------------------------------
//
Bool_ 
TDA18271InitTick_C2(
							 ptmTDA18271Object_t_C2	pObj,		// I: Tuner unit number
							 UInt16					wTime		// I: time to wait for
							 )
{
	UInt32 uCurrentTick;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return False;

	// get current tick
	uCurrentTick = _SYSTEMFUNC.SY_GetTickTime();

	// Calculate end tick
	pObj->uTickEnd = (UInt32)wTime;
	pObj->uTickEnd += _SYSTEMFUNC.SY_GetTickPeriod()/2;
	pObj->uTickEnd /= _SYSTEMFUNC.SY_GetTickPeriod();
	pObj->uTickEnd += uCurrentTick;

	// always add 1 because of rounding issue
	if (wTime)
		pObj->uTickEnd++;

	// test overflow
	if (pObj->uTickEnd < uCurrentTick)
		return False;
	else
		return True;
}

//-----------------------------------------------------------------------------
// FUNCTION:    TDA18271WaitTick_C2
//
// DESCRIPTION: this function will block for the number of millisecond
//
// RETURN:      True if time has elapsed else False
//
// NOTES:       
//-----------------------------------------------------------------------------
//
Bool_ 
TDA18271WaitTick_C2(
							 ptmTDA18271Object_t_C2	pObj		// I: Tuner unit number
							 )
{
	// test the Object
	if (pObj == Null || pObj->init == False)
		return False;

	// test if time has elapsed
	if (_SYSTEMFUNC.SY_GetTickTime() >= pObj->uTickEnd)
		return True;
	else
		return False;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271Write_C2
//
// DESCRIPTION: This function writes I2C data in the Tuner
//
// RETURN:      True or False
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
Bool_ 
TDA18271Write_C2(
						  ptmTDA18271Object_t_C2	pObj,		// I: Tuner unit number
						  UInt8					uSubAddress,// I: sub address
						  UInt8					uNbData		// I: nb of data
						  )
{
	Bool_	I2CCommResult = TM_FALSE;

	UInt8	uCounter;
	UInt8*	pI2CMap;
	UInt32	WriteBuffer[TDA18271_NB_BYTES_C2] = {0};
	UInt32*	pWriteBuffer;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return False;

	// force I2CMap
	pObj->I2CMap.uBx03.bF.Dis_Power_level = (UInt8)pObj->Config.uPLMODE;

	// pI2CMap & pWriteBuffer initialization
	pI2CMap = &(pObj->I2CMap.uBx00.ID_BYTE);
	pWriteBuffer = &(WriteBuffer[0]);

	// copy I2CMap data in WriteBuffer
	for (uCounter = 0; uCounter < TDA18271_NB_BYTES_C2; uCounter++)
	{
		*pWriteBuffer = (UInt32)(*pI2CMap);
		pWriteBuffer ++;
		pI2CMap ++;
	}

	// write data in the Tuner
	I2CCommResult = _SYSTEMFUNC.SY_Write_C2(	pObj->uHwAddress, 
		uSubAddress,
		uNbData,
		&(WriteBuffer[uSubAddress]) );

	// shift I2CLog content
	TDA18271ShiftLog_C2 (pObj,1);

	// copy written data in I2CLog [0]
	for (uCounter = uSubAddress; uCounter < uSubAddress + uNbData; uCounter++)
		pObj->I2CLog [0][uCounter] = WriteBuffer [uCounter];

	// set additional values
	pObj->I2CLog [0][TDA18271_NB_BYTES_C2] = pObj->uHwAddress;
	pObj->I2CLog [0][TDA18271_NB_BYTES_C2 + 1] = I2CCommResult;

	// return value
	return I2CCommResult;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271Read_C2
//
// DESCRIPTION: This function reads I2C data from the Tuner
//
// RETURN:      True or False
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
Bool_ 
TDA18271Read_C2(
						 ptmTDA18271Object_t_C2	pObj,		// I: Tuner unit number
						 UInt8					uSubAddress,// I: sub address
						 UInt8					uNbData		// I: nb of data
						 )
{
	Bool_	I2CCommResult = TM_FALSE;

	UInt8	uCounter;
	UInt8*	pI2CMap;
	UInt32	ReadBuffer[TDA18271_NB_BYTES_C2] = {0};
	UInt32*	pReadBuffer;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return False;

	// pI2CMap & pReadBuffer initialization
	pI2CMap = &(pObj->I2CMap.uBx00.ID_BYTE) + uSubAddress;
	pReadBuffer = &(ReadBuffer[uSubAddress]);

	// read data from the Tuner
	I2CCommResult = _SYSTEMFUNC.SY_Read_C2(	pObj->uHwAddress,
		0,
		uSubAddress + uNbData,
		&(ReadBuffer[0]));

	// copy readen data in I2CMap
	for (uCounter = 0; uCounter < uNbData; uCounter++)
	{
		*pI2CMap = (UInt8)(*pReadBuffer);
		pI2CMap ++;
		pReadBuffer ++;
	}

	// shift I2CLog content
	TDA18271ShiftLog_C2 (pObj,1);

	// copy readen data in I2CLog [0]
	for (uCounter = uSubAddress; uCounter < uSubAddress + uNbData; uCounter++)
		pObj->I2CLog [0][uCounter] = ReadBuffer [uCounter];

	// set additional values
	pObj->I2CLog [0][TDA18271_NB_BYTES_C2] = pObj->uHwAddress + 1;
	pObj->I2CLog [0][TDA18271_NB_BYTES_C2 + 1] = I2CCommResult;

	// return value
	return I2CCommResult;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271Wait_C2
//
// DESCRIPTION: This function waits for requested time
//
// RETURN:      True or False
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
Bool_ 
TDA18271Wait_C2(
						 ptmTDA18271Object_t_C2		pObj,		//  I: Tuner unit number
						 UInt16					wTime		//  I: time to wait for
						 )
{
	// test the Object
	if (pObj == Null || pObj->init == False)
		return False;

	User_delay( pObj->AFAInfo_C2.demodulator, wTime);
	// Return value
	return True;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271ShiftLog_C2
//
// DESCRIPTION: Shift I2CLog content of wanted lines
//
// RETURN:      True
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
Bool_ 
TDA18271ShiftLog_C2(
							 ptmTDA18271Object_t_C2	pObj,	// I: Tuner unit number
							 UInt32					uNbRows	// I: nb of lines
							 )
{
	UInt32	uRow;
	UInt8	uColumn;
	UInt32	uCounter;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return False;

	// Shift I2CLog content of wanted lines
	for (uCounter = 0; uCounter < uNbRows; uCounter++)
	{
		for (uRow = TDA18271_LOG_NB_ROWS_C2 - 1; uRow > 0; uRow--)
		{
			for (uColumn = 0; uColumn < TDA18271_NB_BYTES_C2 + 2; uColumn++)
				pObj->I2CLog [uRow][uColumn] = pObj->I2CLog [uRow - 1][uColumn];
		}

		for (uColumn = 0; uColumn < TDA18271_NB_BYTES_C2 + 2; uColumn++)
			pObj->I2CLog [0][uColumn] = TDA18271_LOG_BLANK_DATA_C2;
	}

	// Return value
	return True;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271CalcMAINPLL_C2:
//
// DESCRIPTION: Calculate the MAIN fractionnal PLL settings
//
// RETURN:      True or False
//
// NOTES:       This function doesn't write in the tuner
//-------------------------------------------------------------------------------------
//
Bool_
TDA18271CalcMAINPLL_C2 (
								 ptmTDA18271Object_t_C2		pObj,		// I: tuner Object
								 UInt32					uLO			// I: local oscillator frequency in hertz
								 )
{	
	UInt8	uCounter = 0;
	UInt32	uDiv;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return False;

	// search for MAIN_Post_Div corresponding to uLO
	do uCounter ++;
	while (uLO > pObj->Config.MAIN_PLL_Map[uCounter - 1].uLO_Max && uCounter < TDA18271_MAIN_PLL_NB_ROWS_C2);
	pObj->I2CMap.uBx0C.bF.MAIN_Post_Div = ((UInt8)pObj->Config.MAIN_PLL_Map[uCounter - 1].uPost_Div) & 0x77;

	// calculate MAIN_Div
	uDiv = (((UInt32)(pObj->Config.MAIN_PLL_Map[uCounter - 1].uDiv) * (uLO / 1000)) << 7) / 125;
	pObj->I2CMap.uBx0D.bF.MAIN_Div_22_to_16 = (UInt8)(uDiv >> 16) & 0x7F;
	pObj->I2CMap.uBx0E.bF.MAIN_Div_15_to_8 = (UInt8)(uDiv >> 8);
	pObj->I2CMap.uBx0F.bF.MAIN_Div_7_to_0 = (UInt8)(uDiv);

	return True;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271CalcCALPLL_C2:
//
// DESCRIPTION: Calculate the CAL fractionnal PLL settings
//
// RETURN:      True or False
//
// NOTES:       This function doesn't write in the tuner
//-------------------------------------------------------------------------------------
//
Bool_
TDA18271CalcCALPLL_C2 (
								ptmTDA18271Object_t_C2		pObj,		// I: tuner Object
								UInt32					uLO			// I: local oscillator frequency in hertz
								)
{	
	UInt8	uCounter = 0;
	UInt32	uDiv;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return False;

	// search for CAL_Post_Div corresponding to uLO
	do uCounter ++;
	while (uLO > pObj->Config.CAL_PLL_Map[uCounter - 1].uLO_Max && uCounter < TDA18271_CAL_PLL_NB_ROWS_C2);
	pObj->I2CMap.uBx08.CAL_POST_DIV_BYTE = (UInt8)pObj->Config.CAL_PLL_Map[uCounter - 1].uPost_Div; 

	// calculate CAL_Div
	uDiv = (((UInt32)(pObj->Config.CAL_PLL_Map[uCounter - 1].uDiv) * (uLO / 1000)) << 7) / 125;
	pObj->I2CMap.uBx09.bF.CAL_Div_22_to_16 = (UInt8)(uDiv >> 16) & 0x7F;
	pObj->I2CMap.uBx0A.bF.CAL_Div_15_to_8 = (UInt8)(uDiv >> 8);
	pObj->I2CMap.uBx0B.bF.CAL_Div_7_to_0 = (UInt8)(uDiv);

	return True;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271CalibrateRF_C2:
//
// DESCRIPTION: RF tracking filter calibration
//
// RETURN:      TMBSL_ERR_IIC_ERR
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
TDA18271CalibrateRF_C2 (
								 ptmTDA18271Object_t_C2	pObj,		// I: tuner Object
								 UInt32					uRF,		// I: RF frequency in hertz
								 UInt8*					puCprog     // I: Address of the variable to output the Cprog value
								 )
{
	UInt32	uCounter = 0;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	//------------------------------
	// initialization
	//------------------------------
	// set CAL_Mode to normal mode
	pObj->I2CMap.uBx06.bF.CAL_Mode = 0x00;
	// write byte EASY_PROG_BYTE_4
	if (TDA18271Write_C2(pObj,0x06,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// set AGC1Gain = 15dB
	pObj->I2CMap.uBx21.bF.AGC1_Gain = 0x03;
	// write byte EXTENDED_BYTE_18
	if (TDA18271Write_C2(pObj,0x21,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// switch off AGC1
	pObj->I2CMap.uBx05.bF.SM_LT = 0x01;

	//------------------------------
	// frequency dependent parameters update
	//------------------------------
	// search for BP_Filter corresponding to uRF
	uCounter=0;
	do uCounter ++;
	while (uRF > pObj->Config.BP_FILTER_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_BP_FILTER_NB_ROWS_C2);
	pObj->I2CMap.uBx03.bF.BP_Filter = (UInt8)pObj->Config.BP_FILTER_Map[uCounter - 1].uBP_Filter;

	// search for Gain_Taper corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (uRF > pObj->Config.GAIN_TAPER_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_GAIN_TAPER_NB_ROWS_C2);
	pObj->I2CMap.uBx04.bF.Gain_Taper = (UInt8)pObj->Config.GAIN_TAPER_Map[uCounter - 1].uGain_Taper;

	// search for RF_BAND corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (uRF > pObj->Config.RF_BAND_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_BAND_NB_ROWS_C2);
	pObj->I2CMap.uBx04.bF.RF_Band = (UInt8)pObj->Config.RF_BAND_Map[uCounter - 1].uRF_Band;

	// search for K,M corresponding to uRF
	uCounter=0;
	do uCounter ++;
	while (uRF > pObj->Config.RF_CAL_KMCO_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_CAL_KMCO_NB_ROWS_C2);		
	pObj->I2CMap.uBx1C.bF.RFC_K = (UInt8)pObj->Config.RF_CAL_KMCO_Map[uCounter - 1].uK;
	pObj->I2CMap.uBx1C.bF.RFC_M = (UInt8)pObj->Config.RF_CAL_KMCO_Map[uCounter - 1].uM;

	// write bytes EASY_PROG_BYTE_1 to EASY_PROG_BYTE_3
	if (TDA18271Write_C2(pObj,0x03,3) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// write byte EXTENDED_BYTE_13
	if (TDA18271Write_C2(pObj,0x1C,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// MAIN pll charge pump source
	pObj->I2CMap.uBx13.bF.LO_ForceSrce = 0x01;
	// write byte EXTENDED_BYTE_4
	if (TDA18271Write_C2(pObj,0x13,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// CAL pll charge pump source
	pObj->I2CMap.uBx16.bF.CAL_ForceSrce = 0x01;
	// write byte EXTENDED_BYTE_7
	if (TDA18271Write_C2(pObj,0x16,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// force DCDC converter to 0V
	pObj->I2CMap.uBx1D.RFC_Cprog = 0x00;
	// write byte EXTENDED_BYTE_14
	if (TDA18271Write_C2(pObj,0x1D,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// disable plls lock
	pObj->I2CMap.uBx23.bF.Force_Lock = 0x00;
	// write byte EXTENDED_BYTE_20
	if (TDA18271Write_C2(pObj,0x23,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// RF tracking filters calibration mode
	pObj->I2CMap.uBx06.bF.CAL_Mode = 0x03;

	// write bytes EASY_PROG_BYTE_4 & EASY_PROG_BYTE_5
	if (TDA18271Write_C2(pObj,0x06,2) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	//------------------------------
	// set internal calibration signals
	//------------------------------
	// calculate CAL PLL
	// CAL LO Frequency = channel center frequency
	if (TDA18271CalcCALPLL_C2(pObj, uRF) == False)
		return TMBSL_ERR_IIC_ERR_C2;

	// calculate MAIN PLL
	// MAIN LO Frequency = channel center frequency + 1MHz
	if (TDA18271CalcMAINPLL_C2(pObj, uRF + RF_CAL_IF_FREQ_C2) == False)
		return TMBSL_ERR_IIC_ERR_C2;

	// write bytes 0x05 to 0x0F
	if (TDA18271Write_C2(pObj,0x05,11) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 5 ms for RF tracking filter calibration initialization
	if (TDA18271Wait_C2(pObj,5) == False)
		return TMBSL_ERR_IIC_ERR_C2;

	//------------------------------
	// internal synchronization
	//------------------------------
	// write byte EASY_PROG_BYTE_2
	if (TDA18271Write_C2(pObj,0x04,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// write byte EASY_PROG_BYTE_1
	if (TDA18271Write_C2(pObj,0x03,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// write byte EASY_PROG_BYTE_2
	if (TDA18271Write_C2(pObj,0x04,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// write byte EASY_PROG_BYTE_1
	if (TDA18271Write_C2(pObj,0x03,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	//------------------------------
	// RF calibration launch
	//------------------------------
	// MAIN pll charge pump source
	pObj->I2CMap.uBx13.bF.LO_ForceSrce = 0x00;
	// write byte EXTENDED_BYTE_4
	if (TDA18271Write_C2(pObj,0x13,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// CAL pll charge pump source
	pObj->I2CMap.uBx16.bF.CAL_ForceSrce = 0x00;
	// write byte EXTENDED_BYTE_7
	if (TDA18271Write_C2(pObj,0x16,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 10 ms for pll locking
	if (TDA18271Wait_C2(pObj,10) == False)
		return TMBSL_ERR_IIC_ERR_C2;

	// launch the RF tracking filters calibartion
	pObj->I2CMap.uBx23.bF.Force_Lock = 0x01;
	// write byte EXTENDED_BYTE_20
	if (TDA18271Write_C2(pObj,0x23,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 60 ms for calibration
	if (TDA18271Wait_C2(pObj,60) == False)
		return TMBSL_ERR_IIC_ERR_C2;

	// normal mode
	pObj->I2CMap.uBx06.bF.CAL_Mode = 0x00;

	// set AGC1Gain = 6dB
	pObj->I2CMap.uBx21.bF.AGC1_Gain = 0x00;
	// write byte EXTENDED_BYTE_18
	if (TDA18271Write_C2(pObj,0x21,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// switch on AGC1
	pObj->I2CMap.uBx05.bF.SM_LT = 0x00;

	// write bytes EASY_PROG_BYTE_3 & EASY_PROG_BYTE_4
	if (TDA18271Write_C2(pObj,0x05,2) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// write byte EASY_PROG_BYTE_1
	if (TDA18271Write_C2(pObj,0x03,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// read bytes 0x00 to 0x26
	if (TDA18271Read_C2 (pObj,0x00,39) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// update puCprog
	*puCprog = pObj->I2CMap.uBx1D.RFC_Cprog;

	// return value
	return TM_OK;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271PowerScanInit_C2:
//
// DESCRIPTION: Initializes power scan
//
// RETURN:      TMBSL_ERR_IIC_ERR
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
TDA18271PowerScanInit_C2 (
								   ptmTDA18271Object_t_C2		pObj		// I: Tuner unit number
								   )
{
	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	// set standard mode to DVBT 1.5 MHz
	pObj->I2CMap.uBx05.bF.Std = 0x12;
	pObj->I2CMap.uBx06.bF.IF_Level = 0x00;
	pObj->I2CMap.uBx06.bF.CAL_Mode = 0x00;
	// write bytes EASY_PROG_BYTE_3 & EASY_PROG_BYTE_4
	if (TDA18271Write_C2(pObj,0x05,2) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// set AGC1Gain = 6dB
	pObj->I2CMap.uBx21.bF.AGC1_Gain = 0x00;
	// write byte EXTENDED_BYTE_18
	if (TDA18271Write_C2(pObj,0x21,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// set AGC2Gain = -15dB
	pObj->I2CMap.uBx24.bF.AGC2_Gain = 0x00;
	// set low pass filter to 1.5MHz
	pObj->I2CMap.uBx26.bF.ForceLP_Fc2_En = 0x01;
	pObj->I2CMap.uBx26.bF.LP_Fc = 0x01;
	// write byte EXTENDED_BYTE_21 to EXTENDED_BYTE_23
	if (TDA18271Write_C2(pObj,0x24,3) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// return value
	return TM_OK;
}

#define POWER_SCAN_FREQ_STEP 200000

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271PowerScan_C2:
//
// DESCRIPTION: Scan power and adjust RF Frequency
//
// RETURN:      TMBSL_ERR_IIC_ERR
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
TDA18271PowerScan_C2 (
							   ptmTDA18271Object_t_C2		pObj,		// I: Tuner unit number
							   UInt32*					puRF,		// I/O: RF frequency in hertz
							   Bool_*					pCal		// O: Calibration allowed if pCal = True
							   )
{
	UInt32 uCounter = 0;
	UInt32 count_limit = 0;
	UInt32 freq_input = 0;
	UInt32 freq_MAINPLL = 0;
	UInt32 step = 0;

	UInt8 CID_Gain = 0;
	UInt8 CID_Target = 0;

	Int8 sgn = 0;

	Bool_ wait = False;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	// set freq_input
	freq_input = *puRF;

	// search for count_limit corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (freq_input > pObj->Config.RF_CAL_CID_TARGET_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_CAL_CID_TARGET_NB_ROWS_C2);
	count_limit = pObj->Config.RF_CAL_CID_TARGET_Map[uCounter - 1].uCount_Limit;

	// check if powerscan is requested
	if (count_limit == 0)
	{
		// enable calibration and exit
		*pCal = True;
		return TM_OK;
	}

	// search for CID_Target corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (freq_input > pObj->Config.RF_CAL_CID_TARGET_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_CAL_CID_TARGET_NB_ROWS_C2);
	CID_Target = (UInt8)pObj->Config.RF_CAL_CID_TARGET_Map[uCounter - 1].uCID_Target;

	// search for sub-band corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (freq_input > pObj->Config.RF_BAND_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_BAND_NB_ROWS_C2);
	pObj->I2CMap.uBx04.bF.RF_Band = (UInt8)pObj->Config.RF_BAND_Map[uCounter - 1].uRF_Band;

	// search for Cprog corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (freq_input > pObj->Config.RF_CAL_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_CAL_NB_ROWS_C2);
	pObj->I2CMap.uBx1D.RFC_Cprog = (UInt8)pObj->Config.RF_CAL_Map[uCounter - 1].uRFC_Cprog;

	// search for Gain_Taper corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (freq_input > pObj->Config.GAIN_TAPER_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_GAIN_TAPER_NB_ROWS_C2);
	pObj->I2CMap.uBx04.bF.Gain_Taper = (UInt8)pObj->Config.GAIN_TAPER_Map[uCounter - 1].uGain_Taper;

	// write byte EASY_PROG_BYTE_2
	if (TDA18271Write_C2(pObj,0x04,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// write byte EXTENDED_BYTE_14
	if (TDA18271Write_C2(pObj,0x1D,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// set freq_MAINPLL
	freq_MAINPLL = freq_input + RF_CAL_IF_FREQ_C2;

	// calculate MAIN PLL
	if (TDA18271CalcMAINPLL_C2(pObj, freq_MAINPLL) == False)
		return TMBSL_ERR_IIC_ERR_C2;	

	// write bytes 0x0C to 0x0F
	if (TDA18271Write_C2(pObj,0x0C,4) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// wait 5 ms for pll locking
	if (TDA18271Wait_C2(pObj,5) == False)
		return TM_FALSE;

	// launch power detection measurement
	pObj->I2CMap.uBx06.bF.CAL_Mode = 0x01;

	// write byte EASY_PROG_BYTE_4
	if (TDA18271Write_C2(pObj,0x06,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// write byte EASY_PROG_BYTE_2
	if (TDA18271Write_C2(pObj,0x04,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// read power detector informations
	if (TDA18271Read_C2 (pObj,0x00,39) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	//update CID_Gain
	CID_Gain = pObj->I2CMap.uBx19.bF.CID_Gain;

	//----------------------
	// power scan algorithm
	//----------------------
	// initialization
	uCounter = 0;
	sgn = 1;	
	*puRF = freq_input;
	*pCal = False;
	step = POWER_SCAN_FREQ_STEP;
	wait = False;

	// main loop
	while (CID_Gain < CID_Target)
	{		
		// update freq_MAINPLL
		freq_MAINPLL = freq_input + sgn * uCounter + RF_CAL_IF_FREQ_C2;

		// calculate MAIN PLL
		if (TDA18271CalcMAINPLL_C2(pObj, freq_MAINPLL) == False)
			return TMBSL_ERR_IIC_ERR_C2;

		// write bytes 0x0C to 0x0F
		if (TDA18271Write_C2(pObj,0x0C,4) != True)
			return TMBSL_ERR_IIC_ERR_C2;

		if (wait)
		{
			// wait 5 ms for pll locking
			if (TDA18271Wait_C2(pObj,5) == False)
				return TM_FALSE;

			// reset wait flag
			wait = False;
		}
		else
		{
			// wait 100 �s for pll locking
		}

		// write byte EASY_PROG_BYTE_2
		if (TDA18271Write_C2(pObj,0x04,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;

		// read power detector informations
		if (TDA18271Read_C2 (pObj,0x00,39) != True)
			return TMBSL_ERR_IIC_ERR_C2;

		// update CID_Gain
		CID_Gain = pObj->I2CMap.uBx19.bF.CID_Gain;

		// increase count
		uCounter += step;

		// check uCounter
		if (uCounter >= count_limit)
		{
			if (sgn > 0)
			{
				// update sgn
				sgn = -sgn;

				// update uCounter
				uCounter = step;

				// update wait flag
				wait = True;
			}
			else
			{
				// exit loop
				break;
			}
		}
	}

	// return results
	if (CID_Gain >= CID_Target)
	{
		*pCal = True;
		*puRF = freq_MAINPLL - RF_CAL_IF_FREQ_C2;
	}
	else
	{
		*pCal = False;
		*puRF = freq_input;
	}

	return TM_OK;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271CalcRFFilterCurve_C2:
//
// DESCRIPTION: Calculate RF Filter curve coefficients
//
// RETURN:      TMBSL_ERR_IIC_ERR
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
TDA18271CalcRFFilterCurve_C2 (
									   ptmTDA18271Object_t_C2			pObj			// I: tuner Object
									   )
{	
	tmErrorCode_t ret = TM_OK;
	UInt32	uCounter = 0;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	// wait 200 ms for die temperature stabilization
	if (TDA18271Wait_C2(pObj,200) == False)
		return TM_FALSE;

	// power scan initialization
	TDA18271PowerScanInit_C2(pObj);

	// calculate RF filter curve
	for (uCounter = 0; uCounter < TDA18271_RF_BAND_NB_ROWS_C2; uCounter++)
	{
		if (pObj->Config.RF_BAND_Map[uCounter].uRF1_default != 0)
		{
			ret = TDA18271RFTrackingFiltersInit_C2(pObj, &(pObj->Config.RF_BAND_Map[uCounter]));
			if (ret != TM_OK)
				return ret;
		}
	}

	// sense temperature
	ret = TDA18271ThermometerRead_C2(pObj, &(pObj->Config.uTMVALUE_RFCAL));
	if (ret != TM_OK)
		return ret;

	// return value
	return TM_OK;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271RFTrackingFiltersInit_C2:
//
// DESCRIPTION: Initialize RF Filter calibration
//
// RETURN:      TMBSL_ERR_IIC_ERR
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
TDA18271RFTrackingFiltersInit_C2 (
	ptmTDA18271Object_t_C2			pObj,			// I: tuner Object
	ptmTDA18271_RF_BAND_Map_t_C2	pRF_BAND_Map	// I: address of RF band map
	)
{
	tmErrorCode_t ret = TM_OK;

	UInt32	uCounter = 0;

	UInt8	uCprog_cal_1 = 0;
	UInt8	uCprog_table_1 = 0;
	UInt8	uCprog_cal_2 = 0;
	UInt8	uCprog_table_2 = 0;
	UInt8	uCprog_cal_3 = 0;
	UInt8	uCprog_table_3 = 0;

	Bool_	bCal = False;

	tmTDA18271StandardMode_t_C2	StandardMode = pObj->StandardMode;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	//----------------------
	// RF tracking filter calibration at RF1 frequency
	//----------------------
	// test uRF1_default value
	if (pRF_BAND_Map->uRF1_default == 0)
		return ret;

	// look for optimized calibration frequency
	pRF_BAND_Map->uRF1 = pRF_BAND_Map->uRF1_default;
	ret = TDA18271PowerScan_C2(pObj, &pRF_BAND_Map->uRF1, &bCal);
	if (ret != TM_OK)
		return ret;

	// search for uCprog_table_1 corresponding to RF1
	uCounter = 0;
	do uCounter ++;
	while (pRF_BAND_Map->uRF1 > pObj->Config.RF_CAL_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_CAL_NB_ROWS_C2);
	uCprog_table_1 = (UInt8)pObj->Config.RF_CAL_Map[uCounter - 1].uRFC_Cprog;

	if(bCal)
	{
		// launch tracking filter calibration
		ret = TDA18271CalibrateRF_C2(pObj, pRF_BAND_Map->uRF1, &uCprog_cal_1);
		if (ret != TM_OK)
			return ret;
	}
	else
	{
		// use tracking filter table value
		uCprog_cal_1 = uCprog_table_1;
	}

	// set A1 coefficient
	pRF_BAND_Map->uRF_A1 = 0;

	// calculate B1 coefficient
	pRF_BAND_Map->uRF_B1 = uCprog_cal_1 - uCprog_table_1;

	//----------------------
	// RF tracking filter calibration at RF2 frequency
	//----------------------
	// test RF2 value
	if (pRF_BAND_Map->uRF2_default == 0)
		return ret;

	// look for optimized calibration frequency
	pRF_BAND_Map->uRF2 = pRF_BAND_Map->uRF2_default;
	ret = TDA18271PowerScan_C2(pObj, &pRF_BAND_Map->uRF2, &bCal);
	if (ret != TM_OK)
		return ret;

	// search for uCprog_table_2 corresponding to RF2
	uCounter = 0;
	do uCounter ++;
	while (pRF_BAND_Map->uRF2 > pObj->Config.RF_CAL_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_CAL_NB_ROWS_C2);
	uCprog_table_2 = (UInt8)pObj->Config.RF_CAL_Map[uCounter - 1].uRFC_Cprog;

	if(bCal)
	{
		// launch tracking filter calibration
		ret = TDA18271CalibrateRF_C2(pObj, pRF_BAND_Map->uRF2, &uCprog_cal_2);
		if (ret != TM_OK)
			return ret;
	}
	else
	{
		// use tracking filter table value
		uCprog_cal_2 = uCprog_table_2;
	}

	// calculate A1 coefficient
	pRF_BAND_Map->uRF_A1 = ((uCprog_cal_2 - uCprog_table_2 - (uCprog_cal_1 - uCprog_table_1)) * 1000000)
		/ (Int32)((pRF_BAND_Map->uRF2 - pRF_BAND_Map->uRF1) / 1000000);

	//----------------------
	// RF tracking filter calibration at RF3 frequency
	//----------------------
	// test RF3 value
	if (pRF_BAND_Map->uRF3_default == 0)
		return ret;

	// look for optimized calibration frequency
	pRF_BAND_Map->uRF3 = pRF_BAND_Map->uRF3_default;
	ret = TDA18271PowerScan_C2(pObj, &pRF_BAND_Map->uRF3, &bCal);
	if (ret != TM_OK)
		return ret;

	// search for uCprog_table_3 corresponding to RF3
	uCounter = 0;
	do uCounter ++;
	while (pRF_BAND_Map->uRF3 > pObj->Config.RF_CAL_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_CAL_NB_ROWS_C2);
	uCprog_table_3 = (UInt8)pObj->Config.RF_CAL_Map[uCounter - 1].uRFC_Cprog;

	if(bCal)
	{
		// launch tracking filter calibration
		ret = TDA18271CalibrateRF_C2(pObj, pRF_BAND_Map->uRF3, &uCprog_cal_3);
		if (ret != TM_OK)
			return ret;
	}
	else
	{
		// use tracking filter table value
		uCprog_cal_3 = uCprog_table_3;
	}

	// calculate A2 coefficient
	pRF_BAND_Map->uRF_A2 = ((uCprog_cal_3 - uCprog_table_3 - (uCprog_cal_2 - uCprog_table_2)) * 1000000) 
		/ (Int32)((pRF_BAND_Map->uRF3 - pRF_BAND_Map->uRF2) / 1000000);

	// calculate B2 coefficient
	pRF_BAND_Map->uRF_B2 = uCprog_cal_2 - uCprog_table_2;

	// return value
	return TM_OK;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271ThermometerRead_C2:
//
// DESCRIPTION: Read die temperature
//
// RETURN:      TMBSL_ERR_IIC_ERR
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
TDA18271ThermometerRead_C2 (
									 ptmTDA18271Object_t_C2		pObj,		// I: Tuner unit number
									 UInt32*					puValue		// O: Read thermometer value
									 )
{
	tmErrorCode_t ret = TMBSL_ERR_IIC_ERR_C2;

	UInt32 uCounter = 0;

	// test the Object
	if (pObj == Null || pObj->init == False)
		return TMBSL_ERR_TUNER_NOT_INITIALIZED_C2;

	// switch thermometer on
	pObj->I2CMap.uBx01.bF.TM_ON = 0x01;

	// write byte THERMO_BYTE
	if (TDA18271Write_C2(pObj,0x01,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// read byte THERMO_BYTE
	if (TDA18271Read_C2 (pObj, 0x00, 16) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	// set & write TM_Range
	if (((pObj->I2CMap.uBx01.bF.TM_D == 0x00) && (pObj->I2CMap.uBx01.bF.TM_Range == 0x01)) || ((pObj->I2CMap.uBx01.bF.TM_D == 0x08) && (pObj->I2CMap.uBx01.bF.TM_Range == 0x00)))
	{
		pObj->I2CMap.uBx01.bF.TM_Range = !(pObj->I2CMap.uBx01.bF.TM_Range);

		// write byte THERMO_BYTE
		if (TDA18271Write_C2(pObj,0x01,1) != True)
			return TMBSL_ERR_IIC_ERR_C2;

		// wait 10ms
		if (TDA18271Wait_C2(pObj,10) == False)
			return TM_FALSE;   

		// read byte THERMO_BYTE
		if (TDA18271Read_C2 (pObj, 0x00, 16) != True)
			return TMBSL_ERR_IIC_ERR_C2;
	}

	// search for TMVALUE corresponding to TM_D
	uCounter = 0;
	do uCounter ++;
	while (pObj->I2CMap.uBx01.bF.TM_D > pObj->Config.THERMOMETER_Map[uCounter - 1].uTM_D && uCounter < TDA18271_THERMOMETER_NB_ROWS_C2);

	// get TMVALUE value
	if (pObj->I2CMap.uBx01.bF.TM_Range == 0x00)
		*puValue = (UInt8)pObj->Config.THERMOMETER_Map[uCounter - 1].uTM_60_92;
	else
		*puValue = (UInt8)pObj->Config.THERMOMETER_Map[uCounter - 1].uTM_92_122;

	// switch thermometer off
	pObj->I2CMap.uBx01.bF.TM_ON = 0x00;

	// write byte THERMO_BYTE
	if (TDA18271Write_C2(pObj,0x01,1) != True)
		return TMBSL_ERR_IIC_ERR_C2;

	return TM_OK;
}