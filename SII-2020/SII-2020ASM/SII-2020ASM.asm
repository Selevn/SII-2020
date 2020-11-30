.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/SII-2020LIB.lib
	ExitProcess PROTO :DWORD


	random PROTO :DWORD 
	chr PROTO :DWORD 
outputuint PROTO :DWORD
outputchar PROTO :BYTE
outputstr PROTO :DWORD

strConcat PROTO :DWORD,:DWORD

.stack 4096
.const
	findFactLEX1 DWORD 1 ;INT
	mainLEX4 DWORD 9 ;INT
	mainLEX6 BYTE "Факториал числа", 0  ;STR
	mainLEX7 BYTE "равен", 0  ;STR
	mainLEX8 BYTE "Вывод символов от а до я", 0  ;STR
	mainLEX9 BYTE 'а' ;CHR
	mainLEX10 BYTE 'я' ;CHR
	mainLEX12 BYTE "pen", 0  ;STR
	mainLEX13 BYTE "123341", 0  ;STR
	mainLEX14 DWORD 0 ;INT
.data
	findFactanswer DWORD 0 ;INT
	maina DWORD 0 ;INT
	mainq BYTE 0 ;CHR
	maina1 DWORD 0 ;STR
	maina2 DWORD 0 ;STR
	mainuu DWORD 0 ;STR

.code
findFact PROC uses ebx ecx edi esi ,	findFacta: DWORD 
; String #3 :ivl
push findFactLEX1
pop findFactanswer

While17Start: 
mov eax, findFacta
mov ebx, findFactLEX1
cmp eax, ebx
jl While17End

; String #5 :iviiv
push findFactanswer
push findFacta
pop ebx
pop eax
imul ebx
push eax
pop findFactanswer

; String #6 :ivilv
push findFacta
push findFactLEX1
pop ebx
pop eax
sub eax, ebx
push eax
pop findFacta
jmp While17Start
While17End: 

mov eax, findFactanswer
ret
findFact ENDP

main PROC

; String #13 :ivil@1
invoke random, mainLEX4
push eax ;результат функции
pop maina

; String #14 :ivilv
push maina
push findFactLEX1
pop ebx
pop eax
add eax, ebx 
push eax
pop maina

push offset mainLEX6
CALL outputstr

push maina
CALL outputuint

push offset mainLEX7
CALL outputstr

; String #18 :ivii@1
invoke findFact, maina
push eax ;результат функции
pop maina

push maina
CALL outputuint

push offset mainLEX8
CALL outputstr

; String #24 :ivl
movzx eax, mainLEX9
push eax 
pop eax
mov mainq, al
push eax
movzx eax, mainq
push eax
CALL outputchar
pop eax


While113Start: 
movzx eax, mainq
movzx ebx, mainLEX10
cmp eax, ebx
je While113End

; String #27 :iviil@1v
movzx eax, mainq
push eax 
invoke chr, findFactLEX1
push eax ;результат функции
pop ebx
pop eax
add eax, ebx 
push eax
pop eax
mov mainq, al
push eax
movzx eax, mainq
push eax
CALL outputchar
pop eax

jmp While113Start
While113End: 

; String #32 :ivl
push offset mainLEX12
pop maina1

; String #33 :ivilv
push maina1
push offset mainLEX13
pop ebx
pop eax
invoke strConcat, eax, ebx
push eax
pop maina2

push maina2
CALL outputstr

push mainuu
CALL outputstr

mov eax, mainLEX14
	invoke		ExitProcess, eax
main ENDP
end main