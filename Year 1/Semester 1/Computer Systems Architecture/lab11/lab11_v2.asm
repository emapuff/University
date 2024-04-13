bits 32 
global start        

extern subsecventa
extern exit, scanf, printf           
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll   
                          
;Se citesc mai multe siruri de caractere. Sa se determine daca primul apare ca subsecventa in fiecare din celelalte si sa se dea un mesaj corespunzator.
segment data use32 class=data
    string_principal resd 1
    format db '%s', 0
    string_auxiliar resd 1
    format_afisare db '%s', 0
    cuvant resd 1
    mesaj_pozitiv db "Este subsir! ", 0
    mesaj_negativ db "Nu este subsir! ", 0
   

segment code use32 class=code
    start:
        ;citim sirul principal
        push string_principal
        push dword format
        call [scanf]
        add esp, 2*4 
        
        repeta: 
            push string_auxiliar
            push dword format
            call [scanf]
            add esp, 2*4
            
            cmp byte [string_auxiliar], '#'
            je final
            
            push string_principal
            push string_auxiliar
            call subsecventa
            
            
            cmp ebx,1
            je am
            push dword mesaj_negativ
            call [printf]
            jmp doit
            am:
                push dword mesaj_pozitiv
                call [printf]
             
            doit:
            

        jmp repeta
        
    final:
        push    dword 0      
        call    [exit] 
        
    ; am:
        ; push dword mesaj_pozitiv
        ; call [printf]
        ; add esp,4
        ; ret
         
    
    
    ; nu_am:
        ; push dword mesaj_negativ
        ; call [printf]
        ; add esp,4
        ; ret
     
    
    