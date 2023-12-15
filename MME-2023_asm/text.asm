.586
.model flat, stdcall
includelib kernel32.lib

ExitProcess PROTO :DWORD

SetConsoleTitleA proto :dword
GetStdHandle proto : dword
WriteConsoleA proto : dword, : dword, : dword, : dword, : dword

.const

L0 dword 2
L1 dword 3
L2 byte 12, '1w234567890', 0
L3 byte 11, '1234567890', 0
L4 dword 5
L5 byte 5, 'true', 0
L6 byte 5, 'true', 0
L7 byte 6, 'false', 0
L8 byte 6, 'Hello', 0
L9 dword 0
L10 dword 0

.data

retfi dword 0
fix dword 0
fiy dword 0
fiz dword 0
retfss byte 0
	byte 128 dup(0)
fssa byte  0
	byte 128 dup(0)
fssb byte  0
	byte 128 dup(0)
fssc byte  0
	byte 128 dup(0)
retmain dword 0
mainx dword 2
mainy dword 0
mainz dword 0
mainsa byte 12, '1w234567890', 0
	byte 116 dup(0)
mainsb byte 11, '1234567890', 0
	byte 117 dup(0)
mainsc byte  0
	byte 128 dup(0)
consol byte 'Console', 0
endl byte 10, 0
buffer byte 20 dup(0)


.code
printconsole proc uses eax ebx ecx edi esi,
			pstr:dword, ptitle : dword
			push ptitle
			call SetConsoleTitleA
			push - 11
			call GetStdHandle
			mov esi, pstr
			mov edi, -1
			count:
		inc edi
			cmp byte ptr[esi + edi], 0
			jne count
			push 0
			push 0
			push edi
			push pstr
			push eax
			call WriteConsoleA
			ret
			printconsole endp

int_to_char proc uses eax ebx ecx edi esi,
			pstr:dword,
			intfield : dword
			mov edi, pstr
			mov esi, 0
			mov eax, intfield
			cdq
			mov ebx, 10
			idiv ebx
			test eax, 80000000h
			jz plus
			neg eax
			neg edx
			mov cl, '-'
			mov[edi], cl
			inc edi
			plus :
		push dx
			inc esi
			test eax, eax
			jz fin
			cdq
			idiv ebx
			jmp plus
			fin :
		mov ecx, esi
			write :
		pop bx
			add bl, '0'
			mov[edi], bl
			inc edi
			loop write
			ret
			int_to_char endp

fi proc 

push fix
push fix
push fiy
pop ebx
pop eax
add eax,ebx
push eax
pop ebx
pop eax
mul ebx
push eax
pop fiz
push fiz
pop retfi
ret
fi endp

fss proc 

lea eax,fssa
push eax
pop eax
push offset consol
inc eax
push eax
call printconsole
push offset consol
push offset endl
call printconsole
lea eax,fssb
push eax
pop eax
push offset consol
inc eax
push eax
call printconsole
push offset consol
push offset endl
call printconsole
lea eax,fssa
push eax
xor ecx,ecx
lea edi,fssc
pop esi
mov cl,[esi]
rep movsb
lea eax,fssc
push eax
xor ecx,ecx
lea edi,retfss
pop esi
mov cl,[esi]
rep movsb
ret
fss endp

main proc 

push mainx
push L1
pop ebx
pop eax
add eax,ebx
push eax
pop mainy
push L4
push offset buffer
call int_to_char
push offset consol
push offset buffer
call printconsole
push offset consol
push offset endl
call printconsole
push mainz
pop eax
cmp eax, 0

jz endif0
lea eax,L5
push eax
pop eax
push offset consol
inc eax
push eax
call printconsole
push offset consol
push offset endl
call printconsole
jmp endif0

endif0:

lea eax,mainsc
push eax
pop edx
mov eax,[edx]
cmp eax, 0

jz labelf0
lea eax,L6
push eax
pop eax
push offset consol
inc eax
push eax
call printconsole
push offset consol
push offset endl
call printconsole
jmp endif1

labelf0:

lea eax,L7
push eax
pop eax
push offset consol
inc eax
push eax
call printconsole
push offset consol
push offset endl
call printconsole

endif1:

push mainx
push offset buffer
call int_to_char
push offset consol
push offset buffer
call printconsole
push offset consol
push offset endl
call printconsole
push mainy
push offset buffer
call int_to_char
push offset consol
push offset buffer
call printconsole
push offset consol
push offset endl
call printconsole
push mainx
push mainy
pop ebx
pop eax
mul ebx
push eax
push mainx
push mainy
pop fiy
pop fix
call fi
push retfi
pop ebx
pop eax
add eax,ebx
push eax
pop mainz
push mainz
push offset buffer
call int_to_char
push offset consol
push offset buffer
call printconsole
push offset consol
push offset endl
call printconsole
push mainx
push mainy
pop ebx
pop eax
add eax,ebx
push eax
push mainx
push mainy
pop fiy
pop fix
call fi
push retfi
pop ebx
pop eax
mul ebx
push eax
pop mainz
push mainz
push offset buffer
call int_to_char
push offset consol
push offset buffer
call printconsole
push offset consol
push offset endl
call printconsole
lea eax,mainsa
push eax
pop eax
push offset consol
inc eax
push eax
call printconsole
push offset consol
push offset endl
call printconsole
lea eax,mainsb
push eax
pop eax
push offset consol
inc eax
push eax
call printconsole
push offset consol
push offset endl
call printconsole
lea eax,mainsa
push eax
lea eax,mainsb
push eax
xor ecx,ecx
lea edi,fssb
pop esi
mov cl,[esi]
rep movsb
xor ecx,ecx
lea edi,fssa
pop esi
mov cl,[esi]
rep movsb
call fss
xor ecx,ecx
lea edi,retfss
pop esi
mov cl,[esi]
rep movsb
xor ecx,ecx
lea edi,mainsc
pop esi
mov cl,[esi]
rep movsb
lea eax,L8
push eax
pop eax
push offset consol
inc eax
push eax
call printconsole
push offset consol
push offset endl
call printconsole
push mainz
push L9
pop ebx
mov edx,0
pop eax
div ebx
push eax
push offset buffer
call int_to_char
push offset consol
push offset buffer
call printconsole
push L10
pop retmain
push - 1
call ExitProcess
main endp

end main
