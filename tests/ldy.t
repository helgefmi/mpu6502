test ldy_imm
    LDY #$AB
assert reg.p 2
assert reg.y 0xAB

test ldy_zero
    LDA #$AB
    STA $CD
    LDA #0
    LDY $CD
assert reg.p 8
assert reg.y 0xAB

test ldy_zero_x
    LDX #$A
    LDA #$BC
    STA $5A
    LDY $50,X
assert reg.p 8
assert reg.y 0xBC

test ldy_abs
    LDA #$AB
    STA $ABCD
    LDA #0
    LDY $ABCD
assert reg.p 10
assert reg.y 0xAB

test ldy_abs_y
    LDA #$AB
    STA $ABDC
    LDX #$DC
    LDY $AB00,X
assert reg.p 10
assert reg.y 0xAB
