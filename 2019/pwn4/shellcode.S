#include <sys/syscall.h>
.intel_syntax noprefix

.text
mov  rdi, 0x68732F6E69622F
push rdi
mov  rdi, rsp

xor  eax, eax
push rax
push rdi
mov  rsi, rsp

xor edx, edx
mov al, SYS_execve

syscall
