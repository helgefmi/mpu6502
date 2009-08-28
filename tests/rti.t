test rti simple
    LDA #label1
    STA $FFFE

    CLV
    CLC

    BRK
    .byte 2

label1:
    LDA #$7F
    ADC #$FF

    LDY #$AB
    SEC
    RTI
    .byte 2

label2:
    LDX #$AB
    .byte 2
assert reg.p 9
assert reg.y 0xAB
assert reg.x 0
assert flags.b 0
assert flags.c 0
assert flags.v 0


test rti simple2
    LDA #label2
    STA $FFFE

    LDA #$7F
    ADC #1
    SEC

    BRK
    .byte 2

label1:
    LDY #$AB
    .byte 2

label2:
    CLC
    CLV

    LDX #$AB
    RTI
    .byte 2
assert reg.p 12
assert reg.y 0
assert reg.x 0xAB
assert flags.b 0
assert flags.c 1
assert flags.v 1


test rti flags
    SEC
    LDA #label2
    STA $FFFE

    BRK
    .byte 2

label1:
    LDY #$AB
    .byte 2

label2:
    LDX #$AB
    CLC
    RTI
    .byte 2
assert reg.p 8
assert reg.y 0
assert reg.x 0xAB
assert mem.0x1FF 7
assert mem.0x1FE 1
assert flags.b 0
assert flags.c 1
assert flags.v 0
