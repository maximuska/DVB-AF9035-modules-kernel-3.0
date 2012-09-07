//                                                   
// Automatically generated C source file for         
// control of the XC3028 via the i2c interface.      
//                                                   
// Filename : xc3028_control.c                                     
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
// History:
//
// 8/4/2005 rpp : Changes for firmware v2.2
//      Changed 32-bit i2c register writes to have subaddress msb = 1:
//      1) Power-down (0x0008_0000 => 0x8008_0000)
//      2) S-Code sequence (0x2000_0000 => 0xA000_0000)
//      3) Set RF Channel (0x0002_0000 => 0x8002_0000)
//
//



//#include <math.h> //for Linux
#include "xc3028_control.h"
#include "xc3028_channelmaps.h"
#include "xc3028_scodes.h"
#include "xc3028_firmwares.h"


#define XCEIVE_XC3028_SUBADDR_FREQ_ERROR      0x0001
#define XCEIVE_XC3028_SUBADDR_LOCK            0x0002
#define XCEIVE_XC3028_SUBADDR_VERSION         0x0004
#define XCEIVE_XC3028_SUBADDR_PRODUCT_ID      0x0008
#define XCEIVE_XC3028_SUBADDR_HSYNC_FREQ      0x0010
#define XCEIVE_XC3028_SUBADDR_FRAME_LINES     0x0020
#define XCEIVE_XC3028_SUBADDR_QUALITY         0x0040
#define XCEIVE_XC3028_SUBADDR_ADC_ENVELOPE    0x0100


/* *************************************************************** */
/*        GLOBAL VARIABLES                                         */
/* *************************************************************** */

XC3028_TV_MODE      XC3028_current_tv_mode = {0,0,0};
XC3028_CHANNEL_MAP *XC3028_current_channel_map_ptr = 0;
XC3028_CHANNEL      XC3028_current_channel = {{' ',' ',' ',' '}, 0, 0};



/* *************************************************************** */
/* *************************************************************** */
/*                                                                 */
/*       FOLLOWING FUNCTIONS TO BE IMPLEMENTED BY CUSTOMER         */
/*                                                                 */
/* *************************************************************** */
/* *************************************************************** */


int xc3028_send_i2c_data(unsigned char *bytes_to_send, int nb_bytes_to_send);
int xc3028_read_i2c_data(unsigned char *bytes_received, int nb_bytes_to_receive);
int xc3028_reset();
int xc3028_wait(int wait_ms);






/* *************************************************************** */
/* *************************************************************** */
/*                                                                 */
/*              CODE PROVIDED BY XCEIVE                            */
/*                                                                 */
/* *************************************************************** */
/* *************************************************************** */



int xc3028_load_i2c_sequence(XC3028_I2C_SEQUENCE i2c_sequence)
{

    int i,nbytes_to_send,pos,result;
    unsigned int length, index;
    unsigned char buf[XC3028_MAX_I2C_WRITE_LENGTH];

    index=0;

    while ((i2c_sequence.sequence[index]!=0xFF) || (i2c_sequence.sequence[index+1]!=0xFF)) {

        length = i2c_sequence.sequence[index]*256 + i2c_sequence.sequence[index+1];

        if (length==0x0000) {
            //this is in fact a RESET command
            result = xc3028_reset();
            index+=2;
            if (result!=XC3028_RESULT_SUCCESS)
                return result;
        } else if (length & 0x8000) {
            //this is in fact a WAIT command
            result = xc3028_wait(length & 0x7FFF);
            index+=2;
            if (result!=XC3028_RESULT_SUCCESS)
                return result;
        } else {
            //send i2c data whilst ensuring individual transactions do
            //not exceed XC3028_MAX_I2C_WRITE_LENGTH bytes
            index+=2;
            buf[0] = i2c_sequence.sequence[index];
            pos = 1;
            while (pos < length) {

               if ( (length-pos) > XC3028_MAX_I2C_WRITE_LENGTH-1) {
                  nbytes_to_send = XC3028_MAX_I2C_WRITE_LENGTH;
               } else {
                  nbytes_to_send = (length-pos+1);
               }

               for (i=1;i<nbytes_to_send;i++) {
                   buf[i] = i2c_sequence.sequence[index+pos+i-1];
               }

               result = xc3028_send_i2c_data(buf, nbytes_to_send);

               if (result!=XC3028_RESULT_SUCCESS)
                   return result;

               pos += nbytes_to_send-1;
            }
            index+=length;
        }
    }


    return XC3028_RESULT_SUCCESS;
}


int xc3028_get_reg(unsigned short int subaddr, unsigned short int *data)
{
    unsigned char buf[2];
    int result;

    buf[0]=(subaddr>>8) & 0xFF;
    buf[1]=subaddr & 0xFF;
    result = xc3028_send_i2c_data(buf, 2);
    if (result!=XC3028_RESULT_SUCCESS)
       return result;

    result = xc3028_read_i2c_data(buf, 2);
    if (result!=XC3028_RESULT_SUCCESS)
       return result;

    (*data) = buf[0];
    (*data) = ((*data) << 8) + buf[1];

    return XC3028_RESULT_SUCCESS;
}


int xc3028_initialize(XC3028_TV_MODE* new_tv_mode_ptr, XC3028_CHANNEL_MAP* new_channel_map_ptr)
{

    int result;
    int base_firmware_changed = (new_tv_mode_ptr->base_firmware_ptr != XC3028_current_tv_mode.base_firmware_ptr);
    int std_firmware_changed = (new_tv_mode_ptr->std_firmware_ptr != XC3028_current_tv_mode.std_firmware_ptr);

    // if base firmware has changed, then do hardware reset and reload base
    // firmware file
    if (base_firmware_changed) {
       result = xc3028_reset();
       if (result!=XC3028_RESULT_SUCCESS)
           return result;

       result = xc3028_load_i2c_sequence(*(new_tv_mode_ptr->base_firmware_ptr));
       if (result!=XC3028_RESULT_SUCCESS)
           return result;
    }

    // if base firmware has changed -or- standard-specific firmware has
    // changed then reload standard-specific firmware file
    if (base_firmware_changed || std_firmware_changed) {
       result = xc3028_load_i2c_sequence(*(new_tv_mode_ptr->std_firmware_ptr));
       if (result!=XC3028_RESULT_SUCCESS)
           return result;
    }

    XC3028_current_tv_mode = *new_tv_mode_ptr;
    XC3028_current_channel_map_ptr = new_channel_map_ptr;

    // if base firmware has changed -or- standard-specific firmware has
    // changed then re-write RF channel

    if (base_firmware_changed || std_firmware_changed) {
          //do not return error if channel is incorrect...
          xc3028_set_channel(XC3028_current_channel);
    }

    return XC3028_RESULT_SUCCESS;
}

int xc3028_shutdown()
{
    //unsigned char buf[4] = {0x00, 0x08, 0x00, 0x00};
    unsigned char buf[4] = {0x80, 0x08, 0x00, 0x00}; //modified for firmware v2.2
    int res;

    xc3028_send_i2c_data(buf, 4); //no ack check

    //reset current firmware pointers to force firmware reload
    //during subsequent call to xc3028_initialize()
    XC3028_current_tv_mode.base_firmware_ptr=0;
    XC3028_current_tv_mode.std_firmware_ptr=0;

    return 0;
}

int xc3028_set_frequency(long frequency_in_hz)
{
    unsigned int frequency_code;
    int result;
    XC3028_CHANNEL new_channel;

    if (XC3028_current_channel_map_ptr == 0)
        return XC3028_RESULT_NO_CHANNELMAP_SPECIFIED;

//    if ((frequency_in_mhz>1023) || (frequency_in_mhz<1))
    if ((frequency_in_hz>1023000000) || (frequency_in_hz<1))
        return XC3028_RESULT_OUT_OF_RANGE;

//    frequency_code = (unsigned int)floor(frequency_in_mhz/0.015625);
    frequency_code = (unsigned int)(frequency_in_hz/15625);

    new_channel.frequency = frequency_code;
    new_channel.dcode = 0xFF;

    return xc3028_set_channel(new_channel);
}


int xc3028_send_scode(unsigned char dcode)
{
    unsigned char buf[4];
    int result;

    //buf[0] = 0x20;
    buf[0] = 0xA0;  // modified for firmware v2.2
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x00;

    if (XC3028_current_tv_mode.scode_table_ptr==0) {
       return XC3028_RESULT_SUCCESS;
    }

    result = xc3028_send_i2c_data(buf, 4);
    if (result!=XC3028_RESULT_SUCCESS)
       return result;

    result = xc3028_send_i2c_data((*(XC3028_current_tv_mode.scode_table_ptr))[dcode], 12);
    if (result!=XC3028_RESULT_SUCCESS)
       return result;

    buf[0] = 0x00;
    buf[1] = 0x8C;

    result = xc3028_send_i2c_data(buf, 2);
    if (result!=XC3028_RESULT_SUCCESS)
       return result;

    return XC3028_RESULT_SUCCESS;
}

int xc3028_set_channel(XC3028_CHANNEL new_channel)
{
    int i,result;
    unsigned int frequency;
    unsigned char dcode;
    unsigned char buf[4];

    XC3028_current_channel = new_channel;

    frequency = new_channel.frequency;
    if (frequency==0) {
        if (XC3028_current_channel_map_ptr == 0) {
            return XC3028_RESULT_NO_CHANNELMAP_SPECIFIED;
        }

        //lookup frequency from table using identifier
        for (i=0;i<XC3028_current_channel_map_ptr->nb_channels;i++) {
            if ( (XC3028_current_channel_map_ptr->channels[i].identifier[0] == new_channel.identifier[0]) &&
                 (XC3028_current_channel_map_ptr->channels[i].identifier[1] == new_channel.identifier[1]) &&
                 (XC3028_current_channel_map_ptr->channels[i].identifier[2] == new_channel.identifier[2]) &&
                 (XC3028_current_channel_map_ptr->channels[i].identifier[3] == new_channel.identifier[3]) ) {
                frequency = XC3028_current_channel_map_ptr->channels[i].frequency;
            }
        }
    }

    if (frequency==0)
       return XC3028_RESULT_INVALID_CHANNEL_IDENTIFIER;

    /* if supplied dcode is 0xFF, then lookup dcode using current channel map */
    dcode = new_channel.dcode;
    if (dcode==0xFF) {
        if (XC3028_current_channel_map_ptr == 0) {
            return XC3028_RESULT_NO_CHANNELMAP_SPECIFIED;
        }

        dcode=0; //default value if no close channel found
        for (i=0;i<(XC3028_current_channel_map_ptr->nb_channels);i++) {
            if ( (frequency > XC3028_current_channel_map_ptr->channels[i].frequency - 64) &&
                 (frequency < XC3028_current_channel_map_ptr->channels[i].frequency + 64) ) {
                dcode = XC3028_current_channel_map_ptr->channels[i].dcode;
            }
        }
    }

    result = xc3028_send_scode(dcode);
    if (result!=XC3028_RESULT_SUCCESS)
       return result;

    //buf[0] = 0x00;
    buf[0] = 0x80;   // modified for firmware v2.2
    buf[1] = 0x02;
    buf[2] = 0x00;
    buf[3] = 0x00;

    result = xc3028_send_i2c_data(buf, 4);
    if (result!=XC3028_RESULT_SUCCESS)
       return result;

    buf[0] = 0x00;
    buf[1] = dcode & 0x0F;
    buf[2] = (frequency>>8) % 256;
    buf[3] = (frequency) % 256;

    return xc3028_send_i2c_data(buf, 4);
}

// Obtain current frequency error of XC3028.
// Refer to datasheet for values.
int xc3028_get_frequency_error(long *frequency_error_hz)
{
    unsigned short int data;
    short int signed_data;
    int result;

    result = xc3028_get_reg(XCEIVE_XC3028_SUBADDR_FREQ_ERROR, &data);
    if (result)
        return result;

    signed_data = (short int)data;
    (*frequency_error_hz) = signed_data * 15625;

    return 0;
}

// Obtain current lock status of XC3028.
// Refer to datasheet for values.
int xc3028_get_lock_status(unsigned short int *lock_status)
{
    return xc3028_get_reg(XCEIVE_XC3028_SUBADDR_LOCK, lock_status);
}

// Obtain Version codes from XC3028.
// Refer to datasheet for values.
int xc3028_get_version(unsigned char* hw_majorversion,
                       unsigned char* hw_minorversion,
                       unsigned char* fw_majorversion,
                       unsigned char* fw_minorversion)
{
    unsigned short int data;
    int result;

    result = xc3028_get_reg(XCEIVE_XC3028_SUBADDR_VERSION, &data);
    if (result)
        return result;

    (*hw_majorversion) = (data>>12) & 0x0F;
    (*hw_minorversion) = (data>>8) & 0x0F;
    (*fw_majorversion) = (data>>4) & 0x0F;
    (*fw_minorversion) = (data) & 0x0F;

    return 0;
 }

 // Obtain Product ID from XC3028.
 // Refer to datasheet for values.
int xc3028_get_product_id(unsigned short int *product_id) {
     return xc3028_get_reg(XCEIVE_XC3028_SUBADDR_PRODUCT_ID, product_id);
 }

 // Obtain current horizontal video frequency as measured by XC3028.
 // Refer to datasheet for values.
int xc3028_get_hsync_freq(long *hsync_freq_hz)
 {
     unsigned short int data;
     int result;

     result = xc3028_get_reg(XCEIVE_XC3028_SUBADDR_HSYNC_FREQ, &data);
     if (result)
        return result;

     (*hsync_freq_hz) = (data&0x0fff)*7630;

     return 0;
 }

 // Obtain current number of lines per frame as measured by XC3028.
 // Refer to datasheet for values.
int xc3028_get_frame_lines(unsigned short int *frame_lines)
 {
     unsigned short int data;
     int result;

     result = xc3028_get_reg(XCEIVE_XC3028_SUBADDR_FRAME_LINES, &data);
     if (result)
        return result;

     (*frame_lines) = (data & 0x03ff);

     return 0;
 }

 // Obtain current video signal quality as measured by XC3028.
 // Refer to datasheet for values.
int xc3028_get_quality(unsigned short int *quality)
 {
     return xc3028_get_reg(XCEIVE_XC3028_SUBADDR_QUALITY, quality);
 }

// Scan via 2.5MHz increments from freq_min to freq_max and update table
// with frequencies of channels found. For all channels that lock, we do
// additional check on carrier stability and quality level
int xc3028_full_scan(unsigned int freq_min, unsigned int freq_max, int freq_list_size, unsigned int *freq_list, int *nb_freq_found )
 {
     int num_channels = 0;
     XC3028_CHANNEL curr_channel;
     unsigned short int lock_status;
     long freq_error, min_freq_error, max_freq_error;
     unsigned short int quality, max_quality;
     int res;

     curr_channel.frequency = freq_min;
     curr_channel.dcode = 0xFF;

     while ((num_channels<freq_list_size) && (curr_channel.frequency<freq_max)) {

 	   res=xc3028_set_channel(curr_channel);
	   if (res!=XC3028_RESULT_SUCCESS)
		return res;

           *nb_freq_found = num_channels;

	   //poll lock register
	   lock_status=0;
	   while (!lock_status) {
              res=xc3028_get_lock_status(&lock_status);
  	      if (res!=XC3028_RESULT_SUCCESS)
		 return res;
	   }

           if (lock_status!=1) {
              //no channel found
	      curr_channel.frequency += 160;	// 160*15.625khz = 2.5 MHz
           } else {
                //locked

                xc3028_wait(6);

                res=xc3028_get_frequency_error(&freq_error);
                if (res!=XC3028_RESULT_SUCCESS) return res;
                max_freq_error = freq_error;
                min_freq_error = freq_error;

                res=xc3028_get_quality(&quality);
                if (res!=XC3028_RESULT_SUCCESS) return res;
                max_quality=quality;

                xc3028_wait(6);

                res=xc3028_get_frequency_error(&freq_error);
                if (res!=XC3028_RESULT_SUCCESS) return res;
                max_freq_error = (max_freq_error>freq_error) ? max_freq_error : freq_error;
                min_freq_error = (min_freq_error<freq_error) ? min_freq_error : freq_error;

                res=xc3028_get_quality(&quality);
                if (res!=XC3028_RESULT_SUCCESS) return res;
                max_quality=(max_quality>quality) ? max_quality : quality;

                xc3028_wait(6);

                res=xc3028_get_frequency_error(&freq_error);
                if (res!=XC3028_RESULT_SUCCESS) return res;
                max_freq_error = (max_freq_error>freq_error) ? max_freq_error : freq_error;
                min_freq_error = (min_freq_error<freq_error) ? min_freq_error : freq_error;

                res=xc3028_get_quality(&quality);
                if (res!=XC3028_RESULT_SUCCESS) return res;
                max_quality=(max_quality>quality) ? max_quality : quality;


                //We got lock, but now we check that carrier is stable and that quality is sufficient
                if (((max_freq_error-min_freq_error)<60000) && (max_quality>0)) {
                    //add new channel
//         	    freq_list[num_channels]=curr_channel.frequency + floor(freq_error / 15625.0);
         	    freq_list[num_channels]=(int) (curr_channel.frequency + (unsigned int)(freq_error / 15625));
   
                    if (num_channels>0) {
                        //checking for duplicate in table
                        if ((freq_list[num_channels-1]<freq_list[num_channels]+4) &&  (freq_list[num_channels-1]>freq_list[num_channels]-4) ) {
                            //previous channel is same: cancel new entry
                            num_channels--;
                        }
                    }

        	    num_channels++;

                    // update channel frequency for next scan step
        	    curr_channel.frequency += 384;	// 384*15.625khz = 6 MHz
               } else {
                    // update channel frequency for next scan step
                    curr_channel.frequency += 160;	// 160*15.625khz = 2.5 MHz
               }
  	   }
     }

     (*nb_freq_found) = num_channels;

     return XC3028_RESULT_SUCCESS;
 }


