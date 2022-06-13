#include <linux/fs.h>
#include <linux/device.h>

#include "device.h"
#include "device_operations.h"

static int major;
static struct file_operations chardev_fops = {
	.open = device_open,
	.read = device_read,
	.release = device_release,
	.write = device_write,
};
static struct class* cls;
static const char* DEVICE_NAME = "";

int register_chardev__ (struct module* module, const char* device_name) {
	DEVICE_NAME = device_name;
	device_operations_set_module(module);

	major = register_chrdev(0, DEVICE_NAME, &chardev_fops);
	if (major < 0) {
		pr_alert("Registration chardev failed with %d\n", major);
		return major;
	}
	pr_info("Device %s was assign to major number %d\n", DEVICE_NAME, major);

	cls = class_create(module, DEVICE_NAME);
	device_create(cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);

	pr_info("Device created on /dev/%s\n", DEVICE_NAME);

	return major;
}

void unregister_chardev__(void) {
	device_destroy(cls, MKDEV(major, 0));
	class_destroy(cls);
	unregister_chrdev(major, DEVICE_NAME);
}
