.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/SII-2020LIB.lib
	ExitProcess PROTO :DWORD


	ord PROTO :BYTE
	chr PROTO :DWORD 
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
	mainLEX13 BYTE "Демонстрация конкатенации строк", 0  ;STR
	mainLEX14 BYTE "первая строка", 0  ;STR
	mainLEX15 BYTE "вторая строка11", 0  ;STR
	mainLEX16 BYTE "Вывод символов от 'а' до 'я':", 0  ;STR
	mainLEX17 BYTE 'а' ;CHR
	mainLEX18 BYTE 'я' ;CHR
	mainLEX20 BYTE 'a' ;CHR
	mainLEX22 DWORD 0 ;INT
.data
	FindFactanswer DWORD 0 ;INT
	mainnumber DWORD 0 ;INT
	maindemo DWORD 0 ;INT
	maindemo1 DWORD 0 ;INT
	maindemo2 DWORD 0 ;INT
	mains1 DWORD 0 ;STR
	mains2 DWORD 0 ;STR
	mains3 DWORD 0 ;STR
	maina BYTE 0 ;CHR
	mainqq BYTE 0 ;CHR

.code
FindFact PROC uses ebx ecx edi esi ,	FindFacta: DWORD 
; String #5 :ivl
push FindFactLEX1
pop FindFactanswer

While35Start: 
mov eax, FindFacta
mov ebx, FindFactLEX1
cmp eax, ebx
jl While35End

; String #6 :iviiv
push FindFactanswer
push FindFacta
pop ebx
pop eax
imul ebx
push eax
pop FindFactanswer

; String #6 :ivilv
push FindFacta
push FindFactLEX1
pop ebx
pop eax
sub eax, ebx
push eax
pop FindFacta
jmp While35Start
While35End: 

mov eax, FindFactanswer
ret
FindFact ENDP

main PROC

push offset mainLEX4
CALL outputstr

; String #13 :ivil@1
invoke random, mainLEX5
push eax ;результат функции
pop mainnumber

push mainnumber
CALL outputuint

push offset mainLEX6
CALL outputstr

; String #16 :ivii@1
invoke FindFact, mainnumber
push eax ;результат функции
pop mainnumber

push mainnumber
CALL outputuint

push offset mainLEX7
CALL outputstr

; String #20 :ivl
push mainLEX8
pop maindemo

push maindemo
CALL outputuint

; String #23 :ivilv
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

; String #27 :ivilv
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

push offset mainLEX13
CALL outputstr

; String #34 :ivl
push offset mainLEX14
pop mains1

; String #35 :ivl
push offset mainLEX15
pop mains2

push mains1
CALL outputstr

push mains2
CALL outputstr

; String #38 :iviiv
push mains1
push mains2
pop ebx
pop eax
invoke strConcat, eax, ebx
push eax
pop mains2

push mains2
CALL outputstr

; String #40 :iviiv
push mains1
push mains2
pop ebx
pop eax
invoke strConcat, eax, ebx
push eax
pop mains3

push mains3
CALL outputstr

push offset mainLEX16
CALL outputstr

; String #43 :ivl
movzx eax, mainLEX17
push eax 
pop eax
mov maina, al
push eax
movzx eax, maina
push eax
CALL outputchar
pop eax


While209Start: 
movzx eax, maina
movzx ebx, mainLEX18
cmp eax, ebx
je While209End

; String #44 :iviil@1v
movzx eax, maina
push eax 
invoke chr, FindFactLEX1
push eax ;результат функции
pop ebx
pop eax
add eax, ebx 
push eax
pop eax
mov maina, al
push eax
movzx eax, maina
push eax
CALL outputchar
pop eax

jmp While209Start
While209End: 

; String #47 :ivl
movzx eax, mainLEX20
push eax 
pop eax
mov mainqq, al
push eax
movzx eax, mainqq
push eax
CALL outputchar
pop eax


; String #49 :iviil@1v
movzx eax, mainqq
push eax 
invoke chr, mainLEX9
push eax ;результат функции
pop ebx
pop eax
add eax, ebx 
push eax
pop eax
mov mainqq, al
push eax
movzx eax, mainqq
push eax
CALL outputchar
pop eax


mov eax, mainLEX22
	invoke		ExitProcess, eax
main ENDP
end main