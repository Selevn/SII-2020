.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/SII-2020LIB.lib
	ExitProcess PROTO :DWORD


	chr PROTO :DWORD 
	ord PROTO :BYTE
outputuint PROTO :DWORD
outputchar PROTO :BYTE
outputstr PROTO :DWORD

strConcat PROTO :DWORD,:DWORD

.stack 4096
.const
divideOnZeroExeption BYTE "Попытка деления на ноль.", 0  ;STR, для вывода ошибки при делении на ноль
	main$LEX1 DWORD 357 ;INT
	main$LEX2 DWORD 1 ;INT
	main$LEX3 DWORD 0 ;INT
.data
	maina BYTE 0 ;CHR
	mainc BYTE 0 ;CHR
	mainb DWORD 0 ;INT

.code
main PROC

; String #7 :ivil@1
invoke chr, main$LEX1
push eax ;результат функции
pop eax
mov maina, al

; String #8 :ivii@1
invoke ord, maina
push eax ;результат функции
pop mainb

; String #9 :ivil@1
invoke chr, main$LEX2
push eax ;результат функции
pop eax
mov mainc, al
push eax
movzx eax, maina
push eax
CALL outputchar
pop eax

push eax
movzx eax, mainc
push eax
CALL outputchar
pop eax


push mainb
CALL outputuint

mov eax, main$LEX3
	jmp endPoint
	div_by_0:
	push offset divideOnZeroExeption
CALL outputstr
endPoint:
	invoke		ExitProcess, eax
main ENDP
end main