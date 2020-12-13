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
	main$LEX1 DWORD 5 ;INT
	main$LEX2 DWORD 6 ;INT
	main$LEX3 DWORD 0 ;INT
.data
	maina DWORD 0 ;INT
	mainb DWORD 0 ;INT
	mainc DWORD 0 ;INT
	mainverylog2 DWORD 0 ;INT
	mainverylogn DWORD 0 ;INT
	mainstring DWORD 0 ;STR

.code
QQQ PROC uses ebx ecx edi esi ,	QQQa: DWORD ,	QQQb: DWORD 
mov eax, QQQa
ret
QQQ ENDP

main PROC

; String #12 :ivill@2!
invoke QQQ, main$LEX1, main$LEX2
push eax ;результат функции
pop maina

push maina
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