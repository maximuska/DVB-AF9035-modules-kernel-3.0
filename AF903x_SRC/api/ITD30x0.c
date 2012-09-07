
/*! 
*******************************************************************************
* \FILE <ITD30x0.CPP>
* 
* \BRIEF
*    <ITD30x0 MP user API v2.2 - the part of implementation> 
*		- Source Integration 
*		- Added "Reset PLL" Option
*		- Added "Power-down" Mode
*               - Added "A,B type Selection"
*		- RSSI Computing Option
*
* \DATE
*    < 2006-08-28 >
*
* \AUTHOR
*    Integrant Technologies. Inc.
*    - <Dennis Hong>                    <Dennis.Hong@analog.com>
*******************************************************************************
*/

#include "ITD30x0.h"


/* Global Variable */
int				i;
int				ADCOUT;
int				cnt_loop = 15;
long			TUNER_REFCLK; 
long			LO_FREQ;  
long			PLL_FREQ;
long			PLL_N, PLL_F, PLLR = 1;
int				old_VCO_BAND;
int				DIVSEL;	
int				BAND;
int				VCORG;
long			TUNER_IF;
long			TUNER_RF;
int				RegRFAGC = 0;
int				RegDATA71, RegDATA72, RegData85;
long			fInpRFPOW = 0;
int				SPLIT_ID;
INT_U8			CHIP_TYPE;
INT_U8			CurBAND = CUR_RF_BAND3;
INT_U8			FCCLK;
INT_U8			RFAGC_SPEED_L;	/* SPEED[2:0] we had a resolution of 10 bits for RFAGC */
INT_U8			RFAGC_SPEED_H;	/* SPEED[9:3] */
INT_U8			IFAGC_SPEED;
INT_U8			AGCMODE = 0;	/* If this value = 0, Internal AGC mode. */
								/* If this value = 1, External AGC mode  */


/* Band - III					        */
/* LO Freq (MHz)    BAND VCORGI2CDIVSEL */
/* From    	To(dec)	                    */
RG_NUM_BAND  BAND_III_PLL_TABLE[26]=
{
	{160000,	162850, 2,	0,	1},
	{162850,	165350, 2,	1,	1},
	{165350,	168350, 2,	2,	1},
	{168350,	171600,  2,	3,  	1},
	{171600,	174800,  2,	4,  	1},
	{174800 ,	176350, 2,	5,	1},
	{176350,	179850, 2,	6,	1},
	{179850,	183350, 2,	7,	1},
	{183350,	188850, 2,	8,	1},
	{188850,	191850, 2,	9,	1},
	{191850,	195850, 2,	10,	1},
	{195850,	200850, 2,	11,	1},
	{200850,	205850, 2,	12,	1},
	{205850,	211850, 2,	13,	1},
	{211850,	216850, 2,	14,	1},
	{216850,	221850, 2,	15,	1},
	{221850,	226850, 0,	6,	2},
	{226850,	231850, 0,	7,	2},
	{231850,	236850, 0,	8,	2},
	{236850,	240850, 0,	9,	2},
	{240850,	247850, 0,	10, 	2},
	{247850,	254850, 0,	11, 	2},
	{254850,	261850, 0,	12,	2},
	{261850,	268850, 0,	13, 	2},
	{268850,	277850, 0,	14, 	2},
	{277850,	285850, 0,	15, 	2}
};

RG_NUM_BAND LBAND_PLL_TABLE[2]=
{
  {1445000,	1460000,	1,	1,	3},
  {1460000,	1495000,	1,	2,	3}
};

RG_NUM_BAND FMBAND_PLL_TABLE[19]=
{
	{82500,		83000,		2,	2,	0},
	{83000,	  	84300,	2,	3,	0},
	{84300,		86000,		2,	4,	0},
	{86000,	  	87300,	2,	5,	0},
	{87300,		89000,		2,	6,	0},
	{89000,	  	91000,		2,	7,	0},
	{91000,	  	93000,		2,	8,	0},
	{93000,	  	95000,		2,	9,	0},
	{95000,	  	97000,		2,	10,	0},
	{97000,	  	99100,	2,	11,	0},
	{99100,		102000,	2,	12,	0},
	{102000,	  	103000,	0,	2,	1},
	{103000,	  	104500,	0,	3,	1},
	{104500,		107000,	0,	4,	1},
	{107000,	  	109000,	0,	5,	1},
	{109000,	  	111000,	0,	6,	1},
	{111000,	  	114000,	0,	7,	1},
	{114000,	  	116300,	0,	8,	1},
	{116300,		118000,	0,	9,	1}
};								

DIV_CURRENT_SETTING ITD30x0MP_DCSET_A[4]= 
{
	{0,0},  /* DIVSEL, DIVCON */
	{1,1},
	{2,2},
	{3,6}
};

DIV_CURRENT_SETTING ITD30x0MP_DCSET_B[4]= 
{
	{0,0},  /* DIVSEL, DIVCON */
	{1,1},
	{2,2},
	{3,7}
};

long BAND3[BAND3CH_MAX]= {   /*5A*/174928, /*5B*/176640, /*5C*/178352,\
/*5D*/180064, /*6A*/181936, /*6B*/183648, /*6C*/185360, /*6D*/187072,\
/*7A*/188928, /*7B*/190640, /*7C*/192352, /*7D*/194064, /*8A*/195936,\
/*8B*/197648, /*8C*/199360, /*8D*/201072, /*9A*/202928, /*9B*/204640,\
/*9C*/206352, /*9D*/208064, /*10A*/209936,/*10B*/211648,/*10C*/213360,\
/*10D*/215072,/*11A*/216928,/*11B*/218640,/*11C*/220352,/*11D*/222064,\
/*12A*/223936,/*12B*/225648,/*12C*/227360,/*12D*/229072,/*13A*/230784,\
/*13B*/232496,/*13C*/234208,/*13D*/235776,/*13E*/237488,/*13F*/239200};

long KBAND[KBANDCH_MAX]={      /*8A*/181280,/*8B*/183008,/*8C*/184736,\
  /*10A*/193280,/*10B*/195008,/*10C*/196736,/*12A*/205280,/*12B*/207008,\
  /*12C*/208736};


long LBAND[LBANDCH_MAX]= {/*LA*/1452960,/*LB*/1454672,/*LC*/1456384,/*LD*/1458096, \
   /*LE*/1459808,/*LF*/1461520,/*LG*/1463232,/*LH*/1464944,/*LI*/1466656,\
   /*LJ*/1468386,/*LK*/1470080,/*LL*/1471792,/*LM*/1473504,/*LN*/1475216,\
   /*LO*/1476928,/*LP*/1478640,/*LQ*/1480352,/*LR*/1482064,/*LS*/1483776,\
   /*LT*/1485488,/*LU*/1487200,/*LV*/1488912,/*LW*/1490624};

INT_U8* INITVAL;
INT_U8 INITVAL_B3[68]=
{
	/*00:0x73*/			/*01:0x74*/			/*02:0x75*/			/*03:0x76*/			/*04:0x77*/
	0x80,				0x8a,				0x8d,				0xb3/*0xc3->0xb3*/,	0x11,
	/*05:0x78*/			/*06:0x79*/			/*07:0x7A*/			/*08:0x7B*/			/*09:0x7C*/
	0x03,				0x00,				0x20,				0x40,				0x20,
	/*10:0x7D*/			/*11:0x7E*/			/*12:0x7F*/			/*13:0x80*/			/*14:0x81*/
	0x06,				0x05,				0xb0/*0x90->0xb0*/,	0x00,				0x33,
	/*15:0x82*/			/*16:0x83*/			/*17:0x84*/			/*18:0x85*/			/*19:0x86*/
	0x90,				0x09,				0x32,				0x88,				0xfd,
	/*20:0x87*/			/*21:0x88*/			/*22:0x89*/			/*23:0x8A*/			/*24:0x8B*/
	0xf1,				0x2b,				0xff,				0xb2,				0x94,
	/*25:0x8C*/			/*26:0x8D*/			/*27:0x8E*/			/*28:0x8F*/			/*29:0x90*/
	0xce,				0x55/*0x20->0x55*/,	0x0a,				0x7f,				0x81,
	/*30:0x91*/			/*31:0x92*/			/*32:0x93*/			/*33:0x94*/			/*34:0x95*/
	0x7f,				0x81,				0x01,				0xc6,				0x40,
	/*35:0x96*/			/*36:0x97*/			/*37:0x98*/			/*38:0x99*/			/*39:0x9A*/
	0x46,				0x7e/*0x70->0x7e*/,	0x13,				0x05,				0x00,
	/*40:0x9B*/			/*41:0x9C*/			/*42:0x9D*/			/*43:0x9E*/			/*44:0x9F*/
	0x02/*0xc2->0x02*/,	0x00/*0x5a->0x00*/,	0x00/*0x63->0x00*/,	0xe0/*0xe7->0xe0*/,	0x80/*0x83->0x80*/,
	/*45:0xA0*/			/*46:0xA1*/			/*47:0xA2*/			/*48:0xA3*/			/*49:0xA4*/
	0x01/*0x05->0x01*/,	0xb0,				0x7e,				0x7f,				0x00/*0x58->0x00*/,
	/*50:0xA5*/			/*51:0xA6*/			/*52:0xA7*/			/*53:0xA8*/			/*54:0xA9*/
	0x1f,				0x1f,				0x1f,				0x1f,				0x1f,
	/*55:0xAA*/			/*56:0xAB*/			/*57:0xAC*/			/*58:0xAD*/			/*59:0xAE*/
	0x1f,				0x1f,				0x1f,				0x1f,				0x1f,
	/*60:0xAF*/			/*61:0xB0*/			/*62:0xB1*/			/*63:0xB2*/			/*64:0xB3*/
	0x1f,				0x1f,				0x1f,				0x1f,				0x1f,
	/*65:0xB4*/			/*66:0xB5*/			/*67:0xB6*/
	0x1f,				0x21,				0x08
};

INT_U8 INITVAL_LB[68]=
{
	/*00:0x73*/			/*01:0x74*/			/*02:0x75*/			/*03:0x76*/			/*04:0x77*/
	0x80/*0xf0->0x80*/,	0x9a,				0x82,				0xb3/*0xc3->0xb3*/,	0x11,
	/*05:0x78*/			/*06:0x79*/			/*07:0x7A*/			/*08:0x7B*/			/*09:0x7C*/
	0x83,/*0x8b->0x83*/	0x00/*0x92->0x00*/,	0x20/*0xcb->0x20*/,	0x40/*0xc6->0x40*/, 0x20/*0xff->0x20*/,
	/*10:0x7D*/			/*11:0x7E*/			/*12:0x7F*/			/*13:0x80*/			/*14:0x81*/
	0x06/*0xcc->0x06*/,	0x05/*0x04->0x05*/,	0xb0/*0x90->0xb0*/,	0x00,				0x33/*0x31->0x33*/,
	/*15:0x82*/			/*16:0x83*/			/*17:0x84*/			/*18:0x85*/			/*19:0x86*/
	0x70,				0x0d,/*0x2d->0x0d*/	0x3b,				0x30/*0x34->0x30*/,	0xaa,
	/*20:0x87*/			/*21:0x88*/			/*22:0x89*/			/*23:0x8A*/			/*24:0x8B*/
	0xd0,				0x2e,				0xff,				0xb2/*0xba->0xb2*/,	0x94,
	/*25:0x8C*/			/*26:0x8D*/			/*27:0x8E*/			/*28:0x8F*/			/*29:0x90*/
	0xce,				0x55/*0x20->0x55*/,	0x2a/*0x24->0x2a*/,	0x7f/*0x3f->0x7f*/,	0x81,
	/*30:0x91*/			/*31:0x92*/			/*32:0x93*/			/*33:0x94*/			/*34:0x95*/
	0x7f,				0x81,				0x01,				0xc6,				0x40/*0x3a->0x40*/,
	/*35:0x96*/			/*36:0x97*/			/*37:0x98*/			/*38:0x99*/			/*39:0x9A*/
	0x46,				0x7e,				0x13,				0x05/*0x00->0x05*/,	0x00,
	/*40:0x9B*/			/*41:0x9C*/			/*42:0x9D*/			/*43:0x9E*/			/*44:0x9F*/
	0x02/*0x00->0x02*/,	0x00/*0x04->0x00*/,	0x00,				0xe0/*0x40->0xe0*/,	0x80/*0x83->0x80*/,
	/*45:0xA0*/			/*46:0xA1*/			/*47:0xA2*/			/*48:0xA3*/			/*49:0xA4*/
	0x01/*0x03->0x01*/,	0xb0/*0xb2->0xb0*/,	0x7e,				0x7f,				0x00/*0x84->0x00*/,
	/*50:0xA5*/			/*51:0xA6*/			/*52:0xA7*/			/*53:0xA8*/			/*54:0xA9*/
	0x1f/*0x2f->0x1f*/,	0x1f,				0x1f,				0x1f,				0x1f,
	/*55:0xAA*/			/*56:0xAB*/			/*57:0xAC*/			/*58:0xAD*/			/*59:0xAE*/
	0x1f,				0x1f,				0x1f,				0x1f,				0x1f,
	/*60:0xAF*/			/*61:0xB0*/			/*62:0xB1*/			/*63:0xB2*/			/*64:0xB3*/
	0x1f,				0x1f,				0x1f,				0x1f,				0x1f,
	/*65:0xB4*/			/*66:0xB5*/			/*67:0xB6*/
	0x1f,				0x21/*0x20->0x21*/,	0x08                                                  
};


void WriteIIC (INT_U8 address, INT_U8 value) {
	Standard_writeTunerRegisters (Integrant_ITD3020_EXT_demodulator, Integrant_ITD3020_EXT_chip, address, 1, &value);
}


void WriteIIC_MultiByte (INT_U8 address, INT_U8* buffer, INT_U8 bufferLength) {
	Standard_writeTunerRegisters (Integrant_ITD3020_EXT_demodulator, Integrant_ITD3020_EXT_chip, address, bufferLength, buffer);
}


INT_U8 ReadIIC (INT_U8 address) {
	Byte value;

	Standard_readTunerRegisters (Integrant_ITD3020_EXT_demodulator, Integrant_ITD3020_EXT_chip, address, 1, &value);
	return (value);
}


long SetFreq(long iRF) 
{
	SPLIT_ID = ReadIIC(ID1);
	if ( SPLIT_ID >= LBAND_REVISION )
	{
		if (iRF>1000) /* MHz */
		{
			if (TUNER_REFCLK>=20000) /* KHz */
			{
				PLLR=2;
				WriteIIC(W50,(ReadIIC(W50)&0xfc) | 0x01);
				WriteIIC(RCHP0, 0x1F);		/* added by Shane, 2006.10.12, charge pump value change */
			}
			else
			{
				PLLR=1;
				WriteIIC(W50,(ReadIIC(W50)&0xfc));
				WriteIIC(RCHP0, 0x12);		/* added by Shane, 2006.10.12, charge pump value change */
			}
		}
		else
		{
			PLLR=1;
			WriteIIC(W50,(ReadIIC(W50)&0xfc));
			WriteIIC(RCHP0, 0x1F);			/* added by Shane, 2006.10.12, charge pump value change */
		}
	}
	else
	{
		PLLR=1;
		WriteIIC(W50,(ReadIIC(W50)&0xfc));
	}

	LO_FREQ = iRF + TUNER_IF; /* TUNER_IF = 0.85 */
	if (CurBAND==0)      LO_FREQ = RFTuning(LO_FREQ, FMBAND_PLL_TABLE,  FMBAND_TABLE_LEN);
	else if (CurBAND==1) LO_FREQ = RFTuning(LO_FREQ, BAND_III_PLL_TABLE,BAND_III_TABLE_LEN);
	else                 LO_FREQ = RFTuning(LO_FREQ, LBAND_PLL_TABLE,   LBAND_TABLE_LEN);
	
	return LO_FREQ;
}

long RFTuning(long fLO_FREQ, RG_NUM_BAND* pRGBAND, INT_U8 tlen)
{
	int i;
    /* PM 5:37 2006-08-24 Added by Shane(Integrant) */
 	unsigned char fusepon;	/* fuse power on */
	
	cnt_loop = 15;

	if (fLO_FREQ < 120000) {
		if (CurBAND != CUR_RF_FMBAND)
			ITD30x0MP_Tuner_Init();
	} else if (fLO_FREQ < 255000) {
		if (CurBAND != CUR_RF_BAND3)
			ITD30x0MP_Tuner_Init();
	} else if (fLO_FREQ > 1000000) {
		if (CurBAND != CUR_RF_LBAND)
			ITD30x0MP_Tuner_Init();
	}

	for(i=0; i<tlen; i++)  /* BAND RANGE */
	{
		if((fLO_FREQ > pRGBAND[i].lo_from) && (fLO_FREQ <= pRGBAND[i].lo_to))
		{
			/* PARAM1=divsel, PARAM2=lband */
			PLL_FREQ = LO2PLL_Freq(pRGBAND[i].DIVSEL, fLO_FREQ);
			RegData85 = SetPrescaler(PLL_FREQ, TUNER_REFCLK );
			BAND = pRGBAND[i].VCO_BAND;
			VCORG = pRGBAND[i].VCO_RG;
			DIVSEL = pRGBAND[i].DIVSEL;

			WriteIIC(W03, (INITVAL[2] & 0xf0) | VCORG );
			WriteIIC( W16, ( INITVAL[15]&0x0f ) | ( DIVSEL << 4 ) | ( BAND << 6 ) ); 

			{
				PLL_N = PLL_FREQ / (TUNER_REFCLK / PLLR );
				PLL_F = (((PLL_FREQ*1024 / (TUNER_REFCLK / PLLR )) - PLL_N*1024) * (1 << 10));
				RegData85 = (RegData85 & 0xfc) | ((PLL_N >> 8) & 0x03);
				WriteIIC( W18, (Byte) (PLL_N & 0xff) );

				/* 2006-08-24 Added by Shane(Integrant) 		*/
				if(ReadIIC(ID1) >= 0x12 && CurBAND == CUR_RF_LBAND)	/* if the version of chip is over 0x12, it should be checked whether A or B. */
				{
					fusepon = ReadIIC(W29);				/* A,B TYPE SELECTION */
					WriteIIC( W29, (fusepon & 0xFE));
					CHIP_TYPE = ReadIIC(ID2) & 0x10;
					WriteIIC( W29, (fusepon | 0x01));
				}
				else		/* it is A-Type That version of chip is small than 0x12. */
				{
					CHIP_TYPE = 0x10;	/* default Chip Type = A */
				}

				if ( CHIP_TYPE==0x10 ) 
					RegData85 = ( RegData85 & 0xc7 ) | ( ( ITD30x0MP_DCSET_A[DIVSEL].DIVCON ) << 3 );
				else
					RegData85 = ( RegData85 & 0xc7 ) | ( ( ITD30x0MP_DCSET_B[DIVSEL].DIVCON ) << 3 );

				WriteIIC( W19, RegData85 );
				WriteIIC( W20, (Byte) (PLL_F & 0xff) );
				WriteIIC( W21, (Byte) ((PLL_F >> 8)  & 0xff) );
				WriteIIC( W22, (Byte) (INITVAL[21]&0xf0 | ( PLL_F >> 16 ) & 0x0f) );

				PLLReset();

				User_delay(NULL, 1);
			}

			while(1)
			{
				old_VCO_BAND = pRGBAND[i].VCO_BAND;
				ADCOUT = ( ReadIIC(RD9) & 0xf0 ) >> 4;
				if( ADCOUT < 4 ) i--;   
				else if( ADCOUT >  12 ) i++;
				else break;
				
				if((i >= 0) && (i < tlen))
				{
					BAND   = pRGBAND[i].VCO_BAND;
					VCORG  = pRGBAND[i].VCO_RG;
					DIVSEL = pRGBAND[i].DIVSEL;
					WriteIIC( W03, ( INITVAL[2]&0xf0 )  | VCORG );
					WriteIIC( W16, ( INITVAL[15]&0x0f ) | ( DIVSEL << 4 ) | ( BAND << 6 )  );

					if(BAND != old_VCO_BAND)
					{
						PLL_FREQ = LO2PLL_Freq(pRGBAND[i].DIVSEL, LO_FREQ);
						RegData85 = SetPrescaler(PLL_FREQ, TUNER_REFCLK );

						PLL_N = PLL_FREQ / (TUNER_REFCLK / PLLR );
						PLL_F = (((PLL_FREQ*1024 / (TUNER_REFCLK / PLLR )) - PLL_N*1024) * (1 << 10));
						RegData85 = (RegData85 & 0xfc) | ((PLL_N >> 8) & 0x03);
						WriteIIC( W18, (Byte) (PLL_N & 0xff) );

						if ( CHIP_TYPE==0x10 ) 
							RegData85 = ( RegData85&0xc7 ) | ( ( ITD30x0MP_DCSET_A[DIVSEL].DIVCON ) << 3 );		/* A Type */
						else
							RegData85 = ( RegData85&0xc7 ) | ( ( ITD30x0MP_DCSET_B[DIVSEL].DIVCON ) << 3 );		/* B Type */

						WriteIIC( W19, RegData85 );
						WriteIIC( W20, (Byte) (PLL_F & 0xff) );
						WriteIIC( W21, (Byte) ((PLL_F >> 8) & 0xff) );
						WriteIIC( W22, (Byte) (INITVAL[21]&0xf0 | ( PLL_F >> 16 ) & 0x0f) );

						PLLReset();

						User_delay(NULL, 1);
					}
					
					cnt_loop--;
					if(cnt_loop == 0)
						break;
				}
				else
				{
					return -1;
				}
			}
			return fLO_FREQ;
		} 
	}
	return fLO_FREQ;
}

/*! 
******************************************************************************
* \BRIEF
*    <LO2PLL_Freq() change LO Freq. to PLL Freq.> 
*
* \PARAM <int divsel>
*    <Divider Selector(divsel) is used to compute PLL Frequency.>
* \PARAM <long LO_FREQ>
*    <LO Frequency(LO_FREQ) equal RF Freq. + IF Freq.>
*
* \RETURN
*    <long>
******************************************************************************
*/

long LO2PLL_Freq(int divsel,long LO_FREQ) /* LO Freq. to PLL Freq. */
{
	long PLL_FREQ=0;
	switch(divsel)
	{
		case 0:
			PLL_FREQ = LO_FREQ*8;   /* PLLS=8 */
			break;
		case 1:
			PLL_FREQ = LO_FREQ*4;	/* PLLS=4 */
			break;
		case 2:
			PLL_FREQ = LO_FREQ*2;	/* PLLS=2 */
			break;
		case 3:
			PLL_FREQ = LO_FREQ*1;	/* PLLS=1 */
			break;
		default:
			break;
			/* add exceptional condition code  */
	}
	return PLL_FREQ;
}
/*! 
*******************************************************************************
* \BRIEF
*    <FCTuning() is used when Initialized.> 
*
* \PARAM <void>
*
* \RETURN
*    <void>
*******************************************************************************
*/

void FCTuning()    /* Tuning function for Cut-Off Freq. */
{
	int rsv2;

	WriteIIC( W13, 0x40 | ( INITVAL[12] & 0x3f ) ); /* Tune enable, Extune disable */

	User_delay(NULL, 1);
	rsv2 = (ReadIIC(RD1) & 0xf0) >> 4; /* Get CtuneI2C */

	if(rsv2 > 13)
		rsv2 = 13;

	WriteIIC(W13, 0x80 | (INITVAL[12] & 0x3f)); /* Extune enable, Tune disable */
	WriteIIC(W02, (rsv2 << 4) | (INITVAL[1] & 0x0f)); /* Set Extune */
}				

/*! 
*******************************************************************************
* \BRIEF
*    <For Tuner to Initialize, ITD30x0MP_Tuner_Init() is called after power-on> 
*
* \PARAM <void>
*
* \RETURN
*    <void>
*
* \NOTE
*    <before you set, you should select options, TUNER_REFCLK, TUNER_RF.>
*
* \PARAGRAPH <title>
*    <paragraph>
*
* \PARAGRAPH
*    <another paragraph>
*******************************************************************************
*/

void ITD30x0MP_Tuner_Init()														
{
	/* FCCLK, if RF x-tal = 24.576MHz, 0x04. if RF x-tal = 16.384MHz, 0x05. */
	/* if RF x-tal = 19.2MHz, 0x06 */
	if (TUNER_RF < 120000) {
  		CurBAND = CUR_RF_FMBAND;
  		INITVAL = INITVAL_B3;
  	} else if (TUNER_RF < 255000) {
  		CurBAND = CUR_RF_BAND3; 
  		INITVAL = INITVAL_B3;
  	} else if (TUNER_RF > 1000000) {
		CurBAND = CUR_RF_LBAND; 
		INITVAL = INITVAL_LB;
	}

	if(TUNER_REFCLK <= 16384)
	{
		FCCLK = 5; 
		RFAGC_SPEED_L = 7;
		RFAGC_SPEED_H = 0; 
		IFAGC_SPEED = 0x21;
	}
	else if(TUNER_REFCLK <= 19200)
	{ 
		FCCLK = 6; 
		RFAGC_SPEED_L = 7;
		RFAGC_SPEED_H = 0;
		IFAGC_SPEED = 0x21;
	}
	else if(TUNER_REFCLK <= 24576)
	{
		if(CurBAND == CUR_RF_LBAND)
		{
			FCCLK = 4;
			RFAGC_SPEED_L = 1;
			RFAGC_SPEED_H = 3;
			IFAGC_SPEED = 0x20;
		}
		else
		{
			FCCLK = 4;
			RFAGC_SPEED_L = 1;
			RFAGC_SPEED_H = 3;
			IFAGC_SPEED = 0xFF;
		}
	}

	INITVAL[11] = FCCLK;
	INITVAL[27] = AGCMODE << 5 | (INITVAL[27] & 0xdf);
	INITVAL[43] = RFAGC_SPEED_L << 5 | (INITVAL[43] & 0x1f);
	INITVAL[44] = RFAGC_SPEED_H | (INITVAL[44] & 0x80);
	INITVAL[66] = IFAGC_SPEED;

	WriteIIC_MultiByte(W01, INITVAL, 68);

	/* addr 0xb5, IFAGC SPEED, if x-tal = 24.576MHz, 0xff. */
	/* if x-tal = 16.384MHz or 19.2MHz, 0x21.              */
	/* (when agc mode = internal agc, this apply to ...)   */

	PostProcessingAfterInit();
	SetFreq(TUNER_RF);
	
	FCTuning();
}								
/*!
*******************************************************************************
* \BRIEF
*    <PostProcessingAfterInit() is called when initialized.>
*
* \PARAM <void>
*    <void type>
*
* \RETURN
*    <void>
*
* \NOTE
*    <this process have to called for tuner to stable.>
* \PARAGRAPH
*    <External AGC Mode = 0x08, Internal AGC Mode = 0x00>
*******************************************************************************
*/

void PostProcessingAfterInit()
{
	WriteIIC (W48, 0x00);							
	WriteIIC (W49, AGCMODE << 3);		
}

/*! 
*******************************************************************************
* \BRIEF
*    <PowerDown() function is able to switch all blocks on Tuner.> 
*
* \PARAM <bool bOnOff>
*    <all blocks on Tuner is Turn On/Off by bOnOff.>
*
* \RETURN
*    <void>
*
* \NOTE
*    <if bOnOff=1, power down mode    , else bOnOff=0, power up mode.>
*
*******************************************************************************
*/

void PowerDownOnOff(unsigned char bOnOff) 
{
	if (!bOnOff)
	{
		WriteIIC(W48, 0x00);							
		WriteIIC(W49, AGCMODE << 3);	
	}
	else
	{
		WriteIIC(W48, 0x01);							
		WriteIIC(W49, AGCMODE << 3);	
	}
}
/*! 
*******************************************************************************
* \BRIEF
*    <GetRssiValue() Function is used to Get RF Power.> 
*
* \PARAM <void>
*    <void type>
*
* \RETURN
*    <integer value[dBm]>
*
* \NOTE
*    <when this function is called, SNR is not good. 
*     we recommend to call under once per one second. >
*
* \PARAGRAPH <RF Power computing algorithm>
*    <RF input power =  
*    -(RFAGC[8:0]x0.133dB)-(LNAGAIN[0]x22dB)-(MIXGAIN[0]x13dB)-9.5>
*     
*
* \PARAGRAPH
*    <RFAGC addr = 0x71, 0x72, LNAGAIN addr = 0x72[6] MIXERGAIN addr 0x72[7]>>
*******************************************************************************
*/

int GetRssiValue() 
{
	RegDATA71 = ReadIIC (RD10);
	RegDATA72 = ReadIIC (RD11);
	RegRFAGC  = RegDATA71 + ((RegDATA72&0x01)*256);
	fInpRFPOW  = -(RegRFAGC*133) - ((RegDATA72&0x40)>>6)*22000-((RegDATA72&0x80)>>7)*13000-9500;
	fInpRFPOW=fInpRFPOW/1000;
	/*iRFAGC_val = RegRFAGC;*/
	/*iRFPWR_dB = fInpRFPOW;*/
	return fInpRFPOW;
}
/*! 
*******************************************************************************
* \BRIEF
*    <GetPLLStatus() function inform us the status of PLL lock.>
*
* \PARAM <void>
*    <void type>
*
* \RETURN
*    <bool : True or False>
*
* \NOTE
*    <if this bit = 1, Lock else unLock >
*******************************************************************************
*/

unsigned char GetPLLStatus()
{
	return (ReadIIC(RD2) & 0x01);  
}
/*! 
*******************************************************************************
* \BRIEF
*    <PLLReset() function is used to restart for PLL block. > 
*
* \PARAM <void>
*
* \RETURN
*    <void>
*
* \NOTE
*    <Call this function after PLL-Setting>
*******************************************************************************
*/

void PLLReset()
{
	unsigned char data, data_Low, data_High;

	data = INITVAL[16];
	data_Low = data & 0xfd;
	data_High = data & 0xff | 0x02;

	WriteIIC(W17,data_Low);
	WriteIIC(W17,data_High);
	WriteIIC(W17,data_Low);
}

INT_U8 SetPrescaler(long pllfreq, long iREF)
{
  unsigned char data;

  data = INITVAL[18] & 0x3f;

  if ((pllfreq/(iREF/PLLR))<64)     
  {
    return (data | 0x80); /* PC4 */
  }
  else
  {
     return (data | 0x00); /* PC8 */
  }
}
