test bne do_branch label
    LDA #1

    BNE label
    LDX #$AB
    .byte 2

label
    LDY #$AB
    .byte 2
assert reg.y 0xAB
assert reg.x 0x0

test bne dont_branch label
    LDA #0

    BNE label
    LDX #$AB
    .byte 2

label
    LDY #$AB
    .byte 2
assert reg.y 0x0
assert reg.x 0xAB
