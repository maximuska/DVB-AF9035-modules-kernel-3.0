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
**  CVS ID:         $Id: mt_userdef.c,v 1.2 2006/10/26 16:39:18 software Exp $
**  CVS Source:     $Source: /export/home/cvsroot/software/tuners/MT2266/mt_userdef.c,v $
**	               
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   03-25-2004    DAD    Original
**
*****************************************************************************/
#include "mt2266_userdef.h"


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
UData_t MT2266_WriteSub(Handle_t handle, 
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
UData_t MT2266_ReadSub(Handle_t handle, 
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
void MT2266_Sleep(Handle_t handle, 
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


#if defined(MT2060_CNT)
#if MT2060_CNT > 0
/*****************************************************************************
**
**  Name: MT_TunerGain  (MT2060 only)
**
**  Description:    Measure the relative tuner gain using the demodulator
**
**  Parameters:     handle  - User-specific I/O parameter that was
**                               passed to tuner's Open function.
**                  pMeas      - Tuner gain (1/100 of dB scale).
**                               ie. 1234 = 12.34 (dB)
**
**  Returns:        status:
**                      MT_OK  - No errors
**                      user-defined errors could be set
**
**  Notes:          This is a callback function that is called from the
**                  the 1st IF location routine.  You MUST provide
**                  code that measures the relative tuner gain in a dB
**                  (not linear) scale.  The return value is an integer
**                  value scaled to 1/100 of a dB.
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   06-16-2004    DAD    Original
**   N/A   11-30-2004    DAD    Renamed from MT_DemodInputPower.  This name
**                              better describes what this function does.
**
*****************************************************************************/
int IfGainTable[256] = {
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	6000,
	5993,
	5987,
	5981,
	5975,
	5968,
	5962,
	5956,
	5950,
	5949,
	5948,
	5947,
	5946,
	5945,
	5944,
	5943,
	5942,
	5941,
	5940,
	5939,
	5938,
	5937,
	5937,
	5936,
	5935,
	5934,
	5933,
	5932,
	5931,
	5930,
	5929,
	5928,
	5927,
	5926,
	5925,
	5925,
	5924,
	5923,
	5922,
	5921,
	5920,
	5919,
	5918,
	5917,
	5916,
	5915,
	5914,
	5913,
	5912,
	5912,
	5911,
	5910,
	5909,
	5908,
	5907,
	5906,
	5905,
	5904,
	5903,
	5902,
	5901,
	5900,
	5900,
	5885,
	5871,
	5857,
	5842,
	5828,
	5814,
	5800,
	5785,
	5771,
	5757,
	5742,
	5728,
	5714,
	5700,
	5685,
	5671,
	5657,
	5642,
	5628,
	5614,
	5600,
	5585,
	5571,
	5557,
	5542,
	5528,
	5514,
	5500,
	5485,
	5471,
	5457,
	5442,
	5428,
	5414,
	5400,
	5381,
	5362,
	5344,
	5325,
	5307,
	5288,
	5270,
	5251,
	5233,
	5214,
	5196,
	5177,
	5159,
	5140,
	5122,
	5103,
	5085,
	5066,
	5048,
	5029,
	5011,
	4992,
	4974,
	4955,
	4937,
	4918,
	4900,
	4871,
	4842,
	4813,
	4784,
	4755,
	4726,
	4697,
	4668,
	4639,
	4610,
	4581,
	4552,
	4523,
	4494,
	4465,
	4436,
	4407,
	4378,
	4350,
	4318,
	4287,
	4256,
	4225,
	4193,
	4162,
	4131,
	4100,
	4068,
	4037,
	4006,
	3975,
	3943,
	3912,
	3881,
	3850,
	3809,
	3768,
	3727,
	3686,
	3645,
	3604,
	3563,
	3522,
	3481,
	3440,
	3400,
	3358,
	3316,
	3275,
	3233,
	3191,
	3150,
	3108,
	3066,
	3025,
	2983,
	2941,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900,
	2900
};

UData_t MT2266_TunerGain(Handle_t handle,
                     SData_t* pMeas)
{
    UData_t status = MT_OK;                        /* Status to be returned        */
    U8Data      rfAgc;
    U8Data      ifAgc;
    PUserData   userData;

    /*
    **  ToDo:  Add code here to return the gain / power level measured
    **         at the input to the demodulator.
    */


    /*
    **  ToDo:  Add code here to return the gain / power level measured
    **         at the input to the demodulator.
    */
    userData = (PUserData)handle;

    MT2060_Sleep(handle, 100);

    status = Standard_getIfAgcGain (userData->demodulator, userData->chip, &rfAgc, &ifAgc);
    if (status) goto exit;

    *pMeas = IfGainTable[ifAgc];

exit:
    return (status);
}
#endif
#endif