/** MXL5005.cpp : Defines the initialization routines for the DLL. */
/** 2.6.14 */

#include "MXL5005.h"


void InitTunerControls(Tuner_struct *Tuner)
{
	MXL5005_RegisterInit(Tuner);
	MXL5005_ControlInit(Tuner);
#ifdef _MXL_INTERNAL
	MXL5005_MXLControlInit(Tuner);
#endif
}

/**
 *                                                                           
 * Function:       MXL_ConfigTuner                                           
 *                                                                           
 * Description:    Configure MXL5005Tuner structure for desired              
 *                 Channel Bandwidth/Channel Frequency                       
 *                                                                           
 *                                                                           
 * Functions used:                                                           
 *                 MXL_SynthIFLO_Calc                                        
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner_struct: structure defined at higher level           
 *                 Mode:         Tuner Mode (Analog/Digital)                 
 *                 IF_Mode:      IF Mode ( Zero/Low )                        
 *				   Bandwidth:    Filter Channel Bandwidth (in Hz)            
 *                 IF_out:       Desired IF out Frequency (in Hz)            
 *                 Fxtal:        Crystal Frerquency (in Hz)                  
 *		           TOP:			 0: Dual AGC; Value: take over point         
 *				   IF_OUT_LOAD:	 IF out load resistor (200/300 Ohms)		 
 *				   CLOCK_OUT:	 0: Turn off clock out; 1: turn on clock out 
 *				   DIV_OUT:      0: Div-1; 1: Div-4							 
 *				   CAPSELECT:	 0: Disable On-chip pulling cap; 1: Enable   
 *				   EN_RSSI:		 0: Disable RSSI; 1: Enable RSSI			 
 *                                                                           
 * Outputs:                                                                  
 *                 Tuner                                                     
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful                                            
 *               > 0 : Failed                                                
 *                                                                           
 */
WORD MXL5005_TunerConfig(Tuner_struct *Tuner, 
		BYTE	Mode,		 /* 0: Analog Mode; 1: Digital Mode            */
		BYTE	IF_mode,	 /* for Analog Mode, 0: zero IF; 1: low IF      */
		DWORD	Bandwidth,	 /* filter  channel bandwidth (6, 7, 8)         */
		DWORD	IF_out,		 /* Desired IF Out Frequency                    */
		DWORD	Fxtal,		 /* XTAL Frequency                              */
		BYTE	AGC_Mode,	 /* AGC Mode - Dual AGC: 0, Single AGC: 1       */
		WORD	TOP,         /* 0: Dual AGC; Value: take over point         */
		WORD	IF_OUT_LOAD, /* IF Out Load Resistor (200 / 300 Ohms)       */
		BYTE	CLOCK_OUT, 	 /* 0: turn off clock out; 1: turn on clock out */
		BYTE	DIV_OUT,	 /* 0: Div-1; 1: Div-4                          */
		BYTE	CAPSELECT, 	 /* 0: disable On-Chip pulling cap; 1: enable   */
		BYTE	EN_RSSI, 	 /* 0: disable RSSI; 1: enable RSSI             */
		BYTE	Mod_Type,	 /* Modulation Type;                            */
							/* 0 - Default;	1 - DVB-T; 2 - ATSC; 3 - QAM; 4 - Analog Cable */
		BYTE		TF_Type		/* Tracking Filter */
							/* 0 - Default; 1 - Off; 2 - Type C; 3 - Type C-H */
		) 
{
	WORD status = 0;

	Tuner->Mode = Mode;
	Tuner->IF_Mode = IF_mode;
	Tuner->Chan_Bandwidth = Bandwidth;
	Tuner->IF_OUT = IF_out;
	Tuner->Fxtal = Fxtal;
	Tuner->AGC_Mode = AGC_Mode;
	Tuner->TOP = TOP;
	Tuner->IF_OUT_LOAD = IF_OUT_LOAD;
	Tuner->CLOCK_OUT = CLOCK_OUT;
	Tuner->DIV_OUT = DIV_OUT;
	Tuner->CAPSELECT = CAPSELECT;
	Tuner->EN_RSSI = EN_RSSI;
	Tuner->Mod_Type = Mod_Type;
	Tuner->TF_Type = TF_Type;

	/**
	 *	Initialize all the controls and registers
	 */
	InitTunerControls (Tuner);
	/**
	 * Synthesizer LO frequency calculation
	 */
	MXL_SynthIFLO_Calc( Tuner );

	return status;
}

/**
 *                                                                           
 * Function:       MXL_SynthIFLO_Calc                                        
 *                                                                           
 * Description:    Calculate Internal IF-LO Frequency                        
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Functions used:                                                           
 *                 NONE                                                      
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner_struct: structure defined at higher level           
 *                                                                           
 * Outputs:                                                                  
 *                 Tuner                                                     
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful                                            
 *               > 0 : Failed                                                
 *                                                                           
 */
void MXL_SynthIFLO_Calc(Tuner_struct *Tuner)
{
	if (Tuner->Mode == 1) /* Digital Mode */
	{
		Tuner->IF_LO = Tuner->IF_OUT;
	}
	else /* Analog Mode */
	{
		if(Tuner->IF_Mode == 0) /* Analog Zero IF mode */
		{
			Tuner->IF_LO = Tuner->IF_OUT + 400000;
		}
		else /* Analog Low IF mode */
		{
			Tuner->IF_LO = Tuner->IF_OUT + Tuner->Chan_Bandwidth/2;
		}
	}
}

/**
 *                                                                           
 * Function:       MXL_SynthRFTGLO_Calc                                      
 *                                                                           
 * Description:    Calculate Internal RF-LO frequency and                    
 *                 internal Tone-Gen(TG)-LO frequency                        
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Functions used:                                                           
 *                 NONE                                                      
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner_struct: structure defined at higher level           
 *                                                                           
 * Outputs:                                                                  
 *                 Tuner                                                     
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful                                            
 *               > 0 : Failed                                                
 *                                                                           
 */
void MXL_SynthRFTGLO_Calc(Tuner_struct *Tuner)
{
	if (Tuner->Mode == 1) /* Digital Mode */
	{
			/** remove 20.48MHz setting for 2.6.10 */
			Tuner->RF_LO = Tuner->RF_IN;
			Tuner->TG_LO = Tuner->RF_IN - 750000;  /** change for 2.6.6 */
	}
	else /* Analog Mode */
	{
		if(Tuner->IF_Mode == 0) /* Analog Zero IF mode */
		{
			Tuner->RF_LO = Tuner->RF_IN - 400000;
			Tuner->TG_LO = Tuner->RF_IN - 1750000;
		}
		else /* Analog Low IF mode */
		{
			Tuner->RF_LO = Tuner->RF_IN - Tuner->Chan_Bandwidth/2;
			Tuner->TG_LO = Tuner->RF_IN - Tuner->Chan_Bandwidth + 500000;
		}
	}
}

/**
 *                                                                           
 * Function:       MXL_OverwriteICDefault                                    
 *                                                                           
 * Description:    Overwrite the Default Register Setting                    
 *                                                                           
 *                                                                           
 * Functions used:                                                           
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner_struct: structure defined at higher level           
 * Outputs:                                                                  
 *                 Tuner                                                     
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful                                            
 *               > 0 : Failed                                                
 *                                                                           
 */
WORD MXL_OverwriteICDefault( Tuner_struct *Tuner)
{
	WORD status = 0;

	status += MXL_ControlWrite(Tuner, OVERRIDE_1, 1);
	status += MXL_ControlWrite(Tuner, OVERRIDE_2, 1);
	status += MXL_ControlWrite(Tuner, OVERRIDE_3, 1);
	status += MXL_ControlWrite(Tuner, OVERRIDE_4, 1);

	return status;
}

/**
 *                                                                           
 * Function:       MXL_BlockInit                                             
 *                                                                           
 * Description:    Tuner Initialization as a function of 'User Settings'     
 *                  * User settings in Tuner strcuture must be assigned      
 *                    first                                                  
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Functions used:                                                           
 *                 Tuner_struct: structure defined at higher level           
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner       : Tuner structure defined at higher level     
 *                                                                           
 * Outputs:                                                                  
 *                 Tuner                                                     
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful                                            
 *               > 0 : Failed                                                
 *                                                                           
 */
WORD MXL_BlockInit( Tuner_struct *Tuner ) 
{
	WORD status = 0;

	status += MXL_OverwriteICDefault(Tuner);

	/** 
	 * Downconverter Control
	 */
	status += MXL_ControlWrite(Tuner, DN_IQTN_AMP_CUT, Tuner->Mode ? 1 : 0);

	/**
	 * Filter Control
	 */
	status += MXL_ControlWrite(Tuner, BB_MODE,          Tuner->Mode ? 0 : 1);
	status += MXL_ControlWrite(Tuner, BB_BUF,           Tuner->Mode ? 3 : 2);
	status += MXL_ControlWrite(Tuner, BB_BUF_OA,        Tuner->Mode ? 1 : 0);

	status += MXL_ControlWrite(Tuner, BB_IQSWAP,        Tuner->Mode ? 0 : 1);
	status += MXL_ControlWrite(Tuner, BB_INITSTATE_DLPF_TUNE,  0);

	/* Initialize Low-Pass Filter */
	if (Tuner->Mode) { /* Digital Mode */
		switch (Tuner->Chan_Bandwidth) {
			case 8000000:
				status += MXL_ControlWrite(Tuner, BB_DLPF_BANDSEL, 0);
				break;
			case 7000000:
				status += MXL_ControlWrite(Tuner, BB_DLPF_BANDSEL, 2);
				break;
			case 6000000:
				status += MXL_ControlWrite(Tuner, BB_DLPF_BANDSEL, 3);
				break;
		}
	} else { /* Analog Mode */
		switch (Tuner->Chan_Bandwidth) {
			case 8000000:													/* Low Zero	 */
				status += MXL_ControlWrite(Tuner, BB_ALPF_BANDSELECT, (Tuner->IF_Mode ? 0 : 3));
				break;
			case 7000000:
				status += MXL_ControlWrite(Tuner, BB_ALPF_BANDSELECT, (Tuner->IF_Mode ? 1 : 4));
				break;
			case 6000000:
				status += MXL_ControlWrite(Tuner, BB_ALPF_BANDSELECT, (Tuner->IF_Mode ? 2 : 5));
				break;
		}
	}

	/**
	 * Charge Pump Control
	 */
	status += MXL_ControlWrite(Tuner, RFSYN_CHP_GAIN,      Tuner->Mode ? 5 : 8);
	status += MXL_ControlWrite(Tuner, RFSYN_EN_CHP_HIGAIN, Tuner->Mode ?  1 :  1);
	status += MXL_ControlWrite(Tuner, EN_CHP_LIN_B, Tuner->Mode ? 0 : 0);

	/** 
	 * AGC TOP Control
	 */
	if (Tuner->AGC_Mode == 0) /* Dual AGC */
	{
		status += MXL_ControlWrite(Tuner, AGC_IF, 15);
		status += MXL_ControlWrite(Tuner, AGC_RF, 15);
	}
	else /*  Single AGC Mode */
		status += MXL_ControlWrite(Tuner, AGC_RF, Tuner->Mode? 15 : 12);


	if (Tuner->TOP == 55) /* TOP == 5.5 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0x0);

	if (Tuner->TOP == 72) /* TOP == 7.2 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0x1);

	if (Tuner->TOP == 92) /* TOP == 9.2 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0x2);

	if (Tuner->TOP == 110) /* TOP == 11.0 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0x3);

	if (Tuner->TOP == 129) /* TOP == 12.9 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0x4);

	if (Tuner->TOP == 147) /* TOP == 14.7 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0x5);

	if (Tuner->TOP == 168) /* TOP == 16.8 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0x6);

	if (Tuner->TOP == 194) /* TOP == 19.4 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0x7);

	if (Tuner->TOP == 212) /* TOP == 21.2 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0x9);

	if (Tuner->TOP == 232) /* TOP == 23.2 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0xA);

	if (Tuner->TOP == 252) /* TOP == 25.2 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0xB);

	if (Tuner->TOP == 271) /* TOP == 27.1 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0xC);

	if (Tuner->TOP == 292) /* TOP == 29.2 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0xD);

	if (Tuner->TOP == 317) /* TOP == 31.7 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0xE);

	if (Tuner->TOP == 349) /* TOP == 34.9 */
		status += MXL_ControlWrite(Tuner, AGC_IF, 0xF);

	/**
	 * IF Synthesizer Control
	 */
	status += MXL_IFSynthInit( Tuner );

	/**
	 * IF UpConverter Control
	 */
	if (Tuner->IF_OUT_LOAD == 200)
	{
		status += MXL_ControlWrite(Tuner, DRV_RES_SEL, 6);
		status += MXL_ControlWrite(Tuner, I_DRIVER, 2);
	}
	if (Tuner->IF_OUT_LOAD == 300)
	{
		status += MXL_ControlWrite(Tuner, DRV_RES_SEL, 4);
		status += MXL_ControlWrite(Tuner, I_DRIVER, 1);
	}

	/**
	 * Anti-Alias Filtering Control
	 */
	/* initialise Anti-Aliasing Filter */
	if (Tuner->Mode) { /* Digital Mode */
		if (Tuner->IF_OUT >= 4000000UL && Tuner->IF_OUT <= 6280000UL) {
			status += MXL_ControlWrite(Tuner, EN_AAF, 1);
			status += MXL_ControlWrite(Tuner, EN_3P, 1);
			status += MXL_ControlWrite(Tuner, EN_AUX_3P, 1);
			status += MXL_ControlWrite(Tuner, SEL_AAF_BAND, 0);
		}
		if ((Tuner->IF_OUT == 36125000UL) || (Tuner->IF_OUT == 36150000UL)) {
			status += MXL_ControlWrite(Tuner, EN_AAF, 1);
			status += MXL_ControlWrite(Tuner, EN_3P, 1);
			status += MXL_ControlWrite(Tuner, EN_AUX_3P, 1);
			status += MXL_ControlWrite(Tuner, SEL_AAF_BAND, 1);
		}
		if (Tuner->IF_OUT > 36150000UL) {
			status += MXL_ControlWrite(Tuner, EN_AAF, 0);
			status += MXL_ControlWrite(Tuner, EN_3P, 1);
			status += MXL_ControlWrite(Tuner, EN_AUX_3P, 1);
			status += MXL_ControlWrite(Tuner, SEL_AAF_BAND, 1);
		}
	} else { /* Analog Mode */
		if (Tuner->IF_OUT >= 4000000UL && Tuner->IF_OUT <= 5000000UL)
		{
			status += MXL_ControlWrite(Tuner, EN_AAF, 1);
			status += MXL_ControlWrite(Tuner, EN_3P, 1);
			status += MXL_ControlWrite(Tuner, EN_AUX_3P, 1);
			status += MXL_ControlWrite(Tuner, SEL_AAF_BAND, 0);
		}
		if (Tuner->IF_OUT > 5000000UL)
		{
			status += MXL_ControlWrite(Tuner, EN_AAF, 0);
			status += MXL_ControlWrite(Tuner, EN_3P, 0);
			status += MXL_ControlWrite(Tuner, EN_AUX_3P, 0);
			status += MXL_ControlWrite(Tuner, SEL_AAF_BAND, 0);
		}
	}

	/**
	 * Demod Clock Out
	 */
	if (Tuner->CLOCK_OUT)
		status += MXL_ControlWrite(Tuner, SEQ_ENCLK16_CLK_OUT, 1);
	else
		status += MXL_ControlWrite(Tuner, SEQ_ENCLK16_CLK_OUT, 0);

	if (Tuner->DIV_OUT == 1)
		status += MXL_ControlWrite(Tuner, SEQ_SEL4_16B, 1);
	if (Tuner->DIV_OUT == 0)
		status += MXL_ControlWrite(Tuner, SEQ_SEL4_16B, 0);

	/**
	 * Crystal Control
	 */ 
	if (Tuner->CAPSELECT)
		status += MXL_ControlWrite(Tuner, XTAL_CAPSELECT, 1);
	else
		status += MXL_ControlWrite(Tuner, XTAL_CAPSELECT, 0);

	if (Tuner->Fxtal >= 12000000UL && Tuner->Fxtal <= 16000000UL)
		status += MXL_ControlWrite(Tuner, IF_SEL_DBL, 1);
	if (Tuner->Fxtal > 16000000UL && Tuner->Fxtal <= 32000000UL)
		status += MXL_ControlWrite(Tuner, IF_SEL_DBL, 0);

	if (Tuner->Fxtal >= 12000000UL && Tuner->Fxtal <= 22000000UL)
		status += MXL_ControlWrite(Tuner, RFSYN_R_DIV, 3);
	if (Tuner->Fxtal > 22000000UL && Tuner->Fxtal <= 32000000UL)
		status += MXL_ControlWrite(Tuner, RFSYN_R_DIV, 0);

	/**
	 * Misc Controls
	 */
	if (Tuner->Mode == 0 && Tuner->IF_Mode == 1) /** Analog LowIF mode */
		status += MXL_ControlWrite(Tuner, SEQ_EXTIQFSMPULSE, 0);
	else
		status += MXL_ControlWrite(Tuner, SEQ_EXTIQFSMPULSE, 1);

	/** Set TG_R_DIV */
	status += MXL_ControlWrite(Tuner, TG_R_DIV, MXL_Ceiling(Tuner->Fxtal, 1000000));

	/**
	 * Apply Default value to BB_INITSTATE_DLPF_TUNE
	 */



	/**
	 * RSSI Control
	 */
	if(Tuner->EN_RSSI)
	{
		status += MXL_ControlWrite(Tuner, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(Tuner, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(Tuner, AGC_EN_RSSI, 1);
		status += MXL_ControlWrite(Tuner, RFA_ENCLKRFAGC, 1);
		/* RSSI reference point */
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REF, 2);
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REFH, 3);
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REFL, 1);
		/* TOP point */
		status += MXL_ControlWrite(Tuner, RFA_FLR, 0);
		status += MXL_ControlWrite(Tuner, RFA_CEIL, 12);
	}

	/**
	 * Modulation type bit settings
	 * Override the control values preset
	 */
	if (Tuner->Mod_Type == MXL_DVBT) /** DVB-T Mode */
	{
		Tuner->AGC_Mode = 1;		/* Single AGC Mode */

		/* Enable RSSI */
		status += MXL_ControlWrite(Tuner, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(Tuner, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(Tuner, AGC_EN_RSSI, 1);
		status += MXL_ControlWrite(Tuner, RFA_ENCLKRFAGC, 1);
		/* RSSI reference point */
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REF, 3);
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REFH, 5);
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REFL, 1);
		/* TOP point */
		status += MXL_ControlWrite(Tuner, RFA_FLR, 2);
		status += MXL_ControlWrite(Tuner, RFA_CEIL, 13);
		if (Tuner->IF_OUT <= 6280000UL)	/* Low IF */
			status += MXL_ControlWrite(Tuner, BB_IQSWAP, 0);
		else /* High IF */
			status += MXL_ControlWrite(Tuner, BB_IQSWAP, 1);

	}
	if (Tuner->Mod_Type == MXL_ATSC) /* ATSC Mode */
	{
		Tuner->AGC_Mode = 1;		/* Single AGC Mode */
		Tuner->EN_RSSI = 1;		/* Enable RSSI */
		/* Enable RSSI */
		status += MXL_ControlWrite(Tuner, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(Tuner, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(Tuner, AGC_EN_RSSI, 1);
		status += MXL_ControlWrite(Tuner, RFA_ENCLKRFAGC, 1);
		/* RSSI reference point */
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REF, 2);
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REFH, 4);
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REFL, 1);
		/* TOP point */
		status += MXL_ControlWrite(Tuner, RFA_FLR, 2);
		status += MXL_ControlWrite(Tuner, RFA_CEIL, 13);

		status += MXL_ControlWrite(Tuner, BB_INITSTATE_DLPF_TUNE, 1);
		status += MXL_ControlWrite(Tuner, RFSYN_CHP_GAIN, 5);	/* Low Zero */
		if (Tuner->IF_OUT <= 6280000UL)	/* Low IF */
			status += MXL_ControlWrite(Tuner, BB_IQSWAP, 0);
		else /* High IF */
			status += MXL_ControlWrite(Tuner, BB_IQSWAP, 1);
	}
	if (Tuner->Mod_Type == MXL_QAM) /* QAM Mode */
	{
		Tuner->Mode = MXL_DIGITAL_MODE;

		/** Disable RSSI */										/** change here for v2.6.5 */
		status += MXL_ControlWrite(Tuner, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(Tuner, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(Tuner, AGC_EN_RSSI, 0);
		status += MXL_ControlWrite(Tuner, RFA_ENCLKRFAGC, 1);

		/* RSSI reference point */
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REFH, 5);
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REF, 3);
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REFL, 2);

		status += MXL_ControlWrite(Tuner, RFSYN_CHP_GAIN, 3);	/** change here for v2.6.5 */

		if (Tuner->IF_OUT <= 6280000UL)	/** Low IF */
			status += MXL_ControlWrite(Tuner, BB_IQSWAP, 0);
		else /** High IF */
			status += MXL_ControlWrite(Tuner, BB_IQSWAP, 1);
	}
	if (Tuner->Mod_Type == MXL_ANALOG_CABLE) /** Analog Cable Mode */
	{
		Tuner->AGC_Mode = 1;		/** Single AGC Mode */

		/** Disable RSSI */
		status += MXL_ControlWrite(Tuner, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(Tuner, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(Tuner, AGC_EN_RSSI, 0);
		status += MXL_ControlWrite(Tuner, RFA_ENCLKRFAGC, 1);

		status += MXL_ControlWrite(Tuner, AGC_IF, 1);  /** change for 2.6.3 */
		status += MXL_ControlWrite(Tuner, AGC_RF, 15);

		status += MXL_ControlWrite(Tuner, BB_IQSWAP, 1);
	}

	if (Tuner->Mod_Type == MXL_ANALOG_OTA) /** Analog OTA Terrestrial mode add for 2.6.7 */
	{
		/** Enable RSSI */
		status += MXL_ControlWrite(Tuner, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(Tuner, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(Tuner, AGC_EN_RSSI, 1);
		status += MXL_ControlWrite(Tuner, RFA_ENCLKRFAGC, 1);

		/** RSSI reference point */
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REFH, 5);
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REF, 3);
		status += MXL_ControlWrite(Tuner, RFA_RSSI_REFL, 2);

		status += MXL_ControlWrite(Tuner, RFSYN_CHP_GAIN, 3);

		status += MXL_ControlWrite(Tuner, BB_IQSWAP, 1);
	}

	/** RSSI disable */
	if(Tuner->EN_RSSI==0)
	{
		status += MXL_ControlWrite(Tuner, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(Tuner, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(Tuner, AGC_EN_RSSI, 0);
		status += MXL_ControlWrite(Tuner, RFA_ENCLKRFAGC, 1);
	}

	return status;
}

/**
 *                                                                           
 * Function:       MXL_IFSynthInit                                           
 *                                                                           
 * Description:    Tuner IF Synthesizer related register initialization      
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Functions used:                                                           
 *                 Tuner_struct: structure defined at higher level           
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner       : Tuner structure defined at higher level     
 *                                                                           
 * Outputs:                                                                  
 *                 Tuner                                                     
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful                                            
 *               > 0 : Failed                                                
 *                                                                           
 */
WORD MXL_IFSynthInit( Tuner_struct * Tuner )
{
	WORD status = 0;
	/* Declare Local Variables */
	DWORD	Fref = 0;
	DWORD	Kdbl, intModVal;
    DWORD	fracModVal;    
	Kdbl = 2;

	if (Tuner->Fxtal >= 12000000UL && Tuner->Fxtal <= 16000000UL)
		Kdbl = 2;
	if (Tuner->Fxtal > 16000000UL && Tuner->Fxtal <= 32000000UL)
		Kdbl = 1;

	/**
	 * IF Synthesizer Control
	 */
	if (Tuner->Mode == 0 && Tuner->IF_Mode == 1) /* Analog Low IF mode */
	{
		if (Tuner->IF_LO == 41000000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x0C);
			Fref = 328000000UL;
		}
		if (Tuner->IF_LO == 47000000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 376000000UL;
		}
		if (Tuner->IF_LO == 54000000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x10);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x0C);
			Fref = 324000000UL;
		}
		if (Tuner->IF_LO == 60000000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x10);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 360000000UL;
		}
		if (Tuner->IF_LO == 39250000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x0C);
			Fref = 314000000UL;
		}
		if (Tuner->IF_LO == 39650000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x0C);
			Fref = 317200000UL;
		}
		if (Tuner->IF_LO == 40150000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x0C);
			Fref = 321200000UL;
		}
		if (Tuner->IF_LO == 40650000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x0C);
			Fref = 325200000UL;
		}
	}

	if (Tuner->Mode || (Tuner->Mode == 0 && Tuner->IF_Mode == 0))
	{
		if (Tuner->IF_LO == 57000000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x10);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 342000000UL;
		}
		if (Tuner->IF_LO == 44000000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 352000000UL;
		}
		if (Tuner->IF_LO == 43750000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 350000000UL;
		}
		if (Tuner->IF_LO == 36650000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 366500000UL;
		}
		if (Tuner->IF_LO == 36150000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 361500000UL;
		}
		if (Tuner->IF_LO == 36000000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 360000000UL;
		}
		if (Tuner->IF_LO == 35250000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 352500000UL;
		}
		if (Tuner->IF_LO == 34750000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 347500000UL;
		}
		if (Tuner->IF_LO == 6280000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x07);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 376800000UL;
		}
		if (Tuner->IF_LO == 5000000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x09);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 360000000UL;
		}
		if (Tuner->IF_LO == 4500000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x06);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 360000000UL;
		}
		if (Tuner->IF_LO == 4570000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x06);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 365600000UL;
		}
		if (Tuner->IF_LO == 4000000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x05);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 360000000UL;
		}
		if (Tuner->IF_LO == 57400000UL)
		{
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x10);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 344400000UL;
		}
		if (Tuner->IF_LO == 44400000UL)
		{
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 355200000UL;
		}
		if (Tuner->IF_LO == 44150000UL)
		{
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 353200000UL;
		}
		if (Tuner->IF_LO == 37050000UL)
		{
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 370500000UL;
		}
		if (Tuner->IF_LO == 36550000UL)
		{
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 365500000UL;
		}
		if (Tuner->IF_LO == 36125000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 361250000UL;
		}
		if (Tuner->IF_LO == 6000000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x07);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 360000000UL;
		}
		if (Tuner->IF_LO == 5400000UL)
		{
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x07);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x0C);
			Fref = 324000000UL;
		}
		if (Tuner->IF_LO == 5380000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x07);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x0C);
			Fref = 322800000UL;
		}
		if (Tuner->IF_LO == 5200000UL) {
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x09);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 374400000UL;
		}
		if (Tuner->IF_LO == 4900000UL)
		{
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x09);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 352800000UL;
		}
		if (Tuner->IF_LO == 4400000UL)
		{
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x06);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 352000000UL;
		}
		if (Tuner->IF_LO == 4063000UL)  /** add for 2.6.8 */
		{
			status += MXL_ControlWrite(Tuner, IF_DIVVAL,   0x05);
			status += MXL_ControlWrite(Tuner, IF_VCO_BIAS, 0x08);
			Fref = 365670000UL;
		}
	}
	/* CHCAL_INT_MOD_IF */
	/* CHCAL_FRAC_MOD_IF */
	intModVal = Fref / (Tuner->Fxtal * Kdbl/2);
	status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_IF, intModVal );

	fracModVal = (2<<15)*(Fref/1000 - (Tuner->Fxtal/1000 * Kdbl/2) * intModVal);
	fracModVal = fracModVal / ((Tuner->Fxtal * Kdbl/2)/1000);
	status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_IF, fracModVal);



	return status;
}

/**
 *                                                                           
 * Function:       MXL_GetXtalInt                                            
 *                                                                           
 * Description:    return the Crystal Integration Value for				     
 *				   TG_VCO_BIAS calculation									 
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Functions used:                                                           
 *                 NONE											             
 *                                                                           
 * Inputs:                                                                   
 *                 Crystal Frequency Value in Hz						     
 *                                                                           
 * Outputs:                                                                  
 *                 Calculated Crystal Frequency Integration Value            
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful                                            
 *               > 0 : Failed                                                
 *                                                                           
 */
DWORD MXL_GetXtalInt(DWORD Xtal_Freq)
{
	if ((Xtal_Freq % 1000000) == 0)
		return (Xtal_Freq / 10000);
	else
		return (((Xtal_Freq / 1000000) + 1)*100);
}

/**
 *                                                                           
 * Function:       MXL5005_TuneRF                                            
 *                                                                           
 * Description:    Set control names to tune to requested RF_IN frequency    
 *                                                                           
 * Globals:                                                                  
 *                 None                                                      
 *                                                                           
 * Functions used:                                                           
 *                 MXL_SynthRFTGLO_Calc                                      
 *                 MXL5005_ControlWrite                                      
 *				   MXL_GetXtalInt											 
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner       : Tuner structure defined at higher level     
 *                                                                           
 * Outputs:                                                                  
 *                 Tuner                                                     
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful                                            
 *                 1 : Unsuccessful                                          
 */
WORD MXL_TuneRF(Tuner_struct *Tuner, DWORD RF_Freq) 
{
	/* Declare Local Variables */
	WORD status = 0;
	DWORD divider_val, E3, E4, E5, E5A;
	DWORD Fmax, Fmin, FmaxBin, FminBin;
	DWORD Kdbl_RF = 2; 
	DWORD tg_divval;
	DWORD tg_lo;
	DWORD Xtal_Int;
	
	DWORD Fref_TG;
	DWORD Fvco;

	Xtal_Int = MXL_GetXtalInt(Tuner->Fxtal );

	Tuner->RF_IN = RF_Freq;

	MXL_SynthRFTGLO_Calc( Tuner );

	if (Tuner->Fxtal >= 12000000UL && Tuner->Fxtal <= 22000000UL)
		Kdbl_RF = 2;
	if (Tuner->Fxtal > 22000000 && Tuner->Fxtal <= 32000000)
		Kdbl_RF = 1;

	/**
	 * Downconverter Controls
	 *
	 * Look-Up Table Implementation for:
	 *	DN_POLY
	 *	DN_RFGAIN
	 *	DN_CAP_RFLPF
	 *	DN_EN_VHFUHFBAR
	 *	DN_GAIN_ADJUST
	 * Change the boundary reference from RF_IN to RF_LO
	 */
	if (Tuner->RF_LO < 40000000UL) {
		return -1;
	}
	if (Tuner->RF_LO >= 40000000UL && Tuner->RF_LO <= 75000000UL) {
		/* Look-Up Table implementation */
		status += MXL_ControlWrite(Tuner, DN_POLY,              2);
		status += MXL_ControlWrite(Tuner, DN_RFGAIN,            3);
		status += MXL_ControlWrite(Tuner, DN_CAP_RFLPF,         423);
		status += MXL_ControlWrite(Tuner, DN_EN_VHFUHFBAR,      1);
		status += MXL_ControlWrite(Tuner, DN_GAIN_ADJUST,       1);
	}
	if (Tuner->RF_LO > 75000000UL && Tuner->RF_LO <= 100000000UL) {
		/* Look-Up Table implementation */
		status += MXL_ControlWrite(Tuner, DN_POLY,              3);
		status += MXL_ControlWrite(Tuner, DN_RFGAIN,            3);
		status += MXL_ControlWrite(Tuner, DN_CAP_RFLPF,         222);
		status += MXL_ControlWrite(Tuner, DN_EN_VHFUHFBAR,      1);
		status += MXL_ControlWrite(Tuner, DN_GAIN_ADJUST,       1);
	}
	if (Tuner->RF_LO > 100000000UL && Tuner->RF_LO <= 150000000UL) {
		/* Look-Up Table implementation */
		status += MXL_ControlWrite(Tuner, DN_POLY,              3);
		status += MXL_ControlWrite(Tuner, DN_RFGAIN,            3);
		status += MXL_ControlWrite(Tuner, DN_CAP_RFLPF,         147);
		status += MXL_ControlWrite(Tuner, DN_EN_VHFUHFBAR,      1);
		status += MXL_ControlWrite(Tuner, DN_GAIN_ADJUST,       2);
	}
	if (Tuner->RF_LO > 150000000UL && Tuner->RF_LO <= 200000000UL) {
		/* Look-Up Table implementation */
		status += MXL_ControlWrite(Tuner, DN_POLY,              3);
		status += MXL_ControlWrite(Tuner, DN_RFGAIN,            3);
		status += MXL_ControlWrite(Tuner, DN_CAP_RFLPF,         9);
		status += MXL_ControlWrite(Tuner, DN_EN_VHFUHFBAR,      1);
		status += MXL_ControlWrite(Tuner, DN_GAIN_ADJUST,       2);
	}
	if (Tuner->RF_LO > 200000000UL && Tuner->RF_LO <= 300000000UL) {
		/* Look-Up Table implementation */
		status += MXL_ControlWrite(Tuner, DN_POLY,              3);
		status += MXL_ControlWrite(Tuner, DN_RFGAIN,            3);
		status += MXL_ControlWrite(Tuner, DN_CAP_RFLPF,         0);
		status += MXL_ControlWrite(Tuner, DN_EN_VHFUHFBAR,      1);
		status += MXL_ControlWrite(Tuner, DN_GAIN_ADJUST,       3);
	}
	if (Tuner->RF_LO > 300000000UL && Tuner->RF_LO <= 650000000UL) {
		/* Look-Up Table implementation */
		status += MXL_ControlWrite(Tuner, DN_POLY,              3);
		status += MXL_ControlWrite(Tuner, DN_RFGAIN,            1);
		status += MXL_ControlWrite(Tuner, DN_CAP_RFLPF,         0);
		status += MXL_ControlWrite(Tuner, DN_EN_VHFUHFBAR,      0);
		status += MXL_ControlWrite(Tuner, DN_GAIN_ADJUST,       3);
	}
	if (Tuner->RF_LO > 650000000UL && Tuner->RF_LO <= 900000000UL) {
		/* Look-Up Table implementation */
		status += MXL_ControlWrite(Tuner, DN_POLY,              3);
		status += MXL_ControlWrite(Tuner, DN_RFGAIN,            2);
		status += MXL_ControlWrite(Tuner, DN_CAP_RFLPF,         0);
		status += MXL_ControlWrite(Tuner, DN_EN_VHFUHFBAR,      0);
		status += MXL_ControlWrite(Tuner, DN_GAIN_ADJUST,       3);
	}
	if (Tuner->RF_LO > 900000000UL) {
		return -1;
	}
	/* DN_IQTNBUF_AMP */
	/* DN_IQTNGNBFBIAS_BST */
	if (Tuner->RF_LO >= 40000000UL && Tuner->RF_LO <= 75000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 75000000UL && Tuner->RF_LO <= 100000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 100000000UL && Tuner->RF_LO <= 150000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 150000000UL && Tuner->RF_LO <= 200000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 200000000UL && Tuner->RF_LO <= 300000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 300000000UL && Tuner->RF_LO <= 400000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 400000000UL && Tuner->RF_LO <= 450000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 450000000UL && Tuner->RF_LO <= 500000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 500000000UL && Tuner->RF_LO <= 550000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 550000000UL && Tuner->RF_LO <= 600000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 600000000UL && Tuner->RF_LO <= 650000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 650000000UL && Tuner->RF_LO <= 700000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 700000000UL && Tuner->RF_LO <= 750000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 750000000UL && Tuner->RF_LO <= 800000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (Tuner->RF_LO > 800000000UL && Tuner->RF_LO <= 850000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       10);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  1);
	}
	if (Tuner->RF_LO > 850000000UL && Tuner->RF_LO <= 900000000UL) {
		status += MXL_ControlWrite(Tuner, DN_IQTNBUF_AMP,       10);
		status += MXL_ControlWrite(Tuner, DN_IQTNGNBFBIAS_BST,  1);
	}

	/**
	 * Set RF Synth and LO Path Control
	 *
	 * Look-Up table implementation for:
	 *	RFSYN_EN_OUTMUX
	 *	RFSYN_SEL_VCO_OUT
	 *	RFSYN_SEL_VCO_HI
	 *  RFSYN_SEL_DIVM
	 *	RFSYN_RF_DIV_BIAS
	 *	DN_SEL_FREQ
	 *
	 * Set divider_val, Fmax, Fmix to use in Equations
	 */
	FminBin = 28000000UL;
	FmaxBin = 42500000UL;
	if (Tuner->RF_LO >= 40000000UL && Tuner->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX,     1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT,   0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI,    0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(Tuner, DN_SEL_FREQ,         1);
		divider_val = 64;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 42500000UL;
	FmaxBin = 56000000UL;
	if (Tuner->RF_LO > FminBin && Tuner->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX,     1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT,   0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI,    1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(Tuner, DN_SEL_FREQ,         1);
		divider_val = 64;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 56000000UL;
	FmaxBin = 85000000UL;
	if (Tuner->RF_LO > FminBin && Tuner->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI,    0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(Tuner, DN_SEL_FREQ,         1);
		divider_val = 32;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 85000000UL;
	FmaxBin = 112000000UL;
	if (Tuner->RF_LO > FminBin && Tuner->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI,    1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(Tuner, DN_SEL_FREQ,         1);
		divider_val = 32;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 112000000UL;
	FmaxBin = 170000000UL;
	if (Tuner->RF_LO > FminBin && Tuner->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI,    0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(Tuner, DN_SEL_FREQ,         2);
		divider_val = 16;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 170000000UL;
	FmaxBin = 225000000UL;
	if (Tuner->RF_LO > FminBin && Tuner->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI,    1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(Tuner, DN_SEL_FREQ,         2);
		divider_val = 16;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 225000000UL;
	FmaxBin = 300000000UL;
	if (Tuner->RF_LO > FminBin && Tuner->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI,    0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(Tuner, DN_SEL_FREQ,         4);
		divider_val = 8;
		Fmax = 340000000UL;
		Fmin = FminBin;
	}
	FminBin = 300000000UL;
	FmaxBin = 340000000UL;
	if (Tuner->RF_LO > FminBin && Tuner->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX,     1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT,   0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI,    0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(Tuner, DN_SEL_FREQ,         0);
		divider_val = 8;
		Fmax = FmaxBin;
		Fmin = 225000000UL;
	}
	FminBin = 340000000UL;
	FmaxBin = 450000000UL;
	if (Tuner->RF_LO > FminBin && Tuner->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX,     1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT,   0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI,    1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS,   2);
		status += MXL_ControlWrite(Tuner, DN_SEL_FREQ,         0);
		divider_val = 8;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 450000000UL;
	FmaxBin = 680000000UL;
	if (Tuner->RF_LO > FminBin && Tuner->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI,    0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM,      1);
		status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(Tuner, DN_SEL_FREQ,         0);
		divider_val = 4;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 680000000UL;
	FmaxBin = 900000000UL;
	if (Tuner->RF_LO > FminBin && Tuner->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI,    1);
		status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM,      1);
		status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(Tuner, DN_SEL_FREQ,         0);
		divider_val = 4;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}

	/* CHCAL_INT_MOD_RF */
	/* CHCAL_FRAC_MOD_RF */
	/* RFSYN_LPF_R */
	/* CHCAL_EN_INT_RF */

	/* Equation E3 */
	/* RFSYN_VCO_BIAS */
	E3 = (((Fmax-Tuner->RF_LO)/1000)*32)/((Fmax-Fmin)/1000) + 8;
	status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, E3);

	/* Equation E4 */
	/* CHCAL_INT_MOD_RF */
	E4 = (Tuner->RF_LO*divider_val/1000)/(2*Tuner->Fxtal*Kdbl_RF/1000);
	MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, E4);

	/* Equation E5 */
	/* CHCAL_FRAC_MOD_RF */
	/* CHCAL_EN_INT_RF */
	E5 = ((2<<17)*(Tuner->RF_LO/10000*divider_val - (E4*(2*Tuner->Fxtal*Kdbl_RF)/10000)))/(2*Tuner->Fxtal*Kdbl_RF/10000);
	status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, E5);

	/* Equation E5A */
	/* RFSYN_LPF_R */
	E5A = (((Fmax - Tuner->RF_LO)/1000)*4/((Fmax-Fmin)/1000)) + 1;
	status += MXL_ControlWrite(Tuner, RFSYN_LPF_R, E5A);

	/* Euqation E5B */
	/* CHCAL_EN_INIT_RF */
	status += MXL_ControlWrite(Tuner, CHCAL_EN_INT_RF, ((E5 == 0) ? 1 : 0));

	/**
	 * Set TG Synth
	 *
	 * Look-Up table implementation for:
	 *	TG_LO_DIVVAL
	 *	TG_LO_SELVAL
	 *
	 * Set divider_val, Fmax, Fmix to use in Equations
	 */
	if (Tuner->TG_LO < 33000000UL) {
		return -1;
	}
	FminBin = 33000000UL;
	FmaxBin = 50000000UL;
	if (Tuner->TG_LO >= FminBin && Tuner->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, TG_LO_DIVVAL,	0x6);
		status += MXL_ControlWrite(Tuner, TG_LO_SELVAL,	0x0);
		divider_val = 36;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 50000000UL;
	FmaxBin = 67000000UL;
	if (Tuner->TG_LO > FminBin && Tuner->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, TG_LO_DIVVAL,	0x1);
		status += MXL_ControlWrite(Tuner, TG_LO_SELVAL,	0x0);
		divider_val = 24;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 67000000UL;
	FmaxBin = 100000000UL;
	if (Tuner->TG_LO > FminBin && Tuner->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, TG_LO_DIVVAL,	0xC);
		status += MXL_ControlWrite(Tuner, TG_LO_SELVAL,	0x2);
		divider_val = 18;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 100000000UL;
	FmaxBin = 150000000UL;
	if (Tuner->TG_LO > FminBin && Tuner->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, TG_LO_DIVVAL,	0x8);
		status += MXL_ControlWrite(Tuner, TG_LO_SELVAL,	0x2);
		divider_val = 12;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 150000000UL;
	FmaxBin = 200000000UL;
	if (Tuner->TG_LO > FminBin && Tuner->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, TG_LO_DIVVAL,	0x0);
		status += MXL_ControlWrite(Tuner, TG_LO_SELVAL,	0x2);
		divider_val = 8;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 200000000UL;
	FmaxBin = 300000000UL;
	if (Tuner->TG_LO > FminBin && Tuner->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, TG_LO_DIVVAL,	0x8);
		status += MXL_ControlWrite(Tuner, TG_LO_SELVAL,	0x3);
		divider_val = 6;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 300000000UL;
	FmaxBin = 400000000UL;
	if (Tuner->TG_LO > FminBin && Tuner->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, TG_LO_DIVVAL,	0x0);
		status += MXL_ControlWrite(Tuner, TG_LO_SELVAL,	0x3);
		divider_val = 4;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 400000000UL;
	FmaxBin = 600000000UL;
	if (Tuner->TG_LO > FminBin && Tuner->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, TG_LO_DIVVAL,	0x8);
		status += MXL_ControlWrite(Tuner, TG_LO_SELVAL,	0x7);
		divider_val = 3;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}
	FminBin = 600000000UL;
	FmaxBin = 900000000UL;
	if (Tuner->TG_LO > FminBin && Tuner->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(Tuner, TG_LO_DIVVAL,	0x0);
		status += MXL_ControlWrite(Tuner, TG_LO_SELVAL,	0x7);
		divider_val = 2;
		Fmax = FmaxBin;
		Fmin = FminBin;
	}

	/* TG_DIV_VAL */
	tg_divval = (Tuner->TG_LO*divider_val/100000) 
			 *(MXL_Ceiling(Tuner->Fxtal,1000000) * 100) / (Tuner->Fxtal/1000);
	status += MXL_ControlWrite(Tuner, TG_DIV_VAL, tg_divval);

	if (Tuner->TG_LO > 600000000UL)
		status += MXL_ControlWrite(Tuner, TG_DIV_VAL, tg_divval + 1 );

	Fmax = 1800000000UL;
	Fmin = 1200000000UL;



	/** to prevent overflow of 32 bit unsigned integer, use following equation. Edit for v2.6.4 */
	Fref_TG = (Tuner->Fxtal/1000)/ MXL_Ceiling(Tuner->Fxtal, 1000000); /** Fref_TF = Fref_TG*1000 */

	Fvco = (Tuner->TG_LO/10000) * divider_val * Fref_TG;  /** Fvco = Fvco/10 */

	tg_lo = (((Fmax/10 - Fvco)/100)*32) / ((Fmax-Fmin)/1000)+8;
	
	
	status += MXL_ControlWrite(Tuner, TG_VCO_BIAS , tg_lo);



	/** add for 2.6.5 */
	/** Special setting for QAM */
	if(Tuner ->Mod_Type == MXL_QAM)
	{
	if(Tuner->RF_IN < 680000000)
		status += MXL_ControlWrite(Tuner, RFSYN_CHP_GAIN, 3);
	else
		status += MXL_ControlWrite(Tuner, RFSYN_CHP_GAIN, 2);
	}
	

	/** remove 20.48MHz setting for 2.6.10 */

	/**
	 * Off Chip Tracking Filter Control
	 */
	if (Tuner->TF_Type == MXL_TF_OFF) /** Tracking Filter Off State; turn off all the banks */
	{
		status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0);
		status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0);

		status += MXL_SetGPIO(Tuner, 3, 1); /** turn off Bank 1 */
		status += MXL_SetGPIO(Tuner, 1, 1); /** turn off Bank 2 */
		status += MXL_SetGPIO(Tuner, 4, 1); /** turn off Bank 3 */
	}

	if (Tuner->TF_Type == MXL_TF_C) /** Tracking Filter type C */
	{
		status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1);
		status += MXL_ControlWrite(Tuner, DAC_DIN_A, 0);

		if (Tuner->RF_IN >= 43000000 && Tuner->RF_IN < 150000000)
		{
			
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 Off */
			status += MXL_ControlWrite(Tuner, DAC_DIN_B, 0);
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 150000000 && Tuner->RF_IN < 280000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 Off */
			status += MXL_ControlWrite(Tuner, DAC_DIN_B, 0);
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 280000000 && Tuner->RF_IN < 360000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 Off */
			status += MXL_ControlWrite(Tuner, DAC_DIN_B, 0);
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 360000000 && Tuner->RF_IN < 560000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 Off */
			status += MXL_ControlWrite(Tuner, DAC_DIN_B, 0);
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 560000000 && Tuner->RF_IN < 580000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
			status += MXL_ControlWrite(Tuner, DAC_DIN_B, 29); 
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 580000000 && Tuner->RF_IN < 630000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
			status += MXL_ControlWrite(Tuner, DAC_DIN_B, 0);
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 630000000 && Tuner->RF_IN < 700000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
			status += MXL_ControlWrite(Tuner, DAC_DIN_B, 16);
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 700000000 && Tuner->RF_IN < 760000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
			status += MXL_ControlWrite(Tuner, DAC_DIN_B, 7);
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 760000000 && Tuner->RF_IN <= 900000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
			status += MXL_ControlWrite(Tuner, DAC_DIN_B, 0);
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank3 Off */
		}
	}
		
	if (Tuner->TF_Type == MXL_TF_C_H) /** Tracking Filter type C-H for Hauppauge only */
	{
		status += MXL_ControlWrite(Tuner, DAC_DIN_A, 0);

		if (Tuner->RF_IN >= 43000000 && Tuner->RF_IN < 150000000)
		{
			
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 150000000 && Tuner->RF_IN < 280000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 280000000 && Tuner->RF_IN < 360000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 360000000 && Tuner->RF_IN < 560000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 560000000 && Tuner->RF_IN < 580000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 580000000 && Tuner->RF_IN < 630000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 630000000 && Tuner->RF_IN < 700000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 700000000 && Tuner->RF_IN < 760000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 760000000 && Tuner->RF_IN <= 900000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank3 Off */
		}
	}

	if (Tuner->TF_Type == MXL_TF_D) /** Tracking Filter type D */
	{
		status += MXL_ControlWrite(Tuner, DAC_DIN_B, 0);

		if (Tuner->RF_IN >= 43000000 && Tuner->RF_IN < 174000000)
		{
			
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 174000000 && Tuner->RF_IN < 250000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 250000000 && Tuner->RF_IN < 310000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 310000000 && Tuner->RF_IN < 360000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 360000000 && Tuner->RF_IN < 470000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 470000000 && Tuner->RF_IN < 640000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 640000000 && Tuner->RF_IN <= 900000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
	}


	if (Tuner->TF_Type == MXL_TF_D_L) /** Tracking Filter type D-L for Lumanate ONLY  change for 2.6.3 */
	{
		status += MXL_ControlWrite(Tuner, DAC_DIN_A, 0);

		if (Tuner->RF_IN >= 471000000 && (Tuner->RF_IN - 471000000)%6000000 != 0) /** if UHF and terrestrial => Turn off Tracking Filter */
		{
			/** Turn off all the banks */
			status += MXL_SetGPIO(Tuner, 3, 1);
			status += MXL_SetGPIO(Tuner, 1, 1);
			status += MXL_SetGPIO(Tuner, 4, 1);
			status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0);

			status += MXL_ControlWrite(Tuner, AGC_IF, 10);
		}
		
		else  /** if VHF or cable => Turn on Tracking Filter */
		{
			if (Tuner->RF_IN >= 43000000 && Tuner->RF_IN < 140000000)
			{
				
				status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 Off */
				status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 On */
				status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
				status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 Off */
			}
			if (Tuner->RF_IN >= 140000000 && Tuner->RF_IN < 240000000)
			{
				status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 Off */
				status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 On */
				status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
				status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 Off */
			}
			if (Tuner->RF_IN >= 240000000 && Tuner->RF_IN < 340000000)
			{
				status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 Off */
				status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 Off */
				status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 On */
				status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 Off */
			}
			if (Tuner->RF_IN >= 340000000 && Tuner->RF_IN < 430000000)
			{
				status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 Off */
				status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 Off */
				status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
				status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 On */
			}
			if (Tuner->RF_IN >= 430000000 && Tuner->RF_IN < 470000000)
			{
				status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 Off */
				status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
				status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 Off */
				status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 On */
			}
			if (Tuner->RF_IN >= 470000000 && Tuner->RF_IN < 570000000)
			{
				status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
				status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 Off */
				status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 Off */
				status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 On */
			}
			if (Tuner->RF_IN >= 570000000 && Tuner->RF_IN < 620000000)
			{
				status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 0); /** Bank4 On */
				status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 Off */
				status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
				status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Offq */
			}
			if (Tuner->RF_IN >= 620000000 && Tuner->RF_IN < 760000000)
			{
				status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
				status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 Off */
				status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
				status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
			}
			if (Tuner->RF_IN >= 760000000 && Tuner->RF_IN <= 900000000)
			{
				status += MXL_ControlWrite(Tuner, DAC_A_ENABLE, 1); /** Bank4 On */
				status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
				status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
				status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
			}
		}
	}

	if (Tuner->TF_Type == MXL_TF_E) /** Tracking Filter type E */
	{
		status += MXL_ControlWrite(Tuner, DAC_DIN_B, 0);

		if (Tuner->RF_IN >= 43000000 && Tuner->RF_IN < 174000000)
		{
			
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 174000000 && Tuner->RF_IN < 250000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 250000000 && Tuner->RF_IN < 310000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 310000000 && Tuner->RF_IN < 360000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 360000000 && Tuner->RF_IN < 470000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 470000000 && Tuner->RF_IN < 640000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 640000000 && Tuner->RF_IN <= 900000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
	}

	if (Tuner->TF_Type == MXL_TF_F) /** Tracking Filter type F */
	{
		status += MXL_ControlWrite(Tuner, DAC_DIN_B, 0);

		if (Tuner->RF_IN >= 43000000 && Tuner->RF_IN < 160000000)
		{
			
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 160000000 && Tuner->RF_IN < 210000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 210000000 && Tuner->RF_IN < 300000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 300000000 && Tuner->RF_IN < 390000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 390000000 && Tuner->RF_IN < 515000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 515000000 && Tuner->RF_IN < 650000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 650000000 && Tuner->RF_IN <= 900000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
	}

	if (Tuner->TF_Type == MXL_TF_E_2) /** Tracking Filter type E_2 */
	{
		status += MXL_ControlWrite(Tuner, DAC_DIN_B, 0);

		if (Tuner->RF_IN >= 43000000 && Tuner->RF_IN < 174000000)
		{
			
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 174000000 && Tuner->RF_IN < 250000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 250000000 && Tuner->RF_IN < 350000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 on */
		}
		if (Tuner->RF_IN >= 350000000 && Tuner->RF_IN < 400000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 400000000 && Tuner->RF_IN < 570000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 570000000 && Tuner->RF_IN < 770000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 770000000 && Tuner->RF_IN <= 900000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
	}

	if (Tuner->TF_Type == MXL_TF_G) /** Tracking Filter type G add for v2.6.8 */
	{
		status += MXL_ControlWrite(Tuner, DAC_DIN_B, 0);

		if (Tuner->RF_IN >= 50000000 && Tuner->RF_IN < 190000000)
		{
			
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 190000000 && Tuner->RF_IN < 280000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 280000000 && Tuner->RF_IN < 350000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 350000000 && Tuner->RF_IN < 400000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 400000000 && Tuner->RF_IN < 470000000)		/** modified for 2.6.11 */
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 470000000 && Tuner->RF_IN < 640000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 640000000 && Tuner->RF_IN < 820000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 820000000 && Tuner->RF_IN <= 900000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
	}

	if (Tuner->TF_Type == MXL_TF_E_NA) /** Tracking Filter type E-NA for Empia ONLY  change for 2.6.8 */
	{
		status += MXL_ControlWrite(Tuner, DAC_DIN_B, 0);

		if (Tuner->RF_IN >= 471000000 && (Tuner->RF_IN - 471000000)%6000000 != 0) /**if UHF and terrestrial=> Turn off Tracking Filter */
		{
			/** Turn off all the banks */
			status += MXL_SetGPIO(Tuner, 3, 1);
			status += MXL_SetGPIO(Tuner, 1, 1);
			status += MXL_SetGPIO(Tuner, 4, 1);
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0);

			/** 2.6.12 */
			/** Turn on RSSI */
			status += MXL_ControlWrite(Tuner, SEQ_EXTSYNTHCALIF, 1);
			status += MXL_ControlWrite(Tuner, SEQ_EXTDCCAL, 1);
			status += MXL_ControlWrite(Tuner, AGC_EN_RSSI, 1);
			status += MXL_ControlWrite(Tuner, RFA_ENCLKRFAGC, 1);

			/** RSSI reference point */
			status += MXL_ControlWrite(Tuner, RFA_RSSI_REFH, 5);
			status += MXL_ControlWrite(Tuner, RFA_RSSI_REF, 3);
			status += MXL_ControlWrite(Tuner, RFA_RSSI_REFL, 2);

			/** following parameter is from analog OTA mode, can be change to seek better performance */
			status += MXL_ControlWrite(Tuner, RFSYN_CHP_GAIN, 3);
		}
		
		else  /** if VHF or Cable =>  Turn on Tracking Filter */
		{
		        /** 2.6.12 */
		        /** Turn off RSSI		 */
		        status += MXL_ControlWrite(Tuner, AGC_EN_RSSI, 0);

		        /** change back from above condition */
		        status += MXL_ControlWrite(Tuner, RFSYN_CHP_GAIN, 5);
		if (Tuner->RF_IN >= 43000000 && Tuner->RF_IN < 174000000)
		{
			
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 174000000 && Tuner->RF_IN < 250000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 0); /** Bank1 On */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 250000000 && Tuner->RF_IN < 350000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		if (Tuner->RF_IN >= 350000000 && Tuner->RF_IN < 400000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 0); /** Bank2 On */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 400000000 && Tuner->RF_IN < 570000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 0); /** Bank4 Off */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 570000000 && Tuner->RF_IN < 770000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 0); /** Bank3 On */
		}
		if (Tuner->RF_IN >= 770000000 && Tuner->RF_IN <= 900000000)
		{
			status += MXL_ControlWrite(Tuner, DAC_B_ENABLE, 1); /** Bank4 On */
			status += MXL_SetGPIO(Tuner, 4, 1); /** Bank1 Off */
			status += MXL_SetGPIO(Tuner, 1, 1); /** Bank2 Off */
			status += MXL_SetGPIO(Tuner, 3, 1); /** Bank3 Off */
		}
		}
	}
	return status;
}

WORD MXL_SetGPIO(Tuner_struct *Tuner, BYTE GPIO_Num, BYTE GPIO_Val)
{
	WORD status = 0;

	if (GPIO_Num == 1)
		status += MXL_ControlWrite(Tuner, GPIO_1B, GPIO_Val ? 0 : 1);
	/* GPIO2 is not available */
	if (GPIO_Num == 3)
	{
		if (GPIO_Val == 1) {
			status += MXL_ControlWrite(Tuner, GPIO_3, 0);
			status += MXL_ControlWrite(Tuner, GPIO_3B, 0);
		}
		if (GPIO_Val == 0) {
			status += MXL_ControlWrite(Tuner, GPIO_3, 1);
			status += MXL_ControlWrite(Tuner, GPIO_3B, 1);
		}
		if (GPIO_Val == 3) { /* tri-state */
			status += MXL_ControlWrite(Tuner, GPIO_3, 0);
			status += MXL_ControlWrite(Tuner, GPIO_3B, 1);
		}
	}
	if (GPIO_Num == 4)
	{
		if (GPIO_Val == 1) {
			status += MXL_ControlWrite(Tuner, GPIO_4, 0);
			status += MXL_ControlWrite(Tuner, GPIO_4B, 0);
		}
		if (GPIO_Val == 0) {
			status += MXL_ControlWrite(Tuner, GPIO_4, 1);
			status += MXL_ControlWrite(Tuner, GPIO_4B, 1);
		}
		if (GPIO_Val == 3) { /* tri-state */
			status += MXL_ControlWrite(Tuner, GPIO_4, 0);
			status += MXL_ControlWrite(Tuner, GPIO_4B, 1);
		}
	}

	return status;
}

/**
 *                                                                           
 * Function:       MXL_ControlWrite                                          
 *                                                                           
 * Description:    Update control name value                                 
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Functions used:                                                           
 *                 MXL_ControlWrite( Tuner, controlName, value, Group )      
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner         : Tuner structure                           
 *                 ControlName   : Control name to be updated                
 *                 value         : Value to be written                       
 *                                                                           
 * Outputs:                                                                  
 *                 Tuner       : Tuner structure defined at higher level     
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful write                                      
 *                 >0 : Value exceed maximum allowed for control number      
 *                                                                           
 */
WORD MXL_ControlWrite(Tuner_struct *Tuner, WORD ControlNum, DWORD value)
{
	WORD status = 0;
	/* Will write ALL Matching Control Name */
	status += MXL_ControlWrite_Group( Tuner, ControlNum, value, 1 );    /* Write Matching INIT Control */
	status += MXL_ControlWrite_Group( Tuner, ControlNum, value, 2 );    /* Write Matching CH Control */
#ifdef _MXL_INTERNAL
	status += MXL_ControlWrite_Group( Tuner, ControlNum, value, 3 );    /* Write Matching MXL Control */
#endif

	return status;
}

/**
 *                                                                           
 * Function:       MXL_ControlWrite                                          
 *                                                                           
 * Description:    Update control name value                                 
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Functions used:                                                           
 *                 strcmp                                                    
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner_struct: structure defined at higher level           
 *                 ControlName      : Control Name                           
 *                 value            : Value Assigned to Control Name         
 *                 controlGroup     : Control Register Group                 
 *                                                                           
 * Outputs:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful write                                      
 *                 1 : Value exceed maximum allowed for control name         
 *                 2 : Control name not found                                
 *                                                                           
 */
WORD MXL_ControlWrite_Group(Tuner_struct *Tuner, WORD controlNum, DWORD value, WORD controlGroup)
{
	WORD i, j, k;
	DWORD highLimit;
	DWORD ctrlVal;
	
	if( controlGroup == 1) /* Initial Control */
	{
		for (i=0; i<Tuner->Init_Ctrl_Num; i++)
		{
			if ( controlNum == Tuner->Init_Ctrl[i].Ctrl_Num )
			{   /* find the control Name */
				highLimit = 1 << Tuner->Init_Ctrl[i].size ;
				if ( value < highLimit)
				{
					for( j=0; j<Tuner->Init_Ctrl[i].size; j++)
					{
						Tuner->Init_Ctrl[i].val[j] = (BYTE)((value >> j) & 0x01);
						/** change the register map accordingly */
						MXL_RegWriteBit( Tuner, (BYTE)(Tuner->Init_Ctrl[i].addr[j]), 
							(BYTE)(Tuner->Init_Ctrl[i].bit[j]), 
							(BYTE)((value>>j) & 0x01) );
					}
					ctrlVal = 0;
					for(k=0; k<Tuner->Init_Ctrl[i].size; k++)
					{
						ctrlVal += Tuner->Init_Ctrl[i].val[k] * (1 << k);
					}
				}
				else
				{
				  	return -1;
				}
			}
		}
	}
	if ( controlGroup == 2) /* Chan change Control */
	{
		for (i=0; i<Tuner->CH_Ctrl_Num; i++)
		{
			if ( controlNum == Tuner->CH_Ctrl[i].Ctrl_Num )
			{   /* find the control Name */
				highLimit = 1 << Tuner->CH_Ctrl[i].size;
				if ( value < highLimit)
				{
					for( j=0; j<Tuner->CH_Ctrl[i].size; j++)
					{
						Tuner->CH_Ctrl[i].val[j] = (BYTE)((value >> j) & 0x01);
						/** change the register map accordingly */
						MXL_RegWriteBit( Tuner, (BYTE)(Tuner->CH_Ctrl[i].addr[j]), 
							(BYTE)(Tuner->CH_Ctrl[i].bit[j]), 
							(BYTE)((value>>j) & 0x01) );
					}
					ctrlVal = 0;
					for(k=0; k<Tuner->CH_Ctrl[i].size; k++)
					{
						ctrlVal += Tuner->CH_Ctrl[i].val[k] * (1 << k);
					}
				}
				else
				{
				  	return -1;
				}
			}
		}
	}
#ifdef _MXL_INTERNAL
	if ( controlGroup == 3) /* Maxlinear Control */
	{
		for (i=0; i<Tuner->MXL_Ctrl_Num; i++)
		{
			if ( controlNum == Tuner->MXL_Ctrl[i].Ctrl_Num )
			{   /* find the control Name */
				highLimit = (1 << Tuner->MXL_Ctrl[i].size);
				if ( value < highLimit)
				{
					for( j=0; j<Tuner->MXL_Ctrl[i].size; j++)
					{
						Tuner->MXL_Ctrl[i].val[j] = (BYTE)((value >> j) & 0x01);
						/** change the register map accordingly */
						MXL_RegWriteBit( Tuner, (BYTE)(Tuner->MXL_Ctrl[i].addr[j]), 
							(BYTE)(Tuner->MXL_Ctrl[i].bit[j]), 
							(BYTE)((value>>j) & 0x01) );
					}
					ctrlVal = 0;
					for(k=0; k<Tuner->MXL_Ctrl[i].size; k++)
					{
						ctrlVal += Tuner->MXL_Ctrl[i].val[k] * (1 << k);
					}
				}
				else
				{
				  	return -1;
				}
			}
		}
	}
#endif
	return 0; /* successful return */
}

/**
 *                                                                           
 * Function:       MXL_RegWrite                                              
 *                                                                           
 * Description:    Update tuner register value                               
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Functions used:                                                           
 *                 NONE                                                      
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner_struct: structure defined at higher level           
 *                 RegNum    : Register address to be assigned a value       
 *                 RegVal    : Register value to write                       
 *                                                                           
 * Outputs:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful write                                      
 *                 -1 : Invalid Register Address                             
 *                                                                           
 */
WORD MXL_RegWrite(Tuner_struct *Tuner, BYTE RegNum, BYTE RegVal) 
{
	int i;

	for (i=0; i<104; i++)
	{
		if (RegNum == Tuner->TunerRegs[i].Reg_Num )
		{
			Tuner->TunerRegs[i].Reg_Val = RegVal;
			return 0;
		}
	}

	return 1;
}

/**
 *                                                                           
 * Function:       MXL_RegRead                                               
 *                                                                           
 * Description:    Retrieve tuner register value                             
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Functions used:                                                           
 *                 NONE                                                      
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner_struct: structure defined at higher level           
 *                 RegNum    : Register address to be assigned a value       
 *                                                                           
 * Outputs:                                                                  
 *                 RegVal    : Retrieved register value                      
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful read                                       
 *                 -1 : Invalid Register Address                             
 *                                                                           
 */
WORD MXL_RegRead(Tuner_struct *Tuner, BYTE RegNum, BYTE *RegVal) 
{
	int i;

	for (i=0; i<104; i++)
	{
		if (RegNum == Tuner->TunerRegs[i].Reg_Num )
		{
			*RegVal = (BYTE)(Tuner->TunerRegs[i].Reg_Val);
			return 0;
		}
	}

	return 1;
}

/**
 *                                                                           
 * Function:       MXL_ControlRead                                           
 *                                                                           
 * Description:    Retrieve the control value based on the control name      
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner_struct  : structure defined at higher level         
 *                 ControlName   : Control Name                              
 *                                                                           
 * Outputs:                                                                  
 *                 value  : returned control value                           
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful read                                       
 *                 -1 : Invalid control name                                 
 *                                                                           
 */
WORD MXL_ControlRead(Tuner_struct *Tuner, WORD controlNum, DWORD * value) 
{
	DWORD ctrlVal;
	WORD i, k;

	for (i=0; i<Tuner->Init_Ctrl_Num; i++)
	{
		if ( controlNum == Tuner->Init_Ctrl[i].Ctrl_Num )
		{
			ctrlVal = 0;
			for(k=0; k<Tuner->Init_Ctrl[i].size; k++)
				ctrlVal += Tuner->Init_Ctrl[i].val[k] * (1 << k);
			*value = ctrlVal;
			return 0;
		}
	}
	for (i=0; i<Tuner->CH_Ctrl_Num; i++)
	{
		if ( controlNum == Tuner->CH_Ctrl[i].Ctrl_Num )
		{
			ctrlVal = 0;
			for(k=0; k<Tuner->CH_Ctrl[i].size; k++)
				ctrlVal += Tuner->CH_Ctrl[i].val[k] * (1 << k);
			*value = ctrlVal;
			return 0;
		}
	}

#ifdef _MXL_INTERNAL
	for (i=0; i<Tuner->MXL_Ctrl_Num; i++)
	{
		if ( controlNum == Tuner->MXL_Ctrl[i].Ctrl_Num )
		{
			ctrlVal = 0;
			for(k=0; k<Tuner->MXL_Ctrl[i].size; k++)
				ctrlVal += Tuner->MXL_Ctrl[i].val[k] * (1<<k);
			*value = ctrlVal;
			return 0;
		}
	}
#endif
	return 1;
}

/**
 *                                                                           
 * Function:       MXL_ControlRegRead                                        
 *                                                                           
 * Description:    Retrieve the register addresses and count related to a    
 *				   a specific control name									 
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner_struct  : structure defined at higher level         
 *                 ControlName   : Control Name                              
 *                                                                           
 * Outputs:                                                                  
 *                 RegNum  : returned register address array                 
 *				   count   : returned register count related to a control    
 *                                                                           
 * Return:                                                                   
 *                 0 : Successful read                                       
 *                 -1 : Invalid control name                                 
 *                                                                           
 */
WORD MXL_ControlRegRead(Tuner_struct *Tuner, WORD controlNum, BYTE *RegNum, int * count)
{
	WORD i, j, k;
	WORD Count;

	for (i=0; i<Tuner->Init_Ctrl_Num; i++)
	{
		if ( controlNum == Tuner->Init_Ctrl[i].Ctrl_Num )
		{
			Count = 1;
			RegNum[0] = (BYTE)(Tuner->Init_Ctrl[i].addr[0]);

			for(k=1; k<Tuner->Init_Ctrl[i].size; k++)
			{
				for (j= 0; j<Count; j++)
				{
					if (Tuner->Init_Ctrl[i].addr[k] != RegNum[j])
					{
						Count ++;
						RegNum[Count-1] = (BYTE)(Tuner->Init_Ctrl[i].addr[k]);
					}
				}

			}
			*count = Count;
			return 0;
		}
	}
	for (i=0; i<Tuner->CH_Ctrl_Num; i++)
	{
		if ( controlNum == Tuner->CH_Ctrl[i].Ctrl_Num )
		{
			Count = 1;
			RegNum[0] = (BYTE)(Tuner->CH_Ctrl[i].addr[0]);

			for(k=1; k<Tuner->CH_Ctrl[i].size; k++)
			{
				for (j= 0; j<Count; j++)
				{
					if (Tuner->CH_Ctrl[i].addr[k] != RegNum[j])
					{
						Count ++;
						RegNum[Count-1] = (BYTE)(Tuner->CH_Ctrl[i].addr[k]);
					}
				}
			}
			*count = Count;
			return 0;
		}
	}
#ifdef _MXL_INTERNAL
	for (i=0; i<Tuner->MXL_Ctrl_Num; i++)
	{
		if ( controlNum == Tuner->MXL_Ctrl[i].Ctrl_Num )
		{
			Count = 1;
			RegNum[0] = (BYTE)(Tuner->MXL_Ctrl[i].addr[0]);

			for(k=1; k<Tuner->MXL_Ctrl[i].size; k++)
			{
				for (j= 0; j<Count; j++)
				{
					if (Tuner->MXL_Ctrl[i].addr[k] != RegNum[j])
					{
						Count ++;
						RegNum[Count-1] = (BYTE)Tuner->MXL_Ctrl[i].addr[k];
					}
				}
			}
			*count = Count;
			return 0;
		}
	}
#endif
	*count = 0;
	return 1;
}

/**
 *                                                                           
 * Function:       MXL_RegWriteBit                                           
 *                                                                           
 * Description:    Write a register for specified register address,          
 *                 register bit and register bit value                          
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Inputs:                                                                   
 *                 Tuner_struct  : structure defined at higher level         
 *                 address       : register address                          
 *				   bit			 : register bit number						 
 *				   bitVal		 : register bit value                        
 *                                                                           
 * Outputs:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Return:                                                                   
 *                 NONE                                                      
 *                                                                           
 */
void MXL_RegWriteBit(Tuner_struct *Tuner, BYTE address, BYTE bit, BYTE bitVal)
{
	int i;

	/* Declare Local Constants */
	const BYTE AND_MAP[8] = {
		0xFE, 0xFD, 0xFB, 0xF7, 
		0xEF, 0xDF, 0xBF, 0x7F };
	
	const BYTE OR_MAP[8] = {
		0x01, 0x02, 0x04, 0x08,
		0x10, 0x20, 0x40, 0x80 };

	for(i=0; i<Tuner->TunerRegs_Num; i++) {
		if ( Tuner->TunerRegs[i].Reg_Num == address ) {
			if (bitVal)
				Tuner->TunerRegs[i].Reg_Val |= OR_MAP[bit];
			else
				Tuner->TunerRegs[i].Reg_Val &= AND_MAP[bit];
			break;
		}
	}
};


/**
 *                                                                           
 * Function:       MXL_Ceiling                                               
 *                                                                           
 * Description:    Complete to closest increment of resolution               
 *                                                                           
 * Globals:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Functions used:                                                           
 *                 NONE                                                      
 *                                                                           
 * Inputs:                                                                   
 *                 value       : Input number to compute                     
 *                 resolution  : Increment step                              
 *                                                                           
 * Outputs:                                                                  
 *                 NONE                                                      
 *                                                                           
 * Return:                                                                   
 *                Computed value                                             
 *                                                                           
 */
DWORD MXL_Ceiling( DWORD value, DWORD resolution )
{
	return (value/resolution + (value%resolution > 0 ? 1 : 0));
};

/**
 * Retrieve the Initialzation Registers
 */
WORD MXL_GetInitRegister(Tuner_struct *Tuner, BYTE * RegNum, BYTE *RegVal, int *count) 
{
	WORD status = 0;
	int i;

	BYTE RegAddr[] = {11, 12, 13, 22, 32, 43, 44, 53, 56, 59, 73, 
							   76, 77, 91, 134, 135, 137, 147,
							   156, 166, 167, 168, 25 };
	*count = sizeof(RegAddr) / sizeof(BYTE);
	
	status += MXL_BlockInit(Tuner);

	for (i=0; i< *count; i++)
	{
		RegNum[i] = RegAddr[i];
		status += MXL_RegRead(Tuner, RegNum[i], &RegVal[i]);
	}

	return status;
}

WORD MXL_GetCHRegister(Tuner_struct *Tuner, BYTE * RegNum, BYTE *RegVal, int *count) 
{
	WORD status = 0;
	int i;

/** add 77, 166, 167, 168 register for 2.6.12 */
#ifdef _MXL_PRODUCTION
	BYTE RegAddr[] = {14, 15, 16, 17, 22, 43, 65, 68, 69, 70, 73, 92, 93, 106, 
							   107, 108, 109, 110, 111, 112, 136, 138, 149, 77, 166, 167, 168 };
#else
	BYTE RegAddr[] = {14, 15, 16, 17, 22, 43, 68, 69, 70, 73, 92, 93, 106, 
							   107, 108, 109, 110, 111, 112, 136, 138, 149, 77, 166, 167, 168 };
#endif

	*count = sizeof(RegAddr) / sizeof(BYTE);

	for (i=0; i< *count; i++)
	{
		RegNum[i] = RegAddr[i];
		status += MXL_RegRead(Tuner, RegNum[i], &RegVal[i]);
	}

	return status;

}

WORD MXL_GetCHRegister_ZeroIF(Tuner_struct *Tuner, BYTE * RegNum, BYTE *RegVal, int *count) 
{
	WORD status = 0;
	int i;

	BYTE RegAddr[] = {43, 136};

	*count = sizeof(RegAddr) / sizeof(BYTE);

	for (i=0; i<*count; i++)
	{
		RegNum[i] = RegAddr[i];
		status += MXL_RegRead(Tuner, RegNum[i], &RegVal[i]);
	}
	return status;

}

WORD MXL_GetCHRegister_LowIF(Tuner_struct *Tuner, BYTE * RegNum, BYTE *RegVal, int *count)
{
	WORD status = 0;
	int i;

	BYTE RegAddr[] = {138};

	*count = sizeof(RegAddr) / sizeof(BYTE);

	for (i=0; i<*count; i++)
	{
		RegNum[i] = RegAddr[i];
		status += MXL_RegRead(Tuner, RegNum[i], &RegVal[i]);
	}
	return status;

}

WORD MXL_GetMasterControl(BYTE *MasterReg, int state) 
{
	if (state == 1) /** Load_Start */
		*MasterReg = 0xF3;
	if (state == 2) /** Power_Down */
		*MasterReg = 0x41;
	if (state == 3) /** Synth_Reset */
		*MasterReg = 0xB1;
	if (state == 4) /** Seq_Off */
		*MasterReg = 0xF1;

	return 0;
}

#ifdef _MXL_PRODUCTION
WORD MXL_VCORange_Test(Tuner_struct *Tuner, int VCO_Range) 
{
    WORD status = 0;
    
   if (VCO_Range == 1) {
         status += MXL_ControlWrite(Tuner, RFSYN_EN_DIV, 1);
         status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_DIVM, 1 );
         status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT, 1 );
         status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS, 1 );
         status += MXL_ControlWrite(Tuner, DN_SEL_FREQ, 0 );
         if (Tuner->Mode == 0 && Tuner->IF_Mode == 1) /* Analog Low IF Mode */
         {
             status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 1 );
             status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 8 );
             status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 56 );
             status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, 180224 );
         }
         if (Tuner->Mode == 0 && Tuner->IF_Mode == 0) /* Analog Zero IF Mode */
         {
             status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 1 );
             status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 8 );
             status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 56 );
             status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, 222822 );
         }
         if (Tuner->Mode == 1) /* Digital Mode */
         {
             status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 1 );
             status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 8 );
             status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 56 );
             status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, 229376 );
         }
    }

    if (VCO_Range == 2) {
         status += MXL_ControlWrite(Tuner, RFSYN_EN_DIV, 1);
         status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_DIVM, 1 );
         status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT, 1 );
         status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS, 1 );
         status += MXL_ControlWrite(Tuner, DN_SEL_FREQ, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 1 );
         status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 40 );
         status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 41 );
         if (Tuner->Mode == 0 && Tuner->IF_Mode == 1) /* Analog Low IF Mode */
         {
             status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 1 );
             status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 40 );
             status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 42 );
             status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, 206438 );
         }
         if (Tuner->Mode == 0 && Tuner->IF_Mode == 0) /* Analog Zero IF Mode */
         {
             status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 1 );
             status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 40 );
             status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 42 );
             status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, 206438 );
         }
         if (Tuner->Mode == 1) /* Digital Mode */
         {
             status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 1 );
             status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 40 );
             status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 41 );
             status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, 16384 );
         }
    }

    if (VCO_Range == 3) {
         status += MXL_ControlWrite(Tuner, RFSYN_EN_DIV, 1);
         status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_DIVM, 1 );
         status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT, 1 );
         status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS, 1 );
         status += MXL_ControlWrite(Tuner, DN_SEL_FREQ, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 8 );
         status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 42 );
         if (Tuner->Mode == 0 && Tuner->IF_Mode == 1) /* Analog Low IF Mode */
         {
             status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 0 );
             status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 8 );
             status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 44 );
             status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, 173670 );
         }
         if (Tuner->Mode == 0 && Tuner->IF_Mode == 0) /* Analog Zero IF Mode */
         {
             status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 0 );
             status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 8 );
             status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 44 );
             status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, 173670 );
         }
         if (Tuner->Mode == 1) /* Digital Mode */
         {
             status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 0 );
             status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 8 );
             status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 42 );
             status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, 245760 );
         }
    }

    if (VCO_Range == 4) {
         status += MXL_ControlWrite(Tuner, RFSYN_EN_DIV, 1);
         status += MXL_ControlWrite(Tuner, RFSYN_EN_OUTMUX, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_SEL_DIVM, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_DIVM, 1 );
         status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_OUT, 1 );
         status += MXL_ControlWrite(Tuner, RFSYN_RF_DIV_BIAS, 1 );
         status += MXL_ControlWrite(Tuner, DN_SEL_FREQ, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 0 );
         status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 40 );
         status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 27 );
         if (Tuner->Mode == 0 && Tuner->IF_Mode == 1) /* Analog Low IF Mode */
         {
             status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 0 );
             status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 40 );
             status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 27 );
             status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, 206438 );
         }
         if (Tuner->Mode == 0 && Tuner->IF_Mode == 0) /* Analog Zero IF Mode */
         {
             status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 0 );
             status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 40 );
             status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 27 );
             status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, 206438 );
         }
         if (Tuner->Mode == 1) /* Digital Mode */
         {
             status += MXL_ControlWrite(Tuner, RFSYN_SEL_VCO_HI, 0 );
             status += MXL_ControlWrite(Tuner, RFSYN_VCO_BIAS, 40 );
             status += MXL_ControlWrite(Tuner, CHCAL_INT_MOD_RF, 27 );
             status += MXL_ControlWrite(Tuner, CHCAL_FRAC_MOD_RF, 212992 );
         }
   }
    
    return status;
}

WORD MXL_Hystersis_Test(Tuner_struct *Tuner, int Hystersis) 
{
	WORD status = 0;

	if (Hystersis == 1)
		status += MXL_ControlWrite(Tuner, DN_BYPASS_AGC_I2C, 1);

	return status;
}
#endif
