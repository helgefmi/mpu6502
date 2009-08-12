test ldx_imm
    LDX #$AB
assert reg.p 2
assert reg.x 0xAB

test ldx_zero
    LDA #$AB
    STA $CD
    LDA #0
    LDX $CD
assert reg.p 8
assert reg.x 0xAB

test ldx_zero_y
    LDY #$A
    LDA #$BC
    STA $5A
    LDX $50,Y
assert reg.p 8
assert reg.x 0xBC

test ldx_abs
    LDA #$AB
    STA $ABCD
    LDA #0
    LDX $ABCD
assert reg.p 10
assert reg.x 0xAB

test ldx_abs_y
    LDA #$AB
    STA $ABDC
    LDY #$DC
    LDX $AB00,Y
assert reg.p 10
assert reg.x 0xAB
