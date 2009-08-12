test ora_imm
    LDA #$F0
    ORA #$AB
assert reg.p 4
assert reg.a 0xFB

test ora_zero
    LDA #$AB
    STA $CD
    LDA #$F0
    ORA $CD
assert reg.p 8
assert reg.a 0xFB

test ora_zero_x
    LDX #$A
    LDA #$F0
    STA $5A
    LDA #$AB
    ORA $50,X
assert reg.p 10
assert reg.a 0xFB

test ora_abs
    LDA #$F0
    STA $ABCD
    LDA #$AB
    ORA $ABCD
assert reg.p 10
assert reg.a 0xFB

test ora_abs_x
    LDX #$CD
    LDA #$F0
    STA $ABCD
    LDA #$AB
    ORA $AB00,X
assert reg.p 12
assert reg.a 0xFB

test ora_abs_y
    LDY #$DC
    LDA #$F0
    STA $ABDC
    LDA #$AB
    ORA $AB00,Y
assert reg.p 12
assert reg.a 0xFB

test ora_ind_x
    LDX #$3
    LDA #$AB
    STA $53
    LDA #$F0
    STA $AB
    LDA #$AB
    ORA ($50,X)
assert reg.p 14
assert reg.a 0xFB

test ora_ind_x_abs
    LDX #$3
    LDA #$CD
    STA $53
    LDA #$AB
    STA $54
    LDA #$F0
    STA $ABCD
    LDA #$AB
    ORA ($50,X)
assert reg.p 19
assert reg.a 0xFB

test ora_ind_y
    LDY #$3
    LDA #$AB
    STA $50
    LDA #$F0
    STA $AE
    LDA #$AB
    ORA ($50),Y
assert reg.p 14
assert reg.a 0xFB

test ora_ind_y_abs
    LDY #$2
    LDA #$CD
    STA $50
    LDA #$AB
    STA $51
    LDA #$F0
    STA $ABCF
    LDA #$AB
    ORA ($50),Y
assert reg.p 19
assert reg.a 0xFB
