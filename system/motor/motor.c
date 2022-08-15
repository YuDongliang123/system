#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_gpio.h>

#define DR "motor"
struct gpio_desc *desc;
int MOTOR_init_control(char *);
int major = 0;
struct class *cls = NULL;
struct device *dev = NULL;

int file_open(struct inode *inode, struct file *file)
{
	return 0;
}
ssize_t file_read(struct file *file, char __user *uaf, size_t size, loff_t *offset)
{
	return 0;
}
ssize_t file_write(struct file *file, const char __user *uaf, size_t size, loff_t *offset)
{

	char kaf[2];
	int i = 0;
	//读从用户空间传过来的数值
	i = copy_from_user(kaf, uaf, size);
	// printk("%s,%s\n",kaf,uaf);
	if (kaf[0] == '1')
	{
		//用GPIOD开风扇
		MOTOR_init_control("1"); //传参
	}
	else
	{
		//用GPIOD关风扇
		MOTOR_init_control("2"); //传参
	}

	return 0;
}
int file_close(struct inode *inode, struct file *file)
{
	return 0;
}
struct file_operations fops =
	{
		.open = file_open,
		.read = file_read,
		.write = file_write,
		.release = file_close,
};

static int __init mycdev_init(void)
{
	// a.注册字符设备
	major = register_chrdev(0, DR, &fops);
	if (major < 0)
	{
		printk("-------------------------------------------%d\n", __LINE__);
		return -1;
	}
	// b.自动提交设备节点
	cls = class_create(THIS_MODULE, DR);
	if (IS_ERR(cls))
	{
		printk("__%d__\n", __LINE__);
		return PTR_ERR(cls);
	}
	dev = device_create(cls, NULL, MKDEV(major, 0), NULL, DR);
	if (IS_ERR(dev))
	{
		printk("__%d__\n", __LINE__);
		return PTR_ERR(dev);
	}
	return 0;
}
static void __exit mycdev_exit(void)
{
	// b.销毁自动提交设备节点
	device_destroy(cls, MKDEV(major, 0));
	class_destroy(cls);
	// a.销毁字符设备
	unregister_chrdev(major, DR);
}

int MOTOR_init_control(char abc[])
{
	struct device_node *pnode, *enode;
	//获取设备树节点
	pnode = of_find_compatible_node(NULL, NULL, "hqyj,device");
	if (pnode == NULL)
	{
		printk("-------------------------------------------%d\n", __LINE__);
		return -1;
	}
	enode = of_get_child_by_name(pnode, "pwm");
	if (enode == NULL)
	{
		printk("-------------------------------------------%d\n", __LINE__);
		return -1;
	}
	//通过GPIOD点蜂鸣器
	if (!(strcmp("1", abc)))
	{
		printk("---------------------转----------------------\n");
		//转
		desc = gpiod_get_from_of_node(enode, "motor", 0, GPIOD_OUT_HIGH, NULL);
		if (IS_ERR(desc))
		{
			printk("gpio operation error\n");
			return PTR_ERR(desc);
		}
	}
	else
	{
		printk("--------------------不转---------------------\n");
		//不转
		gpiod_set_value(desc, 0);
		gpiod_put(desc);
	}
	return 0;
}

module_init(mycdev_init);
module_exit(mycdev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("C.C 2717802307@qq.com");
