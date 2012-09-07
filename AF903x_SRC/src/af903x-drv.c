#include "af903x.h"

#define FW_VER         0x08060000
int dvb_usb_af903x_debug;
module_param_named(debug,dvb_usb_af903x_debug, int, 0644);
MODULE_PARM_DESC(debug, "set debugging level.(info=1,deb_fw=2,deb_fwdata=4,deb_data=8)" DVB_USB_DEBUG_STATUS);

struct usb_device *udevs;
PDEVICE_CONTEXT PDC;

static DEFINE_MUTEX(mymutex);
  
//************** DRV_ *************//

static DWORD DRV_IrTblDownload(IN      void * handle)
{
        DWORD dwError = Error_NO_ERROR;
        PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;
        struct file *filp;
        unsigned char b_buf[512] ;
        int i, fileSize;
        mm_segment_t oldfs;

        deb_data("- Enter %s Function -\n",__FUNCTION__);

        oldfs=get_fs();
        set_fs(KERNEL_DS);

        filp=filp_open("/lib/firmware/af35irtbl.bin", O_RDWR,0644);
        if ( IS_ERR(filp) ) {
                deb_data("      LoadIrTable : Can't open file\n");goto exit;}

        if ( (filp->f_op) == NULL ) {
                deb_data("      LoadIrTable : File Operation Method Error!!\n");goto exit;}

        filp->f_pos=0x00;
        fileSize = filp->f_op->read(filp,b_buf,sizeof(b_buf),&filp->f_pos);

        for(i=0; i<fileSize; i++)
        {
              //deb_data("\n Data %d",i); //
              //deb_data("0x%x",b_buf[i]);//
              // dwError = Af901xWriteReg(ucDemod2WireAddr, 0, MERC_IR_TABLE_BASE_ADDR + i, b_buf[i]);
              //if (dwError) goto exit;
        }

        dwError = Demodulator_loadIrTable((Demodulator*) &pdc->Demodulator, (Word)fileSize, b_buf);
        if (dwError) {deb_data("Demodulator_loadIrTable fail"); goto exit;}

        filp_close(filp, NULL);
        set_fs(oldfs);

        return (dwError);
exit:
        deb_data("LoadIrTable fail!\n");

}

static DWORD  DRV_GetEEPROMConfig2(
        void *      handle,
        BYTE       ucSlaveDemod)
{

	DWORD dwError = Error_NO_ERROR;
    	tWORD    shift = 0;
    	PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;
	BYTE btmp = 0;

	deb_data("- Enter %s Function -",__FUNCTION__);
	
    	if(ucSlaveDemod) shift = EEPROM_SHIFT;
    
    	dwError = Demodulator_readRegisters((Demodulator*) &pdc->Demodulator, 0, Processor_LINK, EEPROM_TUNERID+shift, 1, &btmp);
    	if (dwError) goto exit;
    	deb_data("EEPROM_TUNERID%d  = 0x%02X\n", ucSlaveDemod, btmp);		
    	PTI.TunerId = btmp;  

exit:
    
    return(dwError);     
}  

static DWORD DRV_SetFreqBw(
    	void*	handle,      
     	BYTE 	ucSlaveDemod,
      	DWORD   dwFreq,      
      	WORD	ucBw
)
{
    	DWORD dwError = Error_NO_ERROR;
    
    	PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;

	Bool bLock = true;

	deb_data("- Enter %s Function -\n ",__FUNCTION__);
	deb_data("	ucSlaveDemod = %d, Freq= %d, BW=%d\n", ucSlaveDemod, dwFreq, ucBw);

    if (pdc->fc[ucSlaveDemod].bEnPID)
    {
        Demodulator_resetPid((Demodulator*) &pdc->Demodulator, ucSlaveDemod);
        //Disable PID filter
        Demodulator_writeRegisterBits ((Demodulator*) &pdc->Demodulator, ucSlaveDemod, Processor_OFDM, p_mp2if_pid_en, mp2if_pid_en_pos, mp2if_pid_en_len, 0);
	 pdc->fc[ucSlaveDemod].bEnPID = 0;
    }
	
    PTI.bSettingFreq = true; //before acquireChannel, it is ture;  otherwise, it is false

    if(dwFreq) {
        pdc->fc[ucSlaveDemod].ulDesiredFrequency = dwFreq;
    }
    else {
        dwFreq = pdc->fc[ucSlaveDemod].ulDesiredFrequency;
    }

    if(ucBw) {
        pdc->fc[ucSlaveDemod].ucDesiredBandWidth = ucBw*1000;
	}
    else {
        ucBw = pdc->fc[ucSlaveDemod].ucDesiredBandWidth;
    	}

    deb_data("	Real Freq= %d, BW=%d\n", pdc->fc[ucSlaveDemod].ulDesiredFrequency, pdc->fc[ucSlaveDemod].ucDesiredBandWidth);
           

    if(!PTI.bTunerInited){
        deb_data("	Skip SetFreq - Tuner is still off!\n");
        goto exit;
    }
	
    PTI.bTunerOK = false;        

    if (pdc->fc[ucSlaveDemod].ulDesiredFrequency!=0 && pdc->fc[ucSlaveDemod].ucDesiredBandWidth!=0)	
    {
	deb_data("	AcquireChannel : Real Freq= %d, BW=%d\n", pdc->fc[ucSlaveDemod].ulDesiredFrequency, pdc->fc[ucSlaveDemod].ucDesiredBandWidth);
	dwError = Demodulator_acquireChannel ((Demodulator*) &pdc->Demodulator, ucSlaveDemod, pdc->fc[ucSlaveDemod].ucDesiredBandWidth, pdc->fc[ucSlaveDemod].ulDesiredFrequency);  
	//PTI.bSettingFreq = false;
    	if (dwError) 
    	{
        	deb_data("	Demod_acquireChannel fail! 0x%08x\n", dwError);
        	goto exit;
    	}	
	else //when success acquireChannel, record currentFreq/currentBW.
	{
		pdc->fc[ucSlaveDemod].ulCurrentFrequency = pdc->fc[ucSlaveDemod].ulDesiredFrequency;	
		pdc->fc[ucSlaveDemod].ucCurrentBandWidth = pdc->fc[ucSlaveDemod].ucDesiredBandWidth;  
	}
    }

    if(pdc->StreamType == StreamType_DVBT_DATAGRAM) {
        PDC->fc[ucSlaveDemod].OvrFlwChk = 5;
    }
  
    /*if (pdc->fc[ucSlaveDemod].ulDesiredFrequency!=0 && pdc->fc[ucSlaveDemod].ucDesiredBandWidth!=0)
    {
	// patch for Demodulator_isLocked
	//mdelay(700);

    	dwError= Demodulator_isLocked((Demodulator*) &pdc->Demodulator, ucSlaveDemod, &bLock);
    	if(dwError)  
        	deb_data("	Demodulator_isLocked is failed!\n"); 
    	else 
	{
        	deb_data("	The signal is %s Lock\n", bLock?"":"not"); 

		//patch for mce channel change lag
		if(bLock) {
			mdelay(500); 
		}
    	}
    }*/

    PTI.bTunerOK = true;

exit:

    PTI.bSettingFreq = false;

    return(dwError);  
}

DWORD DRV_ResetPID(
    IN	void*	handle,
    IN	BYTE	chip
)
{
    deb_data("- Enter %s Function -\n ",__FUNCTION__);

    DWORD   dwError = Error_NO_ERROR;
    
    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;
          
    //Clear pidTable
    dwError = Demodulator_resetPid ((Demodulator*) &pdc->Demodulator, chip);

    return(dwError);
    
}

DWORD DRV_AddPID(
    IN	void*	handle,
    IN	BYTE	ucSlaveDemod,
    IN  Byte  	index,
    IN 	Pid		pid
)
{
    deb_data("- Enter %s Function - , index:%d, pid:%x \n",__FUNCTION__, index, pid.value);

    DWORD   dwError = Error_NO_ERROR;
    
    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;
          
    dwError = Demodulator_addPidToFilter ((Demodulator*) &pdc->Demodulator, ucSlaveDemod,index, pid);

    return(dwError);
    
}

DWORD DRV_RemovePID(
    IN	void*	handle,
    IN	BYTE	ucSlaveDemod,
    IN  Byte  	index,
    IN 	Pid		pid
)
{
    deb_data("- Enter %s Function - , index:%d, pid:%x \n",__FUNCTION__, index, pid.value);

    DWORD   dwError = Error_NO_ERROR;
    
    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;
          
    dwError = Demodulator_removePidAt ((Demodulator*) &pdc->Demodulator, ucSlaveDemod,index, pid);

    return(dwError);
    
}

DWORD DRV_PIDOnOff(
    IN	void *	handle,
    IN  	BYTE    	ucSlaveDemod,
    IN  	bool        bOn
)
{
    deb_data("- Enter %s Function -onoff:%d\n ",__FUNCTION__, bOn);

    DWORD  dwError = Error_NO_ERROR;

    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;

    if (bOn)
        dwError = Demodulator_controlPidFilter ((Demodulator*) &pdc->Demodulator, ucSlaveDemod, 1);
    else
        dwError = Demodulator_controlPidFilter ((Demodulator*) &pdc->Demodulator, ucSlaveDemod, 0);		

    return(dwError);    
}

static DWORD DRV_isLocked(
        void*   handle,
        BYTE    ucSlaveDemod,
        Bool*   bLock   
)
{
        DWORD dwError = Error_NO_ERROR;
        PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;
        *bLock = true;

	deb_data("- Enter %s Function -\n ",__FUNCTION__);

	dwError= Demodulator_isLocked((Demodulator*) &pdc->Demodulator, ucSlaveDemod, bLock);
        if(dwError)  
                deb_data("      Demodulator_isLocked is failed!\n"); 
        else 
                deb_data("      The chip=%d signal is %s Lock\n", ucSlaveDemod, *bLock?"":"not"); 

	return(dwError);
}
static DWORD DRV_getSignalStrength(
        void*   handle,
        BYTE    ucSlaveDemod,
        BYTE*    strength  
)
{
        DWORD dwError = Error_NO_ERROR;
        PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;

        deb_data("- Enter %s Function -\n ",__FUNCTION__);

	 dwError= Demodulator_getSignalStrength((Demodulator*) &pdc->Demodulator, ucSlaveDemod, strength);
	if(dwError)
                deb_data("      Demodulator_getSignalStrength is failed!\n");
	else
                deb_data("      The signal strength is %d \n", *strength);

	return(dwError);
}

static DWORD DRV_getSignalStrengthDbm(
    void*   handle,
    BYTE    ucSlaveDemod,
    Long*   strengthDbm
)
{
    DWORD dwError = Error_NO_ERROR;
    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;

    deb_data("- Enter %s Function -\n ",__FUNCTION__);

    dwError= Demodulator_getSignalStrengthDbm((Demodulator*) &pdc->Demodulator, ucSlaveDemod, 1, 1, strengthDbm);
    if(dwError)
	deb_data("      Demodulator_getSignalStrengthDbm is failed!\n");
    else
	deb_data("      The signal strengthDbm is %d \n", *strengthDbm);

    return(dwError);
}

static DWORD DRV_getChannelStatistic(
    void*   handle,
    BYTE    ucSlaveDemod,
    ChannelStatistic*           channelStatistic
)
{
    DWORD dwError = Error_NO_ERROR;
    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;
    
    deb_data("- Enter %s Function -\n ",__FUNCTION__);
    
    dwError= Demodulator_getChannelStatistic((Demodulator*) &pdc->Demodulator, ucSlaveDemod, channelStatistic);
    if(dwError)
	deb_data("      Demodulator_getChannelStatistic is failed!\n");

    return(dwError);
}

static DWORD DRV_getChannelModulation(
    void*   handle,
    BYTE    ucSlaveDemod,
    ChannelModulation*      channelModulation
)
{
    DWORD dwError = Error_NO_ERROR;
    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;

    deb_data("- Enter %s Function -\n ",__FUNCTION__);

    dwError= Standard_getChannelModulation((Demodulator*) &pdc->Demodulator, ucSlaveDemod, channelModulation);
    if(dwError)
	deb_data("      Demodulator_getChannelStatistic is failed!\n");

    return(dwError);
}

static DWORD DRV_getSNRValue(
    void*   handle,
    DWORD*   snr_value
)
{
    DWORD dwError = Error_NO_ERROR;
    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;
    BYTE snr_reg_23_16, snr_reg_15_8, snr_reg_7_0;
    
    deb_data("- Enter %s Function -\n ",__FUNCTION__);


    dwError = Demodulator_readRegister((Demodulator*) &pdc->Demodulator, 0,Processor_OFDM, 0x2e,(unsigned char *) &snr_reg_23_16);
    if(dwError)
	deb_data("      Demodulator_getSNR snr_reg_23_16 is failed!\n");

     dwError = Demodulator_readRegister((Demodulator*) &pdc->Demodulator, 0,Processor_OFDM, 0x2d,(unsigned char *) &snr_reg_15_8);
     if(dwError)
	deb_data("      Demodulator_getSNR snr_reg_15_8 is failed!\n");

    dwError = Demodulator_readRegister((Demodulator*) &pdc->Demodulator, 0,Processor_OFDM, 0x2c,(unsigned char *) &snr_reg_7_0);
    if(dwError)
	deb_data("      Demodulator_getSNR snr_reg_7_0 is failed!\n");

    *snr_value = (snr_reg_23_16&0xff)*256*256+(snr_reg_15_8&0xff)*256+(snr_reg_7_0&0xff);

    return(dwError);
}

static DWORD DRV_getFirmwareVersionFromFile( 
	 	Processor	processor, 
		DWORD* 		version
)
{
    DWORD OFDM_VER1 = DVB_OFDM_VERSION1;
    DWORD OFDM_VER2 = DVB_OFDM_VERSION2;
    DWORD OFDM_VER3 = DVB_OFDM_VERSION3;
    DWORD OFDM_VER4 = DVB_OFDM_VERSION4;

    DWORD LINK_VER1 = DVB_LL_VERSION1;
    DWORD LINK_VER2 = DVB_LL_VERSION2;
    DWORD LINK_VER3 = DVB_LL_VERSION3;    
    DWORD LINK_VER4 = DVB_LL_VERSION4;    

    if(processor == Processor_OFDM) {
        *version = (DWORD)( (OFDM_VER1 << 24) + (OFDM_VER2 << 16) + (OFDM_VER3 << 8) + OFDM_VER4);
    }
    else { //LINK
        *version = (DWORD)( (LINK_VER1 << 24) + (LINK_VER2 << 16) + (LINK_VER3 << 8) + LINK_VER4);    
    }
    
    return *version;
}

static DWORD  DRV_Initialize(
	    void *      handle
)
{
	DWORD error = Error_NO_ERROR;
	 
	PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;

	DWORD fileVersion, cmdVersion = 0; 

	deb_data("- Enter %s Function -\n",__FUNCTION__);

	if(pdc->Demodulator.booted) //from Standard_setBusTuner() > Standard_getFirmwareVersion()
    	{
        	//use "#define version" to get fw version (from firmware.h title)
        	error = DRV_getFirmwareVersionFromFile(Processor_OFDM, &fileVersion);

        	//use "Command_QUERYINFO" to get fw version 
        	error = Demodulator_getFirmwareVersion((Demodulator*) &pdc->Demodulator, Processor_OFDM, &cmdVersion);
        	if(error) deb_data("DRV_Initialize : Demodulator_getFirmwareVersion : error = 0x%08x\n", error);

        	if(cmdVersion != fileVersion)
        	{
            		deb_data("Reboot: Outside Fw = 0x%X, Inside Fw = 0x%X", fileVersion, cmdVersion);               
            		error = Demodulator_reboot((Demodulator*) &pdc->Demodulator);
            		pdc->bBootCode = true;
            		if(error) 
            		{
                		deb_data("Demodulator_reboot : error = 0x%08x\n", error);
                		return error;
            		}
            		else {
                		return Error_NOT_READY;
            		}
        	}
        	else
        	{
            		deb_data("	Fw version is the same!\n");
  	      		error = Error_NO_ERROR;
        	}
	}//pdc->Demodulator.booted

ReInit:  //Patch for NIM fail or disappear, Maggie   
    error = Demodulator_initialize ((Demodulator*) &pdc->Demodulator, pdc->Demodulator.chipNumber , 8000, pdc->StreamType, pdc->architecture); 
    if (error) 
    { 
        deb_data("Device initialize fail : 0x%08x\n", error);
        if( ((error&Error_FIRMWARE_STATUS) && (error&0x10)) && (pdc->Demodulator.chipNumber>1) )
        {
            pdc->Demodulator.cmdDescription->sendCommand ((Demodulator*) &pdc->Demodulator, Command_FW_DOWNLOAD_END, 0, Processor_LINK, 0, NULL, 0, NULL);

            deb_data("	Retry to download FW with Single TS\n");
            pdc->Demodulator.chipNumber = 1;
            pdc->bDualTs = false;
            error = Demodulator_writeRegister ((Demodulator*) &pdc->Demodulator, 0, Processor_LINK, 0x417F, 0);
            goto ReInit;
       }
    }
    else {
        deb_data("    Device initialize Ok!!\n");
    }

    Demodulator_getFirmwareVersion ((Demodulator*) &pdc->Demodulator, Processor_OFDM, &cmdVersion);
    deb_data("    FwVer OFDM = 0x%X, ", cmdVersion);
    Demodulator_getFirmwareVersion ((Demodulator*) &pdc->Demodulator, Processor_LINK, &cmdVersion);
    deb_data("FwVer LINK = 0x%X\n", cmdVersion);
    
    return error;
	
}

static DWORD DRV_InitDevInfo(
    	void *      handle,
    	BYTE        ucSlaveDemod
)
{
    DWORD dwError = Error_NO_ERROR;    
 
    PDC->fc[ucSlaveDemod].ulCurrentFrequency = 0;  
    PDC->fc[ucSlaveDemod].ucCurrentBandWidth = 0;

    PDC->fc[ucSlaveDemod].ulDesiredFrequency = 0;	
    PDC->fc[ucSlaveDemod].ucDesiredBandWidth = 6000;	

    //For PID Filter Setting
    //PDC->fc[ucSlaveDemod].ulcPIDs = 0;    
    PDC->fc[ucSlaveDemod].bEnPID = false;

    PDC->fc[ucSlaveDemod].bApOn = false;
    
    PDC->fc[ucSlaveDemod].bResetTs = false;



    PTI.bTunerOK = false;
    PTI.bSettingFreq = false;

    return dwError;
}	

static DWORD DRV_GetEEPROMConfig(    
	void *      handle)
{
	DWORD dwError = Error_NO_ERROR;
	PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;
    	BYTE ucSlaveDemod = 0;
	BYTE btmp = 0;
	int cnt;

	deb_data("- Enter %s Function -",__FUNCTION__);	
   
	//bIrTblDownload option
	dwError =   Demodulator_readRegisters((Demodulator*) &pdc->Demodulator, 0, Processor_LINK, EEPROM_IRMODE, 1, &btmp);
	if (dwError) return(dwError);
	PDC->bIrTblDownload = btmp ? true:false;
	deb_data(	"EEPROM_IRMODE = 0x%02X, ", btmp);
        deb_data("bIrTblDownload %s\n", PDC->bIrTblDownload?"ON":"OFF");
 
    	PDC->bDualTs = false;
    	PDC->architecture = Architecture_DCA;
    	PDC->Demodulator.chipNumber = 1;   
    	PDC->bDCAPIP = false;

	//bDualTs option
	dwError = Demodulator_readRegisters((Demodulator*) &pdc->Demodulator, 0, Processor_LINK,EEPROM_TSMODE, 1, &btmp);
	if (dwError) return(dwError);
	deb_data("EEPROM_TSMODE = 0x%02X", btmp);

	if (btmp == 0)
	    deb_data("TSMode = TS1 mode\n");
	else if (btmp == 1)
	{
	    deb_data("TSMode = DCA+PIP mode\n");
	    PDC->architecture = Architecture_DCA;
	    PDC->Demodulator.chipNumber = 2;
	    PDC->bDualTs = true;
	    //PDC->bDCAPIP = true;
	}
	else if (btmp == 3)
	{
	     deb_data("TSMode = PIP mode\n");
	     PDC->architecture = Architecture_PIP;
	     PDC->Demodulator.chipNumber = 2;
	     PDC->bDualTs = true;
	}
	else
	{   
	    deb_data("TSMode = DCA mode\n");
	    PDC->architecture = Architecture_DCA;
	    PDC->Demodulator.chipNumber = 2;
	}

	if(PDC->bDualTs) {
	    cnt = 2;
	}
	else {
	    cnt = 1;
	}

	for(ucSlaveDemod; ucSlaveDemod < cnt; ucSlaveDemod++)
	{
	    dwError = DRV_GetEEPROMConfig2(pdc, ucSlaveDemod);
	    if (dwError) return(dwError);  
	    dwError = DRV_InitDevInfo(pdc, ucSlaveDemod);
	    if (dwError) return(dwError);
	}
    
   	 return(dwError);     
}   

static DWORD DRV_SetBusTuner(
	 void * handle, 
	 Word busId, 
	 Word tunerId
)
{
	DWORD dwError = Error_NO_ERROR;
	DWORD 	 version = 0;

	PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;

	deb_data("- Enter %s Function -",__FUNCTION__);
	deb_data("busId = 0x%x, tunerId =0x%x\n", busId, tunerId);

	if ((pdc->UsbMode==0x0110) && (busId==Bus_USB)) {
        busId=Bus_USB11;    
    }
    
    	dwError = Demodulator_setBusTuner ((Demodulator*) &pdc->Demodulator, busId, tunerId);
	if (dwError) {deb_data("Demodulator_setBusTuner error\n");return dwError;}

	dwError = Demodulator_getFirmwareVersion ((Demodulator*) &pdc->Demodulator, Processor_LINK, &version);
    	if (version != 0) {
        	pdc->Demodulator.booted = True;
    	} 
    	else {
        	pdc->Demodulator.booted = False;
    	}
	if (dwError) {deb_data("Demodulator_getFirmwareVersion  error\n");}

    	return(dwError); 
}



static DWORD DRV_TunerPowerCtrl(
    	void *	handle, 
     	BYTE	ucSlaveDemod,
     	Bool		bPowerOn
)
{ 
    DWORD dwError = Error_NO_ERROR;	

    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;

    deb_data("- Enter %s Function -",__FUNCTION__);
    deb_data("chip = %d\n", ucSlaveDemod); 

    /* init gpioH7 */
    dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK,  p_reg_top_gpioh7_en, reg_top_gpioh7_en_pos, reg_top_gpioh7_en_len, 1);    
    dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK,  p_reg_top_gpioh7_on, reg_top_gpioh7_on_pos, reg_top_gpioh7_on_len, 1);    

    if(bPowerOn)
        PTI.bTunerInited = true;
    else
        PTI.bTunerInited = false;    


    if(bPowerOn) //tuner on
    {
        dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK,  p_reg_top_gpioh7_o, reg_top_gpioh7_o_pos, reg_top_gpioh7_o_len, 1);    

        if(pdc->bTunerPowerOff == true) 
        {
            dwError = Demodulator_initialize ((Demodulator*) &pdc->Demodulator, pdc->Demodulator.chipNumber , pdc->Demodulator.bandwidth[0], pdc->StreamType, pdc->architecture);  
            pdc->bTunerPowerOff = false;
        }              	        
    }
    else //tuner off
    {
        if(pdc->architecture == Architecture_PIP)
        {
            if(pdc->fc[0].tunerinfo.bTunerInited == false && pdc->fc[1].tunerinfo.bTunerInited == false) 
            {                                
                if(pdc->bTunerPowerOff == false) 
                {
                    dwError = Demodulator_finalize((Demodulator*) &pdc->Demodulator);
                    pdc->bTunerPowerOff = true;
                }
                
                dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK,  p_reg_top_gpioh7_o, reg_top_gpioh7_o_pos, reg_top_gpioh7_o_len, 0);    
            }                   
        }
        else 
        {
            if(pdc->bTunerPowerOff == false) 
            {                
                dwError = Demodulator_finalize((Demodulator*) &pdc->Demodulator);
                pdc->bTunerPowerOff = true;
            }      

            dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK,  p_reg_top_gpioh7_o, reg_top_gpioh7_o_pos, reg_top_gpioh7_o_len, 0);    
        }        	

    }
    return(dwError);
}

static DWORD DRV_ApCtrl (
      void *      handle,
      Byte        ucSlaveDemod,
      Bool        bOn
)
{
	DWORD dwError = Error_NO_ERROR;

        PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;

	deb_data("- Enter %s Function -\n",__FUNCTION__);
	deb_data(" ucSlaveDemod = %d, bOn = %s \n", ucSlaveDemod, bOn?"ON":"OFF"); 

      //deb_data("enter DRV_ApCtrl: Demod[%d].GraphBuilt = %d", ucSlaveDemod, pdc->fc[ucSlaveDemod].GraphBuilt); 

	dwError = DRV_TunerPowerCtrl(pdc, ucSlaveDemod, bOn);
       	if(dwError) { deb_data("	DRV_TunerPowerCtrl Fail: 0x%08x\n", dwError); return(dwError);}

	
    	dwError = Demodulator_controlPowerSaving((Demodulator*) &pdc->Demodulator, ucSlaveDemod, bOn);   
    	if(dwError) { deb_data("	DRV_ApCtrl: Demodulator_controlPowerSaving error = 0x%08x\n", dwError); return(dwError);}
	
    return(dwError);
}


static DWORD DRV_TunerWakeup(
      void *     handle
)
{   
    	DWORD dwError = Error_NO_ERROR;

    	PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT) handle;

	deb_data("- Enter %s Function -\n",__FUNCTION__);

	//tuner power on
	dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK,  p_reg_top_gpioh7_o, reg_top_gpioh7_o_pos, reg_top_gpioh7_o_len, 1);	 

    return(dwError);

}

static DWORD DRV_Reboot(
      void *     handle
)
{
	DWORD dwError = Error_NO_ERROR;

        PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT) handle;

        deb_data("- Enter %s Function -\n",__FUNCTION__);

        dwError = Demodulator_reboot((Demodulator*) &pdc->Demodulator);

	return(dwError);
}



static DWORD DRV_USBSetup(
    void*	handle
)
{
    DWORD dwError = Error_NO_ERROR;

    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT) handle;

    deb_data("- Enter %s Function -\n",__FUNCTION__);

    int i;

    if (pdc->Demodulator.chipNumber == 2)
    {
	//timing
	for (i=0; i<2; i++)
	{
	    dwError = Demodulator_writeRegisterBits ((Demodulator*) &pdc->Demodulator,i, Processor_OFDM, p_reg_dca_fpga_latch, reg_dca_fpga_latch_pos, reg_dca_fpga_latch_len, 0x66);
	    if(dwError) return (dwError);
	    dwError = Demodulator_writeRegisterBits ((Demodulator*) &pdc->Demodulator, i, Processor_OFDM, p_reg_dca_platch, reg_dca_platch_pos, reg_dca_platch_len, 1);
	    if(dwError) return (dwError);
	}
    }
    return(dwError);
}

static DWORD DRV_NIMSuspend(
    void *      handle,
    bool        bSuspend

)
{
    deb_data("- Enter DRV_NIMSuspend : bSuspend = %s\n", bSuspend ? "ON":"OFF");

    DWORD dwError = Error_NO_ERROR;

    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT) handle;

    if(bSuspend) //sleep
    {
	dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK, p_reg_top_gpioh5_o, reg_top_gpioh5_o_pos, reg_top_gpioh5_o_len, 1);
	if(dwError) return (dwError);
    }
    else //resume
    {
	dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK, p_reg_top_gpioh5_o, reg_top_gpioh5_o_pos, reg_top_gpioh5_o_len, 0);
	if(dwError) return (dwError);
    }

    return(dwError);
}

static DWORD DRV_InitNIMSuspendRegs(
    void *      handle
)
{
    deb_data("- Enter %s Function -\n",__FUNCTION__);

    DWORD dwError = Error_NO_ERROR;

    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT) handle;

    dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK, p_reg_top_gpioh5_en, reg_top_gpioh5_en_pos, reg_top_gpioh5_en_len, 1);
    dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK, p_reg_top_gpioh5_on, reg_top_gpioh5_on_pos, reg_top_gpioh5_on_len, 1);
    dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK, p_reg_top_gpioh5_o, reg_top_gpioh5_o_pos, reg_top_gpioh5_o_len, 0);

    dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 1, Processor_LINK, p_reg_top_pwrdw, reg_top_pwrdw_pos, reg_top_pwrdw_len, 1);

    dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 1, Processor_LINK, p_reg_top_pwrdw_hwen, reg_top_pwrdw_hwen_pos, reg_top_pwrdw_hwen_len, 1);

    return(dwError);
}

static DWORD DRV_NIMReset(
    void *      handle
)
{
    deb_data("- Enter %s Function -\n",__FUNCTION__);

    DWORD   dwError = Error_NO_ERROR;

    PDEVICE_CONTEXT pdc = (PDEVICE_CONTEXT)handle;

    //Set AF0350 GPIOH1 to 0 to reset AF0351

    dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK,  p_reg_top_gpioh1_en, reg_top_gpioh1_en_pos, reg_top_gpioh1_en_len, 1);
    dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK,  p_reg_top_gpioh1_on, reg_top_gpioh1_on_pos, reg_top_gpioh1_on_len, 1);
    dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK,  p_reg_top_gpioh1_o, reg_top_gpioh1_o_pos, reg_top_gpioh1_o_len, 0);

    mdelay(50);

    dwError = Demodulator_writeRegisterBits((Demodulator*) &pdc->Demodulator, 0, Processor_LINK,  p_reg_top_gpioh1_o, reg_top_gpioh1_o_pos, reg_top_gpioh1_o_len, 1);

    return(dwError);
}

//************** DL_ *************//

static DWORD DL_NIMReset(
    void *      handle
)
{

    mutex_lock(&mymutex);

    DWORD dwError = Error_NO_ERROR;
    
    dwError = DRV_NIMReset(handle);

    mutex_unlock(&mymutex);

    return (dwError);
}

static DWORD DL_USBSetup(
    void *      handle
)
{

    mutex_lock(&mymutex);

   DWORD dwError = Error_NO_ERROR;

   dwError = DRV_USBSetup(handle);

   mutex_unlock(&mymutex);

     return (dwError);
}

static DWORD DL_NIMSuspend(
    void *      handle,
    bool	bSuspend
)
{

    mutex_lock(&mymutex);

    DWORD dwError = Error_NO_ERROR;

    dwError = DRV_NIMSuspend(handle, bSuspend);

    mutex_unlock(&mymutex);

    return (dwError);
}

static DWORD DL_InitNIMSuspendRegs(
    void *      handle
)
{
    
    mutex_lock(&mymutex);
    
    DWORD dwError = Error_NO_ERROR;

    dwError = DRV_InitNIMSuspendRegs(handle);

    mutex_unlock(&mymutex);

    return (dwError);
}
static DWORD DL_Initialize(
	    void *      handle
)
{

    mutex_lock(&mymutex);

    	DWORD dwError = Error_NO_ERROR;  
    
     	dwError = DRV_Initialize(handle);   

	mutex_unlock(&mymutex);

	return (dwError); 
    
}

static DWORD DL_SetBusTuner(
	 void * handle, 
	 Word busId, 
	 Word tunerId
)
{

   mutex_lock(&mymutex);

	DWORD dwError = Error_NO_ERROR;
	
    	dwError = DRV_SetBusTuner(handle, busId, tunerId);

    mutex_unlock(&mymutex);

	return (dwError);

}

static DWORD  DL_GetEEPROMConfig(
	 void *      handle
)
{   

    mutex_lock(&mymutex);
    
    DWORD dwError = Error_NO_ERROR;

    dwError = DRV_GetEEPROMConfig(handle);

    mutex_unlock(&mymutex);

    return(dwError);
} 

static DWORD DL_TunerWakeup(
      void *     handle
)
{    

    mutex_lock(&mymutex);

	DWORD dwError = Error_NO_ERROR;

	 dwError = DRV_TunerWakeup(handle);

    mutex_unlock(&mymutex);
   
    	return(dwError);
}
static DWORD  DL_IrTblDownload(
      void *     handle
)
{

    mutex_lock(&mymutex);

        DWORD dwError = Error_NO_ERROR;

	dwError = DRV_IrTblDownload(handle);

    mutex_unlock(&mymutex);

        return(dwError);
}


DWORD DL_TunerPowerCtrl(u8 bPowerOn)
{


    mutex_lock(&mymutex);

	DWORD dwError = Error_NO_ERROR;
	BYTE    ucSlaveDemod=0;

	deb_data("enter DL_TunerPowerCtrl:  bOn = %s\n", bPowerOn?"ON":"OFF");

    for (ucSlaveDemod=0; ucSlaveDemod<PDC->Demodulator.chipNumber; ucSlaveDemod++)
    {
    	dwError = DRV_TunerPowerCtrl(PDC, ucSlaveDemod, bPowerOn);
	if(dwError) deb_data("  DRV_TunerPowerCtrl Fail: 0x%08x\n", dwError);
    }

    mutex_unlock(&mymutex);

    return (dwError);
}
//EXPORT_SYMBOL(DL_TunerPowerCtrl);

DWORD DL_ResetPID(
    IN	BYTE	chip
)
{
    mutex_lock(&mymutex);

    DWORD dwError = DRV_ResetPID(PDC, chip);

    mutex_unlock(&mymutex);

    return(dwError);
}

DWORD DL_AddPID(
    IN	BYTE	ucSlaveDemod,
    IN      Byte  	index,
    IN 	Pid		pid
)
{
    mutex_lock(&mymutex);

    DWORD dwError = DRV_AddPID(PDC, ucSlaveDemod,index, pid);

    mutex_unlock(&mymutex);

    return(dwError);
}

DWORD DL_RemovePID(
    IN	BYTE	ucSlaveDemod,
    IN      Byte  	index,
    IN 	Pid		pid
)
{
    mutex_lock(&mymutex);

    DWORD dwError = DRV_RemovePID(PDC, ucSlaveDemod,index, pid);

    mutex_unlock(&mymutex);

    return(dwError);
}
	
DWORD DL_PIDOnOff(
    IN  	BYTE    		ucSlaveDemod,
    IN  	bool    		bOn
)
{
    mutex_lock(&mymutex);
    
    DWORD dwError = DRV_PIDOnOff(PDC, ucSlaveDemod, bOn);
    
    mutex_unlock(&mymutex);
    
    return(dwError);
}

DWORD DL_ApCtrl (
    BYTE    ucSlaveDemod,
    Bool        bOn
)
{

    mutex_lock(&mymutex);

        DWORD dwError = Error_NO_ERROR;
	BYTE    i=0;

	deb_data("- Enter %s Function -",__FUNCTION__);
	deb_data("  chip =  %d  bOn = %s\n", ucSlaveDemod, bOn?"ON":"OFF");

    if(PDC->architecture != Architecture_PIP)
    {
	if ( PDC->Demodulator.chipNumber == 2 && bOn) dwError = DL_NIMSuspend(PDC, false);

	for (i=0; i<PDC->Demodulator.chipNumber; i++)
	{	 
	   if (bOn) 
		dwError = DRV_ApCtrl (PDC, i, bOn);
	   else 
		if (PDC->bTunerPowerOff != true) dwError = DRV_ApCtrl (PDC, i, bOn);

	    if(!bOn)
	    {
                PDC->fc[i].ulDesiredFrequency = 0;
		PDC->fc[i].ucDesiredBandWidth = 0;
	    }
	}

	if(PDC->Demodulator.chipNumber == 2 && !bOn) dwError = DL_NIMSuspend(PDC, true);
    }
    else
    {
	if (bOn)
	{
	    PDC->fc[ucSlaveDemod].GraphBuilt = 1;

	    if (PDC->fc[0].GraphBuilt == 0 ||  PDC->fc[1].GraphBuilt == 0)
		dwError = DL_NIMSuspend(PDC, false);

	    dwError = DRV_ApCtrl (PDC, ucSlaveDemod, bOn);
	}
	else
	{
	    
	    PDC->fc[ucSlaveDemod].GraphBuilt = 0;

	    if (PDC->bTunerPowerOff != true) dwError = DRV_ApCtrl (PDC, ucSlaveDemod, bOn);

	    if (PDC->fc[0].GraphBuilt == 0 && PDC->fc[1].GraphBuilt == 0 && PDC->bTunerPowerOff == true)
		dwError = DL_NIMSuspend(PDC, true);
	}
    }

    mutex_unlock(&mymutex);

    	return(dwError);
}
//EXPORT_SYMBOL(DL_ApCtrl);

DWORD DL_Tuner_SetFreqBw(BYTE ucSlaveDemod, u32 dwFreq,u8 ucBw)
{

    mutex_lock(&mymutex);

	DWORD dwError = Error_NO_ERROR;
	
	deb_data("- Enter %s Function -\n",__FUNCTION__);
	if (PDC->fc[ucSlaveDemod].ulDesiredFrequency!=dwFreq || PDC->fc[ucSlaveDemod].ucDesiredBandWidth!=ucBw*1000) 
	 	dwError = DRV_SetFreqBw(PDC, ucSlaveDemod, dwFreq, ucBw);

    mutex_unlock(&mymutex);
    	return(dwError);	
}
//EXPORT_SYMBOL(DL_Tuner_SetFreq);

DWORD DL_isLocked(BYTE ucSlaveDemod, Bool *bLock )
{

    mutex_lock(&mymutex);

	DWORD dwError = Error_NO_ERROR;

	deb_data("- Enter %s Function -\n",__FUNCTION__);
	
	dwError =  DRV_isLocked(PDC, ucSlaveDemod, bLock);	

    mutex_unlock(&mymutex);
	return(dwError);
}

DWORD DL_getSignalStrength(BYTE ucSlaveDemod, BYTE* strength)
{

    mutex_lock(&mymutex);

	DWORD dwError = Error_NO_ERROR;

        deb_data("- Enter %s Function -\n",__FUNCTION__);

        dwError =  DRV_getSignalStrength(PDC, ucSlaveDemod, strength);

//	deb_data("      The signal strength is %d \n", *strength);
    mutex_unlock(&mymutex);

        return(dwError);
}

DWORD DL_getSignalStrengthDbm(BYTE ucSlaveDemod, Long* strengthDbm)
{

    mutex_lock(&mymutex);

    DWORD dwError = Error_NO_ERROR;

    deb_data("- Enter %s Function -\n",__FUNCTION__);

    dwError =  DRV_getSignalStrengthDbm(PDC, ucSlaveDemod, strengthDbm);

mutex_unlock(&mymutex);
    return(dwError);
}

DWORD DL_getChannelStatistic(BYTE ucSlaveDemod, ChannelStatistic*	channelStatistic)
{

    mutex_lock(&mymutex);

    DWORD dwError = Error_NO_ERROR;

    deb_data("- Enter %s Function -\n",__FUNCTION__);

    dwError = DRV_getChannelStatistic(PDC, ucSlaveDemod, channelStatistic);

    mutex_unlock(&mymutex);

    return(dwError);
}

DWORD DL_getChannelModulation(BYTE ucSlaveDemod, ChannelModulation*    channelModulation)
{

    mutex_lock(&mymutex);

    DWORD dwError = Error_NO_ERROR;

    deb_data("- Enter %s Function -\n",__FUNCTION__);

    dwError = DRV_getChannelModulation(PDC, ucSlaveDemod, channelModulation);

    mutex_unlock(&mymutex);

    return(dwError);
}

DWORD DL_getSNR(BYTE ucSlaveDemod, Constellation* constellation, BYTE* snr)
{

    mutex_lock(&mymutex);

    DWORD dwError = Error_NO_ERROR;
    ChannelModulation    channelModulation;
    DWORD   snr_value;

    deb_data("- Enter %s Function -\n",__FUNCTION__);

    dwError = DRV_getChannelModulation(PDC, ucSlaveDemod, &channelModulation);
    if (dwError)    return(dwError);

     dwError = DRV_getSNRValue(PDC, &snr_value);
     if (dwError)    return(dwError);

    *constellation = channelModulation.constellation;

    if(channelModulation.constellation == 0) //Constellation_QPSK 
    {
	if(snr_value < 0xB4771)    *snr = 0;
	else if(snr_value < 0xC1AED)	*snr = 1;
	else if(snr_value < 0xD0D27)   *snr = 2;
	else if(snr_value < 0xE4D19)   *snr = 3;
	else if(snr_value < 0xE5DA8)   *snr = 4;
	else if(snr_value < 0x107097)   *snr = 5;
	else if(snr_value < 0x116975)   *snr = 6;
	else if(snr_value < 0x1252D9)   *snr = 7;
	else if(snr_value < 0x131FA4)   *snr = 8;
	else if(snr_value < 0x13D5E1)   *snr = 9;
	else if(snr_value < 0x148E53)   *snr = 10;
	else if(snr_value < 0x15358B)   *snr = 11;
	else if(snr_value < 0x15DD29)   *snr = 12;
	else if(snr_value < 0x168112)   *snr = 13;
	else if(snr_value < 0x170B61)   *snr = 14;
	else if(snr_value < 0x17A532)   *snr = 15;
	else if(snr_value < 0x180F94)   *snr = 16;
	else if(snr_value < 0x186ED2)   *snr = 17;
	else if(snr_value < 0x18B271)   *snr = 18;
	else if(snr_value < 0x18E118)   *snr = 19;
	else if(snr_value < 0x18FF4B)   *snr = 20;
	else if(snr_value < 0x190AF1)   *snr = 21;
	else if(snr_value < 0x191451)   *snr = 22;
	else	*snr = 23;
    }

    else if ( channelModulation.constellation == 1) //Constellation_16QAM
    {
        if(snr_value < 0x4F0D5)    *snr = 0;
	else if(snr_value < 0x5387A)   *snr = 1;
	else if(snr_value < 0x573A4)   *snr = 2;
	else if(snr_value < 0x5A99E)   *snr = 3;
	else if(snr_value < 0x5CC80)   *snr = 4;
	else if(snr_value < 0x5EB62)   *snr = 5;
	else if(snr_value < 0x5FECF)   *snr = 6;
	else if(snr_value < 0x60B80)   *snr = 7;
	else if(snr_value < 0x62501)   *snr = 8;
	else if(snr_value < 0x64865)   *snr = 9;
	else if(snr_value < 0x69604)   *snr = 10;
	else if(snr_value < 0x6F356)   *snr = 11;
	else if(snr_value < 0x7706A)   *snr = 12;
	else if(snr_value < 0x804D3)   *snr = 13;
	else if(snr_value < 0x89D1A)   *snr = 14;
	else if(snr_value < 0x93E3D)   *snr = 15;
	else if(snr_value < 0x9E35D)   *snr = 16;
	else if(snr_value < 0xA7C3C)   *snr = 17;
	else if(snr_value < 0xAFAF8)   *snr = 18;
	else if(snr_value < 0xB719D)   *snr = 19;
	else if(snr_value < 0xBDA6A)   *snr = 20;
	else if(snr_value < 0xC0C75)   *snr = 21;
	else if(snr_value < 0xC3F7D)   *snr = 22;
	else if(snr_value < 0xC5E62)   *snr = 23;
	else if(snr_value < 0xC6C31)   *snr = 24;
	else if(snr_value < 0xC7925)   *snr = 25;
	else    *snr = 26;
    }

    else if ( channelModulation.constellation == 2) //Constellation_64QAM
    {
        if(snr_value < 0x256D0)    *snr = 0;
	else if(snr_value < 0x27A65)   *snr = 1;
	else if(snr_value < 0x29873)   *snr = 2;
	else if(snr_value < 0x2B7FE)   *snr = 3;
	else if(snr_value < 0x2CF1E)   *snr = 4;
	else if(snr_value < 0x2E234)   *snr = 5;
	else if(snr_value < 0x2F409)   *snr = 6;
	else if(snr_value < 0x30046)   *snr = 7;
	else if(snr_value < 0x30844)   *snr = 8;
	else if(snr_value < 0x30A02)   *snr = 9;
	else if(snr_value < 0x30CDE)   *snr = 10;
	else if(snr_value < 0x31031)   *snr = 11;
	else if(snr_value < 0x3144C)   *snr = 12;
	else if(snr_value < 0x315DD)   *snr = 13;
	else if(snr_value < 0x31920)   *snr = 14;
	else if(snr_value < 0x322D0)   *snr = 15;
	else if(snr_value < 0x339FC)   *snr = 16;
	else if(snr_value < 0x364A1)   *snr = 17;
	else if(snr_value < 0x38BCC)   *snr = 18;
	else if(snr_value < 0x3C7D3)   *snr = 19;
	else if(snr_value < 0x408CC)   *snr = 20;
	else if(snr_value < 0x43BED)   *snr = 21;
	else if(snr_value < 0x48061)   *snr = 22;
	else if(snr_value < 0x4BE95)   *snr = 23;
	else if(snr_value < 0x4FA7D)   *snr = 24;
	else if(snr_value < 0x52405)   *snr = 25;
	else if(snr_value < 0x5570D)   *snr = 26;
	else if(snr_value < 0x59FEB)   *snr = 27;
	else if(snr_value < 0x5BF38)   *snr = 28;
	else    *snr = 29;
    }

    else 
	deb_data("      Get constellation is failed!\n");

    mutex_unlock(&mymutex);	

    return(dwError);
}

DWORD DL_ReSetInterval(void)
{


    mutex_lock(&mymutex);

         DWORD dwError = Error_NO_ERROR;

    mutex_unlock(&mymutex);

         return(dwError);
}
//EXPORT_SYMBOL(DL_ReSetInterval);

DWORD DL_Reboot(void) 
{


    mutex_lock(&mymutex);

        DWORD dwError = Error_NO_ERROR;

        deb_data("- Enter %s Function -\n",__FUNCTION__);

        dwError = DRV_Reboot(PDC);

    mutex_unlock(&mymutex);

        return(dwError);
}

DWORD DL_CheckTunerInited(BYTE ucSlaveDemod, Bool *bOn )
{

    mutex_lock(&mymutex);

    DWORD dwError = Error_NO_ERROR;

    deb_data("- Enter %s Function -\n",__FUNCTION__);

    *bOn = PTI.bTunerInited;

    mutex_unlock(&mymutex);

    return(dwError);
}

DWORD Device_init(struct usb_device *udev,PDEVICE_CONTEXT PDCs, Bool bBoot)
{
	 DWORD error = Error_NO_ERROR;
	 BYTE filterIdx=0;
	 udevs=udev;
	 PDC=PDCs;
	 int errcount=0;

	deb_data("- Enter %s Function -\n",__FUNCTION__);

// define in Af903x.h
#ifdef QuantaMID
	printk("    === AfaDTV on Quanta  ===\n");
#endif
#ifdef EEEPC
	printk("    === AfaDTV on EEEPC ===\n");
#endif

#ifdef DRIVER_RELEASE_VERSION
        printk("        DRIVER_RELEASE_VERSION : %s\n", DRIVER_RELEASE_VERSION);
#else
	printk("        DRIVER_RELEASE_VERSION : v0.0-0\n");
#endif

#ifdef FW_RELEASE_VERSION
	printk("        FW_RELEASE_VERSION     : %s\n", FW_RELEASE_VERSION);
#else
	printk("        FW_RELEASE_VERSION     : v0_0_0_0\n");	
#endif

#ifdef Version_NUMBER
	printk("        API_RELEASE_VERSION    : %X.%X.%X\n", Version_NUMBER, Version_DATE, Version_BUILD);
#else
	printk("        API_RELEASE_VERSION    :000.00000000.0\n");
#endif


//	printk("	FW_RELEASE_VERSION : %s\n", FW_RELEASE_VERSION);
//	printk("	API_RELEASE_VERSION : %X.%X.%X\n", Version_NUMBER, Version_DATE, Version_BUILD);


	//************* Set Device init Info *************//
	PDC->bEnterSuspend = false;
    	PDC->bSurpriseRemoval = false;
    	PDC->bDevNotResp = false;
    	PDC->bSelectiveSuspend = false; 
	PDC->bTunerPowerOff = false;

	if (bBoot)
	{
		PDC->bSupportSelSuspend = false;
		PDC->Demodulator.userData = (Handle)PDC;
		PDC->Demodulator.chipNumber = 1; 
		PDC->architecture=Architecture_DCA;
		PDC->Demodulator.frequency[0] = 666000;
		PDC->Demodulator.bandwidth[0] = 8000;
		PDC->bIrTblDownload = false;
		PDC->fc[0].tunerinfo.TunerId = 0;
		PDC->fc[1].tunerinfo.TunerId = 0;
		PDC->bDualTs=false;	
        	PDC->FilterCnt = 0;
		PDC->StreamType = StreamType_DVBT_DATAGRAM;
		PDC->UsbCtrlTimeOut = 1;
	}
	else {
        	PDC->UsbCtrlTimeOut = 5;
    	}//bBoot

#ifdef AFA_USB_DEVICE 	
	if (bBoot) {
		//************* Set USB Info *************//
		PDC->MaxPacketSize = 0x0200; //default USB2.0
		PDC->UsbMode = (PDC->MaxPacketSize == 0x200)?0x0200:0x0110;  
		deb_data("USB mode= 0x%x\n", PDC->UsbMode);

		PDC->TsPacketCount = (PDC->UsbMode == 0x200)?TS_PACKET_COUNT_HI:TS_PACKET_COUNT_FU;
		PDC->TsFrames = (PDC->UsbMode == 0x200)?TS_FRAMES_HI:TS_FRAMES_FU;
		PDC->TsFrameSize = TS_PACKET_SIZE*PDC->TsPacketCount;
		PDC->TsFrameSizeDw = PDC->TsFrameSize/4;
	}
	PDC->bEP12Error = false;
    	PDC->bEP45Error = false; 
    	PDC->ForceWrite = false;    
    	PDC->ulActiveFilter = 0;
#else
    	PDC->bSupportSuspend = false; 
#endif//AFA_USB_DEVICE
	
#ifdef AFA_USB_DEVICE
	if(bBoot)
    	{
		//patch for eeepc
        	error = DL_SetBusTuner (PDC, Bus_USB, Tuner_Afatech_AF9007);
        	PDC->UsbCtrlTimeOut = 5;
        
        	error = DL_SetBusTuner (PDC, Bus_USB, Tuner_Afatech_AF9007);
        	if (error)
        	{
            		deb_data("First DL_SetBusTuner fail : 0x%08x\n",error );
			errcount++;
            		goto Exit; 
        	}

        	error =DL_GetEEPROMConfig(PDC);
        	if (error)
        	{
            		deb_data("DL_GetEEPROMConfig fail : 0x%08x\n", error);
			errcount++;
            		goto Exit;
        	}
	}//bBoot
	
	error = DL_SetBusTuner(PDC, Bus_USB, PDC->fc[0].tunerinfo.TunerId);
    	if (error)
    	{
        	deb_data("DL_SetBusTuner fail!\n");
		errcount++;
        	goto Exit;
    	}

	
	 if (PDC->Demodulator.chipNumber == 2 && !PDC->Demodulator.booted) //plug/cold-boot/S4
    	{
        	error = DL_NIMReset(PDC);            
    	}
    	else if(PDC->Demodulator.chipNumber == 2 && PDC->Demodulator.booted) //warm-boot/(S1)
    	{
        	error = DL_NIMSuspend(PDC, false); 
		error = DL_TunerWakeup(PDC); //actually for mt2266
    	}
	
	
	if(PDC->Demodulator.chipNumber == 1 && PDC->Demodulator.booted) //warm-boot/(S1)
	{
		error = DL_TunerWakeup(PDC);
	}
	if(error) deb_data("DL_NIMReset or DL_NIMSuspend or DL_TunerWakeup fail!\n"); 

	error = DL_Initialize(PDC);
    	if (error) 
    	{
        	deb_data("DL_Initialize fail! 0x%08x\n", error);
		errcount++;
        	goto Exit;
    	}
	
	if (PDC->bIrTblDownload) 
    	{
        	error = DL_IrTblDownload(PDC);
       	 	if (error) {deb_data("DL_IrTblDownload fail");errcount++;}
    	}

   	 if (PDC->Demodulator.chipNumber == 2)
    	{
        	error = DL_USBSetup(PDC);
        	if (error) deb_data("DRV_SDIOSetup fail!");
    	}

    	if (PDC->Demodulator.chipNumber == 2)
    	{
        	error = DL_InitNIMSuspendRegs(PDC);
        	if (error) deb_data("DL_InitNIMSuspendRegs fail!");
    	}	
	
    	for (filterIdx=0; filterIdx< PDC->Demodulator.chipNumber; filterIdx++) 
    	{  
        	if (bBoot || !PDC->fc[filterIdx].GraphBuilt)
        	{
            		error = DRV_ApCtrl(PDC, filterIdx, false);
            		if (error) {deb_data("%d: DRV_ApCtrl Fail!\n", filterIdx);errcount++;}
        	} 
    	}        
	
/*    	if(PDC->Demodulator.chipNumber == 2)
    	{
       	 if(PDC->fc[0].GraphBuilt==0 && PDC->fc[1].GraphBuilt==0)
        	{
            		error = DL_NIMSuspend(PDC, true);            
            		if(error) deb_data("DL_NIMSuspend fail!");   
        	}
    	}
*/
	deb_data("	%s success!! \n",__FUNCTION__);

Exit:
#endif //AFA_USB_DEVICE
	
	if(errcount)
                printk( "[Device_init] Error %d\n", errcount);
	return (error);
}
//EXPORT_SYMBOL(Device_init);

