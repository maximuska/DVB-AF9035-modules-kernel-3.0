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
// FILE NAME:    tmbslTDA18271_C2_Askey.h
//
// DESCRIPTION:  define the object for the TDA18271_C2_Askey
//
// DOCUMENT REF: DVP Software Coding Guidelines v1.14
//               DVP Board Support Library Architecture Specification v0.5
//
// NOTES:        
//-----------------------------------------------------------------------------
//
#ifndef _TMBSL_TDA18271_C2_Askey_H //-----------------
#define _TMBSL_TDA18271_C2_Askey_H

//-----------------------------------------------------------------------------
// Standard include files:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// Project include files:
//-----------------------------------------------------------------------------
//
//#ifndef NXPFE
#ifdef __cplusplus
extern "C"
{
#endif
//#endif // NXPFE

//-----------------------------------------------------------------------------
// Types and defines:
//-----------------------------------------------------------------------------
//
tmErrorCode_t
TDA18271Init_C2_Askey (
			  tmUnitSelect_t			TunerUnit	// I: Tuner Object
			  );
Bool_ 
TDA18271InitTick_C2_Askey(
			  ptmTDA18271Object_t_C2_Askey	pObj,	    // I: Tuner unit number
			  UInt16					wTime		// I: time to wait forTDA18271Init
			  );
Bool_ 
TDA18271WaitTick_C2_Askey(
			  ptmTDA18271Object_t_C2_Askey	pObj		// I: Tuner unit number
			  );
Bool_ 
TDA18271Write_C2_Askey(
			  ptmTDA18271Object_t_C2_Askey	pObj,		// I: Tuner unit number
			  UInt8					    uSubAddress,// I: sub address
			  UInt8					    uNbData		// I: nb of data
			  );
Bool_ 
TDA18271Read_C2_Askey(
			 ptmTDA18271Object_t_C2_Askey		pObj,		// I: Tuner unit number
			 UInt8					    uSubAddress,// I: sub address
			 UInt8					    uNbData		// I: nb of data
			 );
Bool_ 
TDA18271Wait_C2_Askey(
			 ptmTDA18271Object_t_C2_Askey		pObj,		//  I: Tuner unit number
			 UInt16					    wTime		//  I: time to wait for
			 );
Bool_ 
TDA18271ShiftLog_C2_Askey(
			 ptmTDA18271Object_t_C2_Askey	    pObj, 	    // I: Tuner unit number
			 UInt32					    uNbRows	    // I: nb of lines
			 );
tmErrorCode_t
TDA18271SetStandardMode_C2_Askey(
			 ptmTDA18271Object_t_C2_Askey		pObj,		// I: tuner Object
			 tmTDA18271StandardMode_t_C2_Askey	StandardMode// I: Standard mode of this device
			 );
tmErrorCode_t
TDA18271GetStandardMode_C2_Askey(
			 ptmTDA18271Object_t_C2_Askey			pObj,			// I: tuner Object
			 tmTDA18271StandardMode_t_C2_Askey	*pStandardMode	// I: Standard mode of this device
			 );
tmErrorCode_t
TDA18271SetPowerState_C2_Askey(
			 ptmTDA18271Object_t_C2_Askey		pObj,		// I: tuner Object
			 tmTDA18271PowerState_t_C2_Askey	powerState	// I: Power state of this device
			 );
tmErrorCode_t
TDA18271GetPowerState_C2_Askey(
			 ptmTDA18271Object_t_C2_Askey 	pObj,		// I: tuner Object
			 tmTDA18271PowerState_t_C2_Askey	*pPowerState// I: Power state of this device
			 );
Bool_
TDA18271CalcMAINPLL_C2_Askey (
			 ptmTDA18271Object_t_C2_Askey	    pObj,		// I: tuner Object
			 UInt32					    uLO			// I: local oscillator frequency in hertz
			 );
Bool_
TDA18271CalcCALPLL_C2_Askey (
			 ptmTDA18271Object_t_C2_Askey		pObj,		// I: tuner Object
			 UInt32					    uLO			// I: local oscillator frequency in hertz
			 );
tmErrorCode_t
TDA18271CalcRFFilterCurve_C2_Askey (
			 ptmTDA18271Object_t_C2_Askey		pObj		// I: tuner Object
			 );
tmErrorCode_t
TDA18271RFTrackingFiltersInit_C2_Askey (
			 ptmTDA18271Object_t_C2_Askey			pObj,			// I: tuner Object
			 ptmTDA18271_RF_BAND_Map_t_C2_Askey	pRF_BAND_Map	// I: address of RF band map
			 );
tmErrorCode_t
TDA18271CalibrateRF_C2_Askey (
			 ptmTDA18271Object_t_C2_Askey		pObj,		// I: tuner Object
			 UInt32					    uRF,		// I: RF frequency in hertz
			 UInt8*					    puCprog     // I: Address of the variable to output the Cprog value
			 );
tmErrorCode_t
TDA18271PowerScan_C2_Askey (
			 ptmTDA18271Object_t_C2_Askey		pObj,		// I: Tuner unit number
			 UInt32*					puRF,		// I/O: RF frequency in hertz
			 Bool_*					    pCal		// O: Calibration allowed if pCal = True
			 );
tmErrorCode_t
TDA18271PowerScanInit_C2_Askey (
			 ptmTDA18271Object_t_C2_Askey		pObj		// I: Tuner unit number
			 );
tmErrorCode_t
TDA18271ThermometerRead_C2_Askey (
			 ptmTDA18271Object_t_C2_Askey		pObj,		// I: Tuner unit number
			 UInt32*					puValue		// O: Read thermometer value
			 );
tmErrorCode_t
allocInstance_C2_Askey (
			 UInt32					    DeviceUnit,	// I: Tuner unit number
			 pptmTDA18271Object_t_C2_Askey	ppDrvObject	// I: Tuner Object
			 );
tmErrorCode_t
deAllocInstance_C2_Askey (		
			 UInt32					    DeviceUnit	// I: Tuner unit number
			 );
tmErrorCode_t
getInstance_C2_Askey (
			 tmUnitSelect_t			    DeviceUnit,	// I: Tuner unit number
			 pptmTDA18271Object_t_C2_Askey	ppDrvObject	// I: Tuner Object
			 );
tmErrorCode_t
             tmbslTDA18271Init_C2_Askey(
             tmUnitSelect_t		        TunerUnit,    //  I: Tuner unit number
             tmbslTuParam_t_C2_Askey		    Param         //  I: setup parameters
             );
tmErrorCode_t
    tmbslTDA18271SetConfig_C2_Askey(
    tmUnitSelect_t		TunerUnit,  //  I: TunerUnit number
    UInt32				uItemId,    //  I: Identifier of the item to modify
    UInt32				uValue      //  I: Value to set for the config item
    );
tmErrorCode_t
    tmbslTDA18271SetRf_C2_Askey(
    tmUnitSelect_t		TunerUnit,  //  I: Tuner unit number
    UInt32				uRF			//  I: RF frequency in hertz
    );

//#ifndef NXPFE
#ifdef __cplusplus
}
#endif
//#endif // NXPFE

#endif // TM<MODULE>_H //---------------
