#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>

static ssize_t dRead(struct file *filp, /* see include/linux/fs.h   */
                           char *buffer,      /* buffer to fill with data */
                           size_t length,     /* length of the buffer     */
                           loff_t *offset)
{
///////////////////////////////////////////////////////////////////////////
//	struct timespec t = current_kernel_time();
//	struct timespec t2;
//	getnstimeofday(&t2);
  int bytes_read = sprintf(buffer, "Hi");
//	int bytes_read = sprintf(buffer, "current_kernel_time : %lu %9lu , getnstimeofday : %lu %9lu", t.tv_sec, t.tv_nsec, t2.tv_sec, t2.tv_nsec);
///////////////////////////////////////////////////////////////////////////	
return bytes_read;
}


static int sample_open(struct inode *inode, struct file *file)
{
    pr_info("I have been awoken\n");
    return 0;
}

static int sample_close(struct inode *inodep, struct file *filp)
{
    pr_info("Sleepy time\n");
    return 0;
}

static ssize_t sample_write(struct file *file, const char __user *buf,
		       size_t len, loff_t *ppos)
{
    pr_info("Yummy - I just ate %d bytes\n", len);
    return len; /* But we don't actually do anything with the data */
}

static const struct file_operations sample_fops = {
    .owner			= THIS_MODULE,
    .write			= sample_write,
    .read			= dRead,
    .open			= sample_open,
    .release		= sample_close,
    .llseek 		= no_llseek,
};

struct miscdevice sample_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "kMod",
    .fops = &sample_fops,
};

static int __init misc_init(void)
{
    int error;

    error = misc_register(&sample_device);
    if (error) {
        pr_err("can't misc_register :(\n");
        return error;
    }

    pr_info("I'm in\n");
    return 0;
}

static void __exit misc_exit(void)
{
    misc_deregister(&sample_device);
    pr_info("I'm out\n");
}

module_init(misc_init)
module_exit(misc_exit)

MODULE_DESCRIPTION("Simple Misc Driver");
MODULE_AUTHOR("Tony");
MODULE_LICENSE("GPL");
