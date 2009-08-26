test txa_1
    LDX #$AB
    TXS
    .byte $2
assert reg.p 4
assert reg.s 0xAB
