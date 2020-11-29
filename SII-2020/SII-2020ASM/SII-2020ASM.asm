.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/SII-2020LIB.lib
	ExitProcess PROTO :DWORD


	random PROTO :DWORD 
	ord PROTO :BYTE
outputuint PROTO :DWORD
outputchar PROTO :BYTE
outputstr PROTO :DWORD

.stack 4096
.const
	fiLEX1 DWORD 1 ;INT
	fiLEX2 DWORD 2 ;INT
	mainLEX3 DWORD 5 ;INT
	mainLEX4 DWORD 91 ;INT
	mainLEX5 DWORD 3 ;INT
	mainLEX6 DWORD 4 ;INT
	mainLEX7 BYTE 'a' ;CHR
	mainLEX8 BYTE "akbar", 0  ;STR
	mainLEX10 DWORD 6663 ;INT
	mainLEX12 DWORD 6 ;INT
.data
	fiz DWORD ? ;INT
	mainx DWORD ? ;INT
	mainy DWORD ? ;INT
	mainz DWORD ? ;INT
	mainsa BYTE ? ;CHR
	mainallah DWORD ? ;STR
	mainsb BYTE ? ;CHR
	mainsc BYTE ? ;CHR

.code
fi PROC uses ebx ecx edi esi, 	fix: DWORD ,	fiy: DWORD 
; String #4 :ivlivlv!!
push fiLEX1
push fix
pop ebx
pop eax
add eax, ebx 
push eax
push fiLEX2
pop ebx
pop eax
imul ebx
push eax
pop fiz
mov eax, fiz
ret 
fi ENDP

main PROC

; String #10 :ivl
push mainLEX3
pop mainx

; String #11 :ivilv
push mainx
push mainLEX4
pop ebx
pop eax
sub eax, ebx
push eax
pop mainx
push mainx
CALL outputuint

; String #13 :ivilv
push mainx
push mainLEX5
pop ebx
pop eax
add eax, ebx 
push eax
pop mainx

; String #17 :ivil@1
invoke random, mainLEX6
push eax ;результат функции
pop mainy

; String #20 :ivl
push DWORD ptr mainLEX7
pop eax
mov mainsa, al

; String #22 :ivl
push offset mainLEX8
pop mainallah

; String #25 :ivl
push mainLEX3
pop mainy

; String #26 :ivili@2!
invoke fi, mainLEX10, mainy
push eax ;результат функции
pop mainz

; String #27 :ivii@1
invoke ord, mainsa
push eax ;результат функции
pop mainz

; String #29 :ivllv
push mainLEX6
push mainLEX12
pop ebx
pop eax
sub eax, ebx
push eax
pop mainz
push DWORD ptr mainsa
CALL outputchar
push mainallah
CALL outputstr
push mainz
CALL outputuint
mov eax, mainz
	invoke		ExitProcess, eax
main ENDP
end main