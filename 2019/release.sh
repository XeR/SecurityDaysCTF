#!/bin/sh

# Assume containers are down
for task in pwn*; do
	docker container start "$task"
done

docker container exec pwn1 tar zcvf - Makefile main.c               > pwn1.tar.gz
docker container exec pwn2 tar zcvf - Makefile main.c main          > pwn2.tar.gz
docker container exec pwn3 tar zcvf - Makefile main.c main          > pwn3.tar.gz
docker container exec pwn4 tar zcvf - Makefile main.c               > pwn4.tar.gz
docker container exec pwn5 tar zcvf - main /lib/ld-musl-x86_64.so.1 > pwn5.tar.gz
