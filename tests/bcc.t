test bcc do_branch label
    CLC

    BCC label
    LDX #$AB
    .byte 2

label:
    LDY #$AB
    .byte 2
assert reg.y 0xAB
assert reg.x 0

test bcc dont_branch label
    SEC

    BCC label
    LDX #$AB
    .byte 2

label:
    LDY #$AB
    .byte 2
assert reg.y 0
assert reg.x 0xAB
