test jsr abs
    NOP
    JSR end
    LDA #$AB
    end .byte 2
assert reg.a 0
assert mem.0x1FF 3

test jsr abs 2
    LDA #$AB
    JSR end
    SEC
    SED
    SEI
    LDA #$0
    end .byte 2
assert reg.a 0xAB
assert flags.c 0
assert flags.d 0
assert flags.i 0
assert mem.0x1FF 4
