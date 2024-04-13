bits 32

segment code use32 public code
global subsecventa

subsecventa:
        mov edi, [esp+4] ; edi=string auxiliar
        mov esi, [esp+8] ; esi= string principal 
          
        ;caut prima litera din string-ul principal
        mov al, [esi]
        call cauta
        cmp ebx, 0
        je nu_e_subsit
      
    
        inc esi
        inc edi 
        mov ebx, 0
        saltut:
            mov dl, [edi]
            cmp dl, 0
            je nu_e_subsit
            
            mov al, [esi]
            cmp al, dl 
            jne nu_e_subsit
            inc edi
            inc esi 
            cmp byte [esi], 0 
            jne saltut
            
          
          
    este:
        mov ebx, 1
        
    nu_e_subsit:
        ret 4*2
        
        
    cauta:
        mov ebx, 0 
        jump:
            mov dl, [edi]
            cmp al, dl 
            je exista
            inc edi 
            cmp byte [edi],0 
            jne jump
            
        jmp nu_exista
        
    exista:
        mov ebx, 1
 
        
    nu_exista:
        ret 4*2