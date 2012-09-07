/**
 * @(#)Afa_E4000.cpp
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
#include "standard.h"


extern Demodulator* E4000_demodulator;
extern Byte E4000_chip;
extern Dword Ref_clk;
extern Dword E4000_frequency;
extern Word E4000_bandwidth;

/****************************************************************************\  
*  Function: tunerreset
*
*  Detailed Description:
*  The function resets the E4000 tuner. (Register 0x00).
*
\****************************************************************************/

Dword E4000_tunerreset (
						
						)
{
	Dword error = 0;
	Byte buffer[1];
	buffer[0] = 0x01;
	error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x00, 1, buffer);
	return (Error_NO_ERROR);
}

/****************************************************************************\  
*  Function: Tunerclock
*
*  Detailed Description:
*  The function configures the E4000 clock. (Register 0x06, 0x7a).
*  Function enablesa CMOS clock - values can be modified to disable if required.
\****************************************************************************/

Dword E4000_Tunerclock()
{
   Dword error = 0;
   Byte buffer[1];
   buffer[0] = 0x06;
   error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x06, 1, buffer);
   //buffer[0] = 0x96;
  // error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x7a, 1, buffer);
  //**Modify commands above with value required if output clock is not required, 
  return (Error_NO_ERROR);  
}

/****************************************************************************\  
*  Function: filtercal
*
*  Detailed Description:
*  Instructs RC filter calibration. (Register 0x7b).
*
\****************************************************************************/

//Dword filtercal()
//{
//  Dword error = 0;
//   Byte buffer[1];
//   buffer[0] = 0x01;
//   error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x7b, 1, buffer);
//  return (Error_NO_ERROR);
//}
/****************************************************************************\  
*  Function: Qpeak()
*
*  Detailed Description:
*  The function configures the E4000 gains. 
*  Also sigma delta controller. (Register 0x82).
*
\****************************************************************************/
Dword E4000_Qpeak()
{
  Dword error = 0;
  Byte buffer[2];
  buffer[0] = 0x01;
  buffer[1]=0xfe;
  error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x7e, 2, buffer);
  buffer[0] = 0x00;
  error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x82, 1, buffer);
  buffer[0] = 0x05;
  error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x24, 1, buffer);
  buffer[0] = 0x20;
  buffer[1]=0x01;
  error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x87, 2, buffer);
  buffer[0] = 0x7f;
  buffer[1]=0x07;
  error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x9f, 2, buffer);
  return (Error_NO_ERROR);
}
/****************************************************************************\  
*  Function: PLL
*
*  Detailed Description:
*  Configures E4000 PLL divider & sigma delta. 0x0d,0x09, 0x0a, 0x0b).
*
\****************************************************************************/

Dword E4000_PLL()
{
  //printf("freq=%d", E4000_frequency);
  //printf("ref clock=%d", Ref_clk);
  Dword VCO_freq;
  Dword error = 0;
  Byte buffer[5];
 if (E4000_frequency<=72400)
    {
    buffer[4] = 15;
    VCO_freq=E4000_frequency*48;
    }
 else if (E4000_frequency<=81200)
    {
    buffer[4] = 14;
    VCO_freq=E4000_frequency*40;
    }
 else if (E4000_frequency<=108300)
    {
    buffer[4]=13;
    VCO_freq=E4000_frequency*32;
    }
 else if (E4000_frequency<=162500)
    {
    buffer[4]=12;
    VCO_freq=E4000_frequency*24;
    }   
 else if (E4000_frequency<=216600)       
    {
    buffer[4]=11;  
    VCO_freq=E4000_frequency*16;
    }
 else if (E4000_frequency<=325000)
    {
    buffer[4]=10;
    VCO_freq=E4000_frequency*12;
    }
 else if (E4000_frequency<=350000)
    {
    buffer[4]=9;
    VCO_freq=E4000_frequency*8;  
    }
 else if (E4000_frequency<=432000)
  {
    buffer[4]=3;
    VCO_freq=E4000_frequency*8;
  }
 else if (E4000_frequency<=700000)
    {
    buffer[4]=2; 
    VCO_freq=E4000_frequency*6; 
    }
 else if (E4000_frequency<=1200000)
    {
    buffer[4]=1;
    VCO_freq=E4000_frequency*4;
    }
    else
    {
    buffer[4]=0;
    VCO_freq=E4000_frequency*2; 
    }
  
 Dword divider;
 Dword intVCOfreq; 
 Dword SigDel;
 Dword SigDel2;
 Dword SigDel3;  
 divider =  VCO_freq / Ref_clk;

 buffer[0]= divider;  
 intVCOfreq = divider * Ref_clk;

 SigDel=65536 * (VCO_freq - intVCOfreq) / Ref_clk;

if (SigDel<=512)
{
     SigDel = 512;
}
else if (SigDel>=65024)
{
     SigDel=65024;
}
SigDel2 = SigDel / 256;

buffer[2] = SigDel2;
SigDel3 = SigDel - (256 * SigDel2);

buffer[1]= SigDel3;
buffer[3]=0;
error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x09, 5, buffer);
  return (Error_NO_ERROR);
}
/****************************************************************************\  
*  Function: LNAfilter
*
*  Detailed Description:
*  The function configures the E4000 LNA filter. (Register 0x10).
*
\****************************************************************************/

Dword E4000_LNAfilter()
{
 Dword error = 0;
 Byte buffer[1];
 if(E4000_frequency<=370000)
  {
              buffer[0]=0;
  }
else if(E4000_frequency<=392500)
     {
                   buffer[0]=1;
    }
 else if(E4000_frequency<=415000)
     {
                  buffer[0] =2;
     }
  else if(E4000_frequency<=437500)
     {
                   buffer[0]=3;
     }
  else if(E4000_frequency<=462500)
     {
                   buffer[0]=4;
     }
  else if(E4000_frequency<=490000)
     {
                   buffer[0]=5;
     }
  else if(E4000_frequency<=522500)
     {
                   buffer[0]=6;
     }
 else if(E4000_frequency<=557500)
     {
                   buffer[0]=7;
     }
 else if(E4000_frequency<=595000)
     {
                   buffer[0]=8;
     }
  else if(E4000_frequency<=642500)
     {
                   buffer[0]=9;
     }
else if(E4000_frequency<=695000)
     {
                   buffer[0]=10;
     }
else if(E4000_frequency<=740000)
     {
                   buffer[0]=11;
     }
else if(E4000_frequency<=800000)
     {
                   buffer[0]=12;
     }
else if(E4000_frequency<=865000)
     {
                  buffer[0] =13;
     }
else if(E4000_frequency<=930000)
     {
                  buffer[0]=14;
     }
else if(E4000_frequency<=1000000)
     {
                   buffer[0]=15;
     }
else if(E4000_frequency<=1310000)
     {
                   buffer[0]=0;
     }
else if(E4000_frequency<=1340000)
     {
                   buffer[0]=1;
     }
else if(E4000_frequency<=1385000)
     {
                   buffer[0]=2;
     }
else if(E4000_frequency<=1427500)
     {
                   buffer[0]=3;
     }
else if(E4000_frequency<=1452500)
     {
                   buffer[0]=4;
     }
else if(E4000_frequency<=1475000)
    {
                   buffer[0]=5;
     }
else if(E4000_frequency<=1510000)
     {
                   buffer[0]=6;
     }
else if(E4000_frequency<=1545000)
    {
                   buffer[0]=7;
     }
else if(E4000_frequency<=1575000)
     {
                  buffer[0] =8;
     }
else if(E4000_frequency<=1615000)
     {
                   buffer[0]=9;
     }
else if(E4000_frequency<=1650000)
     {
                  buffer[0] =10;
     }
else if(E4000_frequency<=1670000)
     {
                   buffer[0]=11;
     }
else if(E4000_frequency<=1690000)
     {
                   buffer[0]=12;
     }
else if(E4000_frequency<=1710000)
     {
                   buffer[0]=13;
     }
else if(E4000_frequency<=1735000)
     {
                   buffer[0]=14;
     }
else
     {
                   buffer[0]=15;
     }
 error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x10, 1, buffer);
 return (Error_NO_ERROR);  
}
/****************************************************************************\  
*  Function: IFfilter
*
*  Detailed Description:
*  The function configures the E4000 IF filter. (Register 0x11,0x12).
*
\****************************************************************************/
Dword E4000_IFfilter()
{
	Dword error = 0;
    Byte buffer[2];
    Word IF_BW;
    IF_BW = E4000_bandwidth / 2;
     if(IF_BW<=2150)
         {
         buffer[0]=0xfd;
         buffer[1]=0x1f;
         }
     else if(IF_BW<=2200)
         {
         buffer[0]=0xfd;
         buffer[1]=0x1e;
         }
     else if(IF_BW<=2240)
         {
         buffer[0]=0xfc;                  
         buffer[1]=0x1d;
         }
     else if(IF_BW<=2280)
         {
         buffer[0]=0xfc;                  
         buffer[1]=0x1c;
         }
     else if(IF_BW<=2300)
         {
         buffer[0]=0xfc;
        buffer[1]=0x1b;
         }
     else if(IF_BW<=2400)
         {
         buffer[0]=0xfc;
         buffer[1]=0x1a;
         }
     else if(IF_BW<=2450)
         {
         buffer[0]=0xfc;                  
         buffer[1]=0x19;
         }
     else if(IF_BW<=2500)
         {
         buffer[0]=0xfc;               
         buffer[1]=0x18;
         }
     else if(IF_BW<=2550)
         {
         buffer[0]=0xfc;                 
         buffer[1]=0x17;
         }
     else if(IF_BW<=2600)
         {
         buffer[0]=0xfc;                 
         buffer[1]=0x16;
         }
     else if(IF_BW<=2700)
         {
         buffer[0]=0xfc;                 
         buffer[1]=0x15;
         }
     else if(IF_BW<=2750)
         {
         buffer[0]=0xfc;                  
         buffer[1]=0x14;
         }
     else if(IF_BW<=2800)
         {
         buffer[0]=0xfc;
         buffer[1]=0x13;
         }
     else if(IF_BW<=2900)
         {
         buffer[0]==0xfb;                
         buffer[1]=0x12;
         }
     else if(IF_BW<=2950)
         {
         buffer[0]=0xfb;
        buffer[1]=0x11;
         }
     else if(IF_BW<=3000)
         {
         buffer[0]=0xfb;              
         buffer[1]=0x10;
         }
     else if(IF_BW<=3100)
         {
         buffer[0]=0xfb;                 
         buffer[1]=0x0f;
         }
     else if(IF_BW<=3200)
         {
         buffer[0]=0xfa;
         buffer[1]=0x0e;
         }
     else if(IF_BW<=3300)
         {
         buffer[0]=0xfa;                 
         buffer[1]=0x0d;
         }
     else if(IF_BW<=3400)
         {
         buffer[0]=0xf9;                 
         buffer[1]=0x0c;
         }
     else if(IF_BW<=3600)
         {
         buffer[0]=0xf9;
         buffer[1]=0x0b;
         }
     else if(IF_BW<=3700)
         {
         buffer[0]=0xf9;
         buffer[1]=0x0a;
         }
     else if(IF_BW<=3800)
         {
         buffer[0]=0xf8;
         buffer[1]=0x09;
         }
     else if(IF_BW<=3900)
         {
         buffer[0]=0xf8;
         buffer[1]=0x08;
         }
     else if(IF_BW<=4100)
         {
         buffer[0]=0xf8;
         buffer[1]=0x07;
         }
     else if(IF_BW<=4300)
         {
         buffer[0]=0xf7;
         buffer[1]=0x06;
         }
     else if(IF_BW<=4400)
         {
         buffer[0]=0xf7;
         buffer[1]=0x05;
         }
     else if(IF_BW<=4600)
         {
         buffer[0]=0xf7;
         buffer[1]=0x04;
         }
     else if(IF_BW<=4800)
         {
         buffer[0]=0xf6;
         buffer[1]=0x03;
         }
     else if(IF_BW<=5000)
         {
         buffer[0]=0xf6;
         buffer[1]=0x02;
         }
     else if(IF_BW<=5300)
         {
         buffer[0]=0xf5;
         buffer[1]=0x01;
         }
     else if(IF_BW<=5500)
         {
         buffer[0]=0xf5;
         buffer[1]=0x00;
         }
     else
         {
         buffer[0]=0x00;
         buffer[1]=0x20;
         }
	 error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x11, 2, buffer);            
     return (Error_NO_ERROR);
}
/****************************************************************************\  
*  Function: freqband
*
*  Detailed Description:
*  Configures the E4000 frequency band. (Registers 0x07, 0x78).
*
\****************************************************************************/
Dword E4000_freqband()
{  
    Dword error = 0;
    Byte buffer[1];
  if (E4000_frequency<=140000)
     {
     buffer[0] = 1;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x07, 1, buffer);
	 buffer[0] = 3;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x78, 1, buffer);
     }
  else if (E4000_frequency<=350000)
       {
         buffer[0] = 3;
         error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x07, 1, buffer);
		 buffer[0] = 3;
		 error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x78, 1, buffer);
       }
  else if (E4000_frequency<=1000000)
       {
          buffer[0] = 5;
		  error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x07, 1, buffer);
		  buffer[0] = 3;
		  error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x78, 1, buffer);
       }
  else 
       {
           buffer[0] = 7;
		   error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x07, 1, buffer);
           buffer[0] = 0;
		   error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x78, 1, buffer);
       }
  return (Error_NO_ERROR);  
}
/****************************************************************************\  
*  Function: DCoffLUT
*
*  Detailed Description:
*  Populates DC offset LUT. (Registers 0x50 - 0x53, 0x60 - 0x63).
*
\****************************************************************************/
Dword E4000_DCoffLUT()
{
     Word IOFF;
     Word QOFF;
     Word RANGE1;
     Word RANGE2;
     Word QRANGE;
     Word IRANGE;
     Dword error = 0;
     Byte buffer[3];
     buffer[0] = 0x00;
     buffer[1] = 0x7e;
     buffer[2] = 0x24;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x15, 3, buffer);
     // Sets mixer & IF stage 1 gain = 00 and IF stg 2+ to max gain.
    buffer[0] = 0x01;
	error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x29, 1, buffer);
     // Instructs a DC offset calibration. 
    error = Standard_readTunerRegisters (E4000_demodulator, 0, 0x2a, 3, buffer);
	//printf("\n2a=%d",buffer[0]);
	//printf("\n2b=%d",buffer[1]);
	//printf("\n2c=%d",buffer[2]);
    IOFF=buffer[0];
    QOFF=buffer[1];
   RANGE1=buffer[2];
    //reads DC offset values back
     if(RANGE1>=32)
     {
                 RANGE1 = RANGE1 -32;
     }
     if(RANGE1>=16)
     {
                RANGE1 = RANGE1 - 16;
     }
     IRANGE=RANGE1;
     QRANGE = (buffer[2] - RANGE1) / 16;
     buffer[0] = (IRANGE * 64) + IOFF;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x60, 1, buffer);
     buffer[0] = (QRANGE * 64) + QOFF;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x50, 1, buffer);
     // Populate DC offset LUT
     buffer[0] = 0;
     buffer[1] = 127;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x15, 2, buffer);
     // Sets mixer & IF stage 1 gain = 01 leaving IF stg 2+ at max gain.
     buffer[0]= 1;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x29, 1, buffer);
     // Instructs a DC offset calibration.
    error = Standard_readTunerRegisters (E4000_demodulator, 0, 0x2a, 3, buffer);
    //printf("\n2a=%d",buffer[0]);
	//printf("\n2b=%d",buffer[1]);
	//printf("\n2c=%d",buffer[2]);
    IOFF=buffer[0];
    QOFF=buffer[1];
    RANGE1=buffer[2];
     // Read DC offset values
     if(RANGE1>=32)
     {
                 RANGE1 = RANGE1 -32;
    }
     if(RANGE1>=16)
     {
                 RANGE1 = RANGE1 - 16;
    }
    IRANGE = RANGE1;
    QRANGE = (buffer[2] - RANGE1) / 16;
    buffer[0] = (IRANGE * 64) + IOFF;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x61, 1, buffer);
     buffer[0] = (QRANGE * 64) + QOFF;
	 error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x51, 1, buffer);
     // Populate DC offset LUT
     buffer[0] = 0x01;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x15, 1, buffer);
     // Sets mixer & IF stage 1 gain = 11 leaving IF stg 2+ at max gain.
     buffer[0] = 1;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x29, 1, buffer);
     // Instructs a DC offset calibration.
     error = Standard_readTunerRegisters (E4000_demodulator, 0, 0x2a, 3, buffer);
	//printf("\n2a=%d",buffer[0]);
	//printf("\n2b=%d",buffer[1]);
	//printf("\n2c=%d",buffer[2]);
    IOFF=buffer[0];
    QOFF=buffer[1];
    RANGE1 = buffer[2];
    // Read DC offset values
     if(RANGE1>=32)
     {
                  RANGE1 = RANGE1 -32;
     }
     if(RANGE1>=16)
     {
                  RANGE1 = RANGE1 - 16;
     }
     IRANGE = RANGE1;
     QRANGE = (buffer[2] - RANGE1) / 16;
     buffer[0] = (IRANGE * 64) + IOFF;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x63, 1, buffer);
     buffer[0] = (QRANGE * 64) + QOFF;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x53, 1, buffer);
     // Populate DC offset LUT
     buffer[0] = 0x7e;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x16, 1, buffer);
     // Sets mixer & IF stage 1 gain = 11 leaving IF stg 2+ at max gain.
     buffer[0] = 0x01;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x29, 1, buffer);
     // Instructs a DC offset calibration.
     error = Standard_readTunerRegisters (E4000_demodulator, E4000_chip, 0x2a, 3, buffer);
	 //printf("\n2a=%d",buffer[0]);
	 //printf("\n2b=%d",buffer[1]);
	 //printf("\n2c=%d",buffer[2]);
    IOFF=buffer[0];
    QOFF=buffer[1];
    RANGE1=buffer[2];
     // Read DC offset values
    if(RANGE1>=32)
    {
                 RANGE1 = RANGE1 -32;
    }
     if(RANGE1>=16)
    {
                 RANGE1 = RANGE1 - 16;
    }
    IRANGE = RANGE1;
    QRANGE = (buffer[2] - RANGE1) / 16;
    buffer[0]=(IRANGE * 64) + IOFF;
    error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x62, 1, buffer);
    buffer[0] = (QRANGE * 64) + QOFF;
    error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x52, 1, buffer);
     // Populate DC offset LUT
     return (Error_NO_ERROR);
}
/****************************************************************************\  
*  Function: DCoffloop
*
*  Detailed Description:
*  Populates DC offset LUT. (Registers 0x2d, 0x70, 0x71).
*  Turns on DC offset LUT and time varying DC offset.
\****************************************************************************/
Dword E4000_DCoffloop()
{
    Dword error = 0;
    Byte buffer[2]; 
	buffer[0] = 0x1f;
    error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x2d, 1, buffer);
     buffer[0] = 0x01;
     buffer[1] = 0x01;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x70, 2, buffer);
     return (Error_NO_ERROR);
}
/****************************************************************************\  
*  Function: commonmode
*
*  Detailed Description:
*  Configures common mode voltage. (Registers 0x2f).
*  
\****************************************************************************/
//Dword E4000_commonmode()
//{
//     //Dword error = 0;
//     //Byte buffer[1];
//	 //buffer[0] = 0;  
//     //error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x2f, 1, buffer);
//     // Sets 550mV. Modify if alternative is desired.
//     return (Error_NO_ERROR);
//}
/****************************************************************************\  
*  Function: GainControlinit
*
*  Detailed Description:
*  Configures gain control mode. (Registers 0x1d, 0x1e, 0x1f, 0x20, 0x21, 
*  0x1a, 0x74h, 0x75h).
*  User may wish to modify values depending on usage scenario.
*  Routine configures LNA: autonomous gain control
*  IF PWM gain control. 
*  PWM thresholds = default
*  Mixer: switches when LNA gain =7.5dB
*  Sensitivity / Linearity mode: manual switch
*  
\****************************************************************************/
Dword E4000_GainControlinit()
{
     Dword sum=255;
     Dword error = 0;
     Byte buffer[5]; 
     buffer[0] = 0x17;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x1a, 1, buffer);
     buffer[0] = 0x24;  
     buffer[1] = 0x06;
     buffer[2] = 0x1a;  
     buffer[3] = 0x0f;  
     buffer[4] = 0x00;  
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x1d, 5, buffer);
     error = Standard_readTunerRegisters (E4000_demodulator, 0, 0x1b, 1, buffer);
     if (buffer[0]<=sum)
     {
     sum=buffer[0];
     }
	 //printf("sum1=%d",sum);
     buffer[0]=0x1a;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x1f, 1, buffer);
     error = Standard_readTunerRegisters (E4000_demodulator, 0, 0x1b, 1, buffer);
     if (buffer[0]<=sum)
     {
     sum=buffer[0];
	 }
	// printf("sum2=%d",sum);
     buffer[0]=0x1a;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x1f, 1, buffer);
	 error = Standard_readTunerRegisters (E4000_demodulator, 0, 0x1b, 1, buffer);
     if (buffer[0]<=sum)
     {
     sum=buffer[0];
	 }
	// printf("sum3=%d",sum);
     buffer[0]=0x1a;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x1f, 1, buffer);
	 error = Standard_readTunerRegisters (E4000_demodulator, 0, 0x1b, 1, buffer);
     if (buffer[0]<=sum)
     {
     sum=buffer[0];
	 }
	 //printf("sum4=%d",sum);
     buffer[0]=0x1a;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x1f, 1, buffer);
	 error = Standard_readTunerRegisters (E4000_demodulator, 0, 0x1b, 1, buffer);
     if (buffer[0]<=sum)
     {
     sum=buffer[0];
	 }
	 //printf("sum5=%d",sum);
     buffer[0]=sum;
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x1b, 1, buffer);
     //buffer[0] = 0x03;
     //buffer[1] = 0xfc;
     //buffer[2] = 0x03;  
     //buffer[3] = 0xfc; 
     //error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x74, 4, buffer);
     return (Error_NO_ERROR);
}
/****************************************************************************\  
*  Function: E4000_Gainmanual
*
*  Detailed Description:
*  Sets gain to manualcontrol. (Register 0x1a).
*  
\****************************************************************************/
Dword E4000_Gainmanual()
{
     Dword error = 0;
     Byte buffer[1];
	 buffer[0] = 0x00;  
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x1a, 1, buffer);
     return (Error_NO_ERROR);
}
/****************************************************************************\  
*  Function: E4000_Gainauto
*
*  Detailed Description:
*  Sets gain to manualcontrol. (Register 0x1a).
*  
\****************************************************************************/
Dword E4000_Gainauto()
{
     Dword error = 0;
     Byte buffer[1];
	 buffer[0] = 0x17;  
     error = Standard_writeTunerRegisters (E4000_demodulator, E4000_chip, 0x1a, 1, buffer);
     return (Error_NO_ERROR);
}
