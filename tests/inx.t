test inx zero
    LDX #$AA
    INX
    .byte 2
assert reg.p 4
assert flags.n 1
assert flags.z 0
assert reg.x 0xAB

test inx zero
    LDX #$FF
    INX
    .byte 2
assert reg.p 4
assert flags.n 0
assert flags.z 1
assert reg.x 0x0
