test bmi do_branch label
    LDA #$FF

    BMI label
    LDX #$AB
    .byte 2

label
    LDY #$AB
    .byte 2
assert reg.y 0xAB
assert reg.x 0x0

test bmi dont_branch label
    LDX #1

    BMI label
    LDX #$AB
    .byte 2

label
    LDY #$AB
    .byte 2
assert reg.y 0x0
assert reg.x 0xAB
