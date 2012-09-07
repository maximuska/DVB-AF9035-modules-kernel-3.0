//                                                   
// Automatically generated C header file for         
// control of the XC3028L via the i2c interface.      
//                                                   
// Filename : xc3028_control.h                                     
// Generated : 7/3/2007 2:48:24 PM                                    
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
                                                     
#ifndef __XC3028_CONTROL_H                                       
#define __XC3028_CONTROL_H                                       
                                                     
/* *********************************************************************** */
/* Defines                                                                 */
/* *********************************************************************** */

#define XC3028_MAX_I2C_WRITE_LENGTH                     52

#define XC3028_RESULT_SUCCESS                           0
#define XC3028_RESULT_RESET_FAILURE                     1
#define XC3028_RESULT_I2C_WRITE_FAILURE                 2
#define XC3028_RESULT_I2C_READ_FAILURE                  3
#define XC3028_RESULT_WAIT_FAILURE                      4
#define XC3028_RESULT_OUT_OF_RANGE                      5
#define XC3028_RESULT_INVALID_CHANNEL_IDENTIFIER        6
#define XC3028_RESULT_NO_CHANNELMAP_SPECIFIED           7

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
    unsigned char *sequence;
} XC3028_I2C_SEQUENCE; 

typedef unsigned char XC3028_SCODE_TABLE[16][12];

typedef struct {
    char              identifier[4];
    unsigned int      frequency;
    unsigned char     dcode;
} XC3028_CHANNEL;

typedef struct {
    int               nb_channels;
    XC3028_CHANNEL    *channels;
} XC3028_CHANNEL_MAP;

typedef struct {
    XC3028_I2C_SEQUENCE    *base_firmware_ptr;
    XC3028_I2C_SEQUENCE    *std_firmware_ptr;
    XC3028_SCODE_TABLE     *scode_table_ptr;
} XC3028_TV_MODE;

typedef struct _XC3028_Current_Modes
{
	XC3028_TV_MODE      XC3028_current_tv_mode;
	XC3028_CHANNEL_MAP *XC3028_current_channel_map_ptr;
	XC3028_CHANNEL      XC3028_current_channel;
}XC3028_Current_Modes;

/* *********************************************************************** */
/* Dummy functions to be implemented by customer                           */
/* *********************************************************************** */

// Sends data bytes to xc3028 via I2C starting with
// bytes_to_send[0] and ending with bytes_to_send[nb_bytes_to_send-1]
// Returns one of the XCEIVE_XC3028_RESULT result codes listed above
int i2c_send_to_xc3028(unsigned char *bytes_to_send, int nb_bytes_to_send);
// Reads data bytes from xc3028 via I2C starting with
// bytes_received[0] and ending with bytes_received[nb_bytes_to_receive-1]
// Returns one of the XCEIVE_XC3028_RESULT result codes listed above
int i2c_receive_from_xc3028(unsigned char *bytes_received, int nb_bytes_to_receive);
// Does hardware reset
// Returns one of the XCEIVE_XC3028_RESULT result codes listed above
int reset_xc3028();
// Waits for wait_ms milliseconds
// Returns one of the XCEIVE_XC3028_RESULT result codes listed above
int wait_xc3028(int wait_ms);

/* *********************************************************************** */
/* Functions implemented in xc3028_init.c file                             */
/* All return one of the XCEIVE_XC3028_RESULT result codes as listed above */
/* *********************************************************************** */

// Initialize device according to supplied tv mode.
// Supplied channel map will be used for future calls to xc3028_set_channel.
int xc3028_initialize(XC3028_TV_MODE* new_tv_mode_ptr, XC3028_CHANNEL_MAP* new_channel_map_ptr);

// Switch to new RF channel.
// Set channel.frequency=0 to enable lookup of frequency+dcode using channel.identifier
// Set channel.dcode to 0xFF to enable dcode lookup from channel map, otherwise
// provided value is used instead.
int xc3028_set_channel(XC3028_CHANNEL new_channel);

int xc3028_set_frequency(long frequency_in_hz);

// Power-down device.
// To restart, call xc3028_initialize().
int xc3028_shutdown();

// Get current frequency error.
int xc3028_get_frequency_error(long *frequency_error_hz);

// Get lock status.
int xc3028_get_lock_status(unsigned short int *lock_status);

// Get device version information.
int xc3028_get_version( unsigned char* hw_majorversion,unsigned char* hw_minorversion,
                        unsigned char* fw_majorversion, unsigned char* fw_minorversion);

// Get device product ID.
int xc3028_get_product_id(unsigned short int *product_id);

// Get horizontal sync frequency.
int xc3028_get_hsync_freq(long *hsync_freq_hz);

// Get number of lines per frame.
int xc3028_get_frame_lines(unsigned short int *frame_lines);

// Get quality estimate.
int xc3028_get_quality(unsigned short int *quality);

// Do full scan for channels
int xc3028_full_scan(unsigned int freq_min, unsigned int freq_max, int freq_list_size, unsigned int *freq_list, int *nb_freq_found);

#endif


