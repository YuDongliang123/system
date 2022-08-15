#ifndef _HEAD_H_ //if no define----如果没有定义xxx(_XXX_H_为格式，XXX内容自己取名)
#define _HEAD_H_ //马上定义

#define PRINT_ERR(msg) do{\
	fprintf(stderr, "__%d__:", __LINE__);\
	perror(msg);\
}while(0) 

//ISO C标准定义的头文件(24项)
#include <assert.h>  //验证程序断言
#include <complex.h>  //支持复数算术运算
#include <ctype.h>  //字符类型
#include <errno.h>  //出错码	
#include <fenv.h>  //浮点环境
#include <float.h>  //浮点常量
#include <inttypes.h>  //整型格式转换
#include <iso646.h>  //替代关系操作符宏
#include <limits.h>  //实现常量
#include <locale.h>  //局部类别
#include <math.h>  //数学常量
#include <setjmp.h>  //非局部goto
#include <signal.h>  //信号
#include <stdarg.h>  //可变参数表
#include <stdbool.h>  //布尔类型和值
#include <stddef.h>  //标准定义
#include <stdint.h>  //整型
#include <stdio.h>  //标准I/O库
#include <stdlib.h>  //实用程序库函数
#include <string.h>  //字符串操作
#include <tgmath.h>  //通用类型数学宏
#include <time.h>  //时间和日期
#include <wchar.h>  //宽字符支持
#include <wctype.h>  //宽字符分类和映射支持

 
//POSIX标准定义的必须的头文件(26项)
#include <dirent.h>  //目录项
#include <fcntl.h>  //文件控制
#include <fnmatch.h>  //文件名匹配类型
#include <glob.h>  //路径名模式匹配类型
#include <grp.h>  //组文件
#include <netdb.h>  //网络数据库操作
#include <pwd.h>  //口令文件
#include <regex.h>  //正则表达式
#include <tar.h>  //tar归档值
#include <termios.h>  //终端I/O
#include <unistd.h>  //符号常量
#include <utime.h>  //文件时间
#include <wordexp.h>  //字扩展类型
#include <arpa/inet.h>  //Internet定义
#include <net/if.h>  //套接字本地接口
#include <netinet/in.h>  //Internet地址族
#include <netinet/tcp.h>  //传输控制协议
#include <sys/mman.h>  //内存管理声明
#include <sys/select.h>  //select函数
#include <sys/socket.h>  //套接字接口
#include <sys/stat.h>  //文件状态
#include <sys/times.h>  //进程时间
#include <sys/types.h>  //基本系统数据类型
#include <sys/un.h>  //UNIX域套接字定义
#include <sys/utsname.h>  //系统名
#include <sys/wait.h>  //进程控制
#include <sys/ioctl.h>
 
//POSIX标准定义的XSI扩展头文件(26项)
#include <cpio.h>  //cpio归档值
#include <dlfcn.h>  //动态链接
#include <fmtmsg.h>  //消息显示结构
#include <ftw.h>  //文件树漫游
#include <iconv.h>  //代码集转换实用程序
#include <langinfo.h>  //语言信息常量
#include <libgen.h>  //模式匹配函数定义
#include <monetary.h>  //货币类型
//#include <ndbm.h>  //数据库操作
#include <nl_types.h>  //消息类别
#include <poll.h>  //轮询函数
#include <search.h>  //搜索表
#include <strings.h>  //字符串操作
#include <syslog.h>  //系统出错日志记录
#include <ucontext.h>  //用户上下文
#include <ulimit.h>  //用户限制
#include <utmpx.h>  //用户帐户数据库
#include <sys/ipc.h>  //IPC
#include <sys/msg.h>  //消息队列
#include <sys/resource.h>  //资源操作
#include <sys/sem.h>  //信号量
#include <sys/shm.h>  //共享存储
#include <sys/statvfs.h>  //文件系统信息
#include <sys/time.h>  //时间类型
#include <sys/timeb.h>  //附加的时间
#include <sys/uio.h>  //矢量I/O操作
 
//POSIX标准定义的可选头文件(8项)
#include <aio.h>  //异步I/O
#include <mqueue.h>  //消息队列
#include <pthread.h>  //线程
#include <sched.h>  //执行调度
#include <semaphore.h>  //信号量
#include <spawn.h>  //实时spawn接口
#include <stropts.h>  //XSI STREAMS接口
//#include <trace.h>//时间跟踪

#endif
