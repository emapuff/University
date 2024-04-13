bits 32

global start        

extern exit, scanf, printf              
import exit msvcrt.dll    
import scanf msvcrt.dll
import printf msvcrt.dll

; Sa se citeasca de la tastatura un numar in baza 10 si sa se afiseze valoarea acelui numar in baza 16.
segment data use32 class=data
    n dd 0 ; aici vom citi numarul
    message db "Introduceti un numar in baza 10: ", 0
    format_citire db '%d', 0
    format_afisare db '%X',0

; our code starts here
segment code use32 class=code
    start:
        xor eax, eax
        push dword message
        call [printf]
        add esp, 4
        
        
        push dword n
        push dword format_citire
        call [scanf]
        add esp, 4*2

        
        mov eax, [n]

        push eax 
        push dword format_afisare 
        call [printf]
        add esp, 4*2

        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
