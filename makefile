all: 
	gcc -fpic -I/usr/include/apr-1 -I/opt/ganglia/include -D_LARGEFILE64_SOURCE -Wall -c mod_ib.c -o mod_ib.o
	ld -shared mod_ib.o -ldl -lnsl -lexpat -lconfuse -lapr-1 -lpthread -soname modInfiniband.so -o modInfiniband.so
