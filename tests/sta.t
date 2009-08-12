test sta_zero
    LDA #$AB
    STA $CD
assert reg.p 4
assert mem.0xCD 0xAB

test sta_zero_x
    LDX #$A
    LDA #$EF
    STA $50,X
assert reg.p 6
assert mem.0x5A 0xEF

test sta_abs
    LDA #$EF
    STA $ABCD
assert reg.p 5
assert mem.0xABCD 0xEF

test sta_abs_x
    LDX #$D
    LDA #$EF
    STA $ABC0,X
assert reg.p 7
assert mem.0xABCD 0xEF

test sta_abs_y
    LDY #$D
    LDA #$EF
    STA $ABC0,Y
assert reg.p 7
assert mem.0xABCD 0xEF

test sta_ind_x
    LDX #$3
    LDA #$AB
    STA $53
    LDA #$CD
    STA ($50,X)
assert reg.p 10
assert mem.0xAB 0xCD

test sta_ind_x_abs
    LDX #$3
    LDA #$CD
    STA $53
    LDA #$AB
    STA $54
    LDA #$EF
    STA ($50,X)
assert reg.p 14
assert mem.0xABCD 0xEF

test sta_ind_y
    LDY #$3
    LDA #$AB
    STA $50
    LDA #$CD
    STA ($50),Y
assert reg.p 10
assert mem.0xAE 0xCD

test sta_ind_y_abs
    LDY #$2
    LDA #$CD
    STA $50
    LDA #$AB
    STA $51
    LDA #$EF
    STA ($50),Y
assert reg.p 14
assert mem.0xABCF 0xEF
