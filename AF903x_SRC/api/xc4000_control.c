//
// control of the XC4000 via the i2c interface.
//
// Filename : xc4000_control.cpp
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


//#include <math.h> //for Linux
#include "xc4000_control.h"
#include "i2c_driver.h"

#define XREG_INIT               0x00
#define XREG_VIDEO_MODE         0x01
#define XREG_AUDIO_MODE         0x02
#define XREG_RF_FREQ            0x03
#define XREG_DCODE              0x04
#define XREG_DIRECTSITTING_MODE 0x05
#define XREG_SEEK_MODE          0x06
#define XREG_POWER_DOWN         0x08
#define XREG_RF_MODE            0x0A
#define XREG_AMPLITUDE          0x10

#define XREG_ADC_ENV            0x00
#define XREG_QUALITY            0x01
#define XREG_FRAME_LINES        0x02
#define XREG_HSYNC_FREQ         0x03
#define XREG_LOCK               0x04
#define XREG_FREQ_ERROR         0x05
#define XREG_SNR                0x06
#define XREG_VERSION            0x07
#define XREG_PRODUCT_ID         0x08

/* *************************************************************** */
/* *************************************************************** */
/*                                                                 */
/*              CODE PROVIDED BY XCEIVE                            */
/*                                                                 */
/* *************************************************************** */
/* *************************************************************** */
int xc_write_reg(unsigned short int regAddr, unsigned short int i2cData)
{
  unsigned char buf[4];
  buf[0] = (regAddr >> 8) & 0xFF;
  buf[1] = regAddr & 0xFF;
  buf[2] = (i2cData >> 8) & 0xFF;
  buf[3] = i2cData & 0xFF;
  return xc_send_i2c_data(buf, 4);
}

int xc_read_reg(unsigned short int regAddr, unsigned short int *i2cData)
{
  unsigned char buf[2];
  int result;

  buf[0] = (regAddr >> 8) & 0xFF;
  buf[1] = regAddr & 0xFF;
  result = xc_send_i2c_data(buf, 2);
  if (result!=XC_RESULT_SUCCESS)
    return result;

  result = xc_read_i2c_data(buf, 2);
  if (result!=XC_RESULT_SUCCESS)
    return result;

  *i2cData = buf[0] * 256 + buf[1];
  return XC_RESULT_SUCCESS;
}

int xc_load_i2c_sequence(unsigned char i2c_sequence[])
{
  int i,nbytes_to_send,result;
  unsigned int length, pos, index;
  unsigned char buf[XC_MAX_I2C_WRITE_LENGTH];

  index=0;
  while ((i2c_sequence[index]!=0xFF) || (i2c_sequence[index+1]!=0xFF))
  {
    length = i2c_sequence[index]* 256 + i2c_sequence[index+1];
    if (length==0x0000)
    {
      //this is in fact a RESET command
      result = xc_reset();
      index += 2;
      if (result!=XC_RESULT_SUCCESS)
        return result;
    }
    else if (length & 0x8000)
    {
      //this is in fact a WAIT command
      xc_wait(length & 0x7FFF);
      index += 2;
    }
    else
    {
      //send i2c data whilst ensuring individual transactions do
      //not exceed XC_MAX_I2C_WRITE_LENGTH bytes
      index += 2;
      buf[0] = i2c_sequence[index];
      buf[1] = i2c_sequence[index + 1];
      pos = 2;
      while (pos < length)
      {
        if ((length - pos) > XC_MAX_I2C_WRITE_LENGTH - 2)
        {
          nbytes_to_send = XC_MAX_I2C_WRITE_LENGTH;
        }
        else
        {
          nbytes_to_send = (length - pos + 2);
        }
        for (i=2; i<nbytes_to_send; i++)
        {
          buf[i] = i2c_sequence[index + pos + i - 2];
        }
        result = xc_send_i2c_data(buf, nbytes_to_send);

        if (result!=XC_RESULT_SUCCESS)
          return result;

        pos += nbytes_to_send - 2;
      }
      index += length;
    }
  }
  return XC_RESULT_SUCCESS;
}

int xc_initialize()
{
  return xc_write_reg(XREG_INIT, 0);
}

int xc_SetTVStandard(unsigned short int VideoMode, unsigned short int AudioMode)
{
  int returnStatus = xc_write_reg(XREG_VIDEO_MODE, VideoMode);
  if (returnStatus == XC_RESULT_SUCCESS)
    returnStatus = xc_write_reg(XREG_AUDIO_MODE, AudioMode);
  return returnStatus;
}

int xc_shutdown()
{
  return xc_write_reg(XREG_POWER_DOWN, 0);
}

int xc_enter_directsitting_mode()
{
  return xc_write_reg(XREG_DIRECTSITTING_MODE, 0);
}

int xc_exit_directsitting_mode()
{
  unsigned char buf[]={0x00,0x00,0x00,0x00,0x88};
  return xc_send_i2c_data(buf, 5);
}

int xc_set_RF_frequency(long frequency_in_hz)
{
  unsigned int frequency_code;
  if ((frequency_in_hz>1023000000) || (frequency_in_hz<1000000))
    return XC_RESULT_OUT_OF_RANGE;

  frequency_code = (unsigned int)(frequency_in_hz / 15625L);
  return xc_write_reg(XREG_RF_FREQ ,frequency_code);
}

int xc_set_dcode( int dcode)
{
  return xc_write_reg(XREG_DCODE ,dcode&0x0f);
}

int xc_rf_mode(int mode)
{
  return xc_write_reg(XREG_RF_MODE, mode&0x01); // 0 is Air; 1 is cable
}



//int xc_set_IF_frequency(long frequency_in_hz)
//{
//  unsigned int frequency_code = (frequency_in_hz * 1024)/1000000;
//  return xc_write_reg(XREG_IF_OUT ,frequency_code);
//}


int xc_get_ADC_Envelope(unsigned short int *adc_envelope)
{
  return xc_read_reg(XREG_ADC_ENV, adc_envelope);
}

// Obtain current frequency error
// Refer to datasheet for values.
int xc_get_frequency_error(long *frequency_error_hz)
{
  unsigned short int data;
  short int signed_data;
  int result;

  result = xc_read_reg(XREG_FREQ_ERROR, &data);
  if (result)
    return result;

  signed_data = (short int)data;
  (*frequency_error_hz) = signed_data * 15625;

  return 0;
}

// Obtain current lock status.
// Refer to datasheet for values.
int xc_get_lock_status(unsigned short int *lock_status)
{
  return xc_read_reg(XREG_LOCK, lock_status);
}

// Obtain Version codes.
// Refer to datasheet for values.
int xc_get_version(unsigned char* hw_majorversion,
                       unsigned char* hw_minorversion,
                       unsigned char* fw_majorversion,
                       unsigned char* fw_minorversion)
{
  unsigned short int data;
  int result;

  result = xc_read_reg(XREG_VERSION, &data);
  if (result)
    return result;

    (*hw_majorversion) = (data>>12) & 0x0F;
    (*hw_minorversion) = (data>>8) & 0x0F;
    (*fw_majorversion) = (data>>4) & 0x0F;
    (*fw_minorversion) = (data) & 0x0F;

  return 0;
}

// Obtain Product ID.
// Refer to datasheet for values.
int xc_get_product_id(unsigned short int *product_id)
{
  return xc_read_reg(XREG_PRODUCT_ID, product_id);
}

// Obtain current horizontal video frequency.
// Refer to datasheet for values.
int xc_get_hsync_freq(int *hsync_freq_hz)
{
  unsigned short int regData;
  int result;

  result = xc_read_reg(XREG_HSYNC_FREQ, &regData);
  if (result)
    return result;
  (*hsync_freq_hz) = ((regData & 0x0fff) * 763)/100;
  return result;
}

 // Obtain current number of lines per frame.
 // Refer to datasheet for values.
int xc_get_frame_lines(unsigned short int *frame_lines)
{
  return xc_read_reg(XREG_FRAME_LINES, frame_lines);
}

// Obtain current video signal quality.
// Refer to datasheet for values.
int xc_get_quality(unsigned short int *quality)
{
  return xc_read_reg(XREG_QUALITY, quality);
}

unsigned short int WaitForLock()
{
  unsigned short int lockState = 0;
  int watchDogCount = 40;
  while ((lockState == 0) && (watchDogCount > 0))
  {
    xc_get_lock_status(&lockState);
    if (lockState != 1)
    {
      xc_wait(5);      // wait 5 ms
      watchDogCount--;
    }
  }
  return lockState;
}

int xc_tune_channel(long chnl_freq)//for Linux
{
  long freq_error, min_freq_error, max_freq_error;
  unsigned short int quality, max_quality;
  int res;
  int  chnl_found = 0;//for Linux

  if (xc_set_RF_frequency(chnl_freq) != XC_RESULT_SUCCESS)
    return 0;//for Linux
  if (WaitForLock()== 1)
  {
    xc_wait(6);
    res=xc_get_frequency_error(&freq_error);
    if (res!=XC_RESULT_SUCCESS) return res;
    max_freq_error = freq_error;
    min_freq_error = freq_error;

    xc_wait(6);

    res=xc_get_frequency_error(&freq_error);
    if (res!=XC_RESULT_SUCCESS) return res;
    max_freq_error = (max_freq_error>freq_error) ? max_freq_error : freq_error;
    min_freq_error = (min_freq_error<freq_error) ? min_freq_error : freq_error;

    xc_wait(6);

    res=xc_get_frequency_error(&freq_error);
    if (res!=XC_RESULT_SUCCESS) return res;
    max_freq_error = (max_freq_error>freq_error) ? max_freq_error : freq_error;
    min_freq_error = (min_freq_error<freq_error) ? min_freq_error : freq_error;

    //We got lock, but now we check that carrier is stable and that quality is sufficient
    if ((max_freq_error-min_freq_error)<60000)
      chnl_found = 1;//for Linux
      //add new channel

  }
  return chnl_found;
}
