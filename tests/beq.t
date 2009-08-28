test beq dont_branch label
    LDA #1

    BEQ label
    LDX #$AB
    .byte 2

label:
    LDY #$AB
    .byte 2
assert reg.y 0x0
assert reg.x 0xAB

test beq do_branch label
    LDA #0

    BEQ label
    LDX #$AB
    .byte 2

label:
    LDY #$AB
    .byte 2
assert reg.y 0xAB
assert reg.x 0x0
