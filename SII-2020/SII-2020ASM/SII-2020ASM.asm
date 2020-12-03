.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/SII-2020LIB.lib
	ExitProcess PROTO :DWORD


	random PROTO :DWORD 
outputuint PROTO :DWORD
outputchar PROTO :BYTE
outputstr PROTO :DWORD

strConcat PROTO :DWORD,:DWORD

.stack 4096
.const
	FindFactLEX1 DWORD 1 ;INT
	mainLEX4 BYTE "Нахождение факториала числа ", 0  ;STR
	mainLEX5 DWORD 11 ;INT
	mainLEX6 BYTE "Равен ", 0  ;STR
	mainLEX7 BYTE "Демонстрация сдвига", 0  ;STR
	mainLEX8 DWORD 32 ;INT
	mainLEX9 DWORD 2 ;INT
	mainLEX10 BYTE "demo<<2", 0  ;STR
	mainLEX12 BYTE "demo>>2", 0  ;STR
	mainLEX13 DWORD 0 ;INT
.data
	FindFactanswer DWORD 0 ;INT
	mainnumber DWORD 0 ;INT
	maindemo DWORD 0 ;INT
	maindemo1 DWORD 0 ;INT
	maindemo2 DWORD 0 ;INT

.code
FindFact PROC uses ebx ecx edi esi ,	FindFacta: DWORD 
; String #3 :ivl
push FindFactLEX1
pop FindFactanswer

While17Start: 
mov eax, FindFacta
mov ebx, FindFactLEX1
cmp eax, ebx
jl While17End

; String #4 :iviiv
push FindFactanswer
push FindFacta
pop ebx
pop eax
imul ebx
push eax
pop FindFactanswer

; String #4 :ivilv
push FindFacta
push FindFactLEX1
pop ebx
pop eax
sub eax, ebx
push eax
pop FindFacta
jmp While17Start
While17End: 

mov eax, FindFactanswer
ret
FindFact ENDP

main PROC

push offset mainLEX4
CALL outputstr

; String #11 :ivil@1
invoke random, mainLEX5
push eax ;результат функции
pop mainnumber

push mainnumber
CALL outputuint

push offset mainLEX6
CALL outputstr

; String #14 :ivii@1
invoke FindFact, mainnumber
push eax ;результат функции
pop mainnumber

push mainnumber
CALL outputuint

push offset mainLEX7
CALL outputstr

; String #18 :ivl
push mainLEX8
pop maindemo

push maindemo
CALL outputuint

; String #21 :ivilv
push maindemo
push mainLEX9
pop ebx
pop eax
push ecx ; сохраняем данные регистра ecx
mov ecx, ebx
SHL eax, cl
pop ecx
push eax
pop maindemo1

push offset mainLEX10
CALL outputstr

push maindemo1
CALL outputuint

; String #25 :ivilv
push maindemo
push mainLEX9
pop ebx
pop eax
push ecx ; сохраняем данные регистра ecx
mov ecx, ebx
SHR eax, cl
pop ecx
push eax
pop maindemo2

push offset mainLEX12
CALL outputstr

push maindemo2
CALL outputuint

mov eax, mainLEX13
	invoke		ExitProcess, eax
main ENDP
end main