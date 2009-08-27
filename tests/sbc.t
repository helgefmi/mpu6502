test sbc 0 - 1 = -1
    LDA #$00
    SEC
    SBC #$01
    .byte $2
assert reg.p 6
assert flags.v 0
assert flags.c 0
assert flags.n 1
assert flags.z 0

test sbc -128 - 1 = -129
    LDA #$80
    SEC
    SBC #$01
    .byte $2
assert reg.p 6
assert flags.v 1
assert flags.c 1
assert flags.n 0
assert flags.z 0

test sbc 127 - -1 = 128
    LDA #$7F
    SEC
    SBC #$FF
    .byte $2
assert reg.p 6
assert flags.v 1
assert flags.c 0
assert flags.n 1
assert flags.z 0


test sbc zero
    LDA #$01
    STA $50
    LDA #$11
    SEC
    SBC $50
    .byte $2
assert reg.p 10
assert reg.ac 0x10

test sbc zero x
    LDX #$10
    LDA #$81
    STA $50
    LDA #$01
    SEC
    SBC $40,X
    .byte $2
assert reg.p 12
assert reg.ac 0x80

test sbc abs
    LDA #$81
    STA $5000
    LDA #$01
    SEC
    SBC $5000
    .byte $2
assert reg.p 12
assert reg.ac 0x80

test sbc abs x
    LDX #$10
    LDA #$81
    STA $5000
    LDA #$01
    SEC
    SBC $4FF0,X
    .byte $2
assert reg.p 14
assert reg.ac 0x80

test sbc abs y
    LDY #$10
    LDA #$81
    STA $5000
    LDA #$01
    SEC
    SBC $4FF0,Y
    .byte $2
assert reg.p 14
assert reg.ac 0x80

test sbc ind x
    LDX #$10
    LDA #$AB
    STA $50
    LDA #$81
    STA $AB
    LDA #$01
    SEC
    SBC ($40,X)
    .byte $2
assert reg.p 16
assert reg.ac 0x80

test sbc ind y
    LDY #$0B
    LDA #$A0
    STA $50
    LDA #$81
    STA $AB
    LDA #$01
    SEC
    SBC ($50),Y
    .byte $2
assert reg.p 16
assert reg.ac 0x80


test sbc borrow makes overflow
    LDA #$81
    SBC #1
    .byte 2
assert flags.v 1
assert flags.c 1
