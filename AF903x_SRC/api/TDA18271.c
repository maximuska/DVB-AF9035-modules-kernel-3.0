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
// FILE NAME:    tmbslTDA18271.c
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
//#include "tmbslTuner.h"
#include "TDA18271Local.h"

#include "standard.h"

//-----------------------------------------------------------------------------
// Types and defines:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// Global data:
//-----------------------------------------------------------------------------
//
//
// default instance
tmTDA18271Object_t gTDA18271Instance[] = 
{
	{
        {
			NULL,   /* Demodulator */
			0x01    /* chip */
		},
		
		False,							// init (instance initialization default)

        0,								// uHwAddress (HwId default value)

        {								// SystemFunc (system functions default addresses)
			NULL,
			NULL,
		},
		tmPowerSleepMode,				// default power state
		tmDigital_TV_ATSC_6MHz,			// default standard mode
        {								// Config
			CUSTOM_BOARD_DEF,				// uBoard [default Configuration structure]
			OM57XX_STANDARD_DEF,			// uStandard
			545000000,						// uRF
			3250000,						// uIF
			6000000,						// uBW
			0,								// uTMMODE
			1,								// uPLMODE
			0,								// uMapName
			0,								// uMAPCOLUMN
			0,								// uMAPROW
			0x6F,							// uPROTOCOLSTEP
			0x051E3C00,						// uPROTOCOLWAIT
			{								// IR_MEAS_Map uRF_Max 
				{30000000},
				{200000000},		
				{600000000},
				{865000000},
			},
			{							// IR_CAL_Map uRF, uIR_GStep 
				{72000000, 0x03},		
				{408000000, 0x03},
				{808000000, 0x03},
			},
			{							// BP_FILTER_Map uRF_Max, uBP_Filter 
				{62000000, 0x00},		
				{84000000, 0x01},
				{100000000, 0x02},
				{140000000, 0x03},
				{170000000, 0x04},
				{180000000, 0x05},
				{865000000, 0x06},
			},
			{							// RF_BAND_Map uRF_Max, uRF_Band
				{47900000, 0x00},		
				{61100000, 0x01},	
				{152600000, 0x02},	
				{164700000, 0x03},	
				{203500000, 0x04},	
				{457800000, 0x05},	
				{865000000, 0x06},	
			},		
			{							// GAIN_TAPER_Map uRF_Max, uGain_Taper 
				{45400000, 0x1F},			
				{45800000, 0x1E},			
				{46200000, 0x1D},			
				{46700000, 0x1C},			
				{47100000, 0x1B},			
				{47500000, 0x1A},			
				{47900000, 0x19},			
				{49600000, 0x17},			
				{51200000, 0x16},			
				{52900000, 0x15},			
				{54500000, 0x14},			
				{56200000, 0x13},			
				{57800000, 0x12},			
				{59500000, 0x11},			
				{61100000, 0x10},			
				{67600000, 0x0D},			
				{74200000, 0x0C},			
				{80700000, 0x0B},			
				{87200000, 0x0A},			
				{93800000, 0x09},			
				{100300000, 0x08},			
				{106900000, 0x07},			
				{113400000, 0x06},			
				{119900000, 0x05},			
				{126500000, 0x04},			
				{133000000, 0x03},			
				{139500000, 0x02},			
				{146100000, 0x01},			
				{152600000, 0x00},			
				{154300000, 0x1F},			
				{156100000, 0x1E},			
				{157800000, 0x1D},			
				{159500000, 0x1C},			
				{161200000, 0x1B},			
				{163000000, 0x1A},			
				{164700000, 0x19},			
				{170200000, 0x17},			
				{175800000, 0x16},			
				{181300000, 0x15},			
				{186900000, 0x14},			
				{192400000, 0x13},			
				{198000000, 0x12},			
				{203500000, 0x11},			
				{216200000, 0x14},			
				{228900000, 0x13},			
				{241600000, 0x12},			
				{254400000, 0x11},			
				{267100000, 0x10},			
				{279800000, 0x0F},			
				{292500000, 0x0E},			
				{305200000, 0x0D},			
				{317900000, 0x0C},			
				{330700000, 0x0B},			
				{343400000, 0x0A},			
				{356100000, 0x09},			
				{368800000, 0x08},			
				{381500000, 0x07},			
				{394200000, 0x06},			
				{406900000, 0x05},			
				{419700000, 0x04},			
				{432400000, 0x03},			
				{445100000, 0x02},			
				{457800000, 0x01},			
				{476300000, 0x19},			
				{494800000, 0x18},			
				{513300000, 0x17},			
				{531800000, 0x16},			
				{550300000, 0x15},			
				{568900000, 0x14},			
				{587400000, 0x13},			
				{605900000, 0x12},			
				{624400000, 0x11},			
				{642900000, 0x10},			
				{661400000, 0x0F},			
				{679900000, 0x0E},			
				{698400000, 0x0D},			
				{716900000, 0x0C},			
				{735400000, 0x0B},			
				{753900000, 0x0A},			
				{772500000, 0x09},			
				{791000000, 0x08},			
				{809500000, 0x07},			
				{828000000, 0x06},			
				{846500000, 0x05},			
				{865000000, 0x04},			
			},
			{							// RF_CAL_Map uRF_Max, uRFC_Cprog
				{41000000, 0x1E},
				{43000000, 0x30},
				{45000000, 0x43},
				{46000000, 0x4D},
				{47000000, 0x54},
				{47900000, 0x64},
				{49100000, 0x20},
				{50000000, 0x22},
				{51000000, 0x2A},
				{53000000, 0x32},
				{55000000, 0x35},
				{56000000, 0x3C},
				{57000000, 0x3F},
				{58000000, 0x48},
				{59000000, 0x4D},
				{60000000, 0x58},
				{61100000, 0x5F},
			},
			{							// RF_CAL_KMCO_Map uRF_Max uK, uM, UCOAmp
				{61100000,	7,	1,	3},		
				{350000000,	4,	0,	3},		
				{720000000,	3,	0,	3},		
				{865000000,	4,	0,	3},
			},
			{							// THERMOMETER_Map uTM_D, uTM_60_92, uTM_92_122 
				{0x00, 0x3C, 0x5C},
				{0x01, 0x3E, 0x5E},
				{0x02, 0x42, 0x62},
				{0x03, 0x40, 0x60},
				{0x04, 0x4A, 0x6A},
				{0x05, 0x48, 0x68},
				{0x06, 0x44, 0x64},
				{0x07, 0x46, 0x66},
				{0x08, 0x5A, 0x7A},
				{0x09, 0x58, 0x78},
				{0x0A, 0x54, 0x74},
				{0x0B, 0x56, 0x76},
				{0x0C, 0x4C, 0x6C},
				{0x0D, 0x4E, 0x6E},
				{0x0E, 0x52, 0x72},
				{0x0F, 0x50, 0x70},	
			},
			{							// CAL_PLL_Map uLO_Max, uPost_Div, uDiv
				{33000000,	0xDD,	0xD0},		
				{36000000,	0xDC,	0xC0},		
				{40000000,	0xDB,	0xB0},		
				{44000000,	0xDA,	0xA0},		
				{49000000,	0xD9,	0x90},		
				{55000000,	0xD8,	0x80},		
				{63000000,	0xD3,	0x70},		
				{67000000,	0xCD,	0x68},		
				{73000000,	0xCC,	0x60},		
				{80000000,	0xCB,	0x58},		
				{88000000,	0xCA,	0x50},		
				{98000000,	0xC9,	0x48},		
				{110000000,	0xC8,	0x40},		
				{126000000,	0xC3,	0x38},		
				{135000000,	0xBD,	0x34},		
				{147000000,	0xBC,	0x30},		
				{160000000,	0xBB,	0x2C},		
				{176000000,	0xBA,	0x28},		
				{196000000,	0xB9,	0x24},		
				{220000000,	0xB8,	0x20},		
				{252000000,	0xB3,	0x1C},		
				{271000000,	0xAD,	0x1A},		
				{294000000,	0xAC,	0x18},		
				{321000000,	0xAB,	0x16},		
				{353000000,	0xAA,	0x14},		
				{392000000,	0xA9,	0x12},		
				{441000000,	0xA8,	0x10},		
				{505000000,	0xA3,	0x0E},		
				{543000000,	0x9D,	0x0D},		
				{589000000,	0x9C,	0x0C},		
				{642000000,	0x9B,	0x0B},		
				{707000000,	0x9A,	0x0A},		
				{785000000,	0x99,	0x09},		
				{883000000,	0x98,	0x08},		
				{1010000000,0x93,	0x07},		
			},					
			{							// MAIN_PLL_Map uLO_Max, uPost_Div, uDiv
				{32000000,	0x5F,	0xF0},
				{35000000,	0x5E,	0xE0},
				{37000000,	0x5D,	0xD0},
				{41000000,	0x5C,	0xC0},
				{44000000,	0x5B,	0xB0},
				{49000000,	0x5A,	0xA0},
				{54000000,	0x59,	0x90},
				{61000000,	0x58,	0x80},
				{65000000,	0x4F,	0x78},
				{70000000,	0x4E,	0x70},
				{75000000,	0x4D,	0x68},
				{82000000,	0x4C,	0x60},
				{89000000,	0x4B,	0x58},
				{98000000,	0x4A,	0x50},
				{109000000,	0x49,	0x48},
				{123000000,	0x48,	0x40},
				{131000000,	0x3F,	0x3C},
				{141000000,	0x3E,	0x38},
				{151000000,	0x3D,	0x34},
				{164000000,	0x3C,	0x30},
				{179000000,	0x3B,	0x2C},
				{197000000,	0x3A,	0x28},
				{219000000,	0x39,	0x24},
				{246000000,	0x38,	0x20},
				{263000000,	0x2F,	0x1E},
				{282000000,	0x2E,	0x1C},
				{303000000,	0x2D,	0x1A},
				{329000000,	0x2C,	0x18},
				{359000000,	0x2B,	0x16},
				{395000000,	0x2A,	0x14},
				{438000000,	0x29,	0x12},
				{493000000,	0x28,	0x10},
				{526000000,	0x1F,	0x0F},
				{564000000,	0x1E,	0x0E},
				{607000000,	0x1D,	0x0D},
				{658000000,	0x1C,	0x0C},
				{718000000,	0x1B,	0x0B},
				{790000000,	0x1A,	0x0A},
				{877000000,	0x19,	0x09},
				{987000000,	0x18,	0x08},	
			},
		},
		0,								// I2CMap
		0,								// I2CLog
        0,								// uTickEnd [end tick value]		
	},									// end of 1st element
	{
        {
			NULL,   /* Demodulator */
			0x01    /* chip */
		},
		
		False,							// init (instance initialization default)

        0,								// uHwAddress (HwId default value)

        {								// SystemFunc (system functions default addresses)
			NULL,
			NULL,
		},
		tmPowerSleepMode,				// default power state
		tmDigital_TV_ATSC_6MHz,					// default standard mode
        {								// Config
			CUSTOM_BOARD_DEF,				// uBoard [default Configuration structure]
			OM57XX_STANDARD_DEF,			// uStandard
			545000000,						// uRF
			3250000,						// uIF
			6000000,						// uBW
			0,								// uTMMODE
			1,								// uPLMODE
			0,								// uMapName
			0,								// uMAPCOLUMN
			0,								// uMAPROW
			0x6F,							// uPROTOCOLSTEP
			0x051E3C00,						// uPROTOCOLWAIT
			{								// IR_MEAS_Map uRF_Max 
				{30000000},
				{200000000},		
				{600000000},
				{865000000},
			},
			{							// IR_CAL_Map uRF, uIR_GStep 
				{72000000, 0x03},		
				{408000000, 0x03},
				{808000000, 0x03},
			},
			{							// BP_FILTER_Map uRF_Max, uBP_Filter 
				{62000000, 0x00},		
				{84000000, 0x01},
				{100000000, 0x02},
				{140000000, 0x03},
				{170000000, 0x04},
				{180000000, 0x05},
				{865000000, 0x06},
			},
			{							// RF_BAND_Map uRF_Max, uRF_Band
				{47900000, 0x00},		
				{61100000, 0x01},	
				{152600000, 0x02},	
				{164700000, 0x03},	
				{203500000, 0x04},	
				{457800000, 0x05},	
				{865000000, 0x06},	
			},		
			{							// GAIN_TAPER_Map uRF_Max, uGain_Taper 
				{45400000, 0x1F},			
				{45800000, 0x1E},			
				{46200000, 0x1D},			
				{46700000, 0x1C},			
				{47100000, 0x1B},			
				{47500000, 0x1A},			
				{47900000, 0x19},			
				{49600000, 0x17},			
				{51200000, 0x16},			
				{52900000, 0x15},			
				{54500000, 0x14},			
				{56200000, 0x13},			
				{57800000, 0x12},			
				{59500000, 0x11},			
				{61100000, 0x10},			
				{67600000, 0x0D},			
				{74200000, 0x0C},			
				{80700000, 0x0B},			
				{87200000, 0x0A},			
				{93800000, 0x09},			
				{100300000, 0x08},			
				{106900000, 0x07},			
				{113400000, 0x06},			
				{119900000, 0x05},			
				{126500000, 0x04},			
				{133000000, 0x03},			
				{139500000, 0x02},			
				{146100000, 0x01},			
				{152600000, 0x00},			
				{154300000, 0x1F},			
				{156100000, 0x1E},			
				{157800000, 0x1D},			
				{159500000, 0x1C},			
				{161200000, 0x1B},			
				{163000000, 0x1A},			
				{164700000, 0x19},			
				{170200000, 0x17},			
				{175800000, 0x16},			
				{181300000, 0x15},			
				{186900000, 0x14},			
				{192400000, 0x13},			
				{198000000, 0x12},			
				{203500000, 0x11},			
				{216200000, 0x14},			
				{228900000, 0x13},			
				{241600000, 0x12},			
				{254400000, 0x11},			
				{267100000, 0x10},			
				{279800000, 0x0F},			
				{292500000, 0x0E},			
				{305200000, 0x0D},			
				{317900000, 0x0C},			
				{330700000, 0x0B},			
				{343400000, 0x0A},			
				{356100000, 0x09},			
				{368800000, 0x08},			
				{381500000, 0x07},			
				{394200000, 0x06},			
				{406900000, 0x05},			
				{419700000, 0x04},			
				{432400000, 0x03},			
				{445100000, 0x02},			
				{457800000, 0x01},			
				{476300000, 0x19},			
				{494800000, 0x18},			
				{513300000, 0x17},			
				{531800000, 0x16},			
				{550300000, 0x15},			
				{568900000, 0x14},			
				{587400000, 0x13},			
				{605900000, 0x12},			
				{624400000, 0x11},			
				{642900000, 0x10},			
				{661400000, 0x0F},			
				{679900000, 0x0E},			
				{698400000, 0x0D},			
				{716900000, 0x0C},			
				{735400000, 0x0B},			
				{753900000, 0x0A},			
				{772500000, 0x09},			
				{791000000, 0x08},			
				{809500000, 0x07},			
				{828000000, 0x06},			
				{846500000, 0x05},			
				{865000000, 0x04},			
			},
			{							// RF_CAL_Map uRF_Max, uRFC_Cprog
				{41000000, 0x1E},
				{43000000, 0x30},
				{45000000, 0x43},
				{46000000, 0x4D},
				{47000000, 0x54},
				{47900000, 0x64},
				{49100000, 0x20},
				{50000000, 0x22},
				{51000000, 0x2A},
				{53000000, 0x32},
				{55000000, 0x35},
				{56000000, 0x3C},
				{57000000, 0x3F},
				{58000000, 0x48},
				{59000000, 0x4D},
				{60000000, 0x58},
				{61100000, 0x5F},
			},
			{							// RF_CAL_KMCO_Map uRF_Max uK, uM, UCOAmp
				{61100000,	7,	1,	3},		
				{350000000,	4,	0,	3},		
				{720000000,	3,	0,	3},		
				{865000000,	4,	0,	3},
			},
			{							// THERMOMETER_Map uTM_D, uTM_60_92, uTM_92_122 
				{0x00, 0x3C, 0x5C},
				{0x01, 0x3E, 0x5E},
				{0x02, 0x42, 0x62},
				{0x03, 0x40, 0x60},
				{0x04, 0x4A, 0x6A},
				{0x05, 0x48, 0x68},
				{0x06, 0x44, 0x64},
				{0x07, 0x46, 0x66},
				{0x08, 0x5A, 0x7A},
				{0x09, 0x58, 0x78},
				{0x0A, 0x54, 0x74},
				{0x0B, 0x56, 0x76},
				{0x0C, 0x4C, 0x6C},
				{0x0D, 0x4E, 0x6E},
				{0x0E, 0x52, 0x72},
				{0x0F, 0x50, 0x70},	
			},
			{							// CAL_PLL_Map uLO_Max, uPost_Div, uDiv
				{33000000,	0xDD,	0xD0},		
				{36000000,	0xDC,	0xC0},		
				{40000000,	0xDB,	0xB0},		
				{44000000,	0xDA,	0xA0},		
				{49000000,	0xD9,	0x90},		
				{55000000,	0xD8,	0x80},		
				{63000000,	0xD3,	0x70},		
				{67000000,	0xCD,	0x68},		
				{73000000,	0xCC,	0x60},		
				{80000000,	0xCB,	0x58},		
				{88000000,	0xCA,	0x50},		
				{98000000,	0xC9,	0x48},		
				{110000000,	0xC8,	0x40},		
				{126000000,	0xC3,	0x38},		
				{135000000,	0xBD,	0x34},		
				{147000000,	0xBC,	0x30},		
				{160000000,	0xBB,	0x2C},		
				{176000000,	0xBA,	0x28},		
				{196000000,	0xB9,	0x24},		
				{220000000,	0xB8,	0x20},		
				{252000000,	0xB3,	0x1C},		
				{271000000,	0xAD,	0x1A},		
				{294000000,	0xAC,	0x18},		
				{321000000,	0xAB,	0x16},		
				{353000000,	0xAA,	0x14},		
				{392000000,	0xA9,	0x12},		
				{441000000,	0xA8,	0x10},		
				{505000000,	0xA3,	0x0E},		
				{543000000,	0x9D,	0x0D},		
				{589000000,	0x9C,	0x0C},		
				{642000000,	0x9B,	0x0B},		
				{707000000,	0x9A,	0x0A},		
				{785000000,	0x99,	0x09},		
				{883000000,	0x98,	0x08},		
				{1010000000,0x93,	0x07},		
			},					
			{							// MAIN_PLL_Map uLO_Max, uPost_Div, uDiv
				{32000000,	0x5F,	0xF0},
				{35000000,	0x5E,	0xE0},
				{37000000,	0x5D,	0xD0},
				{41000000,	0x5C,	0xC0},
				{44000000,	0x5B,	0xB0},
				{49000000,	0x5A,	0xA0},
				{54000000,	0x59,	0x90},
				{61000000,	0x58,	0x80},
				{65000000,	0x4F,	0x78},
				{70000000,	0x4E,	0x70},
				{75000000,	0x4D,	0x68},
				{82000000,	0x4C,	0x60},
				{89000000,	0x4B,	0x58},
				{98000000,	0x4A,	0x50},
				{109000000,	0x49,	0x48},
				{123000000,	0x48,	0x40},
				{131000000,	0x3F,	0x3C},
				{141000000,	0x3E,	0x38},
				{151000000,	0x3D,	0x34},
				{164000000,	0x3C,	0x30},
				{179000000,	0x3B,	0x2C},
				{197000000,	0x3A,	0x28},
				{219000000,	0x39,	0x24},
				{246000000,	0x38,	0x20},
				{263000000,	0x2F,	0x1E},
				{282000000,	0x2E,	0x1C},
				{303000000,	0x2D,	0x1A},
				{329000000,	0x2C,	0x18},
				{359000000,	0x2B,	0x16},
				{395000000,	0x2A,	0x14},
				{438000000,	0x29,	0x12},
				{493000000,	0x28,	0x10},
				{526000000,	0x1F,	0x0F},
				{564000000,	0x1E,	0x0E},
				{607000000,	0x1D,	0x0D},
				{658000000,	0x1C,	0x0C},
				{718000000,	0x1B,	0x0B},
				{790000000,	0x1A,	0x0A},
				{877000000,	0x19,	0x09},
				{987000000,	0x18,	0x08},	
			},
		},
		0,								// I2CMap
		0,								// I2CLog
        0,								// uTickEnd [end tick value]
	},									// end of 2nd element
};

//-----------------------------------------------------------------------------
// Internal Prototypes:
//-----------------------------------------------------------------------------
//
Bool_
TDA18271Init (
    tmUnitSelect_t			TunerUnit	// I: Tuner Object
    );
Bool_ 
TDA18271WaitTick(
    ptmTDA18271Object_t	pObj		// I: Tuner unit number
    );
Bool_ 
TDA18271Write(
    ptmTDA18271Object_t		pObj,		// I: Tuner unit number
	UInt8					uSubAddress,// I: sub address
	UInt8					uNbData		// I: nb of data
	);
Bool_ 
TDA18271Read(
    ptmTDA18271Object_t		pObj,		// I: Tuner unit number
	UInt8					uSubAddress,// I: sub address
	UInt8					uNbData		// I: nb of data
	);
Bool_ 
TDA18271Wait(
    ptmTDA18271Object_t		pObj,		//  I: Tuner unit number
    UInt16					wTime		//  I: time to wait for
	);
Bool_ 
TDA18271ShiftLog(
    ptmTDA18271Object_t		pObj,		// I: Tuner unit number
	UInt8					uNbRows	// I: nb of lines
	);
Bool_
TDA18271CalcMAINPLL (
    ptmTDA18271Object_t		pObj,		// I: tuner Object
    UInt32					uLO			// I: local oscillator frequency in hertz
    );
Bool_
TDA18271CalcCALPLL (
    ptmTDA18271Object_t		pObj,		// I: tuner Object
    UInt32					uLO			// I: local oscillator frequency in hertz
    );
Bool_
TDA18271CalcRFFilter (
    ptmTDA18271Object_t		pObj,		// I: tuner Object
    UInt32					uLO			// I: local oscillator frequency in hertz
    );
tmErrorCode_t
tmbslTDA18271SetConfig(
    tmUnitSelect_t		TunerUnit,  //  I: TunerUnit number
    UInt32				uItemId,    //  I: Identifier of the item to modify
    UInt32				uValue      //  I: Value to set for the config item
    );
    
Bool_    SY_Write(UInt32  uAddress,
                 UInt32  uSubAddress,
                 UInt32  uNbData,
                 UInt32* pDataBuff)
{
	Bool_					RetStatus = False;
	ptmTDA18271Object_t		pObj;
	UInt32					dwError = 0;
	UInt8					uBuffer[39];
	UInt32					i;

	for (i = 0; i < uNbData; i++)
	{
		uBuffer[i] = (UInt8)pDataBuff[i];
	}

	pObj = &gTDA18271Instance[0];
	
	dwError = Standard_writeTunerRegisters (pObj->AFAInfo.demodulator, pObj->AFAInfo.chip,
	                                        (unsigned short)uSubAddress, (UInt8)uNbData, uBuffer);

	if (dwError == 0) RetStatus = True;

	return (RetStatus);
};

Bool_    SY_Read(UInt32  uAddress,
                UInt32  uSubAddress,
                UInt32  uNbData,
                UInt32* pDataBuff)
{
	Bool_					RetStatus = False;
	ptmTDA18271Object_t		pObj;
	UInt32					dwError = 0;
	UInt8					uBuffer[39];
	UInt32					i;

	pObj = &gTDA18271Instance[0];

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


//-----------------------------------------------------------------------------
// Exported functions:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271Init:
//
// DESCRIPTION: create an instance of a TDA18271 Tuner
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TM_OK
//  
// NOTES:
//-----------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271Init(
    tmUnitSelect_t     TunerUnit,    //  I: Tuner unit number
    tmbslTuParam_t     Param         //  I: setup parameters
    )
{
	ptmTDA18271Object_t		pObj;

    //----------------------
    // test input parameters
    //----------------------
    // test the max number
    if (TunerUnit > TDA18271_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    //----------------------
    // initialize the Object
    //----------------------
    // return if already initialized
    if(gTDA18271Instance[TunerUnit].init == True)
        return TM_OK;

	// pObj initialisation
	pObj = &gTDA18271Instance[TunerUnit];

    //----------------
    // init the Object
    //----------------
    // initialize the Object by default values
    pObj->uHwAddress = Param.uHwAddress;
    pObj->SystemFunc = Param.systemFunc;
    pObj->init = True;

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
tmbslTDA18271DeInit (
    tmUnitSelect_t  TunerUnit     //  I: Tuner unit number
    )
{
	ptmTDA18271Object_t		pObj;

    //----------------------
    // test input parameters
    //----------------------
    // test the instance number
    if (TunerUnit > TDA18271_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    // test the Object
    if (gTDA18271Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

	// pObj initialisation
	pObj = &gTDA18271Instance[TunerUnit];

    //-------------------------
    // De-initialize the Object
    //-------------------------
    pObj->init = False;

    return TM_OK;
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
tmbslTDA18271GetSWVersion (
    ptmSWVersion_t     pSWVersion        //  I: Receives SW Version 
    )
{
    pSWVersion->compatibilityNr = TDA18271_BSL_COMP_NUM;
    pSWVersion->majorVersionNr  = TDA18271_BSL_MAJOR_VER;
    pSWVersion->minorVersionNr  = TDA18271_BSL_MINOR_VER;

    return TM_OK;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271SetPowerState:
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
tmbslTDA18271SetPowerState (
    tmUnitSelect_t				TunerUnit,		//  I: Tuner unit number
    tmTDA18271PowerState_t	powerState		//  I: Power state of this device
	)
{
	ptmTDA18271Object_t		pObj;

    //------------------------------
    // test input parameters
    //------------------------------
    // test the instance number
    if (TunerUnit > TDA18271_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    // test the object
    if (gTDA18271Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

	// pObj initialisation
	pObj = &gTDA18271Instance[TunerUnit];

	switch (powerState)
	{
		case tmPowerNormalMode:					
			// set SM bits
			pObj->I2CMap.SM = 0x00;
			pObj->I2CMap.SM_LT = 0x00;
			pObj->I2CMap.SM_XT = 0x00;
			break;

		case tmPowerSleepMode:
			// set SM bits
			pObj->I2CMap.SM = 0x01;
			pObj->I2CMap.SM_LT = 0x01;
			pObj->I2CMap.SM_XT = 0x01;
			break;

		case tmPowerStandbyWith16MHz:
			// set SM bits
			pObj->I2CMap.SM = 0x01;
			pObj->I2CMap.SM_LT = 0x01;
			pObj->I2CMap.SM_XT = 0x00;
			break;

		case tmPowerStandbyWith16MHzAndLoopThrough:
			// set SM bits
			pObj->I2CMap.SM = 0x01;
			pObj->I2CMap.SM_LT = 0x00;
			pObj->I2CMap.SM_XT = 0x00;
			break;

		case tmPowerStandbyWithLoopThrough:
			// set SM bits
			pObj->I2CMap.SM = 0x01;
			pObj->I2CMap.SM_LT = 0x00;
			pObj->I2CMap.SM_XT = 0x01;
			break;
		
		default:
			// power state not supported
			return TM_ERR_NOT_SUPPORTED;
	}

	// store powerstate 
	pObj->curPowerState = powerState;

    return TM_OK;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271GetPowerState:
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
tmbslTDA18271GetPowerState (
    tmUnitSelect_t				TunerUnit,		//  I: Tuner unit number
    tmTDA18271PowerState_t	*pPowerState	//  O: Power state of this device
	)
{
	ptmTDA18271Object_t		pObj;
	
    //------------------------------
    // test input parameters
    //------------------------------
    // test the instance number
    if (TunerUnit > TDA18271_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    // test the object
    if (gTDA18271Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

	// pObj initialisation
	pObj = &gTDA18271Instance[TunerUnit];

	//----------------------
    // get the value
    //----------------------
	if ((pObj->I2CMap.SM == 0x00) && (pObj->I2CMap.SM_LT == 0x00) && (pObj->I2CMap.SM_XT == 0x00))
		*pPowerState = tmPowerNormalMode;
	else if ((pObj->I2CMap.SM == 0x01) && (pObj->I2CMap.SM_LT == 0x01) && (pObj->I2CMap.SM_XT == 0x01))
		*pPowerState = tmPowerSleepMode;
	else if ((pObj->I2CMap.SM == 0x01) && (pObj->I2CMap.SM_LT == 0x01) && (pObj->I2CMap.SM_XT == 0x00))
		*pPowerState = tmPowerStandbyWith16MHz;
	else if ((pObj->I2CMap.SM == 0x01) && (pObj->I2CMap.SM_LT == 0x00) && (pObj->I2CMap.SM_XT == 0x00))
		*pPowerState = tmPowerStandbyWith16MHzAndLoopThrough;
	else if ((pObj->I2CMap.SM == 0x01) && (pObj->I2CMap.SM_LT == 0x00) && (pObj->I2CMap.SM_XT == 0x01))
		*pPowerState = tmPowerStandbyWithLoopThrough;
	else
		*pPowerState = tmPowerNotSupported;

    return TM_OK;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271SetStandardMode:
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
tmbslTDA18271SetStandardMode (
    tmUnitSelect_t					TunerUnit,		//  I: Tuner unit number
    tmTDA18271StandardMode_t		StandardMode	//  I: Standard mode of this device
	)
{
	ptmTDA18271Object_t		pObj;

    //------------------------------
    // test input parameters
    //------------------------------
    // test the instance number
    if (TunerUnit > TDA18271_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    // test the object
    if (gTDA18271Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

	// pObj initialisation
	pObj = &gTDA18271Instance[TunerUnit];

    // set uIF & Std & FM_RFn
	switch (StandardMode)
	{
		case tmDigital_TV_ATSC_6MHz:
			// set IF frequency 
			pObj->Config.uIF = 3250000;
			// set Bandwith value 
			pObj->Config.uBW = 6000000;			
			// set Std bit
			pObj->I2CMap.Std = 0x1C;
			// set FM_RFn bit
			pObj->I2CMap.FM_RFn = 0x00;
			break;

		case tmDigital_TV_DVBT_7MHz:
			// set IF frequency 
			pObj->Config.uIF = 3800000;
			// set Bandwith value 
			pObj->Config.uBW = 7000000;				
			// set Std bit
			pObj->I2CMap.Std = 0x1D;
			// set FM_RFn bit
			pObj->I2CMap.FM_RFn = 0x00;
			break;
		
		case tmDigital_TV_DVBT_8MHz:
			// set IF frequency 
			pObj->Config.uIF = 4300000;	
			// set Bandwith value 
			pObj->Config.uBW = 8000000;				
			// set Std bit
			pObj->I2CMap.Std = 0x1E;
			// set FM_RFn bit
			pObj->I2CMap.FM_RFn = 0x00;
			break;

		case tmAnalog_TV_MN:
			// set IF frequency 
			pObj->Config.uIF = 5750000;
			// set Bandwith value 
			pObj->Config.uBW = 6000000;	
			// set Std bit
			pObj->I2CMap.Std = 0x0D;
			// set FM_RFn bit
			pObj->I2CMap.FM_RFn = 0x00;
			break;

		case tmAnalog_TV_B:
			// set IF frequency 
			pObj->Config.uIF = 6750000;
			// set Bandwith value 
			pObj->Config.uBW = 7000000;	
			// set Std bit
			pObj->I2CMap.Std = 0x0E;
			// set FM_RFn bit
			pObj->I2CMap.FM_RFn = 0x00;
			break;

		case tmAnalog_TV_GH:
		case tmAnalog_TV_I:
		case tmAnalog_TV_DK:
		case tmAnalog_TV_L:					
			// set IF frequency 
			pObj->Config.uIF = 7750000;
			// set Bandwith value 
			pObj->Config.uBW = 8000000;				
			// set Std bit
			pObj->I2CMap.Std = 0x0F;
			// set FM_RFn bit
			pObj->I2CMap.FM_RFn = 0x00;
			break;

		case tmAnalog_TV_LL:
			// set IF frequency 
			pObj->Config.uIF = 1250000;
			// set Bandwith value 
			pObj->Config.uBW = 1500000;				
			// set Std bit
			pObj->I2CMap.Std = 0x0F;
			// set FM_RFn bit
			pObj->I2CMap.FM_RFn = 0x00;
			break;

		case tmAnalog_FM_Radio:
			// set IF frequency 
			pObj->Config.uIF = 1250000;
			// set Bandwith value 
			pObj->Config.uBW = 250000;				
			// set Std bit
			pObj->I2CMap.Std = 0x18; /* FM radio in digital mode */
			// set FM_RFn bit
			pObj->I2CMap.FM_RFn = 0x01;
			break;

		case tmDigital_TV_QAM_6MHz:
			// set IF frequency 
			pObj->Config.uIF = 4000000;
			// set Bandwith value 
			pObj->Config.uBW = 6000000;				
			// set Std bit
			pObj->I2CMap.Std = 0x1D;
			// set FM_RFn bit
			pObj->I2CMap.FM_RFn = 0x00;
			break;

		case tmDigital_TV_QAM_8MHz:
			// set IF frequency 
			pObj->Config.uIF = 5000000;
			// set Bandwith value 
			pObj->Config.uBW = 8000000;				
			// set Std bit
			pObj->I2CMap.Std = 0x1F;
			// set FM_RFn bit
			pObj->I2CMap.FM_RFn = 0x00;
			break;
	}

	// set IF_Level & IF_notch & RFAGC_Top & IFAGC_Top
	switch (StandardMode)
	{
		case tmDigital_TV_ATSC_6MHz:
		case tmDigital_TV_DVBT_7MHz:
		case tmDigital_TV_DVBT_8MHz:
		case tmDigital_TV_QAM_6MHz:
		case tmDigital_TV_QAM_8MHz:
			// set IF_Level
			pObj->I2CMap.IF_Level = 0x01;
			// set IF_notch
			pObj->I2CMap.IF_notch = 0x01;
			// set RFAGC_Top & IFAGC_Top
			pObj->I2CMap.EXTENDED_BYTE_22 = 0x37;
			break;

		case tmAnalog_TV_MN:
		case tmAnalog_TV_B:
		case tmAnalog_TV_GH:
		case tmAnalog_TV_I:
		case tmAnalog_TV_DK:
		case tmAnalog_TV_L:					
		case tmAnalog_TV_LL:
		case tmAnalog_FM_Radio:
			// set IF_Level
			pObj->I2CMap.IF_Level = 0x00;
			// set IF_notch
			pObj->I2CMap.IF_notch = 0x00;
			// set RFAGC_Top & IFAGC_Top
			pObj->I2CMap.EXTENDED_BYTE_22 = 0x2C;
			break;
		
		default:
			// standard mode not supported
			return TM_ERR_NOT_SUPPORTED;
	}

	// store standard mode 
	pObj->StandardMode = StandardMode;

    return TM_OK;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271GetStandardMode:
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
tmbslTDA18271GetStandardMode (
    tmUnitSelect_t					TunerUnit,		//  I: Tuner unit number
    tmTDA18271StandardMode_t		*pStandardMode	//  O: Standard mode of this device
	)
{
	ptmTDA18271Object_t		pObj;
	
    //------------------------------
    // test input parameters
    //------------------------------
    // test the instance number
    if (TunerUnit > TDA18271_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    // test the object
    if (gTDA18271Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

	// pObj initialisation
	pObj = &gTDA18271Instance[TunerUnit];

	//----------------------
    // get the value
    //----------------------
	*pStandardMode = pObj->StandardMode;

    return TM_OK;
}


//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271Write:
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
tmbslTDA18271Write (
    tmUnitSelect_t      TunerUnit,      //  I: Tuner unit number
    UInt32              uIndex,         //  I: Start index to write
    UInt32              uNbBytes,       //  I: Number of bytes to write
    UInt32*             puBytes         //  I: Pointer on an array of bytes
)
{
	
    UInt32	uCounter;
	UInt8*	pI2CMap;

	ptmTDA18271Object_t		pObj;
	
    //----------------------
    // test input parameters
    //----------------------
    // test the instance number
    if (TunerUnit > TDA18271_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    // test the Object
    if (gTDA18271Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

    // test the parameters. uIndex is: 0x0X
    if ((uIndex + uNbBytes) > TDA18271_NB_BYTES)
        return TMBSL_ERR_TUNER_BAD_PARAMETER;

	// pObj & pI2CMap initialisation
	pObj = &gTDA18271Instance[TunerUnit];
	pI2CMap = &(pObj->I2CMap.ID_BYTE) + uIndex;

    //--------------
    // set the value
    //--------------	
	// save the values written in the Tuner
	for (uCounter = 0; uCounter < uNbBytes; uCounter++){
		*pI2CMap = (UInt8)(puBytes[uCounter]);
		pI2CMap ++;
		}
    
    // write in the Tuner
	if (TDA18271Write(pObj,(UInt8)(uIndex),(UInt8)(uNbBytes)) != True)
		return TMBSL_ERR_IIC_ERR;
     
    return TM_OK;
}


//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271WriteBit:
//
// DESCRIPTION: Write in the Tuner.
//
// RETURN:      TM_ERR_NOT_SUPPORTED
//
// NOTES:
//-----------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271WriteBit (
    tmUnitSelect_t      TunerUnit,      //  I: Tuner unit number
    UInt32              uIndex,         //  I: Start index to write
    UInt32              uBitMask,       //  I: bit mask
    UInt32              uBitValue       //  I: bit value
)
{
    return TM_ERR_NOT_SUPPORTED;
}


//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271Read:
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
tmbslTDA18271Read (
    tmUnitSelect_t      TunerUnit,      //  I: Tuner unit number
    UInt32              uIndex,         //  I: Start index to read
    UInt32              uNbBytes,       //  I: Number of bytes to read
    UInt32*             puBytes         //  I: Pointer on an array of bytes
)
{
	UInt32	uCounter;
	UInt8*	pI2CMap;

	ptmTDA18271Object_t		pObj;

    //----------------------
    // test input parameters
    //----------------------
    // test the instance number
    if (TunerUnit > TDA18271_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    // test the Object
    if (gTDA18271Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

    // test the Object
    if (uNbBytes > TDA18271_NB_BYTES)
        return TMBSL_ERR_TUNER_BAD_PARAMETER;

	// test uIndex
	if (uIndex == -1)
		uIndex = 0;

	// pObj & pI2CMap initialisation
	pObj = &gTDA18271Instance[TunerUnit];
	pI2CMap = &(pObj->I2CMap.ID_BYTE) + uIndex;
    
    //--------------
    // get the value
    //--------------
	// read from the Tuner
	if (TDA18271Read(pObj,(UInt8)(uIndex),(UInt8)(uNbBytes)) != True)
		return TMBSL_ERR_IIC_ERR;
     
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
// FUNCTION:    tmbslTDA18271SetConfig:
//
// DESCRIPTION: Set the Config of the TDA18271
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
tmbslTDA18271SetConfig(
    tmUnitSelect_t     TunerUnit,  //  I: TunerUnit number
    UInt32             uItemId,    //  I: Identifier of the item to modify
    UInt32             uValue      //  I: Value to set for the Config item
    )
{
	ptmTDA18271Object_t		pObj;
	UInt8*					pI2CMap;
	UInt32*					pDataMap;
	
	//----------------------
    // test input parameters
    //----------------------
    // test the instance number
    if (TunerUnit > TDA18271_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    // test the Object
    if (gTDA18271Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

	// pObj initialisation
	pObj = &gTDA18271Instance[TunerUnit];

    //--------------
    // set the value
    //--------------
    switch((tmTDA18271cfgIndex_t)uItemId)
    {
        case BOARD:
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
				return TM_ERR_NOT_SUPPORTED;
			}
			// store board
			gTDA18271Instance[TunerUnit].Config.uBoard = uValue;
			break;

		case FEINIT:
			TDA18271Init(TunerUnit);
			break;

		case RF:
			// set RF frequency 
			pObj->Config.uRF = uValue;	
			break;

		case IF:
			// set IF frequency 
			pObj->Config.uIF = uValue;	
			break;

		case TMMODE:
			// set TMMODE
			pObj->Config.uTMMODE = uValue;
			// set TM_ON
			pObj->I2CMap.TM_ON = (UInt8)uValue;
			// write byte THERMO_BYTE
			if (TDA18271Write(pObj,0x01,1) != True)
				return TMBSL_ERR_IIC_ERR;
			break;

		case PLMODE:
			// set uPLMODE
			pObj->Config.uPLMODE = uValue;
			// set Dis_Power_level
			pObj->I2CMap.Dis_Power_level = (UInt8)uValue;
			// write byte EASY_PROG_BYTE_1
			if (TDA18271Write(pObj,0x03,1) != True)
				return TMBSL_ERR_IIC_ERR;
			break;

		case POWERSTATE:
			// set POWERSTATE
			tmbslTDA18271SetPowerState (TunerUnit, (tmTDA18271PowerState_t)uValue);
			// set CAL_Mode to normal mode
			pObj->I2CMap.CAL_Mode = 0x00;
			// write byte EASY_PROG_BYTE_3
			if (TDA18271Write(pObj,0x05,1) != True)
				return TMBSL_ERR_IIC_ERR;
			/*// wait 20 ms
			if (TDA18271Wait(pObj,20) == False)
				return TM_FALSE;*/
			break;

		case STANDARDMODE:
			// set STANDARDMODE
			tmbslTDA18271SetStandardMode (TunerUnit, (tmTDA18271StandardMode_t)uValue);
			// set CAL_Mode to normal mode
			pObj->I2CMap.CAL_Mode = 0x00;
			// write bytes EASY_PROG_BYTE_3 & EASY_PROG_BYTE_4
			if (TDA18271Write(pObj,0x05,2) != True)
				return TMBSL_ERR_IIC_ERR;
			// write MAIN_POST_DIV_BYTE
			if (TDA18271Write(pObj,0x0C,1) != True)
				return TMBSL_ERR_IIC_ERR;
			// write EXTENDED_BYTE_22
			if (TDA18271Write(pObj,0x25,1) != True)
				return TMBSL_ERR_IIC_ERR;
			break;

		case XTOUT:
			// set XTout_ON
			pObj->I2CMap.XTout_ON = (UInt8)(uValue) >> 1;
			// set Xtout_400mV
			pObj->I2CMap.Xtout_400mV = (UInt8)(uValue) & 0x01;
			// write byte EASY_PROG_BYTE_4
			if (TDA18271Write(pObj,0x06,1) != True)
				return TMBSL_ERR_IIC_ERR;
			break;

		case IFLEVEL:
			// set IF_Level
			pObj->I2CMap.IF_Level = (UInt8)uValue; 
			// write byte EASY_PROG_BYTE_4
			if (TDA18271Write(pObj,0x06,1) != True)
				return TMBSL_ERR_IIC_ERR;
			break;

		case EXTENDEDREG:
			// set Extended_Reg
			pObj->I2CMap.Extended_Reg = (UInt8)uValue;
			// write byte EASY_PROG_BYTE_5
			if (TDA18271Write(pObj,0x07,1) != True)
				return TMBSL_ERR_IIC_ERR;
			break;

		case MAPNAME:
			// set map name 
			pObj->Config.uMapName = uValue;
			break;
			
		case MAPCOLUMN:	
			// set map x 
			pObj->Config.uMAPCOLUMN = uValue;
			break;
			
		case MAPROW:	
			// set map y 
			pObj->Config.uMAPROW = uValue;
			break;

		case MAPVALUE:
			// set pointer on wanted cell
			switch (pObj->Config.uMapName)
			{
				case tmTDA18271_IR_MEAS_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_IR_MEAS_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_IR_MEAS_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.IR_MEAS_Map[pObj->Config.uMAPROW].uRF_Max);
				break;	

				case tmTDA18271_IR_CAL_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_IR_CAL_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_IR_CAL_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.IR_CAL_Map[pObj->Config.uMAPROW].uRF);
				break;

				case tmTDA18271_BP_FILTER_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_BP_FILTER_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_BP_FILTER_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.BP_FILTER_Map[pObj->Config.uMAPROW].uRF_Max);
				break;

				case tmTDA18271_RF_BAND_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_BAND_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_RF_BAND_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.RF_BAND_Map[pObj->Config.uMAPROW].uRF_Max);
				break;	

				case tmTDA18271_GAIN_TAPER_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_GAIN_TAPER_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_GAIN_TAPER_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.GAIN_TAPER_Map[pObj->Config.uMAPROW].uRF_Max);
				break;

				case tmTDA18271_RF_CAL_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_CAL_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_RF_CAL_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.RF_CAL_Map[pObj->Config.uMAPROW].uRF_Max);
				break;

				case tmTDA18271_RF_CAL_KMCO_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_CAL_KMCO_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_RF_CAL_KMCO_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.RF_CAL_KMCO_Map[pObj->Config.uMAPROW].uRF_Max);
				break;

				case tmTDA18271_THERMOMETER_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_THERMOMETER_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_THERMOMETER_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.THERMOMETER_Map[pObj->Config.uMAPROW].uTM_D);
				break;

				case tmTDA18271_CAL_PLL_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_CAL_PLL_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_CAL_PLL_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.CAL_PLL_Map[pObj->Config.uMAPROW].uLO_Max);
				break;

				case tmTDA18271_MAIN_PLL_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_MAIN_PLL_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_MAIN_PLL_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.MAIN_PLL_Map[pObj->Config.uMAPROW].uLO_Max);
				break;

				case tmTDA18271_I2C_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > 0) || (pObj->Config.uMAPROW > TDA18271_NB_BYTES - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pI2CMap initialisation
					pI2CMap = &(pObj->I2CMap.ID_BYTE) + pObj->Config.uMAPROW;
				break;
			}

			// set cell value
			if  (pObj->Config.uMapName == tmTDA18271_I2C_Map)
				*(pI2CMap + (UInt8)pObj->Config.uMAPCOLUMN) = (UInt8)uValue;
			else
				*(pDataMap + pObj->Config.uMAPCOLUMN) = uValue;
			break;

		case PROTOCOLSTEP:
			// set channel configuration protocol steps to execute
			pObj->Config.uPROTOCOLSTEP = uValue; 
			break;

		case PROTOCOLWAIT:
			// set channel configuration protocol wait times
			pObj->Config.uPROTOCOLWAIT = uValue; 
			break;

        case READINIT:
            // activate extended register access
            // read bytes 0x00 to 0x26
#if (0)
            if (TDA18271Read (pObj,0x00,39) != True)
		        return TMBSL_ERR_IIC_ERR;
#else
            if (TDA18271Read (pObj,0x00,16) != True)
		        return TMBSL_ERR_IIC_ERR;
#endif
            break;

	}
    return TM_OK;
}


//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271GetConfig:
//
// DESCRIPTION: Get the Config of the TDA18271
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TM_OK
//
// NOTES:       
//-----------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18271GetConfig(
    tmUnitSelect_t     TunerUnit,  //  I: Tuner unit number
    UInt32             uItemId,    //  I: Identifier of the item to get value
    UInt32*            puValue     //  I: Address of the variable to output the Config item value
    )
{
	UInt32 uCounter = 0;

	ptmTDA18271Object_t		pObj;
	UInt8*						pI2CMap;
	UInt32*						pDataMap;
	UInt32						uByte=0; 

	//----------------------
    // test input parameters
    //----------------------
    // test the instance number
    if (TunerUnit > TDA18271_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    // test the Object
    if (gTDA18271Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

	// pObj initialisation
	pObj = &gTDA18271Instance[TunerUnit];

    //--------------
    // get the value
    //--------------
    switch((tmTDA18271cfgIndex_t)uItemId)
    {
		case BOARD:
			// get board
			*puValue = pObj->Config.uBoard;
			break;

		case RF:
			// get RF frequency
			*puValue = pObj->Config.uRF;
			break;

		case IF:
			// get IF frequency
			*puValue = pObj->Config.uIF;
			break;

		case STATUSBYTE:
			// read bytes 0x00 to 0x0F
			if (TDA18271Read (pObj, 0x00, 16) != True)
				return TMBSL_ERR_IIC_ERR;
			break;

        case GETNBOFUNIT:
			*puValue = TDA18271_MAX_UNITS;
            break;

		case ID:
			// get ID value
			*puValue = pObj->I2CMap.ID;
			break;

		case POR:
			// get POR value
			*puValue = pObj->I2CMap.POR;
			break;

		case MAINLOCK:
			// get MAINLOCK value
			*puValue = pObj->I2CMap.MAIN_Lock;
			break;

		case TMMODE:
			// get TMMODE value
			*puValue = pObj->Config.uTMMODE;
			break;
	
		case TMVALUE:
			// test IRCALOK value
			if (pObj->I2CMap.IR_CAL_OK != 1)
				return TMBSL_ERR_IIC_ERR;
			
			// set CAL_Mode to thermo mode
			pObj->I2CMap.CAL_Mode = 0x03;
			// write byte EASY_PROG_BYTE_4
			if (TDA18271Write(pObj,0x06,1) != True)
				return TMBSL_ERR_IIC_ERR;

			// read byte THERMO_BYTE
			if (TDA18271Read (pObj, 0x00, 16) != True)
				return TMBSL_ERR_IIC_ERR;

			// set & write TM_Range
			if (((pObj->I2CMap.TM_D == 0x00) && (pObj->I2CMap.TM_Range == 0x01)) || ((pObj->I2CMap.TM_D == 0x08) && (pObj->I2CMap.TM_Range == 0x00)))
			{
				pObj->I2CMap.TM_Range = !(pObj->I2CMap.TM_Range);
				// write byte THERMO_BYTE
				if (TDA18271Write(pObj,0x01,1) != True)
					return TMBSL_ERR_IIC_ERR;
				// wait 10ms
				if (TDA18271Wait(pObj,10) == False)
					return TM_FALSE;   
				// read byte THERMO_BYTE
				if (TDA18271Read (pObj, 0x00, 16) != True)
					return TMBSL_ERR_IIC_ERR;
			}

			// set & write CAL_Mode to normal mode
			pObj->I2CMap.CAL_Mode = 0x00;
			// write byte EASY_PROG_BYTE_4
			if (TDA18271Write(pObj,0x06,1) != True)
				return TMBSL_ERR_IIC_ERR;

			// search for TMVALUE corresponding to TM_D
			uCounter = 0;
			do uCounter ++;
			while (pObj->I2CMap.TM_D > pObj->Config.THERMOMETER_Map[uCounter - 1].uTM_D && uCounter < TDA18271_THERMOMETER_NB_ROWS);
			// get TMVALUE value
			if (pObj->I2CMap.TM_Range == 0x00)
				*puValue = (UInt8)pObj->Config.THERMOMETER_Map[uCounter - 1].uTM_60_92;
			else
				*puValue = (UInt8)pObj->Config.THERMOMETER_Map[uCounter - 1].uTM_92_122;
			
			break;			

		case PLMODE:
			// get PLMODE value
			*puValue = pObj->Config.uPLMODE;
			break;

		case PLAGC1:
			// get PLAGC1 value
			*puValue = 3 * (2 + ((pObj->I2CMap.Power_Level_7_to_0 & 0x7F) >> 5));
			break;

		case PLAGC2:
			// get PLAGC2 value
			*puValue = 3 * (2 + (3 - (pObj->I2CMap.Power_Level_8 << 1 | pObj->I2CMap.Power_Level_7_to_0 >> 7)));
			break;

		case PLRFAGC:
			// get PLRFAGC value (PLRFAGC = PLRFAGC - 11)
			if (((pObj->I2CMap.EXTENDED_BYTE_22 & 0x7F) >> 4) < 5)
				*puValue = 11 + (92 + 2 * ((pObj->I2CMap.EXTENDED_BYTE_22 & 0x7F) >> 4)) - (103 - (pObj->I2CMap.Power_Level_7_to_0 & 0x1F));
			else
				*puValue = 11 + 102 - (103 - (pObj->I2CMap.Power_Level_7_to_0 & 0x1F));
			// limit PLRFAGC value
			if (*puValue > 33)
				*puValue = 33;
			else if (*puValue < 1)
				*puValue = 1;
			break;

		case RFCALOK:
			// get RFCALOK value
			*puValue = pObj->I2CMap.RF_CAL_OK;
			break;

		case IRCALOK:
			// get IRCALOK value
			*puValue = pObj->I2CMap.IR_CAL_OK;
			break;
		
		case BPFILTER:
			// get BPFILTER value
			*puValue = pObj->I2CMap.BP_Filter;
			break;

		case RFBAND:
			// get RFBAND value
			*puValue = pObj->I2CMap.RF_Band;
			break;

		case GAINTAPER:
			// get GAINTAPER value
			*puValue = pObj->I2CMap.Gain_Taper;
			break;

		case POWERSTATE:
			// get POWERSTATE
			tmbslTDA18271GetPowerState(TunerUnit,(ptmTDA18271PowerState_t)puValue);
			break;

		case LPFC:
			// get LPFC value
			*puValue = pObj->I2CMap.Std & 0x03;
			break;

		case FMRFN:
			// get FMRFN value
			*puValue = pObj->I2CMap.FM_RFn;
			break;

		case STANDARDMODE:
			// get STANDARDMODE
			tmbslTDA18271GetStandardMode(TunerUnit,(ptmTDA18271StandardMode_t)puValue);
			break;

		case XTOUT:
			// get XTout_ON & Xtout_400mV value
			*puValue = (UInt32)(pObj->I2CMap.XTout_ON << 1 | pObj->I2CMap.Xtout_400mV);
			break;

		case IFLEVEL:
			// get IFLEVEL value
			*puValue = pObj->I2CMap.IF_Level;
			break;

		case EXTENDEDREG:
			// get EXTENDEDREG value
			*puValue = pObj->I2CMap.Extended_Reg;
			break;

		case CALPOSTDIV:
			// get CALPOSTDIV value
			*puValue = pObj->I2CMap.CAL_POST_DIV_BYTE & 0x7F;
			break;

		case CALDIV:
			// get CALDIV value
			*puValue = pObj->I2CMap.CAL_Div_22_to_16 << 16 | pObj->I2CMap.CAL_Div_15_to_8 << 8 | pObj->I2CMap.CAL_Div_7_to_0;
			break;

		case MAINPOSTDIV:
			// get MAINPOSTDIV value
			*puValue = pObj->I2CMap.MAIN_Post_Div;
			break;

		case MAINDIV:
			// get MAINDIV value
			*puValue = pObj->I2CMap.MAIN_Div_22_to_16 << 16 | pObj->I2CMap.MAIN_Div_15_to_8 << 8 | pObj->I2CMap.MAIN_Div_7_to_0;
			break;

		case MAPVALUE:
			// set pointer on wanted cell
			switch (pObj->Config.uMapName)
			{
				case tmTDA18271_IR_MEAS_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_IR_MEAS_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_IR_MEAS_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.IR_MEAS_Map[pObj->Config.uMAPROW].uRF_Max);
				break;	

				case tmTDA18271_IR_CAL_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_IR_CAL_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_IR_CAL_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.IR_CAL_Map[pObj->Config.uMAPROW].uRF);
				break;

				case tmTDA18271_BP_FILTER_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_BP_FILTER_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_BP_FILTER_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.BP_FILTER_Map[pObj->Config.uMAPROW].uRF_Max);
				break;

				case tmTDA18271_RF_BAND_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_BAND_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_RF_BAND_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.RF_BAND_Map[pObj->Config.uMAPROW].uRF_Max);
				break;	

				case tmTDA18271_GAIN_TAPER_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_GAIN_TAPER_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_GAIN_TAPER_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.GAIN_TAPER_Map[pObj->Config.uMAPROW].uRF_Max);
				break;

				case tmTDA18271_RF_CAL_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_CAL_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_RF_CAL_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.RF_CAL_Map[pObj->Config.uMAPROW].uRF_Max);
				break;

				case tmTDA18271_RF_CAL_KMCO_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_RF_CAL_KMCO_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_RF_CAL_KMCO_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.RF_CAL_KMCO_Map[pObj->Config.uMAPROW].uRF_Max);
				break;

				case tmTDA18271_THERMOMETER_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_THERMOMETER_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_THERMOMETER_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.THERMOMETER_Map[pObj->Config.uMAPROW].uTM_D);
				break;	

				case tmTDA18271_CAL_PLL_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_CAL_PLL_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_CAL_PLL_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.CAL_PLL_Map[pObj->Config.uMAPROW].uLO_Max);
				break;	

				case tmTDA18271_MAIN_PLL_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > TDA18271_MAIN_PLL_NB_COLUMNS - 1) || (pObj->Config.uMAPROW > TDA18271_MAIN_PLL_NB_ROWS - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pDataMap initialisation
					pDataMap = &(pObj->Config.MAIN_PLL_Map[pObj->Config.uMAPROW].uLO_Max);
				break;

				case tmTDA18271_I2C_Map:
					// test map column & row
					if ((pObj->Config.uMAPCOLUMN > 0) || (pObj->Config.uMAPROW > TDA18271_NB_BYTES - 1))
						return TM_ERR_NOT_SUPPORTED;
					// pI2CMap initialisation
					pI2CMap = &(pObj->I2CMap.ID_BYTE) + pObj->Config.uMAPROW;
				break;
			}
			// get cell value
			if  (pObj->Config.uMapName == tmTDA18271_I2C_Map)
				*puValue = *(pI2CMap + pObj->Config.uMAPCOLUMN);
			else
				*puValue = *(pDataMap + pObj->Config.uMAPCOLUMN);
			break;

		// backdoor functions
		case IDENTITY:
			pObj->SystemFunc.SY_Read( pObj->uHwAddress, TDA18271_IDENTITY_IND, 1, &uByte); 
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
// FUNCTION:    tmbslTDA18271SetRf:
//
// DESCRIPTION: Calculate i2c I2CMap & write in TDA18271
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
tmbslTDA18271SetRf(
    tmUnitSelect_t		TunerUnit,  //  I: Tuner unit number
    UInt32				uRF			//  I: RF frequency in hertz
	)
{	
	UInt16	uCounter = 0;
	UInt8	uIRMeasCounter = 0;

	ptmTDA18271Object_t		pObj;
		
	//------------------------------
    // test input parameters
    //------------------------------
    // test the instance number
    if (TunerUnit > TDA18271_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    // test the Object
    if (gTDA18271Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;
	
	// pObj initialisation
	pObj = &gTDA18271Instance[TunerUnit];
		
	// Config.uRF update
	pObj->Config.uRF = uRF;

	//----------------------
	// read IR_CAL_OK bit value
	//----------------------
	if (((pObj->Config.uPROTOCOLSTEP & 0x40) >> 6) == 0x01)
	{
		// read bytes 0x00 to 0x0F
		if (TDA18271Read (pObj,0x00,16) != True)
			return TMBSL_ERR_IIC_ERR;
	}

	//----------------------
	// power on reset initialisation
	// test IR_CAL_OK bit value to determine if initialisation is needed
	//----------------------
	if ((pObj->I2CMap.IR_CAL_OK != 1 && ((pObj->Config.uPROTOCOLSTEP & 0x20) >> 5) == 0x01) || ((pObj->Config.uPROTOCOLSTEP & 0x10) >> 4) == 0x01)
	{	
		//----------------------
		// I2C map initialisation
		//----------------------
		// set & write all bytes
		pObj->I2CMap.ID_BYTE = 0x83;
		pObj->I2CMap.THERMO_BYTE = 0x08;
		pObj->I2CMap.POWER_LEVEL_BYTE = 0x80;
		pObj->I2CMap.EASY_PROG_BYTE_1 = 0xC6;
		pObj->I2CMap.EASY_PROG_BYTE_2 = 0xDF;
		pObj->I2CMap.EASY_PROG_BYTE_3 = 0x16;	// SM = '0', AGC_Low_BW = 1;
		pObj->I2CMap.EASY_PROG_BYTE_4 = 0x60;
		pObj->I2CMap.EASY_PROG_BYTE_5 = 0x80;	// Extended_Reg = '1'
		pObj->I2CMap.CAL_POST_DIV_BYTE = 0x80;	// Enable_Bus_Cal = '1', IR_GStep = '0'
		pObj->I2CMap.CAL_DIV_BYTE_1 = 0x00;
		pObj->I2CMap.CAL_DIV_BYTE_2 = 0x00;
		pObj->I2CMap.CAL_DIV_BYTE_3 = 0x00;
		pObj->I2CMap.MAIN_POST_DIV_BYTE = 0x00;
		pObj->I2CMap.MAIN_DIV_BYTE_1 = 0x00;
		pObj->I2CMap.MAIN_DIV_BYTE_2 = 0x00;
		pObj->I2CMap.MAIN_DIV_BYTE_3 = 0x00;
		pObj->I2CMap.EXTENDED_BYTE_1 = 0xFF;
		pObj->I2CMap.EXTENDED_BYTE_2 = 0x01;
		pObj->I2CMap.EXTENDED_BYTE_3 = 0x84;
		pObj->I2CMap.EXTENDED_BYTE_4 = 0x41;
		pObj->I2CMap.EXTENDED_BYTE_5 = 0x01;	// HCvco[1] = '0'
		pObj->I2CMap.EXTENDED_BYTE_6 = 0x84;
		pObj->I2CMap.EXTENDED_BYTE_7 = 0x40;	// Cal_Pulse_src = '125�s' // Decrease CAL pll locking time for IR calibration success
		pObj->I2CMap.EXTENDED_BYTE_8 = 0x07;	// IR_Loop = '8' & IR_Target = '62dB'
		pObj->I2CMap.EXTENDED_BYTE_9 = 0x00;
		pObj->I2CMap.EXTENDED_BYTE_10 = 0x00;
		pObj->I2CMap.EXTENDED_BYTE_11 = 0x96;	// CID_EN_Filt1M='1', HCvco[0]='1', CID_CkSpeed='250KHz/4�s', CID_CkDigSpeed='4MHz'
		pObj->I2CMap.EXTENDED_BYTE_12 = 0x0F;	// AGC12_Speed = '250 KHz'
		pObj->I2CMap.EXTENDED_BYTE_13 = 0xC1;	// RFC_Ckspeed = '62.5 KHz'
		pObj->I2CMap.EXTENDED_BYTE_14 = 0x00;
		pObj->I2CMap.EXTENDED_BYTE_15 = 0x8F;
		pObj->I2CMap.EXTENDED_BYTE_16 = 0x00;
		pObj->I2CMap.EXTENDED_BYTE_17 = 0x00;
		pObj->I2CMap.EXTENDED_BYTE_18 = 0x00;
		pObj->I2CMap.EXTENDED_BYTE_19 = 0x00;
		pObj->I2CMap.EXTENDED_BYTE_20 = 0x20;	// Force_Lock = '1'
		pObj->I2CMap.EXTENDED_BYTE_21 = 0x33;
		pObj->I2CMap.EXTENDED_BYTE_22 = 0x48;
		pObj->I2CMap.EXTENDED_BYTE_23 = 0xB0;
#if (0)
        if (TDA18271Write(pObj,0x00,39) != True)
			return TMBSL_ERR_IIC_ERR;
#else
        if (TDA18271Write(pObj,0,16) != True)
			return TMBSL_ERR_IIC_ERR;
        if (TDA18271Write(pObj,16,16) != True)
			return TMBSL_ERR_IIC_ERR;
        if (TDA18271Write(pObj,32,7) != True)
			return TMBSL_ERR_IIC_ERR;
#endif

		//----------------------
		// AGC1 & AGC2 gains setup
		//----------------------
		// AGC1_Gain_do
		// update & write EXTENDED_BYTE_17
		pObj->I2CMap.EXTENDED_BYTE_17 = 0x00;	// set gain_do address
		if (TDA18271Write(pObj,0x20,1) != True)
			return TMBSL_ERR_IIC_ERR;
		pObj->I2CMap.EXTENDED_BYTE_17 = 0x03;	// keep gain_do address, set gain_do 
		if (TDA18271Write(pObj,0x20,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// AGC1_Gain_up
		// update & write EXTENDED_BYTE_17
		pObj->I2CMap.EXTENDED_BYTE_17 = 0x43;	// set gain_up address, keep gain_do 
		if (TDA18271Write(pObj,0x20,1) != True)
			return TMBSL_ERR_IIC_ERR;
		pObj->I2CMap.EXTENDED_BYTE_17 = 0x4C;	// keep gain_up address, set gain_up 
		if (TDA18271Write(pObj,0x20,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// AGC2_Gain_do
		// update & write EXTENDED_BYTE_20
		pObj->I2CMap.EXTENDED_BYTE_20 = 0xA0;	// set gain_do address 
		if (TDA18271Write(pObj,0x23,1) != True)
			return TMBSL_ERR_IIC_ERR;
		pObj->I2CMap.EXTENDED_BYTE_20 = 0xA7;	// keep gain_do address, set gain_do 
		if (TDA18271Write(pObj,0x23,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// AGC2_Gain_up
		// update & write EXTENDED_BYTE_20
		pObj->I2CMap.EXTENDED_BYTE_20 = 0xE7;	// set gain_up address, keep gain_do 
		if (TDA18271Write(pObj,0x23,1) != True)
			return TMBSL_ERR_IIC_ERR;
		pObj->I2CMap.EXTENDED_BYTE_20 = 0xEC;	// keep gain_up address, set gain_up 
		if (TDA18271Write(pObj,0x23,1) != True)
			return TMBSL_ERR_IIC_ERR;

		//----------------------
		// image rejection calibration
		//----------------------		
		//
		//------- low band calibration -------
		//
		// update & write bytes 0x05 to 0x0F
		pObj->I2CMap.EASY_PROG_BYTE_3 = 0x1F;
		pObj->I2CMap.EASY_PROG_BYTE_4 = 0x66;
		pObj->I2CMap.EASY_PROG_BYTE_5 = 0x81;
		pObj->I2CMap.CAL_POST_DIV_BYTE = 0xCC;
		pObj->I2CMap.CAL_DIV_BYTE_1 = 0x6C;
		pObj->I2CMap.CAL_DIV_BYTE_2 = 0x00;
		pObj->I2CMap.CAL_DIV_BYTE_3 = 0x00;
		pObj->I2CMap.MAIN_POST_DIV_BYTE = 0xCD;
		pObj->I2CMap.MAIN_DIV_BYTE_1 = 0x77;
		pObj->I2CMap.MAIN_DIV_BYTE_2 = 0x08;
		pObj->I2CMap.MAIN_DIV_BYTE_3 = 0x00;
		if (TDA18271Write(pObj,0x05,11) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait 5 ms for pll locking
		if (TDA18271Wait(pObj,5) == False)
			return TM_FALSE;

		// update & write byte EASY_PROG_BYTE_1
		pObj->I2CMap.EASY_PROG_BYTE_1 = 0xC6;
		if (TDA18271Write(pObj,0x03,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait x ms for wanted low measurement (default 5 ms)
		if (TDA18271Wait(pObj,(UInt16)((pObj->Config.uPROTOCOLWAIT & 0xFF000000) >> 24)) == False)
			return TM_FALSE;

		// update & write bytes 0x05 to 0x0B
		pObj->I2CMap.EASY_PROG_BYTE_3 = 0x1F;
		pObj->I2CMap.EASY_PROG_BYTE_4 = 0x66;
		pObj->I2CMap.EASY_PROG_BYTE_5 = 0x85;
		pObj->I2CMap.CAL_POST_DIV_BYTE = 0xCB;
		pObj->I2CMap.CAL_DIV_BYTE_1 = 0x66;
		pObj->I2CMap.CAL_DIV_BYTE_2 = 0x70;
		pObj->I2CMap.CAL_DIV_BYTE_3 = 0x00;
		if (TDA18271Write(pObj,0x05,7) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait 5 ms for pll locking
		if (TDA18271Wait(pObj,5) == False)
			return TM_FALSE;
	
		// update & write byte EASY_PROG_BYTE_2
		pObj->I2CMap.EASY_PROG_BYTE_2 = 0xDF;
		if (TDA18271Write(pObj,0x04,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait x ms for image low optimization completion (default 30 ms)
		if (TDA18271Wait(pObj,(UInt16)((pObj->Config.uPROTOCOLWAIT & 0xFF0000) >> 16)) == False)
			return TM_FALSE;

		//
		//------- mid band calibration -------
		//
		// update & write bytes 0x05 to 0x0F
		pObj->I2CMap.EASY_PROG_BYTE_3 = 0x1F;
		pObj->I2CMap.EASY_PROG_BYTE_4 = 0x66;
		pObj->I2CMap.EASY_PROG_BYTE_5 = 0x82;
		pObj->I2CMap.CAL_POST_DIV_BYTE = 0xA8;
		pObj->I2CMap.CAL_DIV_BYTE_1 = 0x66;
		pObj->I2CMap.CAL_DIV_BYTE_2 = 0x00;
		pObj->I2CMap.CAL_DIV_BYTE_3 = 0x00;
		pObj->I2CMap.MAIN_POST_DIV_BYTE = 0xA9;
		pObj->I2CMap.MAIN_DIV_BYTE_1 = 0x73;
		pObj->I2CMap.MAIN_DIV_BYTE_2 = 0x1A;
		pObj->I2CMap.MAIN_DIV_BYTE_3 = 0x00;
		if (TDA18271Write(pObj,0x05,11) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait 5 ms for pll locking
		if (TDA18271Wait(pObj,5) == False)
			return TM_FALSE;

		// update & write byte EASY_PROG_BYTE_1
		pObj->I2CMap.EASY_PROG_BYTE_1 = 0xC6;
		if (TDA18271Write(pObj,0x03,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait x ms for wanted mid measurement (default 5 ms)
		if (TDA18271Wait(pObj,(UInt16)((pObj->Config.uPROTOCOLWAIT & 0xFF000000) >> 24)) == False)
			return TM_FALSE;

		// update & write bytes 0x05 to 0x0B
		pObj->I2CMap.EASY_PROG_BYTE_3 = 0x1F;
		pObj->I2CMap.EASY_PROG_BYTE_4 = 0x66;
		pObj->I2CMap.EASY_PROG_BYTE_5 = 0x86;
		pObj->I2CMap.CAL_POST_DIV_BYTE = 0xA8;
		pObj->I2CMap.CAL_DIV_BYTE_1 = 0x66;
		pObj->I2CMap.CAL_DIV_BYTE_2 = 0xA0;
		pObj->I2CMap.CAL_DIV_BYTE_3 = 0x00;
		if (TDA18271Write(pObj,0x05,7) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait 5 ms for pll locking
		if (TDA18271Wait(pObj,5) == False)
			return TM_FALSE;
	
		// update & write byte EASY_PROG_BYTE_2
		pObj->I2CMap.EASY_PROG_BYTE_2 = 0xDF;
		if (TDA18271Write(pObj,0x04,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait x ms for image mid optimization completion (default 30 ms)
		if (TDA18271Wait(pObj,(UInt16)((pObj->Config.uPROTOCOLWAIT & 0xFF0000) >> 16)) == False)
			return TM_FALSE;
		
		//
		//------- high band calibration -------
		//
		// update & write bytes 0x05 to 0x0F
		pObj->I2CMap.EASY_PROG_BYTE_3 = 0x1F;
		pObj->I2CMap.EASY_PROG_BYTE_4 = 0x66;
		pObj->I2CMap.EASY_PROG_BYTE_5 = 0x83;
		pObj->I2CMap.CAL_POST_DIV_BYTE = 0x98;
		pObj->I2CMap.CAL_DIV_BYTE_1 = 0x65;
		pObj->I2CMap.CAL_DIV_BYTE_2 = 0x00;
		pObj->I2CMap.CAL_DIV_BYTE_3 = 0x00;
		pObj->I2CMap.MAIN_POST_DIV_BYTE = 0x99;
		pObj->I2CMap.MAIN_DIV_BYTE_1 = 0x71;
		pObj->I2CMap.MAIN_DIV_BYTE_2 = 0xCD;
		pObj->I2CMap.MAIN_DIV_BYTE_3 = 0x00;
		if (TDA18271Write(pObj,0x05,11) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait 5 ms for pll locking
		if (TDA18271Wait(pObj,5) == False)
			return TM_FALSE;

		// update & write byte EASY_PROG_BYTE_1
		pObj->I2CMap.EASY_PROG_BYTE_1 = 0xC6;
		if (TDA18271Write(pObj,0x03,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait x ms for wanted high measurement (default 5 ms)
		if (TDA18271Wait(pObj,(UInt16)((pObj->Config.uPROTOCOLWAIT & 0xFF000000) >> 24)) == False)
			return TM_FALSE;

		// update & write bytes 0x05 to 0x0B
		pObj->I2CMap.EASY_PROG_BYTE_3 = 0x1F;
		pObj->I2CMap.EASY_PROG_BYTE_4 = 0x66;
		pObj->I2CMap.EASY_PROG_BYTE_5 = 0x87;
		pObj->I2CMap.CAL_POST_DIV_BYTE = 0x98;
		pObj->I2CMap.CAL_DIV_BYTE_1 = 0x65;
		pObj->I2CMap.CAL_DIV_BYTE_2 = 0x50;
		pObj->I2CMap.CAL_DIV_BYTE_3 = 0x00;
		if (TDA18271Write(pObj,0x05,7) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait 5 ms for pll locking
		if (TDA18271Wait(pObj,5) == False)
			return TM_FALSE;
	
		// update & write byte EASY_PROG_BYTE_2
		pObj->I2CMap.EASY_PROG_BYTE_2 = 0xDF;
		if (TDA18271Write(pObj,0x04,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait x ms for image high optimization completion (default 30 ms)
		if (TDA18271Wait(pObj,(UInt16)((pObj->Config.uPROTOCOLWAIT & 0xFF0000) >> 16)) == False)
			return TM_FALSE;

		// update & write byte EASY_PROG_BYTE_4
		pObj->I2CMap.EASY_PROG_BYTE_4 = 0x64;
		if (TDA18271Write(pObj,0x06,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// update & write byte EASY_PROG_BYTE_1
		pObj->I2CMap.EASY_PROG_BYTE_1 = 0xC6;
		if (TDA18271Write(pObj,0x03,1) != True)
			return TMBSL_ERR_IIC_ERR;
	}

	//----------------------
	// RF tracking filter calibration
	//----------------------
	if (((pObj->Config.uPROTOCOLSTEP & 0x08) >> 3) == 0x01)
	{
		// search for BP_Filter corresponding to uRF
		do uCounter ++;
		while (pObj->Config.uRF > pObj->Config.BP_FILTER_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_BP_FILTER_NB_ROWS);
		pObj->I2CMap.BP_Filter = (UInt8)pObj->Config.BP_FILTER_Map[uCounter - 1].uBP_Filter;
		
		// write byte EASY_PROG_BYTE_1
		if (TDA18271Write(pObj,0x03,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// update & write byte EXTENDED_BYTE_4
		pObj->I2CMap.EXTENDED_BYTE_4 = (pObj->I2CMap.EXTENDED_BYTE_4 & 0x07) | 0x60;
		if (TDA18271Write(pObj,0x13,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// update & write byte EXTENDED_BYTE_7
		pObj->I2CMap.EXTENDED_BYTE_7 = 0x60;
		if (TDA18271Write(pObj,0x16,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// update & write byte EXTENDED_BYTE_14
		pObj->I2CMap.EXTENDED_BYTE_14 = 0x00;
		if (TDA18271Write(pObj,0x1D,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// update & write byte EXTENDED_BYTE_20
		pObj->I2CMap.EXTENDED_BYTE_20 = 0xCC;
		if (TDA18271Write(pObj,0x23,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// set CAL_Mode to RF tracking filter calibration
		pObj->I2CMap.CAL_Mode = 0x03;

		// calculate CAL PLL
		// CAL LO Frequency = beginning of the channel in analog / channel center frequency + bandwith/2 in digital
		if (TDA18271CalcCALPLL(pObj, (pObj->StandardMode > 2) && (pObj->StandardMode < 11) ? 
			pObj->Config.uRF - 1250000 : pObj->Config.uRF + (pObj->Config.uBW/2)) == False)
			return TM_FALSE;
    
		// calculate MAIN PLL
		// MAIN LO Frequency = beginning of the channel + 1MHz in analog / channel center frequency + bandwith/2 + 1MHz in digital
		if (TDA18271CalcMAINPLL(pObj,(pObj->StandardMode > 2) && (pObj->StandardMode < 11) ? 
			pObj->Config.uRF - 250000 : pObj->Config.uRF + (pObj->Config.uBW/2) + 1000000) == False)
			return TM_FALSE;
    
		// write bytes 0x05 to 0x0F
		if (TDA18271Write(pObj,0x05,11) != True)
			return TMBSL_ERR_IIC_ERR;
    
		// wait 5 ms for RF tracking filter calibration initialisation
		if (TDA18271Wait(pObj,5) == False)
			return TM_FALSE;
   
		// search for K,M,CO for RF Calibration, corresponding to uRF
		uCounter=0;
		do uCounter ++;
		while (pObj->Config.uRF > pObj->Config.RF_CAL_KMCO_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_CAL_KMCO_NB_ROWS);		
		
		// update & write EXTENDED_BYTE_13
		pObj->I2CMap.EXTENDED_BYTE_13 = (UInt8)((pObj->I2CMap.EXTENDED_BYTE_13 & 0x83) | pObj->Config.RF_CAL_KMCO_Map[uCounter - 1].uK << 4 | pObj->Config.RF_CAL_KMCO_Map[uCounter - 1].uM << 2 );
		if (TDA18271Write(pObj,0x1C,1) != True)
			return TMBSL_ERR_IIC_ERR;
		
		/*// update & write EXTENDED_BYTE_23
		pObj->I2CMap.EXTENDED_BYTE_23 = (UInt8)((pObj->I2CMap.EXTENDED_BYTE_23 & 0xCF) | pObj->Config.RF_CAL_KMCO_Map[uCounter - 1].uCOAmpl << 4);
		if (TDA18271Write(pObj,0x26,1) != True)
			return TMBSL_ERR_IIC_ERR;*/

		// search for RF_BAND corresponding to uRF
		uCounter = 0;
		do uCounter ++;
		while (pObj->Config.uRF > pObj->Config.RF_BAND_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_BAND_NB_ROWS);
		pObj->I2CMap.RF_Band = (UInt8)pObj->Config.RF_BAND_Map[uCounter - 1].uRF_Band;

		// search for Gain_Taper corresponding to uRF
		uCounter = 0;
		do uCounter ++;
		while (pObj->Config.uRF > pObj->Config.GAIN_TAPER_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_GAIN_TAPER_NB_ROWS);
		pObj->I2CMap.Gain_Taper = (UInt8)pObj->Config.GAIN_TAPER_Map[uCounter - 1].uGain_Taper;

		// write byte EASY_PROG_BYTE_2
		if (TDA18271Write(pObj,0x04,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// write byte EASY_PROG_BYTE_1
		if (TDA18271Write(pObj,0x03,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// write byte EASY_PROG_BYTE_2
		if (TDA18271Write(pObj,0x04,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// write byte EASY_PROG_BYTE_1
		if (TDA18271Write(pObj,0x03,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// update & write byte EXTENDED_BYTE_4
		pObj->I2CMap.EXTENDED_BYTE_4 = (pObj->I2CMap.EXTENDED_BYTE_4 & 0x07) | 0x40;
		if (TDA18271Write(pObj,0x13,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// update & write byte EXTENDED_BYTE_7
		pObj->I2CMap.EXTENDED_BYTE_7 = 0x40;
		if (TDA18271Write(pObj,0x16,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait 10 ms for pll locking
		if (TDA18271Wait(pObj,10) == False)
			return TM_FALSE;

		// update & write byte EXTENDED_BYTE_20
		pObj->I2CMap.EXTENDED_BYTE_20 = 0xEC;
		if (TDA18271Write(pObj,0x23,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// wait x ms for for RF tracking filter calibration completion (default 60 ms)
		if (TDA18271Wait(pObj,(UInt16)((pObj->Config.uPROTOCOLWAIT & 0xFF00) >> 8)) == False)
			return TM_FALSE;

		// set CAL_Mode to normal mode
		pObj->I2CMap.CAL_Mode = 0x00;

		// write byte EASY_PROG_BYTE_4
		if (TDA18271Write(pObj,0x06,1) != True)
			return TMBSL_ERR_IIC_ERR;

		// write byte EASY_PROG_BYTE_1
		if (TDA18271Write(pObj,0x03,1) != True)
			return TMBSL_ERR_IIC_ERR;
	}
    
	//----------------------
	// RF tracking filter correction for VHF_Low band
	//----------------------
	if ((((pObj->Config.uPROTOCOLSTEP & 0x04) >> 2) == 0x01) && (uRF <= pObj->Config.RF_CAL_Map[TDA18271_RF_CAL_NB_ROWS - 1].uRF_Max))
	{
		// search for RFC_Cprog corresponding to uRF
		uCounter = 0;
		do uCounter ++;
		while (uRF > pObj->Config.RF_CAL_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_CAL_NB_ROWS);

		// update & write EXTENDED_BYTE_14
		pObj->I2CMap.EXTENDED_BYTE_14 = (UInt8)pObj->Config.RF_CAL_Map[uCounter - 1].uRFC_Cprog;
		if (TDA18271Write(pObj,0x1D,1) != True)
			return TMBSL_ERR_IIC_ERR;
	}

	//----------------------
	// channel configuration
	//----------------------
	if (((pObj->Config.uPROTOCOLSTEP & 0x01) >> 0) == 0x01)
	{	
		if (((pObj->Config.uPROTOCOLSTEP & 0x02) >> 1) == 0x01)
		{	
			// set standard mode to current standard
			tmbslTDA18271SetStandardMode (TunerUnit,pObj->StandardMode);
		}

		// write EXTENDED_BYTE_22
		if (TDA18271Write(pObj,0x25,1) != True)
			return TMBSL_ERR_IIC_ERR;		
  
		// set CAL_Mode to normal mode
		pObj->I2CMap.CAL_Mode = 0x00;

		// set power level indicator to off
		pObj->Config.uPLMODE = 1;
		pObj->I2CMap.Dis_Power_level = 1;

		// set thermometer to off
		pObj->Config.uTMMODE = 0;
		pObj->I2CMap.TM_ON = 0;

		// search for IR_Meas corresponding to wanted frequency
		uIRMeasCounter = 0;
		do uIRMeasCounter ++;
		while (pObj->Config.uRF > pObj->Config.IR_MEAS_Map[uIRMeasCounter - 1].uRF_Max && uIRMeasCounter - 1 < TDA18271_IR_MEAS_NB_ROWS);
		pObj->I2CMap.IR_Meas = uIRMeasCounter + 3;
    
		// calculate MAIN PLL
		if (TDA18271CalcMAINPLL(pObj, pObj->Config.uRF + pObj->Config.uIF) == False)
			return TM_FALSE;

		// write bytes 0x01 to 0x0F
		if (TDA18271Write(pObj,0x01,15) != True)
			return TMBSL_ERR_IIC_ERR;
    
		// wait 5 ms for pll locking
		if (TDA18271Wait(pObj,5) == False)
			return TM_FALSE;

		// read bytes 0x00 to 0x0F
		if (TDA18271Read (pObj,0x00,16) != True)
			return TMBSL_ERR_IIC_ERR;
	}

    return TM_OK;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18271GetRf:
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
tmbslTDA18271GetRf(
    tmUnitSelect_t		TunerUnit,		//  I: Tuner unit number
    UInt32*				pRF				//  O: RF frequency in hertz
	)
{
	ptmTDA18271Object_t		pObj;

    //------------------------------
    // test input parameters
    //------------------------------
    // test the instance number
    if (TunerUnit > TDA18271_MAX_UNITS)
        return TMBSL_ERR_TUNER_BAD_UNIT_NUMBER;

    // test the Object
    if (gTDA18271Instance[TunerUnit].init == False)
        return TMBSL_ERR_TUNER_NOT_INITIALIZED;

	// pObj initialisation
	pObj = &gTDA18271Instance[TunerUnit];

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
//-----------------------------------------------------------------------------
// FUNCTION:    TDA18271Init:
//
// DESCRIPTION: Initialisation of the Tuner
//
// RETURN:      always True
//
// NOTES:       
//-----------------------------------------------------------------------------
//
Bool_
TDA18271Init (
    tmUnitSelect_t			TunerUnit	// I: Tuner Object
    )
{ 
	return True;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271Write
//
// DESCRIPTION: This function writes I2C data in the Tuner
//
// RETURN:      True or False
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
Bool_ 
TDA18271Write(
    ptmTDA18271Object_t	pObj,		// I: Tuner unit number
	UInt8					uSubAddress,// I: sub address
	UInt8					uNbData		// I: nb of data
	)
{
	Bool_	I2CCommResult;

	UInt8	uCounter;
	UInt8*	pI2CMap;
	UInt32	WriteBuffer[TDA18271_NB_BYTES] = {0};
	UInt32*	pWriteBuffer;

	// pI2CMap & pWriteBuffer initialisation
	pI2CMap = &(pObj->I2CMap.ID_BYTE);
	pWriteBuffer = &(WriteBuffer[0]);

	// copy I2CMap data in WriteBuffer
	for (uCounter = 0; uCounter < TDA18271_NB_BYTES; uCounter++)
	{
		*pWriteBuffer = (UInt32)(*pI2CMap);
		pWriteBuffer ++;
		pI2CMap ++;
	}

	/*// activate extended register access if needed
    if ( (uSubAddress + uNbData >= 0x11) && (uNbData > 1) )
    {
        // update & write byte EASY_PROG_BYTE_5
        pObj->I2CMap.Extended_Reg = 0x01;
        I2CCommResult = TDA18271Write(pObj,0x07,1);
    }*/

	// write data in the Tuner
	I2CCommResult = pObj->SystemFunc.SY_Write(	pObj->uHwAddress, 
												uSubAddress,
												uNbData,
												&(WriteBuffer[uSubAddress]) );

	// shift I2CLog content
	TDA18271ShiftLog (pObj,1);

	// copy written data in I2CLog [0]
	for (uCounter = uSubAddress; uCounter < uSubAddress + uNbData; uCounter++)
		pObj->I2CLog [0][uCounter] = WriteBuffer [uCounter];
	
	// set additional values
	pObj->I2CLog [0][TDA18271_NB_BYTES] = pObj->uHwAddress;
	pObj->I2CLog [0][TDA18271_NB_BYTES + 1] = I2CCommResult;

	/*// deactivate extended register access if needed
    if ( (uSubAddress + uNbData >= 0x11) && (uNbData > 1) )
    {
        // update & write byte EASY_PROG_BYTE_5
        pObj->I2CMap.Extended_Reg = 0x00;
		I2CCommResult = TDA18271Write(pObj,0x07,1);
    }*/

	// return value
    return I2CCommResult;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271Read
//
// DESCRIPTION: This function reads I2C data from the Tuner
//
// RETURN:      True or False
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
Bool_ 
TDA18271Read(
    ptmTDA18271Object_t	pObj,		// I: Tuner unit number
	UInt8				uSubAddress,// I: sub address
	UInt8				uNbData		// I: nb of data
	)
{
	Bool_	I2CCommResult;

	UInt8	uCounter;
	UInt8*	pI2CMap;
	UInt32	ReadBuffer[TDA18271_NB_BYTES] = {0};
	UInt32*	pReadBuffer;

	// pI2CMap & pReadBuffer initialisation
	pI2CMap = &(pObj->I2CMap.ID_BYTE) + uSubAddress;
	pReadBuffer = &(ReadBuffer[uSubAddress]);

	// read data from the Tuner
	I2CCommResult = pObj->SystemFunc.SY_Read(	pObj->uHwAddress,
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
	TDA18271ShiftLog (pObj,1);

	// copy readen data in I2CLog [0]
	for (uCounter = uSubAddress; uCounter < uSubAddress + uNbData; uCounter++)
		pObj->I2CLog [0][uCounter] = ReadBuffer [uCounter];
	
	// set additional values
	pObj->I2CLog [0][TDA18271_NB_BYTES] = pObj->uHwAddress + 1;
	pObj->I2CLog [0][TDA18271_NB_BYTES + 1] = I2CCommResult;

	// return value
    return I2CCommResult;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271Wait
//
// DESCRIPTION: This function waits for requested time
//
// RETURN:      True or False
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
Bool_ 
TDA18271Wait(
    ptmTDA18271Object_t		pObj,		//  I: Tuner unit number
    UInt16					wTime		//  I: time to wait for
	)
{
	User_delay( pObj->AFAInfo.demodulator, wTime);

	return True;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271ShiftLog
//
// DESCRIPTION: Shift I2CLog content of wanted lines
//
// RETURN:      True
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
Bool_ 
TDA18271ShiftLog(
    ptmTDA18271Object_t	pObj,	// I: Tuner unit number
	UInt8					uNbRows	// I: nb of lines
	)
{
	UInt8	uRow;
	UInt8	uColumn;
	UInt8	uCounter;
	
	// Shift I2CLog content of wanted lines
	for (uCounter = 0; uCounter < uNbRows; uCounter++)
	{
		for (uRow = TDA18271_LOG_NB_ROWS - 1; uRow > 0; uRow--)
		{
			for (uColumn = 0; uColumn < TDA18271_NB_BYTES + 2; uColumn++)
				pObj->I2CLog [uRow][uColumn] = pObj->I2CLog [uRow - 1][uColumn];
		}

		for (uColumn = 0; uColumn < TDA18271_NB_BYTES + 2; uColumn++)
				pObj->I2CLog [0][uColumn] = 256;
	}

	// Return value
    return True;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271CalcMAINPLL:
//
// DESCRIPTION: Calculate the MAIN fractionnal PLL settings
//
// RETURN:      True or False
//
// NOTES:       This function doesn't write in the tuner
//-------------------------------------------------------------------------------------
//
Bool_
TDA18271CalcMAINPLL (
    ptmTDA18271Object_t		pObj,		// I: tuner Object
    UInt32					uLO			// I: local oscillator frequency in hertz
    )
{	
	UInt8	uCounter = 0;
	UInt32	uDiv;

	// search for MAIN_Post_Div corresponding to uLO
	uCounter = 0;
	do uCounter ++;
	while (uLO > pObj->Config.MAIN_PLL_Map[uCounter - 1].uLO_Max && uCounter < TDA18271_MAIN_PLL_NB_ROWS);
	// Decalage table : MAIN_Post_Div[4] = 0 in table or MAIN_Post_Div[4] = 1
    pObj->I2CMap.MAIN_Post_Div = ((UInt8)pObj->Config.MAIN_PLL_Map[uCounter - 1].uPost_Div) & 0x7F;

	// calculate MAIN_Div
	uDiv = (((UInt32)(pObj->Config.MAIN_PLL_Map[uCounter - 1].uDiv) * (uLO / 1000)) << 7) / 125;
	pObj->I2CMap.MAIN_Div_22_to_16 = (UInt8)(uDiv >> 16) & 0x7F;
	pObj->I2CMap.MAIN_Div_15_to_8 = (UInt8)(uDiv >> 8);
	pObj->I2CMap.MAIN_Div_7_to_0 = (UInt8)(uDiv);

	return True;
}
//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271CalcCALPLL:
//
// DESCRIPTION: Calculate the CAL fractionnal PLL settings
//
// RETURN:      True or False
//
// NOTES:       This function doesn't write in the tuner
//-------------------------------------------------------------------------------------
//
Bool_
TDA18271CalcCALPLL (
    ptmTDA18271Object_t		pObj,		// I: tuner Object
    UInt32					uLO			// I: local oscillator frequency in hertz
    )
{	
	UInt8	uCounter = 0;
	UInt32	uDiv;

	// search for CAL_Post_Div corresponding to uLO
	do uCounter ++;
	while (uLO > pObj->Config.CAL_PLL_Map[uCounter - 1].uLO_Max && uCounter < TDA18271_CAL_PLL_NB_ROWS);
	//CAL_POST_DIV_BYTE[7] = 0 in table or CAL_POST_DIV_BYTE[7]=1 =>(| 0x80)
    pObj->I2CMap.CAL_POST_DIV_BYTE = (UInt8)pObj->Config.CAL_PLL_Map[uCounter - 1].uPost_Div; 
    
    // calculate CAL_Div
	uDiv = (((UInt32)(pObj->Config.CAL_PLL_Map[uCounter - 1].uDiv) * (uLO / 1000)) << 7) / 125;
	pObj->I2CMap.CAL_Div_22_to_16 = (UInt8)(uDiv >> 16) & 0x7F;
	pObj->I2CMap.CAL_Div_15_to_8 = (UInt8)(uDiv >> 8);
	pObj->I2CMap.CAL_Div_7_to_0 = (UInt8)(uDiv);

	return True;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18271CalcRFFilter:
//
// DESCRIPTION: Calculate the RF Filters
//
// RETURN:      True or False
//
// NOTES:       This function doesn't write in the tuner
//-------------------------------------------------------------------------------------
//
Bool_
TDA18271CalcRFFilter (
    ptmTDA18271Object_t		pObj,		// I: tuner Object
    UInt32					uLO			// I: local oscillator frequency in hertz
    )
{	
	UInt8	uCounter = 0;

	// search for BP_Filter corresponding to uRF
	do uCounter ++;
	while (pObj->Config.uRF > pObj->Config.BP_FILTER_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_BP_FILTER_NB_ROWS);
	pObj->I2CMap.BP_Filter = (UInt8)pObj->Config.BP_FILTER_Map[uCounter - 1].uBP_Filter;

	// search for RF_BAND corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (pObj->Config.uRF > pObj->Config.RF_BAND_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_RF_BAND_NB_ROWS);
	pObj->I2CMap.RF_Band = (UInt8)pObj->Config.RF_BAND_Map[uCounter - 1].uRF_Band;

	// search for Gain_Taper corresponding to uRF
	uCounter = 0;
	do uCounter ++;
	while (pObj->Config.uRF > pObj->Config.GAIN_TAPER_Map[uCounter - 1].uRF_Max && uCounter < TDA18271_GAIN_TAPER_NB_ROWS);
	pObj->I2CMap.Gain_Taper = (UInt8)pObj->Config.GAIN_TAPER_Map[uCounter - 1].uGain_Taper;

	return True;
}

//-------------------------------------------------------------------------------------
// TUNER ERRORS TYPES
//
// RETURN:      TM_OK
//              TM_FALSE
//              TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TMBSL_ERR_TUNER_NOT_INITIALIZED
//              TMBSL_ERR_TUNER_BAD_PARAMETER
//              TMBSL_ERR_TUNER_NOT_SUPPORTED
//              TM_ERR_IIC_ERR
//	
//-------------------------------------------------------------------------------------
//