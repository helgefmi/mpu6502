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

test lda_abs
    LDA #$AB
    STA $ABCD
    LDA #0
    LDA $ABCD
assert reg.p 10
assert reg.a 0xAB

test lda_abs_x
    LDX #$A
    LDA #$BC
    STA $100A
    LDA $1000,X
assert reg.p 10
assert reg.a 0xBC

test lda_abs_y
    LDA #$AB
    STA $ABDC
    LDY #$DC
    LDA $AB00,Y
assert reg.p 10
assert reg.a 0xAB

test lda_ind_x
    LDX #$3
    LDA #$99
    STA $53
    LDA #$AB
    STA $99
    LDA ($50,X)
assert reg.p 12
assert reg.a 0xAB

test lda_ind_x_abs
    LDX #$3
    LDA #$CD
    STA $53
    LDA #$AB
    STA $54
    LDA #$89
    STA $ABCD
    LDA ($50,X)
assert reg.p 17
assert reg.a 0x89

test lda_ind_y
    LDY #$3
    LDA #$AB
    STA $50
    LDA #$89
    STA $AE
    LDA ($50),Y
assert reg.p 12
assert reg.a 0x89

test lda_ind_y_abs
    LDY #$2
    LDA #$CD
    STA $50
    LDA #$AB
    STA $51
    LDA #$89
    STA $ABCF
    LDA ($50),Y
assert reg.a 0x89
assert reg.p 17
