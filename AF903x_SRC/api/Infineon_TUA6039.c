/**
 * @(#)Infineon_TUA6039.cpp
 *
 * ==========================================================
 * Version: 2.0
 * Date:    2008.07.02
 * ==========================================================
 *
 * ==========================================================
 * History:
 *
 * Date         Author      Description
 * ----------------------------------------------------------
 *
 * 2008.07.02   Tom Lin     added tuner version
 * ==========================================================
 *
 * Copyright 2005 Afatech, Inc. All rights reserved.
 *
 */


//#include <stdio.h> //for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "Infineon_TUA6039_Script.h"


//#define ENABLE_AGC_CTRL
//#define Step_Index 3;//166700UL
#define IF_FREQ 36167

//#define AGC_115DB 0x00
#define AGC_115_MAXDB 0x10
#define AGC_112_DEFDB 0x20
#define AGC_109DB 0x30
#define AGC_106DB 0x40
#define AGC_103_MINDB 0x50
#define AGC_EXT 0x60
#define AGC_DIS_3_8V 0x70


typedef enum Band{
	VHF_L,
	VHF_H,
	UHF
};


typedef enum ChargePump{
	CP_50uA,
	CP_125uA	
};


Dword SetStep_6039(Byte Step_Index, Byte *u8TunerData)
{	
    Dword Step = 166670;
    
	switch(Step_Index)
	{
		/* CB: 1 , CP , T2 , T1 , T0 , RSA , RSB , OS */
		case 1:
			Step = 50000;
			u8TunerData[2] &= 0xc9; /* XX00X00X */
			break;

		case 2:
			Step = 31250;
			u8TunerData[2] &= 0xc9;
			u8TunerData[2] |= 0x02; /* XX00X01X */
			break;

		case 3:
			Step = 166670;
			u8TunerData[2] &= 0xf9; 
			u8TunerData[2] |= 0x04; /* XXXXX10X */
			break;

		case 4:
			Step = 62500;
			u8TunerData[2] |=0x06; /* XXXXX11X */
			break;

		case 5:
			Step = 125000;
			u8TunerData[2] &= 0xf9;
			u8TunerData[2] |= 0x30; /* XX11X00X */
			break;

		case 6:
			Step = 142860;
			u8TunerData[2]  &=0xf9; 
			u8TunerData[2] |=0x32; /* XX11X01X */
			break;

		default:
			Step = 166670;
			u8TunerData[2] &= 0xf9; 
			u8TunerData[2] |= 0x04; /* XXXXX10X */
			break;
	}
	return Step;
}


void SetBand_6039(Byte Band_Index, Word bandwidth, Byte *u8TunerData)
{
	//u8TunerData[3] &= 0xe0; /* X,X,X, P4,P3,P2,P1,P0 */
	if(bandwidth == 8)
	{
	    u8TunerData[3] = 0x00; /* X,X,X, P4=0,P3,P2,P1,P0 */  
	}
	else
	{
	    u8TunerData[3] = 0x10; /* X,X,X, P4=1,P3,P2,P1,P0 */ 
	}
	
	switch(Band_Index)
	{
		/* BB: X X X X P4 P3 P2 P1 P0 */
		case VHF_L:			
			u8TunerData[3] |= 0x01; /* 0x01 */
			break;
			
		case VHF_H:			
			u8TunerData[3] |= 0x02; /* 0x02 */
			break;
			
		case UHF:			
			u8TunerData[3] |= 0x04; /* 0x04 */
			break;

		default:
			//printf("Unknow band\n");
			break;
	}

}


void Set_ChargePump_6039(Byte CP_Index, Byte *u8TunerData)
{
	/* CB: 1 CP X X X X X X */
	switch(CP_Index){
		case CP_50uA: /* 50uA  OR 125*/
			u8TunerData[2] = 0xB4;
			break;

		case CP_125uA: /* 250 OR 650uA */ 
			u8TunerData[2] = 0xf4;   // ???
			break;

		default:
			break;
	}	
}


Dword TUA6039_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    return (Error_NO_ERROR);
}


Dword TUA6039_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    return (Error_NO_ERROR);
}


Dword TUA6039_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
	IN  Dword			frequency
) {
    Dword error = Error_NO_ERROR;
    Byte    buffer[10];
    Dword   Step = 166700;
    Byte    AB = AGC_115_MAXDB;

	//SetFreq(177500);
	//unsigned long Step = GetStep();
	
	if(frequency < 177500L)
	{
		SetBand_6039(VHF_L, bandwidth, buffer);		
		Set_ChargePump_6039(CP_50uA, buffer);
	}
	
	if(frequency >= 177500L && frequency <= 226500L)
	{
		SetBand_6039(VHF_H, bandwidth, buffer);
		Set_ChargePump_6039(CP_50uA, buffer);
	}
	
	if(frequency  > 226500L)
	{
		SetBand_6039(UHF, bandwidth, buffer);
		Set_ChargePump_6039(CP_125uA, buffer);  // ???
	}

    Step = SetStep_6039(3, buffer); // "3" is for 166.670 KHz

	frequency += IF_FREQ; //add by martin 2006/03/06	
	frequency *= 1000;	

	buffer[0] = (char)  ((frequency / Step) >>8) ;
	buffer[1] = (char)  ((frequency / Step) & 0xff);	
			
	error = Standard_writeTunerRegisters(demodulator, chip, 0x0000, 4, buffer);
    if (error) goto exit;				

#ifdef ENABLE_AGC_CTRL    
	buffer[2] |= 0x98;
	buffer[2] &= 0xdf; /* byte AB will follow */
	buffer[3] =  AB;
	
	error = Standard_writeTunerRegisters(demodulator, chip, 0x0000, 4, buffer);
    if (error) goto exit;
#endif


exit:
	return(error);
}


TunerDescription tuner_TUA6039 = {
    TUA6039_open,
    TUA6039_close,
    TUA6039_set,
    TUA6039_scripts,
	TUA6039_scriptSets,
    TUA6039_ADDRESS,                /** tuner i2c address */
    0,                              /** length of tuner register address */
    36167000,                       /** tuner if */
    True,                           /** spectrum inverse */
    0x29,                           /** tuner id */
};
