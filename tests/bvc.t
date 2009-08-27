test bvc do_branch label
    CLV

    BVC label
    LDX #$AB
    .byte 2

label
    LDY #$AB
    .byte 2
assert reg.y 0xAB
assert reg.x 0x0

test bvc dont_branch label
    LDA #$7F
    ADC #$01

    BVC label
    LDX #$AB
    .byte 2

label
    LDY #$AB
    .byte 2
assert reg.y 0x0
assert reg.x 0xAB
