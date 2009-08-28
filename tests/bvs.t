test bcs dont_branch label
    CLV

    BVS label
    LDX #$AB
    .byte 2

label:
    LDY #$AB
    .byte 2
assert reg.y 0x00
assert reg.x 0xAB

test bcs do_branch label
    LDA #$7F
    ADC #$01

    BVS label
    LDX #$AB
    .byte 2

label:
    LDY #$AB
    .byte 2
assert reg.x 0x00
assert reg.y 0xAB
