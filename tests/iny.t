test iny zero
    LDY #$AA
    INY
    .byte 2
assert reg.p 4
assert flags.n 1
assert flags.z 0
assert reg.y 0xAB

test iny zero
    LDY #$FF
    INY
    .byte 2
assert reg.p 4
assert flags.n 0
assert flags.z 1
assert reg.y 0x0
