.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/SII-2020LIB.lib
	ExitProcess PROTO :DWORD


	RandUint PROTO :DWORD 
	Ord PROTO :BYTE
.stack 4096
.const
	fiLEX1 DWORD 1 ;INT
	fiLEX2 DWORD 2 ;INT
	mainLEX3 DWORD 5 ;INT
	mainLEX5 DWORD 3 ;INT
	mainLEX6 DWORD 4 ;INT
	mainLEX7 BYTE 'a' ;CHR
	mainLEX9 DWORD 6663 ;INT
	mainLEX10 BYTE '1' ;CHR
.data
	fiz DWORD ? ;INT
	mainx DWORD ? ;INT
	mainy DWORD ? ;INT
	mainz DWORD ? ;INT
	mainsa BYTE ? ;CHR
	mainsb BYTE ? ;CHR
	mainsc BYTE ? ;CHR

.code
fi PROC uses ebx ecx edi esi, 	fix: DWORD ,	fiy: DWORD 
; String #4 :ivlivlv!!
push fiLEX1
push fix
pop eax
pop ebx
add eax, ebx 
push eax
push fiLEX2
pop eax
pop ebx
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
push fiLEX1
pop eax
pop ebx
add eax, ebx 
push eax
pop mainx

; String #12 :ivilv
push mainx
push mainLEX5
pop eax
pop ebx
add eax, ebx 
push eax
pop mainx

; String #16 :ivil@1
invoke RandUint, mainLEX6
push eax ;результат функции
pop mainy

; String #19 :ivl
push DWORD ptr mainLEX7
pop eax
mov mainsa, al

; String #22 :ivl
push mainLEX3
pop mainy

; String #23 :ivili@2!
invoke fi, mainLEX9, mainy
push eax ;результат функции
pop mainz

; String #24 :ivii@1
invoke Ord, mainsa
push eax ;результат функции
pop mainz

; String #25 :ivilv
push DWORD ptr mainsa
push DWORD ptr mainLEX10
pop eax
pop ebx
add eax, ebx 
push eax
pop eax
mov mainsa, al
mov eax, mainx
	invoke		ExitProcess, eax
main ENDP
end main