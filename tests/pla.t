test pla n flag
    LDA #$AB
    PHA
    LDA #1
    PLA
    .byte $2
assert reg.p 7
assert mem.0x1FF 0xAB
assert mem.0x1FE 0x0
assert reg.sp 0xFF
assert reg.ac 0xAB
assert flags.n 1
assert flags.z 0

test pla z flag
    PHA
    LDA #1
    PLA
    .byte $2
assert reg.p 5
assert mem.0x1FF 0x0
assert mem.0x1FE 0x0
assert reg.sp 0xFF
assert reg.ac 0x0
assert flags.n 0
assert flags.z 1
