
/*! 
*******************************************************************************
* \FILE <ITD30x0.H>
*
* \BRIEF
*    <ITD30x0 MP user API v2.2 - the part of declaration> 
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
*    - <Dennis Hong>                    <chatmunk@integrant.com>
*******************************************************************************
*/
#include "standard.h"

extern Demodulator* Integrant_ITD3020_EXT_demodulator;
extern Byte Integrant_ITD3020_EXT_chip;


#pragma once

/* Register Map Define */
#define RD0		100     /*0x64*/
#define ID1		101     /*0x65*/
#define ID2		102     /*0x66*/
#define ID3		103     /*0x67*/
#define RD1		104     /*0x68*/
#define RD2		105     /*0x69*/
#define RD3		106     /*0x6a*/
#define RD4		107     /*0x6b*/
#define RD5		108     /*0x6c*/
#define RD6		109     /*0x6d*/
#define RD7		110     /*0x6e*/
#define RD8		111     /*0x6f*/
#define RD9		112     /*0x70*/
#define RD10	113     /*0x71*/
#define RD11	114     /*0x72*/
#define W01		115     /*0x73*/
#define W02		116     /*0x74*/
#define W03		117     /*0x75*/
#define W04		118     /*0x76*/
#define W05		119     /*0x77*/
#define W06		120     /*0x78*/
#define W07		121     /*0x79*/
#define W08		122     /*0x7a*/
#define W09		123     /*0x7b*/
#define W10		124     /*0x7c*/
#define W11		125     /*0x7d*/
#define W12		126     /*0x7e*/
#define W13		127     /*0x7f*/
#define W14		128     /*0x80*/
#define W15		129     /*0x81*/
#define W16		130     /*0x82*/
#define W17		131     /*0x83*/
#define W18		132     /*0x84*/
#define W19		133     /*0x85*/
#define W20		134     /*0x86*/
#define W21		135     /*0x87*/
#define W22		136     /*0x88*/
#define W23		137     /*0x89*/
#define W24		138     /*0x8a*/
#define W25		139     /*0x8b*/
#define W26		140     /*0x8c*/
#define W27		141     /*0x8d*/
#define W28		142     /*0x8e*/
#define W29		143     /*0x8f*/
#define W30		144     /*0x90*/
#define W31		145     /*0x91*/
#define W32		146     /*0x92*/
#define W33		147     /*0x93*/
#define W34		148     /*0x94*/
#define W35		149     /*0x95*/
#define W36		150     /*0x96*/
#define W37		151     /*0x97*/
#define W38		152     /*0x98*/
#define W39		153     /*0x99*/
#define W40		154     /*0x9a*/
#define W41		155     /*0x9b*/
#define W42		156     /*0x9c*/
#define W43		157     /*0x9d*/
#define W44		158     /*0x9e*/
#define W45		159     /*0x9f*/
#define W46		160     /*0xa0*/
#define W47		161     /*0xa1*/
#define W48		162     /*0xa2*/
#define W49		163     /*0xa3*/
#define W50		164     /*0xa4*/
#define RCHP0	165     /*0xa5*/
#define RCHP1	166     /*0xa6*/
#define RCHP2	167     /*0xa7*/
#define RCHP3	168     /*0xa8*/
#define RCHP4	169     /*0xa9*/
#define RCHP5	170     /*0xaa*/
#define RCHP6	171     /*0xab*/
#define RCHP7	172     /*0xac*/
#define RCHP8	173     /*0xad*/
#define RCHP9	174     /*0xae*/
#define RCHP10	175   /*0xaf*/
#define RCHP11	176   /*0xb0*/
#define RCHP12	177   /*0xb1*/
#define RCHP13	178   /*0xb2*/
#define RCHP14	179   /*0xb3*/
#define RCHP15	180   /*0xb4*/
#define DIVAGO	181   /*0xb5*/
#define AGODIS	182   /*0xb6*/
#define CUR_RF_FMBAND 0
#define CUR_RF_BAND3  1
#define CUR_RF_LBAND  2
#define REF_CLK16M 16     
#define REF_CLK16_384M 16384	/* => representation ~Hz */
#define REF_CLK19_2M 19200		/* => representation ~Hz */
#define REF_CLK24_576M 24576	/* => representation ~Hz */

#define BAND3CH_5A 0
#define BAND3CH_5B 1
#define BAND3CH_5C 2
#define BAND3CH_5D 3
#define BAND3CH_6A 4
#define BAND3CH_6B 5
#define BAND3CH_6C 6
#define BAND3CH_6D 7
#define BAND3CH_7A 8
#define BAND3CH_7B 9
#define BAND3CH_7C 10
#define BAND3CH_7D 11
#define BAND3CH_8A 12
#define BAND3CH_8B 13
#define BAND3CH_8C 14
#define BAND3CH_8D 15
#define BAND3CH_9A 16
#define BAND3CH_9B 17
#define BAND3CH_9C 18
#define BAND3CH_9D 19
#define BAND3CH_10A 20
#define BAND3CH_10B 21
#define BAND3CH_10C 22
#define BAND3CH_10D 23
#define BAND3CH_11A 24
#define BAND3CH_11B 25
#define BAND3CH_11C 26
#define BAND3CH_11D 27
#define BAND3CH_12A 28
#define BAND3CH_12B 29
#define BAND3CH_12C 30
#define BAND3CH_12D 31
#define BAND3CH_13A 32
#define BAND3CH_13B 33
#define BAND3CH_13C 34
#define BAND3CH_13D 35
#define BAND3CH_13E 36
#define BAND3CH_13F 37
#define BAND3CH_MAX 38

#define KBANDCH_8A 0
#define KBANDCH_8B 1
#define KBANDCH_8C 2
#define KBANDCH_10A 3
#define KBANDCH_10B 4
#define KBANDCH_10C 5
#define KBANDCH_12A 6
#define KBANDCH_12B 7
#define KBANDCH_12C 8
#define KBANDCH_MAX 9

#define LBANDCH_LA	0
#define LBANDCH_LB	1
#define LBANDCH_LC	2
#define LBANDCH_LD	3
#define LBANDCH_LE	4
#define LBANDCH_LF	5
#define LBANDCH_LG	6
#define LBANDCH_LH	7
#define LBANDCH_LI	8
#define LBANDCH_LJ	9
#define LBANDCH_LK	10
#define LBANDCH_LL	11
#define LBANDCH_LM	12
#define LBANDCH_LN	13
#define LBANDCH_LO	14
#define LBANDCH_LP	15
#define LBANDCH_LQ	16
#define LBANDCH_LR	17
#define LBANDCH_LS	18
#define LBANDCH_LT	19
#define LBANDCH_LU	20
#define LBANDCH_LV	21
#define LBANDCH_LW	22
#define LBANDCH_MAX	23

#define LBAND_REVISION 0x12
#define LOW_IF_FREQ850  850		/* => representation ~Hz */
#define BAND_III_TABLE_LEN 26
#define LBAND_TABLE_LEN 2
#define FMBAND_TABLE_LEN 19

#define INT_U8 unsigned char

typedef struct 
{
	long lo_from;		/* LO low boundary */
	long lo_to;			/* LO high boundary */
	INT_U8 VCO_BAND;	/* VCO_BAND */
	INT_U8 VCO_RG;		/* VCO_Range */
	INT_U8 DIVSEL;		/* Division selector */
} RG_NUM_BAND;

typedef struct    
{
	INT_U8 DIVSEL;		/* Div sel 0~3 */
	INT_U8 DIVCON;		/* Divcon 3bit */ 
} DIV_CURRENT_SETTING;

extern		long BAND3[BAND3CH_MAX];
extern		long KBAND[KBANDCH_MAX];
extern		long LBAND[LBANDCH_MAX];
extern 		int		i;
extern 		int		ADCOUT;
extern 		int		cnt_loop;
extern 		long	TUNER_REFCLK; 
extern 		long	LO_FREQ;  
extern 		long	PLL_FREQ;
extern 		long	PLL_N, PLL_F;
extern 		int		old_VCO_BAND;
extern 		int		DIVSEL;	
extern 		int		BAND;
extern 		int		VCORG;
extern 		long	TUNER_IF;
extern 		long	TUNER_RF;
extern 		int		RegRFAGC;
extern 		int		RegDATA71, RegDATA72;
extern 		long	fInpRFPOW;
extern 		INT_U8	FCCLK;
extern 		INT_U8	RFAGC_SPEED_L; /* SPEED[2:0]   we had a resolution of 10 bits for RFAGC */
extern 		INT_U8	RFAGC_SPEED_H; /* SPEED[9:3] */
extern 		INT_U8	IFAGC_SPEED;
extern		INT_U8	AGCMODE;
extern		INT_U8	CurBAND;
void PostProcessingAfterInit();
void ITD30x0MP_Tuner_Init();
long SetFreq(long iRF); /* Set RF Freq. Function. */
void PLLReset();
unsigned char GetPLLStatus();
long LO2PLL_Freq(int divsel,long LO_FREQ);
void usbSetSpeed(unsigned char bSpeedonUSB);
long RFTuning(long fLO_FREQ, RG_NUM_BAND* pRGBAND, INT_U8 tlen);
INT_U8 SetPrescaler(long pllfreq, long iREF);
