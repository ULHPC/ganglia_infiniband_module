-*- mode: markdown; mode: auto-fill; fill-column: 80 -*-

`README.md`

---------

Ganglia Infiniband Module
=========================

This repository contains the sources of the Ganglia Infiniband Module 
in use on the HPC platform @ Uni.lu.

# Pre-requisites

Install these packages:

* build-essential
* libapr1-dev
* libexpat1-dev
* libganglia1-dev

# Build

    [11:39:32] root@gaia-59 mod_ib#> make
    gcc -fpic -I/usr/include/apr-1.0 -I/opt/ganglia/include -D_LARGEFILE64_SOURCE -Wall -c mod_ib.c -o mod_ib.o
    ld -shared mod_ib.o -ldl -lnsl -lexpat -lconfuse -lapr-1 -lpthread -soname modInfiniband.so -o modInfiniband.so
    [11:39:33] root@gaia-59 mod_ib#> ls
    ib.conf  makefile  modInfiniband.so  mod_ib.c  mod_ib.o  test.c

# Profit

Adapt the example of configuration in `ib.conf` and merge it into `/etc/ganglia/gmond.conf`.
Finally, restart the ganglia-monitor daemon.

    /etc/init.d/ganglia-monitor restart

