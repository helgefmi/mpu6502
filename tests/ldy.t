test ldy_imm
    LDY #$B
assert reg.p 2
assert reg.y 0xB
