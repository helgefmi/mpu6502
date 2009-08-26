test sty_zero
    LDY #$AB
    STY $CD
    .byte $2
assert reg.p 5
assert mem.0xCD 0xAB

test sty_zero_y
    LDX #$A
    LDY #$EF
    STY $50,X
    .byte $2
assert reg.p 7
assert mem.0x5A 0xEF

test sty_abs
    LDY #$EF
    STY $ABCD
    .byte $2
assert reg.p 6
assert mem.0xABCD 0xEF
