test tay_1
    LDA #$AB
    TAY
    .byte $2
assert reg.p 4
assert reg.y 0xAB
