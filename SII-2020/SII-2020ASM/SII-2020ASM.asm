.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/SII-2020LIB.lib
	ExitProcess PROTO :DWORD


outputuint PROTO :DWORD
outputchar PROTO :BYTE
outputstr PROTO :DWORD

strConcat PROTO :DWORD,:DWORD

.stack 4096
.const
	mainLEX1 DWORD 25 ;INT
	mainLEX2 DWORD 0 ;INT
.data
	maina DWORD 0 ;INT

.code
main PROC

; String #3 :ivilv
push maina
push mainLEX1
pop ebx
pop eax
add eax, ebx 
push eax
pop maina

push maina
CALL outputuint

mov eax, mainLEX2
	invoke		ExitProcess, eax
main ENDP
end main