bits 32 

global start        
;Se citeste de
;Se citeste de la tastatura un cuvant (sir de caractere de maxim 20 de caractere) si un numar reprezentat pe un octet. Daca numarul este impar se cere criptarea cuvantului prin adunarea la fiecare caracter a numarului citit modulo 20. Daca numarul este par se cere criptarea cuvantului prin adaugarea dupa fiecare consoana a gruparii "p"+consoana. Se cere afisarea cuvantului criptat

extern exit, scanf, printf               
import exit msvcrt.dll 
import scanf msvcrt.dll 
import printf msvcrt.dll
   
segment data use32 class=data
   cuvant times 21 db 0 
   n resd 1 
   format_cuv db '%s', 0
   format_numar db '%d', 0
   vocale db 'aeiou'
   len equ $-vocale
   cuvant_afisare times 61 db 0 
   
segment code use32 class=code
    start:
        push dword cuvant
        push dword format_cuv
        call [scanf]
        add esp, 2*4
            
        push dword n 
        push dword format_numar
        call [scanf]
        add esp, 2*4
        
        mov ecx, [n]
        shr ecx, 1 
        
        jc impar ; cf=1, atunci nr e impar
        ;aici cazul in care e par 
                ;Daca numarul este par se cere criptarea cuvantului prin adaugarea dupa fiecare consoana a gruparii "p"+consoana.
                mov ecx, 21 
                mov esi, 0 
                mov edi, 0 ; aici cuvantul nou
                
                salt: 
                    cmp byte [esi+cuvant], 0 ; am ajuns la capatul cuvantului
                    je afisare_par 
                    
                    mov al, [esi+cuvant]
                    push ecx
                    mov ecx, len
                    mov ebx, 0
                    verific_vocala:
                        mov dl, [ebx+vocale]
                        cmp al, dl 
                        je nu_e_consoana
                        inc ebx
                    loop verific_vocala
                    
                    ;tratez cazul cand e consoana
                    mov [cuvant_afisare+edi], al ; consoana
                    inc edi 
                    mov [cuvant_afisare+edi], byte 'p' ;adaug p 
                    inc edi
                    
                    nu_e_consoana:
                    ; aici mereu adaug un caracter nou 
                    mov [cuvant_afisare+edi], al 
                    inc edi
                    inc esi
                    pop ecx
                loop salt 
                
                afisare_par:
                push dword cuvant_afisare
                push dword format_cuv
                call [printf]
                add esp, 4*2 
                
                jmp final
        
        impar:
                ;Daca numarul este impar se cere criptarea cuvantului prin adunarea la fiecare caracter a numarului citit modulo 20.
                mov ecx, 21
                mov esi, 0 ; indicele cu care parcurg cuvantul
                saritura:
                    cmp byte [esi+cuvant], 0; am ajuns la capatul cuvantului
                    je afisare_impar
                    
                    mov ax, [n]
                    mov dx, 0 
                    mov bx, 20 
                    div bx 
                    ;mov edi, [n]
                    add [esi+cuvant],dx
                    inc esi 
                loop saritura
                
                afisare_impar:
                push dword cuvant
                push dword format_cuv
                call [printf]
                add esp, 2*4
                
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
