test stx_zero
    LDX #$AB
    STX $CD
assert reg.p 4
assert mem.0xCD 0xAB

test stx_zero_y
    LDY #$A
    LDX #$EF
    STX $50,Y
assert reg.p 6
assert mem.0x5A 0xEF

test stx_abs
    LDX #$EF
    STX $ABCD
assert reg.p 5
assert mem.0xABCD 0xEF
