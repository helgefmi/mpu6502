test ldy_imm
    LDY #$AB
    .byte $2
assert reg.p 3
assert reg.y 0xAB

test ldy_zero
    LDA #$AB
    STA $CD
    LDA #0
    LDY $CD
    .byte $2
assert reg.p 9
assert reg.y 0xAB

test ldy_zero_x
    LDX #$A
    LDA #$BC
    STA $5A
    LDY $50,X
    .byte $2
assert reg.p 9
assert reg.y 0xBC

test ldy_abs
    LDA #$AB
    STA $ABCD
    LDA #0
    LDY $ABCD
    .byte $2
assert reg.p 11
assert reg.y 0xAB

test ldy_abs_y
    LDA #$AB
    STA $ABDC
    LDX #$DC
    LDY $AB00,X
    .byte $2
assert reg.p 11
assert reg.y 0xAB
