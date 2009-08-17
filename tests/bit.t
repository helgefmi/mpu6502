test bit_zero_flags_nv
    LDA #$FF
    STA $CD
    BIT $CD
assert reg.p 6
assert flags.z 0
assert flags.v 1
assert flags.n 1

test bit_zero_flags_zn
    LDA #$A0
    STA $CD
    LDA #$0A
    BIT $CD
assert reg.p 8
assert flags.z 1
assert flags.v 0
assert flags.n 1

test bit_zero_flags_zv
    LDA #$40
    STA $CD
    LDA #$A0
    BIT $CD
assert reg.p 8
assert flags.z 1
assert flags.v 1
assert flags.n 0

test bit_zero_flags_nv
    LDA #$FF
    STA $CD00
    STA $CE
    BIT $CD00
assert reg.p 10
assert flags.z 0
assert flags.v 1
assert flags.n 1

test bit_zero_flags_zn
    LDA #$A0
    STA $CD00
    LDA #$0A
    BIT $CD00
assert reg.p 10
assert flags.z 1
assert flags.v 0
assert flags.n 1

test bit_zero_flags_zv
    LDA #$40
    STA $CD00
    LDA #$A0
    BIT $CD00
assert reg.p 10
assert flags.z 1
assert flags.v 1
assert flags.n 0
