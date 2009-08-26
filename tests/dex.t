test dex zero
    LDX #$AC
    DEX
    .byte 2
assert reg.p 4
assert flags.n 1
assert flags.z 0
assert reg.x 0xAB

test dex zero
    LDX #$00
    DEX
    .byte 2
assert reg.p 4
assert flags.n 1
assert flags.z 0
assert reg.x 0xFF
