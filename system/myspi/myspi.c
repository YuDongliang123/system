#include <linux/init.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include "myspi.h"
/*
 &spi4 {
    pinctrl-names = "default", "sleep";
    pinctrl-0 = <&spi4_pins_b>;
    pinctrl-1 = <&spi4_sleep_pins_b>;
    cs-gpios = <&gpioe 11 0>;
    status = "okay";
    myspi@0{
     compatible = "myspi";
     reg = <0>;
        spi-max-frequency = <10000000>;
    };
};
*/
#define NAME "myspi"
int major = 0;
int i = 0;
struct class *cls;
struct device *dev;
struct spi_device *gspi;

//无小数点：0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
//有小数点：0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,
u8 code[] = {
    0x3f, // 0
    0x06, // 1
    0x5b, // 2
    0x4f, // 3
    0x66, // 4
    0x6d, // 5
    0x7d, // 6
    0x07, // 7
    0x7f, // 8
    0x6f, // 9
    0xbf,
    0x86,
    0xdb,
    0xcf,
    0xe6,
    0xed,
    0xfd,
    0x87,
    0xff,
    0xef,
};

u8 which[] = {
    0x1, // sg0
    0x2, // sg1
    0x4, // sg2
    0x8, // sg3
};

int myspi_open(struct inode *inode, struct file *file)
{
    return 0;
}
long myspi_ioctl(struct file *file,
                 unsigned int cmd, unsigned long args)
{
    switch (cmd)
    {
    case SEG_WHICH:
        spi_write(gspi, &which[args], 1);
        break;
    case SEG_DAT:
        spi_write(gspi, &code[args], 1);
        break;
    default:
        printk("ioctl error\n");
        break;
    }

    return 0;
}

int myspi_close(struct inode *inode, struct file *file)
{
    return 0;
}
struct file_operations fops = {
    .open = myspi_open,
    .unlocked_ioctl = myspi_ioctl,
    .release = myspi_close,
};

int myspi_probe(struct spi_device *spi)
{
    u8 buf[2] = {0xff, 0x0};
    gspi = spi;
    spi_write(gspi, buf, ARRAY_SIZE(buf));
    // a.注册字符设备
    major = register_chrdev(0, NAME, &fops);
    if (major < 0)
    {
        printk("register chrdev error\n");
        return major;
    }
    // b.自动提交设备节点
    cls = class_create(THIS_MODULE, NAME);
    if (IS_ERR(cls))
    {
        printk("class create  error\n");
        return PTR_ERR(cls);
    }
    dev = device_create(cls, NULL, MKDEV(major, 0), NULL, NAME);
    if (IS_ERR(dev))
    {
        printk("device create  error\n");
        return PTR_ERR(dev);
    }
    return 0;
}

int myspi_remove(struct spi_device *spi)
{
    // b.销毁自动提交设备节点
    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);
    // a.销毁字符设备
    unregister_chrdev(major, NAME);
    return 0;
}

const struct of_device_id of_match[] = {
    {
        .compatible = "hqyj,myspi",
    },
    {},
};
MODULE_DEVICE_TABLE(of, of_match);

struct spi_driver myspi = {
    .probe = myspi_probe,
    .remove = myspi_remove,
    .driver = {
        .name = "hello_myspi",
        .of_match_table = of_match,
    },
};

module_spi_driver(myspi);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("yu 3089575091@qq.com");