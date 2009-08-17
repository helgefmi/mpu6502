test tya_1
    LDY #$AB
    TYA
assert reg.p 3
assert reg.a 0xAB
