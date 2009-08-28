test bcs dont_branch label
    BCS label
    LDX #$AB
    .byte 2

label:
    LDY #$AB
    .byte 2
assert reg.x 0xAB
assert reg.y 0x0

test bcs do_branch label
    SEC

    BCS label
    LDX #$AB
    .byte 2

label:
    LDY #$AB
    .byte 2
assert reg.x 0x0
assert reg.y 0xAB
