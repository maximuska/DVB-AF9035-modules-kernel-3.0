#include "af903x.h"

bool  DevicePower;
static int af903x_pid_filter_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
    int ret =0;
#if LINUX_VERSION_CODE >  KERNEL_VERSION(2,6,18)
    deb_data("%s: onoff:%d\n", __func__, onoff);

	if ( PDC->fc[adap->id].bEnPID !=  onoff )
		DL_ResetPID((BYTE)adap->id);

	PDC->fc[adap->id].bEnPID =  onoff;
	
	DL_PIDOnOff((BYTE)adap->id,onoff);
#endif

    return ret;
}

static int af903x_pid_filter(struct dvb_usb_adapter *adap, int index, u16 pidnum,
    int onoff)
{
    int ret = 0;
 #if LINUX_VERSION_CODE >  KERNEL_VERSION(2,6,18)
    Pid pid;
    deb_data("- %s: set pid filter, index %d, pid %x, onoff %d, now_onoff %d.\n",
	__func__, index, pidnum, onoff, PDC->fc[adap->id].bEnPID);

	if (onoff && !PDC->fc[adap->id].bEnPID)
	{
		DL_ResetPID((BYTE)adap->id);
		PDC->fc[adap->id].bEnPID =  onoff;
		DL_PIDOnOff((BYTE)adap->id,onoff);
		pid.sectionType = SectionType_TABLE;
    		pid.table = 0x00;
    		pid.duration = 0xFF;
	}
	
    	pid.value = (Word)pidnum;
	if (onoff){
		ret = DL_AddPID((BYTE)adap->id, index, pid);
	}else{
		ret = DL_RemovePID((BYTE)adap->id, index, pid);
	}
#endif

    return ret;
}

static int af903x_download_firmware(struct usb_device *udev, const struct firmware *fw)
{
	int ret=0;
	deb_data("- Enter %s Function -\n",__FUNCTION__);
	
	return ret;
}

static int af903x_powerctrl(struct dvb_usb_device *d, int onoff)
{

	int ret;
	DevicePower = onoff;

#if LINUX_VERSION_CODE >  KERNEL_VERSION(2,6,18)
	deb_data("- Enter %s Function - chip=%d:%s\n",__FUNCTION__, d->adapter->id, onoff?"ON":"OFF");
	ret = DL_ApCtrl(d->adapter->id, onoff);
#else
	deb_data("- Enter %s Function - %s\n",__FUNCTION__, onoff?"ON":"OFF");
	ret = DL_ApCtrl(0, onoff);
#endif
	if(ret) deb_data("	af903x_powerctrl Fail: 0x%04X\n", ret);

	return ret;
}

static int af903x_identify_state(struct usb_device *udev, struct dvb_usb_device_properties *props,
			struct dvb_usb_device_description **desc, int *cold)
{
	deb_data("- Enter %s Function -\n",__FUNCTION__);
	*cold = 0;

	return 0;
}

static int af903x_frontend_attach(struct dvb_usb_adapter *adap)
{
#if LINUX_VERSION_CODE >  KERNEL_VERSION(2,6,18)
	deb_data("- Enter %s Function - chip=%d\n", __FUNCTION__, adap->id);
#else
	 deb_data("- Enter %s Function - \n", __FUNCTION__);
#endif
	adap->fe = af903x_attach(1);	

	return adap->fe == NULL ? -ENODEV : 0;
}

static int af903x_tuner_attach(struct dvb_usb_adapter *adap)
{
#if LINUX_VERSION_CODE >  KERNEL_VERSION(2,6,18)
	deb_data("- Enter %s Function - chip=%d\n",__FUNCTION__, adap->id);
#else
         deb_data("- Enter %s Function - \n", __FUNCTION__);
#endif
	tuner_attach(adap->fe);
	return  0;
}

static int af903x_streaming_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
#if LINUX_VERSION_CODE >  KERNEL_VERSION(2,6,18)	    
	deb_data("- Enter %s Function - (%s) streaming state for chip=%d\n",__FUNCTION__, onoff?"ON":"OFF", adap->id);
	//PID off
	DL_ResetPID((BYTE)adap->id);
	PDC->fc[adap->id].bEnPID =  0;
	DL_PIDOnOff((BYTE)adap->id,0);
#else
	deb_data("- Enter %s Function - (%s) streaming state \n",__FUNCTION__, onoff?"ON":"OFF");
#endif
	
	return 0;
}

struct usb_device_id af903x_usb_id_table[] = {
		{ USB_DEVICE(0x15A4,0x1000) },
		{ USB_DEVICE(0x15A4,0x1001) },
		{ USB_DEVICE(0x15A4,0x1002) },
		{ USB_DEVICE(0x15A4,0x1003) },
		{ USB_DEVICE(0x15A4,0x9035) },
		{ 0},		/* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, af903x_usb_id_table);

struct dvb_usb_device_properties af903x_properties[] = {
	{
		.usb_ctrl          = DEVICE_SPECIFIC,
		.download_firmware = af903x_download_firmware,
		.no_reconnect      = 1,
		.power_ctrl		   = af903x_powerctrl,
		.identify_state    = af903x_identify_state,
		
#if LINUX_VERSION_CODE ==  KERNEL_VERSION(2,6,18)
		.caps = DVB_USB_HAS_PID_FILTER | DVB_USB_NEED_PID_FILTERING,
                .pid_filter_count = 32,
                .frontend_attach  = af903x_frontend_attach,
                .tuner_attach     = af903x_tuner_attach,
	        .streaming_ctrl   = af903x_streaming_ctrl,
		.urb = {
			.type = DVB_USB_BULK,
			.count = 10,
			.endpoint = 0x84,
			.u = {
				.bulk = {
					.buffersize = 65424,
				}
			}
		},	
#else
		.num_adapters = 1,
		.adapter = {
			{
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = af903x_pid_filter,
				.pid_filter_ctrl  = af903x_pid_filter_ctrl,
				.frontend_attach  = af903x_frontend_attach,
				.tuner_attach     = af903x_tuner_attach,
				.streaming_ctrl   = af903x_streaming_ctrl,
				.stream = { 
					.type = USB_BULK,
					.count = 4,
					.endpoint = 0x84,
					.u = {
						.bulk = {
							.buffersize = 65424,
						}
					}
				}
			},
			{
                           .caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
                           .pid_filter_count = 32,
                           .pid_filter       = af903x_pid_filter,
                           .pid_filter_ctrl  = af903x_pid_filter_ctrl,
				.frontend_attach  = af903x_frontend_attach,
				.tuner_attach     = af903x_tuner_attach,
				.streaming_ctrl   = af903x_streaming_ctrl,
				.stream = {
					.type = USB_BULK,
					.count = 4,
					.endpoint = 0x85,
					.u = {
					    .bulk = {
						.buffersize = 65424,
					    }
					}
				}
			},
		},
#endif
		.num_device_descs =1,
		.devices =  {
                        {   	"ITEtech USB2.0 DVB-T Recevier",
                        	{ &af903x_usb_id_table[0], &af903x_usb_id_table[1],&af903x_usb_id_table[2], 
				&af903x_usb_id_table[3], &af903x_usb_id_table[4], NULL},
                            	{ NULL },
                        },
			{NULL},

		}
	}
};

int af903x_device_count = ARRAY_SIZE(af903x_properties);
