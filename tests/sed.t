test sed_1
    SED
    .byte $2
assert reg.p 2
assert flags.d 1
