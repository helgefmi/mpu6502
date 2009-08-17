test tay_1
    LDA #$AB
    TAY
assert reg.p 3
assert reg.y 0xAB
