test dey zero
    LDY #$AC
    DEY
assert reg.p 3
assert flags.n 1
assert flags.z 0
assert reg.y 0xAB

test dey zero
    LDY #$00
    DEY
assert reg.p 3
assert flags.n 1
assert flags.z 0
assert reg.y 0xFF
