#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/usb.h>

#define USB_VENDOR_ID       ( 0x2717 )      //USB device's vendor ID
#define USB_PRODUCT_ID      ( 0xff40 )      //USB device's product ID


static int etx_usb_probe(struct usb_interface *interface,
                        const struct usb_device_id *id)
{

    dev_info(&interface->dev, "USB Driver Probed: Vendor ID : 0x%02x,\t"
             "Product ID : 0x%02x\n", id->idVendor, id->idProduct);


    return 0;  //return 0 indicates we are managing this device
}


static void etx_usb_disconnect(struct usb_interface *interface)
{
    dev_info(&interface->dev, "USB Driver Disconnected\n");
}

//usb_device_id provides a list of different types of USB devices that the driver supports
const struct usb_device_id etx_usb_table[] = {
    { USB_DEVICE( USB_VENDOR_ID, USB_PRODUCT_ID ) },
    { }
};

//This enable the linux hotplug system to load the driver automatically when the device is plugged in
MODULE_DEVICE_TABLE(usb, etx_usb_table);

//The structure needs to do is register with the linux subsystem
static struct usb_driver etx_usb_driver = {
    .name       = "*** USB DRIVER ***",
    .probe      = etx_usb_probe,
    .disconnect = etx_usb_disconnect,
    .id_table   = etx_usb_table,
};


static int __init etx_usb_init(void)
{
    return usb_register(&etx_usb_driver);
}

static void __exit etx_usb_exit(void)
{
    usb_deregister(&etx_usb_driver);
}

module_init(etx_usb_init);
module_exit(etx_usb_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ozgur Karaaslan");
MODULE_DESCRIPTION("USB Driver");
MODULE_VERSION("1.00");