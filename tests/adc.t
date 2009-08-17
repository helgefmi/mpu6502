test adc imm 1 + 1 flags
    LDA #$01
    ADC #$01
assert reg.p 4
assert flags.v 0
assert flags.c 0
assert flags.n 0
assert flags.z 0

test adc imm 1 + -1 flags
    LDA #$01 
    ADC #$FF
assert reg.p 4
assert flags.v 0
assert flags.c 1
assert flags.n 0
assert flags.z 1

test adc imm 127 + 1 flags
    LDA #$7F
    ADC #$01
assert reg.p 4
assert flags.v 1
assert flags.c 0
assert flags.n 1
assert flags.z 0

test adc imm -127 + -1 flags
    LDA #$80
    ADC #$FF
assert reg.p 4
assert flags.c 1
assert flags.v 1
assert flags.n 0
assert flags.z 0


test adc zero
    LDA #$01
    STA $50
    LDA #$F
    ADC $50
assert reg.p 8
assert reg.ac 0x10

test adc zero x
    LDX #$10
    LDA #$7F
    STA $50
    LDA #$01
    ADC $40,X
assert reg.p 10
assert reg.ac 0x80

test adc abs
    LDA #$7F
    STA $5000
    LDA #$01
    ADC $5000
assert reg.p 10
assert reg.ac 0x80

test adc abs x
    LDX #$10
    LDA #$7F
    STA $5000
    LDA #$01
    ADC $4FF0,X
assert reg.p 12
assert reg.ac 0x80

test adc abs y
    LDY #$10
    LDA #$7F
    STA $5000
    LDA #$01
    ADC $4FF0,Y
assert reg.p 12
assert reg.ac 0x80

test adc ind x
    LDX #$10
    LDA #$AB
    STA $50
    LDA #$7F
    STA $AB
    LDA #$01
    ADC ($40,X)
assert reg.p 14
assert reg.ac 0x80

test adc ind y
    LDY #$0B
    LDA #$A0
    STA $50
    LDA #$7F
    STA $AB
    LDA #$01
    ADC ($50),Y
assert reg.p 14
assert reg.ac 0x80
