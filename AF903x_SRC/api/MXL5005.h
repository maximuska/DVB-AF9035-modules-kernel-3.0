/**
 * MXL5005.h : main header file for the MXL5005 DLL
 */
#pragma once

#include "Common.h"
#ifdef _MXL_INTERNAL
#include "Common_MXL.h"
#endif

void InitTunerControls( Tuner_struct *Tuner) ;

WORD MXL_BlockInit( Tuner_struct *Tuner ) ;

WORD MXL5005_RegisterInit (Tuner_struct * Tuner) ;
WORD MXL5005_ControlInit (Tuner_struct *Tuner) ;

#ifdef _MXL_INTERNAL
	WORD MXL5005_MXLControlInit(Tuner_struct *Tuner) ;
#endif

WORD MXL5005_TunerConfig(Tuner_struct *Tuner, 
	BYTE	Mode,		/* 0: Analog Mode ; 1: Digital Mode */
	BYTE	IF_mode,	/* for Analog Mode, 0: zero IF; 1: low IF */
	DWORD	Bandwidth,	/* filter  channel bandwidth (6, 7, 8) */
	DWORD	IF_out,		/* Desired IF Out Frequency */
	DWORD	Fxtal,		/* XTAL Frequency */
	BYTE	AGC_Mode,	/* AGC Mode - Dual AGC: 0, Single AGC: 1 */
	WORD	TOP,        /* 0: Dual AGC; Value: take over point */
	WORD	IF_OUT_LOAD,/* IF Out Load Resistor (200 / 300 Ohms) */
	BYTE	CLOCK_OUT, 	/* 0: turn off clock out; 1: turn on clock out */
	BYTE	DIV_OUT,	/* 4MHz or 16MHz */
	BYTE	CAPSELECT, 	/* 0: disable On-Chip pulling cap; 1: enable */
	BYTE	EN_RSSI, 	/* 0: disable RSSI; 1: enable RSSI */
	BYTE		Mod_Type,	/** Modulation Type; */
						/** 0 - Default;		1 - DVB-T;	2 - ATSC;	3 - QAM; 4 - Analog Cable */
	BYTE		TF_Type		/** Tracking Filter Type */
						/** 0 - Default; 1 - Off; 2 - Type C; 3 - Type C-H */
	) ;

void MXL_SynthIFLO_Calc(Tuner_struct *Tuner) ;
void MXL_SynthRFTGLO_Calc(Tuner_struct *Tuner) ;
WORD MXL_RegWrite(Tuner_struct *Tuner, BYTE RegNum, BYTE RegVal) ;
WORD MXL_RegRead(Tuner_struct *Tuner, BYTE RegNum, BYTE *RegVal) ;
WORD MXL_ControlWrite(Tuner_struct *Tuner, WORD ControlNum, DWORD value) ;
WORD MXL_ControlWrite_Group(Tuner_struct *Tuner, WORD ControlNum, DWORD value, WORD controlGroup) ;
WORD MXL_ControlRead(Tuner_struct *Tuner, WORD ControlNum, DWORD * value) ;
WORD MXL_ControlRegRead(Tuner_struct *Tuner, WORD ControlNum, BYTE *RegNum, int * count) ;
void MXL_RegWriteBit(Tuner_struct *Tuner, BYTE address, BYTE bit, BYTE bitVal);
WORD MXL_IFSynthInit( Tuner_struct * Tuner ) ;
WORD MXL_TuneRF(Tuner_struct *Tuner, DWORD RF_Freq) ; 
WORD MXL_OverwriteICDefault( Tuner_struct *Tuner) ;
WORD MXL_SetGPIO(Tuner_struct *Tuner, BYTE GPIO_Num, BYTE GPIO_Val) ;
DWORD MXL_Ceiling( DWORD value, DWORD resolution ) ;
DWORD MXL_GetXtalInt(DWORD Xtal_Freq) ;

WORD MXL_GetInitRegister(Tuner_struct *Tuner, BYTE * RegNum, BYTE *RegVal, int *count) ;
WORD MXL_GetCHRegister(Tuner_struct *Tuner, BYTE * RegNum, BYTE *RegVal, int *count) ;
WORD MXL_GetCHRegister_ZeroIF(Tuner_struct *Tuner, BYTE * RegNum, BYTE *RegVal, int *count) ;
WORD MXL_GetCHRegister_LowIF(Tuner_struct *Tuner, BYTE * RegNum, BYTE *RegVal, int *count) ;
WORD MXL_GetMasterControl(BYTE *MasterReg, int state) ;

#ifdef _MXL_PRODUCTION
WORD MXL_VCORange_Test(Tuner_struct *Tuner, int VCO_Range) ;
WORD MXL_Hystersis_Test(Tuner_struct *Tuner, int Hystersis) ;
#endif


