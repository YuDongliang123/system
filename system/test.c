#include "head.h"
#include "test.h"

//分函数
void LED_control();
void TH_read();
void Buzzer_control();
void Fan_control();
void Motor_control();
void Digital_tube_display();
void set_TH();
void TH_control();
void* callback(void* arg);

//函数跳转
jmp_buf ab;
jmp_buf bb;
jmp_buf cb;
jmp_buf db;
jmp_buf eb;
jmp_buf fb;

int i;
int fd_si7006, fd_spi, fd_led, fd_bee, fd_fan, fd_motor; //文件描述符
int tmp, hum;                                            //温湿度
float rtmp, rhum;
int which;
float data; //数码管
char uaf[2] = "";

float hum_val = 90.00;
float tmp_val = 30.00;

pthread_t tid;

int main(int argc, char const *argv[])
{
    system("insmod si7006.ko");
    system("insmod myspi.ko");
    system("insmod led.ko");
    system("insmod bee.ko");
    system("insmod fan.ko");
    system("insmod motor.ko");

    if ((fd_si7006 = open("/dev/si7006", O_RDWR)) == -1)
        PRINT_ERR("open error");
    if ((fd_spi = open("/dev/myspi", O_RDWR)) == -1)
        PRINT_ERR("open error");
    if ((fd_led = open("/dev/led", O_RDWR)) == -1)
        PRINT_ERR("open error");
    if ((fd_bee = open("/dev/bee", O_RDWR)) == -1)
        PRINT_ERR("open error");
    if ((fd_fan = open("/dev/fan", O_RDWR)) == -1)
        PRINT_ERR("open error");
    if ((fd_motor = open("/dev/motor", O_RDWR)) == -1)
        PRINT_ERR("open error");

    setjmp(ab);

    TH_control();
    printf("***************************************************\n");
    printf("******************智能家居系统*********************\n");
    printf("******************1.LED开关************************\n");
    printf("******************2.温湿度读取*********************\n");
    printf("******************3.蜂鸣器开关*********************\n");
    printf("******************4.风扇开关***********************\n");
    printf("******************5.马达开关***********************\n");
    printf("******************6.数码管显示*********************\n");
    printf("******************7.设置温湿度阈值*****************\n");
    printf("******************8.退出系统***********************\n");
    printf("***************************************************\n");
    printf("你想要操作哪个");
    scanf("%d", &i);
    printf("%d\n", i);
    switch (i)
    {
    case 1:
    {
        LED_control();
    }
    break;
    case 2:
    {
        TH_read();
    }
    break;
    case 3:
    {
        Buzzer_control();
    }
    break;
    case 4:
    {
        Fan_control();
    }
    break;
    case 5:
    {
        Motor_control();
    }
    break;
    case 6:
    {
        Digital_tube_display();
    }
    break;
    case 7:
    {
        set_TH();
    }
    break;
    case 8:
    {
        close(fd_bee);
        close(fd_fan);
        close(fd_motor);
        close(fd_led);
        close(fd_si7006);
        close(fd_spi);
        //卸载驱动
        system("rmmod si7006");
        system("rmmod myspi");
        system("rmmod led");
        system("rmmod bee");
        system("rmmod fan");
        system("rmmod motor");

        exit(0);
    }
    break;
    }
    return 0;
}

void LED_control()
{
    setjmp(bb);
    printf("***************************************************\n");
    printf("*****************1.打开LED*************************\n");
    printf("*****************2.关闭LED*************************\n");
    printf("*****************3.返回上一级**********************\n");
    printf("***************************************************\n");
    printf("你想要操作哪个");
    scanf("%d", &i);
    if (1 == i)
    {
        strcpy(uaf, "1");
        write(fd_led, uaf, sizeof(uaf));
        longjmp(bb, 1);
    }
    else if (2 == i)
    {
        strcpy(uaf, "2");
        write(fd_led, uaf, sizeof(uaf));
        longjmp(bb, 1);
    }
    else if (3 == i)
    {
        longjmp(ab, 1);
    }
    else
    {
        printf("输入有误，重新输入\n");
        longjmp(bb, 1);
    }
}
void TH_read()
{
    ioctl(fd_si7006, GET_SI7006_HUM, &hum);
    rhum = 125 * hum / 65536 - 6;
    ioctl(fd_si7006, GET_SI7006_TMP, &tmp);
    rtmp = 175.72 * tmp / 65536 - 46.85;
    printf("湿度为%.2f,温度为%.2f\n", rhum, rtmp);
    longjmp(ab, 1);
}
void Buzzer_control()
{
    setjmp(cb);
    printf("***************************************************\n");
    printf("*****************1.打开蜂鸣器**********************\n");
    printf("*****************2.关闭蜂鸣器**********************\n");
    printf("*****************3.返回上一级**********************\n");
    printf("***************************************************\n");
    printf("你想要操作哪个");
    scanf("%d", &i);
    if (1 == i)
    {
        strcpy(uaf, "1");
        write(fd_bee, uaf, sizeof(uaf));
        longjmp(cb, 1);
    }
    else if (2 == i)
    {
        strcpy(uaf, "2");
        write(fd_bee, uaf, sizeof(uaf));
        longjmp(cb, 1);
    }
    else if (3 == i)
    {
        longjmp(ab, 1);
    }
    else
    {
        printf("输入有误，重新输入\n");
        longjmp(cb, 1);
    }
}
void Fan_control()
{
    setjmp(db);
    printf("***************************************************\n");
    printf("*****************1.打开风扇************************\n");
    printf("*****************2.关闭风扇************************\n");
    printf("*****************3.返回上一级**********************\n");
    printf("***************************************************\n");
    int i;
    printf("你想要操作哪个");
    scanf("%d", &i);
    if (1 == i)
    {
        strcpy(uaf, "1");
        write(fd_fan, uaf, sizeof(uaf));
        longjmp(db, 1);
    }
    else if (2 == i)
    {
        strcpy(uaf, "2");
        write(fd_fan, uaf, sizeof(uaf));
        longjmp(db, 1);
    }
    else if (3 == i)
    {
        longjmp(ab, 1);
    }
    else
    {
        printf("输入有误，重新输入\n");
        longjmp(db, 1);
    }
}
void Motor_control()
{
    setjmp(eb);
    printf("***************************************************\n");
    printf("*****************1.打开马达************************\n");
    printf("*****************2.关闭马达************************\n");
    printf("*****************3.返回上一级**********************\n");
    printf("***************************************************\n");
    int i;
    printf("你想要操作哪个");
    scanf("%d", &i);
    if (1 == i)
    {
        strcpy(uaf, "1");
        write(fd_motor, uaf, sizeof(uaf));
        longjmp(eb, 1);
    }
    else if (2 == i)
    {
        strcpy(uaf, "2");
        write(fd_motor, uaf, sizeof(uaf));
        longjmp(eb, 1);
    }
    else if (3 == i)
    {
        longjmp(ab, 1);
    }
    else
    {
        printf("输入有误，重新输入\n");
        longjmp(eb, 1);
    }
}
void Digital_tube_display()
{
    setjmp(fb);
    printf("***************************************************\n");
    printf("*****************1.显示温度************************\n");
    printf("*****************2.显示湿度************************\n");
    printf("*****************3.显示温湿度**********************\n");
    printf("*****************4.显示自定义数字******************\n");
    printf("*****************5.返回上一级**********************\n");
    printf("***************************************************\n");
    int i, j;
    printf("你想要操作哪个");
    scanf("%d", &i);

    if (1 == i)
    {
        ioctl(fd_si7006, GET_SI7006_TMP, &tmp);
        rtmp = 175.72 * tmp / 65536 - 46.85;
        printf("温度为%.2f\n", rtmp);
        rtmp *= 100;

        if(pthread_create(&tid, NULL, callback,&rtmp) != 0)
            perror("pthread_create");

        longjmp(fb, 1);
    }
    else if (2 == i)
    {
        ioctl(fd_si7006, GET_SI7006_HUM, &hum);
        rhum = 125 * hum / 65536 - 6;
        printf("湿度为%.2f\n", rhum);
        rhum *= 100;

        if(pthread_create(&tid, NULL, callback,&rhum) != 0)
            perror("pthread_create");

        longjmp(fb, 1);
    }
    else if (3 == i)
    {
        ioctl(fd_si7006, GET_SI7006_TMP, &tmp);
        ioctl(fd_si7006, GET_SI7006_HUM, &hum);
        rtmp = 175.72 * tmp / 65536 - 46.85;
        rhum = 125 * hum / 65536 - 6;
        printf("湿度为%.2f,温度为%.2f\n", rhum, rtmp);
        rhum /= 1;
        rtmp /= 1;
        rtmp += rhum*100;

        if(pthread_create(&tid, NULL, callback,&rtmp) != 0)
            perror("pthread_create");

        longjmp(fb, 1);
    }
    else if (4 == i)
    {
        printf("请输入数字>>>");
        scanf("%f", &data);

        if(pthread_create(&tid, NULL, callback,&data) != 0)
            perror("pthread_create");

        longjmp(fb, 1);
    }
    else if (5 == i)
    {
        longjmp(ab, 1);
    }
}
void set_TH()
{
    printf("你要设置的温度阈值是：");
    scanf("%f", &tmp_val);
    printf("你要设置的湿度阈值是：");
    scanf("%f", &hum_val);
    printf("设置成功\n");

    longjmp(ab, 1);
}

void TH_control()
{
    ioctl(fd_si7006, GET_SI7006_TMP, &tmp);
    ioctl(fd_si7006, GET_SI7006_HUM, &hum);
    rtmp = 175.72 * tmp / 65536 - 46.85;
    rhum = 125 * hum / 65536 - 6;
    strcpy(uaf, "1");
    if (rhum > hum_val || rtmp > tmp_val)
    {
        write(fd_led, uaf, sizeof(uaf));
        write(fd_bee, uaf, sizeof(uaf));
        write(fd_motor, uaf, sizeof(uaf));
        write(fd_fan, uaf, sizeof(uaf));
    }
}

void* callback(void *arg)
{
    float num;
    int j=0;
    for (j=0;j<100;j++)
    {
        num = *(float *)arg;
        for (i = 0; i < 4; i++)
        {
            ioctl(fd_spi, SEG_WHICH, 3 - i);
            if((3-i) != 1)
            {
                ioctl(fd_spi, SEG_DAT, ((int)num) % 10);
            }
            else
            {
                ioctl(fd_spi, SEG_DAT, ((int)num) % 10+10);
            }
            num /= 10;
            usleep(5000);
        }
    }
}