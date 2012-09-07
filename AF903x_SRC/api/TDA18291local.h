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
 * FILE NAME:    tmbsl18291local.h
 *
 * DESCRIPTION:  define the object for the TDA18291
 *
 * DOCUMENT REF: DVP Software Coding Guidelines v1.14
 *               DVP Board Support Library Architecture Specification v0.5
 *
 * NOTES:        
 */

#ifndef _TMBSL_TDA18291LOCAL_H
#define _TMBSL_TDA18291LOCAL_H

#include "type.h"


/**
 * Standard include files:
 */
/* #include "hpi_basictypes.h"
   #include "tmdlFe.h"
   #include "tmhalFEtypes.h"
   #include "dvp.h"
   #include "tmbslTuner.h" */

/**
 * Project include files:
 */

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Types and defines:
 */

#define TDA18291_BSL_COMP_NUM    1
#define TDA18291_BSL_MAJOR_VER   1
#define TDA18291_BSL_MINOR_VER   0

/* #define AF901X_CAN_TUNER            0x1
   #define AF901X_SILICON_TUNER        0x2 */


/**
 * ERROR CODES
 *
 * ++from Max
 */
#define TMBSL_ERR_TUNER_BASE    0x80000000U
#define TM_ERR_BAD_UNIT_NUMBER  0x00000001U
#define TM_ERR_NOT_INITIALIZED  0x00000002U
#define TM_ERR_BAD_PARAMETER    0x00000003U
#define TM_ERR_NOT_SUPPORTED    0x00000004U
#define TM_ERR_IIC_ERR          0x00000005U

typedef enum _tmPowerState_t
{
    tmPowerOn = 1,
    tmPowerStandby,
    tmPowerSuspend,
    tmPowerOff
} tmPowerState_t;




/* Invalid unit id */
#define TMBSL_ERR_TUNER_BAD_UNIT_NUMBER \
(TMBSL_ERR_TUNER_BASE + TM_ERR_BAD_UNIT_NUMBER)

/* Component is not initialized */
#define TMBSL_ERR_TUNER_NOT_INITIALIZED \
(TMBSL_ERR_TUNER_BASE+ TM_ERR_NOT_INITIALIZED)

/* Invalid input parameter */
#define TMBSL_ERR_TUNER_BAD_PARAMETER \
(TMBSL_ERR_TUNER_BASE + TM_ERR_BAD_PARAMETER)

/* Function is not supported */
#define TMBSL_ERR_TUNER_NOT_SUPPORTED \
(TMBSL_ERR_TUNER_BASE + TM_ERR_NOT_SUPPORTED)

/* Function is not supported */
#define TMBSL_ERR_IIC_ERR \
(TMBSL_ERR_TUNER_BASE + TM_ERR_IIC_ERR)

#define TDA18291_MAX_UNITS		2
#define TDA18291_NB_REGISTERS		16
#define	TDA18291_NB_AGC_RANGES	128	

/* Indexes of TDA18291 registers */
#define TDA18291_REG_H00 0x00
#define TDA18291_REG_H01 0x01
#define TDA18291_REG_H02 0x02
#define TDA18291_REG_H03 0x03
#define TDA18291_REG_H04 0x04
#define TDA18291_REG_H05 0x05
#define TDA18291_REG_H06 0x06
#define TDA18291_REG_H07 0x07
#define TDA18291_REG_H08 0x08
#define TDA18291_REG_H09 0x09
#define TDA18291_REG_H0A 0x0A
#define TDA18291_REG_H0B 0x0B
#define TDA18291_REG_H0C 0x0C
#define TDA18291_REG_H0D 0x0D
#define TDA18291_REG_H0E 0x0E
#define TDA18291_REG_H0F 0x0F

#define OM5768_BOARD_DEF			0x57680000  /* 10047 + TDA18281 */
#define CUSTOM_BOARD_DEF            0x00000000  /* custom */

#define CUTOFF_FREQ_FOR_5MHZ		0
#define CUTOFF_FREQ_FOR_6MHZ		1
#define CUTOFF_FREQ_FOR_7MHZ		2
#define CUTOFF_FREQ_FOR_8MHZ		3

typedef float   Float;

typedef unsigned long   UInt32;     /* 32 bit unsigned integer */
typedef unsigned short  UInt16;     /* 16 bit unsigned integer */
typedef unsigned char   UInt8;      /*  8 bit unsigned integer */
typedef UInt32          tmErrorCode_t;
typedef unsigned int    Bool_;       /* Boolean (True/False) */
typedef int             tmUnitSelect_t, *ptmUnitSelect_t; 
#define Null            0

#define TM_OK                               0U         /* Global success return status   */
#define TM_FALSE                            0
#define TM_TRUE                             1

#define True TM_TRUE
#define False TM_FALSE 

/* +++ from Max */
Bool_    SY_Read2(UInt32  uAddress,
                UInt32  uSubAddress,
                UInt32  uNbData,
                UInt32* pDataBuff
);

Bool_    SY_Write2(UInt32  uAddress,
                 UInt32  uSubAddress,
                 UInt32  uNbData,
                 UInt32* pDataBuff
);


typedef struct _tmhalFEBslSystemFunc_t
{
        Bool_    (*SY_Write)         (UInt32  uAddress,
                                     UInt32  uSubAddress,
                                     UInt32  uNbData,
                                     UInt32* pDataBuff);
        Bool_    (*SY_Read)          (UInt32  uAddress,
                                     UInt32  uSubAddress,
                                     UInt32  uNbData,
                                     UInt32* pDataBuff);
} tmhalFEBslSystemFunc_t, *ptmhalFEBslSystemFunc_t;

typedef struct _tmbslTuParam_t
{
      unsigned long             uHwAddress;
      tmhalFEBslSystemFunc_t    systemFunc;    
} tmbslTuParam_t, *ptmbslTuParam_t; 

typedef struct tmSWVersion
{
    UInt32      compatibilityNr;        /* Interface compatibility number */
    UInt32      majorVersionNr;         /* Interface major version number */
    UInt32      minorVersionNr;         /* Interface minor version number */

} tmSWVersion_t, *ptmSWVersion_t; 


#if 0

typedef enum _tmTDA18281StandardMode_t {
    tmDigital_TV_ATSC_6MHz,                 /* Digital TV ATSC 6MHz */
    tmDigital_TV_DVBT_7MHz,                 /* Digital TV DVB-T 7MHz */
    tmDigital_TV_DVBT_8MHz,                 /* Digital TV DVB-T 8MHz */
    tmAnalog_TV_MN,                         /* Analog TV M/N */
    tmAnalog_TV_B,                          /* Analog TV B */
    tmAnalog_TV_GH,                         /* Analog TV G/H */
    tmAnalog_TV_I,                          /* Analog TV I */
    tmAnalog_TV_DK,                         /* Analog TV D/K */
    tmAnalog_TV_L,                          /* Analog TV L */
    tmAnalog_TV_LL,                         /* Analog TV L' */
    tmAnalog_FM_Radio,                      /* Analog FM Radio */
    tmDigital_TV_QAM_6MHz,                  /* Digital TV QAM 6MHz */
    tmDigital_TV_QAM_8MHz,                  /* Digital TV QAM 8MHz */
    tmStandardNotSupported,                 /* Not supported standard */
} tmTDA18281StandardMode_t, *ptmTDA18281StandardMode_t;

#endif

typedef enum _tm18291cfgIndex_t {
    BOARD = 0,
    FEINIT = 100,
    GETNBOFUNIT = 200,
	AGC_BUS_ENABLE = 208,
    AGC_EXT,
	AGC_GAIN_INDEX,
	AGC_GAIN_VALUE,
	LO_XTAL_FREQ_INDEX,
	LO_XTAL_FREQ_VALUE,
	XTAL_MODE,
	ENABLE_LNA,
	CUT_OFF_IND,
    BANDWIDTH = 300,
    GETLEVEL = 301,
    SET_CUTOFF_FREQ = 302
} tm18291cfgIndex_t;


typedef struct _tm18291agcMap_t {
    UInt32	uGain;	  /* Actual value of Gain (equals  (AGC1 + AGC2 + 6.5) * 10 ) */
    UInt32	uAGC_BB;  /* Digit of 9 bits to write in reg and  */
					  /* corresponding to AGC1[2] to AGC1[0] AGC2[5] to AGC2[0] */
} tm18291agcMap_t, *ptm18291agcMap_t;

typedef struct _tm18291config_t {
    UInt32	uBoard;
    UInt32	Nb;
    UInt32	Index;
    tm18291agcMap_t Map[TDA18291_NB_AGC_RANGES];
} tm18291config_t, *ptm18291config_t;

typedef struct _tm18291I2CData_t {
	UInt32	h00;	
	UInt32	h01;	
	UInt32	h02;	
	UInt32	h03;	
	UInt32	h04;	
	UInt32	h05;	
	UInt32	h06;	
	UInt32	h07;	
	UInt32	h08;	
	UInt32	h09;	
	UInt32	h0A;	
	UInt32	h0B;	
	UInt32	h0C;	
	UInt32	h0D;	
	UInt32	h0E;
	UInt32	h0F;
} tm18291I2CData_t, *ptm18291I2CData_t;

typedef struct _tm18291UserData_t {
	UInt8	FlagI2CWrite;			/* FlagI2CWrite = 1; */
	UInt8	FlagPLLCalculateNandK;	/* FlagPLLCalculateNandK = 1; */
	UInt32	AGCBB;						
	UInt8	AGCBusEn;				/* AGCBusEn	[*] AGC control via I2C bus */		
	UInt8	AGCext;					/* AGCext	[*] AGC control via dedicated pin */
	UInt32	AGCGain;				/* AGCGain	[*] AGC gain [AGCGain = (AGCgain + 6.5) * 10] */
	UInt8	FC;						/* FC		[*] Cutt off frequency */
	UInt32	Flo_max08;						
	UInt32	Flo_max09;						
	UInt32	Flo_max10;						
	UInt32	Flo_max11;
	UInt32	Flo_max12;
	UInt32	Flo_max13;
	UInt32	Flo_max14;
	UInt32	Flo_max15;
	UInt8	h03b5;						
	UInt8	h04b3tob0;						
	UInt8	h09b7tob6;						
	UInt8	h0Ab1tob0;						
	UInt8	h0Ab7;						
	UInt8	h0Bb7tob6;						
	UInt8	h0C;						
	UInt8	h0D;						
	UInt8	h0E;						
	UInt8	h0F;						
	UInt32	LO_Frac;						
	UInt32	LO_Int;					
	UInt8	LO_Postdiv;					
	UInt8	LO_Presc;						
	UInt32	LO_VCOFreq;						
	UInt32	LO_XTALFreq;		/* 52MHz or 26 MHz or other values. See gTableXtalFreq */
	UInt8	PDIC;						
	UInt8	PDIF;						
	UInt8	PDRefBuff;						
	UInt8	PDRF;						
	UInt8	PDSYNTH;						
	UInt8	PDVCO;
	UInt8   PD_Xtout;						
	UInt8	Ref_Freq;
	UInt8	Enable_LNA;
	UInt8	CutOffIndex;
} tm18291UserData_t, *ptm18291UserData_t;


typedef struct _tmAFAInfo_t {
    Demodulator*	demodulator;
    UInt8           chip;
} tmAFAInfo_t, *ptmAFAInfo_t;

typedef struct _tm18291object_t {
    tmAFAInfo_t				    AFAInfo;
    Bool_                        init;
    UInt32                      uHwAddress;
    tmhalFEBslSystemFunc_t      systemFunc;
    tmPowerState_t              curPowerState;
    tm18291config_t           config;
    UInt32                      pTunerReg[TDA18291_NB_REGISTERS];
    UInt32                      LO_FreqProg;
    UInt32                      uTickEnd;
    tm18291UserData_t         UserData;
} tm18291object_t, *ptm18291object_t;

/**
 * Global data:
 */

static UInt32 gTableXtalFreq[] =
{ 
	52000,
	19200,
	26000,
	38400
};
static UInt8 gTableCutOffVal[] =
{ 
	3,
	2,
	1
	
};

#ifdef __cplusplus
}
#endif

#endif
