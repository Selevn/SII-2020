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
divideOnZeroExeption BYTE "Попытка деления на ноль.", 0  ;STR, для вывода ошибки при делении на ноль
	FindFact$LEX1 DWORD 1 ;INT
	main$LEX4 BYTE "Нахождение факториала числа ", 0  ;STR
	main$LEX5 DWORD 11 ;INT
	main$LEX6 BYTE "Равен ", 0  ;STR
	main$LEX7 BYTE "Демонстрация сдвига", 0  ;STR
	main$LEX8 DWORD 32 ;INT
	main$LEX9 DWORD 2 ;INT
	main$LEX10 BYTE "demo<<2", 0  ;STR
	main$LEX12 BYTE "demo>>2", 0  ;STR
	main$LEX14 DWORD 0 ;INT
	main$LEX15 BYTE "q", 0  ;STR
	main$LEX16 DWORD 0 ;INT
.data
	FindFactanswer DWORD 0 ;INT
	mainnumber DWORD 0 ;INT
	maindemo DWORD 0 ;INT
	maindemo1 DWORD 0 ;INT
	maindemo2 DWORD 0 ;INT
	maina DWORD 0 ;INT
	mainqq DWORD 0 ;INT
	mainss DWORD 0 ;STR

.code
FindFact PROC uses ebx ecx edi esi ,	FindFacta: DWORD 
; String #3 :ivl
push FindFact$LEX1
pop FindFactanswer

While17Start: 
mov eax, FindFacta
mov ebx, FindFact$LEX1
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
push FindFact$LEX1
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

push offset main$LEX4
CALL outputstr

; String #11 :ivil@1
invoke random, main$LEX5
push eax ;результат функции
pop mainnumber

push mainnumber
CALL outputuint

push offset main$LEX6
CALL outputstr

; String #14 :ivii@1
invoke FindFact, mainnumber
push eax ;результат функции
pop mainnumber

push mainnumber
CALL outputuint

push offset main$LEX7
CALL outputstr

; String #18 :ivl
push main$LEX8
pop maindemo

push maindemo
CALL outputuint

; String #21 :ivilv
push maindemo
push main$LEX9
pop ebx
pop eax
push ecx ; сохраняем данные регистра ecx
mov ecx, ebx
SHL eax, cl
pop ecx
push eax
pop maindemo1

push offset main$LEX10
CALL outputstr

push maindemo1
CALL outputuint

; String #25 :ivilv
push maindemo
push main$LEX9
pop ebx
pop eax
push ecx ; сохраняем данные регистра ecx
mov ecx, ebx
SHR eax, cl
pop ecx
push eax
pop maindemo2

push offset main$LEX12
CALL outputstr

push maindemo2
CALL outputuint

; String #30 :ivl
push FindFact$LEX1
pop mainqq

; String #31 :ivilv
push mainqq
push main$LEX14
pop ebx
pop eax
imul ebx
push eax
pop mainqq

; String #33 :ivl
push offset main$LEX15
pop mainss

push mainqq
CALL outputuint

mov eax, main$LEX16
	jmp endPoint
	div_by_0:
	push offset divideOnZeroExeption
CALL outputstr
endPoint:
	invoke		ExitProcess, eax
main ENDP
end main