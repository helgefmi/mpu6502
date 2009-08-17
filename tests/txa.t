test txa_1
    LDX #$AB
    TXA
assert reg.p 3
assert reg.a 0xAB
