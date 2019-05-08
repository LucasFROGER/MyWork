.386



PUBLIC _vec3add
PUBLIC _vec3sub
PUBLIC _vec3mul
PUBLIC _vec3div

PUBLIC _vec3setadd
PUBLIC _vec3setsub
PUBLIC _vec3setmul
PUBLIC _vec3setdiv

PUBLIC _vec3dotproduct
PUBLIC _vec3crossproduct

PUBLIC _addition
PUBLIC _substraction
PUBLIC _multiplication
PUBLIC _division

_CODE SEGMENT dword public 'CODE' use32
ASSUME CS:_CODE

	_addition PROC near

		push ebp
		mov ebp, esp   
		push ebx
	
		mov	eax, [ebp + 12]			
		mov	ebx, [ebp + 8]			
	
		add	eax, ebx			 
		pop	ebx
		pop	ebp
		ret

	_addition ENDP

_substraction PROC near

	push ebp
	mov ebp, esp   
	push ebx
	
	mov	eax, [ebp + 8]			
	mov	ebx, [ebp + 12]			
	
	sub	eax, ebx
	pop	ebx
	pop	ebp
	ret

_substraction ENDP

_multiplication PROC near

	push ebp
	mov ebp, esp   
	push ebx
	
	mov	eax, [ebp + 12]			
	mov	ebx, [ebp + 8]			
	

	mul ebx	
						
	pop	ebx
	pop	ebp
	ret

_multiplication ENDP

_division PROC near

	push ebp
	mov ebp, esp   
	push ebx
	
	mov	eax, [ebp + 8]			
	mov	ebx, [ebp + 12]			
	
	div ebx			
						
	pop	ebx
	pop	ebp
	ret

_division ENDP

_vec3add PROC near
	
	push ebp
	mov ebp, esp
	push ebx

	mov	ebx, [ebp + 12]
	mov	[eax], DWORD PTR ebx		
	mov	ebx, [ebp + 24]
	
	add	[eax], DWORD PTR ebx

	mov	ebx, [ebp + 16]
	mov	[eax + 4], DWORD PTR ebx
	mov	ebx, [ebp + 28]
	
	add	[eax + 4], DWORD PTR ebx

	mov	ebx, [ebp + 20]
	mov	[eax + 8], DWORD PTR ebx
	mov	ebx, [ebp + 32]
	
	add	[eax + 8], DWORD PTR ebx

	pop	ebx
	pop	ebp
	ret

_vec3add ENDP

_vec3sub PROC near

	push ebp
	mov ebp, esp
	push ebx

	mov	ebx, [ebp + 12]
	mov	[eax], DWORD PTR ebx		
	mov	ebx, [ebp + 24]
	
	sub	[eax], DWORD PTR ebx

	mov	ebx, [ebp + 16]
	mov	[eax + 4], DWORD PTR ebx
	mov	ebx, [ebp + 28]
	
	sub	[eax + 4], DWORD PTR ebx

	mov	ebx, [ebp + 20]
	mov	[eax + 8], DWORD PTR ebx
	mov	ebx, [ebp + 32]
	
	sub	[eax + 8], DWORD PTR ebx

	pop	ebx
	pop	ebp
	ret

_vec3sub ENDP

_vec3mul PROC near

	push ebp
	mov ebp, esp
	push ebx

	push eax ; save eax value

	mov	eax, [ebp + 12]		
	mov	ebx, [ebp + 24]
	
	mul	ebx
	mov ebx, eax
	pop eax ; get eax saved value
	mov [eax], DWORD PTR ebx

	push eax ; save eax value

	mov	eax, [ebp + 16]	; get vec1 value
	mov	ebx, [ebp + 28]	; get vec2 value
	
	mul	ebx ; vec1.value * vec2.value
	mov ebx, eax ; mov result into ebx
	pop eax ; get eax saved value
	mov[eax + 4], DWORD PTR ebx ; add new value to eax

	
	push eax

	mov	eax, [ebp + 20]		
	mov	ebx, [ebp + 32]
	
	mul	ebx
	mov ebx, eax
	pop eax
	mov[eax + 8], DWORD PTR ebx

	pop	ebx
	pop	ebp
	ret

_vec3mul ENDP

_vec3div PROC near

	push ebp
	mov ebp, esp
	push ebx
	push edx

	mov edx, 0 ; used by div

	push eax ; save eax value

	mov	eax, DWORD PTR [ebp + 12]		
	mov	ebx, DWORD PTR [ebp + 24]
	
	div	ebx

	mov ebx, eax
	pop eax ; get eax saved value
	mov [eax], DWORD PTR ebx

	push eax ; save eax value

	mov	eax, [ebp + 16]	; get vec1 value
	mov	ebx, [ebp + 28]	; get vec2 value
	
	div	ebx ; vec1.value / vec2.value
	mov ebx, eax ; mov result into ebx
	pop eax ; get eax saved value
	mov[eax + 4], DWORD PTR ebx ; add new value to eax

	
	push eax

	mov	eax, [ebp + 20]		
	mov	ebx, [ebp + 32]
	
	div	ebx
	mov ebx, eax
	pop eax
	mov[eax + 8], DWORD PTR ebx

	pop edx
	pop	ebx
	pop	ebp
	ret

_vec3div ENDP

_vec3setadd PROC near
	
	push ebp
	mov ebp, esp

	mov ebx, [ebp + 8]
	mov	ecx, [ebp + 12]	
	add	[ebx], DWORD PTR ecx
	mov ecx, [ebx]
	mov [eax], DWORD PTR ecx
	
	mov	ecx, [ebp + 16]
	add	[ebx + 4], DWORD PTR ecx
	mov ecx, [ebx + 4]
	mov [eax + 4], DWORD PTR ecx

	mov	ecx, [ebp + 20]
	add	[ebx + 8], DWORD PTR ecx
	mov ecx, [ebx + 8]
	mov [eax + 8], DWORD PTR ecx

	pop	ebp
	ret

_vec3setadd ENDP

_vec3setsub PROC near

	push ebp
	mov ebp, esp ; stack ptr

	mov ebx, [ebp + 8]
	mov	ecx, [ebp + 12]	
	sub	[ebx], DWORD PTR ecx
	
	mov	ecx, [ebp + 16]
	sub	[ebx + 4], DWORD PTR ecx

	mov	ecx, [ebp + 20]
	sub	[ebx + 8], DWORD PTR ecx

	pop	ebp
	ret

_vec3setsub ENDP

	_vec3setmul PROC near

		push ebp
		mov ebp, esp
	
		mov ebx, [ebp + 8]
	
		push eax
		mov eax, [ebx]
		mov	ecx, [ebp + 12]	
		mul	ecx
		mov [ebx], eax
		mov ecx, eax
		pop eax
		mov [eax], ecx

		push eax
		mov eax, [ebx + 4]
		mov	ecx, [ebp + 16]	
		mul	ecx
		mov [ebx + 4], eax
		mov ecx, eax
		pop eax
		mov [eax + 4], ecx

		push eax
		mov eax, [ebx + 8]
		mov	ecx, [ebp + 20]	
		mul	ecx
		mov [ebx + 8], eax
		mov ecx, eax
		pop eax
		mov [eax + 8], ecx


		pop	ebp
		ret

	_vec3setmul ENDP

_vec3setdiv PROC near
	
	push ebp
	mov ebp, esp ; stack ptr
	
	mov edx, 0

	mov ebx, [ebp + 8]
	
	mov eax, [ebx]
	mov	ecx, [ebp + 12]	
	div	ecx
	mov [ebx], eax

	mov eax, [ebx + 4]
	mov	ecx, [ebp + 16]	
	div	ecx
	mov [ebx + 4], eax

	mov eax, [ebx + 8]
	mov	ecx, [ebp + 20]	
	div	ecx
	mov [ebx + 8], eax

	pop	ebp
	ret

_vec3setdiv ENDP

_vec3dotproduct PROC near
	
	;((m_x * vec.m_x) + (m_y * vec.m_y) + (m_z * vec.m_z))
	push ebp
	mov ebp, esp ; stack ptr
	
	mov	eax, [ebp + 8]		
	mov	ebx, [ebp + 20]
	
	mul	ebx
	mov ecx, eax

	mov	eax, [ebp + 12]		
	mov	ebx, [ebp + 24]
	
	mul	ebx
	add ecx, eax

	
	mov	eax, [ebp + 16]		
	mov	ebx, [ebp + 28]
	
	mul	ebx
	add ecx, eax

	mov eax, DWORD PTR ecx

	pop	ebp
	ret

_vec3dotproduct ENDP

_vec3crossproduct PROC near
	
	;(m_y * vec.m_z) - (m_z * vec.m_y),
	;(m_z * vec.m_x) - (m_x * vec.m_z),
	;(m_x * vec.m_y) - (m_y * vec.m_x)

	; (8, 12, 16) (20, 24, 28)


	push ebp
	mov ebp, esp ; stack ptr
	
	push eax ; store result
	mov	eax, [ebp + 16]	;m_y
	mov	ebx, [ebp + 32] ;vec.m_z
	mul	ebx  ;m_y * vec.m_z
	mov ebx, eax ;(m_y * vec.m_z)
	mov	eax, [ebp + 20] ; m_z
	mov	ecx, [ebp + 28] ;vec.m_y
	mul	ecx; m_z * vec.m_y
	mov ecx, eax; (m_z * vec.m_y)
	sub ebx, ecx ;(m_y * vec.m_z) - (m_z * vec.m_y)
	pop eax; get result
	mov [eax], DWORD PTR ebx; set result.x
	
	push eax ; store result
	mov	eax, [ebp + 20]	;m_z
	mov	ebx, [ebp + 24] ;vec.m_x
	mul	ebx  ;m_z * vec.m_x
	mov ebx, eax ;(m_z * vec.m_x)
	mov	eax, [ebp + 12] ; m_x
	mov	ecx, [ebp + 32] ;vec.m_z
	mul	ecx; m_x * vec.m_z
	mov ecx, eax; (m_x * vec.m_z)
	sub ebx, ecx ;(m_z * vec.m_x) - (m_x * vec.m_z)
	pop eax; get result
	mov [eax + 4], DWORD PTR ebx; set result.y
	
	push eax ; store result
	mov	eax, [ebp + 12]	;m_x
	mov	ebx, [ebp + 28] ;vec.m_y
	mul	ebx  ;m_x * vec.m_y
	mov ebx, eax ;(m_x * vec.m_y)
	mov	eax, [ebp + 16] ; m_y
	mov	ecx, [ebp + 24] ;vec.m_x
	mul	ecx; m_y * vec.m_x
	mov ecx, eax; (m_y * vec.m_x)
	sub ebx, ecx ;(m_x * vec.m_y) - (m_y * vec.m_x)
	pop eax; get result
	mov [eax + 8], DWORD PTR ebx; set result.z


	pop	ebp
	ret

_vec3crossproduct ENDP

_CODE ENDS
END