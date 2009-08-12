test eor_imm
    LDA #$F0
    EOR #$AB
assert reg.p 4
assert reg.a 0x5B

test eor_zero
    LDA #$AB
    STA $CD
    LDA #$F0
    EOR $CD
assert reg.p 8
assert reg.a 0x5B

test eor_zero_x
    LDX #$A
    LDA #$F0
    STA $5A
    LDA #$AB
    EOR $50,X
assert reg.p 10
assert reg.a 0x5B

test eor_abs
    LDA #$F0
    STA $ABCD
    LDA #$AB
    EOR $ABCD
assert reg.p 10
assert reg.a 0x5B

test eor_abs_x
    LDX #$CD
    LDA #$F0
    STA $ABCD
    LDA #$AB
    EOR $AB00,X
assert reg.p 12
assert reg.a 0x5B

test eor_abs_y
    LDY #$DC
    LDA #$F0
    STA $ABDC
    LDA #$AB
    EOR $AB00,Y
assert reg.p 12
assert reg.a 0x5B

test eor_ind_x
    LDX #$3
    LDA #$AB
    STA $53
    LDA #$F0
    STA $AB
    LDA #$AB
    EOR ($50,X)
assert reg.p 14
assert reg.a 0x5B

test eor_ind_x_abs
    LDX #$3
    LDA #$CD
    STA $53
    LDA #$AB
    STA $54
    LDA #$F0
    STA $ABCD
    LDA #$AB
    EOR ($50,X)
assert reg.p 19
assert reg.a 0x5B

test eor_ind_y
    LDY #$3
    LDA #$AB
    STA $50
    LDA #$F0
    STA $AE
    LDA #$AB
    EOR ($50),Y
assert reg.p 14
assert reg.a 0x5B

test eor_ind_y_abs
    LDY #$2
    LDA #$CD
    STA $50
    LDA #$AB
    STA $51
    LDA #$F0
    STA $ABCF
    LDA #$AB
    EOR ($50),Y
assert reg.p 19
assert reg.a 0x5B
