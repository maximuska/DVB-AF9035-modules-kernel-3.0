#include "demodulatorextend.h"
//#include "i2cimpl.h" //for Linux
#include "usb2impl.h"
//#include "spiimpl.h"
//#include "sdioimpl.h"
//#include "i2uimpl.h"
#include "cmd.h"
//#include "i2u.h"
//#include "af9035u2iimpl.h"

#include "Afa_AF9007.h"
#include "Afa_PEACOCK.h"
#include "Freescale_MC44CD02.h"
#include "Integrant_ITD3020.h"
#include "Maxlinear_MXL5005.h"
#include "Microtune_MT2260B0.h"
#include "Microtune_MT2266.h"
#include "Panasonic_ENV77H11D5.h"
#include "Philips_TD1316AFIHP.h"
#include "Philips_TDA18291HN.h"
#include "Xceive_XC3028L.h"
#include "Infineon_TUA9001.h"
#include "Fitipower_FC0011.h"
#include "Infineon_TUA6039.h"
#include "Philips_TDA18271.h"
#include "Philips_FQD1218ME_MK5.h"
#include "Xceive_XC4000.h"
#include "Philips_TDA18271_C2.h"
#include "Infineon_TUA8010.h"
#include "FCI_FC2580.h"
#include "Fitipower_FC0012.h"
#include "Philips_TDA18271_C2_Askey.h"
#include "Elonics_E4000.h"

static PidInfo pidInfo;
BusDescription busDesc[] =
{
    /** 0: NULL bus */
    {
        NULL,
        NULL,
        NULL,
        NULL,
    },
    /** 1: I2C bus */
    {
/*        I2c_getDriver,
        I2c_writeControlBus,
        I2c_readControlBus,
        NULL,
*/    },
    /** 2: USB bus */
    {
        Usb2_getDriver,
        Usb2_writeControlBus,
        Usb2_readControlBus,
        Usb2_readDataBus,
    },
    /** 3: SPI bus */
    {
/*        Spi_getDriver,
        Spi_writeControlBus,
        Spi_readControlBus,
        Spi_readDataBus,
*/    },
    /** 4: SDIO bus */
    {
/*        Sdio_getDriver,
        Sdio_writeControlBus,
        Sdio_readControlBus,
        Sdio_readDataBus,
*/    },
    /** 5: USB11 bus */
    {
        Usb2_getDriver,
        Usb2_writeControlBus,
        Usb2_readControlBus,
        Usb2_readDataBus,
    },
    /** 6: I2M bus - I2C for old mail box */
    {
/*        I2u_getDriver,
        I2u_writeControlBus,
        I2u_readControlBus,
        NULL,
*/    },
    /** 7: I2U bus - 9015 USB for old mail box */
    {
/*        I2u_getDriver,
        I2u_writeControlBus,
        I2u_readControlBus,
        NULL,
*/    },
    /** 8: I2U2 bus - 9015 USB for new mail box */
    {
/*        I2u_getDriver,
        I2u_writeControlBus,
        I2u_readControlBus,
        NULL,
*/    },
    /** 9: 9035U2I bus - 9035 USB to I2C */
    {
/*        Af9035u2i_getDriver,
        Af9035u2i_writeControlBus,
        Af9035u2i_readControlBus,
        NULL,
*/    },
};

CmdDescription cmdDesc[] =
{
    /** NULL Bus */
    {
        0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    /** 1:I2C Bus */
    {
        255,
        &busDesc[1],
        Cmd_writeRegisters,
        Cmd_writeTunerRegisters,
        Cmd_writeEepromValues,
        Cmd_readRegisters,
        Cmd_readTunerRegisters,
        Cmd_readEepromValues,
        NULL,
        Cmd_loadFirmware,
        Cmd_reboot,
        Cmd_sendCommand,
        Cmd_receiveData
    },
    /** 2:USB Bus */
    {
        63,
        &busDesc[2],
        Cmd_writeRegisters,
        Cmd_writeTunerRegisters,
        Cmd_writeEepromValues,
        Cmd_readRegisters,
        Cmd_readTunerRegisters,
        Cmd_readEepromValues,
        NULL,
        Cmd_loadFirmware,
        Cmd_reboot,
        Cmd_sendCommand,
        Cmd_receiveData
    },
    /** 3:SPI Bus */
    {
        255,
        &busDesc[3],
        Cmd_writeRegisters,
        Cmd_writeTunerRegisters,
        Cmd_writeEepromValues,
        Cmd_readRegisters,
        Cmd_readTunerRegisters,
        Cmd_readEepromValues,
        NULL,
        Cmd_loadFirmware,
        Cmd_reboot,
        Cmd_sendCommand,
        Cmd_receiveData
    },
    /** 4:SDIO Bus */
    {
        255,
        &busDesc[4],
        Cmd_writeRegisters,
        Cmd_writeTunerRegisters,
        Cmd_writeEepromValues,
        Cmd_readRegisters,
        Cmd_readTunerRegisters,
        Cmd_readEepromValues,
        NULL,
        Cmd_loadFirmware,
        Cmd_reboot,
        Cmd_sendCommand,
        Cmd_receiveData
    },
    /** 5:USB11 Bus */
    {
        63,
        &busDesc[5],
        Cmd_writeRegisters,
        Cmd_writeTunerRegisters,
        Cmd_writeEepromValues,
        Cmd_readRegisters,
        Cmd_readTunerRegisters,
        Cmd_readEepromValues,
        NULL,
        Cmd_loadFirmware,
        Cmd_reboot,
        Cmd_sendCommand,
        Cmd_receiveData
    },
    /** 6:I2C for old mailbox */
    {
/*        16,
        &busDesc[6],
        I2u_writeRegisters,
        I2u_writeTunerRegisters,
        NULL,
        I2u_readRegisters,
        I2u_readTunerRegisters,
        NULL,
        I2u_modifyRegister,
        NULL,
        NULL,
        NULL,
        NULL
*/    },
    /** 7:USB for old mailbox */
    {
/*        16,
        &busDesc[7],
        I2u_writeRegisters,
        I2u_writeTunerRegisters,
        NULL,
        I2u_readRegisters,
        I2u_readTunerRegisters,
        NULL,
        I2u_modifyRegister,
        NULL,
        NULL,
        NULL,
        NULL
*/    },
    /** 8:USB for new mailbox */
    {
/*        55,
        &busDesc[8],
        Cmd_writeRegisters,
        Cmd_writeTunerRegisters,
        Cmd_writeEepromValues,
        Cmd_readRegisters,
        Cmd_readTunerRegisters,
        Cmd_readEepromValues,
        NULL,
        Cmd_loadFirmware,
        Cmd_reboot,
        Cmd_sendCommand,
        Cmd_receiveData
*/    },
    /** 9:9035 USB to I2C Bus */
    {
/*        54,
        &busDesc[9],
        Cmd_writeRegisters,
        Cmd_writeTunerRegisters,
        Cmd_writeEepromValues,
        Cmd_readRegisters,
        Cmd_readTunerRegisters,
        Cmd_readEepromValues,
        NULL,
        Cmd_loadFirmware,
        Cmd_reboot,
        Cmd_sendCommand,
        Cmd_receiveData
*/    },
};

Dword Demodulator_setBusTuner (
    IN  Demodulator*    demodulator,
    IN  Word            busId,
    IN  Word            tunerId
) {
    Dword error = Error_NO_ERROR;

    Ganymede* ganymede;

    ganymede = (Ganymede*) demodulator;

    ganymede->cmdDescription = &cmdDesc[busId];
    ganymede->busId = busId;

/*    if (busId == Bus_I2U2) {
        I2u_setChipAddress (demodulator, 0x38);
    }
*/
    switch (tunerId)
    {
    case Tuner_Afatech_AF9007:
        ganymede->tunerDescription = &tuner_AF9007;
        break;
    case Tuner_Panasonic_ENV77H11D5:
        ganymede->tunerDescription = &tuner_ENV77H11D5;
        break;
    case Tuner_Philip_TD1316AFIHP:
        ganymede->tunerDescription = &tuner_TD1316AFIHP;
        break;
    case Tuner_Maxlinear_MXL5005:
        ganymede->tunerDescription = &tuner_MXL5005;
        break;
    case Tuner_Freescale_MC44CD02:
        ganymede->tunerDescription = &tuner_MC44CD02;
        break;
    case Tuner_Microtune_MT2260B0:
        ganymede->tunerDescription = &tuner_MT2260B0;
        break;
    case Tuner_Philips_TDA18291HN:
        ganymede->tunerDescription = &tuner_TDA18291HN;
        break;
    case Tuner_Microtune_MT2266:
        ganymede->tunerDescription = &tuner_MT2266;
        MT2266_supportTA4029CTC ((Demodulator*) &ganymede, 0);
        break;
    case Tuner_Integrant_ITD3020:
        ganymede->tunerDescription = &tuner_ITD3020;
        break;
    case Tuner_Afatech_PEACOCK:
        ganymede->tunerDescription = &tuner_PEACOCK;
        break;
    case Tuner_Xceive_XC3028L:
        ganymede->tunerDescription = &tuner_XC3028L;
        break;
    case Tuner_Infineon_TUA9001:
        ganymede->tunerDescription = &tuner_TUA9001;
        break;
    case Tuner_Fitipower_FC0011:
        ganymede->tunerDescription = &tuner_FC0011;
        break;
    case Tuner_Infineon_TUA6039:
        ganymede->tunerDescription = &tuner_TUA6039;
        break;
    case Tuner_Philips_TDA18271:
        ganymede->tunerDescription = &tuner_TDA18271;
        break;
    case Tuner_Philips_FQD1218ME_MK5:
        ganymede->tunerDescription = &tuner_FQD1218ME_MK5;
        break;
    case Tuner_Xceive_XC4000:
        ganymede->tunerDescription = &tuner_XC4000;
        break;
    case Tuner_Philips_TDA18271_C2:
        ganymede->tunerDescription = &tuner_TDA18271_C2;
        break;
    case Tuner_Infineon_TUA8010:
        ganymede->tunerDescription = &tuner_TUA8010;
        break;
    case Tuner_FCI_FC2580:
        ganymede->tunerDescription = &tuner_FC2580;
        break;
    case Tuner_Microtune_MT2266_TA4029CTC:
        ganymede->tunerDescription = &tuner_MT2266;
        MT2266_supportTA4029CTC ((Demodulator*) &ganymede, 1);
        break;
    case Tuner_Fitipower_FC0012:
        ganymede->tunerDescription = &tuner_FC0012;
        break;
    case Tuner_Philips_TDA18271_C2_Askey:
        ganymede->tunerDescription = &tuner_TDA18271_C2_Askey;
        break;
    case Tuner_Elonics_E4000:
        ganymede->tunerDescription = &tuner_E4000;
	break;
    default:
        error = Error_INVALID_TUNER_TYPE;
        goto exit;
        break;
    }

    if (ganymede->tunerDescription->tunerScript == NULL) {
        ganymede->tunerDescription->tunerScript = NULL;
        ganymede->tunerDescription->tunerScriptSets = NULL;
    }


exit:
    return(error);
}
Dword Demodulator_getChannelStatistic (
    IN  Demodulator*            demodulator,
    IN  Byte                    chip,
    OUT ChannelStatistic*       channelStatistic
) {
    Dword error = Error_NO_ERROR;

#if User_USE_DRIVER
    DWORD number;
    BOOL result;
    GetChannelStatisticRequest request;
    Ganymede* ganymede;

    ganymede = (Ganymede*) demodulator;

    if (ganymede->driver != NULL) {
        request.chip = chip;
        request.channelStatistic = channelStatistic;
        result = DeviceIoControl (
                    ganymede->driver,
                    IOCTL_AFA_DEMOD_GETCHANNELSTATISTIC,
                    &request,
                    sizeof (request),
                    NULL,
                    0,
                    &number,
                    NULL
        );
        error = request.error;
    } else {
        error = Error_DRIVER_INVALID;
    }
#else
    Dword postErrCnt;
    Dword postBitCnt;
    Word rsdAbortCnt;
    Ganymede* ganymede;


    ganymede = (Ganymede*) demodulator;


    /** Get BER if couter is ready, error = Error_RSD_COUNTER_NOT_READY if counter is not ready */
    if (ganymede->architecture == Architecture_PIP) {
        error = Standard_getPostVitBer (demodulator, chip, &postErrCnt, &postBitCnt, &rsdAbortCnt);
        if (error == Error_NO_ERROR) {
            ganymede->channelStatistic[chip].postVitErrorCount = postErrCnt;
            ganymede->channelStatistic[chip].postVitBitCount = postBitCnt;
            ganymede->channelStatistic[chip].abortCount = rsdAbortCnt;
        }
    } else {
        error = Standard_getPostVitBer (demodulator, 0, &postErrCnt, &postBitCnt, &rsdAbortCnt);
        if (error == Error_NO_ERROR) {
            ganymede->channelStatistic[chip].postVitErrorCount = postErrCnt;
            ganymede->channelStatistic[chip].postVitBitCount = postBitCnt;
            ganymede->channelStatistic[chip].abortCount = rsdAbortCnt;
        }
    }

    *channelStatistic = ganymede->channelStatistic[chip];

#endif

    return (error);
}
Dword Demodulator_addPid (
    IN  Demodulator*    demodulator,
    IN  Byte            chip,
    IN  Pid             pid
) {
    Dword error = Error_NO_ERROR;

#if User_USE_DRIVER
    DWORD number;
    BOOL result;
    AddPidRequest request;
    Ganymede* ganymede;

    ganymede = (Ganymede*) demodulator;

    if (ganymede->driver != NULL) {
        request.chip = chip;
        request.pid = pid;
        result = DeviceIoControl (
                    ganymede->driver,
                    IOCTL_AFA_DEMOD_ADDPID,
                    &request,
                    sizeof (request),
                    NULL,
                    0,
                    &number,
                    NULL
        );
        error = request.error;
    } else {
        error = Error_DRIVER_INVALID;
    }
#else
    Byte writeBuffer[2];
    Byte i, j;
    Bool found;
    Ganymede* ganymede;

    ganymede = (Ganymede*) demodulator;

    if (pidInfo.pidinit == False) {
        for (i = 0; i < ganymede->chipNumber; i++) {
            for (j = 0; j < 32; j++) {
                pidInfo.pidtable[i].pid[j] = 0xFFFF;
            }
        }
        pidInfo.pidinit = True;
    }

    /** Enable pid filter */
    if (pidInfo.pidcount == 0) {
        error = Standard_writeRegisterBits (demodulator, chip, Processor_OFDM, p_mp2if_pid_en, mp2if_pid_en_pos, mp2if_pid_en_len, 1);
        if (error) goto exit;
    } else {
        found = False;
        for (i = 0; i < 32; i++) {
            if (pidInfo.pidtable[chip].pid[i] == pid.value) {
                found = True;
                break;
            }
        }
        if (found == True)
            goto exit;
    }

    for (i = 0; i < 32; i++) {
        if (pidInfo.pidtable[chip].pid[i] == 0xFFFF)
            break;
    }
    if (i == 32) {
        error = Error_PID_FILTER_FULL;
        goto exit;
    }

    writeBuffer[0] = (Byte) pid.value;
    writeBuffer[1] = (Byte) (pid.value >> 8);

    error = Standard_writeRegisters (demodulator, chip, Processor_OFDM, p_mp2if_pid_dat_l, 2, writeBuffer);
    if (error) goto exit;

    error = Standard_writeRegisterBits (demodulator, chip, Processor_OFDM, p_mp2if_pid_index_en, mp2if_pid_index_en_pos, mp2if_pid_index_en_len, 1);
    if (error) goto exit;

    error = Standard_writeRegister (demodulator, chip, Processor_OFDM, p_mp2if_pid_index, i);
    if (error) goto exit;

    pidInfo.pidtable[chip].pid[i] = pid.value;
    pidInfo.pidcount++;

exit :
#endif

    return (error);
}


Dword Demodulator_addPidAt (
    IN  Demodulator*    demodulator,
    IN  Byte            chip,
    IN  Byte            index,
    IN  Pid             pid
) {
	return (Demodulator_addPidToFilter (demodulator, chip, index, pid));
}


Dword Demodulator_removePid (
    IN  Demodulator*    demodulator,
    IN  Byte            chip,
    IN  Pid             pid
) {
    Dword error = Error_NO_ERROR;

#if User_USE_DRIVER
    DWORD number;
    BOOL result;
    RemovePidRequest request;
    Ganymede* ganymede;

    ganymede = (Ganymede*) demodulator;

    if (ganymede->driver != NULL) {
        request.chip = chip;
        request.pid = pid;
        result = DeviceIoControl (
                    ganymede->driver,
                    IOCTL_AFA_DEMOD_REMOVEPID,
                    &request,
                    sizeof (request),
                    NULL,
                    0,
                    &number,
                    NULL
        );
        error = request.error;
    } else {
        error = Error_DRIVER_INVALID;
    }
#else
    Byte i;
    Bool found;
    Interrupts interrupts;
    Ganymede* ganymede;

    ganymede = (Ganymede*) demodulator;

    found = False;
    for (i = 0; i < 32; i++) {
        if (pidInfo.pidtable[chip].pid[i] == pid.value) {
            found = True;
            break;
        }
    }
    if (found == False)
        goto exit;

    error = Standard_writeRegisterBits (demodulator, chip, Processor_OFDM, p_mp2if_pid_index_en, mp2if_pid_index_en_pos, mp2if_pid_index_en_len, 0);
    if (error) goto exit;

    error = Standard_writeRegister (demodulator, chip, Processor_OFDM, p_mp2if_pid_index, i);
    if (error) goto exit;

    pidInfo.pidtable[chip].pid[i] = 0xFFFF;

    /** Disable pid filter */
    if (pidInfo.pidcount == 1) {
        error = Standard_writeRegisterBits (demodulator, chip, Processor_OFDM, p_mp2if_pid_en, mp2if_pid_en_pos, mp2if_pid_en_len, 0);

        error = Standard_getInterrupts (demodulator, &interrupts);
        if (error) goto exit;
        if (interrupts & Interrupt_DVBT) {
            error = Standard_clearInterrupt (demodulator, Interrupt_DVBT);
            if (error) goto exit;
        }
    }

    pidInfo.pidcount--;

exit :
#endif

    return (error);
}


Dword Demodulator_removePidAt (
    IN  Demodulator*    demodulator,
    IN  Byte            chip,
	IN  Byte			index,
    IN  Pid             pid
) {
    Dword error = Error_NO_ERROR;

#if User_USE_DRIVER
	DWORD number;
	BOOL result;
	RemovePidAtRequest request;
	Ganymede* ganymede;

	ganymede = (Ganymede*) demodulator;
	
	if (ganymede->driver != NULL) {
		request.chip = chip;
		request.index = index;
		request.pid = pid;
		result = DeviceIoControl (
					ganymede->driver,
					IOCTL_AFA_DEMOD_REMOVEPIDAT,
					&request,
					sizeof (request),
					NULL,
					0,
					&number,
					NULL
		);
		error = request.error;
	} else {
		error = Error_DRIVER_INVALID;
	}
#else
	Ganymede* ganymede;

	ganymede = (Ganymede*) demodulator;

	error = Standard_writeRegisterBits (demodulator, chip, Processor_OFDM, p_mp2if_pid_index_en, mp2if_pid_index_en_pos, mp2if_pid_index_en_len, 0);
	if (error) goto exit;

	error = Standard_writeRegister (demodulator, chip, Processor_OFDM, p_mp2if_pid_index, index);
	if (error) goto exit;
exit :
#endif

	return (error);
}


Dword Demodulator_resetPid (
    IN  Demodulator*    demodulator,
    IN  Byte            chip
) {
    Dword error = Error_NO_ERROR;

#if User_USE_DRIVER
#else
    Byte i;
    Ganymede* ganymede;

    ganymede = (Ganymede*) demodulator;

    for (i = 0; i < 32; i++) {
        pidInfo.pidtable[chip].pid[i] = 0xFFFF;
    }
    error = Standard_writeRegisterBits (demodulator, chip, Processor_OFDM, p_mp2if_pid_rst, mp2if_pid_rst_pos, mp2if_pid_rst_len, 1);
    if (error) goto exit;

    pidInfo.pidcount = 0;

exit :
#endif

    return (error);
}


#if UNDER_CE
#else
extern long ActiveSync;
#endif

Dword Demodulator_controlActiveSync (
    IN Demodulator* demodulator,
    IN Byte         control
) {
#if UNDER_CE
//#else //for Linux
    if (control == 0)
        ActiveSync = 0;
    else
        ActiveSync = 1;
#endif

    return (Error_NO_ERROR);
}


Dword Demodulator_setStatisticRange (
    IN  Demodulator*    demodulator,
    IN  Byte            chip,
    IN  Byte            superFrameCount,
    IN  Word            packetUnit
) {
    return (Demodulator_setViterbiRange (demodulator, chip, superFrameCount, packetUnit));
}


Dword Demodulator_getStatisticRange (
    IN  Demodulator*    demodulator,
    IN  Byte            chip,
    IN  Byte*           superFrameCount,
    IN  Word*           packetUnit
) {
    return (Demodulator_getViterbiRange (demodulator, chip, superFrameCount, packetUnit));
}
