test pha once
    LDA #$AB
    PHA
    .byte $2
assert reg.p 4
assert mem.0x1FF 0xAB
assert mem.0x1FE 0x0
assert reg.sp 0xFE

test pha thrice
    LDA #$CD
    PHA
    PHA
    PHA
    .byte $2
assert reg.p 6
assert mem.0x1FF 0xCD
assert mem.0x1FE 0xCD
assert mem.0x1FD 0xCD
assert mem.0x1FC 0x0
assert mem.0x200 0x0

test pha ldx/ldy
    LDA #$AB
    PHA
    LDA #$CD
    PHA
    LDX $1FE
    LDY $1FF
    .byte $2
assert reg.p 13
assert mem.0x1FF 0xAB
assert mem.0x1FE 0xCD
assert reg.x 0xCD
assert reg.y 0xAB
