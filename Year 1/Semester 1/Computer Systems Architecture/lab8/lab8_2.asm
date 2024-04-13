bits 32

global start

extern exit, scanf, fopen, fclose, fprintf
import exit msvcrt.dll
import scanf msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll

; Sa se citeasca de la tastatura un nume de fisier si un text.
; Sa se creeze un fisier cu numele dat in directorul curent si sa se scrie textul in acel fisier.
; Observatii: Numele de fisier este de maxim 30 de caractere. Textul este de maxim 120 de caractere.
section data use32 class=data
    len1 equ 31
    nume_fisier times len1 db 0
    format db '%s', 0 ; Format specifier for string input
    len2 equ 121 ;atentie la 0 
    text times len2 db 0
    mod_acces db 'w', 0
    descriptor_fisier dd -1

section code use32 class=code
start:
    ; Citeste numele fisierului de la tastatura
    push dword nume_fisier
    push dword format
    call [scanf]
    add esp, 4 * 2

    ; Citeste textul de la tastatura
    push dword text
    push dword format
    call [scanf]
    add esp, 4 * 2 ;outeam aici sa pun %s%s in format ca sa am doua stringuri de cititi (ordine inversa)

    ; Deschide fisierul pentru scriere
    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    add esp, 4 * 2
    mov [descriptor_fisier], eax

    cmp eax, 0
    je final

    ; Scrie textul in fisier
    push dword text
    push dword [descriptor_fisier]
    call [fprintf]
    add esp, 4 * 2

    ; Inchide fisierul
    push dword [descriptor_fisier]
    call [fclose]
    add esp, 4

final:
    push dword 0
    call [exit]
