test inx zero
    LDX #$AA
    INX
assert reg.p 3
assert flags.n 1
assert flags.z 0
assert reg.x 0xAB

test inx zero
    LDX #$FF
    INX
assert reg.p 3
assert flags.n 0
assert flags.z 1
assert reg.x 0x0
