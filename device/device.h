#ifndef CHARDEV_MOD_DEVICE_H
#define CHARDEV_MOD_DEVICE_H

#include <linux/module.h>

int register_chardev__ (struct module* module, const char* device_name);
void unregister_chardev__(void);

#endif
