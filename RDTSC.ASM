
BITS 32

GLOBAL _GetTimestamp

SECTION .text code align=16

_GetTimestamp:
PUSH EAX
PUSH EBX
PUSH EDX
RDTSC
MOV EBX,[ESP+16]
MOV [EBX],EAX
MOV [EBX+4],EDX
POP EDX
POP EBX
POP EAX
RET

