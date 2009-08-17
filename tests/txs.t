test txa_1
    LDX #$AB
    TXS
assert reg.p 3
assert reg.s 0xAB
