test cpy imm n
    LDY #$50
    CPY #$60
assert reg.p 4
assert flags.c 0
assert flags.z 0
assert flags.n 1

test cpy imm z
    LDY #$50
    CPY #$50
assert reg.p 4
assert flags.c 1
assert flags.z 1
assert flags.n 0

test cpy imm c
    LDY #$60
    CPY #$50
assert reg.p 4
assert flags.c 1
assert flags.z 0
assert flags.n 0

test cpy zero
    LDA #$F
    STA $50
    LDY #$F
    CPY $50
assert reg.p 8
assert flags.z 1

test cpy abs
    LDA #$7F
    STA $5000
    LDY #$7F
    CPY $5000
assert reg.p 10
assert flags.z 1
