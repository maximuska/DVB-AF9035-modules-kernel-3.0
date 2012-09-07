/*****************************************************************************
**
**  Name: mt2260.c
**
**  Description:    Microtune MT2260 Tuner software interface.
**                  Supports tuners with Part/Rev code: 0x85.
**
**  Functions
**  Implemented:    UData_t  MT2260_Open
**                  UData_t  MT2260_Close
**                  UData_t  MT2260_ChangeFreq
**                  UData_t  MT2260_GetLocked
**                  UData_t  MT2260_GetParam
**                  UData_t  MT2260_GetReg
**                  UData_t  MT2260_GetUserData
**                  UData_t  MT2260_ReInit
**                  UData_t  MT2260_SetParam
**                  UData_t  MT2260_SetPowerModes
**                  UData_t  MT2260_SetReg
**
**  References:     AN-00010: MicroTuner Serial Interface Application Note
**                  MicroTune, Inc.
**
**  Exports:        None
**
**  Dependencies:   MT2260_ReadSub(hUserData, IC_Addr, subAddress, *pData, cnt);
**                  - Read byte(s) of data from the two-wire bus.
**
**                  MT2260_WriteSub(hUserData, IC_Addr, subAddress, *pData, cnt);
**                  - Write byte(s) of data to the two-wire bus.
**
**                  MT2260_Sleep(hUserData, nMinDelayTime);
**                  - Delay execution for x milliseconds
**
**  CVS ID:         $Id: mt2260.c,v 1.1 2006/05/08 22:05:01 software Exp $
**  CVS Source:     $Source: /export/home/cvsroot/web05/html/software/tuners/MT2260/MT2260B0/mt2260.c,v $
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**   N/A   04-26-2006    DAD    Ver 1.01: Add support for 8-38.4 MHz crystals
**
*****************************************************************************/
#include "mt2260.h"
//#include <stdlib.h>                     /* for NULL */ //for Linux

/*  Version of this module                          */
#define VERSION 10001             /*  Version 01.01 */


#ifndef MT2260_CNT
#error You must define MT2260_CNT in the "mt_userdef.h" file
#endif

/*
**  Normally, the "reg" array in the tuner structure is used as a cache
**  containing the current value of the tuner registers.  If the user's
**  application MUST change tuner registers without using the MT2260_SetReg
**  routine provided, he may compile this code with the __NO_CACHE__
**  variable defined.  
**  The PREFETCH macro will insert code code to re-read tuner registers if
**  __NO_CACHE__ is defined.  If it is not defined (normal) then PREFETCH
**  does nothing.
*/

#if defined(__NO_CACHE__)
#define PREFETCH(var, cnt) \
    if (MT_NO_ERROR(status)) \
    status |= MT2260_ReadSub(pInfo->hUserData, pInfo->address, (var), &pInfo->reg[(var)], (cnt));
#else
#define PREFETCH(var, cnt)
#endif



/*
**  Two-wire serial bus subaddresses of the tuner registers.
**  Also known as the tuner's register addresses.
*/
static enum MT2260_Register_Offsets
{
    MT2260_PART_REV = 0,   /*  0x00 */
    MT2260_LO_CTRL_1,      /*  0x01 */
    MT2260_LO_CTRL_2,      /*  0x02 */
    MT2260_LO_CTRL_3,      /*  0x03 */
    MT2260_SMART_ANT,      /*  0x04 */
    MT2260_BAND_CTRL,      /*  0x05 */
    MT2260_CLEARTUNE,      /*  0x06 */
    MT2260_IGAIN,          /*  0x07 */
    MT2260_BBFILT_1,       /*  0x08 */
    MT2260_BBFILT_2,       /*  0x09 */
    MT2260_BBFILT_3,       /*  0x0A */
    MT2260_BBFILT_4,       /*  0x0B */
    MT2260_BBFILT_5,       /*  0x0C */
    MT2260_BBFILT_6,       /*  0x0D */
    MT2260_BBFILT_7,       /*  0x0E */
    MT2260_BBFILT_8,       /*  0x0F */
    MT2260_RCC_CTRL,       /*  0x10 */
    MT2260_RSVD_11,        /*  0x11 */
    MT2260_STATUS_1,       /*  0x12 */
    MT2260_STATUS_2,       /*  0x13 */
    MT2260_STATUS_3,       /*  0x14 */
    MT2260_STATUS_4,       /*  0x15 */
    MT2260_STATUS_5,       /*  0x16 */
    MT2260_SRO_CTRL,       /*  0x17 */
    MT2260_RSVD_18,        /*  0x18 */
    MT2260_RSVD_19,        /*  0x19 */
    MT2260_RSVD_1A,        /*  0x1A */
    MT2260_RSVD_1B,        /*  0x1B */
    MT2260_ENABLES,        /*  0x1C */
    MT2260_RSVD_1D,        /*  0x1D */
    MT2260_RSVD_1E,        /*  0x1E */
    MT2260_RSVD_1F,        /*  0x1F */
    MT2260_GPO,            /*  0x20 */
    MT2260_RSVD_21,        /*  0x21 */
    MT2260_RSVD_22,        /*  0x22 */
    MT2260_RSVD_23,        /*  0x23 */
    MT2260_RSVD_24,        /*  0x24 */
    MT2260_RSVD_25,        /*  0x25 */
    MT2260_RSVD_26,        /*  0x26 */
    MT2260_RSVD_27,        /*  0x27 */
    MT2260_RSVD_28,        /*  0x28 */
    MT2260_RSVD_29,        /*  0x29 */
    MT2260_RSVD_2A,        /*  0x2A */
    MT2260_RSVD_2B,        /*  0x2B */
    MT2260_RSVD_2C,        /*  0x2C */
    MT2260_RSVD_2D,        /*  0x2D */
    MT2260_RSVD_2E,        /*  0x2E */
    MT2260_RSVD_2F,        /*  0x2F */
    MT2260_RSVD_30,        /*  0x30 */
    MT2260_RSVD_31,        /*  0x31 */
    MT2260_RSVD_32,        /*  0x32 */
    MT2260_RSVD_33,        /*  0x33 */
    MT2260_RSVD_34,        /*  0x34 */
    MT2260_RSVD_35,        /*  0x35 */
    MT2260_RSVD_36,        /*  0x36 */
    MT2260_RSVD_37,        /*  0x37 */
    MT2260_RSVD_38,        /*  0x38 */
    MT2260_RSVD_39,        /*  0x39 */
    MT2260_RSVD_3A,        /*  0x3A */
    MT2260_RSVD_3B,        /*  0x3B */
    MT2260_RSVD_3C,        /*  0x3C */
    END_REGS
};

/*
** DefaultsEntry points to an array of U8Data used to initialize
** various registers (the first byte is the starting subaddress)
** and a count of the bytes (including subaddress) in the array.
**
** DefaultsList is an array of DefaultsEntry elements terminated
** by an entry with a NULL pointer for the data array.
*/
typedef struct MT2260_DefaultsEntryTag
{
    U8Data *data;
    UData_t cnt;
} MT2260_DefaultsEntry;

typedef MT2260_DefaultsEntry MT2260_DefaultsList[];

#define DEF_LIST_ENTRY(a) {a, sizeof(a)/sizeof(U8Data) - 1}
#define END_DEF_LIST {0,0}

/*
** Constants used by the tuning algorithm
*/
                                        /* REF_FREQ is now the actual crystal frequency */
#define REF_FREQ          (30000000UL)  /* Reference oscillator Frequency (in Hz) */
#define TUNE_STEP_SIZE          (50UL)  /* Tune in steps of 50 kHz */
#define MIN_UHF_FREQ     (350000000UL)  /* Minimum UHF frequency (in Hz) */
#define MAX_UHF_FREQ     (900000000UL)  /* Maximum UHF frequency (in Hz) */
#define MIN_LBAND_FREQ  (1670000000UL)  /* Minimum L-Band frequency (in Hz) */
#define MAX_LBAND_FREQ  (1680000000UL)  /* Maximum L-Band frequency (in Hz) */
#define OUTPUT_BW          (8000000UL)  /* Output channel bandwidth (in Hz) */
#define UHF_DEFAULT_FREQ (600000000UL)  /* Default UHF input frequency (in Hz) */


/*
**  The number of Tuner Registers
*/
static const UData_t Num_Registers = END_REGS;

typedef struct
{
    Handle_t    handle;
    Handle_t    hUserData;
    UData_t     address;
    UData_t     version;
    UData_t     tuner_id;
    UData_t     f_Ref;
    UData_t     f_Step;
    UData_t     f_in;
    UData_t     f_LO;
    UData_t     f_bw;
    UData_t     band;
    UData_t     num_regs;
    U8Data      RC2_Value;
    U8Data      RC2_Nominal;
    U8Data      reg[END_REGS];
}  MT2260_Info_t;

static UData_t nMaxTuners = MT2260_CNT;
static MT2260_Info_t MT2260_Info[MT2260_CNT];
static MT2260_Info_t *Avail[MT2260_CNT];
static UData_t nOpenTuners = 0;

/*
**  Constants used to write a minimal set of registers when changing bands.
**  If the user wants a total reset, they should call MT2260_Open() again.
**  Skip 01, 02, 03, 04  (get overwritten anyways)
**  Write 05
**  Skip 06 - 18
**  Write 19   (diff for L-Band)
**  Skip 1A 1B 1C
**  Write 1D - 2B
**  Skip 2C - 3C
*/

static U8Data MT2260_UHF_defaults1[] = 
{
    0x05,              /* address 0xC0, reg 0x05 */
    0x52,              /* Reg 0x05 */
};
static U8Data MT2260_UHF_defaults2[] = 
{
    0x19,              /* address 0xC0, reg 0x19 */
    0x61,              /* Reg 0x19 CAPto = 3*/
};
static U8Data MT2260_UHF_defaults3[] = 
{
    0x1D,              /* address 0xC0, reg 0x1D */
    0xDC,              /* Reg 0x1D */
    0x00,              /* Reg 0x1E */
    0x0A,              /* Reg 0x1F */
    0xD4,              /* Reg 0x20 GPO = 1*/
    0x03,              /* Reg 0x21 LBIASen = 1, UBIASen = 1*/
    0x64,              /* Reg 0x22 */
    0x64,              /* Reg 0x23 */
    0x64,              /* Reg 0x24 */
    0x64,              /* Reg 0x25 */
    0x22,              /* Reg 0x26 CASCM = b0100 (bits reversed)*/
    0xAA,              /* Reg 0x27 */
    0xF2,              /* Reg 0x28 */
    0x1E,              /* Reg 0x29 */
    0x80,              /* Reg 0x2A MIXbiasen = 1*/
    0x14,              /* Reg 0x2B */
};

static MT2260_DefaultsList MT2260_UHF_defaults = {
    DEF_LIST_ENTRY(MT2260_UHF_defaults1),
    DEF_LIST_ENTRY(MT2260_UHF_defaults2),
    DEF_LIST_ENTRY(MT2260_UHF_defaults3),
    END_DEF_LIST
};

static U8Data MT2260_LBAND_defaults1[] = 
{
    0x05,              /* address 0xC0, reg 0x05 */
    0xC4,              /* Reg 0x05 */
};
static U8Data MT2260_LBAND_defaults2[] = 
{
    0x19,              /* address 0xC0, reg 0x19 */
    0x63,              /* Reg 0x19 CAPto = 3, VCOamp = 3*/
};
static U8Data MT2260_LBAND_defaults3[] = 
{
    0x1D,              /* address 0xC0, reg 0x1D */
    0xFE,              /* Reg 0x1D */
    0x00,              /* reg 0x1E */
    0x00,              /* reg 0x1F */
    0xB4,              /* Reg 0x20 GPO = 1, RFAext = 0*/
    0x01,              /* Reg 0x21 LBIASen = 1*/
    0xA5,              /* Reg 0x22 */
    0xA5,              /* Reg 0x23 */
    0xA5,              /* Reg 0x24 */
    0xA5,              /* Reg 0x25 */
    0x82,              /* Reg 0x26 CASCM = b0001 (bits reversed)*/
    0xAA,              /* Reg 0x27 */
    0xF1,              /* Reg 0x28 */
    0x17,              /* Reg 0x29 */
    0x80,              /* Reg 0x2A MIXbiasen = 1*/
    0x1F,              /* Reg 0x2B */
};

static MT2260_DefaultsList MT2260_LBAND_defaults = {
    DEF_LIST_ENTRY(MT2260_LBAND_defaults1),
    DEF_LIST_ENTRY(MT2260_LBAND_defaults2),
    DEF_LIST_ENTRY(MT2260_LBAND_defaults3),
    END_DEF_LIST
};

/* This table is used when MaxSensitivity is ON */
static UData_t MT2260_UHF_XFreq[] = 
{
    443000 / TUNE_STEP_SIZE,     /*        < 443 MHz: 15+1 */
    470000 / TUNE_STEP_SIZE,     /*  443 ..  470 MHz: 15 */
    496000 / TUNE_STEP_SIZE,     /*  470 ..  496 MHz: 14 */
    525000 / TUNE_STEP_SIZE,     /*  496 ..  525 MHz: 13 */
    552000 / TUNE_STEP_SIZE,     /*  525 ..  552 MHz: 12 */
    580000 / TUNE_STEP_SIZE,     /*  552 ..  580 MHz: 11 */
    605000 / TUNE_STEP_SIZE,     /*  580 ..  605 MHz: 10 */
    632000 / TUNE_STEP_SIZE,     /*  605 ..  632 MHz:  9 */
    657000 / TUNE_STEP_SIZE,     /*  632 ..  657 MHz:  8 */
    682000 / TUNE_STEP_SIZE,     /*  657 ..  682 MHz:  7 */
    710000 / TUNE_STEP_SIZE,     /*  682 ..  710 MHz:  6 */
    735000 / TUNE_STEP_SIZE,     /*  710 ..  735 MHz:  5 */
    763000 / TUNE_STEP_SIZE,     /*  735 ..  763 MHz:  4 */
    802000 / TUNE_STEP_SIZE,     /*  763 ..  802 MHz:  3 */
    840000 / TUNE_STEP_SIZE,     /*  802 ..  840 MHz:  2 */
    877000 / TUNE_STEP_SIZE      /*  840 ..  877 MHz:  1 */
                                 /*  877+        MHz:  0 */
};

/* This table is used when MaxSensitivity is OFF */
static UData_t MT2260_UHFA_XFreq[] = 
{
    442000 / TUNE_STEP_SIZE,     /*        < 442 MHz: 15+1 */
    472000 / TUNE_STEP_SIZE,     /*  442 ..  472 MHz: 15 */
    505000 / TUNE_STEP_SIZE,     /*  472 ..  505 MHz: 14 */
    535000 / TUNE_STEP_SIZE,     /*  505 ..  535 MHz: 13 */
    560000 / TUNE_STEP_SIZE,     /*  535 ..  560 MHz: 12 */
    593000 / TUNE_STEP_SIZE,     /*  560 ..  593 MHz: 11 */
    620000 / TUNE_STEP_SIZE,     /*  593 ..  620 MHz: 10 */
    647000 / TUNE_STEP_SIZE,     /*  620 ..  647 MHz:  9 */
    673000 / TUNE_STEP_SIZE,     /*  647 ..  673 MHz:  8 */
    700000 / TUNE_STEP_SIZE,     /*  673 ..  700 MHz:  7 */
    727000 / TUNE_STEP_SIZE,     /*  700 ..  727 MHz:  6 */
    752000 / TUNE_STEP_SIZE,     /*  727 ..  752 MHz:  5 */
    783000 / TUNE_STEP_SIZE,     /*  752 ..  783 MHz:  4 */
    825000 / TUNE_STEP_SIZE,     /*  783 ..  825 MHz:  3 */
    865000 / TUNE_STEP_SIZE,     /*  825 ..  865 MHz:  2 */
    905000 / TUNE_STEP_SIZE      /*  865 ..  905 MHz:  1 */
                                 /*  905+        MHz:  0 */
};

static UData_t UncheckedSet(MT2260_Info_t* pInfo,
                            U8Data         reg,
                            U8Data         val);

static UData_t UncheckedGet(MT2260_Info_t* pInfo,
                            U8Data   reg,
                            U8Data*  val);


/******************************************************************************
**
**  Name: MT2260_Open
**
**  Description:    Initialize the tuner's register values.
**
**  Parameters:     MT2260_Addr  - Serial bus address of the tuner.
**                  hMT2260      - Tuner handle passed back.
**                  hUserData    - User-defined data, if needed for the
**                                 MT2260_ReadSub() & MT2260_WriteSub functions.
**
**  Returns:        status:
**                      MT_OK             - No errors
**                      MT_TUNER_ID_ERR   - Tuner Part/Rev code mismatch
**                      MT_TUNER_INIT_ERR - Tuner initialization failed
**                      MT_COMM_ERR       - Serial bus communications error
**                      MT_ARG_NULL       - Null pointer argument passed
**                      MT_TUNER_CNT_ERR  - Too many tuners open
**
**  Dependencies:   MT2260_ReadSub  - Read byte(s) of data from the two-wire bus
**                  MT2260_WriteSub - Write byte(s) of data to the two-wire bus
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
******************************************************************************/
UData_t MT2260_Open(UData_t MT2260_Addr,
                    Handle_t* hMT2260,
                    Handle_t hUserData)
{
    UData_t status = MT_OK;             /*  Status to be returned.  */
    SData_t i;
    MT2260_Info_t* pInfo = NULL;

    /*  Check the argument before using  */
    if (hMT2260 == NULL)
        return MT_ARG_NULL;
    *hMT2260 = NULL;

    /*
    **  If this is our first tuner, initialize the address fields and
    **  the list of available control blocks.
    */
    if (nOpenTuners == 0)
    {
        for (i=MT2260_CNT-1; i>=0; i--)
        {
            MT2260_Info[i].handle = NULL;
            MT2260_Info[i].address = MAX_UDATA;
            MT2260_Info[i].hUserData = NULL;
            Avail[i] = &MT2260_Info[i];
        }
    }

    /*
    **  Look for an existing MT2260_State_t entry with this address.
    */
    for (i=MT2260_CNT-1; i>=0; i--)
    {
        /*
        **  If an open'ed handle provided, we'll re-initialize that structure.
        **
        **  We recognize an open tuner because the address and hUserData are
        **  the same as one that has already been opened
        */
        if ((MT2260_Info[i].address == MT2260_Addr) &&
            (MT2260_Info[i].hUserData == hUserData))
        {
            pInfo = &MT2260_Info[i];
            break;
        }
    }

    /*  If not found, choose an empty spot.  */
    if (pInfo == NULL)
    {
        /*  Check to see that we're not over-allocating.  */
        if (nOpenTuners == MT2260_CNT)
            return MT_TUNER_CNT_ERR;

        /* Use the next available block from the list */
        pInfo = Avail[nOpenTuners];
        nOpenTuners++;
    }

    pInfo->handle = (Handle_t) pInfo;
    pInfo->hUserData = hUserData;
    pInfo->address = MT2260_Addr;

    status |= MT2260_ReInit((Handle_t) pInfo);

    if (MT_IS_ERROR(status))
        MT2260_Close((Handle_t) pInfo);
    else
        *hMT2260 = pInfo->handle;

    return (status);
}


static UData_t IsValidHandle(MT2260_Info_t* handle)
{
    return ((handle != NULL) && (handle->handle == handle)) ? 1 : 0;
}


/******************************************************************************
**
**  Name: MT2260_Close
**
**  Description:    Release the handle to the tuner.
**
**  Parameters:     hMT2260      - Handle to the MT2260 tuner
**
**  Returns:        status:
**                      MT_OK         - No errors
**                      MT_INV_HANDLE - Invalid tuner handle
**
**  Dependencies:   mt_errordef.h - definition of error codes
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
******************************************************************************/
UData_t MT2260_Close(Handle_t hMT2260)
{
    MT2260_Info_t* pInfo = (MT2260_Info_t*) hMT2260;

    if (!IsValidHandle(pInfo))
        return MT_INV_HANDLE;

    /* Remove the tuner from our list of tuners */
    pInfo->handle = NULL;
    pInfo->address = MAX_UDATA;
    pInfo->hUserData = NULL;
    nOpenTuners--;
    Avail[nOpenTuners] = pInfo; /* Return control block to available list */

    return MT_OK;
}


/******************************************************************************
**
**  Name: Run_BB_RC_Cal2
**
**  Description:    Run Base Band RC Calibration (Method 2)
**                  MT2260 B0 only, others return MT_OK
**
**  Parameters:     hMT2260      - Handle to the MT2260 tuner
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_INV_HANDLE    - Invalid tuner handle
**
**  Dependencies:   mt_errordef.h - definition of error codes
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**   N/A   04-26-2006     DAD   Clear bit only if SRO >= 36 MHz (was 33 MHz).
**
******************************************************************************/
static UData_t Run_BB_RC_Cal2(Handle_t h)
{
    UData_t status = MT_OK;                  /* Status to be returned */
    U8Data tmp_rcc;
    U8Data dumy;
    
    MT2260_Info_t* pInfo = (MT2260_Info_t*) h;

    /*  Verify that the handle passed points to a valid tuner         */
    if (IsValidHandle(pInfo) == 0)
        status |= MT_INV_HANDLE;

    /*
    ** Set the crystal frequency in the calibration register 
    ** and enable RC calibration #2
    */
    PREFETCH(MT2260_RCC_CTRL, 1);  /* Fetch register(s) if __NO_CACHE__ defined */
    tmp_rcc = pInfo->reg[MT2260_RCC_CTRL];
    if (pInfo->f_Ref < (36000000 /*/ TUNE_STEP_SIZE*/))
        tmp_rcc = (tmp_rcc & 0xDF) | 0x10;
    else
        tmp_rcc |= 0x30;
    status |= UncheckedSet(pInfo, MT2260_RCC_CTRL, tmp_rcc);

    /*  Read RC Calibration value  */
    status |= UncheckedGet(pInfo, MT2260_STATUS_4, &dumy);

    /* Disable RC Cal 2 */
    status |= UncheckedSet(pInfo, MT2260_RCC_CTRL, pInfo->reg[MT2260_RCC_CTRL] & 0xEF);

    /* Store RC Cal 2 value */
    pInfo->RC2_Value = pInfo->reg[MT2260_STATUS_4];

    if (pInfo->f_Ref < (36000000 /*/ TUNE_STEP_SIZE*/))
        pInfo->RC2_Nominal = (U8Data) ((pInfo->f_Ref + 77570) / 155139);
    else
        pInfo->RC2_Nominal = (U8Data) ((pInfo->f_Ref + 93077) / 186154);

    return (status);
}


/******************************************************************************
**
**  Name: Set_BBFilt
**
**  Description:    Set Base Band Filter bandwidth
**                  Based on SRO frequency & BB RC Calibration
**                  User stores channel bw as 5-8 MHz.  This routine
**                  calculates a 3 dB corner bw based on 1/2 the bandwidth
**                  and a bandwidth related constant.
**
**  Parameters:     hMT2260      - Handle to the MT2260 tuner
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_INV_HANDLE    - Invalid tuner handle
**
**  Dependencies:   mt_errordef.h - definition of error codes
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
******************************************************************************/
static UData_t Set_BBFilt(Handle_t h)
{
    UData_t f_3dB_bw;
    U8Data BBFilt = 0;
    U8Data Sel = 0;
    SData_t TmpFilt;
    SData_t i;
    UData_t status = MT_OK;                  /* Status to be returned */
    
    MT2260_Info_t* pInfo = (MT2260_Info_t*) h;

    /*  Verify that the handle passed points to a valid tuner         */
    if (IsValidHandle(pInfo) == 0)
        status |= MT_INV_HANDLE;

    /*
    ** Convert the channel bandwidth into a 3 dB bw by dividing it by 2
    ** and subtracting 300, 250, 200, or 0 kHz based on 8, 7, 6, 5 MHz
    ** channel bandwidth.
    */
    f_3dB_bw = (pInfo->f_bw / 2);  /* bw -> bw/2 */
    if (pInfo->f_bw > 7500000)
    {
        /*  >3.75 MHz corner  */
        f_3dB_bw -= 300000;
        Sel = 0x00;
        TmpFilt = ((429916107 / pInfo->RC2_Value) * pInfo->RC2_Nominal) / f_3dB_bw - 81;
    }
    else if (pInfo->f_bw > 6500000)
    {
        /*  >3.25 MHz .. 3.75 MHz corner  */
        f_3dB_bw -= 250000;
        Sel = 0x00;
        TmpFilt = ((429916107 / pInfo->RC2_Value) * pInfo->RC2_Nominal) / f_3dB_bw - 81;
    }
    else if (pInfo->f_bw > 5500000)
    {
        /*  >2.75 MHz .. 3.25 MHz corner  */
        f_3dB_bw -= 200000;
        Sel = 0x80;
        TmpFilt = ((429916107 / pInfo->RC2_Value) * pInfo->RC2_Nominal) / f_3dB_bw - 113;
    }
    else
    {
        /*  <= 2.75 MHz corner  */
        Sel = 0xC0;
        TmpFilt = ((429916107 / pInfo->RC2_Value) * pInfo->RC2_Nominal) / f_3dB_bw - 129;
    }

    if (TmpFilt > 63)
        TmpFilt = 63;
    else if (TmpFilt < 0)
        TmpFilt = 0;
    BBFilt = ((U8Data) TmpFilt) | Sel;

    for ( i = MT2260_BBFILT_1; i <= MT2260_BBFILT_8; i++ )
        pInfo->reg[i] = BBFilt;

    if (MT_NO_ERROR(status))
        status |= MT2260_WriteSub(pInfo->hUserData,
                              pInfo->address,
                              MT2260_BBFILT_1,
                              &pInfo->reg[MT2260_BBFILT_1],
                              8);

    return (status);
}

    
/****************************************************************************
**
**  Name: MT2260_GetLocked
**
**  Description:    Checks to see if the PLL is locked.
**
**  Parameters:     h            - Open handle to the tuner (from MT2260_Open).
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_DNC_UNLOCK    - Downconverter PLL unlocked
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_INV_HANDLE    - Invalid tuner handle
**
**  Dependencies:   MT2260_ReadSub    - Read byte(s) of data from the serial bus
**                  MT2260_Sleep      - Delay execution for x milliseconds
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2260_GetLocked(Handle_t h)
{
    const UData_t nMaxWait = 200;            /*  wait a maximum of 200 msec   */
    const UData_t nPollRate = 2;             /*  poll status bits every 2 ms */
    const UData_t nMaxLoops = nMaxWait / nPollRate;
    UData_t status = MT_OK;                  /* Status to be returned */
    UData_t nDelays = 0;
    U8Data statreg;
    MT2260_Info_t* pInfo = (MT2260_Info_t*) h;

    if (IsValidHandle(pInfo) == 0)
        return MT_INV_HANDLE;

    do
    {
        status |= UncheckedGet(pInfo, MT2260_STATUS_1, &statreg);

        if ((MT_IS_ERROR(status)) || ((statreg & 0x40) == 0x40))
            return (status);

        MT2260_Sleep(pInfo->hUserData, nPollRate);       /*  Wait between retries  */
    }
    while (++nDelays < nMaxLoops);

    if ((statreg & 0x40) != 0x40)
        status |= MT_DNC_UNLOCK;

    return (status);
}


/****************************************************************************
**
**  Name: MT2260_GetParam
**
**  Description:    Gets a tuning algorithm parameter.
**
**                  This function provides access to the internals of the
**                  tuning algorithm - mostly for testing purposes.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**                  param       - Tuning algorithm parameter 
**                                (see enum MT2260_Param)
**                  pValue      - ptr to returned value
**
**                  param                   Description
**                  ----------------------  --------------------------------
**                  MT2260_IC_ADDR          Serial Bus address of this tuner
**                  MT2260_MAX_OPEN         Max number of MT2260's that can be open
**                  MT2260_NUM_OPEN         Number of MT2260's currently open
**                  MT2260_NUM_REGS         Number of tuner registers
**                  MT2260_SRO_FREQ         crystal frequency
**                  MT2260_STEPSIZE         minimum tuning step size
**                  MT2260_INPUT_FREQ       input center frequency
**                  MT2260_LO_FREQ          LO Frequency
**                  MT2260_OUTPUT_BW        Output channel bandwidth
**                  MT2260_RC2_VALUE        Base band filter cal RC code (method 2)
**                  MT2260_RC2_NOMINAL      Base band filter nominal cal RC code
**                  MT2260_RF_ADC           RF attenuator A/D readback
**                  MT2260_RF_ATTN          RF attenuation (0-255)
**                  MT2260_RF_EXT           External control of RF atten
**                  MT2260_LNA_GAIN         LNA gain setting (0-15)
**                  MT2260_BB_ADC           BB attenuator A/D readback
**                  MT2260_BB_ATTN          Baseband attenuation (0-255)
**                  MT2260_BB_EXT           External control of BB atten
**
**  Usage:          status |= MT2260_GetParam(hMT2260, 
**                                            MT2260_OUTPUT_BW,
**                                            &f_bw);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_NULL      - Null pointer argument passed
**                      MT_ARG_RANGE     - Invalid parameter requested
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
**
**  See Also:       MT2260_SetParam, MT2260_Open
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2260_GetParam(Handle_t     h,
                        MT2260_Param param,
                        UData_t*     pValue)
{
    UData_t status = MT_OK;                  /* Status to be returned        */
    U8Data tmp;
    MT2260_Info_t* pInfo = (MT2260_Info_t*) h;

    if (pValue == NULL)
        status |= MT_ARG_NULL;

    /*  Verify that the handle passed points to a valid tuner         */
    if (IsValidHandle(pInfo) == 0)
        status |= MT_INV_HANDLE;

    if (MT_NO_ERROR(status))
    {
        switch (param)
        {
        /*  Serial Bus address of this tuner      */
        case MT2260_IC_ADDR:
            *pValue = pInfo->address;
            break;

        /*  Max # of MT2260's allowed to be open  */
        case MT2260_MAX_OPEN:
            *pValue = nMaxTuners;
            break;

        /*  # of MT2260's open                    */
        case MT2260_NUM_OPEN:
            *pValue = nOpenTuners;
            break;

        /*  Number of tuner registers             */
        case MT2260_NUM_REGS:
            *pValue = Num_Registers;
            break;

        /*  crystal frequency                     */
        case MT2260_SRO_FREQ:
            *pValue = pInfo->f_Ref;
            break;

        /*  minimum tuning step size              */
        case MT2260_STEPSIZE:
            *pValue = pInfo->f_Step;
            break;

        /*  input center frequency                */
        case MT2260_INPUT_FREQ:
            *pValue = pInfo->f_in;
            break;

        /*  LO Frequency                          */
        case MT2260_LO_FREQ:
            *pValue = pInfo->f_LO;
            break;

        /*  Output Channel Bandwidth              */
        case MT2260_OUTPUT_BW:
            *pValue = pInfo->f_bw;
            break;

        /*  Base band filter cal RC code          */
        case MT2260_RC2_VALUE:
            *pValue = (UData_t) pInfo->RC2_Value;
            break;

        /*  Base band filter nominal cal RC code          */
        case MT2260_RC2_NOMINAL:
            *pValue = (UData_t) pInfo->RC2_Nominal;
            break;

        /*  RF attenuator A/D readback            */
        case MT2260_RF_ADC:
            status |= UncheckedGet(pInfo, MT2260_STATUS_2, &tmp);
            if (MT_NO_ERROR(status))
                *pValue = (UData_t) tmp;
            break;

        /*  BB attenuator A/D readback            */
        case MT2260_BB_ADC:
            status |= UncheckedGet(pInfo, MT2260_STATUS_3, &tmp);
            if (MT_NO_ERROR(status))
                *pValue = (UData_t) tmp;
            break;

        /*  RF attenuator setting                 */
        case MT2260_RF_ATTN:
            PREFETCH(MT2260_RSVD_1F, 1);  /* Fetch register(s) if __NO_CACHE__ defined */
            if (MT_NO_ERROR(status))
                *pValue = pInfo->reg[MT2260_RSVD_1F];
            break;

        /*  BB attenuator setting                 */
        case MT2260_BB_ATTN:
            PREFETCH(MT2260_RSVD_2C, 3);  /* Fetch register(s) if __NO_CACHE__ defined */
            *pValue = pInfo->reg[MT2260_RSVD_2C]
                    + pInfo->reg[MT2260_RSVD_2D]
                    + pInfo->reg[MT2260_RSVD_2E] - 3;
            break;

        /*  RF external / internal atten control  */
        case MT2260_RF_EXT:
            PREFETCH(MT2260_GPO, 1);  /* Fetch register(s) if __NO_CACHE__ defined */
            *pValue = ((pInfo->reg[MT2260_GPO] & 0x40) != 0x00);
            break;

        /*  BB external / internal atten control  */
        case MT2260_BB_EXT:
            PREFETCH(MT2260_RSVD_33, 1);  /* Fetch register(s) if __NO_CACHE__ defined */
            *pValue = ((pInfo->reg[MT2260_RSVD_33] & 0x10) != 0x00);
            break;

        /*  LNA gain setting (0-15)               */
        case MT2260_LNA_GAIN:
            PREFETCH(MT2260_IGAIN, 1);  /* Fetch register(s) if __NO_CACHE__ defined */
            *pValue = ((pInfo->reg[MT2260_IGAIN] & 0x3C) >> 2);
            break;

        case MT2260_EOP:
        default:
            status |= MT_ARG_RANGE;
        }
    }
    return (status);
}


/****************************************************************************
**  LOCAL FUNCTION - DO NOT USE OUTSIDE OF mt2260.c
**
**  Name: UncheckedGet
**
**  Description:    Gets an MT2260 register with minimal checking
**
**                  NOTE: This is a local function that performs the same
**                  steps as the MT2260_GetReg function that is available
**                  in the external API.  It does not do any of the standard
**                  error checking that the API function provides and should
**                  not be called from outside this file.
**
**  Parameters:     *pInfo      - Tuner control structure
**                  reg         - MT2260 register/subaddress location
**                  *val        - MT2260 register/subaddress value
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_NULL      - Null pointer argument passed
**                      MT_ARG_RANGE     - Argument out of range
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
**
**                  Use this function if you need to read a register from
**                  the MT2260.
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
static UData_t UncheckedGet(MT2260_Info_t* pInfo,
                            U8Data   reg,
                            U8Data*  val)
{
    UData_t status;                  /* Status to be returned        */

#if defined(_DEBUG)
    status = MT_OK;
    /*  Verify that the handle passed points to a valid tuner         */
    if (IsValidHandle(pInfo) == 0)
        status |= MT_INV_HANDLE;
    
    if (val == NULL)
        status |= MT_ARG_NULL;

    if (reg >= END_REGS)
        status |= MT_ARG_RANGE;

    if (MT_IS_ERROR(status))
        return(status);
#endif

    status = MT2260_ReadSub(pInfo->hUserData, pInfo->address, reg, &pInfo->reg[reg], 1);

    if (MT_NO_ERROR(status))
        *val = pInfo->reg[reg];

    return (status);
}


/****************************************************************************
**
**  Name: MT2260_GetReg
**
**  Description:    Gets an MT2260 register.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**                  reg         - MT2260 register/subaddress location
**                  *val        - MT2260 register/subaddress value
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_NULL      - Null pointer argument passed
**                      MT_ARG_RANGE     - Argument out of range
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
**
**                  Use this function if you need to read a register from
**                  the MT2260.
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2260_GetReg(Handle_t h,
                      U8Data   reg,
                      U8Data*  val)
{
    UData_t status = MT_OK;                  /* Status to be returned        */
    MT2260_Info_t* pInfo = (MT2260_Info_t*) h;

    /*  Verify that the handle passed points to a valid tuner         */
    if (IsValidHandle(pInfo) == 0)
        status |= MT_INV_HANDLE;
    
    if (val == NULL)
        status |= MT_ARG_NULL;

    if (reg >= END_REGS)
        status |= MT_ARG_RANGE;

    if (MT_NO_ERROR(status))
        status |= UncheckedGet(pInfo, reg, val);

    return (status);
}


/****************************************************************************
**
**  Name: MT2260_GetUserData
**
**  Description:    Gets the user-defined data item.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_NULL      - Null pointer argument passed
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
**
**                  The hUserData parameter is a user-specific argument
**                  that is stored internally with the other tuner-
**                  specific information.
**
**                  For example, if additional arguments are needed
**                  for the user to identify the device communicating
**                  with the tuner, this argument can be used to supply
**                  the necessary information.
**
**                  The hUserData parameter is initialized in the tuner's
**                  Open function to NULL.
**
**  See Also:       MT2260_SetUserData, MT2260_Open
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2260_GetUserData(Handle_t h,
                           Handle_t* hUserData)
{
    UData_t status = MT_OK;                  /* Status to be returned        */
    MT2260_Info_t* pInfo = (MT2260_Info_t*) h;

    /*  Verify that the handle passed points to a valid tuner         */
    if (IsValidHandle(pInfo) == 0)
        status = MT_INV_HANDLE;

    if (hUserData == NULL)
        status |= MT_ARG_NULL;

    if (MT_NO_ERROR(status))
        *hUserData = pInfo->hUserData;

    return (status);
}


/******************************************************************************
**
**  Name: MT2260_ReInit
**
**  Description:    Initialize the tuner's register values.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**
**  Returns:        status:
**                      MT_OK             - No errors
**                      MT_TUNER_ID_ERR   - Tuner Part/Rev code mismatch
**                      MT_TUNER_INIT_ERR - Tuner initialization failed
**                      MT_INV_HANDLE     - Invalid tuner handle
**                      MT_COMM_ERR       - Serial bus communications error
**
**  Dependencies:   MT2260_ReadSub  - Read byte(s) of data from the two-wire bus
**                  MT2260_WriteSub - Write byte(s) of data to the two-wire bus
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
******************************************************************************/
UData_t MT2260_ReInit(Handle_t h)
{
    U8Data MT2260_Init_Defaults1[] =
    {
        0x01,            /* Start w/register 0x01 */
        0x00,            /* Reg 0x01 */
        0x00,            /* Reg 0x02 */
        0x28,            /* Reg 0x03 */
        0x00,            /* Reg 0x04 */
        0x52,            /* Reg 0x05 */
        0x99,            /* Reg 0x06 */
        0x3F,            /* Reg 0x07 */
    };

    U8Data MT2260_Init_Defaults2[] = 
    {
        0x17,            /* Start w/register 0x17 */
        0x6D,            /* Reg 0x17 */
        0x71,            /* Reg 0x18 */
        0x61,            /* Reg 0x19 */
        0xC0,            /* Reg 0x1A */
        0xBF,            /* Reg 0x1B */
        0xFF,            /* Reg 0x1C */
        0xDC,            /* Reg 0x1D */
        0x00,            /* Reg 0x1E */
        0x0A,            /* Reg 0x1F */
        0xD4,            /* Reg 0x20 */
        0x03,            /* Reg 0x21 */
        0x64,            /* Reg 0x22 */
        0x64,            /* Reg 0x23 */
        0x64,            /* Reg 0x24 */
        0x64,            /* Reg 0x25 */
        0x22,            /* Reg 0x26 */
        0xAA,            /* Reg 0x27 */
        0xF2,            /* Reg 0x28 */
        0x1E,            /* Reg 0x29 */
        0x80,            /* Reg 0x2A */
        0x14,            /* Reg 0x2B */
        0x01,            /* Reg 0x2C */
        0x01,            /* Reg 0x2D */
        0x01,            /* Reg 0x2E */
        0x01,            /* Reg 0x2F */
        0x01,            /* Reg 0x30 */
        0x01,            /* Reg 0x31 */
        0x7F,            /* Reg 0x32 */
        0x5E,            /* Reg 0x33 */
        0x3F,            /* Reg 0x34 */
        0xFF,            /* Reg 0x35 */
        0xFF,            /* Reg 0x36 */
        0xFF,            /* Reg 0x37 */
        0x00,            /* Reg 0x38 */
        0x77,            /* Reg 0x39 */
        0x0F,            /* Reg 0x3A */
        0x2D,            /* Reg 0x3B */
    };

    UData_t status = MT_OK;                  /* Status to be returned        */
    MT2260_Info_t* pInfo = (MT2260_Info_t*) h;
    U8Data BBVref;
    U8Data tmpreg = 0;
    U8Data fusereg = 0;

    /*  Verify that the handle passed points to a valid tuner         */
    if (IsValidHandle(pInfo) == 0)
        status |= MT_INV_HANDLE;

    /*  Read the Part/Rev code from the tuner */
    if (MT_NO_ERROR(status))
        status |= UncheckedGet(pInfo, MT2260_PART_REV, &tmpreg);

    /*  MT2260 B0  */
    if (MT_NO_ERROR(status) && (tmpreg != 0x85))
        status |= MT_TUNER_ID_ERR;      /*  Wrong tuner Part/Rev code   */

    if (MT_NO_ERROR(status))
    {
        /*  Initialize the tuner state.  Hold off on f_in and f_LO */
        pInfo->version = VERSION;
        pInfo->tuner_id = pInfo->reg[MT2260_PART_REV];
        pInfo->f_Ref = REF_FREQ;
        pInfo->f_Step = TUNE_STEP_SIZE * 1000;  /* kHz -> Hz */
        pInfo->f_in = UHF_DEFAULT_FREQ;
        pInfo->f_LO = UHF_DEFAULT_FREQ;
        pInfo->f_bw = OUTPUT_BW;
        pInfo->band = MT2260_UHF_BAND;
        pInfo->num_regs = END_REGS;

        /*  Write the default values to the tuner registers. Default mode is UHF */
        status |= MT2260_WriteSub(pInfo->hUserData, 
                              pInfo->address, 
                              MT2260_Init_Defaults1[0], 
                              &MT2260_Init_Defaults1[1], 
                              sizeof(MT2260_Init_Defaults1)/sizeof(U8Data)-1);
                        
        if (MT_NO_ERROR(status))
        {
            status |= MT2260_WriteSub(pInfo->hUserData, 
                                  pInfo->address, 
                                  MT2260_Init_Defaults2[0], 
                                  &MT2260_Init_Defaults2[1], 
                                  sizeof(MT2260_Init_Defaults2)/sizeof(U8Data)-1);
        }
    }

    /*  Read back all the registers from the tuner */
    if (MT_NO_ERROR(status))
    {
        status |= MT2260_ReadSub(pInfo->hUserData, pInfo->address, 0, &pInfo->reg[0], END_REGS);
    }

    /*
    **  Read the FUSE registers and set BBVref[0x33]  accordingly
    */
    tmpreg = pInfo->reg[MT2260_RSVD_11] |= 0x03;  /* FUSEen=1, FUSErd=1 */
    if (MT_NO_ERROR(status))
        status |= UncheckedSet(pInfo, MT2260_RSVD_11, tmpreg);
    tmpreg &= ~(0x02);  /* FUSErd=0 */
    if (MT_NO_ERROR(status))
        status |= UncheckedSet(pInfo, MT2260_RSVD_11, tmpreg);

    /*  Get and store the fuse register value  */
    if (MT_NO_ERROR(status))
        status |= UncheckedGet(pInfo, MT2260_STATUS_5, &fusereg);

    /*  Use fuse register value to set BBVref  */
    if (MT_NO_ERROR(status))
    {
        BBVref = (((fusereg >> 6) + 2) & 0x03);
        tmpreg = (pInfo->reg[MT2260_RSVD_33] & ~(0x60)) | (BBVref << 5);
        status |= UncheckedSet(pInfo, MT2260_RSVD_33, tmpreg);
    }

    if (MT_NO_ERROR(status))
        status |= Run_BB_RC_Cal2(h);

    if (MT_NO_ERROR(status))
        status |= Set_BBFilt(h);

    return (status);
}


/****************************************************************************
**
**  Name: MT2260_SetParam
**
**  Description:    Sets a tuning algorithm parameter.
**
**                  This function provides access to the internals of the
**                  tuning algorithm.  You can override many of the tuning
**                  algorithm defaults using this function.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**                  param       - Tuning algorithm parameter 
**                                (see enum MT2260_Param)
**                  nValue      - value to be set
**
**                  param                   Description
**                  ----------------------  --------------------------------
**                  MT2260_SRO_FREQ         crystal frequency                   
**                  MT2260_STEPSIZE         minimum tuning step size            
**                  MT2260_INPUT_FREQ       Center of input channel             
**                  MT2260_OUTPUT_BW        Output channel bandwidth
**                  MT2260_RF_ATTN          RF attenuation (0-255)
**                  MT2260_RF_EXT           External control of RF atten
**                  MT2260_LNA_GAIN         LNA gain setting (0-15)
**                  MT2260_LNA_GAIN_DECR    Decrement LNA Gain (arg=min)
**                  MT2260_LNA_GAIN_INCR    Increment LNA Gain (arg=max)
**                  MT2260_BB_ATTN          Baseband attenuation (0-255)
**                  MT2260_BB_EXT           External control of BB atten
**                  MT2260_UHF_MAXSENS      Set for UHF max sensitivity mode
**                  MT2260_UHF_NORMAL       Set for UHF normal mode
**
**  Usage:          status |= MT2260_SetParam(hMT2260, 
**                                            MT2260_STEPSIZE,
**                                            50000);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_RANGE     - Invalid parameter requested
**                                         or set value out of range
**                                         or non-writable parameter
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
**
**  See Also:       MT2260_GetParam, MT2260_Open
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**   N/A   04-26-2006    DAD    Ver 1.01: Add support for 8-38.4 MHz crystals
**
****************************************************************************/
UData_t MT2260_SetParam(Handle_t     h,
                        MT2260_Param param,
                        UData_t      nValue)
{
    UData_t status = MT_OK;                  /* Status to be returned        */
    U8Data tmpreg;
    MT2260_Info_t* pInfo = (MT2260_Info_t*) h;

    /*  Verify that the handle passed points to a valid tuner         */
    if (IsValidHandle(pInfo) == 0)
        status |= MT_INV_HANDLE;

    if (MT_NO_ERROR(status))
    {
        switch (param)
        {
        /*  crystal frequency                     */
        case MT2260_SRO_FREQ:
            pInfo->f_Ref = nValue;
            if (pInfo->f_Ref < 22000000)
            {
                /*  Turn off f_SRO divide by 2  */
                status |= UncheckedSet(pInfo, 
                                       MT2260_SRO_CTRL, 
                                       (U8Data) (pInfo->reg[MT2260_SRO_CTRL] &= 0xFE));
            }
            else
            {
                /*  Turn on f_SRO divide by 2  */
                status |= UncheckedSet(pInfo, 
                                       MT2260_SRO_CTRL, 
                                       (U8Data) (pInfo->reg[MT2260_SRO_CTRL] |= 0x01));
            }
            status |= Run_BB_RC_Cal2(h);
            if (MT_NO_ERROR(status))
                status |= Set_BBFilt(h);
            break;

        /*  minimum tuning step size              */
        case MT2260_STEPSIZE:
            pInfo->f_Step = nValue;
            break;

        /*  Width of output channel               */
        case MT2260_OUTPUT_BW:
            pInfo->f_bw = nValue;
            status |= Set_BBFilt(h);
            break;

        /*  BB attenuation (0-255)                */
        case MT2260_BB_ATTN:
            if (nValue > 255)
                status |= MT_ARG_RANGE;
            else
            {
                UData_t BBA_Stage1;
                UData_t BBA_Stage2;
                UData_t BBA_Stage3;

                BBA_Stage3 = (nValue > 102) ? 103 : nValue + 1;
                BBA_Stage2 = (nValue > 175) ? 75 : nValue + 2 - BBA_Stage3;
                BBA_Stage1 = (nValue > 176) ? nValue - 175 : 1;
                pInfo->reg[MT2260_RSVD_2C] = (U8Data) BBA_Stage1;
                pInfo->reg[MT2260_RSVD_2D] = (U8Data) BBA_Stage2;
                pInfo->reg[MT2260_RSVD_2E] = (U8Data) BBA_Stage3;
                pInfo->reg[MT2260_RSVD_2F] = (U8Data) BBA_Stage1;
                pInfo->reg[MT2260_RSVD_30] = (U8Data) BBA_Stage2;
                pInfo->reg[MT2260_RSVD_31] = (U8Data) BBA_Stage3;
                status |= MT2260_WriteSub(pInfo->hUserData, 
                                      pInfo->address, 
                                      MT2260_RSVD_2C, 
                                      &pInfo->reg[MT2260_RSVD_2C], 
                                      6);
            }
            break;

        /*  RF attenuation (0-255)                */
        case MT2260_RF_ATTN:
            if (nValue > 255)
                status |= MT_ARG_RANGE;
            else
                status |= UncheckedSet(pInfo, MT2260_RSVD_1F, (U8Data) nValue);
            break;

        /*  RF external / internal atten control  */
        case MT2260_RF_EXT:
            if (nValue == 0)
                tmpreg = pInfo->reg[MT2260_GPO] &= ~0x40;
            else
                tmpreg = pInfo->reg[MT2260_GPO] |= 0x40;
            status |= UncheckedSet(pInfo, MT2260_GPO, tmpreg);
            break;

        /*  LNA gain setting (0-15)               */
        case MT2260_LNA_GAIN:
            if (nValue > 15)
                status |= MT_ARG_RANGE;
            else
            {
                tmpreg = (pInfo->reg[MT2260_IGAIN] & 0xC3) | ((U8Data)nValue << 2);
                status |= UncheckedSet(pInfo, MT2260_IGAIN, tmpreg);
            }
            break;

        /*  Decrement LNA Gain setting, argument is min LNA Gain setting  */
        case MT2260_LNA_GAIN_DECR:
            if (nValue > 15)
                status |= MT_ARG_RANGE;
            else
            {
                PREFETCH(MT2260_IGAIN, 1);
                if (MT_NO_ERROR(status) && ((U8Data) ((pInfo->reg[MT2260_IGAIN] & 0x3C) >> 2) > (U8Data) nValue))
                    status |= UncheckedSet(pInfo, MT2260_IGAIN, pInfo->reg[MT2260_IGAIN] - 0x04);
            }
            break;

        /*  Increment LNA Gain setting, argument is max LNA Gain setting  */
        case MT2260_LNA_GAIN_INCR:
            if (nValue > 15)
                status |= MT_ARG_RANGE;
            else
            {
                PREFETCH(MT2260_IGAIN, 1);
                if (MT_NO_ERROR(status) && ((U8Data) ((pInfo->reg[MT2260_IGAIN] & 0x3C) >> 2) < (U8Data) nValue))
                    status |= UncheckedSet(pInfo, MT2260_IGAIN, pInfo->reg[MT2260_IGAIN] + 0x04);
            }
            break;

        /* BB external / internal atten control  */
        case MT2260_BB_EXT:
            if (nValue == 0)
                /* tmpreg = pInfo->reg[MT2260_RSVD_33] &= ~0x08; */
                tmpreg = pInfo->reg[MT2260_RSVD_33] &= ~0x10;
            else
                /* tmpreg = pInfo->reg[MT2260_RSVD_33] |= 0x08; */
                tmpreg = pInfo->reg[MT2260_RSVD_33] |= 0x10;
            status |= UncheckedSet(pInfo, MT2260_RSVD_33, tmpreg);
            break;

        /*  Set for UHF max sensitivity mode  */
        case MT2260_UHF_MAXSENS:
            PREFETCH(MT2260_BAND_CTRL, 1);
            if (MT_NO_ERROR(status) && ((pInfo->reg[MT2260_BAND_CTRL] ^ 0x30) == 0x10))
                status |= UncheckedSet(pInfo, MT2260_BAND_CTRL, pInfo->reg[MT2260_BAND_CTRL] ^ 0x30);
            break;

        /*  Set for UHF normal mode  */
        case MT2260_UHF_NORMAL:
            if (MT_NO_ERROR(status) && ((pInfo->reg[MT2260_BAND_CTRL] ^ 0x30) == 0x20))
                status |= UncheckedSet(pInfo, MT2260_BAND_CTRL, pInfo->reg[MT2260_BAND_CTRL] ^ 0x30);
            break;

        /*  These parameters are read-only  */
        case MT2260_IC_ADDR:
        case MT2260_MAX_OPEN:
        case MT2260_NUM_OPEN:
        case MT2260_NUM_REGS:
        case MT2260_INPUT_FREQ:
        case MT2260_LO_FREQ:
        case MT2260_RC2_VALUE:
        case MT2260_RF_ADC:
        case MT2260_BB_ADC:
        case MT2260_EOP:
        default:
            status |= MT_ARG_RANGE;
        }
    }
    return (status);
}


/****************************************************************************
**
**  Name: MT2260_SetPowerModes
**
**  Description:    Sets the bits in the MT2260_ENABLES register and the
**                  SROsd bit in the MT2260_SROADC_CTRL register.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**                  flags       - Bit mask of flags to indicate enabled
**                                bits.
**
**  Usage:          status = MT2260_SetPowerModes(hMT2260, flags);
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
**
**                  The bits in the MT2260_ENABLES register and the
**                  SROsd bit are set according to the supplied flags.
**
**                  The pre-defined flags are as follows:
**                      MT2260_SROen
**                      MT2260_LOen
**                      MT2260_ADCen
**                      MT2260_PDen
**                      MT2260_DCOCen
**                      MT2260_BBen
**                      MT2260_MIXen
**                      MT2260_LNAen
**                      MT2260_ALL_ENABLES
**                      MT2260_NO_ENABLES
**                      MT2260_SROsd
**                      MT2260_SRO_NOT_sd
**
**                  ONLY the enable bits (or SROsd bit) specified in the
**                  flags parameter will be set.  Any flag which is not
**                  included, will cause that bit to be disabled.
**
**                  The ALL_ENABLES, NO_ENABLES, and SRO_NOT_sd constants
**                  are for convenience.  The NO_ENABLES and SRO_NOT_sd
**                  do not actually have to be included, but are provided
**                  for clarity.
**
**  See Also:       MT2260_Open
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2260_SetPowerModes(Handle_t h,
                             UData_t  flags)
{
    UData_t status = MT_OK;                  /* Status to be returned */
    MT2260_Info_t* pInfo = (MT2260_Info_t*) h;
    U8Data tmpreg;

    /*  Verify that the handle passed points to a valid tuner */
    if (IsValidHandle(pInfo) == 0)
        status |= MT_INV_HANDLE;

    PREFETCH(MT2260_SRO_CTRL, 1);  /* Fetch register(s) if __NO_CACHE__ defined */
    if (MT_NO_ERROR(status))
    {
        if (flags & MT2260_SROsd)
            tmpreg = pInfo->reg[MT2260_SRO_CTRL] |= 0x10;  /* set the SROsd bit */
        else
            tmpreg = pInfo->reg[MT2260_SRO_CTRL] &= 0xEF;  /* clear the SROsd bit */
        status |= UncheckedSet(pInfo, MT2260_SRO_CTRL, tmpreg);
    }

    PREFETCH(MT2260_ENABLES, 1);  /* Fetch register(s) if __NO_CACHE__ defined */

    if (MT_NO_ERROR(status))
    {
        status |= UncheckedSet(pInfo, MT2260_ENABLES, (U8Data)(flags & 0xff));
    }

    return status;
}


/****************************************************************************
**  LOCAL FUNCTION - DO NOT USE OUTSIDE OF mt2260.c
**
**  Name: UncheckedSet
**
**  Description:    Sets an MT2260 register.
**
**                  NOTE: This is a local function that performs the same
**                  steps as the MT2260_SetReg function that is available
**                  in the external API.  It does not do any of the standard
**                  error checking that the API function provides and should
**                  not be called from outside this file.
**
**  Parameters:     *pInfo      - Tuner control structure
**                  reg         - MT2260 register/subaddress location
**                  val         - MT2260 register/subaddress value
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_RANGE     - Argument out of range
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
**
**                  Sets a register value without any preliminary checking for
**                  valid handles or register numbers.
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
static UData_t UncheckedSet(MT2260_Info_t* pInfo,
                            U8Data         reg,
                            U8Data         val)
{
    UData_t status;                  /* Status to be returned */

#if defined(_DEBUG)
    status = MT_OK;
    /*  Verify that the handle passed points to a valid tuner         */
    if (IsValidHandle(pInfo) == 0)
        status |= MT_INV_HANDLE;

    if (reg >= END_REGS)
        status |= MT_ARG_RANGE;

    if (MT_IS_ERROR(status))
        return (status);
#endif

    status = MT2260_WriteSub(pInfo->hUserData, pInfo->address, reg, &val, 1);

    if (MT_NO_ERROR(status))
        pInfo->reg[reg] = val;

    return (status);
}


/****************************************************************************
**
**  Name: MT2260_SetReg
**
**  Description:    Sets an MT2260 register.
**
**  Parameters:     h           - Tuner handle (returned by MT2260_Open)
**                  reg         - MT2260 register/subaddress location
**                  val         - MT2260 register/subaddress value
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_ARG_RANGE     - Argument out of range
**
**  Dependencies:   USERS MUST CALL MT2260_Open() FIRST!
**
**                  Use this function if you need to override a default
**                  register value
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**
****************************************************************************/
UData_t MT2260_SetReg(Handle_t h,
                      U8Data   reg,
                      U8Data   val)
{
    UData_t status = MT_OK;                  /* Status to be returned */
    MT2260_Info_t* pInfo = (MT2260_Info_t*) h;

    /*  Verify that the handle passed points to a valid tuner         */
    if (IsValidHandle(pInfo) == 0)
        status |= MT_INV_HANDLE;

    if (reg >= END_REGS)
        status |= MT_ARG_RANGE;

    if (MT_NO_ERROR(status))
        status |= UncheckedSet(pInfo, reg, val);

    return (status);
}


/****************************************************************************
** LOCAL FUNCTION
**
**  Name: RoundToStep
**
**  Description:    Rounds the given frequency to the closes f_Step value
**                  given the tuner ref frequency..
**
**
**  Parameters:     freq      - Frequency to be rounded (in Hz).
**                  f_Step    - Step size for the frequency (in Hz).
**                  f_Ref     - SRO frequency (in Hz).
**
**  Returns:        Rounded frequency.
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-01-2006    JWS    Original
**
****************************************************************************/
static UData_t RoundToStep(UData_t freq, UData_t f_Step, UData_t f_ref)
{
    return f_ref * (freq / f_ref)
        + f_Step * (((freq % f_ref) + (f_Step / 2)) / f_Step);
}


/****************************************************************************
** LOCAL FUNCTION
**
**  Name: CalcLOMult
**
**  Description:    Calculates Integer divider value and the numerator
**                  value for LO's FracN PLL.
**
**                  This function assumes that the f_LO and f_Ref are
**                  evenly divisible by f_LO_Step.
**
**  Parameters:     Div       - OUTPUT: Whole number portion of the multiplier
**                  FracN     - OUTPUT: Fractional portion of the multiplier
**                  f_LO      - desired LO frequency.
**                  denom     - LO FracN denominator value
**                  f_Ref     - SRO frequency.
**
**  Returns:        Recalculated LO frequency.
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-01-2006    JWS    Original
**
****************************************************************************/
static UData_t CalcLOMult(UData_t *Div,
                          UData_t *FracN,
                          UData_t  f_LO,
                          UData_t  denom,
                          UData_t  f_Ref)
{
    UData_t a, b, i;
	const SData_t TwoNShift = 13;   /* bits to shift to obtain 2^n qty */
    const SData_t RoundShift = 18;  /* bits to shift before rounding */
    const UData_t FracN_Scale = (f_Ref / (MAX_UDATA >> TwoNShift)) + 1;

    /*  Calculate the whole number portion of the divider */
    *Div = f_LO / f_Ref;

    /*
    **  Calculate the FracN numerator 1 bit at a time.  This keeps the
    **  integer values from overflowing when large values are multiplied.
    **  This loop calculates the fractional portion of F/20MHz accurate
    **  to 32 bits.  The 2^n factor is represented by the placement of
    **  the value in the 32-bit word.  Since we want as much accuracy
    **  as possible, we'll leave it at the top of the word.
    */
    *FracN = 0;
    a = f_LO;
    for (i=32; i>0; --i)
    {
        b = 2*(a % f_Ref);
        *FracN = (*FracN * 2) + (b >= f_Ref);
        a = b;
    }

    /*
    **  If the denominator is a 2^n - 1 value (the usual case) then the
    **  value we really need is (F/20) * 2^n - (F/20).  Shifting the
    **  calculated (F/20) value to the right and subtracting produces
    **  the desired result -- still accurate to 32 bits.
    */
    if ((denom & 0x01) != 0)
        *FracN -= (*FracN >> TwoNShift);

    /*
    ** Now shift the result so that it is 1 bit bigger than we need,
    ** use the low-order bit to round the remaining bits, and shift
    ** to make the answer the desired size.
    */
    *FracN >>= RoundShift;
    *FracN = (*FracN & 0x01) + (*FracN >> 1);

    /*  Check for rollover (cannot happen with 50 kHz step size) */
    if (*FracN == (denom | 1))
    {
        *FracN = 0;
        ++Div;
    }


    return (f_Ref * (*Div))
         + FracN_Scale * (((f_Ref / FracN_Scale) * (*FracN)) / denom);
}


/****************************************************************************
**
**  Name: MT2260_ChangeFreq
**
**  Description:    Change the tuner's tuned frequency to f_in.
**
**  Parameters:     h           - Open handle to the tuner (from MT2260_Open).
**                  f_in        - RF input center frequency (in Hz).
**
**  Returns:        status:
**                      MT_OK            - No errors
**                      MT_INV_HANDLE    - Invalid tuner handle
**                      MT_DNC_UNLOCK    - Downconverter PLL unlocked
**                      MT_COMM_ERR      - Serial bus communications error
**                      MT_FIN_RANGE     - Input freq out of range
**                      MT_DNC_RANGE     - Downconverter freq out of range
**
**  Dependencies:   MUST CALL MT2260_Open BEFORE MT2260_ChangeFreq!
**
**                  MT2260_ReadSub       - Read byte(s) of data from the two-wire-bus
**                  MT2260_WriteSub      - Write byte(s) of data to the two-wire-bus
**                  MT2260_Sleep         - Delay execution for x milliseconds
**                  MT2260_GetLocked - Checks to see if the PLL is locked
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   02-03-2006   DAD/JWS Original.
**   N/A   04-26-2006    DAD    Ver 1.01: Add support for 8-38.4 MHz crystals
**
****************************************************************************/
UData_t MT2260_ChangeFreq(Handle_t h,
                          UData_t f_in)     /* RF input center frequency   */
{
    MT2260_Info_t* pInfo = (MT2260_Info_t*) h;

    UData_t status = MT_OK;       /*  status of operation             */
    UData_t LO;                   /*  LO register value               */
    UData_t Num;                  /*  Numerator for LO reg. value     */
    UData_t ofLO;                 /*  last time's LO frequency        */
    UData_t ofin;                 /*  last time's input frequency     */
    U8Data  LO_Band;              /*  LO Mode bits                    */
    UData_t s_fRef;               /*  Ref Freq scaled for LO Band     */
    UData_t this_band;            /*  Band for the requested freq     */
    UData_t SROx2;                /*  SRO times 2                     */

    /*  Verify that the handle passed points to a valid tuner         */
    if (IsValidHandle(pInfo) == 0)
        return MT_INV_HANDLE;

    /*
    **  Save original input and LO value
    */
    ofLO = pInfo->f_LO;
    ofin = pInfo->f_in;

    /*
    **  Assign in the requested input value
    */
    pInfo->f_in = f_in;

    /*
    **  Get the SRO multiplier value
    */
    SROx2 = (2 - (pInfo->reg[MT2260_SRO_CTRL] & 0x01));

    /*  Request an LO that is on a step size boundary  */
    pInfo->f_LO = RoundToStep(f_in, pInfo->f_Step, pInfo->f_Ref);

        if (pInfo->f_LO < MIN_UHF_FREQ)
        {
            status |= MT_FIN_RANGE | MT_ARG_RANGE | MT_DNC_RANGE;
            return status;  /* Does not support frequencies below MIN_UHF_FREQ  */
        }
        else if (pInfo->f_LO <= MAX_UHF_FREQ)
        {
            /*  UHF Band  */
            s_fRef = pInfo->f_Ref * SROx2 / 2;
            LO_Band = 1;
            this_band = MT2260_UHF_BAND;
        }
        else
        {
            /*  L-Band  */
            s_fRef = pInfo->f_Ref * SROx2;
            LO_Band = 3;
            this_band = MT2260_L_BAND;

            /*
            **  Check the LO frequency range
            */
            if ((pInfo->f_LO < MIN_LBAND_FREQ) || (pInfo->f_LO > MAX_LBAND_FREQ))
                status |= MT_FIN_RANGE | MT_DNC_RANGE;
        }

    /*
    ** Calculate the LO frequencies and the values to be placed
    ** in the tuning registers.
    */
    pInfo->f_LO = CalcLOMult(&LO, &Num, pInfo->f_LO, 8191, s_fRef);

    /*
    **  If we have the same LO frequencies and we're already locked,
    **  then just return without writing any registers.
    */
    if ((ofLO == pInfo->f_LO) 
        && ((pInfo->reg[MT2260_STATUS_1] & 0x40) == 0x40))
    {
        return (status);
    }

    /*
    ** Reset defaults here if we're tuning into a new band
    */
    if (MT_NO_ERROR(status))
    {
        if (this_band != pInfo->band)
        {
            MT2260_DefaultsEntry *defaults = NULL;
            switch (this_band)
            {
                case MT2260_L_BAND:
                    defaults = &MT2260_LBAND_defaults[0];
                    break;
                case MT2260_UHF_BAND:
                    defaults = &MT2260_UHF_defaults[0];
                    break;
                default:
                    status |= MT_ARG_RANGE;
            }
            if ( MT_NO_ERROR(status))
            {
                while (defaults->data && MT_NO_ERROR(status))
                {
                    status |= MT2260_WriteSub(pInfo->hUserData, pInfo->address, defaults->data[0], &defaults->data[1], defaults->cnt);
                    defaults++;
                }
                /* re-read the new registers into the cached values */
                status |= MT2260_ReadSub(pInfo->hUserData, pInfo->address, 0, &pInfo->reg[0], END_REGS);
                pInfo->band = this_band;
            }
        }
    }

    /*
    **  Place all of the calculated values into the local tuner
    **  register fields.
    */
    if (MT_NO_ERROR(status))
    {
        pInfo->reg[MT2260_LO_CTRL_1] = (U8Data)(Num >> 8);
        pInfo->reg[MT2260_LO_CTRL_2] = (U8Data)(Num & 0xFF);
        pInfo->reg[MT2260_LO_CTRL_3] = (U8Data)(LO & 0xFF);

        /*
        ** Now write out the computed register values
        */
        status |= MT2260_WriteSub(pInfo->hUserData, pInfo->address, MT2260_LO_CTRL_1, &pInfo->reg[MT2260_LO_CTRL_1], 3);

        if (pInfo->band == MT2260_UHF_BAND)
        {
            U8Data CapSel = 0;                        /*  def when f_in > all    */
            U8Data idx;
            UData_t* XFreq;
            SData_t ClearTune_Fuse;
            SData_t f_offset;
            UData_t f_in_;

            PREFETCH(MT2260_BAND_CTRL, 2);  /* Fetch register(s) if __NO_CACHE__ defined */
            PREFETCH(MT2260_STATUS_5, 1);  /* Fetch register(s) if __NO_CACHE__ defined */

            XFreq = (pInfo->reg[MT2260_BAND_CTRL] & 0x10) ? MT2260_UHFA_XFreq : MT2260_UHF_XFreq;
            ClearTune_Fuse = pInfo->reg[MT2260_STATUS_5] & 0x07;
            f_offset = (10000000) * ((ClearTune_Fuse > 3) ? (ClearTune_Fuse - 8) : ClearTune_Fuse);
            f_in_ = (f_in - f_offset) / 1000 / TUNE_STEP_SIZE;

            for (idx=0; idx<16; ++idx)
            {
                if (XFreq[idx] >= f_in_)
                {
                    CapSel = 16 - idx;
                    break;
                }
            }
            /*  If CapSel == 16, set UBANDen and set CapSel = 15  */
            if (CapSel == 16)
            {
                pInfo->reg[MT2260_BAND_CTRL] |= 0x01;
                CapSel = 15;
            }
            else
                pInfo->reg[MT2260_BAND_CTRL] &= ~(0x01);

            pInfo->reg[MT2260_BAND_CTRL] =
                    (pInfo->reg[MT2260_BAND_CTRL] & 0x3F) | (LO_Band << 6);
            pInfo->reg[MT2260_CLEARTUNE] = (CapSel << 4) | CapSel;
            /*  Write UBANDsel[05] & ClearTune[06]  */
            status |= MT2260_WriteSub(pInfo->hUserData, pInfo->address, MT2260_BAND_CTRL, &pInfo->reg[MT2260_BAND_CTRL], 2);
        }
    }

    /*
    **  Check for LO lock
    */
    if (MT_NO_ERROR(status))
    {
        status |= MT2260_GetLocked(h);
    }

    return (status);
}
