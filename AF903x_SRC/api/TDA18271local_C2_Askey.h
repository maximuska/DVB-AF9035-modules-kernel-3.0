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
// FILE NAME:    tmbslTDA18271local_C2_Askey.h
//
// DESCRIPTION:  define the Object for the TDA18271_C2_Askey
//
// DOCUMENT REF: DVP Software Coding Guidelines v1.14
//               DVP Board Support Library Architecture Specification v0.5
//
// NOTES:        
//-----------------------------------------------------------------------------
//
#ifndef _TMBSL_TDA18271LOCAL_C2_Askey_H //-----------------
#define _TMBSL_TDA18271LOCAL_C2_Askey_H

#include "type.h"

//-----------------------------------------------------------------------------
// Standard include files:
//-----------------------------------------------------------------------------

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
#define TMBSL_TDA18271_COMPONENT_NAME_C2_Askey TDA18271_C2_Askey
#define TMBSL_TDA18271_COMPONENT_NAME_STR_C2_Askey "TDA18271_C2_Askey"

#define _SYSTEMFUNC (pObj->SystemFunc)

#define TDA18271_BSL_COMP_NUM_C2_Askey    3 // Major protocol change - Specification change required
#define TDA18271_BSL_MAJOR_VER_C2_Askey   4 // Minor protocol change - Specification change required
#define TDA18271_BSL_MINOR_VER_C2_Askey   3 // Software update - No protocol change - No specification change required
#define TDA18271_BSL_SUB_VER_C2_Askey     0 // Askey for through TTL3200 AV-In model authentication

//-------------
// ERROR CODES    
//-------------
#define TMBSL_ERR_TUNER_BASE_C2_Askey	0x80000000U
#define TM_ERR_BAD_UNIT_NUMBER_C2_Askey	0x00000001U
#define TM_ERR_NOT_INITIALIZED_C2_Askey	0x00000002U
#define TM_ERR_BAD_PARAMETER_C2_Askey	0x00000003U
#define TM_ERR_NOT_SUPPORTED_C2_Askey	0x00000004U
#define TM_ERR_IIC_ERR_C2_Askey			0x00000005U
// Invalid unit id
#define TMBSL_ERR_TUNER_BAD_UNIT_NUMBER_C2_Askey \
    (TMBSL_ERR_TUNER_BASE_C2_Askey + TM_ERR_BAD_UNIT_NUMBER_C2_Askey)

// Component is not initialized
#define TMBSL_ERR_TUNER_NOT_INITIALIZED_C2_Askey \
    (TMBSL_ERR_TUNER_BASE_C2_Askey+ TM_ERR_NOT_INITIALIZED_C2_Askey)

// Invalid input parameter
#define TMBSL_ERR_TUNER_BAD_PARAMETER_C2_Askey \
    (TMBSL_ERR_TUNER_BASE_C2_Askey + TM_ERR_BAD_PARAMETER_C2_Askey)

// Function is not supported
#define TMBSL_ERR_TUNER_NOT_SUPPORTED_C2_Askey \
    (TMBSL_ERR_TUNER_BASE_C2_Askey + TM_ERR_NOT_SUPPORTED_C2_Askey)

// Function is not supported
#define TMBSL_ERR_IIC_ERR_C2_Askey \
    (TMBSL_ERR_TUNER_BASE_C2_Askey + TM_ERR_IIC_ERR_C2_Askey)

#define TDA18271_MAX_UNITS_C2_Askey					 10			//
#define TDA18271_NB_BYTES_C2_Askey					 39			//
#define TDA18271_LOG_NB_ROWS_C2_Askey				     300		//
#define TDA18271_LOG_BLANK_DATA_C2_Askey				 256		//

#define	TDA18271_IR_MEAS_NB_COLUMNS_C2_Askey			 2			//
#define	TDA18271_IR_CAL_NB_COLUMNS_C2_Askey			 2			//
#define	TDA18271_BP_FILTER_NB_COLUMNS_C2_Askey		 2			//
#define	TDA18271_RF_BAND_NB_COLUMNS_C2_Askey			 12			//
#define	TDA18271_GAIN_TAPER_NB_COLUMNS_C2_Askey		 2			//
#define	TDA18271_RF_CAL_NB_COLUMNS_C2_Askey			 2			//
#define	TDA18271_RF_CAL_DC_OVER_DT_NB_COLUMNS_C2_Askey 2			//
#define	TDA18271_RF_CAL_KMCO_NB_COLUMNS_C2_Askey		 4			//
#define	TDA18271_RF_CAL_CID_TARGET_NB_COLUMNS_C2_Askey 3			//
#define	TDA18271_CAL_PLL_NB_COLUMNS_C2_Askey			 3			//
#define	TDA18271_MAIN_PLL_NB_COLUMNS_C2_Askey		     3			//


#define	TDA18271_IR_MEAS_NB_ROWS_C2_Askey			    3			//
#define	TDA18271_IR_CAL_NB_ROWS_C2_Askey				3			//
#define	TDA18271_BP_FILTER_NB_ROWS_C2_Askey			7			//
#define	TDA18271_RF_BAND_NB_ROWS_C2_Askey			    7			//
#define	TDA18271_GAIN_TAPER_NB_ROWS_C2_Askey			85			//
#define	TDA18271_RF_CAL_NB_ROWS_C2_Askey				437			//	
#define	TDA18271_RF_CAL_DC_OVER_DT_NB_ROWS_C2_Askey	101			//
#define	TDA18271_RF_CAL_KMCO_NB_ROWS_C2_Askey		    5			//
#define	TDA18271_RF_CAL_CID_TARGET_NB_ROWS_C2_Askey	12			//
#define	TDA18271_CAL_PLL_NB_ROWS_C2_Askey			    35			//
#define	TDA18271_MAIN_PLL_NB_ROWS_C2_Askey			40			//



#define	TDA18271_THERMOMETER_NB_COLUMNS_C2_Askey		 3			//
#define	TDA18271_THERMOMETER_NB_ROWS_C2_Askey		     16			//

#define	TDA18271_IDENTITY_IND_C2_Askey				 0			//

#define OM5770C2_BOARD_DEF_C2_Askey					 0x57700002 // TDA8295C1 + TDA10046 + TDA18271
#define OM5775_BOARD_DEF_C2_Askey					     0x57750000 // 2xTDA8290C1 + 2xTDA10048 + 2xTDA18271

#define OM5776_BOARD_DEF_C2_Askey					     0x57760000 //
#define OM5777_BOARD_DEF_C2_Askey					     0x57770000 //
#define OM5780_BOARD_DEF_C2_Askey					     0x57800000 //
#define OM5782_BOARD_DEF_C2_Askey					     0x57820000 //
#define OM5764_BOARD_DEF_C2_Askey					     0x57640199 //
#define CUSTOM_BOARD_DEF_C2_Askey					     0x00000000 // custom
#define OM57XX_STANDARD_DEF_C2_Askey					 2

#define RF_CAL_IF_FREQ_C2_Askey                        1000000

// types
typedef char			Int8;      /*  8 bit unsigned integer */
typedef long			Int32;      /* 32 bit integer */
typedef unsigned long   UInt32;     /* 32 bit unsigned integer */
typedef unsigned short  UInt16;     /* 16 bit unsigned integer */
typedef unsigned char   UInt8;      /*  8 bit unsigned integer */
typedef UInt32 			tmErrorCode_t;
typedef unsigned int    Bool_;       /* Boolean (True/False) */
typedef int 			tmUnitSelect_t, *ptmUnitSelect_t; 
#define NULL			0

#define TM_OK                     			0U         /* Global success return status   */
#define TM_FALSE        					0
#define TM_TRUE         					1

#define True TM_TRUE
#define False TM_FALSE 
#define OM5770C2_BOARD_DEF					0x57700002  //
#define OM5775_BOARD_DEF					0x57750000  //
#define OM5776_BOARD_DEF					0x57760000  //
#define OM5777_BOARD_DEF					0x57770000  //
#define OM5780_BOARD_DEF					0x57800000  //
#define OM5782_BOARD_DEF					0x57820000  //
#define OM5764_BOARD_DEF					0x57640199  //
#define CUSTOM_BOARD_DEF					0x00000000  // custom
#define OM57XX_STANDARD_DEF					2


    typedef enum _tmTDA18271cfgIndex_t_C2_Askey {
        BOARD_C2_Askey = 0,
        STANDARD_C2_Askey = 1,
        FEINIT_C2_Askey = 100,
        IDENTITY_C2_Askey = 102,
        GETNBOFUNIT_C2_Askey = 200,
        BANDWIDTH_C2_Askey = 300,
        RFBAND_C2_Askey = 302,
        RF_C2_Askey,
        ID_C2_Askey,
        POR_C2_Askey,
        MAINLOCK_C2_Askey,
        PLRFAGC_C2_Askey = 310,
        POWERSTATE_C2_Askey = 312,
        PLRUN_C2_Askey = 350,
        TMVALUE_C2_Askey,
        PLMODE_C2_Askey,
        PLAGC1_C2_Askey,
        PLAGC2_C2_Askey,
        RFCALOK_C2_Askey,
        IRCALOK_C2_Askey,
        BPFILTER_C2_Askey,
        GAINTAPER_C2_Askey,
        LPFC_C2_Askey,
		FMRFN_C2_Askey,
        XTOUT_C2_Askey,
        IFLEVEL_C2_Askey,
        EXTENDEDREG_C2_Askey,
        CALPOSTDIV_C2_Askey,
        CALDIV_C2_Askey,
        MAINPOSTDIV_C2_Askey,
        MAINDIV_C2_Askey,
        MAPNAME_C2_Askey,
        MAPCOLUMN_C2_Askey,
        MAPROW_C2_Askey,
        MAPVALUE_C2_Askey,
        READINIT_C2_Askey,
        RFCAL_TCOMP_C2_Askey,
        STATUSBYTE_C2_Askey = 380,
        PROTOCOLWAIT_C2_Askey = 382,
        STANDARDMODE_C2_Askey = 400,
        IF_C2_Askey = 517,
        PROTOCOLSTEP_C2_Askey,
    } tmTDA18271cfgIndex_t_C2_Askey;

    typedef enum _tmTDA18271PowerState_t_C2_Askey {
        tmPowerNormalMode_C2_Askey,						// Device normal mode
        tmPowerSleepMode_C2_Askey,						// Device sleep mode
        tmPowerStandbyWith16MHz_C2_Askey,				    // Device standby with 16Mhz
        tmPowerStandbyWith16MHzAndLoopThrough_C2_Askey,	// Device standby with 16Mhz and loop through
        tmPowerStandbyWithLoopThrough_C2_Askey,			// Device standby with loop through
        tmPowerNotSupported_C2_Askey,					    // Not supported power mode
    } tmTDA18271PowerState_t_C2_Askey, *ptmTDA18271PowerState_t_C2_Askey;

    typedef enum _tmTDA18271StandardMode_t_C2_Askey {
        tmDigital_TV_ATSC_6MHz_C2_Askey,					// Digital TV ATSC 6MHz
        tmDigital_TV_DVBT_7MHz_C2_Askey,					// Digital TV DVB-T 7MHz
        tmDigital_TV_DVBT_8MHz_C2_Askey,					// Digital TV DVB-T 8MHz
		tmAnalog_TV_MN_C2_Askey,							// Analog TV M/N
		tmAnalog_TV_B_C2_Askey,							// Analog TV B
		tmAnalog_TV_GH_C2_Askey,							// Analog TV G/H
		tmAnalog_TV_I_C2_Askey,							// Analog TV I
		tmAnalog_TV_DK_C2_Askey,							// Analog TV D/K
		tmAnalog_TV_L_C2_Askey,							// Analog TV L
		tmAnalog_TV_LL_C2_Askey,							// Analog TV L'
		tmAnalog_FM_Radio_C2_Askey,						// Analog FM Radio
        tmDigital_CAL_C2_Askey,							// Digital CAL mode
        tmDigital_TV_QAM_6MHz_C2_Askey,					// Digital TV QAM 6MHz
        tmDigital_TV_QAM_8MHz_C2_Askey,					// Digital TV QAM 8MHz
        tmDigital_TV_ISDBT_6MHz_C2_Askey,				    // Digital TV ISDBT 6MHz
        tmStandardNotSupported_C2_Askey,					// Not supported standard
    }tmTDA18271StandardMode_t_C2_Askey, *ptmTDA18271StandardMode_t_C2_Askey;
// added
// system function
Bool_    SY_Write_C2_Askey(UInt32  uAddress,
                 UInt32  uSubAddress,
                 UInt32  uNbData,
                 UInt32* pDataBuff);
                 
Bool_    SY_Read_C2_Askey(UInt32  uAddress,
                UInt32  uSubAddress,
                UInt32  uNbData,
                UInt32* pDataBuff);

Bool_    SY_Write_Slave_C2_Askey(UInt32  uAddress,
                 UInt32  uSubAddress,
                 UInt32  uNbData,
                 UInt32* pDataBuff);
                 
Bool_    SY_Read_Slave_C2_Askey(UInt32  uAddress,
                UInt32  uSubAddress,
                UInt32  uNbData,
                UInt32* pDataBuff);

typedef struct _tmhalFEBslSystemFunc_t_C2_Askey
{
        Bool_    (*SY_Write_C2_Askey)     	(UInt32  uAddress,
                                 	 UInt32  uSubAddress,
                                 	 UInt32  uNbData,
                                 	 UInt32* pDataBuff);
        Bool_    (*SY_Read_C2_Askey)       (UInt32  uAddress,
                                 	 UInt32  uSubAddress,
                                 	 UInt32  uNbData,
                                 	 UInt32* pDataBuff);
		UInt32	(*SY_GetTickPeriod)	(void);
		UInt32	(*SY_GetTickTime)	(void);

} tmhalFEBslSystemFunc_t_C2_Askey, *ptmhalFEBslSystemFunc_t_C2_Askey;

typedef struct _tmbslTuParam_t_C2_Askey
{
      unsigned long         	    uHwAddress;
      tmhalFEBslSystemFunc_t_C2_Askey  	systemFunc;    
} tmbslTuParam_t_C2_Askey, *ptmbslTuParam_t_C2_Askey; 

typedef struct tmSWVersion_C2_Askey
{
    UInt32      compatibilityNr;        /* Interface compatibility number */
    UInt32      majorVersionNr;         /* Interface major version number */
    UInt32      minorVersionNr;         /* Interface minor version number */

} tmSWVersion_t_C2_Askey, *ptmSWVersion_t_C2_Askey; 

// added

    typedef enum _tmTDA18271MapName_t_C2_Askey {
        tmTDA18271_IR_MEAS_Map_C2_Askey,					// Image rejection measurement map
        tmTDA18271_IR_CAL_Map_C2_Askey,					// Image rejection calibration map
        tmTDA18271_BP_FILTER_Map_C2_Askey,				// Band pass filter map
        tmTDA18271_RF_BAND_Map_C2_Askey,					// RF band map
        tmTDA18271_GAIN_TAPER_Map_C2_Askey,				// Gain tapper map
        tmTDA18271_RF_CAL_Map_C2_Askey,					// RF calibration map
        tmTDA18271_RF_CAL_DC_OVER_DT_Map_C2_Askey,		// RF calibration temperature adjustment map
        tmTDA18271_RF_CAL_KMCO_Map_C2_Askey,				// RF calibration K,M,COAmpl map
        tmTDA18271_RF_CAL_CID_TARGET_Map_C2_Askey,		// RF calibration CID target map
        tmTDA18271_THERMOMETER_Map_C2_Askey,				// Thermometer map
        tmTDA18271_CAL_PLL_Map_C2_Askey,					// Calibration PLL map
        tmTDA18271_MAIN_PLL_Map_C2_Askey,				    // Main PLL map
        tmTDA18271_I2C_Map_C2_Askey,						// I2C map
    } tmTDA18271MapName_t_C2_Askey, *ptmTDA18271MapName_t_C2_Askey;

    typedef struct _tmTDA18271_IR_MEAS_Map_t_C2_Askey {
        UInt32 uRF_Max;
        UInt32 uIR_Meas;
    } tmTDA18271_IR_MEAS_Map_t_C2_Askey, *ptmTDA18271_IR_MEAS_Map_t_C2_Askey;

    typedef struct _tmTDA18271_IR_CAL_Map_t_C2_Askey {
        UInt32 uRF;
        UInt32 uIR_GStep;
    } tmTDA18271_IR_CAL_Map_t_C2_Askey, *ptmTDA18271_IR_CAL_Map_t_C2_Askey;

    typedef struct _tmTDA18271_BP_FILTER_Map_t_C2_Askey {
        UInt32 uRF_Max;
        UInt32 uBP_Filter;
    } tmTDA18271_BP_FILTER_Map_t_C2_Askey, *ptmTDA18271_BP_FILTER_Map_t_C2_Askey;

    typedef struct _tmTDA18271_RF_BAND_Map_t_C2_Askey {
        UInt32 uRF_Max;
        UInt32 uRF_Band;
        UInt32 uRF1;
        UInt32 uRF2;
        UInt32 uRF3;
        Int32 uRF_A1;
        Int32 uRF_B1;
        Int32 uRF_A2;
        Int32 uRF_B2;
        UInt32 uRF1_default;
        UInt32 uRF2_default;
        UInt32 uRF3_default;
    } tmTDA18271_RF_BAND_Map_t_C2_Askey, *ptmTDA18271_RF_BAND_Map_t_C2_Askey;

    typedef struct _tmTDA18271_GAIN_TAPER_Map_t_C2_Askey {
        UInt32 uRF_Max;
        UInt32 uGain_Taper;
    } tmTDA18271_GAIN_TAPER_Map_t_C2_Askey, *ptmTDA18271_GAIN_TAPER_Map_t_C2_Askey;

    typedef struct _tmTDA18271_RF_CAL_Map_t_C2_Askey {
        UInt32 uRF_Max;
        UInt32 uRFC_Cprog;
    } tmTDA18271_RF_CAL_Map_t_C2_Askey, *ptmTDA18271_RF_CAL_Map_t_C2_Askey;

    typedef struct _tmTDA18271_RF_CAL_DC_OVER_DT_Map_t_C2_Askey {
        UInt32 uRF_Max;
        UInt32 udC_Over_dT;
    } tmTDA18271_RF_CAL_DC_OVER_DT_Map_t_C2_Askey, *ptmTDA18271_RF_CAL_DC_OVER_DT_Map_t_C2_Askey;

    typedef struct _tmTDA18271_RF_CAL_KMCO_Map_t_C2_Askey {
        UInt32 uRF_Max;
        UInt32 uK;
        UInt32 uM;
        UInt32 uCOAmpl;
    } tmTDA18271_RF_CAL_KMCO_Map_t_C2_Askey, *ptmTDA18271_RF_CAL_KMCO_Map_t_C2_Askey;

    typedef struct _tmTDA18271_RF_CAL_CID_TARGET_Map_t_C2_Askey {
        UInt32 uRF_Max;
        UInt32 uCID_Target;
        UInt32 uCount_Limit;
    } tmTDA18271_RF_CAL_CID_TARGET_Map_t_C2_Askey, *ptmTDA18271_RF_CAL_CID_TARGET_Map_t_C2_Askey;

    typedef struct _tmTDA18271_THERMOMETER_Map_t_C2_Askey {
        UInt32 uTM_D;
        UInt32 uTM_60_92;
        UInt32 uTM_92_122;
    } tmTDA18271_THERMOMETER_Map_t_C2_Askey, *ptmTDA18271_THERMOMETER_Map_t_C2_Askey;

    typedef struct _tmTDA18271_PLL_Map_t_C2_Askey {
        UInt32 uLO_Max;
        UInt32 uPost_Div;
        UInt32 uDiv;
    } tmTDA18271_PLL_Map_t_C2_Askey, *ptmTDA18271_PLL_Map_t_C2_Askey;

    typedef struct _tmTDA18271Config_t_C2_Askey {
        UInt32								    uBoard;
        UInt32								    uStandard;
        UInt32								    uRF;
        UInt32								    uIF;
        //UInt32							    uBW;
        UInt32								    uTMVALUE_RFCAL;
        UInt32								    uPLMODE;
        Int32								    uRFCAL_TCOMP;
        UInt32								    uMAPNAME;
        UInt32								    uMAPCOLUMN;
        UInt32								    uMAPROW;
        UInt32								    uPROTOCOLSTEP;
        tmTDA18271_IR_MEAS_Map_t_C2_Askey			    IR_MEAS_Map[TDA18271_IR_MEAS_NB_ROWS_C2_Askey];
        tmTDA18271_IR_CAL_Map_t_C2_Askey			    IR_CAL_Map[TDA18271_IR_CAL_NB_ROWS_C2_Askey];
        tmTDA18271_BP_FILTER_Map_t_C2_Askey		    BP_FILTER_Map[TDA18271_BP_FILTER_NB_ROWS_C2_Askey];
        tmTDA18271_RF_BAND_Map_t_C2_Askey			    RF_BAND_Map[TDA18271_RF_BAND_NB_ROWS_C2_Askey];
        tmTDA18271_GAIN_TAPER_Map_t_C2_Askey			GAIN_TAPER_Map[TDA18271_GAIN_TAPER_NB_ROWS_C2_Askey];
        tmTDA18271_RF_CAL_Map_t_C2_Askey				RF_CAL_Map[TDA18271_RF_CAL_NB_ROWS_C2_Askey];
        tmTDA18271_RF_CAL_DC_OVER_DT_Map_t_C2_Askey	RF_CAL_DC_OVER_DT_Map[TDA18271_RF_CAL_DC_OVER_DT_NB_ROWS_C2_Askey];
        tmTDA18271_RF_CAL_KMCO_Map_t_C2_Askey		    RF_CAL_KMCO_Map[TDA18271_RF_CAL_KMCO_NB_ROWS_C2_Askey];
        tmTDA18271_RF_CAL_CID_TARGET_Map_t_C2_Askey	RF_CAL_CID_TARGET_Map[TDA18271_RF_CAL_CID_TARGET_NB_ROWS_C2_Askey];
        tmTDA18271_THERMOMETER_Map_t_C2_Askey		    THERMOMETER_Map[TDA18271_THERMOMETER_NB_ROWS_C2_Askey];
        tmTDA18271_PLL_Map_t_C2_Askey				    CAL_PLL_Map[TDA18271_CAL_PLL_NB_ROWS_C2_Askey];
        tmTDA18271_PLL_Map_t_C2_Askey				    MAIN_PLL_Map[TDA18271_MAIN_PLL_NB_ROWS_C2_Askey];
    } tmTDA18271Config_t_C2_Askey, *ptmTDA18271Config_t_C2_Askey;

    typedef struct _tmTDA18271I2CMap_t_C2_Askey									
    {									
        union								
        {								
            UInt8 ID_BYTE;				// address 0x00			
            // Chip identification byte
            struct							
            {							
                UInt8 ID			:7;	// Chip identification number		
                UInt8 UNUSED		:1;	// Reserved, must be written as 1				
            }bF;							
        }uBx00;

        union								
        {								
            UInt8 THERMO_BYTE;			// address 0x01				
            // Thermometer byte
            struct							
            {							
                UInt8 TM_D			:4;	// Data from die temperature measurement 		
                UInt8 TM_ON			:1;	// Enable Die temperature measurement		
                UInt8 TM_Range		:1;	// Range selection bit for the internal die sensor			
                // 0: 60 to 92°C
                // 1: 92 to 122°C
                UInt8 MAIN_Lock		:1;	// Indicate that the MAIN synthesizer is locked to the programmed frequency			
                // 0: Not Locked
                // 1: Locked
                UInt8 POR			:1;	// Power on reset bit		
                // This bit is set to 1 each time the power supply falls below a certain level (around 1.4V) and is reset after a read operation ending with a stop condition
            }bF;							
        }uBx01;

        union								
        {								
            UInt8 POWER_LEVEL_BYTE;		// address 0x02					
            // Power level byte
            struct							
            {							
                UInt8 Power_Level_7_to_0:8;// Power level indicator value						
            }bF;							
        }uBx02;

        union								
        {								
            UInt8 EASY_PROG_BYTE_1;		// address 0x03					
            // Easy programming byte 1
            struct							
            {							
                UInt8 BP_Filter		:3;	// RF band-pass filter selection (H3/H5) 			
                UInt8 IR_CAL_OK		:1;	// Indicate that the 3 Image rejection calibration procedure  (Flow, Fmid, Fhigh) have been successful			
                UInt8 RF_CAL_OK		:1;	// Indicate that the RF tracking filter calibration procedure has been successful			
                UInt8 UNUSED		:1;	// Reserved				
                UInt8 Dis_Power_level:1;// Disable power level measurement						
                // 0: Power measurement valid
                // 1: Power measurement not guaranted
                UInt8 Power_Level_8	:1;	// Power level indicator value				
            }bF;							
        }uBx03;

        union								
        {								
            UInt8 EASY_PROG_BYTE_2;		// address 0x04					
            // Easy programming byte 2 
            struct							
            {							
                UInt8 Gain_Taper	:5;	// Gain taper value				
                // 0  : max atten. (end of Band)
                // 31: min atten. (start of Band)
                UInt8 RF_Band		:3;	// RF tracking filter band and sub-band selection			
            }bF;							
        }uBx04;

        union								
        {								
            UInt8 EASY_PROG_BYTE_3;		// address 0x05					
            // Easy programming byte 3 
            struct							
            {							
                UInt8 Std			:5;	// Standard selection		
                UInt8 SM_XT			:1;	// XTAL output sleep mode		
                UInt8 SM_LT			:1;	// Loop through sleep mode		
                UInt8 SM			:1;	// General sleep mode		
            }bF;
        }uBx05;

        union								
        {								
            UInt8 EASY_PROG_BYTE_4;		// address 0x06					
            // Easy programming byte 4 
            struct							
            {							
                UInt8 CAL_Mode		:2;	// calibration mode selection			
                UInt8 IF_Level		:3;	// IF output level selection			
                UInt8 Xtout_400mV	:1;	// XTAL output level optional selection
                UInt8 XTout_ON		:1;	// Enable 16MHz on XTAL output			
                UInt8 FM_RFn		:1;	// FM or RF input selection			
            }bF;							
        }uBx06;

        union								
        {								
            UInt8 EASY_PROG_BYTE_5;		// address 0x07					
            // Easy programming byte 5
            struct							
            {							
                UInt8 IR_Meas		:3;	// Image rejection measurement mode			
                UInt8 I2C_Xtout_Asym:1;	// Reserved
                UInt8 IR_Gstep		:3;	// Gain step for image rejection measurement. Depends on frequency			
                UInt8 Extended_Reg	:1;	// Enable the extended byte addressing				
                // 0: Limited byte (&h00:&h0F)
                // 1: Extended byte (&h00:&h26)
            }bF;							
        }uBx07;

        union									
        {									
            UInt8 CAL_POST_DIV_BYTE;	// address 0x08							
            // CAL post divider byte		
            struct							
            {							
                UInt8 CALPostDiv	:7;	// CAL post divider			
                UInt8 RUF_0			:1;	// Reserved
            }bF;
        }uBx08;

        union									
        {									
            UInt8 CAL_DIV_BYTE_1;		// address 0x09						
            // CAL divider byte	1
            struct								
            {								
                UInt8 CAL_Div_22_to_16:7;// CAL divider value 22 to 16							
                UInt8 RUF_1			:1;	// Reserved
            }bF;							
        }uBx09;

        union									
        {									
            UInt8 CAL_DIV_BYTE_2;		// address 0x0A						
            // CAL divider byte	2
            struct								
            {								
                UInt8 CAL_Div_15_to_8:8;// CAL divider value 15 to 8							
            }bF;							
        }uBx0A;

        union									
        {									
            UInt8 CAL_DIV_BYTE_3;		// address 0x0B						
            // CAL divider byte	3
            struct								
            {								
                UInt8 CAL_Div_7_to_0:8;	// CAL divider value 7 to 0						
            }bF;							
        }uBx0B;

        union									
        {									
            UInt8 MAIN_POST_DIV_BYTE;	// address 0x0C							
            // MAIN post divider byte 	
            struct								
            {							
                UInt8 MAIN_Post_Div	:7;	// MAIN post divider value
                UInt8 IF_notch	:1;	// Reserved
            }bF;							
        }uBx0C;

        union								
        {								
            UInt8 MAIN_DIV_BYTE_1;		// address 0x0D					
            // MAIN divider byte 1
            struct							
            {							
                UInt8 MAIN_Div_22_to_16:7;// MAIN divider value 22 to 16						
                UInt8 RUF_2			:1;	// Reserved				
            }bF;							
        }uBx0D;

        union								
        {								
            UInt8 MAIN_DIV_BYTE_2;		// address 0x0E					
            // MAIN divider byte 2
            struct							
            {							
                UInt8 MAIN_Div_15_to_8:8;// MAIN divider value 15 to 8						
            }bF;							
        }uBx0E;

        union								
        {								
            UInt8 MAIN_DIV_BYTE_3;		// address 0x0F					
            // MAIN divider byte 3
            struct							
            {							
                UInt8 MAIN_Div_7_to_0:8;// MAIN divider value 7 to 0						
            }bF;							
        }uBx0F;

        union								
        {								
            UInt8 EXTENDED_BYTE_1;		// address 0x10					
            // extended byte 1
            struct							
            {							
                UInt8 AGC1_firstn	:1;	// 
                UInt8 AGC1_always_mastern:1;// 
                UInt8 CALVCO_forLOn	:1;	//
                UInt8 UNUSED		:1;	// Reserved		
            }bF;
        }uBx10;	


        union								
        {								
            UInt8 EXTENDED_BYTE_2;		// address 0x11					
        }uBx11;							// extended byte 2


        union								
        {								
            UInt8 EXTENDED_BYTE_3;		// address 0x12					
        }uBx12;							// extended byte 3


        union								
        {								
            UInt8 EXTENDED_BYTE_4;		// address 0x13					
            // extended byte 4
            struct
            {			
                UInt8 UNUSED_1		:5;	// Reserved
                UInt8 LO_ForceSrce	:1;	// 
                UInt8 UNUSED_2		:2;	// Reserved	
            }bF;
        }uBx13;	

        union								
        {								
            UInt8 EXTENDED_BYTE_5;		// address 0x14					
        }uBx14;							// extended byte 5

        union								
        {								
            UInt8 EXTENDED_BYTE_6;		// address 0x15					
        }uBx15;							// extended byte 6

        union								
        {								
            UInt8 EXTENDED_BYTE_7;		// address 0x16					
            // extended byte 7
            struct
            {			
                UInt8 CAL_Lock		:1;
                UInt8 UNUSED_1		:4;	// Reserved
                UInt8 CAL_ForceSrce	:1;	// 
                UInt8 UNUSED_2		:2;	// Reserved	
            }bF;
        }uBx16;	

        union								
        {								
            UInt8 EXTENDED_BYTE_8;		// address 0x17					
            // extended byte 8
            struct
            {			
                UInt8 UNUSED		:7;	// Reserved
                UInt8 CID_Alarm		:1;	//			
            }bF;
        }uBx17;

        union								
        {								
            UInt8 EXTENDED_BYTE_9;		// address 0x18					
        }uBx18;							// extended byte 9

        union								
        {								
            UInt8 EXTENDED_BYTE_10;		// address 0x19					
            // extended byte 10
            struct
            {			
                UInt8 CID_Gain		:6;	// 
                UInt8 UNUSED		:2;	// Reserved
            }bF;
        }uBx19;

        union								
        {								
            UInt8 EXTENDED_BYTE_11;		// address 0x1A					
        }uBx1A;							// extended byte 11

        union								
        {								
            UInt8 EXTENDED_BYTE_12;		// address 0x1B					
            // extended byte 12
            struct
            {			
                UInt8 UNUSED_1		:4;	// Reserved
                UInt8 PD_AGC2_Det	:1;	// 
                UInt8 PD_AGC1_Det	:1;	// 
                UInt8 UNUSED_2		:2;	// Reserved
            }bF;
        }uBx1B;

        union								
        {								
            UInt8 EXTENDED_BYTE_13;		// address 0x1C					
            // extended byte 13
            struct
            {			
                UInt8 UNUSED_1		:2;	// Reserved
                UInt8 RFC_M			:2;	// 
                UInt8 RFC_K			:3;	// 
                UInt8 UNUSED_2		:1;	// Reserved
            }bF;
        }uBx1C;

        union								
        {								
            UInt8 EXTENDED_BYTE_14;		// address 0x1D					
            // extended byte 14
            UInt8 RFC_Cprog;
        }uBx1D;

        union								
        {								
            UInt8 EXTENDED_BYTE_15;		// address 0x1E					
        }uBx1E;							// extended byte 15

        union								
        {								
            UInt8 EXTENDED_BYTE_16;		// address 0x1F					
        }uBx1F;							// extended byte 16

        union								
        {								
            UInt8 EXTENDED_BYTE_17;		// address 0x20					
        }uBx20;							// extended byte 17

        union								
        {								
            UInt8 EXTENDED_BYTE_18;		// address 0x21					
            // extended byte 18
            struct							
            {			
                UInt8 AGC1_Gain		:2;	// 
                UInt8 UNUSED		:5;	// Reserved
                UInt8 AGC1_loop_off	:1;	//
            }bF;
        }uBx21;	

        union								
        {								
            UInt8 EXTENDED_BYTE_19;		// address 0x22					
        }uBx22;							// extended byte 19

        union								
        {								
            UInt8 EXTENDED_BYTE_20;		// address 0x23					
            // extended byte 20
            struct							
            {			
                UInt8 UNUSED_1		:5;	// Reserved 
                UInt8 Force_Lock	:1;	// 
                UInt8 UNUSED_2		:2;	// Reserved
            }bF;
        }uBx23;

        union								
        {								
            UInt8 EXTENDED_BYTE_21;		// address 0x24					
            // extended byte 21
            struct							
            {			
                UInt8 AGC2_Gain		:2;	// 
                UInt8 UNUSED		:5;	// Reserved
                UInt8 AGC2_loop_off	:1;	//
            }bF;
        }uBx24;	

        union								
        {								
            UInt8 EXTENDED_BYTE_22;		// address 0x25					
        }uBx25;							// extended byte 22

        union								
        {								
            UInt8 EXTENDED_BYTE_23;		// address 0x26					
            // extended byte 23
            struct							
            {			
                UInt8 UNUSED_1		:1;	// Reserved
                UInt8 LP_Fc			:1;	// 
                UInt8 ForceLP_Fc2_En:1;	// 
                UInt8 UNUSED_2		:3;	// Reserved
                UInt8 FM_LNAGain		:2;	//
            }bF;
        }uBx26;	

    } tmTDA18271I2CMap_t_C2_Askey, *ptmTDA18271I2CMap_t_C2_Askey;									

typedef struct _tmAFAInfo_t_C2_Askey {
    Demodulator*				demodulator;
    UInt8						chip;
} tmAFAInfo_t_C2_Askey, *ptmAFAInfo_t_C2_Askey;

typedef struct _tmTDA18271Object_t_C2_Askey {
	tmAFAInfo_t_C2_Askey		    	AFAInfo_C2_Askey;
    tmUnitSelect_t			    TunerUnit;
	Bool_						init;
    UInt32						uHwAddress;
/*#ifdef NXPFE
    tmdlDefaultGCRoot<tmdlDefaultDeviceDriver::tmhalFEBslSystemFunc_c^>	SystemFunc;
#else*/
    tmhalFEBslSystemFunc_t_C2_Askey	SystemFunc;
//#endif
    tmTDA18271PowerState_t_C2_Askey	curPowerState;
    tmTDA18271StandardMode_t_C2_Askey	StandardMode;
    tmTDA18271Config_t_C2_Askey		Config;
    tmTDA18271I2CMap_t_C2_Askey		I2CMap;
    UInt32						I2CLog[TDA18271_LOG_NB_ROWS_C2_Askey][TDA18271_NB_BYTES_C2_Askey + 2];
    UInt32						uTickEnd;
} tmTDA18271Object_t_C2_Askey, *ptmTDA18271Object_t_C2_Askey, **pptmTDA18271Object_t_C2_Askey;

    typedef struct _tmTDA18271VbI2CData_t_C2_Askey {
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
        UInt32	h10;	
        UInt32	h11;	
        UInt32	h12;
        UInt32	h13;
        UInt32	h14;	
        UInt32	h15;	
        UInt32	h16;	
        UInt32	h17;	
        UInt32	h18;	
        UInt32	h19;	
        UInt32	h1A;
        UInt32	h1B;
        UInt32	h1C;
        UInt32	h1D;
        UInt32	h1E;
        UInt32	h1F;
        UInt32	h20;	
        UInt32	h21;	
        UInt32	h22;
        UInt32	h23;
        UInt32	h24;	
        UInt32	h25;	
        UInt32	h26;	
        UInt32	I2CAddress;
        UInt32	I2CCommResult;
    } tmTDA18271VbI2CData_t_C2_Askey, *ptmTDA18271VbI2CData_t_C2_Askey;

//-----------------------------------------------------------------------------
// Function:
//-----------------------------------------------------------------------------
//
    Bool_
        TDA18271Wrapper_C2_Askey (
        ptmTDA18271Object_t_C2_Askey	pObj,				//  I: Tuner unit number
        UInt32					uHwAddress,			//  I: Tuner unit I2C address
        UInt32					uLptPort,			//  I: I2C interface LPT port
        UInt32					uI2cSpeed,			//  I: I2C interface speed
        char*					uParamTunerNumber	//  I: Tuner unit number
        );

    Bool_
        TDA18271WrapperClose_C2_Askey();

//#ifndef NXPFE
#ifdef __cplusplus
}
#endif
//#endif //NXPFE

#endif // _TMBSL_TDA18271LOCAL_H_C2_Askey //---------------
