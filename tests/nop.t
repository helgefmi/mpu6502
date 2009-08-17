test nop_1:
    NOP
    NOP
    NOP
    NOP
    NOP
assert reg.p 5
assert reg.a 0
assert reg.x 0
assert reg.y 0
assert reg.s 0xFF
