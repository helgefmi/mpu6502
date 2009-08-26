test dey zero
    LDY #$AC
    DEY
    .byte 2
assert reg.p 4
assert flags.n 1
assert flags.z 0
assert reg.y 0xAB

test dey zero
    LDY #$00
    DEY
    .byte 2
assert reg.p 4
assert flags.n 1
assert flags.z 0
assert reg.y 0xFF
