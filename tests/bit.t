test bit_zero_flags_nv
    LDA #$FF
    STA $CD
    BIT $CD
    .byte 2
assert reg.p 7
assert flags.z 0
assert flags.v 1
assert flags.n 1

test bit_zero_flags_zn
    LDA #$A0
    STA $CD
    LDA #$0A
    BIT $CD
    .byte 2
assert reg.p 9
assert flags.z 1
assert flags.v 0
assert flags.n 1

test bit_zero_flags_zv
    LDA #$40
    STA $CD
    LDA #$A0
    BIT $CD
    .byte 2
assert reg.p 9
assert flags.z 1
assert flags.v 1
assert flags.n 0

test bit_zero_flags_nv
    LDA #$FF
    STA $CD00
    STA $CE
    BIT $CD00
    .byte 2
assert reg.p 11
assert flags.z 0
assert flags.v 1
assert flags.n 1

test bit_zero_flags_zn
    LDA #$A0
    STA $CD00
    LDA #$0A
    BIT $CD00
    .byte 2
assert reg.p 11
assert flags.z 1
assert flags.v 0
assert flags.n 1

test bit_zero_flags_zv
    LDA #$40
    STA $CD00
    LDA #$A0
    BIT $CD00
    .byte 2
assert reg.p 11
assert flags.z 1
assert flags.v 1
assert flags.n 0
