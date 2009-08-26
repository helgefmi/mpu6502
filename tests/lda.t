test lda_imm
    LDA #$AB
    .byte $2
assert reg.p 3
assert reg.a 0xAB

test lda_zero
    LDA #$AB
    STA $CD
    LDA #0
    LDA $CD
    .byte $2
assert reg.p 9
assert reg.a 0xAB

test lda_zero_x
    LDX #$A
    LDA #$BC
    STA $5A
    LDA $50,X
    .byte $2
assert reg.p 9
assert reg.a 0xBC

test lda_abs
    LDA #$EF
    STA $ABCD
    LDA #0
    LDA $ABCD
    .byte $2
assert reg.p 11
assert reg.a 0xEF

test lda_abs_x
    LDX #$CD
    LDA #$EF
    STA $ABCD
    LDA $AB00,X
    .byte $2
assert reg.p 11
assert reg.a 0xEF

test lda_abs_y
    LDA #$AB
    STA $ABDC
    LDY #$DC
    LDA $AB00,Y
    .byte $2
assert reg.p 11
assert reg.a 0xAB

test lda_ind_x
    LDX #$3
    LDA #$AB
    STA $53
    LDA #$CD
    STA $AB
    LDA #0
    LDA ($50,X)
    .byte $2
assert reg.p 15
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
    .byte $2
assert reg.p 20
assert reg.a 0xEF

test lda_ind_y
    LDY #$3
    LDA #$AB
    STA $50
    LDA #$CD
    STA $AE
    LDA #0
    LDA ($50),Y
    .byte $2
assert reg.p 15
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
    .byte $2
assert reg.p 20
assert reg.a 0xEF
