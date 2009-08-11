test ldx_imm
    LDX #$A
assert reg.p 2
assert reg.x 0xA
