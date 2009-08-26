test lsr acc c
    LDA #$AB
    LSR
    .byte $2
assert reg.p 4
assert reg.ac 0x55
assert flags.z 0
assert flags.c 1
assert flags.n 0

test lsr acc z
    LDA #$1
    LSR
    .byte $2
assert reg.p 4
assert reg.ac 0
assert flags.z 1
assert flags.c 1
assert flags.n 0


test lsr zero c
    LDA #$AB
    STA $50
    LSR $50
    .byte $2
assert reg.p 7
assert mem.0x50 0x55
assert flags.z 0
assert flags.c 1
assert flags.n 0

test lsr zero z
    LDA #$1
    STA $50
    LSR $50
    .byte $2
assert reg.p 7
assert mem.0x50 0
assert flags.z 1
assert flags.c 1
assert flags.n 0


test lsr zero x
    LDX #$A
    LDA #$AB
    STA $5A
    LSR $50,X
    .byte $2
assert reg.p 9
assert flags.n 0
assert flags.z 0
assert mem.0x5A 0x55

test lsr abs
    LDA #$AB
    STA $5000
    LSR $5000
    .byte $2
assert reg.p 9
assert flags.n 0
assert flags.z 0
assert mem.0x5000 0x55

test lsr abs x
    LDX #$CC
    LDA #$AB
    STA $50CC
    LSR $5000,X
    .byte $2
assert reg.p 11
assert flags.n 0
assert flags.z 0
assert mem.0x50CC 0x55
