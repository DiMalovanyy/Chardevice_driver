#ifndef CHARDEV_MOD_DEVICE_OPERATIONS_HPP
#define CHARDEV_MOD_DEVICE_OPERATIONS_HPP

#include <linux/fs.h>
#include <linux/module.h>

void device_operations_set_module(struct module* module);

int device_open(struct inode*, struct file* );
int device_release(struct inode*, struct file* );
ssize_t device_read(struct file*, char __user*, size_t, loff_t*);
ssize_t device_write(struct file*, const char __user*, size_t, loff_t*);

#endif
