test stx_zero
    LDX #$AB
    STX $CD
    .byte $2
assert reg.p 5
assert mem.0xCD 0xAB

test stx_zero_y
    LDY #$A
    LDX #$EF
    STX $50,Y
    .byte $2
assert reg.p 7
assert mem.0x5A 0xEF

test stx_abs
    LDX #$EF
    STX $ABCD
    .byte $2
assert reg.p 6
assert mem.0xABCD 0xEF
