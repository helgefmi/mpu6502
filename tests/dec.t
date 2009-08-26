test dec zero
    LDA #$AC
    STA $50
    DEC $50
    .byte 2
assert reg.p 7
assert flags.n 1
assert flags.z 0
assert mem.0x50 0xAB

test dec zero x
    LDX #$A
    LDA #$AC
    STA $5A
    DEC $50,X
    .byte 2
assert reg.p 9
assert flags.n 1
assert flags.z 0
assert mem.0x5A 0xAB

test dec abs
    LDA #$AC
    STA $5000
    DEC $5000
    .byte 2
assert reg.p 9
assert flags.n 1
assert flags.z 0
assert mem.0x5000 0xAB

test dec abs x
    LDX #$CC
    LDA #$AC
    STA $50CC
    DEC $5000,X
    .byte 2
assert reg.p 11
assert flags.n 1
assert flags.z 0
assert mem.0x50CC 0xAB
