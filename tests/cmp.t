test cmp imm n
    LDA #$50
    CMP #$60
assert reg.p 4
assert flags.c 0
assert flags.z 0
assert flags.n 1

test cmp imm z
    LDA #$50
    CMP #$50
assert reg.p 4
assert flags.c 1
assert flags.z 1
assert flags.n 0

test cmp imm c
    LDA #$60
    CMP #$50
assert reg.p 4
assert flags.c 1
assert flags.z 0
assert flags.n 0


test cmp zero
    LDA #$F
    STA $50
    LDA #$F
    CMP $50
assert reg.p 8
assert flags.z 1

test cmp zero x
    LDX #$10
    LDA #$7F
    STA $50
    LDA #$7F
    CMP $40,X
assert reg.p 10
assert flags.z 1

test cmp abs
    LDA #$7F
    STA $5000
    LDA #$7F
    CMP $5000
assert reg.p 10
assert flags.z 1

test cmp abs x
    LDX #$10
    LDA #$7F
    STA $5000
    LDA #$7F
    CMP $4FF0,X
assert reg.p 12
assert flags.z 1

test cmp abs y
    LDY #$10
    LDA #$7F
    STA $5000
    LDA #$7F
    CMP $4FF0,Y
assert reg.p 12
assert flags.z 1

test cmp ind x
    LDX #$10
    LDA #$AB
    STA $50
    LDA #$7F
    STA $AB
    LDA #$7F
    CMP ($40,X)
assert reg.p 14
assert flags.z 1

test cmp ind y
    LDY #$0B
    LDA #$A0
    STA $50
    LDA #$7F
    STA $AB
    LDA #$7F
    CMP ($50),Y
assert reg.p 14
assert flags.z 1
