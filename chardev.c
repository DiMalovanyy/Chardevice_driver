/* Creates read-only char device that says how many times you have read from dev file */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

/* ---------- Logging  ------ */
#include <linux/printk.h>
#include <linux/kern_levels.h>
/* -------------------------- */

#include "device/device.h"
#include "utils.h"

#define SUCCESS 0
#define DEVICE_NAME "chardev"

static int __init chardev_init(void) {
	int device_major;
	get_module_info__ (THIS_MODULE); 
	device_major = register_chardev__ (THIS_MODULE, DEVICE_NAME);
	if (device_major < 0) {
		return device_major;
	}
	return SUCCESS;
}


static void __exit chardev_exit(void) {
	unregister_chardev__ ();
}


module_init(chardev_init);
module_exit(chardev_exit);

MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_AUTHOR("Dmytro Malovanyi");
MODULE_DESCRIPTION("Character device that count read amount");

