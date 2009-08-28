test rts simple
    LDX #$AB
    JSR incme
    .byte 2
incme:
    INX
    RTS
assert reg.x 0xAC

test rts advanced
    LDA #$AB
    LDY #$AB
    LDX #$AB
    JSR one
    .byte 2
one:
    INX
    JSR two
    RTS
    .byte 2
two:
    INY
    JSR three
    NOP
    RTS
    .byte 2
three:
    ADC #1
    RTS
incme:
    INX
    RTS
    .byte 2
assert reg.x 0xAC
assert reg.y 0xAC
assert reg.a 0xAC
assert reg.p 10
assert mem.0x1FF 8
assert mem.0x1FE 13
assert mem.0x1FD 19
assert mem.0x1FC 0
