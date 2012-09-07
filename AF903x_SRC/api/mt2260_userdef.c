/*****************************************************************************
**
**  Name: mt_userdef.c
**
**  Description:    User-defined MicroTuner software interface 
**
**  Functions
**  Requiring
**  Implementation: MT_WriteSub
**                  MT_ReadSub
**                  MT_Sleep
**
**  References:     None
**
**  Exports:        None
**
**  CVS ID:         $Id: mt_userdef.c,v 1.1 2006/05/08 22:05:01 software Exp $
**  CVS Source:     $Source: /export/home/cvsroot/web05/html/software/tuners/MT2260/MT2260B0/mt_userdef.c,v $
**	               
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   03-25-2004    DAD    Original
**   N/A   12-06-2004    JWS    Multi-tuner support
**
*****************************************************************************/
#include "mt2260_userdef.h"


/*****************************************************************************
**
**  Name: MT_WriteSub
**
**  Description:    Write values to device using a two-wire serial bus.
**
**  Parameters:     handle  - User-specific I/O parameter that was
**                               passed to tuner's Open function.
**                  addr       - device serial bus address  (value passed
**                               as parameter to MTxxxx_Open)
**                  subAddress - serial bus sub-address (Register Address)
**                  data      - pointer to the Data to be written to the 
**                               device 
**                  cnt        - number of bytes/registers to be written
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_COMM_ERR      - Serial bus communications error
**                      user-defined
**
**  Notes:          This is a callback function that is called from the
**                  the tuning algorithm.  You MUST provide code for this
**                  function to write data using the tuner's 2-wire serial 
**                  bus.
**
**                  The handle parameter is a user-specific argument.
**                  If additional arguments are needed for the user's
**                  serial bus read/write functions, this argument can be
**                  used to supply the necessary information.
**                  The handle parameter is initialized in the tuner's Open
**                  function.
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   03-25-2004    DAD    Original
**
*****************************************************************************/
UData_t MT2260_WriteSub(Handle_t handle, 
                    UData_t addr, 
                    U8Data subAddress, 
                    U8Data *data, 
                    UData_t cnt)
{
    UData_t status = MT_OK;                  /* Status to be returned        */
    /*
    **  ToDo:  Add code here to implement a serial-bus write
    **         operation to the MTxxxx tuner.  If successful,
    **         return MT_OK.
    */
    PUserData   userData;
    U8Data *    buffer;
    U8Data      i;
    U8Data      blocks;
    U8Data      remains;

    blocks =  (U8Data) (cnt / 17);
    remains = (U8Data) (cnt % 17);

    userData = (PUserData) handle;

    buffer = data;
    for (i = 0; i < blocks; i++) {        
		status = Standard_writeTunerRegisters (userData->demodulator, userData->chip, (unsigned short)subAddress + (unsigned short)i * 17, 17, buffer);
        if (status) goto exit;

        buffer += 17;
    }

    if (remains)
    {
        status = Standard_writeTunerRegisters (userData->demodulator, userData->chip, (unsigned short)subAddress + (unsigned short)i * 17, remains, buffer);
        if (status) goto exit;
    }

exit:
    return (status);
}


/*****************************************************************************
**
**  Name: MT_ReadSub
**
**  Description:    Read values from device using a two-wire serial bus.
**
**  Parameters:     handle  - User-specific I/O parameter that was
**                               passed to tuner's Open function.
**                  addr       - device serial bus address  (value passed
**                               as parameter to MTxxxx_Open)
**                  subAddress - serial bus sub-address (Register Address)
**                  data      - pointer to the Data to be written to the 
**                               device 
**                  cnt        - number of bytes/registers to be written
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_COMM_ERR      - Serial bus communications error
**                      user-defined
**
**  Notes:          This is a callback function that is called from the
**                  the tuning algorithm.  You MUST provide code for this
**                  function to read data using the tuner's 2-wire serial 
**                  bus.
**
**                  The handle parameter is a user-specific argument.
**                  If additional arguments are needed for the user's
**                  serial bus read/write functions, this argument can be
**                  used to supply the necessary information.
**                  The handle parameter is initialized in the tuner's Open
**                  function.
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   03-25-2004    DAD    Original
**
*****************************************************************************/
UData_t MT2260_ReadSub(Handle_t handle, 
                   UData_t addr, 
                   U8Data subAddress, 
                   U8Data *data, 
                   UData_t cnt)
{
    UData_t status = MT_OK;                        /* Status to be returned        */

    /*
    **  ToDo:  Add code here to implement a serial-bus read
    **         operation to the MTxxxx tuner.  If successful,
    **         return MT_OK.
    */
    PUserData   userData;
    U8Data      buffer[8];
    U8Data      i;

    /*
    **  ToDo:  Add code here to implement a serial-bus read
    **         operation to the MTxxxx tuner.  If successful,
    **         return true.
    */
    userData = (PUserData)handle;

    for (i = 0; i < cnt; i++)
    {
		status = Standard_readTunerRegisters (userData->demodulator, userData->chip, subAddress + i, (U8Data)1, &buffer[0]);
        if (status) goto exit;
        *(data + i) = buffer[0];
    }

exit:
    return (status);
}


/*****************************************************************************
**
**  Name: MT_Sleep
**
**  Description:    Delay execution for "nMinDelayTime" milliseconds
**
**  Parameters:     handle     - User-specific I/O parameter that was
**                                  passed to tuner's Open function.
**                  nMinDelayTime - Delay time in milliseconds
**
**  Returns:        None.
**
**  Notes:          This is a callback function that is called from the
**                  the tuning algorithm.  You MUST provide code that
**                  blocks execution for the specified period of time. 
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   03-25-2004    DAD    Original
**
*****************************************************************************/
void MT2260_Sleep(Handle_t handle, 
              UData_t nMinDelayTime)
{
    PUserData   userData;
    /*
    **  ToDo:  Add code here to implement a OS blocking
    **         for a period of "nMinDelayTime" milliseconds.
    */
   userData = (PUserData)handle;

   User_delay (userData->demodulator, (unsigned long) nMinDelayTime);
}
