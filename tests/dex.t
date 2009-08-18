test dex zero
    LDX #$AC
    DEX
assert reg.p 3
assert flags.n 1
assert flags.z 0
assert reg.x 0xAB

test dex zero
    LDX #$00
    DEX
assert reg.p 3
assert flags.n 1
assert flags.z 0
assert reg.x 0xFF
