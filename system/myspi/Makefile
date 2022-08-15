modname := myspi
KERNELDIR := /home/ubuntu/linux-5.10.61
CROSS_COMPILE := arm-linux-gnueabihf-

PWD := $(shell pwd)

CC := $(CROSS_COMPILE)gcc

all:
	make -C $(KERNELDIR)  M=$(PWD)   modules
	cp *.ko ../drive
	make -C $(KERNELDIR)  M=$(PWD)   clean

obj-m := $(modname).o
