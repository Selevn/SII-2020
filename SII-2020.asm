.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib libucrt.lib
	includelib kernel32.lib
	ExitProcess PROTO :DWORD

	includelib ../Debug/KDVlib.lib

.stack 4096
.const
	fiLEX1 DWORD 1 ;INT
	fiLEX2 DWORD 2 ;INT
	mainLEX3 DWORD 5 ;INT
	mainLEX6 DWORD 123 ;INT
	mainLEX8 DWORD 0 ;INT
.data
	fiz DWORD ? ;INT
	mainx DWORD ? ;INT
	mainy DWORD ? ;INT
	mainz DWORD ? ;INT
	mainsa BYTE ? ;CHR
	mainsb BYTE ? ;CHR
	mainsc BYTE ? ;CHR

.code
fi PROC uses eax ebx ecx edi esi, 	fix: DWORD ,	fiy: DWORD 
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

; String #11 :ivl
push mainLEX3
pop mainx

; String #12 :ivl
push mainLEX3
pop mainx

; String #18 :ivl
push mainLEX6
pop mainx

; String #19 :ivl
push mainLEX3
pop mainy

; String #20 :iviii@2!
invoke fi, mainy, mainx
push eax ;результат функции
pop mainz
mov eax, mainLEX8
	invoke		ExitProcess, eax
main ENDP
end main