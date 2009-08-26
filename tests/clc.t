test clc_1
    SEC
    CLC
    .byte 2
assert reg.p 3
assert flags.c 0
