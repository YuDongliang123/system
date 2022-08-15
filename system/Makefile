

CROSS_COMPILE := arm-linux-gnueabihf-
CC := $(CROSS_COMPILE)gcc

all:

	cd si7006 && make && cd ..
	cd myspi && make && cd ..
	cd led && make && cd ..
	
	cd motor && make && cd ..
	cd bee && make && cd ..
	cd fan && make && cd ..
	
	cp drive/*.ko ~/nfs/rootfs

TEST:
	$(CC) test.c -o test -l pthread

	cp test ~/nfs/rootfs