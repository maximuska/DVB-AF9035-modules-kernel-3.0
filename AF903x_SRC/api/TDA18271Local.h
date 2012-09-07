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
#ifndef _TMBSL_TDA18271LOCAL_H //-----------------
#define _TMBSL_TDA18271LOCAL_H

#include "type.h"

//-----------------------------------------------------------------------------
// Standard include files:
//-----------------------------------------------------------------------------
//#include "dvp.h"
//#include "tmbslTuner.h"
//-----------------------------------------------------------------------------
// Project include files:
//-----------------------------------------------------------------------------
//
#ifdef __cplusplus
extern "C"
{
#endif

//-----------------------------------------------------------------------------
// Types and defines:
//-----------------------------------------------------------------------------
// 
#define TDA18271_BSL_COMP_NUM    1
#define TDA18271_BSL_MAJOR_VER   8
#define TDA18271_BSL_MINOR_VER   3
//-------------
// ERROR CODES    
//-------------
#define TMBSL_ERR_TUNER_BASE	0x80000000U
#define TM_ERR_BAD_UNIT_NUMBER	0x00000001U
#define TM_ERR_NOT_INITIALIZED	0x00000002U
#define TM_ERR_BAD_PARAMETER	0x00000003U
#define TM_ERR_NOT_SUPPORTED	0x00000004U
#define TM_ERR_IIC_ERR			0x00000005U

// Invalid unit id
#define TMBSL_ERR_TUNER_BAD_UNIT_NUMBER \
(TMBSL_ERR_TUNER_BASE + TM_ERR_BAD_UNIT_NUMBER)

// Component is not initialized
#define TMBSL_ERR_TUNER_NOT_INITIALIZED \
(TMBSL_ERR_TUNER_BASE+ TM_ERR_NOT_INITIALIZED)

// Invalid input parameter
#define TMBSL_ERR_TUNER_BAD_PARAMETER \
(TMBSL_ERR_TUNER_BASE + TM_ERR_BAD_PARAMETER)

// Function is not supported
#define TMBSL_ERR_TUNER_NOT_SUPPORTED \
(TMBSL_ERR_TUNER_BASE + TM_ERR_NOT_SUPPORTED)

// Function is not supported
#define TMBSL_ERR_IIC_ERR \
(TMBSL_ERR_TUNER_BASE + TM_ERR_IIC_ERR)

#define TDA18271_MAX_UNITS					10			//
#define TDA18271_NB_BYTES					39			//
#define TDA18271_LOG_NB_ROWS				50			//

#define	TDA18271_IR_MEAS_NB_COLUMNS			1			//
#define	TDA18271_IR_MEAS_NB_ROWS			4			//

#define	TDA18271_IR_CAL_NB_COLUMNS			2			//
#define	TDA18271_IR_CAL_NB_ROWS				3			//

#define	TDA18271_BP_FILTER_NB_COLUMNS		2			//
#define	TDA18271_BP_FILTER_NB_ROWS			7			//

#define	TDA18271_RF_BAND_NB_COLUMNS			2			//
#define	TDA18271_RF_BAND_NB_ROWS			7			//

#define	TDA18271_GAIN_TAPER_NB_COLUMNS		2			//
#define	TDA18271_GAIN_TAPER_NB_ROWS			85			//

#define	TDA18271_RF_CAL_NB_COLUMNS			2			//
#define	TDA18271_RF_CAL_NB_ROWS				17			//

#define	TDA18271_RF_CAL_KMCO_NB_COLUMNS		4			//
#define	TDA18271_RF_CAL_KMCO_NB_ROWS		4			//

#define	TDA18271_THERMOMETER_NB_COLUMNS		3			//
#define	TDA18271_THERMOMETER_NB_ROWS		16			//

#define	TDA18271_CAL_PLL_NB_COLUMNS			3			//
#define	TDA18271_CAL_PLL_NB_ROWS			35			//

#define	TDA18271_MAIN_PLL_NB_COLUMNS		3			//
#define	TDA18271_MAIN_PLL_NB_ROWS			40			//

#define	TDA18271_IDENTITY_IND				0			//

#define OM5770C2_BOARD_DEF					0x57700002  // TDA8295C1 + TDA10046 + TDA18271
#define OM5775_BOARD_DEF					0x57750000  // 2xTDA8290C1 + 2xTDA10048 + 2xTDA18271
#define OM5776_BOARD_DEF					0x57760000  //
#define OM5777_BOARD_DEF					0x57770000  //
#define OM5780_BOARD_DEF					0x57800000  //
#define OM5782_BOARD_DEF					0x57820000  //
#define OM5764_BOARD_DEF					0x57640199  //
#define CUSTOM_BOARD_DEF					0x00000000  // custom
#define OM57XX_STANDARD_DEF					2


// types
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

// added
// system function
Bool_    SY_Write(UInt32  uAddress,
                 UInt32  uSubAddress,
                 UInt32  uNbData,
                 UInt32* pDataBuff);
                 
Bool_    SY_Read(UInt32  uAddress,
                UInt32  uSubAddress,
                UInt32  uNbData,
                UInt32* pDataBuff);

Bool_    SY_Write_Slave(UInt32  uAddress,
                 UInt32  uSubAddress,
                 UInt32  uNbData,
                 UInt32* pDataBuff);
                 
Bool_    SY_Read_Slave(UInt32  uAddress,
                UInt32  uSubAddress,
                UInt32  uNbData,
                UInt32* pDataBuff);

typedef struct _tmhalFEBslSystemFunc_t
{
        Bool_    (*SY_Write)     	(UInt32  uAddress,
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
      unsigned long         	uHwAddress;
      tmhalFEBslSystemFunc_t  	systemFunc;    
} tmbslTuParam_t, *ptmbslTuParam_t; 

typedef struct tmSWVersion
{
    UInt32      compatibilityNr;        /* Interface compatibility number */
    UInt32      majorVersionNr;         /* Interface major version number */
    UInt32      minorVersionNr;         /* Interface minor version number */

} tmSWVersion_t, *ptmSWVersion_t; 

// added

typedef enum _tmTDA18271cfgIndex_t {
    BOARD = 0,
	STANDARD = 1,
    FEINIT = 100,
    IDENTITY = 102,
    GETNBOFUNIT = 200,
	BANDWIDTH = 300,
	RFBAND = 302,
	RF,
	ID,
	POR,
	MAINLOCK,
	PLRFAGC = 310,
	POWERSTATE = 312,
	TMMODE = 350,
	TMVALUE,
	PLMODE,
	PLAGC1,
	PLAGC2,
	RFCALOK,
	IRCALOK,
	BPFILTER,
	GAINTAPER,
	LPFC,
	FMRFN,
	XTOUT,
	IFLEVEL,
	EXTENDEDREG,
	CALPOSTDIV,
	CALDIV,
	MAINPOSTDIV,
	MAINDIV,
	MAPNAME,
	MAPCOLUMN,
	MAPROW,
	MAPVALUE,
    READINIT,
	STATUSBYTE = 380,
	PROTOCOLSTEP,
	PROTOCOLWAIT,
	STANDARDMODE = 400,
	IF = 517
} tmTDA18271cfgIndex_t;

typedef enum _tmTDA18271PowerState_t {
    tmPowerNormalMode,						// Device normal mode
    tmPowerSleepMode,						// Device sleep mode
	tmPowerStandbyWith16MHz,				// Device standby with 16Mhz
	tmPowerStandbyWith16MHzAndLoopThrough,	// Device standby with 16Mhz and loop through
	tmPowerStandbyWithLoopThrough,			// Device standby with loop through
	tmPowerNotSupported,					// Not supported power mode
} tmTDA18271PowerState_t, *ptmTDA18271PowerState_t;

typedef enum _tmTDA18271StandardMode_t {
	tmDigital_TV_ATSC_6MHz,					// Digital TV ATSC 6MHz
	tmDigital_TV_DVBT_7MHz,					// Digital TV DVB-T 7MHz
	tmDigital_TV_DVBT_8MHz,					// Digital TV DVB-T 8MHz
	tmAnalog_TV_MN,							// Analog TV M/N
	tmAnalog_TV_B,							// Analog TV B
	tmAnalog_TV_GH,							// Analog TV G/H
	tmAnalog_TV_I,							// Analog TV I
	tmAnalog_TV_DK,							// Analog TV D/K
	tmAnalog_TV_L,							// Analog TV L
	tmAnalog_TV_LL,							// Analog TV L'
	tmAnalog_FM_Radio,						// Analog FM Radio
	tmDigital_TV_QAM_6MHz,					// Digital TV QAM 6MHz
	tmDigital_TV_QAM_8MHz,					// Digital TV QAM 8MHz
	tmStandardNotSupported,					// Not supported standard
} tmTDA18271StandardMode_t, *ptmTDA18271StandardMode_t;

typedef enum _tmTDA18271ThermometerMode_t {
    tmThermometerOff,						// Thermometer off
    tmThermometerOn,						// Thermometer on
} tmTDA18271ThermometerMode_t, *ptmTDA18271ThermometerMode_t;

typedef enum _tmTDA18271MapName_t {
	tmTDA18271_IR_MEAS_Map,					// Image rejection measurement map
	tmTDA18271_IR_CAL_Map,					// Image rejection calibration map
	tmTDA18271_BP_FILTER_Map,				// Band pass filter map
	tmTDA18271_RF_BAND_Map,					// RF band map
	tmTDA18271_GAIN_TAPER_Map,				// Gain tapper map
	tmTDA18271_RF_CAL_Map,					// RF calibration map
	tmTDA18271_RF_CAL_KMCO_Map,				// RF calibration protocol map
	tmTDA18271_THERMOMETER_Map,				// Thermometer map
	tmTDA18271_CAL_PLL_Map,					// Calibration PLL map
	tmTDA18271_MAIN_PLL_Map,				// Main PLL map
	tmTDA18271_I2C_Map,						// I2C map
} tmTDA18271MapName_t, *ptmTDA18271MapName_t;

typedef struct _tmTDA18271_IR_MEAS_Map_t {
    UInt32 uRF_Max;
} tmTDA18271_IR_MEAS_Map_t, *ptmTDA18271_IR_MEAS_Map_t;

typedef struct _tmTDA18271_IR_CAL_Map_t {
    UInt32 uRF;
	UInt32 uIR_GStep;
} tmTDA18271_IR_CAL_Map_t, *ptmTDA18271_IR_CAL_Map_t;

typedef struct _tmTDA18271_BP_FILTER_Map_t {
    UInt32 uRF_Max;
	UInt32 uBP_Filter;
} tmTDA18271_BP_FILTER_Map_t, *ptmTDA18271_BP_FILTER_Map_t;

typedef struct _tmTDA18271_RF_BAND_Map_t {
    UInt32 uRF_Max;
	UInt32 uRF_Band;
} tmTDA18271_RF_BAND_Map_t, *ptmTDA18271_RF_BAND_Map_t;

typedef struct _tmTDA18271_GAIN_TAPER_Map_t {
    UInt32 uRF_Max;
	UInt32 uGain_Taper;
} tmTDA18271_GAIN_TAPER_Map_t, *ptmTDA18271_GAIN_TAPER_Map_t;

typedef struct _tmTDA18271_RF_CAL_Map_t {
    UInt32 uRF_Max;
	UInt32 uRFC_Cprog;
} tmTDA18271_RF_CAL_Map_t, *ptmTDA18271_RF_CAL_Map_t;

typedef struct _tmTDA18271_RF_CAL_KMCO_Map_t {
    UInt32 uRF_Max;
	UInt32 uK;
	UInt32 uM;
	UInt32 uCOAmpl;
} tmTDA18271_RF_CAL_KMCO_Map_t, *ptmTDA18271_RF_CAL_KMCO_Map_t;

typedef struct _tmTDA18271_THERMOMETER_Map_t {
    UInt32 uTM_D;
	UInt32 uTM_60_92;
	UInt32 uTM_92_122;
} tmTDA18271_THERMOMETER_Map_t, *ptmTDA18271_THERMOMETER_Map_t;

typedef struct _tmTDA18271_PLL_Map_t {
    UInt32 uLO_Max;
	UInt32 uPost_Div;
	UInt32 uDiv;
} tmTDA18271_PLL_Map_t, *ptmTDA18271_PLL_Map_t;

typedef struct _tmTDA18271Config_t {
    UInt32								uBoard;
	UInt32								uStandard;
	UInt32								uRF;
	UInt32								uIF;
	UInt32								uBW;
	UInt32								uTMMODE;
	UInt32								uPLMODE;
	UInt32								uMapName;
	UInt32								uMAPCOLUMN;
	UInt32								uMAPROW;
	UInt32								uPROTOCOLSTEP;
	UInt32								uPROTOCOLWAIT;
	tmTDA18271_IR_MEAS_Map_t			IR_MEAS_Map[TDA18271_IR_MEAS_NB_ROWS];
	tmTDA18271_IR_CAL_Map_t				IR_CAL_Map[TDA18271_IR_CAL_NB_ROWS];
	tmTDA18271_BP_FILTER_Map_t			BP_FILTER_Map[TDA18271_BP_FILTER_NB_ROWS];
	tmTDA18271_RF_BAND_Map_t			RF_BAND_Map[TDA18271_RF_BAND_NB_ROWS];
	tmTDA18271_GAIN_TAPER_Map_t			GAIN_TAPER_Map[TDA18271_GAIN_TAPER_NB_ROWS];
	tmTDA18271_RF_CAL_Map_t				RF_CAL_Map[TDA18271_RF_CAL_NB_ROWS];
	tmTDA18271_RF_CAL_KMCO_Map_t		RF_CAL_KMCO_Map[TDA18271_RF_CAL_KMCO_NB_ROWS];
	tmTDA18271_THERMOMETER_Map_t		THERMOMETER_Map[TDA18271_THERMOMETER_NB_ROWS];
	tmTDA18271_PLL_Map_t				CAL_PLL_Map[TDA18271_CAL_PLL_NB_ROWS];
	tmTDA18271_PLL_Map_t				MAIN_PLL_Map[TDA18271_MAIN_PLL_NB_ROWS];
} tmTDA18271Config_t, *ptmTDA18271Config_t;

typedef struct _tmTDA18271I2CMap_t									
{									
	union								
	{								
		UInt8 ID_BYTE;				// address 0x00			
									// Chip identification byte
		struct							
		{							
		 	UInt8 ID			:7;	// Chip identification number		
			UInt8 UNUSED_0x00	:1;	// Reserved, must be written as 1				
		};							
	};								

	union								
	{								
		UInt8 THERMO_BYTE;			// address 0x01				
									// Thermometer byte
		struct							
		{							
		 	UInt8 TM_D			:4;	// Data from die temperature measurement 		
		 	UInt8 TM_ON			:1;	// Enable Die temperature measurement		
		 	UInt8 TM_Range		:1;	// Range selection bit for the internal die sensor			
									// 0: 60 to 92�C
									// 1: 92 to 122�C
		 	UInt8 MAIN_Lock		:1;	// Indicate that the MAIN synthesizer is locked to the programmed frequency			
				 					// 0: Not Locked
									// 1: Locked
			UInt8 POR			:1;	// Power on reset bit		
									// This bit is set to 1 each time the power supply falls below a certain level (around 1.4V) and is reset after a read operation ending with a stop condition
		};							
	};								

	union								
	{								
		UInt8 POWER_LEVEL_BYTE;		// address 0x02					
									// Power level byte
		struct							
		{							
			UInt8 Power_Level_7_to_0:8;// Power level indicator value						
		};							
	};								

	union								
	{								
		UInt8 EASY_PROG_BYTE_1;		// address 0x03					
									// Easy programming byte 1
		struct							
		{							
			UInt8 BP_Filter		:3;	// RF band-pass filter selection (H3/H5) 			
			UInt8 IR_CAL_OK		:1;	// Indicate that the 3 Image rejection calibration procedure  (Flow, Fmid, Fhigh) have been successful			
			UInt8 RF_CAL_OK		:1;	// Indicate that the RF tracking filter calibration procedure has been successful			
			UInt8 UNUSED_0x03	:1;	// Reserved, must be written as 0				
			UInt8 Dis_Power_level:1;// Disable power level measurement						
									// 0: Power measurement valid
									// 1: Power measurement not guaranted
			UInt8 Power_Level_8	:1;	// Power level indicator value				
		};							
	};								

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
		};							
	};								

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
		};							
	};								

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
		};							
	};								

	union								
	{								
		UInt8 EASY_PROG_BYTE_5;		// address 0x07					
									// Easy programming byte 5
		struct							
		{							
			UInt8 IR_Meas		:3;	// Image rejection measurement mode			
			UInt8 UNUSED_0x07	:1;	// Reserved, must be written as 0
			UInt8 IR_Gstep		:3;	// Gain step for image rejection measurement. Depends on frequency			
			UInt8 Extended_Reg	:1;	// Enable the extended byte addressing				
									// 0: Limited byte (&h00:&h0F)
									// 1: Extended byte (&h00:&h26)
		};							
	};									

	union									
	{									
		UInt8 CAL_POST_DIV_BYTE;	// address 0x08							
									// CAL post divider byte	
	};									

	union									
	{									
		UInt8 CAL_DIV_BYTE_1;		// address 0x09						
									// CAL divider byte	1
		struct								
		{								
			UInt8 CAL_Div_22_to_16:7;// CAL divider value 22 to 16							
			UInt8 UNUSED_0x09	:1;	// Reserved, must be written as 0
		};								
	};									

	union									
	{									
		UInt8 CAL_DIV_BYTE_2;		// address 0x0A						
									// CAL divider byte	2
		struct								
		{								
			UInt8 CAL_Div_15_to_8:8;// CAL divider value 15 to 8							
		};								
	};									

	union									
	{									
		UInt8 CAL_DIV_BYTE_3;		// address 0x0B						
									// CAL divider byte	3
		struct								
		{								
			UInt8 CAL_Div_7_to_0:8;	// CAL divider value 7 to 0						
		};								
	};									

	union									
	{									
		UInt8 MAIN_POST_DIV_BYTE;	// address 0x0C							
									// MAIN post divider byte 	
		struct								
		{							
			UInt8 MAIN_Post_Div	:7;	// MAIN post divider value
			UInt8 IF_notch	:1;	// Reserved, must be written as 0
		};							
	};								

	union								
	{								
		UInt8 MAIN_DIV_BYTE_1;		// address 0x0D					
									// MAIN divider byte 1
		struct							
		{							
			UInt8 MAIN_Div_22_to_16:7;// MAIN divider value 22 to 16						
			UInt8 UNUSED_0x0D	:1;	// Reserved, must be written as 0				
		};							
	};								

	union								
	{								
		UInt8 MAIN_DIV_BYTE_2;		// address 0x0E					
									// MAIN divider byte 2
		struct							
		{							
			UInt8 MAIN_Div_15_to_8:8;// MAIN divider value 15 to 8						
		};							
	};								

	union								
	{								
		UInt8 MAIN_DIV_BYTE_3;		// address 0x0F					
									// MAIN divider byte 3
		struct							
		{							
			UInt8 MAIN_Div_7_to_0:8;// MAIN divider value 7 to 0						
		};							
	};								

	UInt8 EXTENDED_BYTE_1;			// address 0x10					
									// extended byte 1

	UInt8 EXTENDED_BYTE_2;			// address 0x11					
									// extended byte 2

	UInt8 EXTENDED_BYTE_3;			// address 0x12					
									// extended byte 3

	UInt8 EXTENDED_BYTE_4;			// address 0x13					
									// extended byte 4

	UInt8 EXTENDED_BYTE_5;			// address 0x14					
									// extended byte 5

	UInt8 EXTENDED_BYTE_6;			// address 0x15					
									// extended byte 6 

	UInt8 EXTENDED_BYTE_7;			// address 0x16					
									// extended byte7

	UInt8 EXTENDED_BYTE_8;			// address 0x17					
									// extended byte 8

	UInt8 EXTENDED_BYTE_9;			// address 0x18					
									// extended byte 9

	UInt8 EXTENDED_BYTE_10;			// address 0x19					
									// extended byte 10

	UInt8 EXTENDED_BYTE_11;			// address 0x1A					
									// extended byte 11

	UInt8 EXTENDED_BYTE_12;			// address 0x1B					
									// extended byte 12

	UInt8 EXTENDED_BYTE_13;			// address 0x1C					
									// extended byte 13

	UInt8 EXTENDED_BYTE_14;			// address 0x1D					
									// extended byte 14

	UInt8 EXTENDED_BYTE_15;			// address 0x1E					
									// extended byte 15

	UInt8 EXTENDED_BYTE_16;			// address 0x1F					
									// extended byte 16

	UInt8 EXTENDED_BYTE_17;			// address 0x20					
									// extended byte 17

	UInt8 EXTENDED_BYTE_18;			// address 0x21					
									// extended byte 18

	UInt8 EXTENDED_BYTE_19;			// address 0x22					
									// extended byte 19

	UInt8 EXTENDED_BYTE_20;			// address 0x23					
									// extended byte 20

	UInt8 EXTENDED_BYTE_21;			// address 0x24					
									// extended byte 21

	UInt8 EXTENDED_BYTE_22;			// address 0x25					
									// extended byte 22

	UInt8 EXTENDED_BYTE_23;			// address 0x26					
									// extended byte 23

} tmTDA18271I2CMap_t, *ptmTDA18271I2CMap_t;

typedef struct _tmAFAInfo_t {
    Demodulator*				demodulator;
    UInt8						chip;
} tmAFAInfo_t, *ptmAFAInfo_t;

typedef struct _tmTDA18271Object_t {
    tmAFAInfo_t				    AFAInfo;
	Bool_						init;
    UInt32						uHwAddress;
    tmhalFEBslSystemFunc_t		SystemFunc;
    tmTDA18271PowerState_t		curPowerState;
    tmTDA18271StandardMode_t	StandardMode;
	tmTDA18271Config_t			Config;
	tmTDA18271I2CMap_t			I2CMap;
	UInt32						I2CLog[TDA18271_LOG_NB_ROWS][TDA18271_NB_BYTES + 2];
    UInt32						uTickEnd;	
} tmTDA18271Object_t, *ptmTDA18271Object_t;

//-----------------------------------------------------------------------------
// Function:
//-----------------------------------------------------------------------------
//

tmErrorCode_t
tmbslTDA18271Init(
    tmUnitSelect_t     TunerUnit,    //  I: Tuner unit number
    tmbslTuParam_t     Param         //  I: setup parameters
);

#ifdef __cplusplus
}
#endif

#endif // _TMBSL_TDA18271LOCAL_H //---------------