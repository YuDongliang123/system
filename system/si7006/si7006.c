#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include "si7006.h"
#define CNAME "si7006"
struct i2c_client* gclient;
int major = 0;
struct class* cls;
struct device* dev;

int i2c_read_tmp_hum(unsigned char reg)
{
    int ret;
    unsigned char r_buf[] = { reg };
    unsigned short data;
    // 1.封装消息
    struct i2c_msg r_msg[] = {
        [0] = {
            .addr = gclient->addr,
            .flags = 0,
            .len = 1,
            .buf = r_buf,
        },
        [1] = {
            .addr = gclient->addr,
            .flags = 1,
            .len = 2,
            .buf =  (__u8 *)&data,
        },
    };
    // 2发送消息
    ret = i2c_transfer(gclient->adapter, r_msg, ARRAY_SIZE(r_msg));
    if (ret != ARRAY_SIZE(r_msg)) {
        printk("i2c read serial or firmware error\n");
        return -EAGAIN;
    }
    data = data >> 8 | data << 8;
    return data;
}

int si7006_open(struct inode* inode, struct file* file)
{
    return 0;
}
long si7006_ioctl(struct file* file,
    unsigned int cmd, unsigned long args)
{
    int ret,data;
    switch (cmd) {
    case GET_SI7006_TMP:
        data = i2c_read_tmp_hum(TMP_ADDR);
        ret = copy_to_user((void *)args,&data,GET_CMD_SIZE(GET_SI7006_TMP));
        if(ret){
            printk("copy data to user error\n");
            return -EIO;
        }

        break;
    case GET_SI7006_HUM:
        data = i2c_read_tmp_hum(HUM_ADDR);
        ret = copy_to_user((void *)args,&data,GET_CMD_SIZE(GET_SI7006_HUM));
        if(ret){
            printk("copy data to user error\n");
            return -EIO;
        }
        break;

    }

    return 0;
}
int si7006_close(struct inode* inode, struct file* file)
{
    return 0;
}
struct file_operations fops = {
    .open = si7006_open,
    .unlocked_ioctl = si7006_ioctl,
    .release = si7006_close,
};

int si7006_probe(struct i2c_client* client, const struct i2c_device_id* id)
{
    gclient = client;
    // a.注册字符设备
    major = register_chrdev(0, CNAME, &fops);
    if (major <= 0) {
        printk("register char device driver error\n");
        return -EAGAIN;
    }
    // b.自动提交设备节点
    cls = class_create(THIS_MODULE, CNAME);
    if (IS_ERR(cls)) {
        printk("class create error\n");
        return PTR_ERR(cls);
    }
    dev = device_create(cls, NULL, MKDEV(major, 0), NULL, CNAME);
    if (IS_ERR(dev)) {
        printk("device create error\n");
        return PTR_ERR(dev);
    }
    return 0;
}
int si7006_remove(struct i2c_client* client)
{
    // b.销毁自动提交设备节点
    device_destroy(cls,MKDEV(major,0));
    class_destroy(cls);
    // a.销毁字符设备
    unregister_chrdev(major,CNAME);
    return 0;
}
const struct of_device_id oftable[] = {
    {
        .compatible = "hqyj,si7006",
    },
    { /*end*/ }
};
MODULE_DEVICE_TABLE(of, oftable);

struct i2c_driver si7006 = {
    .probe = si7006_probe,
    .remove = si7006_remove,
    .driver = {
        .name = "heihei",
        .of_match_table = oftable,
    }
};
module_i2c_driver(si7006);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("yu 3089575091@qq.com");