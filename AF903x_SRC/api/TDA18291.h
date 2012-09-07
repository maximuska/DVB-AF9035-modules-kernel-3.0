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
 *
 * FILE NAME:    tmbslTDA18291.h
 *
 * DESCRIPTION:  define the object for the 18281HNC1
 *
 * DOCUMENT REF: DVP Software Coding Guidelines v1.14
 *               DVP Board Support Library Architecture Specification v0.5
 *
 * NOTES:        
 */

#ifndef _TMBSL_18281HNC1_H
#define _TMBSL_18281HNC1_H

/**
 * Standard include files:
 */


/**
 * Project include files:
 */


/**
 * Types and defines:
 */

tmErrorCode_t
tmbslTDA18291Init(
    tmUnitSelect_t     TunerUnit,    /*  I: Tuner unit number */
    tmbslTuParam_t     sParam        /*  I: setup parameters */
);
tmErrorCode_t 
tmbslTDA18291DeInit (
    tmUnitSelect_t TunerUnit     /*  I: Tuner unit number */
);
tmErrorCode_t   
tmbslTDA18291GetSWVersion (
    ptmSWVersion_t     pSWVersion        /*  I: Receives SW Version */
);
tmErrorCode_t
tmbslTDA18291SetConfig(
    tmUnitSelect_t     TunerUnit,  /*  I: TunerUnit number */
    UInt32             uItemId,    /*  I: Identifier of the item to modify */
    UInt32             uValue      /*  I: Value to set for the config item */
);
tmErrorCode_t
tmbslTDA18291GetConfig(
    tmUnitSelect_t     TunerUnit,  /*  I: Tuner unit number */
    UInt32             uItemId,    /*  I: Identifier of the item to modify */
    UInt32*            puValue     /*  I: Value to set for the config item */
);
tmErrorCode_t
tmbslTDA18291SetRf(
    tmUnitSelect_t		TunerUnit,  /*  I: Tuner unit number */
    UInt32				LO_Freq     /*  I: Frequency in hertz */
);
tmErrorCode_t
tmbslTDA18291GetRf(
    tmUnitSelect_t  TunerUnit,     /*  I: Tuner unit number */
    UInt32*         pLO_Freq       /*  O: Frequency in hertz */
);
#endif
