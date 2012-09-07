#include "standard.h"

#define FREQ_XTAL	16384	//16.384MHz
#define	BORDER_FREQ	2600000	//2.6GHz : The border frequency which determines whether Low VCO or High VCO is used
#define USE_EXT_CLK	0	//0 : Use internal XTAL Oscillator / 1 : Use External Clock input
#define OFS_RSSI 57

extern Demodulator* FCI_FC2580_demodulator;
extern Byte FCI_FC2580_chip;

typedef enum {
	UHF_BAND,
	L_BAND,
	VHF_BAND,
	NO_BAND
} fc2580_band_type;

/*==============================================================================
		i2c command write							EXTERNAL FUNCTION

  This function is a generic function which write a byte into fc2580's
 specific address.

  <input parameter>

  slave_id
	i2c id of slave chip
	type : byte
	
  addr
	memory address of slave chip
	type : byte

  data
	target data
	type : byte

==============================================================================*/
extern void i2c_write( unsigned char slave_id, unsigned char addr, unsigned char data );

/*==============================================================================
		i2c command write							EXTERNAL FUNCTION

  This function is a generic function which gets called to read data from
 slave chip's target memory address.

  <input parameter>

  slave_id
	i2c id of slave chip
	type : byte
	
  addr
	memory address of slave chip
	type : byte

  <return value>
  data
	a byte of data read out of target address 'addr' of slave chip
	type : byte

==============================================================================*/
extern unsigned char i2c_read( unsigned char slave_id, unsigned char addr );

/*==============================================================================
		milisecond delay function					EXTERNAL FUNCTION

  This function is a generic function which write a byte into fc2580's
 specific address.

  <input parameter>

  a
	length of wanted delay in milisecond unit

==============================================================================*/
extern void wait_msec (unsigned long msec);



/*==============================================================================
       fc2580 i2c command write

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
void fc2580_i2c_write( unsigned char addr, unsigned char data );

/*==============================================================================
       fc2580 i2c data read

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
unsigned char fc2580_i2c_read( unsigned char addr );

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
void fc2580_set_init( int ifagc_mode );

/*==============================================================================
       fc2580 frequency setting

  This function is a generic function which gets called to change LO Frequency

  of fc2580 in DVB-H mode or L-Band TDMB mode

  <input parameter>

  f_lo
	Value of target LO Frequency in 'kHz' unit
	ex) 2.6GHz = 2600000

==============================================================================*/
void fc2580_set_freq( unsigned int f_lo );


/*==============================================================================
       fc2580 filter BW setting

  This function is a generic function which gets called to change Bandwidth

  frequency of fc2580's channel selection filter

  <input parameter>

  filter_bw
    1 : 1.53MHz(TDMB)
	5 : 5MHz
	6 : 6MHz
	7 : 7MHz
	8 : 7.8MHz
	9 : 8MHz

==============================================================================*/
void fc2580_set_filter(unsigned char filter_bw);

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
int fc2580_get_rssi(void);

