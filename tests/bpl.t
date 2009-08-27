test bpl do_branch label
    LDA #1

    BPL label
    LDX #$AB
    .byte 2

label
    LDY #$AB
    .byte 2
assert reg.y 0xAB
assert reg.x 0x0

test bpl dont_branch label
    LDA #$FF

    BPL label
    LDX #$AB
    .byte 2

label
    LDY #$AB
    .byte 2
assert reg.y 0x0
assert reg.x 0xAB
