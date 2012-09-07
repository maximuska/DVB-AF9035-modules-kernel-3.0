//
// C header file for control of the XC4000 via the i2c interface.
//
// Filename : xc4000_control.h
// Generated : 1/22/2007 4:41:24 PM
//
// (c) 2007, Xceive Corporation
//
//
// Disclaimer:
//
// Xceive assumes no responsibility for any consequences arising from the use
// of this computer code, nor from any infringement of patents or the rights of
// third parties that may result from its use. No license is granted by
// implication or otherwise under any patent or other rights of Xceive. The
// customer is responsible for assuring that proper design and operating
// safeguards are observed to minimize inherent and procedural hazards. Xceive
// assumes no responsibility for applications assistance or customer product
// design.
// The present computer code is not authorized for use in medical, life-support
// equipment, or any other application involving a potential risk of severe
// property or environmental damage, personal injury, or death without prior
// express written approval of Xceive.  Any such use is understood to be
// entirely at the user's risk.
//
//

#ifndef __XC4000_CONTROL_H
#define __XC4000_CONTROL_H

/* *********************************************************************** */
/* Defines                                                                 */
/* *********************************************************************** */

#define XC_MAX_I2C_WRITE_LENGTH                     52

#define XC_RESULT_SUCCESS                           0
#define XC_RESULT_RESET_FAILURE                     1
#define XC_RESULT_I2C_WRITE_FAILURE                 2
#define XC_RESULT_I2C_READ_FAILURE                  3
#define XC_RESULT_OUT_OF_RANGE                      5

/* *********************************************************************** */
/* Type Declarations                                                       */
/* *********************************************************************** */

/*
   This represents an I2C firmware file encoded as a string of unsigned char.
   Format is as follows:

   char[0  ]=len0_MSB  -> len = len_MSB * 256 + len_LSB
   char[1  ]=len0_LSB  -> length of first write transaction
   char[2  ]=data0 -> first byte to be sent
   char[3  ]=data1
   char[4  ]=data2
   char[   ]=...
   char[M  ]=dataN  -> last byte to be sent
   char[M+1]=len1_MSB  -> len = len_MSB * 256 + len_LSB
   char[M+2]=len1_LSB  -> length of second write transaction
   char[M+3]=data0
   char[M+4]=data1
   ...
   etc.

   The [len] value should be interpreted as follows:

   len= len_MSB _ len_LSB
   len=1111_1111_1111_1111   : End of I2C_SEQUENCE
   len=0000_0000_0000_0000   : Reset command: Do hardware reset
   len=0NNN_NNNN_NNNN_NNNN   : Normal transaction: number of bytes = {1:32767)
   len=1WWW_WWWW_WWWW_WWWW   : Wait command: wait for {1:32767} ms

   For the RESET and WAIT commands, the two following bytes will contain
   immediately the length of the following transaction.

*/
typedef struct {
  char *Name;
  unsigned char *ConfFile;
  unsigned short VideoMode;
  unsigned short AudioMode;
  double         SCode;
} XC_TV_STANDARD;

typedef unsigned char XC4000_SCODE_TABLE[16][13];

// Download firmware
int xc_load_i2c_sequence(unsigned char i2c_sequence[]);

// Perform calibration and initialize default parameter
int xc_initialize();

// Initialize device according to supplied tv mode.
int xc_SetTVStandard(unsigned short int VideoMode, unsigned short int AudioMode);

int xc_set_RF_frequency(long frequency_in_hz);

int xc_set_dcode( int dcode);

//int xc_set_IF_frequency(long frequency_in_hz);

// Power-down device.
int xc_shutdown();

// enter direct-setting-mode
int xc_enter_directsitting_mode();

// exit direct-setting-mode
int xc_exit_directsitting_mode();

// set RF signal source
int xc_rf_mode(int mode);


// Get ADC envelope value.
int xc_get_ADC_Envelope(unsigned short int *adc_envelope);

// Get current frequency error.
int xc_get_frequency_error(long *frequency_error_mhz);

// Get lock status.
int xc_get_lock_status(unsigned short int *lock_status);

// Get device version information.
int xc_get_version( unsigned char* hw_majorversion,unsigned char* hw_minorversion,
                        unsigned char* fw_majorversion, unsigned char* fw_minorversion);

// Get device product ID.
int xc_get_product_id(unsigned short int *product_id);

// Get horizontal sync frequency.
int xc_get_hsync_freq(int *hsync_freq_hz);

// Get number of lines per frame.
int xc_get_frame_lines(unsigned short int *frame_lines);

// Get quality estimate.
int xc_get_quality(unsigned short int *quality);

// Tune a channel
int xc_tune_channel(long chnl_freq); //for Linux

#endif


