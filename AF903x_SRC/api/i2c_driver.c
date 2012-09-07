//---------------------------------------------------------------------------
#include "xc4000_control.h"
#include "i2c_driver.h"
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
//---------------------------------------------------------------------------
Demodulator* XC4000Handle = NULL;
Byte XC4000Chip = 0;

/* *************************************************************** */
/* *************************************************************** */
/*                                                                 */
/*       FOLLOWING FUNCTIONS TO BE IMPLEMENTED BY CUSTOMER         */
/*                                                                 */
/* *************************************************************** */
/* *************************************************************** */

// user must replace the following routines with their own i2c driver
// return XC_RESULT_SUCCESS if i2c data is send correctly,
// return XC_RESULT_I2C_WRITE_FAILURE when error occur.
int xc_send_i2c_data(unsigned char *bytes_to_send, int nb_bytes_to_send)
{
    Dword error = Error_NO_ERROR;

    error = Standard_writeTunerRegisters (XC4000Handle, XC4000Chip, 0x0000, nb_bytes_to_send, bytes_to_send);
    return (error);
}

int xc_read_i2c_data(unsigned char *bytes_received, int nb_bytes_to_receive)
{
    Dword error = Error_NO_ERROR;
   
    error = Standard_readTunerRegisters (XC4000Handle, XC4000Chip, 0x0000, nb_bytes_to_receive, bytes_received);
    return (error);
}

int xc_reset()
{
    Dword error = Error_NO_ERROR;

    error = Standard_writeRegisterBits (XC4000Handle, XC4000Chip, Processor_LINK, p_reg_top_gpiot2_o, reg_top_gpiot2_o_pos, reg_top_gpiot2_o_len, 0);
    if (error) goto exit;
	
    error = Standard_writeRegisterBits (XC4000Handle, XC4000Chip, Processor_LINK, p_reg_top_gpiot2_en, reg_top_gpiot2_en_pos, reg_top_gpiot2_en_len, 1);
    if (error) goto exit;
	
    error = Standard_writeRegisterBits (XC4000Handle, XC4000Chip, Processor_LINK, p_reg_top_gpiot2_on, reg_top_gpiot2_on_pos, reg_top_gpiot2_on_len, 1);
    if (error) goto exit;

    User_delay (XC4000Handle, 250);

    error = Standard_writeRegisterBits (XC4000Handle, XC4000Chip, Processor_LINK, p_reg_top_gpiot2_o, reg_top_gpiot2_o_pos, reg_top_gpiot2_o_len, 1);
    if (error) goto exit;

exit:
    return (error);
}

void xc_wait(int wait_ms)
{
    User_delay (XC4000Handle, (Dword)wait_ms);
}
