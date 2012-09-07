#include "fc2580.h"

/*==============================================================================
    FILE NAME   : FC2580_driver_v1400.c
    
    VERSION     : 1.400
    
    UPDATE      : September 22. 2008

==============================================================================*/ 

/*==============================================================================
		milisecond delay function					EXTERNAL FUNCTION

  This function is a generic function which write a byte into fc2580's
 specific address.

  <input parameter>

  a
	length of wanted delay in milisecond unit

==============================================================================*/
void wait_msec (unsigned long msec)
{
	User_delay (FCI_FC2580_demodulator, msec);
}

static fc2580_band_type curr_band = NO_BAND;
static unsigned char data_0x02 = (USE_EXT_CLK<<5)|0x0E;

/*==============================================================================

           fc2580 i2c write

  This function is a generic function which write a byte into fc2580's
 specific address.

  <input parameter>

  addr
	fc2580's memory address
	type : byte

  data
	target data
	type : byte

==============================================================================*/
void fc2580_i2c_write( unsigned char addr, unsigned char data )
{
	Standard_writeTunerRegisters (FCI_FC2580_demodulator, FCI_FC2580_chip, addr, 1, &data);
}

/*==============================================================================

           fc2580 i2c read

  This function is a generic function which gets called to read data from
 fc2580's target memory address.

  <input parameter>

  addr
	fc2580's memory address
	type : byte


  <return value>
  data
	a byte of data read out of target address 'addr'
	type : byte

==============================================================================*/
unsigned char fc2580_i2c_read( unsigned char addr )
{
	Byte value;

	Standard_readTunerRegisters (FCI_FC2580_demodulator, FCI_FC2580_chip, addr, 1, &value);
	return (value);
}

/*==============================================================================
       fc2580 I2C Test

  This function is a generic function which tests I2C interface's availability

  by reading out it's I2C id data from reg. address '0x01'.

  <input parameter>

  None
  
  <return value>
  int
	1 : success - communication is avilable
	0 : fail - communication is unavailable
  

==============================================================================*/
int fc2580_i2c_test( void )
{
	return ( fc2580_i2c_read( 0x01 ) == 0x56 )? 0x01 : 0x00;
}


/*==============================================================================
       fc2580 initial setting

  This function is a generic function which gets called to initialize

  fc2580 in DVB-H mode or L-Band TDMB mode

  <input parameter>

  ifagc_mode
    type : integer
	1 : Internal AGC
	2 : Voltage Control Mode

==============================================================================*/
void fc2580_set_init( int ifagc_mode )
{
	fc2580_i2c_write(0x00, 0x00);	/*** Confidential ***/
	fc2580_i2c_write(0x12, 0x86);
	fc2580_i2c_write(0x14, 0x5C);
	fc2580_i2c_write(0x16, 0x3C);
	fc2580_i2c_write(0x1F, 0xD2);
	fc2580_i2c_write(0x09, 0xD7);
	fc2580_i2c_write(0x0B, 0xD5);
	fc2580_i2c_write(0x0C, 0x32);
	fc2580_i2c_write(0x0E, 0x43);
	fc2580_i2c_write(0x21, 0x0A);
	fc2580_i2c_write(0x22, 0x82);
	if( ifagc_mode == 1 )
	{
		fc2580_i2c_write(0x45, 0x10);	/** internal AGC */
		fc2580_i2c_write(0x4C, 0x00);	/** HOLD_AGC polarity */
	}
	else if( ifagc_mode == 2 )
	{
		fc2580_i2c_write(0x45, 0x20);	/** Voltage Control Mode */
		fc2580_i2c_write(0x4C, 0x02);	/** HOLD_AGC polarity */
	}
	else if( ifagc_mode == 3 )
	{
		fc2580_i2c_write(0x45, 0x30);	//Up/Down Control ( Digital AGC )
		fc2580_i2c_write(0x4C, 0x02);	//HOLD_AGC polarity
	}
	fc2580_i2c_write(0x3F, 0x88);
	fc2580_i2c_write(0x02, 0x0E);
	fc2580_i2c_write(0x58, 0x14);
	fc2580_set_filter(8);	/** BW = 7.8MHz */

}

/*==============================================================================
       fc2580 frequency setting

  This function is a generic function which gets called to change LO Frequency

  of fc2580 in DVB-H mode or L-Band TDMB mode

  <input parameter>

  f_lo
	Value of target LO Frequency in 'kHz' unit
	ex) 2.6GHz = 2600000

==============================================================================*/
void fc2580_set_freq( unsigned int f_lo )
{
	unsigned int f_diff, f_diff_shifted, n_val, k_val;
	unsigned int f_vco, r_val, f_comp;
	unsigned char pre_shift_bits = 4; /** number of preshift to prevent overflow in shifting f_diff to f_diff_shifted */
	unsigned char data_0x18;

	fc2580_band_type band = ( f_lo > 1000000 )? L_BAND : ( f_lo > 400000 )? UHF_BAND : VHF_BAND;

	f_vco = ( band == UHF_BAND )? f_lo * 4 : (( band == L_BAND )? f_lo * 2 : f_lo * 12);
	r_val = ( f_vco >= 2*76*FREQ_XTAL )? 1 : ( f_vco >= 76*FREQ_XTAL )? 2 : 4;
	f_comp = FREQ_XTAL/r_val;
	n_val =	( f_vco / 2 ) / f_comp;
	
	f_diff = f_vco - 2* f_comp * n_val;
	f_diff_shifted = f_diff << ( 20 - pre_shift_bits );
	k_val = f_diff_shifted / ( ( 2* f_comp ) >> pre_shift_bits );
	
	if( f_diff_shifted - k_val * ( ( 2* f_comp ) >> pre_shift_bits ) >= ( f_comp >> pre_shift_bits ) )
	k_val = k_val + 1;
	
	if( f_vco >= BORDER_FREQ )	/** Select VCO Band */
		data_0x02 = data_0x02 | 0x08;	/** 0x02[3] = 1; */
	else
		data_0x02 = data_0x02 & 0xF7;	/** 0x02[3] = 0; */
	
	//if( band != curr_band ) {
		switch(band)
		{
			case UHF_BAND:
				data_0x02 = (data_0x02 & 0x3F);

				fc2580_i2c_write(0x25, 0xF0);
				fc2580_i2c_write(0x27, 0x77);
				fc2580_i2c_write(0x28, 0x53);
				fc2580_i2c_write(0x29, 0x60);
				fc2580_i2c_write(0x30, 0x09);
				fc2580_i2c_write(0x50, 0x8C);
				fc2580_i2c_write(0x53, 0x50);

				if( f_lo < 538000 )
					fc2580_i2c_write(0x5F, 0x13);
				else					
					fc2580_i2c_write(0x5F, 0x15);

				if( f_lo < 538000 )
				{
					fc2580_i2c_write(0x61, 0x07);
					fc2580_i2c_write(0x62, 0x06);
					fc2580_i2c_write(0x67, 0x06);
					fc2580_i2c_write(0x68, 0x08);
					fc2580_i2c_write(0x69, 0x10);
					fc2580_i2c_write(0x6A, 0x12);
				}
				else if( f_lo < 794000 )
				{
					fc2580_i2c_write(0x61, 0x03);
					fc2580_i2c_write(0x62, 0x03);
					fc2580_i2c_write(0x67, 0x07);
					fc2580_i2c_write(0x68, 0x08);
					fc2580_i2c_write(0x69, 0x0C);
					fc2580_i2c_write(0x6A, 0x0E);
				}
				else
				{
					fc2580_i2c_write(0x61, 0x07);
					fc2580_i2c_write(0x62, 0x06);
					fc2580_i2c_write(0x67, 0x07);
					fc2580_i2c_write(0x68, 0x09);
					fc2580_i2c_write(0x69, 0x10);
					fc2580_i2c_write(0x6A, 0x12);
				}

				fc2580_i2c_write(0x63, 0x15);

				fc2580_i2c_write(0x6B, 0x0F);
				fc2580_i2c_write(0x6C, 0x11);
				fc2580_i2c_write(0x6D, 0x78);
				fc2580_i2c_write(0x6E, 0x32);
				fc2580_i2c_write(0x6F, 0x14);
				/*fc2580_set_filter(8);*/	/** BW = 7.8MHz */
				break;
			case VHF_BAND:
				data_0x02 = (data_0x02 & 0x3F) | 0x80;
				fc2580_i2c_write(0x27, 0x77);
				fc2580_i2c_write(0x28, 0x33);
				fc2580_i2c_write(0x29, 0x40);
				fc2580_i2c_write(0x50, 0x40);
				fc2580_i2c_write(0x53, 0x18);
				fc2580_i2c_write(0x5F, 0x0F);
				fc2580_i2c_write(0x61, 0x07);
				fc2580_i2c_write(0x62, 0x00);
				fc2580_i2c_write(0x63, 0x15);
				fc2580_i2c_write(0x67, 0x03);
				fc2580_i2c_write(0x68, 0x05);
				fc2580_i2c_write(0x69, 0x10);
				fc2580_i2c_write(0x6A, 0x12);
				fc2580_i2c_write(0x6B, 0x0F);
				fc2580_i2c_write(0x6C, 0x11);
				fc2580_i2c_write(0x6D, 0x78);
				fc2580_i2c_write(0x6E, 0x32);
				fc2580_i2c_write(0x6F, 0x54);
				/*fc2580_set_filter(7);*/	/** BW = 6.8MHz */
				break;
			case L_BAND:
				data_0x02 = (data_0x02 & 0x3F) | 0x40;
				fc2580_i2c_write(0x2B, 0x70);
				fc2580_i2c_write(0x2C, 0x37);
				fc2580_i2c_write(0x2D, 0xE7);
				fc2580_i2c_write(0x44, 0x20);
				fc2580_i2c_write(0x50, 0x40);
				fc2580_i2c_write(0x53, 0x18);
				fc2580_i2c_write(0x5F, 0x0F);
				fc2580_i2c_write(0x61, 0x0F);
				fc2580_i2c_write(0x62, 0x00);
				fc2580_i2c_write(0x63, 0x13);
				fc2580_i2c_write(0x67, 0x00);
				fc2580_i2c_write(0x68, 0x02);
				fc2580_i2c_write(0x69, 0x0F);
				fc2580_i2c_write(0x6A, 0x11);
				fc2580_i2c_write(0x6B, 0x0F);
				fc2580_i2c_write(0x6C, 0x11);
				fc2580_i2c_write(0x6D, 0xA0);
				fc2580_i2c_write(0x6E, 0x50);
				fc2580_i2c_write(0x6F, 0x14);
				/*fc2580_set_filter(1);*/	/** BW = 1.53MHz */
				break;
			default:
				break;
		}
		curr_band = band;
	//}

	/** A command about AGC clock's pre-divide ratio */
	if( FREQ_XTAL >= 28000 )
		fc2580_i2c_write( 0x4B, 0x22 );

	/** Commands about VCO Band and PLL setting. */
	fc2580_i2c_write(0x02, data_0x02);
	data_0x18 = ( ( r_val == 1 )? 0x00 : ( ( r_val == 2 )? 0x10 : 0x20 ) ) + (unsigned char)(k_val >> 16);
	fc2580_i2c_write(0x18, data_0x18);						/** Load 'R' value and high part of 'K' values */
	fc2580_i2c_write(0x1A, (unsigned char)( k_val >> 8 ) );	/** Load middle part of 'K' value */
	fc2580_i2c_write(0x1B, (unsigned char)( k_val ) );		/** Load lower part of 'K' value */
	fc2580_i2c_write(0x1C, (unsigned char)( n_val ) );		/** Load 'N' value */

	/** A command about UHF LNA Load Cap */
	if( band == UHF_BAND )
		fc2580_i2c_write(0x2D, ( f_lo <= (unsigned int)794000 )? 0x9F : 0x8F );	/** LNA_OUT_CAP */


}


/*==============================================================================
       fc2580 filter BW setting

  This function is a generic function which gets called to change Bandwidth

  frequency of fc2580's channel selection filter

  <input parameter>

  filter_bw
    1 : 1.53MHz(TDMB)
	5 : 5MHz
	6 : 6MHz
	7 : 6.8MHz
	8 : 7.8MHz
	9 : 8.0MHz

==============================================================================*/
void fc2580_set_filter(unsigned char filter_bw)
{
	unsigned char	cal_mon, i;

	if(filter_bw == 1)
	{
		fc2580_i2c_write(0x36, 0x1C);
		fc2580_i2c_write(0x37, (unsigned char) (((unsigned long) (4151 * FREQ_XTAL)) / 1000000));
		fc2580_i2c_write(0x39, 0x00);
		fc2580_i2c_write(0x2E, 0x09);
	}
	if(filter_bw == 5)
	{
		fc2580_i2c_write(0x36, 0x18);
		fc2580_i2c_write(0x37, (unsigned char) (((unsigned long) (5320 * FREQ_XTAL)) / 1000000));
		fc2580_i2c_write(0x39, 0x00);
		fc2580_i2c_write(0x2E, 0x09);
	}
	else if(filter_bw == 6)
	{
		fc2580_i2c_write(0x36, 0x18);
		fc2580_i2c_write(0x37, (unsigned char) (((unsigned long) (4400 * FREQ_XTAL)) / 1000000));
		fc2580_i2c_write(0x39, 0x00);
		fc2580_i2c_write(0x2E, 0x09);
	}
	else if(filter_bw == 7)
	{
		fc2580_i2c_write(0x36, 0x18);
		fc2580_i2c_write(0x37, (unsigned char) (((unsigned long) (3910 * FREQ_XTAL)) / 1000000));
		fc2580_i2c_write(0x39, 0x80);
		fc2580_i2c_write(0x2E, 0x09);
	}
	else if(filter_bw == 8)
	{
		fc2580_i2c_write(0x36, 0x18);
		fc2580_i2c_write(0x37, (unsigned char) (((unsigned long) (3300 * FREQ_XTAL)) / 1000000));
		fc2580_i2c_write(0x39, 0x80);
		fc2580_i2c_write(0x2E, 0x09);
	}
	else if(filter_bw == 9)
	{
		fc2580_i2c_write(0x36, 0x18);
		fc2580_i2c_write(0x37, (unsigned char) (((unsigned long) (2450 * FREQ_XTAL)) / 1000000));
		fc2580_i2c_write(0x39, 0x80);
		fc2580_i2c_write(0x2E, 0x09);
	}
	
	for(i=0; i<5; i++)
	{
		wait_msec(5); /** wait 5ms */
		cal_mon = fc2580_i2c_read(0x2F);
		if( (cal_mon & 0xC0) != 0xC0)
		{
			fc2580_i2c_write(0x2E, 0x01);
			fc2580_i2c_write(0x2E, 0x09);
		}
		else
			break;
	}

	fc2580_i2c_write(0x2E, 0x01);
}

/*==============================================================================
       fc2580 RSSI function

  This function is a generic function which returns fc2580's
  
  current RSSI value.

  <input parameter>
	none

  <return value>
  int
  	rssi : estimated input power.

==============================================================================*/
int fc2580_get_rssi(void) {
	
	int s_lna = fc2580_i2c_read( 0x71 );
	int s_rfvga = fc2580_i2c_read( 0x72 );
	int s_cfs = fc2580_i2c_read( 0x73 );
	int s_ifvga = fc2580_i2c_read( 0x74 );
	int ofs_lna, ofs_rfvga, ofs_csf, ofs_ifvga, rssi;

	ofs_lna = 
			(curr_band==UHF_BAND)?
				(s_lna==0)? 0 :
				(s_lna==1)? -6 :
				(s_lna==2)? -17 :
				(s_lna==3)? -22 : -30 :
			(curr_band==VHF_BAND)?
				(s_lna==0)? 0 :
				(s_lna==1)? -6 :
				(s_lna==2)? -19 :
				(s_lna==3)? -24 : -32 :
			(curr_band==L_BAND)?
				(s_lna==0)? 0 :
				(s_lna==1)? -6 :
				(s_lna==2)? -11 :
				(s_lna==3)? -16 : -34 :
			0; /** NO_BAND */
	ofs_rfvga = -s_rfvga+((s_rfvga>=11)? 1 : 0) + ((s_rfvga>=18)? 1 : 0);
	ofs_csf = -6*s_cfs;
	ofs_ifvga = s_ifvga/4;

	return rssi = ofs_lna+ofs_rfvga+ofs_csf+ofs_ifvga+OFS_RSSI;
				
}