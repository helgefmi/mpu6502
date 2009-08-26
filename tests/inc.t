test inc zero
    LDA #$AA
    STA $50
    INC $50
    .byte 2
assert reg.p 7
assert flags.n 1
assert flags.z 0
assert mem.0x50 0xAB

test inc zero x
    LDX #$A
    LDA #$AA
    STA $5A
    INC $50,X
    .byte 2
assert reg.p 9
assert flags.n 1
assert flags.z 0
assert mem.0x5A 0xAB

test inc abs
    LDA #$AA
    STA $5000
    INC $5000
    .byte 2
assert reg.p 9
assert flags.n 1
assert flags.z 0
assert mem.0x5000 0xAB

test inc abs x
    LDX #$CC
    LDA #$AA
    STA $50CC
    INC $5000,X
    .byte 2
assert reg.p 11
assert flags.n 1
assert flags.z 0
assert mem.0x50CC 0xAB
