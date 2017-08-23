/* INCLUDES */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/kfifo.h>
#include <asm/uaccess.h>

#include "nunchuk.h"

/* DEFINES */
#define RET_SUCCESS             0
#define RET_ERR                 -1
#define DEVICE_NAME             "nunchuk"
#define NUNCHUK_I2C_ADDRESS     0x52
#define NUNCHUK_I2C_BUS         1

/* PROTOTYPES */
static int init_nunchuk_module(void);
static void deinit_nunchuk_module(void);

static ssize_t nunchuk_read(struct file *, char *, size_t, loff_t *);
static int nunchuk_open(struct inode *, struct file *);
static int nunchuk_release(struct inode *, struct file *);

/* GLOBALS */
static int major_number;
static int opened;
static struct i2c_client* nunchuk_client;

static struct file_operations fops = {
    .read = nunchuk_read,
    .open = nunchuk_open,
    .release = nunchuk_release,
};

static int nunchuk_handshake(void)
{
    int status;
    char buffer[] = { 0x40, 0x00 };
    
    status = i2c_master_send(nunchuk_client, buffer, ARRAY_SIZE(buffer));
    
    if (status < 0)
    {
        return RET_ERR;
    }
    
    buffer[0] = 0x00;
    
    status = i2c_master_send(nunchuk_client, buffer, 1);
    
    if (status < 0)
    {
        return RET_ERR;
    }
    
    return RET_SUCCESS;
}

static int nunchuk_read_registers(struct i2c_client *client, u8 *buf, int buf_size) {
	int status;

	mdelay(10);

	buf[0] = 0x00;
        
	status = i2c_master_send(client, buf, 1);
        
	if (status < 0)
        {
            return RET_ERR;
	}

	mdelay(10);

	return i2c_master_recv(client, buf, buf_size);
}


/* FUNCTIONS */
static int init_nunchuk_module(void)
{
    struct i2c_adapter* bus_adapter;
    
    major_number = register_chrdev(0, DEVICE_NAME, &fops);

    if (major_number < 0)
    {
      printk(KERN_ALERT "Registering char device failed with %d\n", 
            major_number);
      
      return major_number;
    }
    
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major_number);
     
    bus_adapter = i2c_get_adapter(NUNCHUK_I2C_BUS);
    
    if (bus_adapter == NULL)
    {
        return -ENODEV;
    }
    
    nunchuk_client = i2c_new_dummy (bus_adapter, NUNCHUK_I2C_ADDRESS);
    
    if (nunchuk_client == NULL)
    {
        return -ENODEV;
    }
    
    if (nunchuk_handshake() == RET_ERR)
    {
        return RET_ERR;
    }

    return RET_SUCCESS;
}

static void deinit_nunchuk_module(void)
{
    unregister_chrdev(major_number, DEVICE_NAME);
}

static int nunchuk_open(struct inode *inode, struct file *file)
{
    if (opened)
    {
        return -EBUSY;
    }

    opened++;
    
    try_module_get(THIS_MODULE);

    return RET_SUCCESS;
}

static int nunchuk_release(struct inode *inode, struct file *file)
{
    opened--;

    module_put(THIS_MODULE);

    return RET_SUCCESS;
}

static ssize_t nunchuk_read(struct file *filp, char *buffer, size_t length, 
                           loff_t * offset)
{
    ssize_t i = 0;
    int status = 0;
    char reg_values[6];
    
    if(length != ARRAY_SIZE(reg_values))
    {
        return 0;
    }
    
    for(i = 0; i < ARRAY_SIZE(reg_values); i++)
    {
        status = nunchuk_read_registers(nunchuk_client, reg_values, ARRAY_SIZE(reg_values));
	if (status < 0)
        {
		printk(KERN_INFO "Error reading nunchuk registers: %0x", status);
		return 0;
	}
        
        
        
        put_user(reg_values[i], buffer + i);
    }
    
    printk(KERN_INFO "i2c_data: %d %d",reg_values[0], reg_values[1]); 

    return length;
}

module_init(init_nunchuk_module);
module_exit(deinit_nunchuk_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stefan Savic <stefan.savic@rt-rk.com>");
MODULE_DESCRIPTION("This is a simple nunchuk controller driver.");
