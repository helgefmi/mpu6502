test rol acc zero and carry zero sets z flag
    LDA #0
    ROL
    .byte $2
assert reg.p 4
assert reg.a 0
assert flags.z 1
assert flags.n 0
assert flags.c 0

test rol acc zero and carry one clears z flag
    SEC
    LDA #0
    ROL
    .byte $2
assert reg.p 5
assert reg.a 0x01
assert flags.z 0
assert flags.n 0

test rol acc sets n flag
    SEC
    LDA #$40
    ROL
    .byte $2
assert reg.pc 5
assert reg.ac 0x81
assert flags.n 1
assert flags.z 0
assert flags.c 0

test rol acc shifts out zero
    LDA #$7F
    ROL
    .byte $2
assert reg.pc 4
assert reg.ac 0xFE
assert flags.c 0
assert flags.n 1
assert flags.z 0

test rol acc shifts out one
    LDA #$FF
    ROL
    .byte $2
assert reg.pc 4
assert reg.ac 0xFE
assert flags.c 1
assert flags.n 1
assert flags.z 0

test rol absolute zero and carry zero sets z flag
    ROL $ABCD
    .byte $2
assert reg.pc 4
assert mem.0xABCD 0x00
assert flags.z 1
assert flags.n 0
assert flags.c 0

test rol absolute zero and carry one clears z flag
    SEC
    ROL $ABCD
    .byte $2
assert reg.pc 5
assert mem.0xABCD 0x01
assert flags.z 0
assert flags.n 0
assert flags.c 0

test rol absolute sets n flag
    SEC
    LDA #$40
    STA $ABCD
    ROL $ABCD
    .byte $2
assert reg.pc 10
assert mem.0xABCD 0x81
assert flags.n 1
assert flags.z 0
assert flags.c 0

test rol absolute shifts out zero
    LDA #$7F
    STA $ABCD
    ROL $ABCD
    .byte $2
assert reg.pc 9
assert mem.0xABCD 0xFE
assert flags.c 0
assert flags.n 1
assert flags.z 0

test rol absolute shifts out one
    LDA #$FF
    STA $ABCD
    ROL $ABCD
    .byte $2
assert reg.pc 9
assert mem.0xABCD 0xFE
assert flags.c 1
assert flags.n 1
assert flags.z 0

test rol zp zero and carry zero sets z flag
    ROL $10
    .byte $2
assert reg.pc 3
assert mem.0x10 0x00
assert flags.z 1
assert flags.n 0
assert flags.c 0

test rol zp zero and carry one clears z flag
    SEC
    ROL $10
    .byte $2
assert reg.pc 4
assert mem.0x10 0x01
assert flags.z 0
assert flags.n 0
assert flags.c 0

test rol zp sets n flag
    LDA #$40
    STA $10
    ROL $10
    .byte $2
assert reg.pc 7
assert mem.0x10 0x80
assert flags.n 1
assert flags.z 0
assert flags.c 0

test rol zp shifts out zero
    LDA #$7F
    STA $10
    ROL $10
    .byte $2
assert reg.pc 7
assert mem.0x10 0xFE
assert flags.c 0
assert flags.n 1
assert flags.z 0

test rol zp shifts out one
    LDA #$FF
    STA $10
    ROL $10
    .byte $2
assert reg.pc 7
assert mem.0x10 0xFE
assert flags.c 1
assert flags.n 1
assert flags.z 0

test rol absolute x indexed zero and carry zero sets z flag
    LDX #$03
    ROL $ABC0,X
    .byte $2
assert reg.pc 6
assert mem.0xABC3 0
assert flags.z 1
assert flags.n 0
assert flags.c 0

test rol absolute x indexed zero and carry one clears z flag
    SEC
    LDX #$3
    ROL $ABC0,X
    .byte $2
assert reg.pc 7
assert mem.0xABC3 1
assert flags.z 0
assert flags.n 0
assert flags.c 0

test rol absolute x indexed sets n flag
    SEC
    LDX #$03
    LDA #$40
    STA $ABC3
    ROL $ABC0,X
    .byte $2
assert reg.pc 12
assert mem.0xABC3 0x81
assert flags.n 1
assert flags.z 0
assert flags.c 0

test rol absolute x indexed shifts out zero
    LDX #$03
    LDA #$7F
    STA $ABC3
    ROL $ABC0,X
    .byte $2
assert reg.pc 11
assert mem.0xABC3 0xFE
assert flags.c 0
assert flags.n 1
assert flags.z 0

test rol absolute x indexed shifts out one
    LDX #$03
    LDA #$FF
    STA $ABC3
    ROL $ABC0,X
    .byte $2
assert reg.pc 11
assert mem.0xABC3 0xFE
assert flags.c 1
assert flags.n 1
assert flags.z 0

test rol zp x indexed zero and carry zero sets z flag
    LDX #$03
    ROL $10,X
    .byte $2
assert reg.pc 5
assert mem.0x13 0
assert flags.z 1
assert flags.n 0
assert flags.n 0

test rol zp x indexed zero and carry one clears z flag
    SEC
    LDX #$03
    ROL $10,X
    .byte $2
assert reg.pc 6
assert mem.0x13 1
assert flags.z 0
assert flags.n 0
assert flags.c 0

test rol zp x indexed sets n flag
    SEC
    LDA #$40
    STA $13
    LDX #$03
    ROL $10,X
    .byte $2
assert reg.pc 10
assert mem.0x13 0x81
assert flags.n 1
assert flags.z 0
assert flags.c 0

test rol zp x indexed shifts out zero
    LDX #$03
    LDA #$7F
    STA $13
    ROL $10,X
    .byte $2
assert reg.pc 9
assert mem.0x13 0xFE
assert flags.c 0
assert flags.z 0
assert flags.n 1

test rol zp x indexed shifts out one
    LDX #$03
    LDA #$FF
    STA $13
    ROL $10,X
    .byte $2
assert reg.pc 9
assert mem.0x13 0xFE
assert flags.c 1
assert flags.n 1
assert flags.z 0
