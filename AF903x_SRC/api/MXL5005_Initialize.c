#include "MXL5005.h"

WORD MXL5005_RegisterInit (Tuner_struct * Tuner) 
{
	Tuner->TunerRegs_Num = TUNER_REGS_NUM ;

	Tuner->TunerRegs[0].Reg_Num = 9 ;
	Tuner->TunerRegs[0].Reg_Val = 0x40 ;

	Tuner->TunerRegs[1].Reg_Num = 11 ;
	Tuner->TunerRegs[1].Reg_Val = 0x19 ;

	Tuner->TunerRegs[2].Reg_Num = 12 ;
	Tuner->TunerRegs[2].Reg_Val = 0x60 ;

	Tuner->TunerRegs[3].Reg_Num = 13 ;
	Tuner->TunerRegs[3].Reg_Val = 0x00 ;

	Tuner->TunerRegs[4].Reg_Num = 14 ;
	Tuner->TunerRegs[4].Reg_Val = 0x00 ;

	Tuner->TunerRegs[5].Reg_Num = 15 ;
	Tuner->TunerRegs[5].Reg_Val = 0xC0 ;

	Tuner->TunerRegs[6].Reg_Num = 16 ;
	Tuner->TunerRegs[6].Reg_Val = 0x00 ;

	Tuner->TunerRegs[7].Reg_Num = 17 ;
	Tuner->TunerRegs[7].Reg_Val = 0x00 ;

	Tuner->TunerRegs[8].Reg_Num = 18 ;
	Tuner->TunerRegs[8].Reg_Val = 0x00 ;

	Tuner->TunerRegs[9].Reg_Num = 19 ;
	Tuner->TunerRegs[9].Reg_Val = 0x34 ;

	Tuner->TunerRegs[10].Reg_Num = 21 ;
	Tuner->TunerRegs[10].Reg_Val = 0x00 ;

	Tuner->TunerRegs[11].Reg_Num = 22 ;
	Tuner->TunerRegs[11].Reg_Val = 0x6B ;

	Tuner->TunerRegs[12].Reg_Num = 23 ;
	Tuner->TunerRegs[12].Reg_Val = 0x35 ;

	Tuner->TunerRegs[13].Reg_Num = 24 ;
	Tuner->TunerRegs[13].Reg_Val = 0x70 ;

	Tuner->TunerRegs[14].Reg_Num = 25 ;
	Tuner->TunerRegs[14].Reg_Val = 0x3E ;

	Tuner->TunerRegs[15].Reg_Num = 26 ;
	Tuner->TunerRegs[15].Reg_Val = 0x82 ;

	Tuner->TunerRegs[16].Reg_Num = 31 ;
	Tuner->TunerRegs[16].Reg_Val = 0x00 ;

	Tuner->TunerRegs[17].Reg_Num = 32 ;
	Tuner->TunerRegs[17].Reg_Val = 0x40 ;

	Tuner->TunerRegs[18].Reg_Num = 33 ;
	Tuner->TunerRegs[18].Reg_Val = 0x53 ;

	Tuner->TunerRegs[19].Reg_Num = 34 ;
	Tuner->TunerRegs[19].Reg_Val = 0x81 ;

	Tuner->TunerRegs[20].Reg_Num = 35 ;
	Tuner->TunerRegs[20].Reg_Val = 0xC9 ;

	Tuner->TunerRegs[21].Reg_Num = 36 ;
	Tuner->TunerRegs[21].Reg_Val = 0x01 ;

	Tuner->TunerRegs[22].Reg_Num = 37 ;
	Tuner->TunerRegs[22].Reg_Val = 0x00 ;

	Tuner->TunerRegs[23].Reg_Num = 41 ;
	Tuner->TunerRegs[23].Reg_Val = 0x00 ;

	Tuner->TunerRegs[24].Reg_Num = 42 ;
	Tuner->TunerRegs[24].Reg_Val = 0xF8 ;

	Tuner->TunerRegs[25].Reg_Num = 43 ;
	Tuner->TunerRegs[25].Reg_Val = 0x43 ;

	Tuner->TunerRegs[26].Reg_Num = 44 ;
	Tuner->TunerRegs[26].Reg_Val = 0x20 ;

	Tuner->TunerRegs[27].Reg_Num = 45 ;
	Tuner->TunerRegs[27].Reg_Val = 0x80 ;

	Tuner->TunerRegs[28].Reg_Num = 46 ;
	Tuner->TunerRegs[28].Reg_Val = 0x88 ;

	Tuner->TunerRegs[29].Reg_Num = 47 ;
	Tuner->TunerRegs[29].Reg_Val = 0x86 ;

	Tuner->TunerRegs[30].Reg_Num = 48 ;
	Tuner->TunerRegs[30].Reg_Val = 0x00 ;

	Tuner->TunerRegs[31].Reg_Num = 49 ;
	Tuner->TunerRegs[31].Reg_Val = 0x00 ;

	Tuner->TunerRegs[32].Reg_Num = 53 ;
	Tuner->TunerRegs[32].Reg_Val = 0x94 ;

	Tuner->TunerRegs[33].Reg_Num = 54 ;
	Tuner->TunerRegs[33].Reg_Val = 0xFA ;

	Tuner->TunerRegs[34].Reg_Num = 55 ;
	Tuner->TunerRegs[34].Reg_Val = 0x92 ;

	Tuner->TunerRegs[35].Reg_Num = 56 ;
	Tuner->TunerRegs[35].Reg_Val = 0x80 ;

	Tuner->TunerRegs[36].Reg_Num = 57 ;
	Tuner->TunerRegs[36].Reg_Val = 0x41 ;

	Tuner->TunerRegs[37].Reg_Num = 58 ;
	Tuner->TunerRegs[37].Reg_Val = 0xDB ;

	Tuner->TunerRegs[38].Reg_Num = 59 ;
	Tuner->TunerRegs[38].Reg_Val = 0x00 ;

	Tuner->TunerRegs[39].Reg_Num = 60 ;
	Tuner->TunerRegs[39].Reg_Val = 0x00 ;

	Tuner->TunerRegs[40].Reg_Num = 61 ;
	Tuner->TunerRegs[40].Reg_Val = 0x00 ;

	Tuner->TunerRegs[41].Reg_Num = 62 ;
	Tuner->TunerRegs[41].Reg_Val = 0x00 ;

	Tuner->TunerRegs[42].Reg_Num = 65 ;
	Tuner->TunerRegs[42].Reg_Val = 0xF8 ;

	Tuner->TunerRegs[43].Reg_Num = 66 ;
	Tuner->TunerRegs[43].Reg_Val = 0xE4 ;

	Tuner->TunerRegs[44].Reg_Num = 67 ;
	Tuner->TunerRegs[44].Reg_Val = 0x90 ;

	Tuner->TunerRegs[45].Reg_Num = 68 ;
	Tuner->TunerRegs[45].Reg_Val = 0xC0 ;

	Tuner->TunerRegs[46].Reg_Num = 69 ;
	Tuner->TunerRegs[46].Reg_Val = 0x01 ;

	Tuner->TunerRegs[47].Reg_Num = 70 ;
	Tuner->TunerRegs[47].Reg_Val = 0x50 ;

	Tuner->TunerRegs[48].Reg_Num = 71 ;
	Tuner->TunerRegs[48].Reg_Val = 0x06 ;

	Tuner->TunerRegs[49].Reg_Num = 72 ;
	Tuner->TunerRegs[49].Reg_Val = 0x00 ;

	Tuner->TunerRegs[50].Reg_Num = 73 ;
	Tuner->TunerRegs[50].Reg_Val = 0x20 ;

	Tuner->TunerRegs[51].Reg_Num = 76 ;
	Tuner->TunerRegs[51].Reg_Val = 0xBB ;

	Tuner->TunerRegs[52].Reg_Num = 77 ;
	Tuner->TunerRegs[52].Reg_Val = 0x13 ;

	Tuner->TunerRegs[53].Reg_Num = 81 ;
	Tuner->TunerRegs[53].Reg_Val = 0x04 ;

	Tuner->TunerRegs[54].Reg_Num = 82 ;
	Tuner->TunerRegs[54].Reg_Val = 0x75 ;

	Tuner->TunerRegs[55].Reg_Num = 83 ;
	Tuner->TunerRegs[55].Reg_Val = 0x00 ;

	Tuner->TunerRegs[56].Reg_Num = 84 ;
	Tuner->TunerRegs[56].Reg_Val = 0x00 ;

	Tuner->TunerRegs[57].Reg_Num = 85 ;
	Tuner->TunerRegs[57].Reg_Val = 0x00 ;

	Tuner->TunerRegs[58].Reg_Num = 91 ;
	Tuner->TunerRegs[58].Reg_Val = 0x70 ;

	Tuner->TunerRegs[59].Reg_Num = 92 ;
	Tuner->TunerRegs[59].Reg_Val = 0x00 ;

	Tuner->TunerRegs[60].Reg_Num = 93 ;
	Tuner->TunerRegs[60].Reg_Val = 0x00 ;

	Tuner->TunerRegs[61].Reg_Num = 94 ;
	Tuner->TunerRegs[61].Reg_Val = 0x00 ;

	Tuner->TunerRegs[62].Reg_Num = 95 ;
	Tuner->TunerRegs[62].Reg_Val = 0x0C ;

	Tuner->TunerRegs[63].Reg_Num = 96 ;
	Tuner->TunerRegs[63].Reg_Val = 0x00 ;

	Tuner->TunerRegs[64].Reg_Num = 97 ;
	Tuner->TunerRegs[64].Reg_Val = 0x00 ;

	Tuner->TunerRegs[65].Reg_Num = 98 ;
	Tuner->TunerRegs[65].Reg_Val = 0xE2 ;

	Tuner->TunerRegs[66].Reg_Num = 99 ;
	Tuner->TunerRegs[66].Reg_Val = 0x00 ;

	Tuner->TunerRegs[67].Reg_Num = 100 ;
	Tuner->TunerRegs[67].Reg_Val = 0x00 ;

	Tuner->TunerRegs[68].Reg_Num = 101 ;
	Tuner->TunerRegs[68].Reg_Val = 0x12 ;

	Tuner->TunerRegs[69].Reg_Num = 102 ;
	Tuner->TunerRegs[69].Reg_Val = 0x80 ;

	Tuner->TunerRegs[70].Reg_Num = 103 ;
	Tuner->TunerRegs[70].Reg_Val = 0x32 ;

	Tuner->TunerRegs[71].Reg_Num = 104 ;
	Tuner->TunerRegs[71].Reg_Val = 0xB4 ;

	Tuner->TunerRegs[72].Reg_Num = 105 ;
	Tuner->TunerRegs[72].Reg_Val = 0x60 ;

	Tuner->TunerRegs[73].Reg_Num = 106 ;
	Tuner->TunerRegs[73].Reg_Val = 0x83 ;

	Tuner->TunerRegs[74].Reg_Num = 107 ;
	Tuner->TunerRegs[74].Reg_Val = 0x84 ;

	Tuner->TunerRegs[75].Reg_Num = 108 ;
	Tuner->TunerRegs[75].Reg_Val = 0x9C ;

	Tuner->TunerRegs[76].Reg_Num = 109 ;
	Tuner->TunerRegs[76].Reg_Val = 0x02 ;

	Tuner->TunerRegs[77].Reg_Num = 110 ;
	Tuner->TunerRegs[77].Reg_Val = 0x81 ;

	Tuner->TunerRegs[78].Reg_Num = 111 ;
	Tuner->TunerRegs[78].Reg_Val = 0xC0 ;

	Tuner->TunerRegs[79].Reg_Num = 112 ;
	Tuner->TunerRegs[79].Reg_Val = 0x10 ;

	Tuner->TunerRegs[80].Reg_Num = 131 ;
	Tuner->TunerRegs[80].Reg_Val = 0x8A ;

	Tuner->TunerRegs[81].Reg_Num = 132 ;
	Tuner->TunerRegs[81].Reg_Val = 0x10 ;

	Tuner->TunerRegs[82].Reg_Num = 133 ;
	Tuner->TunerRegs[82].Reg_Val = 0x24 ;

	Tuner->TunerRegs[83].Reg_Num = 134 ;
	Tuner->TunerRegs[83].Reg_Val = 0x00 ;

	Tuner->TunerRegs[84].Reg_Num = 135 ;
	Tuner->TunerRegs[84].Reg_Val = 0x00 ;

	Tuner->TunerRegs[85].Reg_Num = 136 ;
	Tuner->TunerRegs[85].Reg_Val = 0x7E ;

	Tuner->TunerRegs[86].Reg_Num = 137 ;
	Tuner->TunerRegs[86].Reg_Val = 0x40 ;

	Tuner->TunerRegs[87].Reg_Num = 138 ;
	Tuner->TunerRegs[87].Reg_Val = 0x38 ;

	Tuner->TunerRegs[88].Reg_Num = 146 ;
	Tuner->TunerRegs[88].Reg_Val = 0xF6 ;

	Tuner->TunerRegs[89].Reg_Num = 147 ;
	Tuner->TunerRegs[89].Reg_Val = 0x1A ;

	Tuner->TunerRegs[90].Reg_Num = 148 ;
	Tuner->TunerRegs[90].Reg_Val = 0x62 ;

	Tuner->TunerRegs[91].Reg_Num = 149 ;
	Tuner->TunerRegs[91].Reg_Val = 0x33 ;

	Tuner->TunerRegs[92].Reg_Num = 150 ;
	Tuner->TunerRegs[92].Reg_Val = 0x80 ;

	Tuner->TunerRegs[93].Reg_Num = 156 ;
	Tuner->TunerRegs[93].Reg_Val = 0x56 ;

	Tuner->TunerRegs[94].Reg_Num = 157 ;
	Tuner->TunerRegs[94].Reg_Val = 0x17 ;

	Tuner->TunerRegs[95].Reg_Num = 158 ;
	Tuner->TunerRegs[95].Reg_Val = 0xA9 ;

	Tuner->TunerRegs[96].Reg_Num = 159 ;
	Tuner->TunerRegs[96].Reg_Val = 0x00 ;

	Tuner->TunerRegs[97].Reg_Num = 160 ;
	Tuner->TunerRegs[97].Reg_Val = 0x00 ;

	Tuner->TunerRegs[98].Reg_Num = 161 ;
	Tuner->TunerRegs[98].Reg_Val = 0x00 ;

	Tuner->TunerRegs[99].Reg_Num = 162 ;
	Tuner->TunerRegs[99].Reg_Val = 0x40 ;

	Tuner->TunerRegs[100].Reg_Num = 166 ;
	Tuner->TunerRegs[100].Reg_Val = 0xAE ;

	Tuner->TunerRegs[101].Reg_Num = 167 ;
	Tuner->TunerRegs[101].Reg_Val = 0x03 ;

	Tuner->TunerRegs[102].Reg_Num = 168 ;
	Tuner->TunerRegs[102].Reg_Val = 0xF2 ;

	Tuner->TunerRegs[103].Reg_Num = 195 ;
	Tuner->TunerRegs[103].Reg_Val = 0x00 ;

	return 0 ;
}

WORD MXL5005_ControlInit (Tuner_struct *Tuner)
{
	Tuner->Init_Ctrl_Num = INITCTRL_NUM ;

	Tuner->Init_Ctrl[0].Ctrl_Num = DN_IQTN_AMP_CUT ;
	Tuner->Init_Ctrl[0].size = 1 ;
	Tuner->Init_Ctrl[0].addr[0] = 73;
	Tuner->Init_Ctrl[0].bit[0] = 7;
	Tuner->Init_Ctrl[0].val[0] = 0;

	Tuner->Init_Ctrl[1].Ctrl_Num = BB_MODE ;
	Tuner->Init_Ctrl[1].size = 1 ;
	Tuner->Init_Ctrl[1].addr[0] = 53;
	Tuner->Init_Ctrl[1].bit[0] = 2;
	Tuner->Init_Ctrl[1].val[0] = 1;

	Tuner->Init_Ctrl[2].Ctrl_Num = BB_BUF ;
	Tuner->Init_Ctrl[2].size = 2 ;
	Tuner->Init_Ctrl[2].addr[0] = 53;
	Tuner->Init_Ctrl[2].bit[0] = 1;
	Tuner->Init_Ctrl[2].val[0] = 0;
	Tuner->Init_Ctrl[2].addr[1] = 57;
	Tuner->Init_Ctrl[2].bit[1] = 0;
	Tuner->Init_Ctrl[2].val[1] = 1;

	Tuner->Init_Ctrl[3].Ctrl_Num = BB_BUF_OA ; 
	Tuner->Init_Ctrl[3].size = 1 ;
	Tuner->Init_Ctrl[3].addr[0] = 53;
	Tuner->Init_Ctrl[3].bit[0] = 0;
	Tuner->Init_Ctrl[3].val[0] = 0;

	Tuner->Init_Ctrl[4].Ctrl_Num = BB_ALPF_BANDSELECT ;
	Tuner->Init_Ctrl[4].size = 3 ;
	Tuner->Init_Ctrl[4].addr[0] = 53;
	Tuner->Init_Ctrl[4].bit[0] = 5;
	Tuner->Init_Ctrl[4].val[0] = 0;
	Tuner->Init_Ctrl[4].addr[1] = 53;
	Tuner->Init_Ctrl[4].bit[1] = 6;
	Tuner->Init_Ctrl[4].val[1] = 0;
	Tuner->Init_Ctrl[4].addr[2] = 53;
	Tuner->Init_Ctrl[4].bit[2] = 7;
	Tuner->Init_Ctrl[4].val[2] = 1;

	Tuner->Init_Ctrl[5].Ctrl_Num = BB_IQSWAP ;
	Tuner->Init_Ctrl[5].size = 1 ;
	Tuner->Init_Ctrl[5].addr[0] = 59;
	Tuner->Init_Ctrl[5].bit[0] = 0;
	Tuner->Init_Ctrl[5].val[0] = 0;

	Tuner->Init_Ctrl[6].Ctrl_Num = BB_DLPF_BANDSEL ;
	Tuner->Init_Ctrl[6].size = 2 ;
	Tuner->Init_Ctrl[6].addr[0] = 53;
	Tuner->Init_Ctrl[6].bit[0] = 3;
	Tuner->Init_Ctrl[6].val[0] = 0;
	Tuner->Init_Ctrl[6].addr[1] = 53;
	Tuner->Init_Ctrl[6].bit[1] = 4;
	Tuner->Init_Ctrl[6].val[1] = 1;

	Tuner->Init_Ctrl[7].Ctrl_Num = RFSYN_CHP_GAIN ;
	Tuner->Init_Ctrl[7].size = 4 ;
	Tuner->Init_Ctrl[7].addr[0] = 22;
	Tuner->Init_Ctrl[7].bit[0] = 4;
	Tuner->Init_Ctrl[7].val[0] = 0;
	Tuner->Init_Ctrl[7].addr[1] = 22;
	Tuner->Init_Ctrl[7].bit[1] = 5;
	Tuner->Init_Ctrl[7].val[1] = 1;
	Tuner->Init_Ctrl[7].addr[2] = 22;
	Tuner->Init_Ctrl[7].bit[2] = 6;
	Tuner->Init_Ctrl[7].val[2] = 1;
	Tuner->Init_Ctrl[7].addr[3] = 22;
	Tuner->Init_Ctrl[7].bit[3] = 7;
	Tuner->Init_Ctrl[7].val[3] = 0;

	Tuner->Init_Ctrl[8].Ctrl_Num = RFSYN_EN_CHP_HIGAIN ;
	Tuner->Init_Ctrl[8].size = 1 ;
	Tuner->Init_Ctrl[8].addr[0] = 22;
	Tuner->Init_Ctrl[8].bit[0] = 2;
	Tuner->Init_Ctrl[8].val[0] = 0;

	Tuner->Init_Ctrl[9].Ctrl_Num = AGC_IF ;
	Tuner->Init_Ctrl[9].size = 4 ;
	Tuner->Init_Ctrl[9].addr[0] = 76;
	Tuner->Init_Ctrl[9].bit[0] = 0;
	Tuner->Init_Ctrl[9].val[0] = 1;
	Tuner->Init_Ctrl[9].addr[1] = 76;
	Tuner->Init_Ctrl[9].bit[1] = 1;
	Tuner->Init_Ctrl[9].val[1] = 1;
	Tuner->Init_Ctrl[9].addr[2] = 76;
	Tuner->Init_Ctrl[9].bit[2] = 2;
	Tuner->Init_Ctrl[9].val[2] = 0;
	Tuner->Init_Ctrl[9].addr[3] = 76;
	Tuner->Init_Ctrl[9].bit[3] = 3;
	Tuner->Init_Ctrl[9].val[3] = 1;

	Tuner->Init_Ctrl[10].Ctrl_Num = AGC_RF ;
	Tuner->Init_Ctrl[10].size = 4 ;
	Tuner->Init_Ctrl[10].addr[0] = 76;
	Tuner->Init_Ctrl[10].bit[0] = 4;
	Tuner->Init_Ctrl[10].val[0] = 1;
	Tuner->Init_Ctrl[10].addr[1] = 76;
	Tuner->Init_Ctrl[10].bit[1] = 5;
	Tuner->Init_Ctrl[10].val[1] = 1;
	Tuner->Init_Ctrl[10].addr[2] = 76;
	Tuner->Init_Ctrl[10].bit[2] = 6;
	Tuner->Init_Ctrl[10].val[2] = 0;
	Tuner->Init_Ctrl[10].addr[3] = 76;
	Tuner->Init_Ctrl[10].bit[3] = 7;
	Tuner->Init_Ctrl[10].val[3] = 1;

	Tuner->Init_Ctrl[11].Ctrl_Num = IF_DIVVAL ;
	Tuner->Init_Ctrl[11].size = 5 ;
	Tuner->Init_Ctrl[11].addr[0] = 43;
	Tuner->Init_Ctrl[11].bit[0] = 3;
	Tuner->Init_Ctrl[11].val[0] = 0;
	Tuner->Init_Ctrl[11].addr[1] = 43;
	Tuner->Init_Ctrl[11].bit[1] = 4;
	Tuner->Init_Ctrl[11].val[1] = 0;
	Tuner->Init_Ctrl[11].addr[2] = 43;
	Tuner->Init_Ctrl[11].bit[2] = 5;
	Tuner->Init_Ctrl[11].val[2] = 0;
	Tuner->Init_Ctrl[11].addr[3] = 43;
	Tuner->Init_Ctrl[11].bit[3] = 6;
	Tuner->Init_Ctrl[11].val[3] = 1;
	Tuner->Init_Ctrl[11].addr[4] = 43;
	Tuner->Init_Ctrl[11].bit[4] = 7;
	Tuner->Init_Ctrl[11].val[4] = 0;

	Tuner->Init_Ctrl[12].Ctrl_Num = IF_VCO_BIAS ;
	Tuner->Init_Ctrl[12].size = 6 ;
	Tuner->Init_Ctrl[12].addr[0] = 44;
	Tuner->Init_Ctrl[12].bit[0] = 2;
	Tuner->Init_Ctrl[12].val[0] = 0;
	Tuner->Init_Ctrl[12].addr[1] = 44;
	Tuner->Init_Ctrl[12].bit[1] = 3;
	Tuner->Init_Ctrl[12].val[1] = 0;
	Tuner->Init_Ctrl[12].addr[2] = 44;
	Tuner->Init_Ctrl[12].bit[2] = 4;
	Tuner->Init_Ctrl[12].val[2] = 0;
	Tuner->Init_Ctrl[12].addr[3] = 44;
	Tuner->Init_Ctrl[12].bit[3] = 5;
	Tuner->Init_Ctrl[12].val[3] = 1;
	Tuner->Init_Ctrl[12].addr[4] = 44;
	Tuner->Init_Ctrl[12].bit[4] = 6;
	Tuner->Init_Ctrl[12].val[4] = 0;
	Tuner->Init_Ctrl[12].addr[5] = 44;
	Tuner->Init_Ctrl[12].bit[5] = 7;
	Tuner->Init_Ctrl[12].val[5] = 0;

	Tuner->Init_Ctrl[13].Ctrl_Num = CHCAL_INT_MOD_IF ;
	Tuner->Init_Ctrl[13].size = 7 ;
	Tuner->Init_Ctrl[13].addr[0] = 11;
	Tuner->Init_Ctrl[13].bit[0] = 0;
	Tuner->Init_Ctrl[13].val[0] = 1;
	Tuner->Init_Ctrl[13].addr[1] = 11;
	Tuner->Init_Ctrl[13].bit[1] = 1;
	Tuner->Init_Ctrl[13].val[1] = 0;
	Tuner->Init_Ctrl[13].addr[2] = 11;
	Tuner->Init_Ctrl[13].bit[2] = 2;
	Tuner->Init_Ctrl[13].val[2] = 0;
	Tuner->Init_Ctrl[13].addr[3] = 11;
	Tuner->Init_Ctrl[13].bit[3] = 3;
	Tuner->Init_Ctrl[13].val[3] = 1;
	Tuner->Init_Ctrl[13].addr[4] = 11;
	Tuner->Init_Ctrl[13].bit[4] = 4;
	Tuner->Init_Ctrl[13].val[4] = 1;
	Tuner->Init_Ctrl[13].addr[5] = 11;
	Tuner->Init_Ctrl[13].bit[5] = 5;
	Tuner->Init_Ctrl[13].val[5] = 0;
	Tuner->Init_Ctrl[13].addr[6] = 11;
	Tuner->Init_Ctrl[13].bit[6] = 6;
	Tuner->Init_Ctrl[13].val[6] = 0;

	Tuner->Init_Ctrl[14].Ctrl_Num = CHCAL_FRAC_MOD_IF ;
	Tuner->Init_Ctrl[14].size = 16 ;
	Tuner->Init_Ctrl[14].addr[0] = 13;
	Tuner->Init_Ctrl[14].bit[0] = 0;
	Tuner->Init_Ctrl[14].val[0] = 0;
	Tuner->Init_Ctrl[14].addr[1] = 13;
	Tuner->Init_Ctrl[14].bit[1] = 1;
	Tuner->Init_Ctrl[14].val[1] = 0;
	Tuner->Init_Ctrl[14].addr[2] = 13;
	Tuner->Init_Ctrl[14].bit[2] = 2;
	Tuner->Init_Ctrl[14].val[2] = 0;
	Tuner->Init_Ctrl[14].addr[3] = 13;
	Tuner->Init_Ctrl[14].bit[3] = 3;
	Tuner->Init_Ctrl[14].val[3] = 0;
	Tuner->Init_Ctrl[14].addr[4] = 13;
	Tuner->Init_Ctrl[14].bit[4] = 4;
	Tuner->Init_Ctrl[14].val[4] = 0;
	Tuner->Init_Ctrl[14].addr[5] = 13;
	Tuner->Init_Ctrl[14].bit[5] = 5;
	Tuner->Init_Ctrl[14].val[5] = 0;
	Tuner->Init_Ctrl[14].addr[6] = 13;
	Tuner->Init_Ctrl[14].bit[6] = 6;
	Tuner->Init_Ctrl[14].val[6] = 0;
	Tuner->Init_Ctrl[14].addr[7] = 13;
	Tuner->Init_Ctrl[14].bit[7] = 7;
	Tuner->Init_Ctrl[14].val[7] = 0;
	Tuner->Init_Ctrl[14].addr[8] = 12;
	Tuner->Init_Ctrl[14].bit[8] = 0;
	Tuner->Init_Ctrl[14].val[8] = 0;
	Tuner->Init_Ctrl[14].addr[9] = 12;
	Tuner->Init_Ctrl[14].bit[9] = 1;
	Tuner->Init_Ctrl[14].val[9] = 0;
	Tuner->Init_Ctrl[14].addr[10] = 12;
	Tuner->Init_Ctrl[14].bit[10] = 2;
	Tuner->Init_Ctrl[14].val[10] = 0;
	Tuner->Init_Ctrl[14].addr[11] = 12;
	Tuner->Init_Ctrl[14].bit[11] = 3;
	Tuner->Init_Ctrl[14].val[11] = 0;
	Tuner->Init_Ctrl[14].addr[12] = 12;
	Tuner->Init_Ctrl[14].bit[12] = 4;
	Tuner->Init_Ctrl[14].val[12] = 0;
	Tuner->Init_Ctrl[14].addr[13] = 12;
	Tuner->Init_Ctrl[14].bit[13] = 5;
	Tuner->Init_Ctrl[14].val[13] = 1;
	Tuner->Init_Ctrl[14].addr[14] = 12;
	Tuner->Init_Ctrl[14].bit[14] = 6;
	Tuner->Init_Ctrl[14].val[14] = 1;
	Tuner->Init_Ctrl[14].addr[15] = 12;
	Tuner->Init_Ctrl[14].bit[15] = 7;
	Tuner->Init_Ctrl[14].val[15] = 0;

	Tuner->Init_Ctrl[15].Ctrl_Num = DRV_RES_SEL ;
	Tuner->Init_Ctrl[15].size = 3 ;
	Tuner->Init_Ctrl[15].addr[0] = 147;
	Tuner->Init_Ctrl[15].bit[0] = 2;
	Tuner->Init_Ctrl[15].val[0] = 0;
	Tuner->Init_Ctrl[15].addr[1] = 147;
	Tuner->Init_Ctrl[15].bit[1] = 3;
	Tuner->Init_Ctrl[15].val[1] = 1;
	Tuner->Init_Ctrl[15].addr[2] = 147;
	Tuner->Init_Ctrl[15].bit[2] = 4;
	Tuner->Init_Ctrl[15].val[2] = 1;

	Tuner->Init_Ctrl[16].Ctrl_Num = I_DRIVER ;
	Tuner->Init_Ctrl[16].size = 2 ;
	Tuner->Init_Ctrl[16].addr[0] = 147;
	Tuner->Init_Ctrl[16].bit[0] = 0;
	Tuner->Init_Ctrl[16].val[0] = 0;
	Tuner->Init_Ctrl[16].addr[1] = 147;
	Tuner->Init_Ctrl[16].bit[1] = 1;
	Tuner->Init_Ctrl[16].val[1] = 1;

	Tuner->Init_Ctrl[17].Ctrl_Num = EN_AAF ;
	Tuner->Init_Ctrl[17].size = 1 ;
	Tuner->Init_Ctrl[17].addr[0] = 147;
	Tuner->Init_Ctrl[17].bit[0] = 7;
	Tuner->Init_Ctrl[17].val[0] = 0;

	Tuner->Init_Ctrl[18].Ctrl_Num = EN_3P ;
	Tuner->Init_Ctrl[18].size = 1 ;
	Tuner->Init_Ctrl[18].addr[0] = 147;
	Tuner->Init_Ctrl[18].bit[0] = 6;
	Tuner->Init_Ctrl[18].val[0] = 0;

	Tuner->Init_Ctrl[19].Ctrl_Num = EN_AUX_3P ;
	Tuner->Init_Ctrl[19].size = 1 ;
	Tuner->Init_Ctrl[19].addr[0] = 156;
	Tuner->Init_Ctrl[19].bit[0] = 0;
	Tuner->Init_Ctrl[19].val[0] = 0;

	Tuner->Init_Ctrl[20].Ctrl_Num = SEL_AAF_BAND ;
	Tuner->Init_Ctrl[20].size = 1 ;
	Tuner->Init_Ctrl[20].addr[0] = 147;
	Tuner->Init_Ctrl[20].bit[0] = 5;
	Tuner->Init_Ctrl[20].val[0] = 0;

	Tuner->Init_Ctrl[21].Ctrl_Num = SEQ_ENCLK16_CLK_OUT ;
	Tuner->Init_Ctrl[21].size = 1 ;
	Tuner->Init_Ctrl[21].addr[0] = 137;
	Tuner->Init_Ctrl[21].bit[0] = 4;
	Tuner->Init_Ctrl[21].val[0] = 0;

	Tuner->Init_Ctrl[22].Ctrl_Num = SEQ_SEL4_16B ;
	Tuner->Init_Ctrl[22].size = 1 ;
	Tuner->Init_Ctrl[22].addr[0] = 137;
	Tuner->Init_Ctrl[22].bit[0] = 7;
	Tuner->Init_Ctrl[22].val[0] = 0;

	Tuner->Init_Ctrl[23].Ctrl_Num = XTAL_CAPSELECT ;
	Tuner->Init_Ctrl[23].size = 1 ;
	Tuner->Init_Ctrl[23].addr[0] = 91;
	Tuner->Init_Ctrl[23].bit[0] = 5;
	Tuner->Init_Ctrl[23].val[0] = 1;

	Tuner->Init_Ctrl[24].Ctrl_Num = IF_SEL_DBL ;
	Tuner->Init_Ctrl[24].size = 1 ;
	Tuner->Init_Ctrl[24].addr[0] = 43;
	Tuner->Init_Ctrl[24].bit[0] = 0;
	Tuner->Init_Ctrl[24].val[0] = 1;

	Tuner->Init_Ctrl[25].Ctrl_Num = RFSYN_R_DIV ;
	Tuner->Init_Ctrl[25].size = 2 ;
	Tuner->Init_Ctrl[25].addr[0] = 22;
	Tuner->Init_Ctrl[25].bit[0] = 0;
	Tuner->Init_Ctrl[25].val[0] = 1;
	Tuner->Init_Ctrl[25].addr[1] = 22;
	Tuner->Init_Ctrl[25].bit[1] = 1;
	Tuner->Init_Ctrl[25].val[1] = 1;

	Tuner->Init_Ctrl[26].Ctrl_Num = SEQ_EXTSYNTHCALIF ;
	Tuner->Init_Ctrl[26].size = 1 ;
	Tuner->Init_Ctrl[26].addr[0] = 134;
	Tuner->Init_Ctrl[26].bit[0] = 2;
	Tuner->Init_Ctrl[26].val[0] = 0;

	Tuner->Init_Ctrl[27].Ctrl_Num = SEQ_EXTDCCAL ;
	Tuner->Init_Ctrl[27].size = 1 ;
	Tuner->Init_Ctrl[27].addr[0] = 137;
	Tuner->Init_Ctrl[27].bit[0] = 3;
	Tuner->Init_Ctrl[27].val[0] = 0;

	Tuner->Init_Ctrl[28].Ctrl_Num = AGC_EN_RSSI ;
	Tuner->Init_Ctrl[28].size = 1 ;
	Tuner->Init_Ctrl[28].addr[0] = 77;
	Tuner->Init_Ctrl[28].bit[0] = 7;
	Tuner->Init_Ctrl[28].val[0] = 0;

	Tuner->Init_Ctrl[29].Ctrl_Num = RFA_ENCLKRFAGC ;
	Tuner->Init_Ctrl[29].size = 1 ;
	Tuner->Init_Ctrl[29].addr[0] = 166;
	Tuner->Init_Ctrl[29].bit[0] = 7;
	Tuner->Init_Ctrl[29].val[0] = 1;

	Tuner->Init_Ctrl[30].Ctrl_Num = RFA_RSSI_REFH ;
	Tuner->Init_Ctrl[30].size = 3 ;
	Tuner->Init_Ctrl[30].addr[0] = 166;
	Tuner->Init_Ctrl[30].bit[0] = 0;
	Tuner->Init_Ctrl[30].val[0] = 0;
	Tuner->Init_Ctrl[30].addr[1] = 166;
	Tuner->Init_Ctrl[30].bit[1] = 1;
	Tuner->Init_Ctrl[30].val[1] = 1;
	Tuner->Init_Ctrl[30].addr[2] = 166;
	Tuner->Init_Ctrl[30].bit[2] = 2;
	Tuner->Init_Ctrl[30].val[2] = 1;

	Tuner->Init_Ctrl[31].Ctrl_Num = RFA_RSSI_REF ;
	Tuner->Init_Ctrl[31].size = 3 ;
	Tuner->Init_Ctrl[31].addr[0] = 166;
	Tuner->Init_Ctrl[31].bit[0] = 3;
	Tuner->Init_Ctrl[31].val[0] = 1;
	Tuner->Init_Ctrl[31].addr[1] = 166;
	Tuner->Init_Ctrl[31].bit[1] = 4;
	Tuner->Init_Ctrl[31].val[1] = 0;
	Tuner->Init_Ctrl[31].addr[2] = 166;
	Tuner->Init_Ctrl[31].bit[2] = 5;
	Tuner->Init_Ctrl[31].val[2] = 1;

	Tuner->Init_Ctrl[32].Ctrl_Num = RFA_RSSI_REFL ;
	Tuner->Init_Ctrl[32].size = 3 ;
	Tuner->Init_Ctrl[32].addr[0] = 167;
	Tuner->Init_Ctrl[32].bit[0] = 0;
	Tuner->Init_Ctrl[32].val[0] = 1;
	Tuner->Init_Ctrl[32].addr[1] = 167;
	Tuner->Init_Ctrl[32].bit[1] = 1;
	Tuner->Init_Ctrl[32].val[1] = 1;
	Tuner->Init_Ctrl[32].addr[2] = 167;
	Tuner->Init_Ctrl[32].bit[2] = 2;
	Tuner->Init_Ctrl[32].val[2] = 0;

	Tuner->Init_Ctrl[33].Ctrl_Num = RFA_FLR ;
	Tuner->Init_Ctrl[33].size = 4 ;
	Tuner->Init_Ctrl[33].addr[0] = 168;
	Tuner->Init_Ctrl[33].bit[0] = 0;
	Tuner->Init_Ctrl[33].val[0] = 0;
	Tuner->Init_Ctrl[33].addr[1] = 168;
	Tuner->Init_Ctrl[33].bit[1] = 1;
	Tuner->Init_Ctrl[33].val[1] = 1;
	Tuner->Init_Ctrl[33].addr[2] = 168;
	Tuner->Init_Ctrl[33].bit[2] = 2;
	Tuner->Init_Ctrl[33].val[2] = 0;
	Tuner->Init_Ctrl[33].addr[3] = 168;
	Tuner->Init_Ctrl[33].bit[3] = 3;
	Tuner->Init_Ctrl[33].val[3] = 0;

	Tuner->Init_Ctrl[34].Ctrl_Num = RFA_CEIL ;
	Tuner->Init_Ctrl[34].size = 4 ;
	Tuner->Init_Ctrl[34].addr[0] = 168;
	Tuner->Init_Ctrl[34].bit[0] = 4;
	Tuner->Init_Ctrl[34].val[0] = 1;
	Tuner->Init_Ctrl[34].addr[1] = 168;
	Tuner->Init_Ctrl[34].bit[1] = 5;
	Tuner->Init_Ctrl[34].val[1] = 1;
	Tuner->Init_Ctrl[34].addr[2] = 168;
	Tuner->Init_Ctrl[34].bit[2] = 6;
	Tuner->Init_Ctrl[34].val[2] = 1;
	Tuner->Init_Ctrl[34].addr[3] = 168;
	Tuner->Init_Ctrl[34].bit[3] = 7;
	Tuner->Init_Ctrl[34].val[3] = 1;

	Tuner->Init_Ctrl[35].Ctrl_Num = SEQ_EXTIQFSMPULSE ;
	Tuner->Init_Ctrl[35].size = 1 ;
	Tuner->Init_Ctrl[35].addr[0] = 135;
	Tuner->Init_Ctrl[35].bit[0] = 0;
	Tuner->Init_Ctrl[35].val[0] = 0;

	Tuner->Init_Ctrl[36].Ctrl_Num = OVERRIDE_1 ;
	Tuner->Init_Ctrl[36].size = 1 ;
	Tuner->Init_Ctrl[36].addr[0] = 56;
	Tuner->Init_Ctrl[36].bit[0] = 3;
	Tuner->Init_Ctrl[36].val[0] = 0;

	Tuner->Init_Ctrl[37].Ctrl_Num = BB_INITSTATE_DLPF_TUNE ;
	Tuner->Init_Ctrl[37].size = 7 ;
	Tuner->Init_Ctrl[37].addr[0] = 59;
	Tuner->Init_Ctrl[37].bit[0] = 1;
	Tuner->Init_Ctrl[37].val[0] = 0;
	Tuner->Init_Ctrl[37].addr[1] = 59;
	Tuner->Init_Ctrl[37].bit[1] = 2;
	Tuner->Init_Ctrl[37].val[1] = 0;
	Tuner->Init_Ctrl[37].addr[2] = 59;
	Tuner->Init_Ctrl[37].bit[2] = 3;
	Tuner->Init_Ctrl[37].val[2] = 0;
	Tuner->Init_Ctrl[37].addr[3] = 59;
	Tuner->Init_Ctrl[37].bit[3] = 4;
	Tuner->Init_Ctrl[37].val[3] = 0;
	Tuner->Init_Ctrl[37].addr[4] = 59;
	Tuner->Init_Ctrl[37].bit[4] = 5;
	Tuner->Init_Ctrl[37].val[4] = 0;
	Tuner->Init_Ctrl[37].addr[5] = 59;
	Tuner->Init_Ctrl[37].bit[5] = 6;
	Tuner->Init_Ctrl[37].val[5] = 0;
	Tuner->Init_Ctrl[37].addr[6] = 59;
	Tuner->Init_Ctrl[37].bit[6] = 7;
	Tuner->Init_Ctrl[37].val[6] = 0;

	Tuner->Init_Ctrl[38].Ctrl_Num = TG_R_DIV ;
	Tuner->Init_Ctrl[38].size = 6 ;
	Tuner->Init_Ctrl[38].addr[0] = 32;
	Tuner->Init_Ctrl[38].bit[0] = 2;
	Tuner->Init_Ctrl[38].val[0] = 0;
	Tuner->Init_Ctrl[38].addr[1] = 32;
	Tuner->Init_Ctrl[38].bit[1] = 3;
	Tuner->Init_Ctrl[38].val[1] = 0;
	Tuner->Init_Ctrl[38].addr[2] = 32;
	Tuner->Init_Ctrl[38].bit[2] = 4;
	Tuner->Init_Ctrl[38].val[2] = 0;
	Tuner->Init_Ctrl[38].addr[3] = 32;
	Tuner->Init_Ctrl[38].bit[3] = 5;
	Tuner->Init_Ctrl[38].val[3] = 0;
	Tuner->Init_Ctrl[38].addr[4] = 32;
	Tuner->Init_Ctrl[38].bit[4] = 6;
	Tuner->Init_Ctrl[38].val[4] = 1;
	Tuner->Init_Ctrl[38].addr[5] = 32;
	Tuner->Init_Ctrl[38].bit[5] = 7;
	Tuner->Init_Ctrl[38].val[5] = 0;

	Tuner->Init_Ctrl[39].Ctrl_Num = EN_CHP_LIN_B ;
	Tuner->Init_Ctrl[39].size = 1 ;
	Tuner->Init_Ctrl[39].addr[0] = 25;
	Tuner->Init_Ctrl[39].bit[0] = 3;
	Tuner->Init_Ctrl[39].val[0] = 1;


	Tuner->CH_Ctrl_Num = CHCTRL_NUM ;

	Tuner->CH_Ctrl[0].Ctrl_Num = DN_POLY ;
	Tuner->CH_Ctrl[0].size = 2 ;
	Tuner->CH_Ctrl[0].addr[0] = 68;
	Tuner->CH_Ctrl[0].bit[0] = 6;
	Tuner->CH_Ctrl[0].val[0] = 1;
	Tuner->CH_Ctrl[0].addr[1] = 68;
	Tuner->CH_Ctrl[0].bit[1] = 7;
	Tuner->CH_Ctrl[0].val[1] = 1;

	Tuner->CH_Ctrl[1].Ctrl_Num = DN_RFGAIN ;
	Tuner->CH_Ctrl[1].size = 2 ;
	Tuner->CH_Ctrl[1].addr[0] = 70;
	Tuner->CH_Ctrl[1].bit[0] = 6;
	Tuner->CH_Ctrl[1].val[0] = 1;
	Tuner->CH_Ctrl[1].addr[1] = 70;
	Tuner->CH_Ctrl[1].bit[1] = 7;
	Tuner->CH_Ctrl[1].val[1] = 0;

	Tuner->CH_Ctrl[2].Ctrl_Num = DN_CAP_RFLPF ;
	Tuner->CH_Ctrl[2].size = 9 ;
	Tuner->CH_Ctrl[2].addr[0] = 69;
	Tuner->CH_Ctrl[2].bit[0] = 5;
	Tuner->CH_Ctrl[2].val[0] = 0;
	Tuner->CH_Ctrl[2].addr[1] = 69;
	Tuner->CH_Ctrl[2].bit[1] = 6;
	Tuner->CH_Ctrl[2].val[1] = 0;
	Tuner->CH_Ctrl[2].addr[2] = 69;
	Tuner->CH_Ctrl[2].bit[2] = 7;
	Tuner->CH_Ctrl[2].val[2] = 0;
	Tuner->CH_Ctrl[2].addr[3] = 68;
	Tuner->CH_Ctrl[2].bit[3] = 0;
	Tuner->CH_Ctrl[2].val[3] = 0;
	Tuner->CH_Ctrl[2].addr[4] = 68;
	Tuner->CH_Ctrl[2].bit[4] = 1;
	Tuner->CH_Ctrl[2].val[4] = 0;
	Tuner->CH_Ctrl[2].addr[5] = 68;
	Tuner->CH_Ctrl[2].bit[5] = 2;
	Tuner->CH_Ctrl[2].val[5] = 0;
	Tuner->CH_Ctrl[2].addr[6] = 68;
	Tuner->CH_Ctrl[2].bit[6] = 3;
	Tuner->CH_Ctrl[2].val[6] = 0;
	Tuner->CH_Ctrl[2].addr[7] = 68;
	Tuner->CH_Ctrl[2].bit[7] = 4;
	Tuner->CH_Ctrl[2].val[7] = 0;
	Tuner->CH_Ctrl[2].addr[8] = 68;
	Tuner->CH_Ctrl[2].bit[8] = 5;
	Tuner->CH_Ctrl[2].val[8] = 0;

	Tuner->CH_Ctrl[3].Ctrl_Num = DN_EN_VHFUHFBAR ;
	Tuner->CH_Ctrl[3].size = 1 ;
	Tuner->CH_Ctrl[3].addr[0] = 70;
	Tuner->CH_Ctrl[3].bit[0] = 5;
	Tuner->CH_Ctrl[3].val[0] = 0;

	Tuner->CH_Ctrl[4].Ctrl_Num = DN_GAIN_ADJUST ;
	Tuner->CH_Ctrl[4].size = 3 ;
	Tuner->CH_Ctrl[4].addr[0] = 73;
	Tuner->CH_Ctrl[4].bit[0] = 4;
	Tuner->CH_Ctrl[4].val[0] = 0;
	Tuner->CH_Ctrl[4].addr[1] = 73;
	Tuner->CH_Ctrl[4].bit[1] = 5;
	Tuner->CH_Ctrl[4].val[1] = 1;
	Tuner->CH_Ctrl[4].addr[2] = 73;
	Tuner->CH_Ctrl[4].bit[2] = 6;
	Tuner->CH_Ctrl[4].val[2] = 0;

	Tuner->CH_Ctrl[5].Ctrl_Num = DN_IQTNBUF_AMP ;
	Tuner->CH_Ctrl[5].size = 4 ;
	Tuner->CH_Ctrl[5].addr[0] = 70;
	Tuner->CH_Ctrl[5].bit[0] = 0;
	Tuner->CH_Ctrl[5].val[0] = 0;
	Tuner->CH_Ctrl[5].addr[1] = 70;
	Tuner->CH_Ctrl[5].bit[1] = 1;
	Tuner->CH_Ctrl[5].val[1] = 0;
	Tuner->CH_Ctrl[5].addr[2] = 70;
	Tuner->CH_Ctrl[5].bit[2] = 2;
	Tuner->CH_Ctrl[5].val[2] = 0;
	Tuner->CH_Ctrl[5].addr[3] = 70;
	Tuner->CH_Ctrl[5].bit[3] = 3;
	Tuner->CH_Ctrl[5].val[3] = 0;

	Tuner->CH_Ctrl[6].Ctrl_Num = DN_IQTNGNBFBIAS_BST ;
	Tuner->CH_Ctrl[6].size = 1 ;
	Tuner->CH_Ctrl[6].addr[0] = 70;
	Tuner->CH_Ctrl[6].bit[0] = 4;
	Tuner->CH_Ctrl[6].val[0] = 1;

	Tuner->CH_Ctrl[7].Ctrl_Num = RFSYN_EN_OUTMUX ;
	Tuner->CH_Ctrl[7].size = 1 ;
	Tuner->CH_Ctrl[7].addr[0] = 111;
	Tuner->CH_Ctrl[7].bit[0] = 4;
	Tuner->CH_Ctrl[7].val[0] = 0;

	Tuner->CH_Ctrl[8].Ctrl_Num = RFSYN_SEL_VCO_OUT ;
	Tuner->CH_Ctrl[8].size = 1 ;
	Tuner->CH_Ctrl[8].addr[0] = 111;
	Tuner->CH_Ctrl[8].bit[0] = 7;
	Tuner->CH_Ctrl[8].val[0] = 1;

	Tuner->CH_Ctrl[9].Ctrl_Num = RFSYN_SEL_VCO_HI ;
	Tuner->CH_Ctrl[9].size = 1 ;
	Tuner->CH_Ctrl[9].addr[0] = 111;
	Tuner->CH_Ctrl[9].bit[0] = 6;
	Tuner->CH_Ctrl[9].val[0] = 1;

	Tuner->CH_Ctrl[10].Ctrl_Num = RFSYN_SEL_DIVM ;
	Tuner->CH_Ctrl[10].size = 1 ;
	Tuner->CH_Ctrl[10].addr[0] = 111;
	Tuner->CH_Ctrl[10].bit[0] = 5;
	Tuner->CH_Ctrl[10].val[0] = 0;

	Tuner->CH_Ctrl[11].Ctrl_Num = RFSYN_RF_DIV_BIAS ;
	Tuner->CH_Ctrl[11].size = 2 ;
	Tuner->CH_Ctrl[11].addr[0] = 110;
	Tuner->CH_Ctrl[11].bit[0] = 0;
	Tuner->CH_Ctrl[11].val[0] = 1;
	Tuner->CH_Ctrl[11].addr[1] = 110;
	Tuner->CH_Ctrl[11].bit[1] = 1;
	Tuner->CH_Ctrl[11].val[1] = 0;

	Tuner->CH_Ctrl[12].Ctrl_Num = DN_SEL_FREQ ;
	Tuner->CH_Ctrl[12].size = 3 ;
	Tuner->CH_Ctrl[12].addr[0] = 69;
	Tuner->CH_Ctrl[12].bit[0] = 2;
	Tuner->CH_Ctrl[12].val[0] = 0;
	Tuner->CH_Ctrl[12].addr[1] = 69;
	Tuner->CH_Ctrl[12].bit[1] = 3;
	Tuner->CH_Ctrl[12].val[1] = 0;
	Tuner->CH_Ctrl[12].addr[2] = 69;
	Tuner->CH_Ctrl[12].bit[2] = 4;
	Tuner->CH_Ctrl[12].val[2] = 0;

	Tuner->CH_Ctrl[13].Ctrl_Num = RFSYN_VCO_BIAS ;
	Tuner->CH_Ctrl[13].size = 6 ;
	Tuner->CH_Ctrl[13].addr[0] = 110;
	Tuner->CH_Ctrl[13].bit[0] = 2;
	Tuner->CH_Ctrl[13].val[0] = 0;
	Tuner->CH_Ctrl[13].addr[1] = 110;
	Tuner->CH_Ctrl[13].bit[1] = 3;
	Tuner->CH_Ctrl[13].val[1] = 0;
	Tuner->CH_Ctrl[13].addr[2] = 110;
	Tuner->CH_Ctrl[13].bit[2] = 4;
	Tuner->CH_Ctrl[13].val[2] = 0;
	Tuner->CH_Ctrl[13].addr[3] = 110;
	Tuner->CH_Ctrl[13].bit[3] = 5;
	Tuner->CH_Ctrl[13].val[3] = 0;
	Tuner->CH_Ctrl[13].addr[4] = 110;
	Tuner->CH_Ctrl[13].bit[4] = 6;
	Tuner->CH_Ctrl[13].val[4] = 0;
	Tuner->CH_Ctrl[13].addr[5] = 110;
	Tuner->CH_Ctrl[13].bit[5] = 7;
	Tuner->CH_Ctrl[13].val[5] = 1;

	Tuner->CH_Ctrl[14].Ctrl_Num = CHCAL_INT_MOD_RF ;
	Tuner->CH_Ctrl[14].size = 7 ;
	Tuner->CH_Ctrl[14].addr[0] = 14;
	Tuner->CH_Ctrl[14].bit[0] = 0;
	Tuner->CH_Ctrl[14].val[0] = 0;
	Tuner->CH_Ctrl[14].addr[1] = 14;
	Tuner->CH_Ctrl[14].bit[1] = 1;
	Tuner->CH_Ctrl[14].val[1] = 0;
	Tuner->CH_Ctrl[14].addr[2] = 14;
	Tuner->CH_Ctrl[14].bit[2] = 2;
	Tuner->CH_Ctrl[14].val[2] = 0;
	Tuner->CH_Ctrl[14].addr[3] = 14;
	Tuner->CH_Ctrl[14].bit[3] = 3;
	Tuner->CH_Ctrl[14].val[3] = 0;
	Tuner->CH_Ctrl[14].addr[4] = 14;
	Tuner->CH_Ctrl[14].bit[4] = 4;
	Tuner->CH_Ctrl[14].val[4] = 0;
	Tuner->CH_Ctrl[14].addr[5] = 14;
	Tuner->CH_Ctrl[14].bit[5] = 5;
	Tuner->CH_Ctrl[14].val[5] = 0;
	Tuner->CH_Ctrl[14].addr[6] = 14;
	Tuner->CH_Ctrl[14].bit[6] = 6;
	Tuner->CH_Ctrl[14].val[6] = 0;

	Tuner->CH_Ctrl[15].Ctrl_Num = CHCAL_FRAC_MOD_RF ;
	Tuner->CH_Ctrl[15].size = 18 ;
	Tuner->CH_Ctrl[15].addr[0] = 17;
	Tuner->CH_Ctrl[15].bit[0] = 6;
	Tuner->CH_Ctrl[15].val[0] = 0;
	Tuner->CH_Ctrl[15].addr[1] = 17;
	Tuner->CH_Ctrl[15].bit[1] = 7;
	Tuner->CH_Ctrl[15].val[1] = 0;
	Tuner->CH_Ctrl[15].addr[2] = 16;
	Tuner->CH_Ctrl[15].bit[2] = 0;
	Tuner->CH_Ctrl[15].val[2] = 0;
	Tuner->CH_Ctrl[15].addr[3] = 16;
	Tuner->CH_Ctrl[15].bit[3] = 1;
	Tuner->CH_Ctrl[15].val[3] = 0;
	Tuner->CH_Ctrl[15].addr[4] = 16;
	Tuner->CH_Ctrl[15].bit[4] = 2;
	Tuner->CH_Ctrl[15].val[4] = 0;
	Tuner->CH_Ctrl[15].addr[5] = 16;
	Tuner->CH_Ctrl[15].bit[5] = 3;
	Tuner->CH_Ctrl[15].val[5] = 0;
	Tuner->CH_Ctrl[15].addr[6] = 16;
	Tuner->CH_Ctrl[15].bit[6] = 4;
	Tuner->CH_Ctrl[15].val[6] = 0;
	Tuner->CH_Ctrl[15].addr[7] = 16;
	Tuner->CH_Ctrl[15].bit[7] = 5;
	Tuner->CH_Ctrl[15].val[7] = 0;
	Tuner->CH_Ctrl[15].addr[8] = 16;
	Tuner->CH_Ctrl[15].bit[8] = 6;
	Tuner->CH_Ctrl[15].val[8] = 0;
	Tuner->CH_Ctrl[15].addr[9] = 16;
	Tuner->CH_Ctrl[15].bit[9] = 7;
	Tuner->CH_Ctrl[15].val[9] = 0;
	Tuner->CH_Ctrl[15].addr[10] = 15;
	Tuner->CH_Ctrl[15].bit[10] = 0;
	Tuner->CH_Ctrl[15].val[10] = 0;
	Tuner->CH_Ctrl[15].addr[11] = 15;
	Tuner->CH_Ctrl[15].bit[11] = 1;
	Tuner->CH_Ctrl[15].val[11] = 0;
	Tuner->CH_Ctrl[15].addr[12] = 15;
	Tuner->CH_Ctrl[15].bit[12] = 2;
	Tuner->CH_Ctrl[15].val[12] = 0;
	Tuner->CH_Ctrl[15].addr[13] = 15;
	Tuner->CH_Ctrl[15].bit[13] = 3;
	Tuner->CH_Ctrl[15].val[13] = 0;
	Tuner->CH_Ctrl[15].addr[14] = 15;
	Tuner->CH_Ctrl[15].bit[14] = 4;
	Tuner->CH_Ctrl[15].val[14] = 0;
	Tuner->CH_Ctrl[15].addr[15] = 15;
	Tuner->CH_Ctrl[15].bit[15] = 5;
	Tuner->CH_Ctrl[15].val[15] = 0;
	Tuner->CH_Ctrl[15].addr[16] = 15;
	Tuner->CH_Ctrl[15].bit[16] = 6;
	Tuner->CH_Ctrl[15].val[16] = 1;
	Tuner->CH_Ctrl[15].addr[17] = 15;
	Tuner->CH_Ctrl[15].bit[17] = 7;
	Tuner->CH_Ctrl[15].val[17] = 1;

	Tuner->CH_Ctrl[16].Ctrl_Num = RFSYN_LPF_R ;
	Tuner->CH_Ctrl[16].size = 5 ;
	Tuner->CH_Ctrl[16].addr[0] = 112;
	Tuner->CH_Ctrl[16].bit[0] = 0;
	Tuner->CH_Ctrl[16].val[0] = 0;
	Tuner->CH_Ctrl[16].addr[1] = 112;
	Tuner->CH_Ctrl[16].bit[1] = 1;
	Tuner->CH_Ctrl[16].val[1] = 0;
	Tuner->CH_Ctrl[16].addr[2] = 112;
	Tuner->CH_Ctrl[16].bit[2] = 2;
	Tuner->CH_Ctrl[16].val[2] = 0;
	Tuner->CH_Ctrl[16].addr[3] = 112;
	Tuner->CH_Ctrl[16].bit[3] = 3;
	Tuner->CH_Ctrl[16].val[3] = 0;
	Tuner->CH_Ctrl[16].addr[4] = 112;
	Tuner->CH_Ctrl[16].bit[4] = 4;
	Tuner->CH_Ctrl[16].val[4] = 1;

	Tuner->CH_Ctrl[17].Ctrl_Num = CHCAL_EN_INT_RF ;
	Tuner->CH_Ctrl[17].size = 1 ;
	Tuner->CH_Ctrl[17].addr[0] = 14;
	Tuner->CH_Ctrl[17].bit[0] = 7;
	Tuner->CH_Ctrl[17].val[0] = 0;

	Tuner->CH_Ctrl[18].Ctrl_Num = TG_LO_DIVVAL ;
	Tuner->CH_Ctrl[18].size = 4 ;
	Tuner->CH_Ctrl[18].addr[0] = 107;
	Tuner->CH_Ctrl[18].bit[0] = 3;
	Tuner->CH_Ctrl[18].val[0] = 0;
	Tuner->CH_Ctrl[18].addr[1] = 107;
	Tuner->CH_Ctrl[18].bit[1] = 4;
	Tuner->CH_Ctrl[18].val[1] = 0;
	Tuner->CH_Ctrl[18].addr[2] = 107;
	Tuner->CH_Ctrl[18].bit[2] = 5;
	Tuner->CH_Ctrl[18].val[2] = 0;
	Tuner->CH_Ctrl[18].addr[3] = 107;
	Tuner->CH_Ctrl[18].bit[3] = 6;
	Tuner->CH_Ctrl[18].val[3] = 0;

	Tuner->CH_Ctrl[19].Ctrl_Num = TG_LO_SELVAL ;
	Tuner->CH_Ctrl[19].size = 3 ;
	Tuner->CH_Ctrl[19].addr[0] = 107;
	Tuner->CH_Ctrl[19].bit[0] = 7;
	Tuner->CH_Ctrl[19].val[0] = 1;
	Tuner->CH_Ctrl[19].addr[1] = 106;
	Tuner->CH_Ctrl[19].bit[1] = 0;
	Tuner->CH_Ctrl[19].val[1] = 1;
	Tuner->CH_Ctrl[19].addr[2] = 106;
	Tuner->CH_Ctrl[19].bit[2] = 1;
	Tuner->CH_Ctrl[19].val[2] = 1;

	Tuner->CH_Ctrl[20].Ctrl_Num = TG_DIV_VAL ;
	Tuner->CH_Ctrl[20].size = 11 ;
	Tuner->CH_Ctrl[20].addr[0] = 109;
	Tuner->CH_Ctrl[20].bit[0] = 2;
	Tuner->CH_Ctrl[20].val[0] = 0;
	Tuner->CH_Ctrl[20].addr[1] = 109;
	Tuner->CH_Ctrl[20].bit[1] = 3;
	Tuner->CH_Ctrl[20].val[1] = 0;
	Tuner->CH_Ctrl[20].addr[2] = 109;
	Tuner->CH_Ctrl[20].bit[2] = 4;
	Tuner->CH_Ctrl[20].val[2] = 0;
	Tuner->CH_Ctrl[20].addr[3] = 109;
	Tuner->CH_Ctrl[20].bit[3] = 5;
	Tuner->CH_Ctrl[20].val[3] = 0;
	Tuner->CH_Ctrl[20].addr[4] = 109;
	Tuner->CH_Ctrl[20].bit[4] = 6;
	Tuner->CH_Ctrl[20].val[4] = 0;
	Tuner->CH_Ctrl[20].addr[5] = 109;
	Tuner->CH_Ctrl[20].bit[5] = 7;
	Tuner->CH_Ctrl[20].val[5] = 0;
	Tuner->CH_Ctrl[20].addr[6] = 108;
	Tuner->CH_Ctrl[20].bit[6] = 0;
	Tuner->CH_Ctrl[20].val[6] = 0;
	Tuner->CH_Ctrl[20].addr[7] = 108;
	Tuner->CH_Ctrl[20].bit[7] = 1;
	Tuner->CH_Ctrl[20].val[7] = 0;
	Tuner->CH_Ctrl[20].addr[8] = 108;
	Tuner->CH_Ctrl[20].bit[8] = 2;
	Tuner->CH_Ctrl[20].val[8] = 1;
	Tuner->CH_Ctrl[20].addr[9] = 108;
	Tuner->CH_Ctrl[20].bit[9] = 3;
	Tuner->CH_Ctrl[20].val[9] = 1;
	Tuner->CH_Ctrl[20].addr[10] = 108;
	Tuner->CH_Ctrl[20].bit[10] = 4;
	Tuner->CH_Ctrl[20].val[10] = 1;

	Tuner->CH_Ctrl[21].Ctrl_Num = TG_VCO_BIAS ;
	Tuner->CH_Ctrl[21].size = 6 ;
	Tuner->CH_Ctrl[21].addr[0] = 106;
	Tuner->CH_Ctrl[21].bit[0] = 2;
	Tuner->CH_Ctrl[21].val[0] = 0;
	Tuner->CH_Ctrl[21].addr[1] = 106;
	Tuner->CH_Ctrl[21].bit[1] = 3;
	Tuner->CH_Ctrl[21].val[1] = 0;
	Tuner->CH_Ctrl[21].addr[2] = 106;
	Tuner->CH_Ctrl[21].bit[2] = 4;
	Tuner->CH_Ctrl[21].val[2] = 0;
	Tuner->CH_Ctrl[21].addr[3] = 106;
	Tuner->CH_Ctrl[21].bit[3] = 5;
	Tuner->CH_Ctrl[21].val[3] = 0;
	Tuner->CH_Ctrl[21].addr[4] = 106;
	Tuner->CH_Ctrl[21].bit[4] = 6;
	Tuner->CH_Ctrl[21].val[4] = 0;
	Tuner->CH_Ctrl[21].addr[5] = 106;
	Tuner->CH_Ctrl[21].bit[5] = 7;
	Tuner->CH_Ctrl[21].val[5] = 1;

	Tuner->CH_Ctrl[22].Ctrl_Num = SEQ_EXTPOWERUP ;
	Tuner->CH_Ctrl[22].size = 1 ;
	Tuner->CH_Ctrl[22].addr[0] = 138;
	Tuner->CH_Ctrl[22].bit[0] = 4;
	Tuner->CH_Ctrl[22].val[0] = 1;

	Tuner->CH_Ctrl[23].Ctrl_Num = OVERRIDE_2 ;
	Tuner->CH_Ctrl[23].size = 1 ;
	Tuner->CH_Ctrl[23].addr[0] = 17;
	Tuner->CH_Ctrl[23].bit[0] = 5;
	Tuner->CH_Ctrl[23].val[0] = 0;

	Tuner->CH_Ctrl[24].Ctrl_Num = OVERRIDE_3 ;
	Tuner->CH_Ctrl[24].size = 1 ;
	Tuner->CH_Ctrl[24].addr[0] = 111;
	Tuner->CH_Ctrl[24].bit[0] = 3;
	Tuner->CH_Ctrl[24].val[0] = 0;

	Tuner->CH_Ctrl[25].Ctrl_Num = OVERRIDE_4 ;
	Tuner->CH_Ctrl[25].size = 1 ;
	Tuner->CH_Ctrl[25].addr[0] = 112;
	Tuner->CH_Ctrl[25].bit[0] = 7;
	Tuner->CH_Ctrl[25].val[0] = 0;

	Tuner->CH_Ctrl[26].Ctrl_Num = SEQ_FSM_PULSE ;
	Tuner->CH_Ctrl[26].size = 1 ;
	Tuner->CH_Ctrl[26].addr[0] = 136;
	Tuner->CH_Ctrl[26].bit[0] = 7;
	Tuner->CH_Ctrl[26].val[0] = 0;

	Tuner->CH_Ctrl[27].Ctrl_Num = GPIO_4B ;
	Tuner->CH_Ctrl[27].size = 1 ;
	Tuner->CH_Ctrl[27].addr[0] = 149;
	Tuner->CH_Ctrl[27].bit[0] = 7;
	Tuner->CH_Ctrl[27].val[0] = 0;

	Tuner->CH_Ctrl[28].Ctrl_Num = GPIO_3B ;
	Tuner->CH_Ctrl[28].size = 1 ;
	Tuner->CH_Ctrl[28].addr[0] = 149;
	Tuner->CH_Ctrl[28].bit[0] = 6;
	Tuner->CH_Ctrl[28].val[0] = 0;

	Tuner->CH_Ctrl[29].Ctrl_Num = GPIO_4 ;
	Tuner->CH_Ctrl[29].size = 1 ;
	Tuner->CH_Ctrl[29].addr[0] = 149;
	Tuner->CH_Ctrl[29].bit[0] = 5;
	Tuner->CH_Ctrl[29].val[0] = 1;

	Tuner->CH_Ctrl[30].Ctrl_Num = GPIO_3 ;
	Tuner->CH_Ctrl[30].size = 1 ;
	Tuner->CH_Ctrl[30].addr[0] = 149;
	Tuner->CH_Ctrl[30].bit[0] = 4;
	Tuner->CH_Ctrl[30].val[0] = 1;

	Tuner->CH_Ctrl[31].Ctrl_Num = GPIO_1B ;
	Tuner->CH_Ctrl[31].size = 1 ;
	Tuner->CH_Ctrl[31].addr[0] = 149;
	Tuner->CH_Ctrl[31].bit[0] = 3;
	Tuner->CH_Ctrl[31].val[0] = 0;

	Tuner->CH_Ctrl[32].Ctrl_Num = DAC_A_ENABLE ;
	Tuner->CH_Ctrl[32].size = 1 ;
	Tuner->CH_Ctrl[32].addr[0] = 93;
	Tuner->CH_Ctrl[32].bit[0] = 1;
	Tuner->CH_Ctrl[32].val[0] = 0;

	Tuner->CH_Ctrl[33].Ctrl_Num = DAC_B_ENABLE ;
	Tuner->CH_Ctrl[33].size = 1 ;
	Tuner->CH_Ctrl[33].addr[0] = 93;
	Tuner->CH_Ctrl[33].bit[0] = 0;
	Tuner->CH_Ctrl[33].val[0] = 0;

	Tuner->CH_Ctrl[34].Ctrl_Num = DAC_DIN_A ;
	Tuner->CH_Ctrl[34].size = 6 ;
	Tuner->CH_Ctrl[34].addr[0] = 92;
	Tuner->CH_Ctrl[34].bit[0] = 2;
	Tuner->CH_Ctrl[34].val[0] = 0;
	Tuner->CH_Ctrl[34].addr[1] = 92;
	Tuner->CH_Ctrl[34].bit[1] = 3;
	Tuner->CH_Ctrl[34].val[1] = 0;
	Tuner->CH_Ctrl[34].addr[2] = 92;
	Tuner->CH_Ctrl[34].bit[2] = 4;
	Tuner->CH_Ctrl[34].val[2] = 0;
	Tuner->CH_Ctrl[34].addr[3] = 92;
	Tuner->CH_Ctrl[34].bit[3] = 5;
	Tuner->CH_Ctrl[34].val[3] = 0;
	Tuner->CH_Ctrl[34].addr[4] = 92;
	Tuner->CH_Ctrl[34].bit[4] = 6;
	Tuner->CH_Ctrl[34].val[4] = 0;
	Tuner->CH_Ctrl[34].addr[5] = 92;
	Tuner->CH_Ctrl[34].bit[5] = 7;
	Tuner->CH_Ctrl[34].val[5] = 0;

	Tuner->CH_Ctrl[35].Ctrl_Num = DAC_DIN_B ;
	Tuner->CH_Ctrl[35].size = 6 ;
	Tuner->CH_Ctrl[35].addr[0] = 93;
	Tuner->CH_Ctrl[35].bit[0] = 2;
	Tuner->CH_Ctrl[35].val[0] = 0;
	Tuner->CH_Ctrl[35].addr[1] = 93;
	Tuner->CH_Ctrl[35].bit[1] = 3;
	Tuner->CH_Ctrl[35].val[1] = 0;
	Tuner->CH_Ctrl[35].addr[2] = 93;
	Tuner->CH_Ctrl[35].bit[2] = 4;
	Tuner->CH_Ctrl[35].val[2] = 0;
	Tuner->CH_Ctrl[35].addr[3] = 93;
	Tuner->CH_Ctrl[35].bit[3] = 5;
	Tuner->CH_Ctrl[35].val[3] = 0;
	Tuner->CH_Ctrl[35].addr[4] = 93;
	Tuner->CH_Ctrl[35].bit[4] = 6;
	Tuner->CH_Ctrl[35].val[4] = 0;
	Tuner->CH_Ctrl[35].addr[5] = 93;
	Tuner->CH_Ctrl[35].bit[5] = 7;
	Tuner->CH_Ctrl[35].val[5] = 0;

#ifdef _MXL_PRODUCTION
	Tuner->CH_Ctrl[36].Ctrl_Num = RFSYN_EN_DIV ;
	Tuner->CH_Ctrl[36].size = 1 ;
	Tuner->CH_Ctrl[36].addr[0] = 109;
	Tuner->CH_Ctrl[36].bit[0] = 1;
	Tuner->CH_Ctrl[36].val[0] = 1;

	Tuner->CH_Ctrl[37].Ctrl_Num = RFSYN_DIVM ;
	Tuner->CH_Ctrl[37].size = 2 ;
	Tuner->CH_Ctrl[37].addr[0] = 112;
	Tuner->CH_Ctrl[37].bit[0] = 5;
	Tuner->CH_Ctrl[37].val[0] = 0;
	Tuner->CH_Ctrl[37].addr[1] = 112;
	Tuner->CH_Ctrl[37].bit[1] = 6;
	Tuner->CH_Ctrl[37].val[1] = 0;

	Tuner->CH_Ctrl[38].Ctrl_Num = DN_BYPASS_AGC_I2C ;
	Tuner->CH_Ctrl[38].size = 1 ;
	Tuner->CH_Ctrl[38].addr[0] = 65;
	Tuner->CH_Ctrl[38].bit[0] = 1;
	Tuner->CH_Ctrl[38].val[0] = 0;
#endif

	return 0 ;
}
