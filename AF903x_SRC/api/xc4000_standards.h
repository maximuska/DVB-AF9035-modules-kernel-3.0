//                                                   
// Automatically generated C header file for         
// control of the XC4000 via the i2c interface.      
//                                                   
// Filename : xc4000_standards.h                                     
// Generated : 9/25/2007 4:58:46 PM                                    
// Firmware version : 1.2                          
//                                                   
// (c) 2007, Xceive Corporation                         
//                                                   
                                                     
#ifndef __XC4000_STANDARDS_H                                           
#define __XC4000_STANDARDS_H                                           
                                                     
                                                     
// ************************************************************ 
// *** Standard with Video/Audio Setting                        
// ************************************************************ 
                                                                
#define MAX_TV_STANDARD   47

XC_TV_STANDARD XC4000_Standard[MAX_TV_STANDARD] = {
 {"M/N-NTSC/PAL-BTSC-IF", NULL, 0x80A0, 0x0000, 4.5 },
 {"M/N-NTSC/PAL-BTSC-IF-NOGD", NULL, 0x8020, 0x0000, 4.5 },
 {"M/N-NTSC/PAL-A2-IF", NULL, 0x80A0, 0x0000, 4.6 },
 {"M/N-NTSC/PAL-A2-IF-NOGD", NULL, 0x8020, 0x0000, 4.6 },
 {"M/N-NTSC/PAL-MTS", NULL, 0x80A0, 0x0078, 4.5 },
 {"M/N-NTSC/PAL-A2-MONO", NULL, 0x80A0, 0x0078, 4.5 },
 {"M/N-NTSC/PAL-A2-MONO-NOGD", NULL, 0x8020, 0x0078, 4.5 },
 {"L-SECAM-NICAM", NULL, 0x0009, 0x8080, 6.20 },
 {"L-SECAM-AM", NULL, 0x0009, 0xA138, 6.50 },
 {"L'-SECAM-NICAM", NULL, 0x4009, 0x8080, 6.20 },
 {"L'-SECAM-AM", NULL, 0x4009, 0xA138, 6.50 },
 {"FM Radio-INPUT1", NULL, 0x9000, 0x0008, 10.70 },
 {"FM Radio-INPUT2", NULL, 0x9800, 0x0008, 10.70 },
 {"DTV6-ATSC-LG-6_0Mhz", NULL, 0x8002, 0x00C0, 6.0 },
 {"DTV6-ATSC-ATI-6_38Mhz", NULL, 0x8002, 0x00C0, 6.38 },
 {"DTV6-ATSC-OREN-5_38Mhz", NULL, 0x8002, 0x00C0, 5.58 },
 {"DTV6-ATSC-OREN-3_6Mhz", NULL, 0x8002, 0x00C0, 3.6 },
 {"DTV6-ATSC-TOYOTA-3_88Mhz", NULL, 0x8002, 0x00C0, 3.88 },
 {"DTV6-ATSC-TOYOTA-7_94Mhz", NULL, 0x8002, 0x00C0, 7.94 },
 {"DTV6-QAM-6_0Mhz", NULL, 0x8002, 0x00C0, 6.0 },
 {"DTV8-DIBCOM-5_2Mhz", NULL, 0x800B, 0x00C0, 5.2 },
 {"DTV78-DIBCOM-5_2Mhz", NULL, 0x801B, 0x00C0, 5.2 },
 {"DTV7-DIBCOM-5_2Mhz", NULL, 0x8007, 0x00C0, 5.2 },
 {"DTV6-ZARLINK-QAM-4_56Mhz", NULL, 0x8002, 0x00C0, 4.56 },
 {"DTV8-ZARLINK-4_56Mhz", NULL, 0x800B, 0x00C0, 4.56 },
 {"DTV78-ZARLINK-4_56Mhz", NULL, 0x801B, 0x00C0, 4.56 },
 {"DTV7-ZARLINK-4_56Mhz", NULL, 0x8007, 0x00C0, 4.56 },
 {"DTV8-China-TEMPORARY", NULL, 0x800B, 0x00C0, 5.4 },
 {"B/G-PAL-NICAM#A", NULL, 0x8159, 0x0004, 5.74 },
 {"B/G-PAL-NICAM#A-MONO", NULL, 0x8159, 0x0078, 5.5 },
 {"B/G-PAL-NICAM#B", NULL, 0x8159, 0x0004, 5.74 },
 {"B/G-PAL-NICAM#B-MONO", NULL, 0x8159, 0x0078, 5.5 },
 {"B/G-PAL-A2#B", NULL, 0x81D9, 0x0000, 5.64 },
 {"B/G-PAL-A2#B-MONO", NULL, 0x81D9, 0x0078, 5.5 },
 {"B/G-PAL-A2#A", NULL, 0x8159, 0x0000, 5.64 },
 {"B/G-PAL-A2#A-MONO", NULL, 0x8159, 0x0078, 5.5 },
 {"I-PAL-NICAM", NULL, 0x8049, 0x0080, 6.24 },
 {"I-PAL-NICAM-MONO", NULL, 0x8049, 0x0078, 6.00 },
 {"D/K-PAL-NICAM", NULL, 0x8049, 0x0080, 6.20 },
 {"D/K-PAL-NICAM-MONO", NULL, 0x8049, 0x0078, 6.5 },
 {"D/K-SECAM-A2 DK1", NULL, 0x8049, 0x0000, 6.34 },
 {"D/K-SECAM-A2 L/DK3", NULL, 0x8049, 0x0000, 6.00 },
 {"D/K-PAL-A2", NULL, 0x8049, 0x0000, 6.38 },
 {"D/K-SECAM-A2 DK1-MONO", NULL, 0x8049, 0x0078, 6.5 },
 {"D/K-SECAM-A2 L/DK3-MONO", NULL, 0x8049, 0x0078, 6.5 },
 {"D/K-PAL-FM-ONLY", NULL, 0x8049, 0x0008, 6.5 },
 {"D/K-PAL-MONO", NULL, 0x8049, 0x0078, 6.5 },
};
                                               
/************************************************/
/* The TV_standard initial routine              */
/************************************************/
 
void XC4000_Loading_TVStandards(void) 
{ 
   XC4000_Standard[ 0 ].ConfFile = XC4000_MN_NTSC_PAL_BTSC_SEQUENCE; 
   XC4000_Standard[ 1 ].ConfFile = XC4000_MN_NTSC_PAL_BTSC_NOGD_SEQUENCE; 
   XC4000_Standard[ 2 ].ConfFile = XC4000_MN_NTSC_PAL_A2_IF_SEQUENCE; 
   XC4000_Standard[ 3 ].ConfFile = XC4000_MN_NTSC_PAL_A2_IF_NOGD_SEQUENCE; 
   XC4000_Standard[ 4 ].ConfFile = XC4000_MN_NTSC_PAL_MTS_SEQUENCE; 
   XC4000_Standard[ 5 ].ConfFile = XC4000_MN_NTSC_PAL_A2_MONO_SEQUENCE; 
   XC4000_Standard[ 6 ].ConfFile = XC4000_MN_NTSC_PAL_A2_MONO_NOGD_SEQUENCE; 
   XC4000_Standard[ 7 ].ConfFile = XC4000_L_SECAM_NICAM_SEQUENCE; 
   XC4000_Standard[ 8 ].ConfFile = XC4000_L_SECAM_AM_SEQUENCE; 
   XC4000_Standard[ 9 ].ConfFile = XC4000_IL_SECAM_NICAM_SEQUENCE; 
   XC4000_Standard[ 10 ].ConfFile = XC4000_IL_SECAM_AM_SEQUENCE; 
   XC4000_Standard[ 11 ].ConfFile = XC4000_FM_INPUT1_SEQUENCE; 
   XC4000_Standard[ 12 ].ConfFile = XC4000_FM_INPUT2_SEQUENCE; 
   XC4000_Standard[ 13 ].ConfFile = XC4000_ATSC_SEQUENCE; 
   XC4000_Standard[ 14 ].ConfFile = XC4000_ATSC_SEQUENCE; 
   XC4000_Standard[ 15 ].ConfFile = XC4000_ATSC_SEQUENCE; 
   XC4000_Standard[ 16 ].ConfFile = XC4000_ATSC_SEQUENCE; 
   XC4000_Standard[ 17 ].ConfFile = XC4000_ATSC_SEQUENCE; 
   XC4000_Standard[ 18 ].ConfFile = XC4000_ATSC_SEQUENCE; 
   XC4000_Standard[ 19 ].ConfFile = XC4000_ATSC_SEQUENCE; 
   XC4000_Standard[ 20 ].ConfFile = XC4000_DVBT_8_SEQUENCE; 
   XC4000_Standard[ 21 ].ConfFile = XC4000_DVBT_78_SEQUENCE; 
   XC4000_Standard[ 22 ].ConfFile = XC4000_DVBT_7_SEQUENCE; 
   XC4000_Standard[ 23 ].ConfFile = XC4000_ATSC_SEQUENCE; 
   XC4000_Standard[ 24 ].ConfFile = XC4000_DVBT_8_SEQUENCE; 
   XC4000_Standard[ 25 ].ConfFile = XC4000_DVBT_78_SEQUENCE; 
   XC4000_Standard[ 26 ].ConfFile = XC4000_DVBT_7_SEQUENCE; 
   XC4000_Standard[ 27 ].ConfFile = XC4000_DVBT_8_SEQUENCE; 
   XC4000_Standard[ 28 ].ConfFile = XC4000_B_G_PAL_NICAM_A_SEQUENCE; 
   XC4000_Standard[ 29 ].ConfFile = XC4000_B_G_PAL_NICAM_A_MONO_SEQUENCE; 
   XC4000_Standard[ 30 ].ConfFile = XC4000_B_G_PAL_NICAM_B_SEQUENCE; 
   XC4000_Standard[ 31 ].ConfFile = XC4000_B_G_PAL_NICAM_B_MONO_SEQUENCE; 
   XC4000_Standard[ 32 ].ConfFile = XC4000_B_G_PAL_A2_B_SEQUENCE; 
   XC4000_Standard[ 33 ].ConfFile = XC4000_B_G_PAL_A2_B_MONO_SEQUENCE; 
   XC4000_Standard[ 34 ].ConfFile = XC4000_B_G_PAL_A2_A_SEQUENCE; 
   XC4000_Standard[ 35 ].ConfFile = XC4000_B_G_PAL_A2_A_MONO_SEQUENCE; 
   XC4000_Standard[ 36 ].ConfFile = XC4000_I_PAL_NICAM_SEQUENCE; 
   XC4000_Standard[ 37 ].ConfFile = XC4000_I_PAL_NICAM_MONO_SEQUENCE; 
   XC4000_Standard[ 38 ].ConfFile = XC4000_D_K_PAL_NICAM_SEQUENCE; 
   XC4000_Standard[ 39 ].ConfFile = XC4000_D_K_PAL_NICAM_MONO_SEQUENCE; 
   XC4000_Standard[ 40 ].ConfFile = XC4000_D_K_SECAM_A2_SEQUENCE; 
   XC4000_Standard[ 41 ].ConfFile = XC4000_D_K_SECAM_A2_SEQUENCE; 
   XC4000_Standard[ 42 ].ConfFile = XC4000_D_K_SECAM_A2_SEQUENCE; 
   XC4000_Standard[ 43 ].ConfFile = XC4000_D_K_SECAM_A2_MONO_SEQUENCE; 
   XC4000_Standard[ 44 ].ConfFile = XC4000_D_K_SECAM_A2_MONO_SEQUENCE; 
   XC4000_Standard[ 45 ].ConfFile = XC4000_D_K_PAL_FM_ONLY_SEQUENCE; 
   XC4000_Standard[ 46 ].ConfFile = XC4000_D_K_SECAM_A2_MONO_SEQUENCE; 
} ; 
#endif                                         
                                               
