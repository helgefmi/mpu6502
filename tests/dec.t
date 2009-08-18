test dec zero
    LDA #$AC
    STA $50
    DEC $50
assert reg.p 6
assert flags.n 1
assert flags.z 0
assert mem.0x50 0xAB

test dec zero x
    LDX #$A
    LDA #$AC
    STA $5A
    DEC $50,X
assert reg.p 8
assert flags.n 1
assert flags.z 0
assert mem.0x5A 0xAB

test dec abs
    LDA #$AC
    STA $5000
    DEC $5000
assert reg.p 8
assert flags.n 1
assert flags.z 0
assert mem.0x5000 0xAB

test dec abs x
    LDX #$CC
    LDA #$AC
    STA $50CC
    DEC $5000,X
assert reg.p 10
assert flags.n 1
assert flags.z 0
assert mem.0x50CC 0xAB
