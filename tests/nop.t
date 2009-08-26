test nop_1:
    NOP
    NOP
    NOP
    NOP
    NOP
    .byte $2
assert reg.p 6
assert reg.a 0
assert reg.x 0
assert reg.y 0
assert reg.s 0xFF
