test bin sec clears c
    CLD
    SEC
    LDA #$58
    ADC #$46
    .byte 2
assert flags.c 0
assert reg.ac 0x9F

test dec sec sets c
    SED
    SEC
    LDA #$58
    ADC #$46
    .byte 2
assert flags.c 1
assert reg.ac 0x05

test dec clc clears c
    SED
    CLC
    LDA #$12
    ADC #$34
    .byte 2
assert flags.c 0
assert reg.ac 0x46

test dec clc clears c
    SED
    CLC
    LDA #$15
    ADC #$26
    .byte 2
assert flags.c 0
assert reg.ac 0x41

test dec clc sets c
    SED
    CLC
    LDA #$81
    ADC #$92
    .byte 2
assert flags.c 1
assert reg.ac 0x73

test dec sbc sec sets c
    SED
    SEC
    LDA #$46
    SBC #$12
    .byte 2
assert flags.c 1
assert reg.ac 0x34

test dec sbc sec sets c
    SED
    SEC
    LDA #$40
    SBC #$13
    .byte 2
assert flags.c 1
assert reg.ac 0x27

test dec clc
    SED
    CLC
    LDA #$32
    SBC #$02
    .byte 2
assert flags.c 1
assert reg.ac 0x29

test dec sbc sec clears c
    SED
    SEC
    LDA #$12
    SBC #$21
    .byte 2
assert flags.c 0
assert reg.ac 0x91

test dec sbc sec clears c
    SED
    SEC
    LDA #$21
    SBC #$34
    .byte 2
assert flags.c 0
assert reg.ac 0x87

test dec clc adc
    SED
    LDA #$05
    CLC
    ADC #$05
    .byte 2
assert reg.ac 0x10

test dec asl
    SED
    LDA #$05
    ASL
    .byte 2
assert reg.ac 0x0A

test dec clc adc
    SED
    LDA #$09
    CLC
    ADC #$01
    .byte 2
assert reg.ac 0x10

test dec inc
    SED
    LDA #$09
    STA $AB
    INC $AB
    .byte 2
assert mem.0xAB 0x0A

test dec sbc sec clears c
    SED
    SEC
    LDA #$12
    SBC #$21
    .byte 2
assert flags.c 0
assert reg.ac 0x91

test dec sbc sec clears c
    SED
    SEC
    LDA #$21
    SBC #$34
    .byte 2
assert flags.c 0
assert reg.ac 0x87
