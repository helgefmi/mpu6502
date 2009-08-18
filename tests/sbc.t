test sbc 0 - 1 = -1
LDA #$00
SBC #$01
assert flags.v 0
assert flags.c 0

test sbc -128 - 1 = -129
LDA #$80
SBC #$01
assert flags.v 1
assert flags.c 1

test sbc 127 - -1 = 128
LDA #$7F
SBC #$FF
assert flags.v 1
assert flags.c 0


test sbc zero
    LDA #$01
    STA $50
    LDA #$11
    SBC $50
assert reg.p 8
assert reg.ac 0x10

test sbc zero x
    LDX #$10
    LDA #$81
    STA $50
    LDA #$01
    SBC $40,X
assert reg.p 10
assert reg.ac 0x80

test sbc abs
    LDA #$81
    STA $5000
    LDA #$01
    SBC $5000
assert reg.p 10
assert reg.ac 0x80

test sbc abs x
    LDX #$10
    LDA #$81
    STA $5000
    LDA #$01
    SBC $4FF0,X
assert reg.p 12
assert reg.ac 0x80

test sbc abs y
    LDY #$10
    LDA #$81
    STA $5000
    LDA #$01
    SBC $4FF0,Y
assert reg.p 12
assert reg.ac 0x80

test sbc ind x
    LDX #$10
    LDA #$AB
    STA $50
    LDA #$81
    STA $AB
    LDA #$01
    SBC ($40,X)
assert reg.p 14
assert reg.ac 0x80

test sbc ind y
    LDY #$0B
    LDA #$A0
    STA $50
    LDA #$81
    STA $AB
    LDA #$01
    SBC ($50),Y
assert reg.p 14
assert reg.ac 0x80
