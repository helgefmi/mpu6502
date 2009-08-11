test lda_imm
    LDA #$A
assert reg.p 2
assert reg.a 0xA

test lda_zero
    LDA #$A
    STA $10
    LDA #0
    LDA $10
assert reg.p 8
assert reg.a 0xA

test lda_abs
    LDA #$A
    STA $1000
    LDA $1000
assert reg.p 8
assert reg.a 0xA

test lda_abs_x
    LDA #$A
    LDX #$A
    STA $100A
    LDA $1000,X
assert reg.p 10
assert reg.a 0xA

test lda_abs_y
    LDA #$A
    STA $100A
    LDY #$A
    LDA $1000,Y
assert reg.p 10
assert reg.a 0xA

test lda_ind_x
    LDX #$3
    LDA #$30
    STA $13
    LDA #$AB
    STA $30
    LDA ($10,X)
assert reg.p 12
assert reg.a 0xAB

test lda_ind_y
    LDY #$3
    LDA #$AB
    STA $10
    LDA #$80
    STA $AE
    LDA ($10),Y
assert reg.a 0x80
