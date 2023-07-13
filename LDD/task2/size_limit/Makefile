obj-m:=sizelimit.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	#sudo insmod char_driver.ko
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	#sudo rmmod char_driver
