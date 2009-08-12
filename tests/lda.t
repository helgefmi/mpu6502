test lda_imm
    LDA #$AB
assert reg.p 2
assert reg.a 0xAB

test lda_zero
    LDA #$AB
    STA $CD
    LDA #0
    LDA $CD
assert reg.p 8
assert reg.a 0xAB

test lda_zero_x
    LDX #$A
    LDA #$BC
    STA $5A
    LDA $50,X
assert reg.p 8
assert reg.a 0xBC

test lda_abs
    LDA #$EF
    STA $ABCD
    LDA #0
    LDA $ABCD
assert reg.p 10
assert reg.a 0xEF

test lda_abs_x
    LDX #$CD
    LDA #$EF
    STA $ABCD
    LDA $AB00,X
assert reg.p 10
assert reg.a 0xEF

test lda_abs_y
    LDA #$AB
    STA $ABDC
    LDY #$DC
    LDA $AB00,Y
assert reg.p 10
assert reg.a 0xAB

test lda_ind_x
    LDX #$3
    LDA #$AB
    STA $53
    LDA #$CD
    STA $AB
    LDA #0
    LDA ($50,X)
assert reg.p 14
assert reg.a 0xCD

test lda_ind_x_abs
    LDX #$3
    LDA #$CD
    STA $53
    LDA #$AB
    STA $54
    LDA #$EF
    STA $ABCD
    LDA #0
    LDA ($50,X)
assert reg.p 19
assert reg.a 0xEF

test lda_ind_y
    LDY #$3
    LDA #$AB
    STA $50
    LDA #$CD
    STA $AE
    LDA #0
    LDA ($50),Y
assert reg.p 14
assert reg.a 0xCD

test lda_ind_y_abs
    LDY #$2
    LDA #$CD
    STA $50
    LDA #$AB
    STA $51
    LDA #$EF
    STA $ABCF
    LDA #0
    LDA ($50),Y
assert reg.p 19
assert reg.a 0xEF
