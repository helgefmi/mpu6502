test ror acc zero and carry zero sets z flag
    LDA #0
    ROR
assert reg.p 3
assert reg.a 0
assert flags.z 1
assert flags.n 0
assert flags.c 0

test ror acc zero and carry one clears z flag
    SEC
    LDA #0
    ROR
assert reg.p 4
assert reg.a 0x80
assert flags.z 0
assert flags.n 1

test ror acc sets n flag
    SEC
    LDA #$40
    ROR
assert reg.pc 4
assert reg.ac 0xA0
assert flags.n 1
assert flags.z 0
assert flags.c 0

test ror acc shifts out zero
    LDA #$7F
    ROR
assert reg.pc 3
assert reg.ac 0x3F
assert flags.c 1
assert flags.n 0
assert flags.z 0

test ror acc shifts out one
    LDA #$FF
    ROR
assert reg.pc 3
assert reg.ac 0x7F
assert flags.c 1
assert flags.n 0
assert flags.z 0

test ror absolute zero and carry zero sets z flag
    ROR $ABCD
assert reg.pc 3
assert mem.0xABCD 0x00
assert flags.z 1
assert flags.n 0
assert flags.c 0

test ror absolute zero and carry one clears z flag
    SEC
    ROR $ABCD
assert reg.pc 4
assert mem.0xABCD 0x80
assert flags.z 0
assert flags.n 1
assert flags.c 0

test ror absolute sets n flag
    SEC
    LDA #$40
    STA $ABCD
    ROR $ABCD
assert reg.pc 9
assert mem.0xABCD 0xA0
assert flags.n 1
assert flags.z 0
assert flags.c 0

test ror absolute shifts out zero
    LDA #$7F
    STA $ABCD
    ROR $ABCD
assert reg.pc 8
assert mem.0xABCD 0x3F
assert flags.c 1
assert flags.n 0
assert flags.z 0

test ror absolute shifts out one
    LDA #$FF
    STA $ABCD
    ROR $ABCD
assert reg.pc 8
assert mem.0xABCD 0x7F
assert flags.c 1
assert flags.n 0
assert flags.z 0

test ror zp zero and carry zero sets z flag
    ROR $10
assert reg.pc 2
assert mem.0x10 0x00
assert flags.z 1
assert flags.n 0
assert flags.c 0

test ror zp zero and carry one clears z flag
    SEC
    ROR $10
assert reg.pc 3
assert mem.0x10 0x80
assert flags.z 0
assert flags.n 1
assert flags.c 0

test ror zp sets n flag
    LDA #$40
    STA $10
    ROR $10
assert reg.pc 6
assert mem.0x10 0x20
assert flags.n 0
assert flags.z 0
assert flags.c 0

test ror zp shifts out zero
    LDA #$7F
    STA $10
    ROR $10
assert reg.pc 6
assert mem.0x10 0x3F
assert flags.c 1
assert flags.n 0
assert flags.z 0

test ror zp shifts out one
    LDA #$FF
    STA $10
    ROR $10
assert reg.pc 6
assert mem.0x10 0x7F
assert flags.c 1
assert flags.n 0
assert flags.z 0

test ror absolute x indexed zero and carry zero sets z flag
    LDX #$03
    ROR $ABC0,X
assert reg.pc 5
assert mem.0xABC3 0
assert flags.z 1
assert flags.n 0
assert flags.c 0

test ror absolute x indexed zero and carry one clears z flag
    SEC
    LDX #$3
    ROR $ABC0,X
assert reg.pc 6
assert mem.0xABC3 0x80
assert flags.z 0
assert flags.n 1
assert flags.c 0

test ror absolute x indexed sets n flag
    SEC
    LDX #$03
    LDA #$40
    STA $ABC3
    ROR $ABC0,X
assert reg.pc 11
assert mem.0xABC3 0xA0
assert flags.n 1
assert flags.z 0
assert flags.c 0

test ror absolute x indexed shifts out zero
    LDX #$03
    LDA #$7F
    STA $ABC3
    ROR $ABC0,X
assert reg.pc 10
assert mem.0xABC3 0x3F
assert flags.c 1
assert flags.n 0
assert flags.z 0

test ror absolute x indexed shifts out one
    LDX #$03
    LDA #$FF
    STA $ABC3
    ROR $ABC0,X
assert reg.pc 10
assert mem.0xABC3 0x7F
assert flags.c 1
assert flags.n 0
assert flags.z 0

test ror zp x indexed zero and carry zero sets z flag
    LDX #$03
    ROR $10,X
assert reg.pc 4
assert mem.0x13 0
assert flags.z 1
assert flags.n 0
assert flags.n 0

test ror zp x indexed zero and carry one clears z flag
    SEC
    LDX #$03
    ROR $10,X
assert reg.pc 5
assert mem.0x13 0x80
assert flags.z 0
assert flags.n 1
assert flags.c 0

test ror zp x indexed sets n flag
    SEC
    LDA #$40
    STA $13
    LDX #$03
    ROR $10,X
assert reg.pc 9
assert mem.0x13 0xA0
assert flags.n 1
assert flags.z 0
assert flags.c 0

test ror zp x indexed shifts out zero
    LDX #$03
    LDA #$7F
    STA $13
    ROR $10,X
assert reg.pc 8
assert mem.0x13 0x3F
assert flags.c 1
assert flags.z 0
assert flags.n 0

test ror zp x indexed shifts out one
    LDX #$03
    LDA #$FF
    STA $13
    ROR $10,X
assert reg.pc 8
assert mem.0x13 0x7F
assert flags.c 1
assert flags.n 0
assert flags.z 0
