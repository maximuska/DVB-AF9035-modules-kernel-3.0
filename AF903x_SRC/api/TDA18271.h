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
// FILE NAME:    tmbslTDA18271Local.h
//
// DESCRIPTION:  define the Object for the TDA18271
//
// DOCUMENT REF: DVP Software Coding Guidelines v1.14
//               DVP Board Support Library Architecture Specification v0.5
//
// NOTES:        
//-----------------------------------------------------------------------------
//
#ifndef _TMBSL_TDA18271_H //-----------------
#define _TMBSL_TDA18271_H

#include "TDA18271Local.h"

//-----------------------------------------------------------------------------
// Standard include files:
//-----------------------------------------------------------------------------
//#include "dvp.h"
//#include "tmbslTuner.h"
//-----------------------------------------------------------------------------
// Project include files:
//-----------------------------------------------------------------------------
//
Bool_    SY_Read(UInt32  uAddress,
                UInt32  uSubAddress,
                UInt32  uNbData,
                UInt32* pDataBuff
);

Bool_    SY_Write(UInt32  uAddress,
                 UInt32  uSubAddress,
                 UInt32  uNbData,
                 UInt32* pDataBuff
);

tmErrorCode_t
tmbslTDA18271Init(
    tmUnitSelect_t     TunerUnit,    //  I: Tuner unit number
    tmbslTuParam_t     Param         //  I: setup parameters
);

tmErrorCode_t
tmbslTDA18271SetConfig(
    tmUnitSelect_t     TunerUnit,  //  I: TunerUnit number
    UInt32             uItemId,    //  I: Identifier of the item to modify
    UInt32             uValue      //  I: Value to set for the Config item
);

tmErrorCode_t
tmbslTDA18271SetRf(
    tmUnitSelect_t		TunerUnit,  //  I: Tuner unit number
    UInt32				uRF			//  I: RF frequency in hertz
);

#endif // _TMBSL_TDA18271LOCAL_H //---------------