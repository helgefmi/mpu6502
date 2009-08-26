test sec_1
    SEC
    .byte $2
assert reg.p 2
assert flags.c 1
