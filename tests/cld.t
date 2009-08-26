test cld_1
    SED
    CLD
    .byte 2
assert reg.p 3
assert flags.d 0
