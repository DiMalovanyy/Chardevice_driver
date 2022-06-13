#include "device_operations.h"

#include <asm/uaccess.h>

#define BUF_LEN 80
#define SUCCESS 0

enum {
	CDEV_NOT_USED = 0,
	CDEV_EXCLUSIVE_OPEN = 1,
};

static atomic_t already_open = ATOMIC_INIT(CDEV_NOT_USED);
static char msg[BUF_LEN];


static struct module* MODULE__ = NULL;
void device_operations_set_module(struct module* module) {
	MODULE__ = module;
}

int device_open(struct inode* inode, struct file* file ) {
	static int counter = 0;
	if  (atomic_cmpxchg(&already_open, CDEV_NOT_USED, CDEV_EXCLUSIVE_OPEN)) {
		return -EBUSY;
	}

	sprintf(msg, "Counter was called %d times\n", counter++);
	try_module_get(MODULE__);
	return SUCCESS;
}

int device_release(struct inode* inode, struct file* file) {
	atomic_set(&already_open, CDEV_NOT_USED);
	module_put(MODULE__);
	return SUCCESS;
}

ssize_t device_read(struct file* filp, char __user* buffer, size_t length, loff_t* offset) {

	int bytes_read = 0;
	const char *msg_ptr = msg;
	if (!*(msg_ptr + *offset)) { /* We are at the end of msg */
		*offset = 0; /* Reset offset */
		return 0; /* Signify end of file */
	}
	
	msg_ptr += *offset;
	/* Actually put the data into the buffer */
	while (length && *msg_ptr) {

		/* The buffer is in the user data segment, not the kernel
		 * segment so "*" assignment won't work.  We have to use
		 * put_user which copies data from the kernel data segment to
		 * the user data segment.
		 */
		 put_user(*(msg_ptr++), buffer++);
		 length--;
		 bytes_read++;
	}
	*offset += bytes_read;
	return bytes_read;
}

ssize_t device_write(struct file* filp, const char __user* buff, size_t length, loff_t* offset) {
	pr_alert("Sorry, this operation is not supported.\n");
	return -EINVAL;
}
