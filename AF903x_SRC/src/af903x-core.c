#include "af903x.h"

DEVICE_CONTEXT DC;
bool TunerInited0, TunerInited1, DeviceReboot;
DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

static int af903x_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	int retval = -ENOMEM;
	int i;

	deb_data("===af903x usb device pluged in!! ===\n");
	retval = Device_init(interface_to_usbdev(intf),&DC, true);
	if (retval){
                if(retval) deb_data("Device_init Fail: 0x%08x\n", retval);
		return retval;
        }

	if ( af903x_device_count > 2)
		af903x_device_count = 2;
	
	for (i = 0; i < af903x_device_count; i++)
	{
#if LINUX_VERSION_CODE >  KERNEL_VERSION(2,6,18)
	    if (DC.architecture == Architecture_PIP)
		af903x_properties[i].num_adapters = 2;
#endif

#if LINUX_VERSION_CODE <=  KERNEL_VERSION(2,6,25)
	    if (dvb_usb_device_init(intf, &af903x_properties[i], THIS_MODULE, NULL) == 0)
		{deb_data("dvb_usb_device_init success!!\n");return 0;}
#else
	    if (dvb_usb_device_init(intf, &af903x_properties[i], THIS_MODULE, NULL,adapter_nr) == 0)
		{deb_data("dvb_usb_device_init success!!\n");return 0;}
#endif
	}

	return -ENOMEM;
}
static int af903x_suspend(struct usb_interface *intf, u32 state)
{
	int error;
	deb_data("Enter %s Function\n",__FUNCTION__);

#ifdef EEEPC
	error = DL_Reboot();
#else
    if (DevicePower)
    {
	error = DL_CheckTunerInited(0, &TunerInited0);
	error = DL_CheckTunerInited(1, &TunerInited1);

	error = DL_ApCtrl(0, 0);
	error = DL_ApCtrl(1, 0);
	if (error) {deb_data("DL_ApCtrl error : 0x%x\n", error);}

	DeviceReboot = true;
    }
#endif
	return 0;
}

static int af903x_resume(struct usb_interface *intf)
{
	int retval = -ENOMEM;
	int error;
	deb_data("Enter %s Function\n",__FUNCTION__);

#ifdef EEEPC
#else
    if(DeviceReboot == true)
    {
	retval = Device_init(interface_to_usbdev(intf),&DC, false);
        if (retval)
                if(retval) deb_data("Device_init Fail: 0x%08x\n", retval);

	if (TunerInited0)
	    error = DL_ApCtrl(0, 1);
	if (TunerInited1)
	    error = DL_ApCtrl(1, 1);
    }
#endif
        return 0;
}


static struct usb_driver af903x_driver = {
#if LINUX_VERSION_CODE <=  KERNEL_VERSION(2,6,15)
	.owner = THIS_MODULE,
#endif
	.name       = "dvb_usb_af903x",
	.probe      = af903x_probe,
	.disconnect = dvb_usb_device_exit,
	.id_table   = af903x_usb_id_table,
//	.suspend    = af903x_suspend,
//	.resume     = af903x_resume,
};

static int __init af903x_module_init(void)
{
	int result;

	info("%s",__FUNCTION__);
	deb_data("dvb_usb_af903x Module is loaded \n");

	if ((result = usb_register(&af903x_driver))) {
		err("usb_register failed. Error number %d",result);
		return result;
	}
	return 0;
}

static void __exit af903x_module_exit(void)
{
	deb_data("dvb_usb_af903x Module is unloaded!\n");
	usb_deregister(&af903x_driver);
}

module_init (af903x_module_init);
module_exit (af903x_module_exit);

MODULE_AUTHOR("Jimmy Chen <JyunYu.Chen@ite.com.tw>");
MODULE_DESCRIPTION("Driver for devices based on ITEtech AF903X");
MODULE_VERSION(DRIVER_RELEASE_VERSION);
MODULE_LICENSE("GPL");
