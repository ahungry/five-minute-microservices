PWD=`pwd`

all: nowrap

start: nowrap
	sudo spawn-fcgi -s /run/fcgiwrap2.sock $(PWD)/nowrap
	sudo chmod 666 /run/fcgiwrap2.sock

nowrap:
	gcc -lfcgi -Wall nowrap.c -o nowrap
