
#ifndef _AF903X_H_
#define _AF903X_H_

#define DVB_USB_LOG_PREFIX "AF903X"
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kref.h>
#include <linux/smp_lock.h>
#include <linux/usb.h>
#include <asm/uaccess.h>
#include "dvb-usb.h"
#include "af903x-ioctl.h"
#include "demodulator.h"
#include "userdef.h"
#include "firmware.h"
#include "type.h"
#include "Common.h"
#include <linux/version.h>
#include <linux/mutex.h>


#define   DRIVER_RELEASE_VERSION    "v9.08.14.1"
//***************** customization *****************
//#define QuantaMID 1
//#define EEEPC 1
//***************** from compat.h *****************
#if LINUX_VERSION_CODE ==  KERNEL_VERSION(2,6,18)
typedef int bool;
#define true 1
#define false 0
//***************** from dvb-usb.h *****************
#define dvb_usb_device_properties  dvb_usb_properties
#define dvb_usb_adapter dvb_usb_device
#endif
//***************** from device.h *****************//
#define AFA_USB_DEVICE

#define SLAVE_DEMOD_2WIREADDR  0x3A

#define TS_PACKET_SIZE              	188
#define TS_PACKET_COUNT_HI       348
#define TS_PACKET_COUNT_FU       21

//***************** from driver.h *****************//
#define TS_FRAMES_HI 16
#define TS_FRAMES_FU 128
#define MAX_USB20_IRP_NUM  5
#define MAX_USB11_IRP_NUM  2

//***************** from afdrv.h *****************//
#define GANY_ONLY 0x42F5
#define EEPROM_FLB_OFS  8

#define EEPROM_IRMODE      (GANY_ONLY+EEPROM_FLB_OFS+0x10)   //00:disabled, 01:HID
#define EEPROM_SELSUSPEND  (GANY_ONLY+EEPROM_FLB_OFS+0x28)   //Selective Suspend Mode
#define EEPROM_TSMODE      (GANY_ONLY+EEPROM_FLB_OFS+0x28+1) //0:one ts, 1:dual ts
#define EEPROM_2WIREADDR   (GANY_ONLY+EEPROM_FLB_OFS+0x28+2) //MPEG2 2WireAddr
#define EEPROM_SUSPEND     (GANY_ONLY+EEPROM_FLB_OFS+0x28+3) //Suspend Mode
#define EEPROM_IRTYPE      (GANY_ONLY+EEPROM_FLB_OFS+0x28+4) //0:NEC, 1:RC6
#define EEPROM_SAWBW1      (GANY_ONLY+EEPROM_FLB_OFS+0x28+5)
#define EEPROM_XTAL1       (GANY_ONLY+EEPROM_FLB_OFS+0x28+6) //0:28800, 1:20480
#define EEPROM_SPECINV1    (GANY_ONLY+EEPROM_FLB_OFS+0x28+7)
#define EEPROM_TUNERID     (GANY_ONLY+EEPROM_FLB_OFS+0x30+4) //
#define EEPROM_IFFREQL     (GANY_ONLY+EEPROM_FLB_OFS+0x30) 
#define EEPROM_IFFREQH     (GANY_ONLY+EEPROM_FLB_OFS+0x30+1)   
#define EEPROM_IF1L        (GANY_ONLY+EEPROM_FLB_OFS+0x30+2)   
#define EEPROM_IF1H        (GANY_ONLY+EEPROM_FLB_OFS+0x30+3)
#define EEPROM_SHIFT       (0x10)                 //EEPROM Addr Shift for slave front end


extern int dvb_usb_af903x_debug;
//#define deb_info(args...)   dprintk(dvb_usb_af903x_debug,0x01,args)
//#define deb_fw(args...)     dprintk(dvb_usb_af903x_debug,0x02,args)
//#define deb_fwdata(args...) dprintk(dvb_usb_af903x_debug,0x04,args)
//#define deb_data(args...)   dprintk(dvb_usb_af903x_debug,0x08,args)


//#define DEBUG 1
#ifdef DEBUG 
#define deb_data(args...)   printk(KERN_NOTICE args)
#else
#define deb_data(args...)
#endif

//***************** from device.h *****************//
typedef struct _TUNER_INFO {

    Bool bTunerInited;
    Bool bSettingFreq;
    BYTE TunerId;
    Bool bTunerOK;
    Tuner_struct MXL5005_Info;

} TUNER_INFO, *PTUNER_INFO;
typedef struct _FILTER_CONTEXT_HW {
    DWORD ulCurrentFrequency;
    WORD  ucCurrentBandWidth;  
    DWORD ulDesiredFrequency;
    WORD  ucDesiredBandWidth;   
    //ULONG ulBandWidth;   
    Bool bTimerOn;
   // PKSFILTER filter;
    Byte GraphBuilt;
    TUNER_INFO tunerinfo; 
    //SIGNAL_STATISTICS ss;
    //SIGNAL_RETRAIN sr;  
    //DWORD   gdwOrigFCW;     //move from AF901x.cpp [global variable]
    //BYTE    gucOrigUnplugTh; //move from AF901x.cpp [global variable]
    //BYTE    gucPreShiftIdx;    //move from AF901x.cpp [global variable]    
   // PKSFILTERFACTORY  pFilterFactory;
    int  bEnPID;
    //ULONG ulcPIDs;
   // ULONG aulPIDs[32];
    Bool bApOn;
    int bResetTs;
    Byte OvrFlwChk;
} FILTER_CONTEXT_HW, *PFILTER_CONTEXT_HW;  

typedef struct _DEVICE_CONTEXT {
    FILTER_CONTEXT_HW fc[2];
    Byte DeviceNo;
    Bool bBootCode;
    Bool bEP12Error;
    Bool bEP45Error;
    //bool bDebugMsg;
    //bool bDevExist;
    Bool bDualTs;
    Bool bIrTblDownload;
    Byte BulkOutData[256];
    u32 WriteLength;
    Bool bSurpriseRemoval;
    Bool bDevNotResp;
    Bool bEnterSuspend;
    Bool bSupportSuspend;
    Bool bSupportSelSuspend;
    u16 regIdx; 
    Byte eepromIdx;
    u16 UsbMode;
    u16 MaxPacketSize;
    u32 MaxIrpSize;
    u32 TsFrames;
    u32 TsFrameSize;
    u32 TsFrameSizeDw;
    u32 TsPacketCount;
    //BYTE  ucDemod2WireAddr;
    //USB_IDLE_CALLBACK_INFO cbinfo;          // callback info for selective suspend          // our selective suspend IRP    

    Bool    bSelectiveSuspend;
    u32   ulActiveFilter;
    //BYTE    ucSerialNo; 
    Architecture architecture;
    //BYTE Tuner_Id;
    StreamType StreamType;
    Bool bDCAPIP;
    Bool bSwapFilter;
    Byte FilterCnt;
    Bool  bTunerPowerOff;
    //PKSPIN PinSave;
    Byte UsbCtrlTimeOut;
	
   Ganymede Demodulator;
   
    Bool ForceWrite;
	
} DEVICE_CONTEXT, *PDEVICE_CONTEXT;

#define PTI             (PDC->fc[ucSlaveDemod].tunerinfo)   //TunerInfo pointer



struct af903x_ofdm_channel {
	u32 RF_kHz;
	u8  Bw;
	s16 nfft;
	s16 guard;
	s16 nqam;
	s16 vit_hrch;
	s16 vit_select_hp;
	s16 vit_alpha;
	s16 vit_code_rate_hp;
	s16 vit_code_rate_lp;
	u8  intlv_native;
};

struct tuner_priv {
        struct tuner_config *cfg;
        struct i2c_adapter   *i2c;

        u32 frequency;
        u32 bandwidth;
        u16 if1_freq;
        u8  fmfreq;
};

extern struct dvb_frontend * tuner_attach(struct dvb_frontend *fe);
extern struct dvb_frontend * af903x_attach(u8 TMP);
extern struct dvb_usb_device_properties af903x_properties[];
extern struct usb_device_id af903x_usb_id_table[];
extern struct usb_device *udevs;
extern PDEVICE_CONTEXT PDC;
extern int af903x_device_count;

extern DWORD Device_init(struct usb_device *udev,PDEVICE_CONTEXT PDCs, Bool bBoot);
extern DWORD DL_ApCtrl (BYTE ucSlaveDemod, Bool bOn);
extern DWORD DL_Tuner_SetFreqBw(BYTE ucSlaveDemod,u32 ucFreq,u8 ucBw);
extern DWORD DL_isLocked(BYTE ucSlaveDemod, Bool *bLock);
extern DWORD DL_getSignalStrength(BYTE ucSlaveDemod, BYTE* strength);
extern DWORD DL_getSignalStrengthDbm(BYTE ucSlaveDemod, Long* strengthDbm);
extern DWORD DL_getChannelStatistic(BYTE ucSlaveDemod, ChannelStatistic*  channelStatistic);
extern DWORD DL_getChannelModulation(BYTE ucSlaveDemod, ChannelModulation*    channelModulation);
extern DWORD DL_getSNR(BYTE ucSlaveDemod, Constellation* constellation, BYTE* snr);
extern DWORD DL_ReSetInterval(void);
extern DWORD DL_Reboot(void);
extern DWORD DL_CheckTunerInited(BYTE ucSlaveDemod, Bool *bOn);
extern DWORD DL_PIDOnOff(BYTE ucSlaveDemod, bool bOn);
extern DWORD DL_ResetPID(BYTE	chip);
extern DWORD DL_AddPID(BYTE ucSlaveDemod, Byte index,Pid pid);
extern DWORD DL_RemovePID(BYTE ucSlaveDemod, Byte index,Pid pid);
extern bool TunerInited0, TunerInited1, DevicePower, DeviceReboot;
#endif

