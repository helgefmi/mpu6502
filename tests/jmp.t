test jmp abs
    JMP end
    LDA #$AB
    end .byte 2
assert reg.a 0

test jmp abs 2
    LDA #$AB
    JMP end
    SEC
    SED
    SEI
    LDA #$0
    end .byte 2
assert reg.a 0xAB
assert flags.c 0
assert flags.d 0
assert flags.i 0

test jmp ind
    LDA #end
    STA $AB
    LDA #0
    JMP ($AB)
    LDA #$AB
    end .byte 2
assert reg.a 0

test jmp ind 2
    LDA #end
    STA $EF
    LDA #$AB
    JMP ($EF)
    SEC
    SED
    SEI
    LDA #$0
    end .byte 2
assert reg.a 0xAB
assert flags.c 0
assert flags.d 0
assert flags.i 0
