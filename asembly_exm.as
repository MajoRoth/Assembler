MAIN: add r3,  LIST
LOOP: prn #48
lea STR,r6
inc r6
mov r3,K
sub r1,r4
bne END

inc r4
;comment
cmp val1,#-6 IDO - UNCOMENT WHEN YOU FIXED get_word_imediate()
bne %END
dec K
jmp %LOOP