test ldx_imm
    LDX #$AB
    .byte $2
assert reg.p 3
assert reg.x 0xAB

test ldx_zero
    LDA #$AB
    STA $CD
    LDA #0
    LDX $CD
    .byte $2
assert reg.p 9
assert reg.x 0xAB

test ldx_zero_y
    LDY #$A
    LDA #$BC
    STA $5A
    LDX $50,Y
    .byte $2
assert reg.p 9
assert reg.x 0xBC

test ldx_abs
    LDA #$AB
    STA $ABCD
    LDA #0
    LDX $ABCD
    .byte $2
assert reg.p 11
assert reg.x 0xAB

test ldx_abs_y
    LDA #$AB
    STA $ABDC
    LDY #$DC
    LDX $AB00,Y
    .byte $2
assert reg.p 11
assert reg.x 0xAB
