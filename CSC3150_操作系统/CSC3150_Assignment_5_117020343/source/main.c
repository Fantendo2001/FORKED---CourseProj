#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/fs.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include "ioc_hw5.h"

MODULE_LICENSE("GPL");

// CONSTS
#define PREFIX_TITLE "OS_AS5"

// DEVICE
#define DEV_NAME "mydev"
#define DEV_BASEMINOR 0
#define DEV_COUNT 1
static int dev_major;
static int dev_minor;
static struct cdev *dev_cdev;


// DMA
#define DMA_BUFSIZE 64
#define DMASTUIDADDR 0x0        // Student ID
#define DMARWOKADDR 0x4         // RW function complete
#define DMAIOCOKADDR 0x8        // ioctl function complete
#define DMAIRQOKADDR 0xc        // ISR function complete
#define DMACOUNTADDR 0x10       // interrupt count function complete
#define DMAANSADDR 0x14         // Computation answer
#define DMAREADABLEADDR 0x18    // READABLE variable for synchronize
#define DMABLOCKADDR 0x1c       // Blocking or non-blocking IO
#define DMAOPCODEADDR 0x20      // data.a opcode
#define DMAOPERANDBADDR 0x21    // data.b operand1
#define DMAOPERANDCADDR 0x25    // data.c operand2
void *dma_buf;

// Declaration for file operations
static ssize_t drv_read(struct file *filp, char __user *buffer, size_t, loff_t*);
static int drv_open(struct inode*, struct file*);
static ssize_t drv_write(struct file *filp, const char __user *buffer, size_t, loff_t*);
static int drv_release(struct inode*, struct file*);
static long drv_ioctl(struct file *, unsigned int , unsigned long );

// cdev file_operations
static struct file_operations fops = {
      owner: THIS_MODULE,
      read: drv_read,
      write: drv_write,
      unlocked_ioctl: drv_ioctl,
      open: drv_open,
      release: drv_release,
};

// in and out function
void myoutc(unsigned char data,unsigned short int port);
void myouts(unsigned short data,unsigned short int port);
void myouti(unsigned int data,unsigned short int port);
unsigned char myinc(unsigned short int port);
unsigned short myins(unsigned short int port);
unsigned int myini(unsigned short int port);

// Work routine
static struct work_struct *work_routine;

// For input data structure
struct DataIn {
    char a;
    int b;
    short c;
} *dataIn;


// Arithmetic funciton
static void drv_arithmetic_routine(struct work_struct* ws);


// Input and output data from/to DMA
void myoutc(unsigned char data,unsigned short int port) {
    *(volatile unsigned char*)(dma_buf+port) = data;
}
void myouts(unsigned short data,unsigned short int port) {
    *(volatile unsigned short*)(dma_buf+port) = data;
}
void myouti(unsigned int data,unsigned short int port) {
    *(volatile unsigned int*)(dma_buf+port) = data;
}
unsigned char myinc(unsigned short int port) {
    return *(volatile unsigned char*)(dma_buf+port);
}
unsigned short myins(unsigned short int port) {
    return *(volatile unsigned short*)(dma_buf+port);
}
unsigned int myini(unsigned short int port) {
    return *(volatile unsigned int*)(dma_buf+port);
}


static int drv_open(struct inode* ii, struct file* ff) {
	try_module_get(THIS_MODULE);
    	printk("%s:%s(): device open\n", PREFIX_TITLE, __func__);
	return 0;
}
static int drv_release(struct inode* ii, struct file* ff) {
	module_put(THIS_MODULE);
    	printk("%s:%s(): device close\n", PREFIX_TITLE, __func__);
	return 0;
}


static ssize_t drv_read(struct file *filp, char __user *buffer, size_t ss, loff_t* lo) {
	/* Implement read operation for your device */
	int result;
	result = myini(DMAANSADDR);	// read the result from DMA
	printk("%s:%s(): ans = %d\n", PREFIX_TITLE, __func__, result);
	put_user(result, (int*)buffer);
	myouti(0, DMAANSADDR);		// clean the result
	myouti(0, DMAREADABLEADDR);	// set readable as false
	return 0;
}


static ssize_t drv_write(struct file *filp, const char __user *buffer, size_t ss, loff_t* lo) {
	/* Implement write operation for your device */

	if (myini(DMARWOKADDR) != 1) return -1;		// check if RW OK

	struct DataIn data;
	copy_from_user(&data, (struct DataIn*)buffer, sizeof(data));

	if (myini(DMAIOCOKADDR) != 1) return -1;	// check if IOC OK

	// output data to DMA
	myoutc(data.a, DMAOPCODEADDR);
	myouti(data.b, DMAOPERANDBADDR);
	myouts(data.c, DMAOPERANDCADDR);

	INIT_WORK(work_routine, drv_arithmetic_routine);

	// decide blocking or not
	if (myini(DMABLOCKADDR)){
		// Blocking IO
		printk("%s:%s(): queue work\n", PREFIX_TITLE, __func__);
		schedule_work(work_routine);
		printk("%s:%s(): block\n", PREFIX_TITLE, __func__);
		flush_scheduled_work();
	}else{
		// Non-blocking IO
		printk("%s:%s(): queue work\n", PREFIX_TITLE, __func__);
		myouti(0, DMAREADABLEADDR);
		schedule_work(work_routine);
	}

	return 0;
}
static long drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
	/* Implement ioctl setting for your device */
	int* ptr = (int*)arg;
	switch (cmd)
	{
		case HW5_IOCSETSTUID:
			printk("%s:%s(): My STUID is = %d\n", PREFIX_TITLE, __func__, *ptr);
			myouti(*ptr, DMASTUIDADDR);
			break;
		case HW5_IOCSETRWOK:
			if (*ptr)
				printk("%s:%s(): RW OK\n", PREFIX_TITLE, __func__);
			myouti(*ptr, DMARWOKADDR);
			break;
		case HW5_IOCSETIOCOK:
			if (*ptr)
				printk("%s:%s(): IOC OK\n", PREFIX_TITLE, __func__);
			myouti(*ptr, DMAIOCOKADDR);
			break;
		case HW5_IOCSETIRQOK:
			if (*ptr)
				printk("%s:%s(): IRQ OK\n", PREFIX_TITLE, __func__);
			myouti(*ptr, DMAIRQOKADDR);
			break;
		case HW5_IOCSETBLOCK:
			if (*ptr){
				printk("%s:%s(): Blocking IO\n", PREFIX_TITLE, __func__);
			}else{
				printk("%s:%s(): Non-Blocking IO\n", PREFIX_TITLE, __func__);
			}
			myouti(*ptr, DMABLOCKADDR);
			break;
		case HW5_IOCWAITREADABLE:
			while (myini(DMAREADABLEADDR) == 0){
				msleep(10);
			}
			printk("%s:%s(): wait readable 1\n", PREFIX_TITLE, __func__);
			*ptr = 1;
			break;
	}
		
	return 0;
}

static void drv_arithmetic_routine(struct work_struct* ws) {
	/* Implement arthemetic routine */
	char operator = myinc(DMAOPCODEADDR);
	int operand1 = myini(DMAOPERANDBADDR);
	short operand2 = myins(DMAOPERANDCADDR);

	int ans;
	int fnd=0;
    int i, num, isPrime, base, nth;

	switch(operator) {
        case '+':
            ans = operand1 + operand2;
            break;
        case '-':
            ans = operand1 - operand2;
            break;
        case '*':
            ans = operand1 * operand2;
            break;
        case '/':
            ans = operand1 / operand2;
            break;
        case 'p':
			base = operand1;
			nth = operand2;
			num = base;
			while(fnd != nth) {
				isPrime = 1;
				num ++;
				for(i = 2;i <= num/2; i ++) {
					if(num % i == 0) {
						isPrime = 0;
						break;
					}
				}
				if(isPrime) {
					fnd ++;
				}
			}
            ans = num;
            break;
        default:
            ans=0;
    } // end switch
	printk("%s:%s(): %d %c %d = %d\n", PREFIX_TITLE, __func__, operand1, operator, operand2, ans);
	myouti(ans, DMAANSADDR);
	if (myini(DMABLOCKADDR) == 0) myouti(1, DMAREADABLEADDR);
}


static int __init init_modules(void) {
    
	printk("%s:%s():...............Start...............\n", PREFIX_TITLE, __func__);

	/* Register chrdev */ 
	dev_t dev;
	int ret = 0;

	ret = alloc_chrdev_region(&dev, DEV_BASEMINOR, DEV_COUNT, DEV_NAME);
	if (ret)
	{
		printk("Cannot alloc chrdev");
		return ret;
	}

	dev_major = MAJOR(dev);
	dev_minor = MINOR(dev);
	printk("%s:%s(): register chrdev (%d, %d)\n", PREFIX_TITLE, __func__, dev_major, dev_minor);

	/* Init cdev and make it alive */
	dev_cdev = cdev_alloc();

	cdev_init(dev_cdev, &fops);
	dev_cdev->owner = THIS_MODULE;
	ret = cdev_add(dev_cdev, MKDEV(dev_major, dev_minor), 1);
	if (ret < 0)
	{
		printk("Add cdev failed\n");
		return ret;
	}

	/* Allocate DMA buffer */
	dma_buf = kzalloc(DMA_BUFSIZE, GFP_KERNEL);
	printk("%s:%s(): allocate dma buffer\n", PREFIX_TITLE, __func__);

	/* Allocate work routine */
	work_routine = kmalloc(sizeof(typeof(*work_routine)), GFP_KERNEL);

	return 0;
}

static void __exit exit_modules(void) {

	/* Free DMA buffer when exit modules */
	kfree(dma_buf);
	printk("%s:%s(): free dma buffer\n", PREFIX_TITLE, __func__);

	/* Delete character device */
	dev_t dev;

	dev = MKDEV(dev_major, dev_minor);
	cdev_del(dev_cdev);

	printk("%s:%s(): unregister chrdev\n", PREFIX_TITLE, __func__);
	unregister_chrdev_region(dev, 1);
	

	/* Free work routine */
	kfree(work_routine);


	printk("%s:%s():..............End..............\n", PREFIX_TITLE, __func__);
}

module_init(init_modules);
module_exit(exit_modules);
