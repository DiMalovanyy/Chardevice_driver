#include "utils.h"

#include <linux/printk.h>
#include <linux/kern_levels.h>

void get_module_info__ (const struct module* module) {
	printk(KERN_INFO "Module name = %s\n", module->name);
	printk(KERN_INFO "Module version = %s\n", module->version);
}
