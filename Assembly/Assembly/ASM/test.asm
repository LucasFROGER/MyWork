.686

; test returning value
PUBLIC _returnint
; test using parameters 
PUBLIC _addpairvalues
PUBLIC _addpairsvalues
; test returning struct
PUBLIC _returnpair
; check parameter order
PUBLIC _combinepairs;
; test using parameters to return struct
PUBLIC _addpairsvalues
; changing parameter value
PUBLIC _changeint
; changing struct value
PUBLIC _changevec4

_DATA SEGMENT dword public 'DATA' use32
ASSUME DS:_DATA

_DATA ENDS

_CODE SEGMENT dword public 'CODE' use32
ASSUME CS:_CODE

_returnint PROC near

	mov eax, 12
	ret

_returnint ENDP

_addpairvalues PROC near

	push ebp
	mov ebp, esp   
	push ebx
	
	mov	eax, [ebp + 12]
	mov	ebx, [ebp + 8]			
	
	add	eax, ebx			 
	pop	ebx
	pop	ebp
	ret

_addpairvalues ENDP

_addpairsvalues PROC near

	push ebp
	mov ebp, esp   
	push ebx
	
	mov	eax, [ebp + 20]			
	mov	ebx, [ebp + 16]			
	
	add	eax, ebx
	
	mov	ebx, [ebp + 12]			
	add	eax, ebx
	
	mov	ebx, [ebp + 8]			
	add	eax, ebx

	pop	ebx
	pop	ebp
	ret

_addpairsvalues ENDP

	_returnpair PROC near

		mov ebx, 120
		mov [eax],    DWORD PTR ebx
	
		mov [eax + 4],  DWORD PTR 12
		ret

	_returnpair ENDP

_combinepairs PROC near

	push ebp
	mov ebp, esp   
	push ebx
	
	mov	ebx, [ebp + 12]			
	mov [eax],  DWORD PTR ebx			
	
	mov	ebx, [ebp + 16]			
	mov [eax+ 4],  DWORD PTR ebx	

	mov	ebx, [ebp + 20]			
	mov [eax + 8],  DWORD PTR ebx	
	
	mov	ebx, [ebp + 24]			
	mov [eax + 12],  DWORD PTR ebx	

	pop	ebx
	pop	ebp
	ret

_combinepairs ENDP

	_addpair PROC near

		push ebp
		mov ebp, esp   
		push ebx

		mov	ebx, DWORD PTR [ebp + 20]
		mov	[eax], DWORD PTR ebx			
		mov	ebx, DWORD PTR [ebp + 12]			
	
		add	[eax], DWORD PTR ebx	

		mov	ebx, DWORD PTR [ebp + 16]
		mov	[eax + 4], DWORD PTR ebx			
		mov	ebx, DWORD PTR [ebp + 24]			
	
		add	[eax + 4], DWORD PTR ebx

		pop	ebx
		pop	ebp
		ret

	_addpair ENDP

	_changeint PROC near

		push ebp
		mov ebp, esp   
	
		mov	eax, [ebp + 8]
		mov ebx, 25
		mov [eax], DWORD PTR ebx
		
		pop	ebp
		ret

	_changeint ENDP

_changevec4 PROC near

	push ebp
	mov ebp, esp   
	push ecx
	
	mov	eax, [ebp + 8]
	mov ecx, 25

	mov [eax], DWORD PTR ecx
	mov [eax + 4], DWORD PTR ecx
	mov [eax + 8], DWORD PTR ecx
	mov [eax + 12], DWORD PTR ecx
	
	pop	ecx
	pop	ebp
	ret

_changevec4 ENDP

_CODE ENDS
END
